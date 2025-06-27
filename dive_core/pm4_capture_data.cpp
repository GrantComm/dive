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

#include "pm4_capture_data.h"

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

namespace
{
constexpr const uint64_t
kMaxNumMemAlloc = (uint64_t(24) << 30) /
                  (4 * 1024);  // Number of allocation in 4k chunks for 16+8 GiB memory
constexpr const uint32_t kMaxMemAllocSize = 1 << 30;      // 1 GiB
constexpr const uint32_t kMaxStrLen = 100 << 20;          // 100 MiB
constexpr const uint32_t kMaxNumWavesPerBlock = 1 << 20;  // 1 MiB
constexpr const uint32_t kMaxNumSGPRPerWave = 1 << 20;    // 1 MiB
constexpr const uint32_t kMaxNumVGPRPerWave = 1 << 20;    // 1 MiB
}  // namespace

// =================================================================================================
// SubmitInfo
// =================================================================================================
SubmitInfo::SubmitInfo(EngineType                       engine_type,
                       QueueType                        queue_type,
                       uint8_t                          engine_index,
                       bool                             is_dummy_submit,
                       DiveVector<IndirectBufferInfo> &&ibs)
{
    m_engine_type = engine_type;
    m_queue_type = queue_type;
    m_engine_index = engine_index;
    m_is_dummy_submit = is_dummy_submit;
    m_ibs = ibs;
}

//--------------------------------------------------------------------------------------------------
EngineType SubmitInfo::GetEngineType() const
{
    return m_engine_type;
}

//--------------------------------------------------------------------------------------------------
QueueType SubmitInfo::GetQueueType() const
{
    return m_queue_type;
}

//--------------------------------------------------------------------------------------------------
uint8_t SubmitInfo::GetEngineIndex() const
{
    return m_engine_index;
}

//--------------------------------------------------------------------------------------------------
bool SubmitInfo::IsDummySubmit() const
{
    return m_is_dummy_submit;
}

//--------------------------------------------------------------------------------------------------
uint32_t SubmitInfo::GetNumIndirectBuffers() const
{
    return (uint32_t)m_ibs.size();
}

//--------------------------------------------------------------------------------------------------
const IndirectBufferInfo &SubmitInfo::GetIndirectBufferInfo(uint32_t ib_index) const
{
    return m_ibs[ib_index];
}

//--------------------------------------------------------------------------------------------------
const IndirectBufferInfo *SubmitInfo::GetIndirectBufferInfoPtr() const
{
    return &m_ibs[0];
}

//--------------------------------------------------------------------------------------------------
void SubmitInfo::AppendIb(const IndirectBufferInfo &ib)
{
    m_ibs.push_back(ib);
}

// =================================================================================================
// Present Info
// =================================================================================================
PresentInfo::PresentInfo()
{
    m_valid_data = false;
}

//--------------------------------------------------------------------------------------------------
PresentInfo::PresentInfo(EngineType engine_type,
                         QueueType  queue_type,
                         uint32_t   submit_index,
                         bool       full_screen,
                         uint64_t   addr,
                         uint64_t   size,
                         uint32_t   vk_format,
                         uint32_t   vk_color_space)
{
    m_valid_data = true;
    m_engine_type = engine_type;
    m_queue_type = queue_type;
    m_submit_index = submit_index;
    m_full_screen = full_screen;
    m_addr = addr;
    m_size = size;
    m_vk_format = vk_format;
    m_vk_color_space = vk_color_space;
}

//--------------------------------------------------------------------------------------------------
bool PresentInfo::HasValidData() const
{
    return m_valid_data;
}

//--------------------------------------------------------------------------------------------------
EngineType PresentInfo::GetEngineType() const
{
    return m_engine_type;
}

//--------------------------------------------------------------------------------------------------
QueueType PresentInfo::GetQueueType() const
{
    return m_queue_type;
}

//--------------------------------------------------------------------------------------------------
uint32_t PresentInfo::GetSubmitIndex() const
{
    return m_submit_index;
}

//--------------------------------------------------------------------------------------------------
bool PresentInfo::IsFullScreen() const
{
    return m_full_screen;
}

//--------------------------------------------------------------------------------------------------
uint64_t PresentInfo::GetSurfaceAddr() const
{
    return m_addr;
}

//--------------------------------------------------------------------------------------------------
uint64_t PresentInfo::GetSurfaceSize() const
{
    return m_size;
}

