/*
** Copyright (c) 2023 Valve Corporation
** Copyright (c) 2022-2023 LunarG, Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
** DEALINGS IN THE SOFTWARE.
*/

#ifndef GFXRECON_DECODE_METADATA_DIVE_CONSUMER_H
#define GFXRECON_DECODE_METADATA_DIVE_CONSUMER_H

#include "util/defines.h"
#include "util/file_path.h"
#include <cstdint>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/// Template shim for turning metadata (metacommands) into JSON using a
/// JsonWriter pointed to by a protected pointer called writer_ in a base class.
/// This can be shimmed into the inheritance hierarchy for any JSON consumer as
/// is done by gfxrecon-convert's main.cpp for both Vulkan and DX12 consumers to
/// provide metacommand support.
/// @note Any API-specific metablocks/metadata/metacommands are best handled directly by the JSON consumer of that API.
/// @note An alternative implementation would make MetadataConsumerBase a virtual base class of the base
/// Vulkan and DX12 consumers, and also a virtual base of a non-template version of MetadataJsonConsumer,
/// and VulkanJSONConsumer and DX12JsonConsumer would both use multiple inheritance to mix-in this posited non-template
/// MetadataJsonConsumer. The advantage would be code space saved due to avoiding two template instantiations with
/// identical code. The downside would be the slower virtual function dispatch due to diamond inheritance from the
/// use of virtual base classes (See Stroustrup, Design and Evolution of C++ for overheads of virtual base classes).
template <class Base>
class MetadataDiveConsumer : public Base
{
    inline void WriteBlockEnd(std::string name, uint32_t cmd_buffer_index = 0) { this->writer_->WriteBlockEnd(name); }

  public:
    virtual void
    ProcessFillMemoryCommand(uint64_t memory_id, uint64_t offset, uint64_t size, const uint8_t* data) override
    {
        WriteBlockEnd("FillMemoryCommand");
    }

    virtual void Process_ExeFileInfo(gfxrecon::util::filepath::FileInfo& info) override
    {
        WriteBlockEnd("ExeFileInfo");
    }

    virtual void ProcessResizeWindowCommand(format::HandleId surface_id, uint32_t width, uint32_t height) override
    {
        using namespace util;
        WriteBlockEnd("ResizeWindowCommand");
    }

    virtual void ProcessResizeWindowCommand2(format::HandleId surface_id,
                                             uint32_t         width,
                                             uint32_t         height,
                                             uint32_t         pre_transform) override
    {
        WriteBlockEnd("ResizeWindowCommand2");
    }

    virtual void
    ProcessCreateHardwareBufferCommand(format::HandleId                                    memory_id,
                                       uint64_t                                            buffer_id,
                                       uint32_t                                            format,
                                       uint32_t                                            width,
                                       uint32_t                                            height,
                                       uint32_t                                            stride,
                                       uint64_t                                            usage,
                                       uint32_t                                            layers,
                                       const std::vector<format::HardwareBufferPlaneInfo>& plane_info) override
    {
        WriteBlockEnd("CreateHardwareBufferCommand");
    }

    virtual void ProcessDestroyHardwareBufferCommand(const uint64_t buffer_id) override
    {
        WriteBlockEnd("DestroyHardwareBufferCommand");
    }

    virtual void ProcessSetDevicePropertiesCommand(format::HandleId   physical_device_id,
                                                   uint32_t           api_version,
                                                   uint32_t           driver_version,
                                                   uint32_t           vendor_id,
                                                   uint32_t           device_id,
                                                   uint32_t           device_type,
                                                   const uint8_t      pipeline_cache_uuid[format::kUuidSize],
                                                   const std::string& device_name) override
    {
        WriteBlockEnd("SetDevicePropertiesCommand");
    }

    virtual void
    ProcessSetOpaqueAddressCommand(format::HandleId device_id, format::HandleId object_id, uint64_t address) override
    {
        WriteBlockEnd("SetOpaqueAddressCommand");
    }

    virtual void ProcessSetRayTracingShaderGroupHandlesCommand(format::HandleId device_id,
                                                               format::HandleId pipeline_id,
                                                               size_t           data_size,
                                                               const uint8_t*   data) override
    {
        WriteBlockEnd("SetRayTracingShaderGroupHandlesCommand");
    }

    virtual void
    ProcessSetSwapchainImageStateCommand(format::HandleId                                    device_id,
                                         format::HandleId                                    swapchain_id,
                                         uint32_t                                            last_presented_image,
                                         const std::vector<format::SwapchainImageStateInfo>& image_state) override
    {
        WriteBlockEnd("SetSwapchainImageStateCommand");
    }

    virtual void ProcessBeginResourceInitCommand(format::HandleId device_id,
                                                 uint64_t         max_resource_size,
                                                 uint64_t         max_copy_size) override
    {
        WriteBlockEnd("BeginResourceInitCommand");
    }

    virtual void ProcessEndResourceInitCommand(format::HandleId device_id) override
    {
        WriteBlockEnd("EndResourceInitCommand");
    }

    virtual void ProcessInitBufferCommand(format::HandleId device_id,
                                          format::HandleId buffer_id,
                                          uint64_t         data_size,
                                          const uint8_t*   data) override
    {
        WriteBlockEnd("InitBufferCommand");
    }

    virtual void ProcessInitImageCommand(format::HandleId             device_id,
                                         format::HandleId             image_id,
                                         uint64_t                     data_size,
                                         uint32_t                     aspect,
                                         uint32_t                     layout,
                                         const std::vector<uint64_t>& level_sizes,
                                         const uint8_t*               data) override
    {
        WriteBlockEnd("InitImageCommand");
    }

    virtual void ProcessSetEnvironmentVariablesCommand(format::SetEnvironmentVariablesCommand& header,
                                                       const char*                             env_string) override
    {
        WriteBlockEnd("SetEnvironmentVariablesCommand");
    }

    virtual void ProcessExecuteBlocksFromFile(uint32_t n_blocks, int64_t offset, const std::string& filename) override
    {
        WriteBlockEnd("ExecuteBlocksFromFile");
    }

    /// @}
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_METADATA_DIVE_CONSUMER_H
