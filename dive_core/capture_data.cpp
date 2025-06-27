/*
 Copyright 2019 Google LLC

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#include "capture_data.h"

#include <assert.h>
#include <string.h>  // memcpy
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <memory>
#include "archive.h"
#include "dive_core/command_hierarchy.h"
#include "dive_core/common/common.h"
#include "freedreno_dev_info.h"
#include "generated/generated_vulkan_dive_consumer.h"
#if defined(DIVE_ENABLE_PERFETTO)
#    include "perfetto_trace/trace_reader.h"
#endif
#include "pm4_info.h"
#include "gfxr_ext/decode/dive_file_processor.h"
#include "third_party/gfxreconstruct/framework/generated/generated_vulkan_decoder.h"

namespace Dive
{

//--------------------------------------------------------------------------------------------------
FileReader::FileReader(const char *file_name) :
    m_file_name(file_name),
    m_handle(std::unique_ptr<struct archive, decltype(&archive_read_free)>(archive_read_new(),
                                                                           &archive_read_free))
{
    DIVE_ASSERT(m_handle != nullptr);
}

//--------------------------------------------------------------------------------------------------
int FileReader::open()
{
    // Enables auto-detection code and decompression support for gzip
    int ret = archive_read_support_filter_gzip(m_handle.get());
    if (ret != ARCHIVE_OK)
    {
        std::cerr << "error archive_read_support_filter_gzip: "
                  << archive_error_string(m_handle.get());
        return ret;
    }

    ret = archive_read_support_filter_none(m_handle.get());
    if (ret != ARCHIVE_OK)
    {
        std::cerr << "error archive_read_support_filter_none: "
                  << archive_error_string(m_handle.get());
        return ret;
    }

    // Enables support for all available formats except the "raw" format
    ret = archive_read_support_format_all(m_handle.get());
    if (ret != ARCHIVE_OK)
    {
        std::cerr << "error archive_read_support_format_all: "
                  << archive_error_string(m_handle.get());
        return ret;
    }

    // The "raw" format handler allows libarchive to be used to read arbitrary data.
    ret = archive_read_support_format_raw(m_handle.get());
    if (ret != ARCHIVE_OK)
    {
        std::cerr << "error archive_read_support_format_raw: "
                  << archive_error_string(m_handle.get());
        return ret;
    }

    ret = archive_read_open_filename(m_handle.get(), m_file_name.c_str(), 10240);
    if (ret != ARCHIVE_OK)
    {
        std::cerr << "error archive_read_open_filename: " << archive_error_string(m_handle.get());
        return ret;
    }
    struct archive_entry *entry;
    ret = archive_read_next_header(m_handle.get(), &entry);
    if (ret != ARCHIVE_OK)
    {
        std::cerr << "error archive_read_next_header: " << archive_error_string(m_handle.get());
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
int64_t FileReader::read(char *buf, int64_t nbytes)
{
    char   *ptr = buf;
    int64_t ret = 0;
    while (nbytes > 0)
    {
        int64_t n = archive_read_data(m_handle.get(), ptr, nbytes);
        if (n < 0)
        {
            std::cerr << "error archive_read_data: " << archive_error_string(m_handle.get());
            return n;
        }
        if (n == 0)
            break;
        ptr += n;
        nbytes -= n;
        ret += n;
    }
    return ret;
}

//--------------------------------------------------------------------------------------------------
int FileReader::close()
{
    m_handle = nullptr;
    return 0;
}

// =================================================================================================
// MemoryAllocationInfo
// =================================================================================================
const MemoryAllocationData *MemoryAllocationInfo::FindInternalAllocation(uint64_t va_addr,
                                                                         uint64_t size) const
{
    for (uint32_t alloc = 0; alloc < m_internal_allocs.size(); ++alloc)
    {
        const MemoryAllocationData &alloc_data = m_internal_allocs[alloc];
        if ((alloc_data.m_gpu_virt_addr <= va_addr) &&
            ((va_addr + size) <= (alloc_data.m_gpu_virt_addr + alloc_data.m_size)))
        {
            return &alloc_data;
        }
    }
    return nullptr;
}

//--------------------------------------------------------------------------------------------------
const MemoryAllocationData *MemoryAllocationInfo::FindGlobalAllocation(uint64_t va_addr,
                                                                       uint64_t size) const
{
    for (uint32_t alloc = 0; alloc < m_global_allocs.size(); ++alloc)
    {
        const MemoryAllocationData &alloc_data = m_global_allocs[alloc];
        if ((alloc_data.m_gpu_virt_addr <= va_addr) &&
            ((va_addr + size) <= (alloc_data.m_gpu_virt_addr + alloc_data.m_size)))
        {
            return &alloc_data;
        }
    }
    return nullptr;
}

//--------------------------------------------------------------------------------------------------
void MemoryAllocationInfo::AddMemoryAllocations(uint32_t                           submit_index,
                                                MemoryAllocationsDataHeader::Type  type,
                                                DiveVector<MemoryAllocationData> &&allocations)
{
    // There can only be 1 single internal and global allocation set, but there can
    // potentially be a submission allocation set *per* submit
    if (type == MemoryAllocationsDataHeader::Type::kInternal)
    {
        DIVE_ASSERT(m_internal_allocs.empty());
        m_internal_allocs = allocations;
    }
    else if (type == MemoryAllocationsDataHeader::Type::kGlobal)
    {
        DIVE_ASSERT(m_global_allocs.empty());
        m_global_allocs = allocations;
    }
}

// =================================================================================================
// MemoryManager
// =================================================================================================
MemoryManager::~MemoryManager()
{
    for (uint32_t i = 0; i < m_memory_blocks.size(); ++i)
    {
        delete[] m_memory_blocks[i].m_data_ptr;
    }
}

//--------------------------------------------------------------------------------------------------
void MemoryManager::AddMemoryBlock(uint32_t submit_index, uint64_t va_addr, MemoryData &&data)
{
    MemoryBlock mem_block;
    mem_block.m_submit_index = submit_index;
    mem_block.m_va_addr = va_addr;
    mem_block.m_data_size = data.m_data_size;
    mem_block.m_data_ptr = data.m_data_ptr;
    m_memory_blocks.push_back(mem_block);

    // Clear the MemoryData since ownership of the data memory has been "moved"
    data.m_data_size = 0;
    data.m_data_ptr = nullptr;
}

//--------------------------------------------------------------------------------------------------
void MemoryManager::AddMemoryAllocations(uint32_t                           submit_index,
                                         MemoryAllocationsDataHeader::Type  type,
                                         DiveVector<MemoryAllocationData> &&allocations)
{
    m_memory_allocations.AddMemoryAllocations(submit_index, type, std::move(allocations));
}

//--------------------------------------------------------------------------------------------------
void MemoryManager::Finalize(bool same_submit_copy_only, bool duplicate_ib_capture)
{
    m_same_submit_only = same_submit_copy_only;

    // Sorting required for GetMaxContiguousSize(), GetMemoryOfUnknownSizeViaCallback(), and others
    // Important: Preserve order of equivalent blocks using stable_sort (later blocks have more
    // updated view of memory)
    std::stable_sort(m_memory_blocks.begin(),
                     m_memory_blocks.end(),
                     [&](const MemoryBlock &lhs, const MemoryBlock &rhs) -> bool {
                         // Only if m_same_submit_only does the submit affect the sort order
                         // When this flag is not enabled, then the memory is "flattened" and memory
                         // can be captured from any submit (ie: memory tracker not reset between
                         // submits)
                         if (m_same_submit_only)
                         {
                             // Sort by submit, then by address
                             if (lhs.m_submit_index == rhs.m_submit_index)
                                 return (lhs.m_va_addr < rhs.m_va_addr);
                             return lhs.m_submit_index < rhs.m_submit_index;
                         }
                         return (lhs.m_va_addr < rhs.m_va_addr);
                     });

    // In libwrap, sometimes we re-capture buffers that have been suballocated from. This means the
    // *later* buffers have a more up-to-date view of memory
    if (m_same_submit_only)
    {
        DiveVector<MemoryBlock> temp_memory_blocks;

        uint64_t prev_addr = 0;
        uint64_t prev_submit = 0;
        uint32_t prev_size = 0;
        for (uint32_t i = 0; i < m_memory_blocks.size(); ++i)
        {
            const MemoryBlock &memory_block = m_memory_blocks[i];

            if (memory_block.m_submit_index != prev_submit)
            {
                prev_submit = memory_block.m_submit_index;
                temp_memory_blocks.push_back(memory_block);
            }
            else
            {
                // Check if it's a completely new block
                if (memory_block.m_va_addr >= (prev_addr + prev_size))
                    temp_memory_blocks.push_back(memory_block);
                else
                {
                    // It's EITHER a new block or it has the same address as the previous block
                    // (i.e. whole or partial overwrite)
                    DIVE_ASSERT(memory_block.m_va_addr == prev_addr);

                    // Use whichever one is bigger and get rid of the smaller one
                    if (memory_block.m_data_size >= temp_memory_blocks.back().m_data_size)
                    {
                        // Replace previous memory block with current one
                        delete[] temp_memory_blocks.back().m_data_ptr;
                        temp_memory_blocks.back() = m_memory_blocks[i];
                    }
                    else
                    {
                        delete[] m_memory_blocks[i].m_data_ptr;
                    }
                }
            }
            prev_addr = memory_block.m_va_addr;
            prev_size = memory_block.m_data_size;
        }
        m_memory_blocks = std::move(temp_memory_blocks);
    }

#ifndef NDEBUG
    // Sanity check
    //      same_submit_only == true -> Make sure there are no overlaps within same submit
    //      same_submit_only == false -> Make sure there are no overlaps, period
    if (m_same_submit_only)
    {
        uint64_t cur_addr = 0;
        uint64_t cur_submit = 0;
        for (uint32_t i = 0; i < m_memory_blocks.size(); ++i)
        {
            const MemoryBlock &memory_block = m_memory_blocks[i];

            if (memory_block.m_submit_index != cur_submit)
                cur_submit = memory_block.m_submit_index;
            else
                DIVE_ASSERT(memory_block.m_va_addr >= cur_addr);
            cur_addr = memory_block.m_va_addr + memory_block.m_data_size;
        }
    }
    else
    {
        // This will trigger if IBs are captured more than once
        // There might be edge cases where duplicate IB capture can cause memory not to be
        // grabbed properly, especially if those IBs span multiple blocks. But generally isn't a big
        // issue and duplicate_ib_capture only applies to early captures which should be made
        // obsolete very soon
        if (!duplicate_ib_capture)
        {
            uint64_t cur_addr = 0;
            uint32_t cur_submit = 0;
            for (uint32_t i = 0; i < m_memory_blocks.size(); ++i)
            {
                const MemoryBlock &memory_block = m_memory_blocks[i];
                DIVE_ASSERT(memory_block.m_submit_index != cur_submit ||
                            memory_block.m_va_addr >= cur_addr);
                cur_addr = memory_block.m_va_addr + memory_block.m_data_size;
                cur_submit = memory_block.m_submit_index;
            }
        }
    }
#endif
}

//--------------------------------------------------------------------------------------------------
const MemoryAllocationInfo &MemoryManager::GetMemoryAllocationInfo() const
{
    return m_memory_allocations;
}

//--------------------------------------------------------------------------------------------------
bool MemoryManager::RetrieveMemoryData(void    *buffer_ptr,
                                       uint32_t submit_index,
                                       uint64_t va_addr,
                                       uint64_t size) const
{
    // Check the last-used block first, because this is the desired block most of the time
    if (m_last_used_block_ptr != nullptr)
    {
        const MemoryBlock &mem_block = *m_last_used_block_ptr;
        uint64_t           mem_block_end_addr = mem_block.m_va_addr + mem_block.m_data_size;
        uint64_t           end_addr = va_addr + size;

        // Can only use the cached block if it fully encompasses the desired region
        bool valid_submit = m_same_submit_only ? (submit_index == mem_block.m_submit_index) : true;
        bool encompasses = (mem_block.m_va_addr <= va_addr) && (end_addr <= mem_block_end_addr);
        if (valid_submit && encompasses)
        {
#ifndef NDEBUG
            if (mem_block.m_data_size >= 16 * 1024 * 1024)
            {
                std::cout << "MemoryManager::RetrieveMemoryData data.m_data_size: "
                          << mem_block.m_data_size << " gpu addr:  " << va_addr << std::endl;
            }
#endif
            memcpy(buffer_ptr, (void *)&mem_block.m_data_ptr[va_addr - mem_block.m_va_addr], size);
            return true;
        }
    }

    // Iterate through the memory blocks to find overlapping blocks and do the appropriate memcopies
    uint64_t           amount_copied = 0;
    uint32_t           num_memory_blocks = (uint32_t)m_memory_blocks.size();
    const MemoryBlock *memory_blocks = (num_memory_blocks > 0) ? &m_memory_blocks.front() : nullptr;
    for (uint32_t i = num_memory_blocks - 1; i != UINT32_MAX; --i)
    {
        const MemoryBlock &mem_block = memory_blocks[i];

        uint64_t mem_block_end_addr = mem_block.m_va_addr + mem_block.m_data_size;
        uint64_t end_addr = va_addr + size;
        bool valid_submit = m_same_submit_only ? (submit_index == mem_block.m_submit_index) : true;
        bool overlaps = (va_addr < mem_block_end_addr) && (mem_block.m_va_addr < end_addr);
        if (valid_submit && overlaps)
        {
            m_last_used_block_ptr = &mem_block;
            uint64_t max_start_addr = std::max(va_addr, mem_block.m_va_addr);
            uint64_t min_end_addr = std::min(mem_block_end_addr, end_addr);
            uint64_t src_offset = max_start_addr - mem_block.m_va_addr;
            uint64_t dst_offset = max_start_addr - va_addr;
            uint64_t size_to_copy = min_end_addr - max_start_addr;

            const uint8_t *src_data_ptr = &mem_block.m_data_ptr[0];
            memcpy((uint8_t *)buffer_ptr + dst_offset, src_data_ptr + src_offset, size_to_copy);
            amount_copied += size_to_copy;
#ifndef NDEBUG
            static int64_t max_buffer_size = 0;
            if (max_buffer_size < mem_block.m_data_size)
            {
                max_buffer_size = mem_block.m_data_size;
                std::cout << "max_buffer_size: " << max_buffer_size << std::endl;
            }
#endif
            // Since capture requirement is there's no overlap in m_memory_blocks within the same
            // submit, if the memory is fully captured, then there should be exactly 'size' amount
            // memcpy-ed
            if (amount_copied == size)
                return true;
        }
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
bool MemoryManager::GetMemoryOfUnknownSizeViaCallback(uint32_t     submit_index,
                                                      uint64_t     va_addr,
                                                      PfnGetMemory data_callback,
                                                      void        *user_ptr) const
{
    uint64_t cur_addr = va_addr;

    // Iterate through the memory blocks to find the biggest block that contains the passed-in addr
    // Note: m_same_submit_only => Blocks are sorted by submit, then by address
    //       otherwise they are just sorted by address
    for (uint64_t i = 0; i < m_memory_blocks.size(); ++i)
    {
        const MemoryBlock &mem_block = m_memory_blocks[i];
        bool valid_submit = m_same_submit_only ? (submit_index == mem_block.m_submit_index) : true;
        if (valid_submit)
        {
            if (cur_addr == va_addr)
            {
                // First block just has to contain this address
                uint64_t mem_block_end_addr = mem_block.m_va_addr + mem_block.m_data_size;
                if (mem_block.m_va_addr <= va_addr && va_addr < mem_block_end_addr)
                {
                    void    *data_ptr = mem_block.m_data_ptr + (va_addr - mem_block.m_va_addr);
                    uint64_t size = mem_block_end_addr - va_addr;
                    if (!data_callback(data_ptr, va_addr, size, user_ptr))
                        break;  // Callback indicates no more searching is needed
                    cur_addr = mem_block_end_addr;
                }
            }
            else if (cur_addr == mem_block.m_va_addr)
            {
                if (!data_callback(mem_block.m_data_ptr, cur_addr, mem_block.m_data_size, user_ptr))
                    break;  // Callback indicates no more searching is needed

                // Is contiguous. Update the cur_addr to reflect this block.
                cur_addr = mem_block.m_va_addr + mem_block.m_data_size;
            }
            else if (cur_addr != va_addr)
            {
                // Not contiguous, and found a discountinuity in captured address range
                // So safe to early out instead of continuing the search
                return true;
            }
        }
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
uint64_t MemoryManager::GetMaxContiguousSize(uint32_t submit_index, uint64_t va_addr) const
{
    uint64_t cur_addr = va_addr;

    // Iterate through the memory blocks to find the biggest block that contains the passed-in addr
    // Note: m_same_submit_only => Blocks are sorted by submit, then by address
    //       otherwise they are just sorted by address
    for (uint64_t i = 0; i < m_memory_blocks.size(); ++i)
    {
        const MemoryBlock &mem_block = m_memory_blocks[i];
        bool valid_submit = m_same_submit_only ? (submit_index == mem_block.m_submit_index) : true;
        if (valid_submit)
        {
            if (cur_addr == va_addr)
            {
                // First block just has to contain this address
                uint64_t mem_block_end_addr = mem_block.m_va_addr + mem_block.m_data_size;
                if (mem_block.m_va_addr <= va_addr && va_addr < mem_block_end_addr)
                    cur_addr = mem_block_end_addr;
            }
            else if (cur_addr == mem_block.m_va_addr)
            {
                // Is contiguous. Update the cur_addr to reflect this block.
                cur_addr = mem_block.m_va_addr + mem_block.m_data_size;
            }
            else if (cur_addr != va_addr)
            {
                // Not contiguous, and found a discountinuity in captured address range
                // So safe to early out instead of continuing the search
                return (cur_addr - va_addr);
            }
        }
    }
    return (cur_addr - va_addr);
}

//--------------------------------------------------------------------------------------------------
bool MemoryManager::IsValid(uint32_t submit_index, uint64_t addr, uint64_t size) const
{
    uint64_t max_size = GetMaxContiguousSize(submit_index, addr);
    return (max_size >= size);
}

// =================================================================================================
// TextInfo
// =================================================================================================
TextInfo::TextInfo(std::string name, uint64_t size, DiveVector<char> &&text)
{
    m_name = std::move(name);
    m_size = size;
    m_text = text;
}

//--------------------------------------------------------------------------------------------------
const std::string &TextInfo::GetName() const
{
    return m_name;
}

//--------------------------------------------------------------------------------------------------
uint64_t TextInfo::GetSize() const
{
    return m_size;
}

//--------------------------------------------------------------------------------------------------
const char *TextInfo::GetText() const
{
    return m_text.data();
}

// =================================================================================================
// CaptureData
// =================================================================================================
CaptureData::CaptureData() :
    m_progress_tracker(NULL),
    m_log_ptr(&LogNull::GetInstance())
{
}

//--------------------------------------------------------------------------------------------------
CaptureData::CaptureData(ILog *log_ptr) :
    m_progress_tracker(NULL),
    m_log_ptr(log_ptr)
{
}

//--------------------------------------------------------------------------------------------------
CaptureData::CaptureData(ProgressTracker *progress_tracker, ILog *log_ptr) :
    m_progress_tracker(progress_tracker),
    m_log_ptr(log_ptr)
{
}

//--------------------------------------------------------------------------------------------------
CaptureData::~CaptureData()
{
}

//--------------------------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const CaptureData::LoadResult &r)
{
    switch (r)
    {
    case CaptureData::LoadResult::kSuccess:
        os << "Success";
        break;
    case CaptureData::LoadResult::kFileIoError:
        os << "File IO Error";
        break;
    case CaptureData::LoadResult::kCorruptData:
        os << "Corrupt Data";
        break;
    case CaptureData::LoadResult::kVersionError:
        os << "Version Error";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}

}  // namespace Dive