//--------------------------------------------------------------------------------------------------
uint32_t PresentInfo::GetSurfaceVkFormat() const
{
    return m_vk_format;
}

//--------------------------------------------------------------------------------------------------
uint32_t PresentInfo::GetSurfaceVkColorSpaceKHR() const
{
    return m_vk_color_space;
}

// =================================================================================================
// RingInfo
// =================================================================================================
RingInfo::RingInfo(QueueType queue_type,
                   uint32_t  queue_index,
                   uint64_t  ring_base_addr,
                   uint32_t  ring_full_size,
                   uint64_t  ring_capture_addr,
                   uint32_t  ring_capture_size,
                   uint64_t  hang_ib_addr,
                   uint64_t  hang_size_left,
                   uint64_t  fence_signaled_addr,
                   uint64_t  fence_emitted_addr)
{
    m_queue_type = queue_type;
    m_queue_index = queue_index;
    m_ring_base_addr = ring_base_addr;
    m_ring_full_size = ring_full_size;
    m_ring_capture_addr = ring_capture_addr;
    m_ring_capture_size = ring_capture_size;
    m_hang_ib_addr = hang_ib_addr;
    m_hang_size_left = hang_size_left;
    m_fence_signaled_addr = fence_signaled_addr;
    m_fence_emitted_addr = fence_emitted_addr;
}

//--------------------------------------------------------------------------------------------------
QueueType RingInfo::GetQueueType() const
{
    return m_queue_type;
}

//--------------------------------------------------------------------------------------------------
uint32_t RingInfo::GetQueueIndex() const
{
    return m_queue_index;
}

//--------------------------------------------------------------------------------------------------
uint64_t RingInfo::GetRingBaseAddress() const
{
    return m_ring_base_addr;
}

//--------------------------------------------------------------------------------------------------
uint32_t RingInfo::GetRingSize() const
{
    return m_ring_full_size;
}

//--------------------------------------------------------------------------------------------------
uint64_t RingInfo::GetRingCaptureAddress() const
{
    return m_ring_capture_addr;
}

//--------------------------------------------------------------------------------------------------
uint32_t RingInfo::GetRingCaptureSize() const
{
    return m_ring_capture_size;
}

//--------------------------------------------------------------------------------------------------
uint64_t RingInfo::GetHungIbAddress() const
{
    return m_hang_ib_addr;
}

//--------------------------------------------------------------------------------------------------
uint64_t RingInfo::GetHungSizeLeft() const
{
    return m_hang_size_left;
}

//--------------------------------------------------------------------------------------------------
uint64_t RingInfo::GetEmittedFenceAddress() const
{
    return m_fence_emitted_addr;
}

//--------------------------------------------------------------------------------------------------
uint64_t RingInfo::GetSignaledFenceAddress() const
{
    return m_fence_signaled_addr;
}

// =================================================================================================
// WaveInfo
// =================================================================================================
WaveStateInfo::WaveStateInfo(const Dive::WaveState &state,
                             DiveVector<uint32_t> &&sgprs,
                             DiveVector<uint32_t> &&vgprs,
                             DiveVector<uint32_t> &&ttmps)
{
    m_state = state;
    m_sgprs = sgprs;
    m_vgprs = vgprs;
    m_ttmps = ttmps;
}

//--------------------------------------------------------------------------------------------------
const Dive::WaveState &WaveStateInfo::GetState() const
{
    return m_state;
}

//--------------------------------------------------------------------------------------------------
const DiveVector<uint32_t> &WaveStateInfo::GetSGPRs() const
{
    return m_sgprs;
}

//--------------------------------------------------------------------------------------------------
const DiveVector<uint32_t> &WaveStateInfo::GetVGPRs() const
{
    return m_vgprs;
}

//--------------------------------------------------------------------------------------------------
const DiveVector<uint32_t> &WaveStateInfo::GetTTMPs() const
{
    return m_ttmps;
}

// =================================================================================================
// WaveInfo
// =================================================================================================
WaveInfo::WaveInfo(DiveVector<WaveStateInfo> &&waves)
{
    m_waves = waves;
}

//--------------------------------------------------------------------------------------------------
const DiveVector<WaveStateInfo> &WaveInfo::GetWaves() const
{
    return m_waves;
}

// =================================================================================================
// RegisterInfo
// =================================================================================================
RegisterInfo::RegisterInfo(std::map<std::string, uint32_t> &&regs)
{
    m_registers = regs;
}

