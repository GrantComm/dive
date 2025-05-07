
#ifndef GFXRECON_DECODE_CUSTOM_VULKAN_STRUCT_TO_JSON_H
#define GFXRECON_DECODE_CUSTOM_VULKAN_STRUCT_TO_JSON_H

#include "decode/custom_vulkan_struct_decoders.h"
#include "generated/generated_vulkan_enum_to_dive.h"
#include "generated/generated_vulkan_struct_to_dive.h"
#include "generated/generated_vulkan_struct_decoders.h"
#include "decode/decode_dive_util.h"

#include "util/defines.h"
#include "util/to_string.h"

#include "vulkan/vulkan.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

class DescriptorUpdateTemplateDecoder;

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkClearValue* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkClearColorValue* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 int                                          discriminant,
                 const Decoded_VkDeviceOrHostAddressConstKHR* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkDeviceOrHostAddressConstKHR* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 int                                     discriminant,
                 const Decoded_VkDeviceOrHostAddressKHR* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkDeviceOrHostAddressKHR* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 VkPipelineExecutableStatisticFormatKHR               discriminant,
                 const Decoded_VkPipelineExecutableStatisticValueKHR* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkPipelineExecutableStatisticKHR* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_SECURITY_ATTRIBUTES* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkAccelerationStructureGeometryDataKHR* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkAccelerationStructureGeometryKHR* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkDescriptorImageInfo* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkWriteDescriptorSet* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkPerformanceValueINTEL* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkShaderModuleCreateInfo* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkPipelineCacheCreateInfo* data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const DescriptorUpdateTemplateDecoder* const pData);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkPushDescriptorSetWithTemplateInfo* const pData);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkIndirectExecutionSetCreateInfoEXT* const pData);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const Decoded_VkIndirectCommandsLayoutTokenEXT* const pData);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const format::DeviceMemoryType& data);

void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const format::DeviceMemoryHeap& data);

template <typename T>
void FieldToJson(std::map<std::string, std::map<std::string, std::string>>& data_map,
                 const std::vector<T>& data)
{
    int i = 0;
    /*for (const auto& item : data)
    {
        FieldToJson(jdata[i++], item, options);
    }*/
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_CUSTOM_VULKAN_STRUCT_TO_JSON_H
