/*
** Copyright (c) 2024 LunarG, Inc.
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

#include "decode/vulkan_object_info.h"
#include "decode/vulkan_replay_dump_resources_compute_ray_tracing.h"
#include "decode/vulkan_replay_dump_resources_draw_calls.h"
#include "decode/vulkan_replay_options.h"
#include "decode/vulkan_replay_dump_resources_delegate.h"
#include "format/format.h"
#include "generated/generated_vulkan_enum_to_string.h"
#include "generated/generated_vulkan_struct_decoders.h"
#include "vulkan_replay_dump_resources.h"
#include "decode/vulkan_pnext_node.h"
#include "graphics/vulkan_struct_get_pnext.h"
#include "util/logging.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <vulkan/vulkan_core.h>
#if !defined(WIN32)
#include <dirent.h>
#endif

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

VulkanReplayDumpResourcesBase::VulkanReplayDumpResourcesBase(const VulkanReplayOptions& options,
                                                             CommonObjectInfoTable*     object_info_table) :
    QueueSubmit_indices_(options.QueueSubmit_Indices),
    recording_(false), dump_resources_before_(options.dump_resources_before), object_info_table_(object_info_table),
    output_json_per_command(options.dump_resources_json_per_command), default_delegate_(nullptr),
    user_delegate_(nullptr), active_delegate_(nullptr)
{
    capture_filename = std::filesystem::path(options.capture_filename).stem().string();

    if (!options.Draw_Indices.size() && !options.Dispatch_Indices.size() && !options.TraceRays_Indices.size())
    {
        return;
    }

    if (user_delegate_ != nullptr)
    {
        active_delegate_ = user_delegate_;
    }
    else
    {
        // Use a default delegate if none was provided.
        default_delegate_ =
            std::make_unique<DefaultVulkanDumpResourcesDelegate>(options, *object_info_table, capture_filename);
        active_delegate_ = default_delegate_.get();
    }

    if (!options.dump_resources_json_per_command)
    {
        active_delegate_->Open();
    }

    for (size_t i = 0; i < options.BeginCommandBuffer_Indices.size(); ++i)
    {
        const uint64_t bcb_index    = options.BeginCommandBuffer_Indices[i];
        const bool     has_draw     = i < options.Draw_Indices.size() && options.Draw_Indices[i].size();
        const bool     has_dispatch = (i < options.Dispatch_Indices.size() && options.Dispatch_Indices[i].size()) ||
                                  (i < options.TraceRays_Indices.size() && options.TraceRays_Indices[i].size());
        const bool has_secondaries =
            ((i < options.ExecuteCommands_Indices.size()) && !options.ExecuteCommands_Indices[i].empty());

        if (has_draw)
        {
            draw_call_contexts.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(bcb_index),
                                       std::forward_as_tuple(&options.Draw_Indices[i],
                                                             &options.RenderPass_Indices[i],
                                                             *object_info_table,
                                                             options,
                                                             *active_delegate_));
        }

        if (has_dispatch)
        {
            dispatch_ray_contexts.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(bcb_index),
                std::forward_as_tuple((options.Dispatch_Indices.size() && options.Dispatch_Indices[i].size())
                                          ? &options.Dispatch_Indices[i]
                                          : nullptr,
                                      (options.TraceRays_Indices.size() && options.TraceRays_Indices[i].size())
                                          ? &options.TraceRays_Indices[i]
                                          : nullptr,
                                      *object_info_table_,
                                      options,
                                      *active_delegate_));
        }
    }

    // Once all contexts are created do a second pass and assign the secondaries to the primaries the are executed from
    for (size_t i = 0; i < options.BeginCommandBuffer_Indices.size() && i < options.ExecuteCommands_Indices.size(); ++i)
    {
        if (options.ExecuteCommands_Indices[i].empty())
        {
            continue;
        }

        const uint64_t bcb_index = options.BeginCommandBuffer_Indices[i];

        DrawCallsDumpingContext* primary_dc_context = FindDrawCallCommandBufferContext(bcb_index);
        for (auto& [execute_commands_index, secondary_bcbs] : options.ExecuteCommands_Indices[i])
        {
            for (auto& secondary_bcb : secondary_bcbs)
            {
                DrawCallsDumpingContext* dc_secondary_context = FindDrawCallCommandBufferContext(secondary_bcb);
                if (dc_secondary_context != nullptr)
                {
                    if (primary_dc_context == nullptr)
                    {
                        auto new_primary =
                            draw_call_contexts.emplace(std::piecewise_construct,
                                                       std::forward_as_tuple(bcb_index),
                                                       std::forward_as_tuple(nullptr,
                                                                             &options.RenderPass_Indices[i],
                                                                             *object_info_table,
                                                                             options,
                                                                             *active_delegate_));

                        primary_dc_context = FindDrawCallCommandBufferContext(bcb_index);
                    }

                    primary_dc_context->AssignSecondary(execute_commands_index, dc_secondary_context);
                }
            }
        }

        DispatchTraceRaysDumpingContext* primary_disp_context = FindDispatchRaysCommandBufferContext(bcb_index);
        for (auto& execute_commands : options.ExecuteCommands_Indices[i])
        {
            const uint64_t execute_commands_index = execute_commands.first;
            for (auto& secondary : execute_commands.second)
            {
                DispatchTraceRaysDumpingContext* disp_secondary_context =
                    FindDispatchRaysCommandBufferContext(secondary);
                if (disp_secondary_context != nullptr)
                {
                    if (primary_disp_context == nullptr)
                    {
                        dispatch_ray_contexts.emplace(
                            std::piecewise_construct,
                            std::forward_as_tuple(bcb_index),
                            std::forward_as_tuple(nullptr, nullptr, *object_info_table_, options, *active_delegate_));

                        primary_disp_context = FindDispatchRaysCommandBufferContext(bcb_index);
                    }
                    primary_disp_context->AssignSecondary(execute_commands_index, disp_secondary_context);
                }
            }
        }
    }

    // Number of command buffers for DrawCallsDumpingContext need to be recalculated when dumping resources from
    // secondaries. This is done in a separate pass since we need to be sure that all assignments have been completed.
    if (!options.ExecuteCommands_Indices.empty())
    {
        for (size_t i = 0; i < options.BeginCommandBuffer_Indices.size(); ++i)
        {
            if (options.ExecuteCommands_Indices[i].empty())
            {
                continue;
            }

            const uint64_t           bcb_index          = options.BeginCommandBuffer_Indices[i];
            DrawCallsDumpingContext* primary_dc_context = FindDrawCallCommandBufferContext(bcb_index);
            if (primary_dc_context != nullptr)
            {
                primary_dc_context->RecaclulateCommandBuffers();
            }
        }
    }
}

VulkanReplayDumpResourcesBase::~VulkanReplayDumpResourcesBase()
{
    Release();
}

void VulkanReplayDumpResourcesBase::Release()
{
    // active_delegate_ could be nullptr because constructor could return before creating delegate.
    if (active_delegate_)
    {
        active_delegate_->Close();
        active_delegate_  = nullptr;
        default_delegate_ = nullptr;
    }
    draw_call_contexts.clear();
    dispatch_ray_contexts.clear();
    cmd_buf_begin_map_.clear();
    QueueSubmit_indices_.clear();

    recording_ = false;
}

DrawCallsDumpingContext*
VulkanReplayDumpResourcesBase::FindDrawCallCommandBufferContext(VkCommandBuffer original_command_buffer)
{
    auto begin_entry = cmd_buf_begin_map_.find(original_command_buffer);
    if (begin_entry == cmd_buf_begin_map_.end())
    {
        return nullptr;
    }

    auto context_entry = draw_call_contexts.find(begin_entry->second);
    if (context_entry == draw_call_contexts.end())
    {
        return nullptr;
    }

    DrawCallsDumpingContext* context = &context_entry->second;
    return context;
}

const DrawCallsDumpingContext*
VulkanReplayDumpResourcesBase::FindDrawCallCommandBufferContext(VkCommandBuffer original_command_buffer) const
{
    auto begin_entry = cmd_buf_begin_map_.find(original_command_buffer);
    if (begin_entry == cmd_buf_begin_map_.end())
    {
        return nullptr;
    }

    const auto context_entry = draw_call_contexts.find(begin_entry->second);
    if (context_entry == draw_call_contexts.end())
    {
        return nullptr;
    }

    const DrawCallsDumpingContext* context = &context_entry->second;
    return context;
}

DrawCallsDumpingContext* VulkanReplayDumpResourcesBase::FindDrawCallCommandBufferContext(uint64_t bcb_id)
{
    auto context_entry = draw_call_contexts.find(bcb_id);
    if (context_entry == draw_call_contexts.end())
    {
        return nullptr;
    }

    DrawCallsDumpingContext* context = &context_entry->second;
    return context;
}

const DrawCallsDumpingContext* VulkanReplayDumpResourcesBase::FindDrawCallCommandBufferContext(uint64_t bcb_id) const
{
    const auto context_entry = draw_call_contexts.find(bcb_id);
    if (context_entry == draw_call_contexts.end())
    {
        return nullptr;
    }

    const DrawCallsDumpingContext* context = &context_entry->second;
    return context;
}

DispatchTraceRaysDumpingContext* VulkanReplayDumpResourcesBase::FindDispatchRaysCommandBufferContext(uint64_t bcb_id)
{
    auto context_entry = dispatch_ray_contexts.find(bcb_id);
    if (context_entry == dispatch_ray_contexts.end())
    {
        return nullptr;
    }

    DispatchTraceRaysDumpingContext* context = &context_entry->second;
    return context;
}

const DispatchTraceRaysDumpingContext*
VulkanReplayDumpResourcesBase::FindDispatchRaysCommandBufferContext(uint64_t bcb_id) const
{
    const auto context_entry = dispatch_ray_contexts.find(bcb_id);
    if (context_entry == dispatch_ray_contexts.end())
    {
        return nullptr;
    }

    const DispatchTraceRaysDumpingContext* context = &context_entry->second;
    return context;
}

DispatchTraceRaysDumpingContext*
VulkanReplayDumpResourcesBase::FindDispatchRaysCommandBufferContext(VkCommandBuffer original_command_buffer)
{
    auto bcb_entry = cmd_buf_begin_map_.find(original_command_buffer);
    if (bcb_entry == cmd_buf_begin_map_.end())
    {
        return nullptr;
    }

    auto dr_context_entry = dispatch_ray_contexts.find(bcb_entry->second);
    if (dr_context_entry == dispatch_ray_contexts.end())
    {
        return nullptr;
    }

    DispatchTraceRaysDumpingContext* context = &dr_context_entry->second;
    return context;
}

const DispatchTraceRaysDumpingContext*
VulkanReplayDumpResourcesBase::FindDispatchRaysCommandBufferContext(VkCommandBuffer original_command_buffer) const
{
    const auto bcb_entry = cmd_buf_begin_map_.find(original_command_buffer);
    if (bcb_entry == cmd_buf_begin_map_.end())
    {
        return nullptr;
    }

    const auto dr_context_entry = dispatch_ray_contexts.find(bcb_entry->second);
    if (dr_context_entry == dispatch_ray_contexts.end())
    {
        return nullptr;
    }

    const DispatchTraceRaysDumpingContext* context = &dr_context_entry->second;
    return context;
}

VkResult VulkanReplayDumpResourcesBase::CloneCommandBuffer(uint64_t                 bcb_index,
                                                           VulkanCommandBufferInfo* original_command_buffer_info,
                                                           const graphics::VulkanDeviceTable*   device_table,
                                                           const graphics::VulkanInstanceTable* inst_table,
                                                           const VkCommandBufferBeginInfo*      begin_info)
{
    assert(device_table);
    assert(inst_table);

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(bcb_index);
    if (dc_context != nullptr)
    {
        VkResult res =
            dc_context->CloneCommandBuffer(original_command_buffer_info, device_table, inst_table, begin_info);
        if (res != VK_SUCCESS)
        {
            GFXRECON_LOG_ERROR("Cloning command buffer for dumping draw calls failed (%s).",
                               util::ToString<VkResult>(res).c_str())
            return res;
        }

        cmd_buf_begin_map_[original_command_buffer_info->handle] = bcb_index;
        recording_                                               = true;
    }

    DispatchTraceRaysDumpingContext* dr_context = FindDispatchRaysCommandBufferContext(bcb_index);
    if (dr_context != nullptr)
    {
        VkResult res =
            dr_context->CloneCommandBuffer(original_command_buffer_info, device_table, inst_table, begin_info);
        if (res != VK_SUCCESS)
        {
            GFXRECON_LOG_ERROR("Cloning command buffer for dumping compute/ray tracing failed (%s).",
                               util::ToString<VkResult>(res).c_str())
            return res;
        }

        cmd_buf_begin_map_[original_command_buffer_info->handle] = bcb_index;
        recording_                                               = true;
    }

    return VK_SUCCESS;
}

void VulkanReplayDumpResourcesBase::OverrideCmdDraw(const ApiCallInfo& call_info,
                                                    PFN_vkCmdDraw      func,
                                                    VkCommandBuffer    original_command_buffer,
                                                    uint32_t           vertex_count,
                                                    uint32_t           instance_count,
                                                    uint32_t           first_vertex,
                                                    uint32_t           first_instance)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t           dc_index   = call_info.index;
    const bool               must_dump  = MustDumpDrawCall(original_command_buffer, dc_index);
    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);

    // Finalize draw call command buffer before the actual draw call in order
    // to handle dumping render targets before the draw call
    if (dump_resources_before_ && must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }

    if (must_dump)
    {
        dc_context->InsertNewDrawParameters(dc_index, vertex_count, instance_count, first_vertex, first_instance);
    }

    CommandBufferIterator first, last;
    GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    for (CommandBufferIterator it = first; it < last; ++it)
    {
        func(*it, vertex_count, instance_count, first_vertex, first_instance);
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer, vertex_count, instance_count, first_vertex, first_instance);
    }

    if (must_dump)
    {
        assert(dc_context != nullptr);

        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdDrawIndexed(const ApiCallInfo&   call_info,
                                                           PFN_vkCmdDrawIndexed func,
                                                           VkCommandBuffer      original_command_buffer,
                                                           uint32_t             index_count,
                                                           uint32_t             instance_count,
                                                           uint32_t             first_index,
                                                           int32_t              vertexOffset,
                                                           uint32_t             first_instance)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t           dc_index   = call_info.index;
    const bool               must_dump  = MustDumpDrawCall(original_command_buffer, dc_index);
    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);

    // Finalize draw call command buffer before the actual draw call in order
    // to handle dumping render targets before the draw call
    if (dump_resources_before_ && must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }

    // Copy vertex attribute info
    if (dc_context != nullptr && must_dump)
    {
        dc_context->InsertNewDrawIndexedParameters(
            dc_index, index_count, instance_count, first_index, vertexOffset, first_instance);
    }

    CommandBufferIterator first, last;
    GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    for (CommandBufferIterator it = first; it < last; ++it)
    {
        func(*it, index_count, instance_count, first_index, vertexOffset, first_instance);
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer, index_count, instance_count, first_index, vertexOffset, first_instance);
    }

    if (must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdDrawIndirect(const ApiCallInfo&      call_info,
                                                            PFN_vkCmdDrawIndirect   func,
                                                            VkCommandBuffer         original_command_buffer,
                                                            const VulkanBufferInfo* buffer_info,
                                                            VkDeviceSize            offset,
                                                            uint32_t                draw_count,
                                                            uint32_t                stride)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t           dc_index   = call_info.index;
    const bool               must_dump  = MustDumpDrawCall(original_command_buffer, dc_index);
    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);

    // Finalize draw call command buffer before the actual draw call in order
    // to handle dumping render targets before the draw call
    if (dump_resources_before_ && must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }

    // Copy vertex attribute info
    if (dc_context != nullptr && must_dump)
    {
        dc_context->InsertNewDrawIndirectParameters(dc_index, buffer_info, offset, draw_count, stride);
    }

    CommandBufferIterator first, last;
    GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    for (CommandBufferIterator it = first; it < last; ++it)
    {
        func(*it, buffer_info->handle, offset, draw_count, stride);
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer, buffer_info->handle, offset, draw_count, stride);
    }

    if (must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdDrawIndexedIndirect(const ApiCallInfo&           call_info,
                                                                   PFN_vkCmdDrawIndexedIndirect func,
                                                                   VkCommandBuffer              original_command_buffer,
                                                                   const VulkanBufferInfo*      buffer_info,
                                                                   VkDeviceSize                 offset,
                                                                   uint32_t                     draw_count,
                                                                   uint32_t                     stride)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t           dc_index   = call_info.index;
    const bool               must_dump  = MustDumpDrawCall(original_command_buffer, dc_index);
    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);

    // Finalize draw call command buffer before the actual draw call in order
    // to handle dumping render targets before the draw call
    if (dump_resources_before_ && must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }

    if (dc_context != nullptr && must_dump)
    {
        dc_context->InsertNewDrawIndexedIndirectParameters(dc_index, buffer_info, offset, draw_count, stride);
    }

    CommandBufferIterator first, last;
    GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    for (CommandBufferIterator it = first; it < last; ++it)
    {
        func(*it, buffer_info->handle, offset, draw_count, stride);
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer, buffer_info->handle, offset, draw_count, stride);
    }

    if (must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::HandleCmdDrawIndirectCount(const ApiCallInfo&         call_info,
                                                               PFN_vkCmdDrawIndirectCount func,
                                                               VkCommandBuffer            original_command_buffer,
                                                               const VulkanBufferInfo*    buffer_info,
                                                               VkDeviceSize               offset,
                                                               const VulkanBufferInfo*    count_buffer_info,
                                                               VkDeviceSize               count_buffer_offset,
                                                               uint32_t                   max_draw_count,
                                                               uint32_t                   stride,
                                                               DrawCallsDumpingContext::DrawCallType drawcall_type)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t           dc_index   = call_info.index;
    const bool               must_dump  = MustDumpDrawCall(original_command_buffer, dc_index);
    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);

    // Finalize draw call command buffer before the actual draw call in order
    // to handle dumping render targets before the draw call
    if (dump_resources_before_ && must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }

    if (dc_context != nullptr && must_dump)
    {
        dc_context->InsertNewIndirectCountParameters(dc_index,
                                                     buffer_info,
                                                     offset,
                                                     count_buffer_info,
                                                     count_buffer_offset,
                                                     max_draw_count,
                                                     stride,
                                                     drawcall_type);
    }

    CommandBufferIterator first, last;
    GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    for (CommandBufferIterator it = first; it < last; ++it)
    {
        func(*it, buffer_info->handle, offset, count_buffer_info->handle, count_buffer_offset, max_draw_count, stride);
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer,
             buffer_info->handle,
             offset,
             count_buffer_info->handle,
             count_buffer_offset,
             max_draw_count,
             stride);
    }

    if (must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::HandleCmdDrawIndexedIndirectCount(
    const ApiCallInfo&                    call_info,
    PFN_vkCmdDrawIndirectCountKHR         func,
    VkCommandBuffer                       original_command_buffer,
    const VulkanBufferInfo*               buffer_info,
    VkDeviceSize                          offset,
    const VulkanBufferInfo*               count_buffer_info,
    VkDeviceSize                          count_buffer_offset,
    uint32_t                              max_draw_count,
    uint32_t                              stride,
    DrawCallsDumpingContext::DrawCallType drawcall_type)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t           dc_index   = call_info.index;
    const bool               must_dump  = MustDumpDrawCall(original_command_buffer, dc_index);
    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);

    // Finalize draw call command buffer before the actual draw call in order
    // to handle dumping render targets before the draw call
    if (dump_resources_before_ && must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }

    if (dc_context != nullptr && must_dump)
    {
        dc_context->InsertNewDrawIndexedIndirectCountParameters(dc_index,
                                                                buffer_info,
                                                                offset,
                                                                count_buffer_info,
                                                                count_buffer_offset,
                                                                max_draw_count,
                                                                stride,
                                                                drawcall_type);
    }

    CommandBufferIterator first, last;
    GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    for (CommandBufferIterator it = first; it < last; ++it)
    {
        func(*it, buffer_info->handle, offset, count_buffer_info->handle, count_buffer_offset, max_draw_count, stride);
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer,
             buffer_info->handle,
             offset,
             count_buffer_info->handle,
             count_buffer_offset,
             max_draw_count,
             stride);
    }

    if (must_dump)
    {
        assert(dc_context != nullptr);
        dc_context->FinalizeCommandBuffer();
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdBeginRenderPass(
    const ApiCallInfo&                                   call_info,
    PFN_vkCmdBeginRenderPass                             func,
    VkCommandBuffer                                      original_command_buffer,
    StructPointerDecoder<Decoded_VkRenderPassBeginInfo>* pRenderPassBegin,
    VkSubpassContents                                    contents)
{
    assert(IsRecording(original_command_buffer));

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context != nullptr && dc_context->ShouldHandleRenderPass(call_info.index))
    {
        const auto render_pass_info_meta = pRenderPassBegin->GetMetaStructPointer();
        auto       framebuffer_id        = render_pass_info_meta->framebuffer;
        auto       render_pass_id        = render_pass_info_meta->renderPass;

        const VulkanFramebufferInfo* framebuffer_info = object_info_table_->GetVkFramebufferInfo(framebuffer_id);
        assert(framebuffer_info);

        VulkanRenderPassInfo* render_pass_info = object_info_table_->GetVkRenderPassInfo(render_pass_id);
        assert(render_pass_info);

        // The attachments for imageless framebuffers are provided in the pNext chain of vkCmdBeginRenderPass
        if ((framebuffer_info->framebuffer_flags & VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT) ==
            VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT)
        {
            const auto* attachment_begin_info = GetPNextMetaStruct<Decoded_VkRenderPassAttachmentBeginInfo>(
                pRenderPassBegin->GetMetaStructPointer()->pNext);
            GFXRECON_ASSERT(attachment_begin_info);

            uint32_t                num_attachments = attachment_begin_info->pAttachments.GetLength();
            const format::HandleId* handle_ids      = attachment_begin_info->pAttachments.GetPointer();

            GFXRECON_ASSERT(num_attachments == render_pass_info->attachment_description_final_layouts.size());
            render_pass_info->begin_renderpass_override_attachments.assign(handle_ids, handle_ids + num_attachments);
        }

        // Do not record vkCmdBeginRenderPass commands in current DrawCall context command buffers.
        // It will be handled by DrawCallsDumpingContext::BeginRenderPass
        const auto* renderpass_begin_info = pRenderPassBegin->GetPointer();
        VkResult res = dc_context->BeginRenderPass(render_pass_info, framebuffer_info, renderpass_begin_info, contents);
        assert(res == VK_SUCCESS);
    }
    else if (dc_context != nullptr)
    {
        CommandBufferIterator first, last;
        dc_context->GetDrawCallActiveCommandBuffers(first, last);
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, pRenderPassBegin->GetPointer(), contents);
        }
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer, pRenderPassBegin->GetPointer(), contents);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdBeginRenderPass2(
    const ApiCallInfo&                                   call_info,
    PFN_vkCmdBeginRenderPass2                            func,
    VkCommandBuffer                                      original_command_buffer,
    StructPointerDecoder<Decoded_VkRenderPassBeginInfo>* pRenderPassBegin,
    StructPointerDecoder<Decoded_VkSubpassBeginInfo>*    pSubpassBeginInfo)
{
    assert(IsRecording(original_command_buffer));

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context != nullptr && dc_context->ShouldHandleRenderPass(call_info.index))
    {
        const auto render_pass_info_meta = pRenderPassBegin->GetMetaStructPointer();
        auto       framebuffer_id        = render_pass_info_meta->framebuffer;
        auto       render_pass_id        = render_pass_info_meta->renderPass;

        const VulkanFramebufferInfo* framebuffer_info = object_info_table_->GetVkFramebufferInfo(framebuffer_id);
        assert(framebuffer_info);

        VulkanRenderPassInfo* render_pass_info = object_info_table_->GetVkRenderPassInfo(render_pass_id);
        assert(render_pass_info);

        if ((framebuffer_info->framebuffer_flags & VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT) ==
            VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT)
        {
            // The attachments for imageless framebuffers are provided in the pNext chain of vkCmdBeginRenderPass
            const auto* attachment_begin_info = GetPNextMetaStruct<Decoded_VkRenderPassAttachmentBeginInfo>(
                pRenderPassBegin->GetMetaStructPointer()->pNext);
            GFXRECON_ASSERT(attachment_begin_info);

            uint32_t                num_attachments = attachment_begin_info->pAttachments.GetLength();
            const format::HandleId* handle_ids      = attachment_begin_info->pAttachments.GetPointer();

            GFXRECON_ASSERT(num_attachments == render_pass_info->attachment_description_final_layouts.size());
            render_pass_info->begin_renderpass_override_attachments.assign(handle_ids, handle_ids + num_attachments);
        }

        // Do not record vkCmdBeginRenderPass commands in current DrawCall context command buffers.
        // It will be handled by DrawCallsDumpingContext::BeginRenderPass
        const auto* renderpass_begin_info = pRenderPassBegin->GetPointer();
        VkResult    res                   = dc_context->BeginRenderPass(
            render_pass_info, framebuffer_info, renderpass_begin_info, pSubpassBeginInfo->GetPointer()->contents);

        assert(res == VK_SUCCESS);
    }
    else if (dc_context != nullptr)
    {
        CommandBufferIterator first, last;
        dc_context->GetDrawCallActiveCommandBuffers(first, last);
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, pRenderPassBegin->GetPointer(), pSubpassBeginInfo->GetPointer());
        }
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer, pRenderPassBegin->GetPointer(), pSubpassBeginInfo->GetPointer());
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdNextSubpass(const ApiCallInfo&   call_info,
                                                           PFN_vkCmdNextSubpass func,
                                                           VkCommandBuffer      original_command_buffer,
                                                           VkSubpassContents    contents)
{
    assert(original_command_buffer != VK_NULL_HANDLE);
    assert(IsRecording(original_command_buffer));

    // Do not record NextSubpass commands in current DrawCall context command buffers.
    // It will be handled by DrawCallsDumpingContext::NextSubpass
    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context != nullptr && dc_context->ShouldHandleRenderPass(call_info.index))
    {
        dc_context->NextSubpass(contents);
    }
    else if (dc_context != nullptr)
    {
        CommandBufferIterator first, last;
        dc_context->GetDrawCallActiveCommandBuffers(first, last);
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, contents);
        }
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer, contents);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdNextSubpass2(
    const ApiCallInfo&                                call_info,
    PFN_vkCmdNextSubpass2                             func,
    VkCommandBuffer                                   original_command_buffer,
    StructPointerDecoder<Decoded_VkSubpassBeginInfo>* pSubpassBeginInfo,
    StructPointerDecoder<Decoded_VkSubpassEndInfo>*   pSubpassEndInfo)
{
    assert(original_command_buffer != VK_NULL_HANDLE);
    assert(IsRecording(original_command_buffer));

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context != nullptr && dc_context->ShouldHandleRenderPass(call_info.index))
    {
        // Do not record NextSubpass commands in current DrawCall context command buffers.
        // It will be handled by DrawCallsDumpingContext::NextSubpass
        dc_context->NextSubpass(pSubpassBeginInfo->GetPointer()->contents);
    }
    else if (dc_context != nullptr)
    {
        CommandBufferIterator first, last;
        dc_context->GetDrawCallActiveCommandBuffers(first, last);
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, pSubpassBeginInfo->GetPointer(), pSubpassEndInfo->GetPointer());
        }
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer, pSubpassBeginInfo->GetPointer(), pSubpassEndInfo->GetPointer());
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdEndRenderPass(const ApiCallInfo&     call_info,
                                                             PFN_vkCmdEndRenderPass func,
                                                             VkCommandBuffer        original_command_buffer)
{
    assert(IsRecording(original_command_buffer));

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context != nullptr && dc_context->ShouldHandleRenderPass(call_info.index))
    {
        // Do not record EndRenderPass commands in current DrawCall context command buffers.
        // It will be handled by DrawCallsDumpingContext::EndRenderPass
        dc_context->EndRenderPass();
    }
    else if (dc_context != nullptr)
    {
        CommandBufferIterator first, last;
        dc_context->GetDrawCallActiveCommandBuffers(first, last);
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it);
        }
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdEndRenderPass2(
    const ApiCallInfo&                              call_info,
    PFN_vkCmdEndRenderPass2                         func,
    VkCommandBuffer                                 original_command_buffer,
    StructPointerDecoder<Decoded_VkSubpassEndInfo>* pSubpassEndInfo)
{
    assert(IsRecording(original_command_buffer));

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context != nullptr && dc_context->ShouldHandleRenderPass(call_info.index))
    {
        // Do not record EndRenderPass commands in current DrawCall context command buffers.
        // It will be handled by DrawCallsDumpingContext::EndRenderPass
        dc_context->EndRenderPass();
    }
    else if (dc_context != nullptr)
    {
        CommandBufferIterator first, last;
        dc_context->GetDrawCallActiveCommandBuffers(first, last);
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, pSubpassEndInfo->GetPointer());
        }
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer, pSubpassEndInfo->GetPointer());
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdBindPipeline(const ApiCallInfo&        call_info,
                                                            PFN_vkCmdBindPipeline     func,
                                                            VkCommandBuffer           original_command_buffer,
                                                            VkPipelineBindPoint       pipelineBindPoint,
                                                            const VulkanPipelineInfo* pipeline)
{
    assert(pipeline);
    assert(IsRecording(original_command_buffer));

    CommandBufferIterator first, last;
    if (GetDrawCallActiveCommandBuffers(original_command_buffer, first, last))
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, pipelineBindPoint, pipeline->handle);
        }

        DrawCallsDumpingContext* context = FindDrawCallCommandBufferContext(original_command_buffer);
        assert(context);
        context->BindPipeline(pipelineBindPoint, pipeline);
    }

    VkCommandBuffer dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        func(dispatch_rays_command_buffer, pipelineBindPoint, pipeline->handle);

        DispatchTraceRaysDumpingContext* context = FindDispatchRaysCommandBufferContext(original_command_buffer);
        GFXRECON_ASSERT(context != nullptr);
        context->BindPipeline(pipelineBindPoint, pipeline);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdBindDescriptorSets(const ApiCallInfo&          call_info,
                                                                  PFN_vkCmdBindDescriptorSets func,
                                                                  VkCommandBuffer             original_command_buffer,
                                                                  VkPipelineBindPoint         pipeline_bind_point,
                                                                  const VulkanPipelineLayoutInfo* layout_info,
                                                                  uint32_t                        first_set,
                                                                  uint32_t                        descriptor_sets_count,
                                                                  const format::HandleId*         descriptor_sets_ids,
                                                                  uint32_t                        dynamicOffsetCount,
                                                                  const uint32_t*                 pDynamicOffsets)
{
    assert(IsRecording(original_command_buffer));
    assert(descriptor_sets_ids);

    std::vector<VkDescriptorSet>                desc_set_handles(descriptor_sets_count, VK_NULL_HANDLE);
    std::vector<const VulkanDescriptorSetInfo*> desc_set_infos(descriptor_sets_count, nullptr);

    for (uint32_t i = 0; i < descriptor_sets_count; ++i)
    {
        const VulkanDescriptorSetInfo* desc_set_info =
            object_info_table_->GetVkDescriptorSetInfo(descriptor_sets_ids[i]);
        desc_set_infos[i]   = desc_set_info;
        desc_set_handles[i] = (desc_set_info != nullptr) ? desc_set_info->handle : VK_NULL_HANDLE;
    }

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context)
    {
        dc_context->BindDescriptorSets(
            pipeline_bind_point, first_set, desc_set_infos, dynamicOffsetCount, pDynamicOffsets);
    }

    CommandBufferIterator first, last;
    GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    for (CommandBufferIterator it = first; it < last; ++it)
    {
        func(*it,
             pipeline_bind_point,
             layout_info->handle,
             first_set,
             descriptor_sets_count,
             desc_set_handles.data(),
             dynamicOffsetCount,
             pDynamicOffsets);
    }

    VkCommandBuffer dr_cmd_buf = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dr_cmd_buf != VK_NULL_HANDLE)
    {
        func(dr_cmd_buf,
             pipeline_bind_point,
             layout_info->handle,
             first_set,
             descriptor_sets_count,
             desc_set_handles.data(),
             dynamicOffsetCount,
             pDynamicOffsets);
    }

    DispatchTraceRaysDumpingContext* dr_context = FindDispatchRaysCommandBufferContext(original_command_buffer);
    if (dr_context)
    {
        dr_context->BindDescriptorSets(
            pipeline_bind_point, first_set, desc_set_infos, dynamicOffsetCount, pDynamicOffsets);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdBindIndexBuffer(const ApiCallInfo&       call_info,
                                                               PFN_vkCmdBindIndexBuffer func,
                                                               VkCommandBuffer          original_command_buffer,
                                                               const VulkanBufferInfo*  buffer,
                                                               VkDeviceSize             offset,
                                                               VkIndexType              indexType)
{
    // buffer can be VK_NULL_HANDLE/NULL
    VkBuffer buffer_handle = buffer != nullptr ? buffer->handle : VK_NULL_HANDLE;

    CommandBufferIterator first, last;
    bool                  found = GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    if (found)
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, buffer_handle, offset, indexType);
        }
    }

    VkCommandBuffer dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        func(dispatch_rays_command_buffer, buffer_handle, offset, indexType);
    }

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context != nullptr)
    {
        dc_context->BindIndexBuffer(call_info.index, buffer, offset, indexType);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdBindIndexBuffer2KHR(const ApiCallInfo&           call_info,
                                                                   PFN_vkCmdBindIndexBuffer2KHR func,
                                                                   VkCommandBuffer              original_command_buffer,
                                                                   const VulkanBufferInfo*      buffer,
                                                                   VkDeviceSize                 offset,
                                                                   VkDeviceSize                 size,
                                                                   VkIndexType                  indexType)
{
    // buffer can be VK_NULL_HANDLE/NULL
    VkBuffer buffer_handle = buffer != nullptr ? buffer->handle : VK_NULL_HANDLE;

    CommandBufferIterator first, last;
    bool                  found = GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    if (found)
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, buffer_handle, offset, size, indexType);
        }
    }

    VkCommandBuffer dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        func(dispatch_rays_command_buffer, buffer_handle, offset, size, indexType);
    }

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context != nullptr)
    {
        dc_context->BindIndexBuffer(call_info.index, buffer, offset, indexType, size);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdBindVertexBuffers(const ApiCallInfo&         call_info,
                                                                 PFN_vkCmdBindVertexBuffers func,
                                                                 VkCommandBuffer            original_command_buffer,
                                                                 uint32_t                   firstBinding,
                                                                 uint32_t                   bindingCount,
                                                                 const format::HandleId*    buffer_ids,
                                                                 const VkDeviceSize*        pOffsets)
{
    CommandBufferIterator first, last;
    bool                  found = GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    VkCommandBuffer       dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);

    std::vector<const VulkanBufferInfo*> buffer_infos(bindingCount, nullptr);
    std::vector<VkBuffer>                buffer_handles(bindingCount, VK_NULL_HANDLE);
    if (found || dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        for (uint32_t i = 0; i < bindingCount; ++i)
        {
            // Buffer can be VK_NULL_HANDLE
            const VulkanBufferInfo* buffer_info = object_info_table_->GetVkBufferInfo(buffer_ids[i]);

            buffer_infos[i]   = buffer_info;
            buffer_handles[i] = buffer_info != nullptr ? buffer_info->handle : VK_NULL_HANDLE;
        }
    }

    if (found)
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, firstBinding, bindingCount, buffer_handles.data(), pOffsets);
        }
    }

    if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        func(dispatch_rays_command_buffer, firstBinding, bindingCount, buffer_handles.data(), pOffsets);
    }

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context != nullptr && bindingCount)
    {
        assert(buffer_infos.size() == bindingCount);
        dc_context->BindVertexBuffers(call_info.index, firstBinding, buffer_infos, pOffsets);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdSetVertexInputEXT(
    const ApiCallInfo&                                                   call_info,
    PFN_vkCmdSetVertexInputEXT                                           func,
    VkCommandBuffer                                                      original_command_buffer,
    uint32_t                                                             vertexBindingDescriptionCount,
    StructPointerDecoder<Decoded_VkVertexInputBindingDescription2EXT>*   pVertexBindingDescriptions,
    uint32_t                                                             vertexAttributeDescriptionCount,
    StructPointerDecoder<Decoded_VkVertexInputAttributeDescription2EXT>* pVertexAttributeDescriptions)
{
    const VkVertexInputBindingDescription2EXT* in_pVertexBindingDescriptions = pVertexBindingDescriptions->GetPointer();
    const VkVertexInputAttributeDescription2EXT* in_pVertexAttributeDescriptions =
        pVertexAttributeDescriptions->GetPointer();

    CommandBufferIterator first, last;
    if (GetDrawCallActiveCommandBuffers(original_command_buffer, first, last))
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it,
                 vertexBindingDescriptionCount,
                 in_pVertexBindingDescriptions,
                 vertexAttributeDescriptionCount,
                 in_pVertexAttributeDescriptions);
        }

        DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
        dc_context->SetVertexInput(vertexBindingDescriptionCount,
                                   in_pVertexBindingDescriptions,
                                   vertexAttributeDescriptionCount,
                                   in_pVertexAttributeDescriptions);
    }

    VkCommandBuffer dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        func(dispatch_rays_command_buffer,
             vertexBindingDescriptionCount,
             in_pVertexBindingDescriptions,
             vertexAttributeDescriptionCount,
             in_pVertexAttributeDescriptions);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdBindVertexBuffers2EXT(const ApiCallInfo&             call_info,
                                                                     PFN_vkCmdBindVertexBuffers2EXT func,
                                                                     VkCommandBuffer         original_command_buffer,
                                                                     uint32_t                firstBinding,
                                                                     uint32_t                bindingCount,
                                                                     const format::HandleId* pBuffers_ids,
                                                                     const VkDeviceSize*     pOffsets,
                                                                     const VkDeviceSize*     pSizes,
                                                                     const VkDeviceSize*     pStrides)
{
    HandleCmdBindVertexBuffers2(
        call_info, func, original_command_buffer, firstBinding, bindingCount, pBuffers_ids, pOffsets, pSizes, pStrides);
}

void VulkanReplayDumpResourcesBase::OverrideCmdBindVertexBuffers2(const ApiCallInfo&          call_info,
                                                                  PFN_vkCmdBindVertexBuffers2 func,
                                                                  VkCommandBuffer             original_command_buffer,
                                                                  uint32_t                    firstBinding,
                                                                  uint32_t                    bindingCount,
                                                                  const format::HandleId*     pBuffers_ids,
                                                                  const VkDeviceSize*         pOffsets,
                                                                  const VkDeviceSize*         pSizes,
                                                                  const VkDeviceSize*         pStrides)
{
    HandleCmdBindVertexBuffers2(
        call_info, func, original_command_buffer, firstBinding, bindingCount, pBuffers_ids, pOffsets, pSizes, pStrides);
}

void VulkanReplayDumpResourcesBase::HandleCmdBindVertexBuffers2(const ApiCallInfo&          call_info,
                                                                PFN_vkCmdBindVertexBuffers2 func,
                                                                VkCommandBuffer             original_command_buffer,
                                                                uint32_t                    firstBinding,
                                                                uint32_t                    bindingCount,
                                                                const format::HandleId*     pBuffers_ids,
                                                                const VkDeviceSize*         pOffsets,
                                                                const VkDeviceSize*         pSizes,
                                                                const VkDeviceSize*         pStrides)
{
    CommandBufferIterator first, last;
    bool                  dc_found = GetDrawCallActiveCommandBuffers(original_command_buffer, first, last);
    VkCommandBuffer       dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);

    std::vector<VkBuffer> buffer_handles(bindingCount);
    if (dc_found || dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        for (uint32_t i = 0; i < bindingCount; ++i)
        {
            const VulkanBufferInfo* buffer_info = object_info_table_->GetVkBufferInfo(pBuffers_ids[i]);
            buffer_handles[i]                   = (buffer_info != nullptr) ? buffer_info->handle : VK_NULL_HANDLE;
        }
    }

    if (dc_found)
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, firstBinding, bindingCount, buffer_handles.data(), pOffsets, pSizes, pStrides);
        }

        DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
        if (dc_context != nullptr && bindingCount)
        {
            std::vector<const VulkanBufferInfo*> buffer_infos(bindingCount);

            for (uint32_t i = 0; i < bindingCount; ++i)
            {
                const VulkanBufferInfo* buffer_info = object_info_table_->GetVkBufferInfo(pBuffers_ids[i]);

                buffer_infos[i] = buffer_info;
            }

            dc_context->BindVertexBuffers2(call_info.index, firstBinding, buffer_infos, pOffsets, pSizes, pStrides);
        }
    }

    if (dispatch_rays_command_buffer)
    {
        func(dispatch_rays_command_buffer,
             firstBinding,
             bindingCount,
             buffer_handles.data(),
             pOffsets,
             pSizes,
             pStrides);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdDispatch(const ApiCallInfo& call_info,
                                                        PFN_vkCmdDispatch  func,
                                                        VkCommandBuffer    original_command_buffer,
                                                        uint32_t           groupCountX,
                                                        uint32_t           groupCountY,
                                                        uint32_t           groupCountZ)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t                   disp_index = call_info.index;
    const bool                       must_dump  = MustDumpDispatch(original_command_buffer, disp_index);
    DispatchTraceRaysDumpingContext* dr_context = FindDispatchRaysCommandBufferContext(original_command_buffer);

    if (must_dump)
    {
        dr_context->InsertNewDispatchParameters(disp_index, groupCountX, groupCountY, groupCountZ);
    }

    if (dump_resources_before_ && must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->CloneDispatchMutableResources(disp_index, true);
        dr_context->FinalizeCommandBuffer(true);
    }

    CommandBufferIterator first, last;
    if (GetDrawCallActiveCommandBuffers(original_command_buffer, first, last))
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, groupCountX, groupCountY, groupCountZ);
        }
    }

    VkCommandBuffer dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        func(dispatch_rays_command_buffer, groupCountX, groupCountY, groupCountZ);
    }

    if (must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->CloneDispatchMutableResources(disp_index, false);
        dr_context->FinalizeCommandBuffer(true);
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdDispatchIndirect(const ApiCallInfo&        call_info,
                                                                PFN_vkCmdDispatchIndirect func,
                                                                VkCommandBuffer           original_command_buffer,
                                                                const VulkanBufferInfo*   buffer_info,
                                                                VkDeviceSize              offset)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t                   disp_index = call_info.index;
    const bool                       must_dump  = MustDumpDispatch(original_command_buffer, disp_index);
    DispatchTraceRaysDumpingContext* dr_context = FindDispatchRaysCommandBufferContext(original_command_buffer);

    if (must_dump)
    {
        dr_context->InsertNewDispatchParameters(disp_index, buffer_info, offset);
    }

    if (dump_resources_before_ && must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->CloneDispatchMutableResources(disp_index, true);
        dr_context->FinalizeCommandBuffer(true);
    }

    CommandBufferIterator first, last;
    if (GetDrawCallActiveCommandBuffers(original_command_buffer, first, last))
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, buffer_info->handle, offset);
        }
    }

    VkCommandBuffer dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        func(dispatch_rays_command_buffer, buffer_info->handle, offset);
    }

    if (must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->CloneDispatchMutableResources(disp_index, false);
        dr_context->FinalizeCommandBuffer(true);
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdTraceRaysKHR(
    const ApiCallInfo&                                             call_info,
    PFN_vkCmdTraceRaysKHR                                          func,
    VkCommandBuffer                                                original_command_buffer,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pRaygenShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pMissShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pHitShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pCallableShaderBindingTable,
    uint32_t                                                       width,
    uint32_t                                                       height,
    uint32_t                                                       depth)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t                   tr_index   = call_info.index;
    const bool                       must_dump  = MustDumpTraceRays(original_command_buffer, tr_index);
    DispatchTraceRaysDumpingContext* dr_context = FindDispatchRaysCommandBufferContext(original_command_buffer);

    const VkStridedDeviceAddressRegionKHR* in_pRaygenShaderBindingTable   = pRaygenShaderBindingTable->GetPointer();
    const VkStridedDeviceAddressRegionKHR* in_pMissShaderBindingTable     = pMissShaderBindingTable->GetPointer();
    const VkStridedDeviceAddressRegionKHR* in_pHitShaderBindingTable      = pHitShaderBindingTable->GetPointer();
    const VkStridedDeviceAddressRegionKHR* in_pCallableShaderBindingTable = pCallableShaderBindingTable->GetPointer();

    if (must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->InsertNewTraceRaysParameters(tr_index,
                                                 in_pRaygenShaderBindingTable,
                                                 in_pMissShaderBindingTable,
                                                 in_pHitShaderBindingTable,
                                                 in_pCallableShaderBindingTable,
                                                 width,
                                                 height,
                                                 depth);
    }

    if (dump_resources_before_ && must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->CloneTraceRaysMutableResources(tr_index, true);
        dr_context->FinalizeCommandBuffer(true);
    }

    CommandBufferIterator first, last;
    if (GetDrawCallActiveCommandBuffers(original_command_buffer, first, last))
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it,
                 in_pRaygenShaderBindingTable,
                 in_pMissShaderBindingTable,
                 in_pHitShaderBindingTable,
                 in_pCallableShaderBindingTable,
                 width,
                 height,
                 depth);
        }
    }

    VkCommandBuffer dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        func(dispatch_rays_command_buffer,
             in_pRaygenShaderBindingTable,
             in_pMissShaderBindingTable,
             in_pHitShaderBindingTable,
             in_pCallableShaderBindingTable,
             width,
             height,
             depth);
    }

    if (must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->CloneTraceRaysMutableResources(tr_index, false);
        dr_context->FinalizeCommandBuffer(false);
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdTraceRaysIndirectKHR(
    const ApiCallInfo&                                             call_info,
    PFN_vkCmdTraceRaysIndirectKHR                                  func,
    VkCommandBuffer                                                original_command_buffer,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pRaygenShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pMissShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pHitShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pCallableShaderBindingTable,
    VkDeviceAddress                                                indirectDeviceAddress)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t                   tr_index   = call_info.index;
    const bool                       must_dump  = MustDumpTraceRays(original_command_buffer, tr_index);
    DispatchTraceRaysDumpingContext* dr_context = FindDispatchRaysCommandBufferContext(original_command_buffer);

    const VkStridedDeviceAddressRegionKHR* in_pRaygenShaderBindingTable   = pRaygenShaderBindingTable->GetPointer();
    const VkStridedDeviceAddressRegionKHR* in_pMissShaderBindingTable     = pMissShaderBindingTable->GetPointer();
    const VkStridedDeviceAddressRegionKHR* in_pHitShaderBindingTable      = pHitShaderBindingTable->GetPointer();
    const VkStridedDeviceAddressRegionKHR* in_pCallableShaderBindingTable = pCallableShaderBindingTable->GetPointer();

    if (must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->InsertNewTraceRaysIndirectParameters(tr_index,
                                                         in_pRaygenShaderBindingTable,
                                                         in_pMissShaderBindingTable,
                                                         in_pHitShaderBindingTable,
                                                         in_pCallableShaderBindingTable,
                                                         indirectDeviceAddress);
    }

    if (dump_resources_before_ && must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->CloneTraceRaysMutableResources(tr_index, true);
        dr_context->FinalizeCommandBuffer(true);
    }

    CommandBufferIterator first, last;
    if (GetDrawCallActiveCommandBuffers(original_command_buffer, first, last))
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it,
                 in_pRaygenShaderBindingTable,
                 in_pMissShaderBindingTable,
                 in_pHitShaderBindingTable,
                 in_pCallableShaderBindingTable,
                 indirectDeviceAddress);
        }
    }

    VkCommandBuffer dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        func(dispatch_rays_command_buffer,
             in_pRaygenShaderBindingTable,
             in_pMissShaderBindingTable,
             in_pHitShaderBindingTable,
             in_pCallableShaderBindingTable,
             indirectDeviceAddress);
    }

    if (must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->CloneTraceRaysMutableResources(tr_index, false);
        dr_context->FinalizeCommandBuffer(false);
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdTraceRaysIndirect2KHR(const ApiCallInfo&             call_info,
                                                                     PFN_vkCmdTraceRaysIndirect2KHR func,
                                                                     VkCommandBuffer original_command_buffer,
                                                                     VkDeviceAddress indirectDeviceAddress)
{
    assert(IsRecording(original_command_buffer));

    const uint64_t                   tr_index   = call_info.index;
    const bool                       must_dump  = MustDumpTraceRays(original_command_buffer, tr_index);
    DispatchTraceRaysDumpingContext* dr_context = FindDispatchRaysCommandBufferContext(original_command_buffer);

    if (must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->InsertNewTraceRaysIndirect2Parameters(tr_index, indirectDeviceAddress);
    }

    if (dump_resources_before_ && must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->CloneTraceRaysMutableResources(tr_index, true);
        dr_context->FinalizeCommandBuffer(true);
    }

    CommandBufferIterator first, last;
    if (GetDrawCallActiveCommandBuffers(original_command_buffer, first, last))
    {
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, indirectDeviceAddress);
        }
    }

    VkCommandBuffer dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(original_command_buffer);
    if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
    {
        func(dispatch_rays_command_buffer, indirectDeviceAddress);
    }

    if (must_dump)
    {
        assert(dr_context != nullptr);

        dr_context->CloneTraceRaysMutableResources(tr_index, false);
        dr_context->FinalizeCommandBuffer(false);
        UpdateRecordingStatus(original_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdBeginRendering(
    const ApiCallInfo&                             call_info,
    PFN_vkCmdBeginRendering                        func,
    VkCommandBuffer                                commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInfo>* pRenderingInfo)
{
    assert(IsRecording(commandBuffer));

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(commandBuffer);
    if (dc_context != nullptr)
    {
        if (dc_context->ShouldHandleRenderPass(call_info.index))
        {
            const auto   rendering_info_meta    = pRenderingInfo->GetMetaStructPointer();
            const size_t n_color_attachments    = rendering_info_meta->pColorAttachments->GetLength();
            const auto   color_attachments_meta = rendering_info_meta->pColorAttachments->GetMetaStructPointer();

            std::vector<VulkanImageInfo*> color_attachments(n_color_attachments);
            std::vector<VkImageLayout>    color_attachment_layouts(n_color_attachments);
            for (size_t i = 0; i < n_color_attachments; ++i)
            {
                const VulkanImageViewInfo* img_view_info =
                    object_info_table_->GetVkImageViewInfo(color_attachments_meta[i].imageView);
                assert(img_view_info != nullptr);

                VulkanImageInfo* img_info = object_info_table_->GetVkImageInfo(img_view_info->image_id);
                assert(img_info != nullptr);

                color_attachments[i]        = img_info;
                color_attachment_layouts[i] = color_attachments_meta[i].decoded_value->imageLayout;
            }

            VulkanImageInfo* depth_attachment;
            VkImageLayout    depth_attachment_layout;
            if (rendering_info_meta->pDepthAttachment != nullptr &&
                rendering_info_meta->pDepthAttachment->GetMetaStructPointer() != nullptr)
            {
                const auto depth_attachment_meta = rendering_info_meta->pDepthAttachment->GetMetaStructPointer();
                const VulkanImageViewInfo* img_view_info =
                    object_info_table_->GetVkImageViewInfo(depth_attachment_meta->imageView);
                assert(img_view_info != nullptr);

                VulkanImageInfo* img_info = object_info_table_->GetVkImageInfo(img_view_info->image_id);
                assert(img_info != nullptr);

                depth_attachment        = img_info;
                depth_attachment_layout = depth_attachment_meta->decoded_value->imageLayout;
            }
            else
            {
                depth_attachment        = nullptr;
                depth_attachment_layout = VK_IMAGE_LAYOUT_GENERAL;
            }

            dc_context->BeginRendering(color_attachments,
                                       color_attachment_layouts,
                                       depth_attachment,
                                       depth_attachment_layout,
                                       pRenderingInfo->GetPointer()->renderArea);
        }

        CommandBufferIterator first, last;
        dc_context->GetDrawCallActiveCommandBuffers(first, last);
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it, pRenderingInfo->GetPointer());
        }
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(commandBuffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer, pRenderingInfo->GetPointer());
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdBeginRenderingKHR(
    const ApiCallInfo&                             call_info,
    PFN_vkCmdBeginRenderingKHR                     func,
    VkCommandBuffer                                commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInfo>* pRenderingInfo)
{
    OverrideCmdBeginRendering(call_info, func, commandBuffer, pRenderingInfo);
}

void VulkanReplayDumpResourcesBase::OverrideCmdEndRendering(const ApiCallInfo&    call_info,
                                                            PFN_vkCmdEndRendering func,
                                                            VkCommandBuffer       commandBuffer)
{
    assert(IsRecording(commandBuffer));

    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(commandBuffer);
    if (dc_context != nullptr)
    {
        if (dc_context->ShouldHandleRenderPass(call_info.index))
        {
            dc_context->EndRendering();
        }

        CommandBufferIterator first, last;
        dc_context->GetDrawCallActiveCommandBuffers(first, last);
        for (CommandBufferIterator it = first; it < last; ++it)
        {
            func(*it);
        }
    }

    VkCommandBuffer dr_command_buffer = GetDispatchRaysCommandBuffer(commandBuffer);
    if (dr_command_buffer != VK_NULL_HANDLE)
    {
        func(dr_command_buffer);
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdEndRenderingKHR(const ApiCallInfo&       call_info,
                                                               PFN_vkCmdEndRenderingKHR func,
                                                               VkCommandBuffer          commandBuffer)
{
    OverrideCmdEndRendering(call_info, func, commandBuffer);
}

bool VulkanReplayDumpResourcesBase::MustDumpDrawCall(VkCommandBuffer original_command_buffer, uint64_t index) const
{
    assert(original_command_buffer != VK_NULL_HANDLE);
    assert(IsRecording(original_command_buffer));

    const DrawCallsDumpingContext* context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (context != nullptr)
    {
        return context->MustDumpDrawCall(index);
    }
    else
    {
        return false;
    }
}

bool VulkanReplayDumpResourcesBase::MustDumpDispatch(VkCommandBuffer original_command_buffer, uint64_t index) const
{
    assert(original_command_buffer != VK_NULL_HANDLE);
    assert(IsRecording(original_command_buffer));

    const DispatchTraceRaysDumpingContext* context = FindDispatchRaysCommandBufferContext(original_command_buffer);
    if (context != nullptr)
    {
        return context->MustDumpDispatch(index);
    }
    else
    {
        return false;
    }
}

bool VulkanReplayDumpResourcesBase::MustDumpTraceRays(VkCommandBuffer original_command_buffer, uint64_t index) const
{
    assert(original_command_buffer != VK_NULL_HANDLE);
    assert(IsRecording(original_command_buffer));

    const DispatchTraceRaysDumpingContext* context = FindDispatchRaysCommandBufferContext(original_command_buffer);
    if (context != nullptr)
    {
        return context->MustDumpTraceRays(index);
    }
    else
    {
        return false;
    }
}

VkResult VulkanReplayDumpResourcesBase::QueueSubmit(const std::vector<VkSubmitInfo>&   submit_infos,
                                                    const graphics::VulkanDeviceTable& device_table,
                                                    VkQueue                            queue,
                                                    VkFence                            fence,
                                                    uint64_t                           index)
{
    bool     pre_submit = false;
    bool     submitted  = false;
    VkResult res        = VK_SUCCESS;

    // First do a submission with all command buffer except the ones we are interested in
    std::vector<VkSubmitInfo>                 modified_submit_infos = submit_infos;
    std::vector<std::vector<VkCommandBuffer>> modified_command_buffer_handles(modified_submit_infos.size());
    for (size_t s = 0; s < modified_submit_infos.size(); s++)
    {
        size_t     command_buffer_count   = modified_submit_infos[s].commandBufferCount;
        const auto command_buffer_handles = modified_submit_infos[s].pCommandBuffers;

        for (uint32_t o = 0; o < command_buffer_count; ++o)
        {
            auto bcb_entry = cmd_buf_begin_map_.find(command_buffer_handles[o]);
            if (bcb_entry != cmd_buf_begin_map_.end())
            {
                continue;
            }
            else
            {
                pre_submit = true;
                modified_command_buffer_handles[s].push_back(command_buffer_handles[o]);
            }
        }

        if (modified_command_buffer_handles[s].size())
        {
            modified_submit_infos[s].commandBufferCount = modified_command_buffer_handles[s].size();
            modified_submit_infos[s].pCommandBuffers    = modified_command_buffer_handles[s].data();
        }
        else
        {
            modified_submit_infos[s].commandBufferCount = 0;
            modified_submit_infos[s].pCommandBuffers    = nullptr;
        }
    }

    if (pre_submit)
    {
        res =
            device_table.QueueSubmit(queue, modified_submit_infos.size(), modified_submit_infos.data(), VK_NULL_HANDLE);
        if (res != VK_SUCCESS)
        {
            GFXRECON_LOG_ERROR(
                "(%s:%u) QueueSubmit failed with %s", __FILE__, __LINE__, util::ToString<VkResult>(res).c_str());
            Release();
            return res;
        }

        // Wait
        res = device_table.QueueWaitIdle(queue);
        if (res != VK_SUCCESS)
        {
            GFXRECON_LOG_ERROR("QueueWaitIdle failed with %s", util::ToString<VkResult>(res).c_str());
            Release();
            return res;
        }
    }

    if (!output_json_per_command)
    {
        active_delegate_->DumpStart();
    }

    for (size_t s = 0; s < submit_infos.size(); s++)
    {
        size_t     command_buffer_count   = submit_infos[s].commandBufferCount;
        const auto command_buffer_handles = submit_infos[s].pCommandBuffers;

        for (size_t o = 0; o < command_buffer_count; ++o)
        {
            if (pre_submit)
            {
                // These semaphores have already been handled. Do not bother with them
                modified_submit_infos[s].waitSemaphoreCount   = 0;
                modified_submit_infos[s].signalSemaphoreCount = 0;
            }

            DrawCallsDumpingContext*         dc_context = FindDrawCallCommandBufferContext(command_buffer_handles[o]);
            DispatchTraceRaysDumpingContext* dr_context =
                FindDispatchRaysCommandBufferContext(command_buffer_handles[o]);

            if (dc_context != nullptr)
            {
                assert(cmd_buf_begin_map_.find(command_buffer_handles[o]) != cmd_buf_begin_map_.end());

                res = dc_context->DumpDrawCalls(
                    queue, index, cmd_buf_begin_map_[command_buffer_handles[o]], modified_submit_infos[s], fence);
                if (res != VK_SUCCESS)
                {
                    Release();
                    RaiseFatalError(("Dumping draw calls failed (" + util::ToString<VkResult>(res) + ")").c_str());
                    return res;
                }

                submitted = true;
            }

            if (dr_context != nullptr)
            {
                assert(cmd_buf_begin_map_.find(command_buffer_handles[o]) != cmd_buf_begin_map_.end());
                res = dr_context->DumpDispatchTraceRays(
                    queue, index, cmd_buf_begin_map_[command_buffer_handles[o]], modified_submit_infos[s], fence);
                if (res != VK_SUCCESS)
                {
                    Release();
                    RaiseFatalError(
                        ("Dumping dispatch/ray tracing failed (" + util::ToString<VkResult>(res) + ")").c_str());
                    return res;
                }

                submitted = true;
            }

            // In case we are dumping multiple command buffers from the same submission
            modified_submit_infos[s].waitSemaphoreCount   = 0;
            modified_submit_infos[s].signalSemaphoreCount = 0;
        }
    }

    assert(res == VK_SUCCESS);

    if (!output_json_per_command)
    {
        active_delegate_->DumpEnd();
    }

    // Looks like we didn't submit anything. Do the submission as it would have been done
    // without further modifications
    if (!submitted)
    {
        res = device_table.QueueSubmit(queue, submit_infos.size(), submit_infos.data(), fence);
        if (res != VK_SUCCESS)
        {
            GFXRECON_LOG_ERROR(
                "(%s:%u) QueueSubmit failed with %s", __FILE__, __LINE__, util::ToString<VkResult>(res).c_str());
        }
    }
    else
    {
        QueueSubmit_indices_.erase(std::remove_if(QueueSubmit_indices_.begin(),
                                                  QueueSubmit_indices_.end(),
                                                  [index](uint64_t i) { return i == index; }),
                                   QueueSubmit_indices_.end());

        // Once all submissions are complete release resources
        if (QueueSubmit_indices_.empty())
        {
            Release();
        }
    }

    return VK_SUCCESS;
}

bool VulkanReplayDumpResourcesBase::DumpingBeginCommandBufferIndex(uint64_t index) const
{
    const DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(index);

    if (dc_context == nullptr)
    {
        const DispatchTraceRaysDumpingContext* dr_context = FindDispatchRaysCommandBufferContext(index);
        return dr_context != nullptr;
    }
    else
    {
        return true;
    }
}

bool VulkanReplayDumpResourcesBase::GetDrawCallActiveCommandBuffers(VkCommandBuffer        original_command_buffer,
                                                                    CommandBufferIterator& first,
                                                                    CommandBufferIterator& last) const
{
    assert(IsRecording(original_command_buffer));

    const DrawCallsDumpingContext* stack = FindDrawCallCommandBufferContext(original_command_buffer);

    if (stack != nullptr)
    {
        stack->GetDrawCallActiveCommandBuffers(first, last);
        return true;
    }
    else
    {
        return false;
    }
}

VkCommandBuffer
VulkanReplayDumpResourcesBase::GetDispatchRaysCommandBuffer(VkCommandBuffer original_command_buffer) const
{
    assert(IsRecording(original_command_buffer));

    const DispatchTraceRaysDumpingContext* context = FindDispatchRaysCommandBufferContext(original_command_buffer);

    if (context != nullptr)
    {
        VkCommandBuffer dr_command_buffer = context->GetDispatchRaysCommandBuffer();
        assert(dr_command_buffer != VK_NULL_HANDLE);

        return dr_command_buffer;
    }
    else
    {
        return VK_NULL_HANDLE;
    }
}

bool VulkanReplayDumpResourcesBase::UpdateRecordingStatus(VkCommandBuffer original_command_buffer)
{
    assert(recording_);

    recording_ = !QueueSubmit_indices_.empty();

    return recording_;
}

bool VulkanReplayDumpResourcesBase::MustDumpQueueSubmitIndex(uint64_t index) const
{
    return std::find(QueueSubmit_indices_.begin(), QueueSubmit_indices_.end(), index) != QueueSubmit_indices_.end();
}

bool VulkanReplayDumpResourcesBase::IsRecording(VkCommandBuffer original_command_buffer) const
{
    if (recording_)
    {
        const DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
        if (dc_context)
        {
            if (dc_context->IsRecording())
            {
                return true;
            }
        }

        const DispatchTraceRaysDumpingContext* dr_context =
            FindDispatchRaysCommandBufferContext(original_command_buffer);
        if (dr_context != nullptr)
        {
            if (dr_context->IsRecording())
            {
                return true;
            }
        }
    }

    return false;
}

uint64_t
VulkanReplayDumpResourcesBase::GetBeginCommandBufferIndexOfCommandBuffer(VkCommandBuffer original_command_buffer) const
{
    const auto& entry = cmd_buf_begin_map_.find(original_command_buffer);
    if (entry != cmd_buf_begin_map_.end())
    {
        return entry->second;
    }
    else
    {
        return 0;
    }
}

void VulkanReplayDumpResourcesBase::ResetCommandBuffer(VkCommandBuffer original_command_buffer)
{
    DrawCallsDumpingContext* dc_context = FindDrawCallCommandBufferContext(original_command_buffer);
    if (dc_context != nullptr)
    {
        dc_context->Release();
    }

    DispatchTraceRaysDumpingContext* dr_context = FindDispatchRaysCommandBufferContext(original_command_buffer);
    if (dr_context != nullptr)
    {
        dr_context->Release();
    }
}

void VulkanReplayDumpResourcesBase::DumpGraphicsPipelineInfos(
    const StructPointerDecoder<Decoded_VkGraphicsPipelineCreateInfo>* pCreateInfos,
    uint32_t                                                          createInfoCount,
    HandlePointerDecoder<VkPipeline>*                                 pPipelines)
{
    const VkGraphicsPipelineCreateInfo*         in_p_create_infos = pCreateInfos->GetPointer();
    const Decoded_VkGraphicsPipelineCreateInfo* create_info_meta  = pCreateInfos->GetMetaStructPointer();

    for (uint32_t i = 0; i < createInfoCount; ++i)
    {
        VulkanPipelineInfo* pipeline_info = reinterpret_cast<VulkanPipelineInfo*>(pPipelines->GetConsumerData(i));

        // Copy vertex input state information
        if (in_p_create_infos != nullptr && in_p_create_infos[i].pVertexInputState)
        {
            // Vertex binding info
            for (uint32_t vb = 0; vb < in_p_create_infos[i].pVertexInputState->vertexBindingDescriptionCount; ++vb)
            {
                VulkanPipelineInfo::InputBindingDescription info{
                    in_p_create_infos[i].pVertexInputState->pVertexBindingDescriptions[vb].stride,
                    in_p_create_infos[i].pVertexInputState->pVertexBindingDescriptions[vb].inputRate
                };

                uint32_t binding = in_p_create_infos[i].pVertexInputState->pVertexBindingDescriptions[vb].binding;
                pipeline_info->vertex_input_binding_map.emplace(binding, info);
            }

            // Vertex attribute info
            for (uint32_t va = 0; va < in_p_create_infos[i].pVertexInputState->vertexAttributeDescriptionCount; ++va)
            {
                VulkanPipelineInfo::InputAttributeDescription info{
                    in_p_create_infos[i].pVertexInputState->pVertexAttributeDescriptions[va].binding,
                    in_p_create_infos[i].pVertexInputState->pVertexAttributeDescriptions[va].format,
                    in_p_create_infos[i].pVertexInputState->pVertexAttributeDescriptions[va].offset
                };

                uint32_t location = in_p_create_infos[i].pVertexInputState->pVertexAttributeDescriptions[va].location;
                pipeline_info->vertex_input_attribute_map.emplace(location, info);
            }
        }

        // Dynamic state
        if (in_p_create_infos != nullptr && in_p_create_infos[i].pDynamicState)
        {
            for (uint32_t ds = 0; ds < in_p_create_infos[i].pDynamicState->dynamicStateCount; ++ds)
            {
                if (in_p_create_infos[i].pDynamicState->pDynamicStates[ds] == VK_DYNAMIC_STATE_VERTEX_INPUT_EXT)
                {
                    pipeline_info->dynamic_vertex_input = true;
                }
                else if (in_p_create_infos[i].pDynamicState->pDynamicStates[ds] ==
                         VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE_EXT)
                {
                    pipeline_info->dynamic_vertex_binding_stride = true;
                }
            }
        }

        // handle optional VkGraphicsPipelineLibraryCreateInfoEXT
        const auto* gpl_info =
            graphics::vulkan_struct_get_pnext<VkGraphicsPipelineLibraryCreateInfoEXT>(in_p_create_infos);
        if (gpl_info != nullptr)
        {
            pipeline_info->gpl_flags = gpl_info->flags;
        }

        // handle optional VkPipelineLibraryCreateInfoKHR
        const auto* pipeline_library_info =
            GetPNextMetaStruct<Decoded_VkPipelineLibraryCreateInfoKHR>(create_info_meta->pNext);
        if (pipeline_library_info != nullptr)
        {
            const uint32_t          library_count = pipeline_library_info->pLibraries.GetLength();
            const format::HandleId* ppl_ids       = pipeline_library_info->pLibraries.GetPointer();

            for (uint32_t lib_idx = 0; lib_idx < library_count; ++lib_idx)
            {
                const VulkanPipelineInfo* gpl_ppl = object_info_table_->GetVkPipelineInfo(ppl_ids[lib_idx]);

                if ((gpl_ppl->gpl_flags & VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT) ==
                    VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT)
                {
                    pipeline_info->vertex_input_attribute_map    = gpl_ppl->vertex_input_attribute_map;
                    pipeline_info->vertex_input_binding_map      = gpl_ppl->vertex_input_binding_map;
                    pipeline_info->dynamic_vertex_input          = gpl_ppl->dynamic_vertex_input;
                    pipeline_info->dynamic_vertex_binding_stride = gpl_ppl->dynamic_vertex_binding_stride;
                }
            }
        }

        // Copy pipeline layout information
        if (create_info_meta != nullptr)
        {
            const auto ppl_layout_info = object_info_table_->GetVkPipelineLayoutInfo(create_info_meta[i].layout);
            if (ppl_layout_info != nullptr)
            {
                pipeline_info->desc_set_layouts = ppl_layout_info->desc_set_layouts;
            }
        }

        // Aggregate used shader stages flags
        for (uint32_t ss = 0; ss < in_p_create_infos[i].stageCount; ++ss)
        {
            pipeline_info->shader_stages |= static_cast<VkShaderStageFlags>(in_p_create_infos[i].pStages[ss].stage);
        }
    }
}

void VulkanReplayDumpResourcesBase::OverrideEndCommandBuffer(const ApiCallInfo&     call_info,
                                                             PFN_vkEndCommandBuffer func,
                                                             VkCommandBuffer        commandBuffer)
{
    if (IsRecording(commandBuffer))
    {
        DispatchTraceRaysDumpingContext* context = FindDispatchRaysCommandBufferContext(commandBuffer);
        if (context != nullptr)
        {
            context->EndCommandBuffer();
        }
    }
}

void VulkanReplayDumpResourcesBase::OverrideCmdExecuteCommands(const ApiCallInfo&       call_info,
                                                               PFN_vkCmdExecuteCommands func,
                                                               VkCommandBuffer          commandBuffer,
                                                               uint32_t                 commandBufferCount,
                                                               const VkCommandBuffer*   pCommandBuffers)
{
    CommandBufferIterator primary_first, primary_last;
    if (GetDrawCallActiveCommandBuffers(commandBuffer, primary_first, primary_last))
    {
        DrawCallsDumpingContext* primary_context = FindDrawCallCommandBufferContext(commandBuffer);
        GFXRECON_ASSERT(primary_context != nullptr);

        if (primary_context->ShouldHandleExecuteCommands(call_info.index))
        {
            uint32_t finalized_primaries = 0;
            for (uint32_t i = 0; i < commandBufferCount; ++i)
            {
                const DrawCallsDumpingContext* secondary_context = FindDrawCallCommandBufferContext(pCommandBuffers[i]);
                if (secondary_context != nullptr)
                {
                    const std::vector<VkCommandBuffer>& secondarys_command_buffers =
                        secondary_context->GetCommandBuffers();

                    GFXRECON_ASSERT(secondarys_command_buffers.size() <=
                                    primary_last - (primary_first + finalized_primaries));
                    for (size_t scb = 0; scb < secondarys_command_buffers.size(); ++scb)
                    {
                        func(*(primary_first + finalized_primaries), 1, &secondarys_command_buffers[scb]);
                        primary_context->FinalizeCommandBuffer();
                        ++finalized_primaries;
                    }

                    // All primaries have been finalized. Nothing else to do
                    if (finalized_primaries == primary_last - primary_first)
                    {
                        break;
                    }
                }
                else
                {
                    for (CommandBufferIterator primary_it = (primary_first + finalized_primaries);
                         primary_it < primary_last;
                         ++primary_it)
                    {
                        func(*primary_it, 1, &pCommandBuffers[i]);
                    }
                }
            }
            primary_context->UpdateSecondaries();
        }
        else
        {
            for (CommandBufferIterator primary_it = primary_first; primary_it < primary_last; ++primary_it)
            {
                func(*primary_it, commandBufferCount, pCommandBuffers);
            }
        }
    }

    if (IsRecording(commandBuffer))
    {
        VkCommandBuffer dispatch_rays_command_buffer = GetDispatchRaysCommandBuffer(commandBuffer);
        if (dispatch_rays_command_buffer != VK_NULL_HANDLE)
        {
            DispatchTraceRaysDumpingContext* primary_context = FindDispatchRaysCommandBufferContext(commandBuffer);
            GFXRECON_ASSERT(primary_context != nullptr);

            if (primary_context->ShouldHandleExecuteCommands(call_info.index))
            {
                for (uint32_t i = 0; i < commandBufferCount; ++i)
                {
                    const DispatchTraceRaysDumpingContext* secondary_context =
                        FindDispatchRaysCommandBufferContext(pCommandBuffers[i]);
                    if (secondary_context != nullptr)
                    {
                        VkCommandBuffer secondary_command_buffer = secondary_context->GetDispatchRaysCommandBuffer();
                        func(dispatch_rays_command_buffer, 1, &secondary_command_buffer);
                    }
                    else
                    {
                        func(dispatch_rays_command_buffer, 1, &pCommandBuffers[i]);
                    }
                }
                primary_context->UpdateSecondaries();
            }
            else
            {
                func(dispatch_rays_command_buffer, commandBufferCount, pCommandBuffers);
            }
        }
    }
}

void VulkanReplayDumpResourcesBase::DumpResourcesSetFatalErrorHandler(std::function<void(const char*)> handler)
{
    fatal_error_handler_ = handler;
}

void VulkanReplayDumpResourcesBase::RaiseFatalError(const char* message) const
{
    if (fatal_error_handler_ != nullptr)
    {
        fatal_error_handler_(message);
    }
}

GFXRECON_END_NAMESPACE(gfxrecon)
GFXRECON_END_NAMESPACE(decode)