//--------------------------------------------------------------------------------------------------
const std::map<std::string, uint32_t> &RegisterInfo::GetRegisters() const
{
    return m_registers;
}

// =================================================================================================
// CaptureData
// =================================================================================================
Pm4CaptureData::Pm4CaptureData() :
    m_progress_tracker(NULL),
    m_log_ptr(&LogNull::GetInstance())
{
}

//--------------------------------------------------------------------------------------------------
Pm4CaptureData::Pm4CaptureData(ILog *log_ptr) :
    m_progress_tracker(NULL),
    m_log_ptr(log_ptr)
{
}

//--------------------------------------------------------------------------------------------------
Pm4CaptureData::Pm4CaptureData(ProgressTracker *progress_tracker, ILog *log_ptr) :
    m_progress_tracker(progress_tracker),
    m_log_ptr(log_ptr)
{
}

//--------------------------------------------------------------------------------------------------
CaptureData::LoadResult Pm4CaptureData::LoadFile(const char *file_name)
{
    std::string file_name_(file_name);
    std::string file_extension = std::filesystem::path(file_name_).extension().generic_string();

    if (file_extension.compare(".dive") == 0)
    {
        return LoadCaptureFile(file_name);
    }
    else if (file_extension.compare(".rd") == 0)
    {
#if defined(DIVE_ENABLE_PERFETTO)
        auto perfetto_trace_path = std::filesystem::path(file_name_ + ".perfetto");
        if (std::filesystem::exists(perfetto_trace_path))
        {
            CaptureData::LoadResult res = LoadPerfettoFile(perfetto_trace_path.string().c_str());
            if (res != CaptureData::LoadResult::kSuccess)
            {
                return res;
            }
        }
#endif
        return LoadAdrenoRdFile(file_name);
    }
#if defined(DIVE_ENABLE_PERFETTO)
    else if (file_extension.compare(".perfetto") == 0)
    {
        return LoadPerfettoFile(file_name);
    }
#endif
    else
    {
        std::cerr << "Unknown capture type: " << file_name << std::endl;
        return LoadResult::kCorruptData;
    }
}

//--------------------------------------------------------------------------------------------------
CaptureData::LoadResult Pm4CaptureData::LoadCaptureFile(const char *file_name)
{
    // Open the file stream
    std::fstream capture_file(file_name, std::ios::in | std::ios::binary);
    if (!capture_file.is_open())
    {
        std::cerr << "Not able to open: " << file_name << std::endl;
        return LoadResult::kFileIoError;
    }

    auto result = LoadCaptureFile(capture_file);
    if (result != LoadResult::kSuccess)
    {
        std::cerr << "Error reading: " << file_name << " (" << result << ")" << std::endl;
    }
    else
    {
        m_cur_capture_file = std::string(file_name);
    }

    return result;
}

//--------------------------------------------------------------------------------------------------
CaptureData::LoadResult Pm4CaptureData::LoadAdrenoRdFile(const char *file_name)
{
    FileReader reader(file_name);
    if (reader.open() != 0)
    {
        std::cerr << "Not able to open: " << file_name << std::endl;
        return LoadResult::kFileIoError;
    }
    auto result = LoadAdrenoRdFile(reader);
    if (result != LoadResult::kSuccess)
    {
        std::cerr << "Error reading: " << file_name << " (" << result << ")" << std::endl;
    }
    else
    {
        m_cur_capture_file = std::string(file_name);
    }

    return result;
}

#if defined(DIVE_ENABLE_PERFETTO)
//--------------------------------------------------------------------------------------------------
CaptureData::LoadResult CaptureData::LoadPerfettoFile(const char *file_name)
{
    std::string name(file_name);
    TraceReader reader(name);
    if (reader.LoadTraceFile())
    {
        return LoadResult::kSuccess;
    }

    return LoadResult::kFileIoError;
}
#endif

