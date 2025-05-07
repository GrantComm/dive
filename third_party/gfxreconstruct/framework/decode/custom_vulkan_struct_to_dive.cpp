/*
** Copyright (c) 2022-2024 LunarG, Inc.
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

#include "custom_vulkan_struct_to_dive.h"
#include "generated/generated_vulkan_struct_decoders.h"
#include "generated/generated_vulkan_struct_to_dive.h"
#include "generated/generated_vulkan_enum_to_dive.h"
#include "decode/descriptor_update_template_decoder.h"
#include "decode/custom_vulkan_struct_decoders.h"

#include "util/platform.h"
#include "util/defines.h"

#include "vulkan/vulkan.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 VkGeometryTypeKHR                                     discriminant,
                 const Decoded_VkAccelerationStructureGeometryDataKHR* data)
{
    if (data)
    {
        switch (discriminant)
        {
            case VkGeometryTypeKHR::VK_GEOMETRY_TYPE_TRIANGLES_KHR:
                FieldToDive(data_map["triangles"], data->triangles);
                break;
            case VkGeometryTypeKHR::VK_GEOMETRY_TYPE_AABBS_KHR:
                FieldToDive(data_map["aabbs"], data->aabbs);
                break;
            case VkGeometryTypeKHR::VK_GEOMETRY_TYPE_INSTANCES_KHR:
                FieldToDive(data_map["instances"], data->instances);
                break;
            default:
                data_map = "Unknown GeometryType: " + std::to_string(discriminant);
        }
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkAccelerationStructureGeometryKHR* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        FieldToDive(data_map["sType"], decoded_value.sType);
        FieldToDive(data_map["geometryType"], decoded_value.geometryType);
        FieldToDive(data_map["geometry"], decoded_value.geometryType, meta_struct.geometry);
        FieldToDive(data_map["pNext"], meta_struct.pNext);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const Decoded_VkClearValue* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        FieldToDive(data_map["color"], meta_struct.color);
        FieldToDive(data_map["depthStencil"]["depth"], decoded_value.depthStencil.depth);
        FieldToDive(data_map["depthStencil"]["stencil"], decoded_value.depthStencil.stencil);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const Decoded_VkClearColorValue* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        FieldToDive(data_map["float32"], decoded_value.float32, 4);
        FieldToDive(data_map["int32"], decoded_value.int32, 4);
        FieldToDive(data_map["uint32"], decoded_value.uint32, 4);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 int                                          discriminant,
                 const Decoded_VkDeviceOrHostAddressConstKHR* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        switch (discriminant)
        {
            case 0:
                FieldToDiveAsHex(data_map["deviceAddress"], decoded_value.deviceAddress);
                break;
            case 1:
                FieldToDiveAsHex(data_map["hostAddress"], decoded_value.hostAddress);
                break;
        }
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkDeviceOrHostAddressConstKHR* data)
{
    FieldToDive(data_map, 0, data);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 int                                     discriminant,
                 const Decoded_VkDeviceOrHostAddressKHR* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        switch (discriminant)
        {
            case 0:
                FieldToDiveAsHex(data_map["deviceAddress"], decoded_value.deviceAddress);
                break;
            case 1:
                FieldToDiveAsHex(data_map["hostAddress"], decoded_value.hostAddress);
                break;
        }
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkDeviceOrHostAddressKHR* data)
{
    FieldToDive(data_map, 0, data);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 VkPipelineExecutableStatisticFormatKHR               discriminant,
                 const Decoded_VkPipelineExecutableStatisticValueKHR* data,
                 const JsonOptions&                                   options)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        switch (discriminant)
        {
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_BOOL32_KHR:
                data_map["b32"] = static_cast<bool>(decoded_value.b32);
                break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_INT64_KHR:
                data_map["i64"] = decoded_value.i64;
                break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_UINT64_KHR:
                data_map["u64"] = decoded_value.u64;
                break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_FLOAT64_KHR:
                data_map["f64"] = decoded_value.f64;
                break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_MAX_ENUM_KHR:
                GFXRECON_LOG_WARNING("Invalid format: VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_MAX_ENUM_KHR");
        }
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkPipelineExecutableStatisticKHR* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        FieldToDive(data_map["sType"], decoded_value.sType);
        FieldToDive(data_map["name"], &meta_struct.name);
        FieldToDive(data_map["description"], &meta_struct.description);
        FieldToDive(data_map["format"], decoded_value.format);
        FieldToDive(data_map["value"], decoded_value.format, meta_struct.value);
        FieldToDive(data_map["pNext"], meta_struct.pNext);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const Decoded_VkDescriptorImageInfo* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        HandleToJson(data_map["sampler"], meta_struct.sampler);
        HandleToJson(data_map["imageView"], meta_struct.imageView);
        HandleToJson(data_map["imageLayout"], decoded_value.imageLayout);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const Decoded_VkWriteDescriptorSet* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        FieldToDive(data_map["sType"], decoded_value.sType);
        HandleToJson(data_map["dstSet"], meta_struct.dstSet);
        FieldToDive(data_map["dstBinding"], decoded_value.dstBinding);
        FieldToDive(data_map["dstArrayElement"], decoded_value.dstArrayElement);
        FieldToDive(data_map["descriptorCount"], decoded_value.descriptorCount);
        FieldToDive(data_map["descriptorType"], decoded_value.descriptorType);
        switch (decoded_value.descriptorType)
        {
            case VK_DESCRIPTOR_TYPE_SAMPLER:
            case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
            case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
            case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
            case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
            case VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM:
            case VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM:
                FieldToDive(data_map["pImageInfo"], meta_struct.pImageInfo);
                break;
            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
            case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
            case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
                FieldToDive(data_map["pBufferInfo"], meta_struct.pBufferInfo);
                break;
            case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
            case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
                HandleToJson(data_map["pTexelBufferView"], &meta_struct.pTexelBufferView);
                break;
            case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR:
            case VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK:
                // Nothing to do here for acceleration-structures and inline-uniform-blocks,
                // as the rest of the data is stored in the pNext chain
                break;
            case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV:
            case VK_DESCRIPTOR_TYPE_MUTABLE_EXT:
            case VK_DESCRIPTOR_TYPE_PARTITIONED_ACCELERATION_STRUCTURE_NV:
                GFXRECON_LOG_WARNING("Descriptor type not supported at " __FILE__ ", line: %d.", __LINE__);
                break;
            case VK_DESCRIPTOR_TYPE_MAX_ENUM:
                GFXRECON_LOG_WARNING("Invalid descriptor type: VK_DESCRIPTOR_TYPE_MAX_ENUM");
        }
        FieldToDive(data_map["pNext"], meta_struct.pNext);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const VkPerformanceValueTypeINTEL          discriminant,
                 const Decoded_VkPerformanceValueDataINTEL* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        switch (discriminant)
        {
            case VK_PERFORMANCE_VALUE_TYPE_UINT32_INTEL:
                FieldToDive(data_map["value32"], decoded_value.value32);
                break;
            case VK_PERFORMANCE_VALUE_TYPE_UINT64_INTEL:
                FieldToDive(data_map["value64"], decoded_value.value64);
                break;
            case VK_PERFORMANCE_VALUE_TYPE_FLOAT_INTEL:
                FieldToDive(data_map["valueFloat"], decoded_value.valueFloat);
                break;
            case VK_PERFORMANCE_VALUE_TYPE_BOOL_INTEL:
                FieldToDive(data_map["valueBool"], decoded_value.valueBool);
                break;
            case VK_PERFORMANCE_VALUE_TYPE_STRING_INTEL:
                FieldToDive(data_map["valueString"], meta_struct.valueString);
                break;
            case VK_PERFORMANCE_VALUE_TYPE_MAX_ENUM_INTEL:
                GFXRECON_LOG_WARNING("Invalid performance value type: VK_PERFORMANCE_VALUE_TYPE_MAX_ENUM_INTEL");
        }
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const Decoded_VkPerformanceValueINTEL* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        FieldToDive(data_map["type"], decoded_value.type);
        FieldToDive(data_map["data"], decoded_value.type, meta_struct.data);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkShaderModuleCreateInfo* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        FieldToDive(data_map["sType"], decoded_value.sType);
        FieldToDive(VkShaderModuleCreateFlags_t(), data_map["flags"], decoded_value.flags);
        FieldToDive(data_map["codeSize"], decoded_value.codeSize);
        // Use "[Binary data]" as placeholder. It will be replaced with a file path if the JSON
        // consumer decides to dump binaries in separate files.
        FieldToDive(data_map["pCode"], "[Binary data]");
        FieldToDive(data_map["pNext"], meta_struct.pNext);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const Decoded_SECURITY_ATTRIBUTES* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        data_map["bInheritHandle"]   = static_cast<bool>(decoded_value.bInheritHandle);
        FieldToDive(data_map["nLength"], decoded_value.nLength);
        FieldToDive(data_map["lpSecurityDescriptor"], meta_struct.lpSecurityDescriptor->GetAddress());
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkPipelineCacheCreateInfo* data)
{
    if (data && data->decoded_value)
    {
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct   = *data;
        FieldToDive(data_map["sType"], decoded_value.sType);
        FieldToDive(VkPipelineCacheCreateFlags_t(), data_map["flags"], decoded_value.flags);
        FieldToDive(data_map["initialDataSize"], decoded_value.initialDataSize);
        // Use "[Binary data]" as placeholder. It will be replaced with a file path if the JSON
        // consumer decides to dump binaries in separate files.
        FieldToDive(data_map["pInitialData"], "[Binary data]");
        FieldToDive(data_map["pNext"], meta_struct.pNext);
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const DescriptorUpdateTemplateDecoder* const pData)
{
    if (pData)
    {
        const size_t                        image_info_count = pData->GetImageInfoCount();
        std::vector<nlohmann::ordered_json> image_infos(image_info_count);

        for (size_t image_info_index = 0; image_info_index < image_info_count; ++image_info_index)
        {
            FieldToDive(
                image_infos[image_info_index], pData->GetImageInfoMetaStructPointer() + image_info_index);
        }
        data_map["imageInfos"] = image_infos;

        const size_t                        buffer_info_count = pData->GetBufferInfoCount();
        std::vector<nlohmann::ordered_json> buffer_infos(buffer_info_count);

        for (size_t buffer_info_index = 0; buffer_info_index < buffer_info_count; ++buffer_info_index)
        {
            FieldToDive(
                buffer_infos[buffer_info_index], pData->GetBufferInfoMetaStructPointer() + buffer_info_index);
        }
        data_map["bufferInfos"] = buffer_infos;

        const size_t texel_buffer_view_count = pData->GetTexelBufferViewCount();
        if (texel_buffer_view_count > 0)
        {
            HandleToJson(
                data_map["bufferViews"], pData->GetTexelBufferViewHandleIdsPointer(), texel_buffer_view_count);
        }

        const size_t acceleration_structure_count = pData->GetAccelerationStructureKHRCount();
        if (acceleration_structure_count > 0)
        {
            HandleToJson(data_map["accelStructViews"],
                         pData->GetAccelerationStructureKHRHandleIdsPointer(),
                         acceleration_structure_count,
                         options);
        }

        const size_t inline_uniform_block_num_bytes = pData->GetInlineUniformBlockCount();
        if (inline_uniform_block_num_bytes > 0)
        {
            data_map["inlineUniformBlock"] =
                std::vector<uint8_t>(pData->GetInlineUniformBlockPointer(),
                                     pData->GetInlineUniformBlockPointer() + inline_uniform_block_num_bytes);
        }
    }
    else
    {
        data_map = nullptr;
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkPushDescriptorSetWithTemplateInfo* const pData)
{
    HandleToJson(data_map["descriptorUpdateTemplate"], pData->descriptorUpdateTemplate);
    HandleToJson(data_map["layout"], pData->layout);
    FieldToDive(data_map["set"], pData->decoded_value->set);
    FieldToDive(data_map["pData"], &pData->pData);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkIndirectExecutionSetCreateInfoEXT* const pData)
{
    FieldToDive(data_map["type"], pData->decoded_type);
    switch (pData->decoded_type)
    {
        case VK_INDIRECT_EXECUTION_SET_INFO_TYPE_PIPELINES_EXT:
            FieldToDive(data_map["info"], pData->info->pPipelineInfo);
            break;
        case VK_INDIRECT_EXECUTION_SET_INFO_TYPE_SHADER_OBJECTS_EXT:
            FieldToDive(data_map["info"], pData->info->pShaderInfo);
            break;
        default:
            break;
    }
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkIndirectCommandsLayoutTokenEXT* const pData)
{
    FieldToDive(data_map["type"], pData->decoded_type);
    switch (pData->decoded_type)
    {
        case VK_INDIRECT_COMMANDS_TOKEN_TYPE_PUSH_CONSTANT_EXT:
        case VK_INDIRECT_COMMANDS_TOKEN_TYPE_SEQUENCE_INDEX_EXT:
            FieldToDive(data_map["data"], pData->data->pPushConstant);
            break;
        case VK_INDIRECT_COMMANDS_TOKEN_TYPE_VERTEX_BUFFER_EXT:
            FieldToDive(data_map["data"], pData->data->pVertexBuffer);
            break;
        case VK_INDIRECT_COMMANDS_TOKEN_TYPE_INDEX_BUFFER_EXT:
            FieldToDive(data_map["data"], pData->data->pIndexBuffer);
            break;
        case VK_INDIRECT_COMMANDS_TOKEN_TYPE_EXECUTION_SET_EXT:
            FieldToDive(data_map["data"], pData->data->pExecutionSet);
            break;
        default:
            break;
    }
    FieldToDive(data_map["offset"], pData->offset);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const format::DeviceMemoryType& data)
{
    FieldToDive(decode::VkMemoryPropertyFlags_t(), data_map["property_flags"], data.property_flags);
    FieldToDive(data_map["heap_index"], data.heap_index);
}

void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const format::DeviceMemoryHeap& data)
{
    FieldToDive(data_map["size"], data.size);
    FieldToDive(decode::VkMemoryHeapFlags_t(), data_map["flags"], data.flags);
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
