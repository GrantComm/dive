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

#pragma once
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include "third_party/libarchive/libarchive/archive.h"
#include "common.h"
#include "dive_core/common/dive_capture_format.h"
#include "dive_core/common/emulate_pm4.h"
#include "dive_core/common/memory_manager_base.h"
#include "log.h"
#include "progress_tracker.h"
#include "gfxr_ext/decode/dive_block_data.h"

// Forward declarations
struct SqttFileChunkAsicInfo;

namespace Dive
{

class CommandHierarchy;
//--------------------------------------------------------------------------------------------------
class MemoryAllocationInfo
{
public:
    // Find the internal memory allocation data for the given range
    // "Internal" allocations are those made by the driver on behalf of the application
    const MemoryAllocationData *FindInternalAllocation(uint64_t va_addr, uint64_t size) const;

    // Find the global memory allocation data for the given range
    // "Global" allocations are those made by the application via vkAllocateMemory
    const MemoryAllocationData *FindGlobalAllocation(uint64_t va_addr, uint64_t size) const;

    // Find the submit memory allocation data for the given range
    // "Submit" allocations are those memory references passed to kernel during submit time
    const MemoryAllocationData *FindSubmitAllocation(uint32_t submit_index,
                                                     uint64_t va_addr,
                                                     uint64_t size) const;

    // Add memory allocation info. The 'type' parameter indicates which array to add it to
    void AddMemoryAllocations(uint32_t                           submit_index,
                              MemoryAllocationsDataHeader::Type  type,
                              DiveVector<MemoryAllocationData> &&allocations);

private:
    struct SubmitAllocations
    {
        uint32_t                         m_submit_index;
        DiveVector<MemoryAllocationData> m_allocations;
    };

    // Allocations done by the driver, for resources like load-sh buffers, shader binaries, etc
    DiveVector<MemoryAllocationData> m_internal_allocs;

    // Allocations done by the application via vkAllocateMemory
    DiveVector<MemoryAllocationData> m_global_allocs;
};

//--------------------------------------------------------------------------------------------------
// Container for the memory data of a memory block
struct MemoryData
{
    uint32_t m_data_size;
    uint8_t *m_data_ptr;
};

//--------------------------------------------------------------------------------------------------
// Handles the loading/storage/caching of all memory blocks in the capture data file
// Assumption is that memory is not re-used from within a submit, but can be re-used
//  in between submits. So a "submit_index" is an important identifier for a memory block.
class MemoryManager : public IMemoryManager
{
public:
    virtual ~MemoryManager();

    // Use an r-value reference instead of normal reference to prevent an extra copy
    // Given the amount of memory potentially in a capture, this can be significant
    void AddMemoryBlock(uint32_t submit_index, uint64_t va_addr, MemoryData &&data);

    // Add memory allocation info to internal MemoryAllocationInfo object
    void AddMemoryAllocations(uint32_t                           submit_index,
                              MemoryAllocationsDataHeader::Type  type,
                              DiveVector<MemoryAllocationData> &&allocations);

    // Finalize load. After this, no memory block should be added!
    // same_submit_copy_only - If set, then RetrieveMemoryData() will only copy from memory blocks
    // used in the same submit. If not set, then allowed to use any allocations from any submit,
    // with the assumption that there is no overlap in captured memory
    void Finalize(bool same_submit_copy_only, bool duplicate_ib_capture);

    const MemoryAllocationInfo &GetMemoryAllocationInfo() const;

    // Load the given va/size from the memory blocks
    virtual bool RetrieveMemoryData(void    *buffer_ptr,
                                    uint32_t submit_index,
                                    uint64_t va_addr,
                                    uint64_t size) const override;

    // Keep grabbing contiguous memory blocks until the callback returns false
    virtual bool GetMemoryOfUnknownSizeViaCallback(uint32_t     submit_index,
                                                   uint64_t     va_addr,
                                                   PfnGetMemory data_callback,
                                                   void        *user_ptr) const override;

    // Given an address, find the maximum contiguous amount of memory accessible from that point
    virtual uint64_t GetMaxContiguousSize(uint32_t submit_index, uint64_t va_addr) const override;

    // Determine if given range is covered by memory blocks
    virtual bool IsValid(uint32_t submit_index, uint64_t addr, uint64_t size) const override;

private:
    struct MemoryBlock
    {
        uint64_t m_va_addr;
        uint32_t m_submit_index;
        uint32_t m_data_size;
        uint8_t *m_data_ptr;
    };

    // mutable variable for caching reasons
    mutable const MemoryBlock *m_last_used_block_ptr = nullptr;

    // Memory blocks containing all the captured memory data
    DiveVector<MemoryBlock> m_memory_blocks;

    // All the captured memory allocation info
    MemoryAllocationInfo m_memory_allocations;

    // If set, then only memory blocks from same submit are considered
    // Otherwise, all previous submits are considered as well
    bool m_same_submit_only = true;
};

//--------------------------------------------------------------------------------------------------
class FileReader
{
public:
    FileReader(const char *file_name);
    int     open();
    int64_t read(char *buf, int64_t size);
    int     close();

private:
    std::string                                                   m_file_name;
    std::unique_ptr<struct archive, decltype(&archive_read_free)> m_handle;
};

//--------------------------------------------------------------------------------------------------
class TextInfo
{
public:
    TextInfo(std::string name, uint64_t size, DiveVector<char> &&data);

    const std::string &GetName() const;
    uint64_t           GetSize() const;
    const char        *GetText() const;

private:
    std::string      m_name;
    uint64_t         m_size;
    DiveVector<char> m_text;
};

//--------------------------------------------------------------------------------------------------
class CaptureData
{
public:
    enum class LoadResult
    {
        kSuccess,
        kFileIoError,
        kCorruptData,
        kVersionError
    };
    CaptureData();
    CaptureData(ILog *log_ptr);
    CaptureData(ProgressTracker *progress_tracker, ILog *log_ptr);
    virtual ~CaptureData();

    CaptureData &operator=(CaptureData &&) = default;

#if defined(DIVE_ENABLE_PERFETTO)
    LoadResult LoadPerfettoFile(const char *file_name);
#endif

private:
    bool       LoadCapture(std::istream &capture_file, const CaptureDataHeader &data_header);

    void Finalize(const CaptureDataHeader &data_header);

    CaptureDataHeader::CaptureType m_capture_type;
    DiveVector<SubmitInfo>         m_submits;
    VulkanMetadataBlockHeader      m_vulkan_metadata_header;
    MemoryManager                  m_memory;
    ProgressTracker               *m_progress_tracker;
    ILog                          *m_log_ptr;
    std::string                    m_cur_capture_file;
    CaptureDataHeader              m_data_header;
};

std::ostream& operator<<(std::ostream& os, const CaptureData::LoadResult& r);

}  // namespace Dive