//--------------------------------------------------------------------------------------------------
CaptureData::LoadResult Pm4CaptureData::LoadCaptureFile(std::istream &capture_file)
{
    // Read file header
    FileHeader file_header;
    if (!capture_file.read((char *)&file_header, sizeof(file_header)))
    {
        return LoadResult::kFileIoError;
    }

    if (file_header.m_file_id != kDiveFileId)
        return LoadResult::kCorruptData;
    if (file_header.m_file_version != kDiveFileVersion)
        return LoadResult::kVersionError;

    BlockInfo block_info;
    while (capture_file.read((char *)&block_info, sizeof(block_info)))
    {
        switch (block_info.m_block_type)
        {
        case BlockType::kCapture:
        {
            // The capture data always begins with some metadata info
            m_data_header = {};
            capture_file.read((char *)&m_data_header, sizeof(m_data_header));
            bool incompatible = ((m_data_header.m_major_version != kCaptureMajorVersion) ||
                                 (m_data_header.m_minor_version > kCaptureMinorVersion));
            // Cannot open version 0.1/0.2.x due to CaptureDataHeader change
            incompatible |= ((m_data_header.m_major_version == 0) &&
                             (m_data_header.m_minor_version == 1 ||
                              m_data_header.m_minor_version == 2));
            if (incompatible)
            {
                std::cerr << "Incompatible capture version " << m_data_header.m_major_version << "."
                          << m_data_header.m_minor_version << std::endl;
                std::cerr << "Supported version: " << kCaptureMajorVersion << "."
                          << kCaptureMinorVersion << std::endl;
                return LoadResult::kVersionError;
            }
            m_capture_type = m_data_header.m_capture_type;
            if (m_progress_tracker)
            {
                m_progress_tracker->sendMessage("Loading memory blocks...");
            }

            // If return false, either encountered a parsing error, or found an unknown block on a
            // capture file with version # <= version supported by the host tool
            if (!LoadCapture(capture_file, m_data_header))
                return LoadResult::kCorruptData;

            break;
        }
        default:
            DIVE_ASSERT(false);  // No other type of parent block supported right now
            return LoadResult::kCorruptData;
        }
    }
    return LoadResult::kSuccess;
}

//--------------------------------------------------------------------------------------------------
CaptureData::LoadResult Pm4CaptureData::LoadAdrenoRdFile(FileReader &capture_file)
{
    enum rd_sect_type
    {
        RD_NONE,
        RD_TEST,           /* ascii text */
        RD_CMD,            /* ascii text */
        RD_GPUADDR,        /* u32 gpuaddr, u32 size */
        RD_CONTEXT,        /* raw dump */
        RD_CMDSTREAM,      /* raw dump */
        RD_CMDSTREAM_ADDR, /* gpu addr of cmdstream */
        RD_PARAM,          /* u32 param_type, u32 param_val, u32 bitlen */
        RD_FLUSH,          /* empty, clear previous params */
        RD_PROGRAM,        /* shader program, raw dump */
        RD_VERT_SHADER,
        RD_FRAG_SHADER,
        RD_BUFFER_CONTENTS,
        RD_GPU_ID,
        RD_CHIP_ID,
    };

    struct BlockInfo
    {
        uint32_t m_block_type;

        // The number of bytes that follow this header.
        uint32_t m_data_size;
    };

    BlockInfo block_info;
    uint64_t  cur_gpu_addr = UINT64_MAX;
    uint32_t  cur_size = UINT32_MAX;
    bool      is_new_submit = false;
    bool      skip_commands = false;
    while (capture_file.read((char *)&block_info, sizeof(block_info)) > 0)
    {
        // Read and discard any trailing 0xffffffff padding from previous block
        while (block_info.m_block_type == 0xffffffff && block_info.m_data_size == 0xffffffff)
        {
            if (capture_file.read((char *)&block_info, sizeof(block_info)) <= 0)
                return LoadResult::kCorruptData;
        }

        switch (block_info.m_block_type)
        {
        case RD_GPUADDR:
            if (!LoadGpuAddressAndSize(capture_file,
                                       block_info.m_data_size,
                                       &cur_gpu_addr,
                                       &cur_size))
                return LoadResult::kFileIoError;
            is_new_submit = true;
            break;
        case RD_CMDSTREAM_ADDR:
            if (!LoadCmdStreamBlockAdreno(capture_file,
                                          block_info.m_data_size,
                                          is_new_submit,
                                          skip_commands))
                return LoadResult::kFileIoError;
            is_new_submit = false;
            break;
        case RD_BUFFER_CONTENTS:
            // The size read from RD_GPUADDR should match block size exactly
            if (block_info.m_data_size != cur_size)
                return LoadResult::kCorruptData;
            if (!LoadMemoryBlockAdreno(capture_file, cur_gpu_addr, cur_size))
                return LoadResult::kFileIoError;
            break;
        case RD_CMD:
        {
            // Skip parsing commands from system processes
            skip_commands = false;
            char *process_name = new char[block_info.m_data_size];
            if (!capture_file.read((char *)process_name, block_info.m_data_size))
                return LoadResult::kFileIoError;
            skip_commands |= (strcmp(process_name, "fdperf") == 0);
            skip_commands |= (strcmp(process_name, "chrome") == 0);
            skip_commands |= (strcmp(process_name, "surfaceflinger") == 0);
            skip_commands |= ((char *)process_name)[0] == 'X';
            delete[] process_name;
            break;
        }
        case RD_NONE:
        case RD_TEST:
        case RD_CONTEXT:
        case RD_CMDSTREAM:
        case RD_PARAM:
        case RD_FLUSH:
        case RD_PROGRAM:
        case RD_VERT_SHADER:
        case RD_FRAG_SHADER:
        {
            DiveVector<char> buf(block_info.m_data_size);
            capture_file.read(buf.data(), block_info.m_data_size);
            break;
        }
        case RD_GPU_ID:
        {
            DIVE_ASSERT(block_info.m_data_size == 4);
            uint32_t gpu_id = 0;
            capture_file.read(reinterpret_cast<char *>(&gpu_id), block_info.m_data_size);
            SetGPUID(gpu_id);
        }
        break;
        case RD_CHIP_ID:
        {
            // If it wasn't set already by a RD_GPU_ID
            // Or if it was an invalid gpu_id, which leads to a kGPUVariantNone
            if ((GetGPUID() == 0) || (GetGPUVariantType() == kGPUVariantNone))
            {
                DIVE_ASSERT(block_info.m_data_size == 8);
                fd_dev_id dev_id;
                capture_file.read(reinterpret_cast<char *>(&dev_id.chip_id),
                                  block_info.m_data_size);
                dev_id.gpu_id = 0;
                auto info = fd_dev_info(&dev_id);
                // It is possible that only RD_GPU_ID is valid, and RD_CHIP_ID contains invalid
                // values
                if (info != nullptr)
                {
                    SetGPUID(info->chip * 100);
                }
            }
        }
        break;
        }
    }
    m_memory.Finalize(true, true);
    return LoadResult::kSuccess;
}

//--------------------------------------------------------------------------------------------------
CaptureDataHeader::CaptureType Pm4CaptureData::GetCaptureType() const
{
    return m_capture_type;
}

//--------------------------------------------------------------------------------------------------
const MemoryManager &Pm4CaptureData::GetMemoryManager() const
{
    return m_memory;
}

//--------------------------------------------------------------------------------------------------
uint32_t Pm4CaptureData::GetNumSubmits() const
{
    return (uint32_t)m_submits.size();
}

//--------------------------------------------------------------------------------------------------
const SubmitInfo &Pm4CaptureData::GetSubmitInfo(uint32_t submit_index) const
{
    return m_submits[submit_index];
}

//--------------------------------------------------------------------------------------------------
const DiveVector<SubmitInfo> &Pm4CaptureData::GetSubmits() const
{
    return m_submits;
}

//--------------------------------------------------------------------------------------------------
uint32_t Pm4CaptureData::GetNumPresents() const
{
    return (uint32_t)m_presents.size();
}

//--------------------------------------------------------------------------------------------------
const PresentInfo &Pm4CaptureData::GetPresentInfo(uint32_t present_index) const
{
    return m_presents[present_index];
}

//--------------------------------------------------------------------------------------------------
uint32_t Pm4CaptureData::GetNumRings() const
{
    return (uint32_t)m_rings.size();
}

//--------------------------------------------------------------------------------------------------
const RingInfo &Pm4CaptureData::GetRingInfo(uint32_t ring_index) const
{
    return m_rings[ring_index];
}

//--------------------------------------------------------------------------------------------------
const WaveInfo &Pm4CaptureData::GetWaveInfo() const
{
    return m_waves;
}

//--------------------------------------------------------------------------------------------------
const RegisterInfo &Pm4CaptureData::GetRegisterInfo() const
{
    return m_registers;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadCapture(std::istream &capture_file, const CaptureDataHeader &data_header)
{
    BlockInfo block_info;
    while (capture_file.read((char *)&block_info, sizeof(block_info)))
    {
        switch (block_info.m_block_type)
        {
        case BlockType::kMemoryAlloc:
            if (!LoadMemoryAllocBlock(capture_file))
                return false;
            break;
        case BlockType::kSubmit:
            if (!LoadSubmitBlock(capture_file))
                return false;
            break;
        case BlockType::kMemoryRaw:
            if (!LoadMemoryBlock(capture_file))
                return false;
            break;
        case BlockType::kPresent:
            if (!LoadPresentBlock(capture_file))
                return false;
            break;
        case BlockType::kWaveState:
            if (!LoadWaveStateBlock(capture_file, data_header))
                return false;
            break;
        case BlockType::kText:
            if (!LoadTextBlock(capture_file))
                return false;
            break;
        case BlockType::kRegisters:
            if (!LoadRegisterBlock(capture_file))
                return false;
            break;
        case BlockType::kVulkanMetadata:
            if (!LoadVulkanMetaDataBlock(capture_file))
                return false;
            break;
        default:
            // It is an error if it is NOT a future version of the capture format AND there are
            // unsupported blocks. The idea is that unsupported blocks are possible due to forward
            // compatibility ONLY.
            bool later_capture = (data_header.m_major_version > kCaptureMajorVersion);
            later_capture |= ((data_header.m_major_version == kCaptureMajorVersion) &&
                              (data_header.m_minor_version > kCaptureMinorVersion));
            later_capture |= ((data_header.m_major_version == kCaptureMajorVersion) &&
                              (data_header.m_minor_version == kCaptureMinorVersion) &&
                              (data_header.m_revision > kCaptureRevision));
            if (!later_capture)
            {
                DIVE_ERROR_MSG("Unsupported block type 0x%x found!\n", block_info.m_block_type);
                DIVE_ASSERT(false);  // Unsupported block type found!
                return false;
            }
            capture_file.seekg(block_info.m_data_size, std::ios::cur);
        }
    }
    Finalize(data_header);
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadMemoryAllocBlock(std::istream &capture_file)
{
    MemoryAllocationsDataHeader memory_allocations_header;
    if (!capture_file.read((char *)&memory_allocations_header, sizeof(memory_allocations_header)))
        return false;
    if (memory_allocations_header.m_num_allocations > kMaxNumMemAlloc)
        return false;

    // Load the allocations
    DiveVector<MemoryAllocationData> allocations;
    allocations.resize(memory_allocations_header.m_num_allocations);
    uint32_t size = memory_allocations_header.m_num_allocations * sizeof(MemoryAllocationData);
    if (!capture_file.read((char *)&allocations[0], size))
        return false;

    // Add it to memory manager
    uint32_t submit_index = (uint32_t)(m_submits.size());
    m_memory.AddMemoryAllocations(submit_index,
                                  memory_allocations_header.m_type,
                                  std::move(allocations));

    return true;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadSubmitBlock(std::istream &capture_file)
{
    SubmitDataHeader submit_data_header;
    if (!capture_file.read((char *)&submit_data_header, sizeof(submit_data_header)))
        return false;

    // Load the ib info
    DiveVector<IndirectBufferInfo> ibs;
    for (uint32_t ib = 0; ib < submit_data_header.m_num_ibs; ++ib)
    {
        IndirectBufferData ib_data;
        if (!capture_file.read((char *)&ib_data, sizeof(ib_data)))
            return false;

        IndirectBufferInfo ib_info;
        ib_info.m_va_addr = ib_data.m_va_addr;
        ib_info.m_size_in_dwords = ib_data.m_size_in_dwords;
        ib_info.m_skip = false;
        ibs.push_back(ib_info);
    }

    SubmitInfo submit_info((EngineType)submit_data_header.m_engine_type,
                           (QueueType)submit_data_header.m_queue_type,
                           submit_data_header.m_engine_index,
                           submit_data_header.m_is_dummy_submit,
                           std::move(ibs));
    m_submits.push_back(std::move(submit_info));
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadMemoryBlock(std::istream &capture_file)
{
    MemoryRawDataHeader memory_raw_data_header;
    if (!capture_file.read((char *)&memory_raw_data_header, sizeof(memory_raw_data_header)))
        return false;

    if (memory_raw_data_header.m_size_in_bytes > kMaxMemAllocSize)
        return false;
    MemoryData raw_memory;
    raw_memory.m_data_size = memory_raw_data_header.m_size_in_bytes;
    raw_memory.m_data_ptr = new uint8_t[raw_memory.m_data_size];
    if (!capture_file.read((char *)raw_memory.m_data_ptr, memory_raw_data_header.m_size_in_bytes))
    {
        delete[] raw_memory.m_data_ptr;
        return false;
    }

    uint32_t submit_index = (uint32_t)(m_submits.size() - 1);

    m_memory.AddMemoryBlock(submit_index, memory_raw_data_header.m_va_addr, std::move(raw_memory));
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadPresentBlock(std::istream &capture_file)
{
    PresentData present_data;
    if (!capture_file.read((char *)&present_data, sizeof(present_data)))
        return false;

    uint32_t submit_index = (uint32_t)(m_submits.size() - 1);
    if (present_data.m_valid_data)
    {
        PresentInfo present_info((EngineType)present_data.m_engine_type,
                                 (QueueType)present_data.m_queue_type,
                                 submit_index,
                                 present_data.m_full_screen,
                                 present_data.m_addr,
                                 present_data.m_size,
                                 present_data.m_vk_format,
                                 present_data.m_vk_color_space);
        m_presents.push_back(present_info);
    }
    else
    {
        m_presents.push_back(PresentInfo());
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadTextBlock(std::istream &capture_file)
{
    TextBlockHeader text_header;

    if (!capture_file.read((char *)&text_header, sizeof(text_header)))
        return false;

    std::string name;
    if (text_header.m_name_len > kMaxStrLen || text_header.m_size_in_bytes > kMaxMemAllocSize)
        return false;
    name.reserve(text_header.m_name_len);
    if (!std::getline(capture_file, name, '\0'))
        return false;

    DiveVector<char> data;
    data.resize(text_header.m_size_in_bytes);

    if (!capture_file.read((char *)data.data(), data.size()))
        return false;

    m_text.push_back(TextInfo(std::move(name), text_header.m_size_in_bytes, std::move(data)));
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadWaveStateBlock(std::istream            &capture_file,
                                     const CaptureDataHeader &data_header)
{
    // Only one wave block per capture is expected.
    assert(m_waves.GetWaves().size() == 0);

    // Read chunk header
    WaveStateBlockHeader wave_header;

    if (!capture_file.read((char *)&wave_header, sizeof(wave_header)))
        return false;

    DiveVector<WaveStateInfo> waves;
    if (wave_header.m_num_waves > kMaxNumWavesPerBlock)
        return false;
    for (uint32_t i = 0; i < wave_header.m_num_waves; ++i)
    {
        Dive::WaveState state;
        if (!capture_file.read((char *)&state, sizeof(state)))
            return false;

        assert(state.num_threads == 64);
        assert((state.num_vgprs % state.num_threads) == 0);
        if (state.num_sgprs > kMaxNumSGPRPerWave || state.num_vgprs > kMaxNumVGPRPerWave)
        {
            return false;
        }
        DiveVector<uint32_t> sgprs(state.num_sgprs);
        if (sgprs.size() > 0)
        {
            if (!capture_file.read((char *)sgprs.data(), state.num_sgprs * sizeof(uint32_t)))
                return false;
        }

        DiveVector<uint32_t> vgprs(state.num_vgprs);
        if (vgprs.size() > 0)
        {
            if (!capture_file.read((char *)vgprs.data(), state.num_vgprs * sizeof(uint32_t)))
                return false;
        }

        // If this was captured while a trap handler was active,
        // we should have 16 tmp registers.
        bool has_temps = state.WAVE_STATUS & (1 << 6);

        // Older versions didn't have temp registers captured.
        if (data_header.m_major_version == 0 && data_header.m_minor_version <= 3 &&
            data_header.m_revision < 11)
        {
            has_temps = false;
        }

        DiveVector<uint32_t> ttmps;
        if (has_temps)
        {
            ttmps.resize(16);
            if (!capture_file.read((char *)ttmps.data(), 16 * sizeof(uint32_t)))
                return false;
        }

        waves.emplace_back(state, std::move(sgprs), std::move(vgprs), std::move(ttmps));
    }

    m_waves = WaveInfo(std::move(waves));
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadRegisterBlock(std::istream &capture_file)
{
    // Only one wave block per capture is expected.
    assert(m_registers.GetRegisters().size() == 0);

    // Read chunk header
    RegisterBlockHeader reg_header;

    if (!capture_file.read((char *)&reg_header, sizeof(reg_header)))
        return false;

    std::map<std::string, uint32_t> regs;
    for (uint32_t i = 0; i < reg_header.m_num_registers; ++i)
    {
        std::string name;
        if (!std::getline(capture_file, name, '\0'))
            return false;

        uint32_t value;
        if (!capture_file.read((char *)&value, sizeof(uint32_t)))
            return false;

        regs.emplace(name, value);
    }

    m_registers = RegisterInfo(std::move(regs));
    return true;
}

bool Pm4CaptureData::LoadVulkanMetaDataBlock(std::istream &capture_file)
{
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadGpuAddressAndSize(FileReader &capture_file,
                                        uint32_t    block_size,
                                        uint64_t   *gpu_addr,
                                        uint32_t   *size)
{
    assert(block_size >= 2 * sizeof(uint32_t));

    uint32_t dword;
    if (!capture_file.read((char *)&dword, sizeof(uint32_t)))
        return false;
    *gpu_addr = dword;
    if (!capture_file.read((char *)&dword, sizeof(uint32_t)))
        return false;
    *size = dword;

    // It's possible that only the lower 32-bits are written to the file?
    if (block_size > 2 * sizeof(uint32_t))
    {
        if (!capture_file.read((char *)&dword, sizeof(uint32_t)))
            return false;
        *gpu_addr |= ((uint64_t)(dword)) << 32;
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadMemoryBlockAdreno(FileReader &capture_file, uint64_t gpu_addr, uint32_t size)
{
    MemoryData raw_memory;
    raw_memory.m_data_size = size;
    raw_memory.m_data_ptr = new uint8_t[raw_memory.m_data_size];
    if (!capture_file.read((char *)raw_memory.m_data_ptr, size))
    {
        delete[] raw_memory.m_data_ptr;
        return false;
    }

    // Unlike with Dive, all memory blocks for a submit come *before* the submit
    uint32_t submit_index = (uint32_t)(m_submits.size());
    m_memory.AddMemoryBlock(submit_index, gpu_addr, std::move(raw_memory));
    return true;
}

//--------------------------------------------------------------------------------------------------
bool Pm4CaptureData::LoadCmdStreamBlockAdreno(FileReader &capture_file,
                                           uint32_t    block_size,
                                           bool        create_new_submit,
                                           bool        skip_commands)
{
    uint64_t gpu_addr;
    uint32_t size_in_dwords;
    if (!LoadGpuAddressAndSize(capture_file, block_size, &gpu_addr, &size_in_dwords))
        return false;

    IndirectBufferInfo ib_info;
    ib_info.m_va_addr = gpu_addr;
    ib_info.m_size_in_dwords = size_in_dwords;
    ib_info.m_skip = skip_commands;
    if (create_new_submit)
    {
        DiveVector<IndirectBufferInfo> ibs;
        ibs.push_back(ib_info);

        SubmitInfo submit_info(EngineType::kUniversal,
                               QueueType::kUniversal,
                               0,
                               false,
                               std::move(ibs));
        m_submits.push_back(std::move(submit_info));
    }
    else
    {
        // Append it to the previous submit
        DIVE_ASSERT(!m_submits.empty());
        m_submits.back().AppendIb(ib_info);
    }
    return true;
}

//--------------------------------------------------------------------------------------------------
void Pm4CaptureData::Finalize(const CaptureDataHeader &data_header)
{
    // 0.3.2 implemented memory tracking for IBs - ie. no more duplicate capturing
    // Can probably remove this extra check later, since there are very few captures
    // before 0.3.2
    bool duplicate_ib_capture = (data_header.m_major_version == 0) &&
                                ((data_header.m_minor_version < 3) ||
                                 ((data_header.m_minor_version == 3) &&
                                  (data_header.m_revision < 2)));

    // If capture process resets memory tracker in between every submit, then each submit is
    // "self-sufficient" in the sense that all memory referenced by that submit should be
    // captured, even if the same memory content was captured for a previous submit already.
    // This is one way to ensure all referenced memory is captured, since there is no
    // way to check that the memory content of a memory range has changed in between submits
    // (ie: there is no checksum algorithm employed in the capture process). However, this
    // bloats capture file size and affects any profiling code running at the same time, so
    // the reset is only done for certain capture modes.
    bool same_submit_copy_only = data_header.m_reset_memory_tracker;
    m_memory.Finalize(same_submit_copy_only, duplicate_ib_capture);
}

//--------------------------------------------------------------------------------------------------
std::string Pm4CaptureData::GetFileFormatVersion() const
{
    std::stringstream os;
    os << m_data_header.m_major_version << "." << m_data_header.m_minor_version << "."
       << m_data_header.m_revision;
    return os.str();
}

}  // namespace Dive
