/*
** Copyright (c) 2018-2023 Valve Corporation
** Copyright (c) 2018-2023 LunarG, Inc.
** Copyright (c) 2023 Advanced Micro Devices, Inc.
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

/*
** This file is generated from the Khronos Vulkan XML API Registry.
**
*/

#include "util/defines.h"
#include "util/dive_args.h"
#include "generated/generated_vulkan_dive_consumer.h"
#include "decode/custom_vulkan_struct_to_json.h"

#include "vulkan/vulkan.h"
#include "vk_video/vulkan_video_codec_h264std.h"
#include "vk_video/vulkan_video_codec_h264std_decode.h"
#include "vk_video/vulkan_video_codec_h264std_encode.h"
#include "vk_video/vulkan_video_codec_h265std.h"
#include "vk_video/vulkan_video_codec_h265std_decode.h"
#include "vk_video/vulkan_video_codec_h265std_encode.h"
#include "vk_video/vulkan_video_codecs_common.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

using util::JsonOptions;

void VulkanExportDiveConsumer::Process_vkCreateInstance(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    StructPointerDecoder<Decoded_VkInstanceCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkInstance>*           pInstance)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pInstance"], pInstance, json_options);
    WriteBlockEnd("vkCreateInstance");
}

void VulkanExportDiveConsumer::Process_vkDestroyInstance(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyInstance");
}

void VulkanExportDiveConsumer::Process_vkEnumeratePhysicalDevices(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    PointerDecoder<uint32_t>*                   pPhysicalDeviceCount,
    HandlePointerDecoder<VkPhysicalDevice>*     pPhysicalDevices)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pPhysicalDeviceCount"], pPhysicalDeviceCount, json_options);
    HandleToJson(args["pPhysicalDevices"], pPhysicalDevices, json_options);
    WriteBlockEnd("vkEnumeratePhysicalDevices");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFeatures(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceFeatures>* pFeatures)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pFeatures"], pFeatures, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceFeatures");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFormatProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    VkFormat                                    format,
    StructPointerDecoder<Decoded_VkFormatProperties>* pFormatProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["format"], format, json_options);
    FieldToJson(args["pFormatProperties"], pFormatProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceFormatProperties");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceImageFormatProperties(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    VkFormat                                    format,
    VkImageType                                 type,
    VkImageTiling                               tiling,
    VkImageUsageFlags                           usage,
    VkImageCreateFlags                          flags,
    StructPointerDecoder<Decoded_VkImageFormatProperties>* pImageFormatProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["format"], format, json_options);
    FieldToJson(args["type"], type, json_options);
    FieldToJson(args["tiling"], tiling, json_options);
    FieldToJson(VkImageUsageFlags_t(), args["usage"], usage, json_options);
    FieldToJson(VkImageCreateFlags_t(), args["flags"], flags, json_options);
    FieldToJson(args["pImageFormatProperties"], pImageFormatProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceImageFormatProperties");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceProperties>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceProperties");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceQueueFamilyProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pQueueFamilyPropertyCount,
    StructPointerDecoder<Decoded_VkQueueFamilyProperties>* pQueueFamilyProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pQueueFamilyPropertyCount"], pQueueFamilyPropertyCount, json_options);
    FieldToJson(args["pQueueFamilyProperties"], pQueueFamilyProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceQueueFamilyProperties");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceMemoryProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceMemoryProperties>* pMemoryProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pMemoryProperties"], pMemoryProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceMemoryProperties");
}

void VulkanExportDiveConsumer::Process_vkCreateDevice(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkDeviceCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDevice>*             pDevice)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pDevice"], pDevice, json_options);
    WriteBlockEnd("vkCreateDevice");
}

void VulkanExportDiveConsumer::Process_vkDestroyDevice(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyDevice");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceQueue(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    uint32_t                                    queueFamilyIndex,
    uint32_t                                    queueIndex,
    HandlePointerDecoder<VkQueue>*              pQueue)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["queueFamilyIndex"], queueFamilyIndex, json_options);
    FieldToJson(args["queueIndex"], queueIndex, json_options);
    HandleToJson(args["pQueue"], pQueue, json_options);
    WriteBlockEnd("vkGetDeviceQueue");
}

void VulkanExportDiveConsumer::Process_vkQueueSubmit(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    uint32_t                                    submitCount,
    StructPointerDecoder<Decoded_VkSubmitInfo>* pSubmits,
    format::HandleId                            fence)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    FieldToJson(args["submitCount"], submitCount, json_options);
    FieldToJson(args["pSubmits"], pSubmits, json_options);
    HandleToJson(args["fence"], fence, json_options);
    WriteBlockEnd("vkQueueSubmit");
}

void VulkanExportDiveConsumer::Process_vkQueueWaitIdle(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    WriteBlockEnd("vkQueueWaitIdle");
}

void VulkanExportDiveConsumer::Process_vkDeviceWaitIdle(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    WriteBlockEnd("vkDeviceWaitIdle");
}

void VulkanExportDiveConsumer::Process_vkAllocateMemory(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryAllocateInfo>* pAllocateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDeviceMemory>*       pMemory)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pAllocateInfo"], pAllocateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pMemory"], pMemory, json_options);
    WriteBlockEnd("vkAllocateMemory");
}

void VulkanExportDiveConsumer::Process_vkFreeMemory(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            memory,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["memory"], memory, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkFreeMemory");
}

void VulkanExportDiveConsumer::Process_vkMapMemory(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            memory,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkMemoryMapFlags                            flags,
    PointerDecoder<uint64_t, void*>*            ppData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["memory"], memory, json_options);
    FieldToJson(args["offset"], offset, json_options);
    FieldToJson(args["size"], size, json_options);
    FieldToJson(VkMemoryMapFlags_t(), args["flags"], flags, json_options);
    FieldToJsonAsHex(args["ppData"], ppData, json_options);
    WriteBlockEnd("vkMapMemory");
}

void VulkanExportDiveConsumer::Process_vkUnmapMemory(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            memory)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["memory"], memory, json_options);
    WriteBlockEnd("vkUnmapMemory");
}

void VulkanExportDiveConsumer::Process_vkFlushMappedMemoryRanges(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    memoryRangeCount,
    StructPointerDecoder<Decoded_VkMappedMemoryRange>* pMemoryRanges)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["memoryRangeCount"], memoryRangeCount, json_options);
    FieldToJson(args["pMemoryRanges"], pMemoryRanges, json_options);
    WriteBlockEnd("vkFlushMappedMemoryRanges");
}

void VulkanExportDiveConsumer::Process_vkInvalidateMappedMemoryRanges(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    memoryRangeCount,
    StructPointerDecoder<Decoded_VkMappedMemoryRange>* pMemoryRanges)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["memoryRangeCount"], memoryRangeCount, json_options);
    FieldToJson(args["pMemoryRanges"], pMemoryRanges, json_options);
    WriteBlockEnd("vkInvalidateMappedMemoryRanges");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceMemoryCommitment(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            memory,
    PointerDecoder<VkDeviceSize>*               pCommittedMemoryInBytes)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["memory"], memory, json_options);
    FieldToJson(args["pCommittedMemoryInBytes"], pCommittedMemoryInBytes, json_options);
    WriteBlockEnd("vkGetDeviceMemoryCommitment");
}

void VulkanExportDiveConsumer::Process_vkBindBufferMemory(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            buffer,
    format::HandleId                            memory,
    VkDeviceSize                                memoryOffset)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    HandleToJson(args["memory"], memory, json_options);
    FieldToJson(args["memoryOffset"], memoryOffset, json_options);
    WriteBlockEnd("vkBindBufferMemory");
}

void VulkanExportDiveConsumer::Process_vkBindImageMemory(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            image,
    format::HandleId                            memory,
    VkDeviceSize                                memoryOffset)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["image"], image, json_options);
    HandleToJson(args["memory"], memory, json_options);
    FieldToJson(args["memoryOffset"], memoryOffset, json_options);
    WriteBlockEnd("vkBindImageMemory");
}

void VulkanExportDiveConsumer::Process_vkGetBufferMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            buffer,
    StructPointerDecoder<Decoded_VkMemoryRequirements>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetBufferMemoryRequirements");
}

void VulkanExportDiveConsumer::Process_vkGetImageMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkMemoryRequirements>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["image"], image, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetImageMemoryRequirements");
}

void VulkanExportDiveConsumer::Process_vkGetImageSparseMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    PointerDecoder<uint32_t>*                   pSparseMemoryRequirementCount,
    StructPointerDecoder<Decoded_VkSparseImageMemoryRequirements>* pSparseMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["image"], image, json_options);
    FieldToJson(args["pSparseMemoryRequirementCount"], pSparseMemoryRequirementCount, json_options);
    FieldToJson(args["pSparseMemoryRequirements"], pSparseMemoryRequirements, json_options);
    WriteBlockEnd("vkGetImageSparseMemoryRequirements");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSparseImageFormatProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    VkFormat                                    format,
    VkImageType                                 type,
    VkSampleCountFlagBits                       samples,
    VkImageUsageFlags                           usage,
    VkImageTiling                               tiling,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkSparseImageFormatProperties>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["format"], format, json_options);
    FieldToJson(args["type"], type, json_options);
    FieldToJson(args["samples"], samples, json_options);
    FieldToJson(VkImageUsageFlags_t(), args["usage"], usage, json_options);
    FieldToJson(args["tiling"], tiling, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSparseImageFormatProperties");
}

void VulkanExportDiveConsumer::Process_vkQueueBindSparse(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindSparseInfo>* pBindInfo,
    format::HandleId                            fence)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    FieldToJson(args["bindInfoCount"], bindInfoCount, json_options);
    FieldToJson(args["pBindInfo"], pBindInfo, json_options);
    HandleToJson(args["fence"], fence, json_options);
    WriteBlockEnd("vkQueueBindSparse");
}

void VulkanExportDiveConsumer::Process_vkCreateFence(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkFenceCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkFence>*              pFence)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pFence"], pFence, json_options);
    WriteBlockEnd("vkCreateFence");
}

void VulkanExportDiveConsumer::Process_vkDestroyFence(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            fence,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["fence"], fence, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyFence");
}

void VulkanExportDiveConsumer::Process_vkResetFences(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    fenceCount,
    HandlePointerDecoder<VkFence>*              pFences)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["fenceCount"], fenceCount, json_options);
    HandleToJson(args["pFences"], pFences, json_options);
    WriteBlockEnd("vkResetFences");
}

void VulkanExportDiveConsumer::Process_vkGetFenceStatus(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            fence)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["fence"], fence, json_options);
    WriteBlockEnd("vkGetFenceStatus");
}

void VulkanExportDiveConsumer::Process_vkWaitForFences(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    fenceCount,
    HandlePointerDecoder<VkFence>*              pFences,
    VkBool32                                    waitAll,
    uint64_t                                    timeout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["fenceCount"], fenceCount, json_options);
    HandleToJson(args["pFences"], pFences, json_options);
    Bool32ToJson(args["waitAll"], waitAll, json_options);
    FieldToJson(args["timeout"], timeout, json_options);
    WriteBlockEnd("vkWaitForFences");
}

void VulkanExportDiveConsumer::Process_vkCreateSemaphore(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSemaphore>*          pSemaphore)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSemaphore"], pSemaphore, json_options);
    WriteBlockEnd("vkCreateSemaphore");
}

void VulkanExportDiveConsumer::Process_vkDestroySemaphore(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            semaphore,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["semaphore"], semaphore, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroySemaphore");
}

void VulkanExportDiveConsumer::Process_vkCreateEvent(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkEventCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkEvent>*              pEvent)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pEvent"], pEvent, json_options);
    WriteBlockEnd("vkCreateEvent");
}

void VulkanExportDiveConsumer::Process_vkDestroyEvent(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            event,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["event"], event, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyEvent");
}

void VulkanExportDiveConsumer::Process_vkGetEventStatus(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            event)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["event"], event, json_options);
    WriteBlockEnd("vkGetEventStatus");
}

void VulkanExportDiveConsumer::Process_vkSetEvent(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            event)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["event"], event, json_options);
    WriteBlockEnd("vkSetEvent");
}

void VulkanExportDiveConsumer::Process_vkResetEvent(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            event)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["event"], event, json_options);
    WriteBlockEnd("vkResetEvent");
}

void VulkanExportDiveConsumer::Process_vkCreateQueryPool(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkQueryPoolCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkQueryPool>*          pQueryPool)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pQueryPool"], pQueryPool, json_options);
    WriteBlockEnd("vkCreateQueryPool");
}

void VulkanExportDiveConsumer::Process_vkDestroyQueryPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            queryPool,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyQueryPool");
}

void VulkanExportDiveConsumer::Process_vkGetQueryPoolResults(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount,
    size_t                                      dataSize,
    PointerDecoder<uint8_t>*                    pData,
    VkDeviceSize                                stride,
    VkQueryResultFlags                          flags)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["firstQuery"], firstQuery, json_options);
    FieldToJson(args["queryCount"], queryCount, json_options);
    FieldToJson(args["dataSize"], dataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    FieldToJson(args["stride"], stride, json_options);
    FieldToJson(VkQueryResultFlags_t(), args["flags"], flags, json_options);
    WriteBlockEnd("vkGetQueryPoolResults");
}

void VulkanExportDiveConsumer::Process_vkCreateBuffer(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkBuffer>*             pBuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pBuffer"], pBuffer, json_options);
    WriteBlockEnd("vkCreateBuffer");
}

void VulkanExportDiveConsumer::Process_vkDestroyBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            buffer,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyBuffer");
}

void VulkanExportDiveConsumer::Process_vkCreateBufferView(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferViewCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkBufferView>*         pView)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pView"], pView, json_options);
    WriteBlockEnd("vkCreateBufferView");
}

void VulkanExportDiveConsumer::Process_vkDestroyBufferView(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            bufferView,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["bufferView"], bufferView, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyBufferView");
}

void VulkanExportDiveConsumer::Process_vkCreateImage(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkImage>*              pImage)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pImage"], pImage, json_options);
    WriteBlockEnd("vkCreateImage");
}

void VulkanExportDiveConsumer::Process_vkDestroyImage(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["image"], image, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyImage");
}

void VulkanExportDiveConsumer::Process_vkGetImageSubresourceLayout(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkImageSubresource>* pSubresource,
    StructPointerDecoder<Decoded_VkSubresourceLayout>* pLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["image"], image, json_options);
    FieldToJson(args["pSubresource"], pSubresource, json_options);
    FieldToJson(args["pLayout"], pLayout, json_options);
    WriteBlockEnd("vkGetImageSubresourceLayout");
}

void VulkanExportDiveConsumer::Process_vkCreateImageView(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageViewCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkImageView>*          pView)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pView"], pView, json_options);
    WriteBlockEnd("vkCreateImageView");
}

void VulkanExportDiveConsumer::Process_vkDestroyImageView(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            imageView,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["imageView"], imageView, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyImageView");
}

void VulkanExportDiveConsumer::Process_vkDestroyShaderModule(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            shaderModule,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["shaderModule"], shaderModule, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyShaderModule");
}

void VulkanExportDiveConsumer::Process_vkDestroyPipelineCache(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            pipelineCache,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipelineCache"], pipelineCache, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyPipelineCache");
}

void VulkanExportDiveConsumer::Process_vkMergePipelineCaches(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            dstCache,
    uint32_t                                    srcCacheCount,
    HandlePointerDecoder<VkPipelineCache>*      pSrcCaches)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["dstCache"], dstCache, json_options);
    FieldToJson(args["srcCacheCount"], srcCacheCount, json_options);
    HandleToJson(args["pSrcCaches"], pSrcCaches, json_options);
    WriteBlockEnd("vkMergePipelineCaches");
}

void VulkanExportDiveConsumer::Process_vkCreateGraphicsPipelines(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            pipelineCache,
    uint32_t                                    createInfoCount,
    StructPointerDecoder<Decoded_VkGraphicsPipelineCreateInfo>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipeline>*           pPipelines)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipelineCache"], pipelineCache, json_options);
    FieldToJson(args["createInfoCount"], createInfoCount, json_options);
    FieldToJson(args["pCreateInfos"], pCreateInfos, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pPipelines"], pPipelines, json_options);
    WriteBlockEnd("vkCreateGraphicsPipelines");
}

void VulkanExportDiveConsumer::Process_vkCreateComputePipelines(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            pipelineCache,
    uint32_t                                    createInfoCount,
    StructPointerDecoder<Decoded_VkComputePipelineCreateInfo>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipeline>*           pPipelines)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipelineCache"], pipelineCache, json_options);
    FieldToJson(args["createInfoCount"], createInfoCount, json_options);
    FieldToJson(args["pCreateInfos"], pCreateInfos, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pPipelines"], pPipelines, json_options);
    WriteBlockEnd("vkCreateComputePipelines");
}

void VulkanExportDiveConsumer::Process_vkDestroyPipeline(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            pipeline,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipeline"], pipeline, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyPipeline");
}

void VulkanExportDiveConsumer::Process_vkCreatePipelineLayout(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineLayoutCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipelineLayout>*     pPipelineLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pPipelineLayout"], pPipelineLayout, json_options);
    WriteBlockEnd("vkCreatePipelineLayout");
}

void VulkanExportDiveConsumer::Process_vkDestroyPipelineLayout(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            pipelineLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipelineLayout"], pipelineLayout, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyPipelineLayout");
}

void VulkanExportDiveConsumer::Process_vkCreateSampler(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSamplerCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSampler>*            pSampler)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSampler"], pSampler, json_options);
    WriteBlockEnd("vkCreateSampler");
}

void VulkanExportDiveConsumer::Process_vkDestroySampler(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            sampler,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["sampler"], sampler, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroySampler");
}

void VulkanExportDiveConsumer::Process_vkCreateDescriptorSetLayout(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorSetLayout>* pSetLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSetLayout"], pSetLayout, json_options);
    WriteBlockEnd("vkCreateDescriptorSetLayout");
}

void VulkanExportDiveConsumer::Process_vkDestroyDescriptorSetLayout(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            descriptorSetLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["descriptorSetLayout"], descriptorSetLayout, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyDescriptorSetLayout");
}

void VulkanExportDiveConsumer::Process_vkCreateDescriptorPool(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorPoolCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorPool>*     pDescriptorPool)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pDescriptorPool"], pDescriptorPool, json_options);
    WriteBlockEnd("vkCreateDescriptorPool");
}

void VulkanExportDiveConsumer::Process_vkDestroyDescriptorPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            descriptorPool,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["descriptorPool"], descriptorPool, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyDescriptorPool");
}

void VulkanExportDiveConsumer::Process_vkResetDescriptorPool(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            descriptorPool,
    VkDescriptorPoolResetFlags                  flags)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["descriptorPool"], descriptorPool, json_options);
    FieldToJson(VkDescriptorPoolResetFlags_t(), args["flags"], flags, json_options);
    WriteBlockEnd("vkResetDescriptorPool");
}

void VulkanExportDiveConsumer::Process_vkAllocateDescriptorSets(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorSetAllocateInfo>* pAllocateInfo,
    HandlePointerDecoder<VkDescriptorSet>*      pDescriptorSets)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pAllocateInfo"], pAllocateInfo, json_options);
    HandleToJson(args["pDescriptorSets"], pDescriptorSets, json_options);
    WriteBlockEnd("vkAllocateDescriptorSets");
}

void VulkanExportDiveConsumer::Process_vkFreeDescriptorSets(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            descriptorPool,
    uint32_t                                    descriptorSetCount,
    HandlePointerDecoder<VkDescriptorSet>*      pDescriptorSets)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["descriptorPool"], descriptorPool, json_options);
    FieldToJson(args["descriptorSetCount"], descriptorSetCount, json_options);
    HandleToJson(args["pDescriptorSets"], pDescriptorSets, json_options);
    WriteBlockEnd("vkFreeDescriptorSets");
}

void VulkanExportDiveConsumer::Process_vkUpdateDescriptorSets(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    uint32_t                                    descriptorWriteCount,
    StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites,
    uint32_t                                    descriptorCopyCount,
    StructPointerDecoder<Decoded_VkCopyDescriptorSet>* pDescriptorCopies)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["descriptorWriteCount"], descriptorWriteCount, json_options);
    FieldToJson(args["pDescriptorWrites"], pDescriptorWrites, json_options);
    FieldToJson(args["descriptorCopyCount"], descriptorCopyCount, json_options);
    FieldToJson(args["pDescriptorCopies"], pDescriptorCopies, json_options);
    WriteBlockEnd("vkUpdateDescriptorSets");
}

void VulkanExportDiveConsumer::Process_vkCreateFramebuffer(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkFramebufferCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkFramebuffer>*        pFramebuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pFramebuffer"], pFramebuffer, json_options);
    WriteBlockEnd("vkCreateFramebuffer");
}

void VulkanExportDiveConsumer::Process_vkDestroyFramebuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            framebuffer,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["framebuffer"], framebuffer, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyFramebuffer");
}

void VulkanExportDiveConsumer::Process_vkCreateRenderPass(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderPassCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkRenderPass>*         pRenderPass)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pRenderPass"], pRenderPass, json_options);
    WriteBlockEnd("vkCreateRenderPass");
}

void VulkanExportDiveConsumer::Process_vkDestroyRenderPass(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            renderPass,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["renderPass"], renderPass, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyRenderPass");
}

void VulkanExportDiveConsumer::Process_vkGetRenderAreaGranularity(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            renderPass,
    StructPointerDecoder<Decoded_VkExtent2D>*   pGranularity)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["renderPass"], renderPass, json_options);
    FieldToJson(args["pGranularity"], pGranularity, json_options);
    WriteBlockEnd("vkGetRenderAreaGranularity");
}

void VulkanExportDiveConsumer::Process_vkCreateCommandPool(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCommandPoolCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkCommandPool>*        pCommandPool)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pCommandPool"], pCommandPool, json_options);
    WriteBlockEnd("vkCreateCommandPool");
}

void VulkanExportDiveConsumer::Process_vkDestroyCommandPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            commandPool,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["commandPool"], commandPool, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyCommandPool");
}

void VulkanExportDiveConsumer::Process_vkResetCommandPool(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            commandPool,
    VkCommandPoolResetFlags                     flags)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["commandPool"], commandPool, json_options);
    FieldToJson(VkCommandPoolResetFlags_t(), args["flags"], flags, json_options);
    WriteBlockEnd("vkResetCommandPool");
}

void VulkanExportDiveConsumer::Process_vkAllocateCommandBuffers(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCommandBufferAllocateInfo>* pAllocateInfo,
    HandlePointerDecoder<VkCommandBuffer>*      pCommandBuffers)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pAllocateInfo"], pAllocateInfo, json_options);
    HandleToJson(args["pCommandBuffers"], pCommandBuffers, json_options);
    WriteBlockEnd("vkAllocateCommandBuffers");
}

void VulkanExportDiveConsumer::Process_vkFreeCommandBuffers(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            commandPool,
    uint32_t                                    commandBufferCount,
    HandlePointerDecoder<VkCommandBuffer>*      pCommandBuffers)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["commandPool"], commandPool, json_options);
    FieldToJson(args["commandBufferCount"], commandBufferCount, json_options);
    HandleToJson(args["pCommandBuffers"], pCommandBuffers, json_options);
    WriteBlockEnd("vkFreeCommandBuffers");
}

void VulkanExportDiveConsumer::Process_vkBeginCommandBuffer(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCommandBufferBeginInfo>* pBeginInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pBeginInfo"], pBeginInfo, json_options);
    WriteBlockEnd("vkBeginCommandBuffer");
}

void VulkanExportDiveConsumer::Process_vkEndCommandBuffer(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    WriteBlockEnd("vkEndCommandBuffer");
}

void VulkanExportDiveConsumer::Process_vkResetCommandBuffer(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer,
    VkCommandBufferResetFlags                   flags)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkCommandBufferResetFlags_t(), args["flags"], flags, json_options);
    WriteBlockEnd("vkResetCommandBuffer");
}

void VulkanExportDiveConsumer::Process_vkCmdBindPipeline(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    format::HandleId                            pipeline)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pipelineBindPoint"], pipelineBindPoint, json_options);
    HandleToJson(args["pipeline"], pipeline, json_options);
    util::DiveFunctionData function_data("vkCmdBindPipeline", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewport(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkViewport>*   pViewports)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstViewport"], firstViewport, json_options);
    FieldToJson(args["viewportCount"], viewportCount, json_options);
    FieldToJson(args["pViewports"], pViewports, json_options);
    util::DiveFunctionData function_data("vkCmdSetViewport", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetScissor(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstScissor,
    uint32_t                                    scissorCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pScissors)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstScissor"], firstScissor, json_options);
    FieldToJson(args["scissorCount"], scissorCount, json_options);
    FieldToJson(args["pScissors"], pScissors, json_options);
    util::DiveFunctionData function_data("vkCmdSetScissor", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineWidth(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    float                                       lineWidth)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["lineWidth"], lineWidth, json_options);
    util::DiveFunctionData function_data("vkCmdSetLineWidth", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBias(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    float                                       depthBiasConstantFactor,
    float                                       depthBiasClamp,
    float                                       depthBiasSlopeFactor)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["depthBiasConstantFactor"], depthBiasConstantFactor, json_options);
    FieldToJson(args["depthBiasClamp"], depthBiasClamp, json_options);
    FieldToJson(args["depthBiasSlopeFactor"], depthBiasSlopeFactor, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthBias", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetBlendConstants(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    PointerDecoder<float>*                      blendConstants)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["blendConstants"], blendConstants, json_options);
    util::DiveFunctionData function_data("vkCmdSetBlendConstants", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBounds(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    float                                       minDepthBounds,
    float                                       maxDepthBounds)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["minDepthBounds"], minDepthBounds, json_options);
    FieldToJson(args["maxDepthBounds"], maxDepthBounds, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthBounds", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilCompareMask(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    compareMask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkStencilFaceFlags_t(), args["faceMask"], faceMask, json_options);
    FieldToJson(args["compareMask"], compareMask, json_options);
    util::DiveFunctionData function_data("vkCmdSetStencilCompareMask", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilWriteMask(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    writeMask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkStencilFaceFlags_t(), args["faceMask"], faceMask, json_options);
    FieldToJson(args["writeMask"], writeMask, json_options);
    util::DiveFunctionData function_data("vkCmdSetStencilWriteMask", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilReference(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    reference)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkStencilFaceFlags_t(), args["faceMask"], faceMask, json_options);
    FieldToJson(args["reference"], reference, json_options);
    util::DiveFunctionData function_data("vkCmdSetStencilReference", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBindDescriptorSets(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    format::HandleId                            layout,
    uint32_t                                    firstSet,
    uint32_t                                    descriptorSetCount,
    HandlePointerDecoder<VkDescriptorSet>*      pDescriptorSets,
    uint32_t                                    dynamicOffsetCount,
    PointerDecoder<uint32_t>*                   pDynamicOffsets)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pipelineBindPoint"], pipelineBindPoint, json_options);
    HandleToJson(args["layout"], layout, json_options);
    FieldToJson(args["firstSet"], firstSet, json_options);
    FieldToJson(args["descriptorSetCount"], descriptorSetCount, json_options);
    HandleToJson(args["pDescriptorSets"], pDescriptorSets, json_options);
    FieldToJson(args["dynamicOffsetCount"], dynamicOffsetCount, json_options);
    FieldToJson(args["pDynamicOffsets"], pDynamicOffsets, json_options);
    util::DiveFunctionData function_data("vkCmdBindDescriptorSets", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBindIndexBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    VkIndexType                                 indexType)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    FieldToJson(args["indexType"], indexType, json_options);
    util::DiveFunctionData function_data("vkCmdBindIndexBuffer", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBindVertexBuffers(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    HandlePointerDecoder<VkBuffer>*             pBuffers,
    PointerDecoder<VkDeviceSize>*               pOffsets)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstBinding"], firstBinding, json_options);
    FieldToJson(args["bindingCount"], bindingCount, json_options);
    HandleToJson(args["pBuffers"], pBuffers, json_options);
    FieldToJson(args["pOffsets"], pOffsets, json_options);
    util::DiveFunctionData function_data("vkCmdBindVertexBuffers", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDraw(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    vertexCount,
    uint32_t                                    instanceCount,
    uint32_t                                    firstVertex,
    uint32_t                                    firstInstance)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["vertexCount"], vertexCount, json_options);
    FieldToJson(args["instanceCount"], instanceCount, json_options);
    FieldToJson(args["firstVertex"], firstVertex, json_options);
    FieldToJson(args["firstInstance"], firstInstance, json_options);
    util::DiveFunctionData function_data("vkCmdDraw", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndexed(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    indexCount,
    uint32_t                                    instanceCount,
    uint32_t                                    firstIndex,
    int32_t                                     vertexOffset,
    uint32_t                                    firstInstance)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["indexCount"], indexCount, json_options);
    FieldToJson(args["instanceCount"], instanceCount, json_options);
    FieldToJson(args["firstIndex"], firstIndex, json_options);
    FieldToJson(args["vertexOffset"], vertexOffset, json_options);
    FieldToJson(args["firstInstance"], firstInstance, json_options);
    util::DiveFunctionData function_data("vkCmdDrawIndexed", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndirect(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    FieldToJson(args["drawCount"], drawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawIndirect", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndexedIndirect(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    FieldToJson(args["drawCount"], drawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawIndexedIndirect", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDispatch(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["groupCountX"], groupCountX, json_options);
    FieldToJson(args["groupCountY"], groupCountY, json_options);
    FieldToJson(args["groupCountZ"], groupCountZ, json_options);
    util::DiveFunctionData function_data("vkCmdDispatch", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDispatchIndirect(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    util::DiveFunctionData function_data("vkCmdDispatchIndirect", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            srcBuffer,
    format::HandleId                            dstBuffer,
    uint32_t                                    regionCount,
    StructPointerDecoder<Decoded_VkBufferCopy>* pRegions)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["srcBuffer"], srcBuffer, json_options);
    HandleToJson(args["dstBuffer"], dstBuffer, json_options);
    FieldToJson(args["regionCount"], regionCount, json_options);
    FieldToJson(args["pRegions"], pRegions, json_options);
    util::DiveFunctionData function_data("vkCmdCopyBuffer", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyImage(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            srcImage,
    VkImageLayout                               srcImageLayout,
    format::HandleId                            dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    StructPointerDecoder<Decoded_VkImageCopy>*  pRegions)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["srcImage"], srcImage, json_options);
    FieldToJson(args["srcImageLayout"], srcImageLayout, json_options);
    HandleToJson(args["dstImage"], dstImage, json_options);
    FieldToJson(args["dstImageLayout"], dstImageLayout, json_options);
    FieldToJson(args["regionCount"], regionCount, json_options);
    FieldToJson(args["pRegions"], pRegions, json_options);
    util::DiveFunctionData function_data("vkCmdCopyImage", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBlitImage(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            srcImage,
    VkImageLayout                               srcImageLayout,
    format::HandleId                            dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    StructPointerDecoder<Decoded_VkImageBlit>*  pRegions,
    VkFilter                                    filter)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["srcImage"], srcImage, json_options);
    FieldToJson(args["srcImageLayout"], srcImageLayout, json_options);
    HandleToJson(args["dstImage"], dstImage, json_options);
    FieldToJson(args["dstImageLayout"], dstImageLayout, json_options);
    FieldToJson(args["regionCount"], regionCount, json_options);
    FieldToJson(args["pRegions"], pRegions, json_options);
    FieldToJson(args["filter"], filter, json_options);
    util::DiveFunctionData function_data("vkCmdBlitImage", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBufferToImage(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            srcBuffer,
    format::HandleId                            dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    StructPointerDecoder<Decoded_VkBufferImageCopy>* pRegions)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["srcBuffer"], srcBuffer, json_options);
    HandleToJson(args["dstImage"], dstImage, json_options);
    FieldToJson(args["dstImageLayout"], dstImageLayout, json_options);
    FieldToJson(args["regionCount"], regionCount, json_options);
    FieldToJson(args["pRegions"], pRegions, json_options);
    util::DiveFunctionData function_data("vkCmdCopyBufferToImage", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyImageToBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            srcImage,
    VkImageLayout                               srcImageLayout,
    format::HandleId                            dstBuffer,
    uint32_t                                    regionCount,
    StructPointerDecoder<Decoded_VkBufferImageCopy>* pRegions)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["srcImage"], srcImage, json_options);
    FieldToJson(args["srcImageLayout"], srcImageLayout, json_options);
    HandleToJson(args["dstBuffer"], dstBuffer, json_options);
    FieldToJson(args["regionCount"], regionCount, json_options);
    FieldToJson(args["pRegions"], pRegions, json_options);
    util::DiveFunctionData function_data("vkCmdCopyImageToBuffer", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdUpdateBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                dataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["dstBuffer"], dstBuffer, json_options);
    FieldToJson(args["dstOffset"], dstOffset, json_options);
    FieldToJson(args["dataSize"], dataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    util::DiveFunctionData function_data("vkCmdUpdateBuffer", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdFillBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                size,
    uint32_t                                    data)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["dstBuffer"], dstBuffer, json_options);
    FieldToJson(args["dstOffset"], dstOffset, json_options);
    FieldToJson(args["size"], size, json_options);
    FieldToJson(args["data"], data, json_options);
    util::DiveFunctionData function_data("vkCmdFillBuffer", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdClearColorImage(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            image,
    VkImageLayout                               imageLayout,
    StructPointerDecoder<Decoded_VkClearColorValue>* pColor,
    uint32_t                                    rangeCount,
    StructPointerDecoder<Decoded_VkImageSubresourceRange>* pRanges)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["image"], image, json_options);
    FieldToJson(args["imageLayout"], imageLayout, json_options);
    FieldToJson(args["pColor"], pColor, json_options);
    FieldToJson(args["rangeCount"], rangeCount, json_options);
    FieldToJson(args["pRanges"], pRanges, json_options);
    util::DiveFunctionData function_data("vkCmdClearColorImage", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdClearDepthStencilImage(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            image,
    VkImageLayout                               imageLayout,
    StructPointerDecoder<Decoded_VkClearDepthStencilValue>* pDepthStencil,
    uint32_t                                    rangeCount,
    StructPointerDecoder<Decoded_VkImageSubresourceRange>* pRanges)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["image"], image, json_options);
    FieldToJson(args["imageLayout"], imageLayout, json_options);
    FieldToJson(args["pDepthStencil"], pDepthStencil, json_options);
    FieldToJson(args["rangeCount"], rangeCount, json_options);
    FieldToJson(args["pRanges"], pRanges, json_options);
    util::DiveFunctionData function_data("vkCmdClearDepthStencilImage", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdClearAttachments(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    attachmentCount,
    StructPointerDecoder<Decoded_VkClearAttachment>* pAttachments,
    uint32_t                                    rectCount,
    StructPointerDecoder<Decoded_VkClearRect>*  pRects)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["attachmentCount"], attachmentCount, json_options);
    FieldToJson(args["pAttachments"], pAttachments, json_options);
    FieldToJson(args["rectCount"], rectCount, json_options);
    FieldToJson(args["pRects"], pRects, json_options);
    util::DiveFunctionData function_data("vkCmdClearAttachments", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdResolveImage(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            srcImage,
    VkImageLayout                               srcImageLayout,
    format::HandleId                            dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    StructPointerDecoder<Decoded_VkImageResolve>* pRegions)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["srcImage"], srcImage, json_options);
    FieldToJson(args["srcImageLayout"], srcImageLayout, json_options);
    HandleToJson(args["dstImage"], dstImage, json_options);
    FieldToJson(args["dstImageLayout"], dstImageLayout, json_options);
    FieldToJson(args["regionCount"], regionCount, json_options);
    FieldToJson(args["pRegions"], pRegions, json_options);
    util::DiveFunctionData function_data("vkCmdResolveImage", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetEvent(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    VkPipelineStageFlags                        stageMask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["event"], event, json_options);
    FieldToJson(VkPipelineStageFlags_t(), args["stageMask"], stageMask, json_options);
    util::DiveFunctionData function_data("vkCmdSetEvent", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdResetEvent(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    VkPipelineStageFlags                        stageMask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["event"], event, json_options);
    FieldToJson(VkPipelineStageFlags_t(), args["stageMask"], stageMask, json_options);
    util::DiveFunctionData function_data("vkCmdResetEvent", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdWaitEvents(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    eventCount,
    HandlePointerDecoder<VkEvent>*              pEvents,
    VkPipelineStageFlags                        srcStageMask,
    VkPipelineStageFlags                        dstStageMask,
    uint32_t                                    memoryBarrierCount,
    StructPointerDecoder<Decoded_VkMemoryBarrier>* pMemoryBarriers,
    uint32_t                                    bufferMemoryBarrierCount,
    StructPointerDecoder<Decoded_VkBufferMemoryBarrier>* pBufferMemoryBarriers,
    uint32_t                                    imageMemoryBarrierCount,
    StructPointerDecoder<Decoded_VkImageMemoryBarrier>* pImageMemoryBarriers)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["eventCount"], eventCount, json_options);
    HandleToJson(args["pEvents"], pEvents, json_options);
    FieldToJson(VkPipelineStageFlags_t(), args["srcStageMask"], srcStageMask, json_options);
    FieldToJson(VkPipelineStageFlags_t(), args["dstStageMask"], dstStageMask, json_options);
    FieldToJson(args["memoryBarrierCount"], memoryBarrierCount, json_options);
    FieldToJson(args["pMemoryBarriers"], pMemoryBarriers, json_options);
    FieldToJson(args["bufferMemoryBarrierCount"], bufferMemoryBarrierCount, json_options);
    FieldToJson(args["pBufferMemoryBarriers"], pBufferMemoryBarriers, json_options);
    FieldToJson(args["imageMemoryBarrierCount"], imageMemoryBarrierCount, json_options);
    FieldToJson(args["pImageMemoryBarriers"], pImageMemoryBarriers, json_options);
    util::DiveFunctionData function_data("vkCmdWaitEvents", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdPipelineBarrier(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlags                        srcStageMask,
    VkPipelineStageFlags                        dstStageMask,
    VkDependencyFlags                           dependencyFlags,
    uint32_t                                    memoryBarrierCount,
    StructPointerDecoder<Decoded_VkMemoryBarrier>* pMemoryBarriers,
    uint32_t                                    bufferMemoryBarrierCount,
    StructPointerDecoder<Decoded_VkBufferMemoryBarrier>* pBufferMemoryBarriers,
    uint32_t                                    imageMemoryBarrierCount,
    StructPointerDecoder<Decoded_VkImageMemoryBarrier>* pImageMemoryBarriers)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkPipelineStageFlags_t(), args["srcStageMask"], srcStageMask, json_options);
    FieldToJson(VkPipelineStageFlags_t(), args["dstStageMask"], dstStageMask, json_options);
    FieldToJson(VkDependencyFlags_t(), args["dependencyFlags"], dependencyFlags, json_options);
    FieldToJson(args["memoryBarrierCount"], memoryBarrierCount, json_options);
    FieldToJson(args["pMemoryBarriers"], pMemoryBarriers, json_options);
    FieldToJson(args["bufferMemoryBarrierCount"], bufferMemoryBarrierCount, json_options);
    FieldToJson(args["pBufferMemoryBarriers"], pBufferMemoryBarriers, json_options);
    FieldToJson(args["imageMemoryBarrierCount"], imageMemoryBarrierCount, json_options);
    FieldToJson(args["pImageMemoryBarriers"], pImageMemoryBarriers, json_options);
    util::DiveFunctionData function_data("vkCmdPipelineBarrier", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginQuery(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    query,
    VkQueryControlFlags                         flags)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["query"], query, json_options);
    FieldToJson(VkQueryControlFlags_t(), args["flags"], flags, json_options);
    util::DiveFunctionData function_data("vkCmdBeginQuery", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndQuery(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    query)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["query"], query, json_options);
    util::DiveFunctionData function_data("vkCmdEndQuery", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdResetQueryPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["firstQuery"], firstQuery, json_options);
    FieldToJson(args["queryCount"], queryCount, json_options);
    util::DiveFunctionData function_data("vkCmdResetQueryPool", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdWriteTimestamp(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlagBits                     pipelineStage,
    format::HandleId                            queryPool,
    uint32_t                                    query)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pipelineStage"], pipelineStage, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["query"], query, json_options);
    util::DiveFunctionData function_data("vkCmdWriteTimestamp", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyQueryPoolResults(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount,
    format::HandleId                            dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                stride,
    VkQueryResultFlags                          flags)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["firstQuery"], firstQuery, json_options);
    FieldToJson(args["queryCount"], queryCount, json_options);
    HandleToJson(args["dstBuffer"], dstBuffer, json_options);
    FieldToJson(args["dstOffset"], dstOffset, json_options);
    FieldToJson(args["stride"], stride, json_options);
    FieldToJson(VkQueryResultFlags_t(), args["flags"], flags, json_options);
    util::DiveFunctionData function_data("vkCmdCopyQueryPoolResults", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginRenderPass(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderPassBeginInfo>* pRenderPassBegin,
    VkSubpassContents                           contents)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pRenderPassBegin"], pRenderPassBegin, json_options);
    FieldToJson(args["contents"], contents, json_options);
    util::DiveFunctionData function_data("vkCmdBeginRenderPass", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdNextSubpass(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkSubpassContents                           contents)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["contents"], contents, json_options);
    util::DiveFunctionData function_data("vkCmdNextSubpass", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndRenderPass(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    util::DiveFunctionData function_data("vkCmdEndRenderPass", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdExecuteCommands(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    commandBufferCount,
    HandlePointerDecoder<VkCommandBuffer>*      pCommandBuffers)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["commandBufferCount"], commandBufferCount, json_options);
    HandleToJson(args["pCommandBuffers"], pCommandBuffers, json_options);
    util::DiveFunctionData function_data("vkCmdExecuteCommands", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkBindBufferMemory2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindBufferMemoryInfo>* pBindInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["bindInfoCount"], bindInfoCount, json_options);
    FieldToJson(args["pBindInfos"], pBindInfos, json_options);
    WriteBlockEnd("vkBindBufferMemory2");
}

void VulkanExportDiveConsumer::Process_vkBindImageMemory2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindImageMemoryInfo>* pBindInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["bindInfoCount"], bindInfoCount, json_options);
    FieldToJson(args["pBindInfos"], pBindInfos, json_options);
    WriteBlockEnd("vkBindImageMemory2");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceGroupPeerMemoryFeatures(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    uint32_t                                    heapIndex,
    uint32_t                                    localDeviceIndex,
    uint32_t                                    remoteDeviceIndex,
    PointerDecoder<VkPeerMemoryFeatureFlags>*   pPeerMemoryFeatures)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["heapIndex"], heapIndex, json_options);
    FieldToJson(args["localDeviceIndex"], localDeviceIndex, json_options);
    FieldToJson(args["remoteDeviceIndex"], remoteDeviceIndex, json_options);
    FieldToJson(args["pPeerMemoryFeatures"], pPeerMemoryFeatures, json_options);
    WriteBlockEnd("vkGetDeviceGroupPeerMemoryFeatures");
}

void VulkanExportDiveConsumer::Process_vkCmdSetDeviceMask(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    deviceMask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["deviceMask"], deviceMask, json_options);
    util::DiveFunctionData function_data("vkCmdSetDeviceMask", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDispatchBase(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    baseGroupX,
    uint32_t                                    baseGroupY,
    uint32_t                                    baseGroupZ,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["baseGroupX"], baseGroupX, json_options);
    FieldToJson(args["baseGroupY"], baseGroupY, json_options);
    FieldToJson(args["baseGroupZ"], baseGroupZ, json_options);
    FieldToJson(args["groupCountX"], groupCountX, json_options);
    FieldToJson(args["groupCountY"], groupCountY, json_options);
    FieldToJson(args["groupCountZ"], groupCountZ, json_options);
    util::DiveFunctionData function_data("vkCmdDispatchBase", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkEnumeratePhysicalDeviceGroups(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    PointerDecoder<uint32_t>*                   pPhysicalDeviceGroupCount,
    StructPointerDecoder<Decoded_VkPhysicalDeviceGroupProperties>* pPhysicalDeviceGroupProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pPhysicalDeviceGroupCount"], pPhysicalDeviceGroupCount, json_options);
    FieldToJson(args["pPhysicalDeviceGroupProperties"], pPhysicalDeviceGroupProperties, json_options);
    WriteBlockEnd("vkEnumeratePhysicalDeviceGroups");
}

void VulkanExportDiveConsumer::Process_vkGetImageMemoryRequirements2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageMemoryRequirementsInfo2>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetImageMemoryRequirements2");
}

void VulkanExportDiveConsumer::Process_vkGetBufferMemoryRequirements2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferMemoryRequirementsInfo2>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetBufferMemoryRequirements2");
}

void VulkanExportDiveConsumer::Process_vkGetImageSparseMemoryRequirements2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageSparseMemoryRequirementsInfo2>* pInfo,
    PointerDecoder<uint32_t>*                   pSparseMemoryRequirementCount,
    StructPointerDecoder<Decoded_VkSparseImageMemoryRequirements2>* pSparseMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pSparseMemoryRequirementCount"], pSparseMemoryRequirementCount, json_options);
    FieldToJson(args["pSparseMemoryRequirements"], pSparseMemoryRequirements, json_options);
    WriteBlockEnd("vkGetImageSparseMemoryRequirements2");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFeatures2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceFeatures2>* pFeatures)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pFeatures"], pFeatures, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceFeatures2");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceProperties2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceProperties2>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceProperties2");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFormatProperties2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    VkFormat                                    format,
    StructPointerDecoder<Decoded_VkFormatProperties2>* pFormatProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["format"], format, json_options);
    FieldToJson(args["pFormatProperties"], pFormatProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceFormatProperties2");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceImageFormatProperties2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceImageFormatInfo2>* pImageFormatInfo,
    StructPointerDecoder<Decoded_VkImageFormatProperties2>* pImageFormatProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pImageFormatInfo"], pImageFormatInfo, json_options);
    FieldToJson(args["pImageFormatProperties"], pImageFormatProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceImageFormatProperties2");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceQueueFamilyProperties2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pQueueFamilyPropertyCount,
    StructPointerDecoder<Decoded_VkQueueFamilyProperties2>* pQueueFamilyProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pQueueFamilyPropertyCount"], pQueueFamilyPropertyCount, json_options);
    FieldToJson(args["pQueueFamilyProperties"], pQueueFamilyProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceQueueFamilyProperties2");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceMemoryProperties2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceMemoryProperties2>* pMemoryProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pMemoryProperties"], pMemoryProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceMemoryProperties2");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSparseImageFormatProperties2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSparseImageFormatInfo2>* pFormatInfo,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkSparseImageFormatProperties2>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pFormatInfo"], pFormatInfo, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSparseImageFormatProperties2");
}

void VulkanExportDiveConsumer::Process_vkTrimCommandPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            commandPool,
    VkCommandPoolTrimFlags                      flags)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["commandPool"], commandPool, json_options);
    FieldToJson(VkCommandPoolTrimFlags_t(), args["flags"], flags, json_options);
    WriteBlockEnd("vkTrimCommandPool");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceQueue2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceQueueInfo2>* pQueueInfo,
    HandlePointerDecoder<VkQueue>*              pQueue)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pQueueInfo"], pQueueInfo, json_options);
    HandleToJson(args["pQueue"], pQueue, json_options);
    WriteBlockEnd("vkGetDeviceQueue2");
}

void VulkanExportDiveConsumer::Process_vkCreateSamplerYcbcrConversion(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSamplerYcbcrConversionCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSamplerYcbcrConversion>* pYcbcrConversion)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pYcbcrConversion"], pYcbcrConversion, json_options);
    WriteBlockEnd("vkCreateSamplerYcbcrConversion");
}

void VulkanExportDiveConsumer::Process_vkDestroySamplerYcbcrConversion(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            ycbcrConversion,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["ycbcrConversion"], ycbcrConversion, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroySamplerYcbcrConversion");
}

void VulkanExportDiveConsumer::Process_vkCreateDescriptorUpdateTemplate(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorUpdateTemplateCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorUpdateTemplate>* pDescriptorUpdateTemplate)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pDescriptorUpdateTemplate"], pDescriptorUpdateTemplate, json_options);
    WriteBlockEnd("vkCreateDescriptorUpdateTemplate");
}

void VulkanExportDiveConsumer::Process_vkDestroyDescriptorUpdateTemplate(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            descriptorUpdateTemplate,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["descriptorUpdateTemplate"], descriptorUpdateTemplate, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyDescriptorUpdateTemplate");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalBufferProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalBufferInfo>* pExternalBufferInfo,
    StructPointerDecoder<Decoded_VkExternalBufferProperties>* pExternalBufferProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pExternalBufferInfo"], pExternalBufferInfo, json_options);
    FieldToJson(args["pExternalBufferProperties"], pExternalBufferProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceExternalBufferProperties");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalFenceProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalFenceInfo>* pExternalFenceInfo,
    StructPointerDecoder<Decoded_VkExternalFenceProperties>* pExternalFenceProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pExternalFenceInfo"], pExternalFenceInfo, json_options);
    FieldToJson(args["pExternalFenceProperties"], pExternalFenceProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceExternalFenceProperties");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalSemaphoreProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalSemaphoreInfo>* pExternalSemaphoreInfo,
    StructPointerDecoder<Decoded_VkExternalSemaphoreProperties>* pExternalSemaphoreProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pExternalSemaphoreInfo"], pExternalSemaphoreInfo, json_options);
    FieldToJson(args["pExternalSemaphoreProperties"], pExternalSemaphoreProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceExternalSemaphoreProperties");
}

void VulkanExportDiveConsumer::Process_vkGetDescriptorSetLayoutSupport(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutSupport>* pSupport)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pSupport"], pSupport, json_options);
    WriteBlockEnd("vkGetDescriptorSetLayoutSupport");
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndirectCount(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    format::HandleId                            countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    HandleToJson(args["countBuffer"], countBuffer, json_options);
    FieldToJson(args["countBufferOffset"], countBufferOffset, json_options);
    FieldToJson(args["maxDrawCount"], maxDrawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawIndirectCount", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndexedIndirectCount(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    format::HandleId                            countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    HandleToJson(args["countBuffer"], countBuffer, json_options);
    FieldToJson(args["countBufferOffset"], countBufferOffset, json_options);
    FieldToJson(args["maxDrawCount"], maxDrawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawIndexedIndirectCount", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCreateRenderPass2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderPassCreateInfo2>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkRenderPass>*         pRenderPass)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pRenderPass"], pRenderPass, json_options);
    WriteBlockEnd("vkCreateRenderPass2");
}

void VulkanExportDiveConsumer::Process_vkCmdBeginRenderPass2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderPassBeginInfo>* pRenderPassBegin,
    StructPointerDecoder<Decoded_VkSubpassBeginInfo>* pSubpassBeginInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pRenderPassBegin"], pRenderPassBegin, json_options);
    FieldToJson(args["pSubpassBeginInfo"], pSubpassBeginInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBeginRenderPass2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdNextSubpass2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSubpassBeginInfo>* pSubpassBeginInfo,
    StructPointerDecoder<Decoded_VkSubpassEndInfo>* pSubpassEndInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pSubpassBeginInfo"], pSubpassBeginInfo, json_options);
    FieldToJson(args["pSubpassEndInfo"], pSubpassEndInfo, json_options);
    util::DiveFunctionData function_data("vkCmdNextSubpass2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndRenderPass2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSubpassEndInfo>* pSubpassEndInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pSubpassEndInfo"], pSubpassEndInfo, json_options);
    util::DiveFunctionData function_data("vkCmdEndRenderPass2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkResetQueryPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["firstQuery"], firstQuery, json_options);
    FieldToJson(args["queryCount"], queryCount, json_options);
    WriteBlockEnd("vkResetQueryPool");
}

void VulkanExportDiveConsumer::Process_vkGetSemaphoreCounterValue(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            semaphore,
    PointerDecoder<uint64_t>*                   pValue)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["semaphore"], semaphore, json_options);
    FieldToJson(args["pValue"], pValue, json_options);
    WriteBlockEnd("vkGetSemaphoreCounterValue");
}

void VulkanExportDiveConsumer::Process_vkWaitSemaphores(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
    uint64_t                                    timeout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pWaitInfo"], pWaitInfo, json_options);
    FieldToJson(args["timeout"], timeout, json_options);
    WriteBlockEnd("vkWaitSemaphores");
}

void VulkanExportDiveConsumer::Process_vkSignalSemaphore(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pSignalInfo"], pSignalInfo, json_options);
    WriteBlockEnd("vkSignalSemaphore");
}

void VulkanExportDiveConsumer::Process_vkGetBufferDeviceAddress(
    const ApiCallInfo&                          call_info,
    VkDeviceAddress                             returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferDeviceAddressInfo>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetBufferDeviceAddress");
}

void VulkanExportDiveConsumer::Process_vkGetBufferOpaqueCaptureAddress(
    const ApiCallInfo&                          call_info,
    uint64_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferDeviceAddressInfo>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetBufferOpaqueCaptureAddress");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceMemoryOpaqueCaptureAddress(
    const ApiCallInfo&                          call_info,
    uint64_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceMemoryOpaqueCaptureAddressInfo>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetDeviceMemoryOpaqueCaptureAddress");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceToolProperties(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pToolCount,
    StructPointerDecoder<Decoded_VkPhysicalDeviceToolProperties>* pToolProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pToolCount"], pToolCount, json_options);
    FieldToJson(args["pToolProperties"], pToolProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceToolProperties");
}

void VulkanExportDiveConsumer::Process_vkCreatePrivateDataSlot(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPrivateDataSlotCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPrivateDataSlot>*    pPrivateDataSlot)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pPrivateDataSlot"], pPrivateDataSlot, json_options);
    WriteBlockEnd("vkCreatePrivateDataSlot");
}

void VulkanExportDiveConsumer::Process_vkDestroyPrivateDataSlot(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            privateDataSlot,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["privateDataSlot"], privateDataSlot, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyPrivateDataSlot");
}

void VulkanExportDiveConsumer::Process_vkSetPrivateData(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    format::HandleId                            privateDataSlot,
    uint64_t                                    data)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["objectType"], objectType, json_options);
    HandleToJson(args["objectHandle"], objectHandle, json_options);
    HandleToJson(args["privateDataSlot"], privateDataSlot, json_options);
    FieldToJson(args["data"], data, json_options);
    WriteBlockEnd("vkSetPrivateData");
}

void VulkanExportDiveConsumer::Process_vkGetPrivateData(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    format::HandleId                            privateDataSlot,
    PointerDecoder<uint64_t>*                   pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["objectType"], objectType, json_options);
    HandleToJson(args["objectHandle"], objectHandle, json_options);
    HandleToJson(args["privateDataSlot"], privateDataSlot, json_options);
    FieldToJson(args["pData"], pData, json_options);
    WriteBlockEnd("vkGetPrivateData");
}

void VulkanExportDiveConsumer::Process_vkCmdSetEvent2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["event"], event, json_options);
    FieldToJson(args["pDependencyInfo"], pDependencyInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetEvent2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdResetEvent2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    VkPipelineStageFlags2                       stageMask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["event"], event, json_options);
    FieldToJson(VkPipelineStageFlags2_t(), args["stageMask"], stageMask, json_options);
    util::DiveFunctionData function_data("vkCmdResetEvent2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdWaitEvents2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    eventCount,
    HandlePointerDecoder<VkEvent>*              pEvents,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["eventCount"], eventCount, json_options);
    HandleToJson(args["pEvents"], pEvents, json_options);
    FieldToJson(args["pDependencyInfos"], pDependencyInfos, json_options);
    util::DiveFunctionData function_data("vkCmdWaitEvents2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdPipelineBarrier2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pDependencyInfo"], pDependencyInfo, json_options);
    util::DiveFunctionData function_data("vkCmdPipelineBarrier2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdWriteTimestamp2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlags2                       stage,
    format::HandleId                            queryPool,
    uint32_t                                    query)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkPipelineStageFlags2_t(), args["stage"], stage, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["query"], query, json_options);
    util::DiveFunctionData function_data("vkCmdWriteTimestamp2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkQueueSubmit2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    uint32_t                                    submitCount,
    StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
    format::HandleId                            fence)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    FieldToJson(args["submitCount"], submitCount, json_options);
    FieldToJson(args["pSubmits"], pSubmits, json_options);
    HandleToJson(args["fence"], fence, json_options);
    WriteBlockEnd("vkQueueSubmit2");
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBuffer2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferInfo2>* pCopyBufferInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pCopyBufferInfo"], pCopyBufferInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyBuffer2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyImage2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageInfo2>* pCopyImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pCopyImageInfo"], pCopyImageInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyImage2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBufferToImage2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferToImageInfo2>* pCopyBufferToImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pCopyBufferToImageInfo"], pCopyBufferToImageInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyBufferToImage2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyImageToBuffer2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageToBufferInfo2>* pCopyImageToBufferInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pCopyImageToBufferInfo"], pCopyImageToBufferInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyImageToBuffer2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBlitImage2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBlitImageInfo2>* pBlitImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pBlitImageInfo"], pBlitImageInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBlitImage2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdResolveImage2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkResolveImageInfo2>* pResolveImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pResolveImageInfo"], pResolveImageInfo, json_options);
    util::DiveFunctionData function_data("vkCmdResolveImage2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginRendering(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInfo>* pRenderingInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pRenderingInfo"], pRenderingInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBeginRendering", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndRendering(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    util::DiveFunctionData function_data("vkCmdEndRendering", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCullMode(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCullModeFlags                             cullMode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkCullModeFlags_t(), args["cullMode"], cullMode, json_options);
    util::DiveFunctionData function_data("vkCmdSetCullMode", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetFrontFace(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkFrontFace                                 frontFace)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["frontFace"], frontFace, json_options);
    util::DiveFunctionData function_data("vkCmdSetFrontFace", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPrimitiveTopology(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPrimitiveTopology                         primitiveTopology)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["primitiveTopology"], primitiveTopology, json_options);
    util::DiveFunctionData function_data("vkCmdSetPrimitiveTopology", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportWithCount(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkViewport>*   pViewports)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["viewportCount"], viewportCount, json_options);
    FieldToJson(args["pViewports"], pViewports, json_options);
    util::DiveFunctionData function_data("vkCmdSetViewportWithCount", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetScissorWithCount(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    scissorCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pScissors)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["scissorCount"], scissorCount, json_options);
    FieldToJson(args["pScissors"], pScissors, json_options);
    util::DiveFunctionData function_data("vkCmdSetScissorWithCount", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBindVertexBuffers2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    HandlePointerDecoder<VkBuffer>*             pBuffers,
    PointerDecoder<VkDeviceSize>*               pOffsets,
    PointerDecoder<VkDeviceSize>*               pSizes,
    PointerDecoder<VkDeviceSize>*               pStrides)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstBinding"], firstBinding, json_options);
    FieldToJson(args["bindingCount"], bindingCount, json_options);
    HandleToJson(args["pBuffers"], pBuffers, json_options);
    FieldToJson(args["pOffsets"], pOffsets, json_options);
    FieldToJson(args["pSizes"], pSizes, json_options);
    FieldToJson(args["pStrides"], pStrides, json_options);
    util::DiveFunctionData function_data("vkCmdBindVertexBuffers2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthTestEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthTestEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["depthTestEnable"], depthTestEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthTestEnable", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthWriteEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthWriteEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["depthWriteEnable"], depthWriteEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthWriteEnable", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthCompareOp(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCompareOp                                 depthCompareOp)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["depthCompareOp"], depthCompareOp, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthCompareOp", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBoundsTestEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthBoundsTestEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["depthBoundsTestEnable"], depthBoundsTestEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthBoundsTestEnable", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilTestEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    stencilTestEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["stencilTestEnable"], stencilTestEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetStencilTestEnable", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilOp(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkStencilFaceFlags                          faceMask,
    VkStencilOp                                 failOp,
    VkStencilOp                                 passOp,
    VkStencilOp                                 depthFailOp,
    VkCompareOp                                 compareOp)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkStencilFaceFlags_t(), args["faceMask"], faceMask, json_options);
    FieldToJson(args["failOp"], failOp, json_options);
    FieldToJson(args["passOp"], passOp, json_options);
    FieldToJson(args["depthFailOp"], depthFailOp, json_options);
    FieldToJson(args["compareOp"], compareOp, json_options);
    util::DiveFunctionData function_data("vkCmdSetStencilOp", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRasterizerDiscardEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    rasterizerDiscardEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["rasterizerDiscardEnable"], rasterizerDiscardEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetRasterizerDiscardEnable", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBiasEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthBiasEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["depthBiasEnable"], depthBiasEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthBiasEnable", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPrimitiveRestartEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    primitiveRestartEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["primitiveRestartEnable"], primitiveRestartEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetPrimitiveRestartEnable", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceBufferMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceBufferMemoryRequirements>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetDeviceBufferMemoryRequirements");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageMemoryRequirements>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetDeviceImageMemoryRequirements");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageSparseMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageMemoryRequirements>* pInfo,
    PointerDecoder<uint32_t>*                   pSparseMemoryRequirementCount,
    StructPointerDecoder<Decoded_VkSparseImageMemoryRequirements2>* pSparseMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pSparseMemoryRequirementCount"], pSparseMemoryRequirementCount, json_options);
    FieldToJson(args["pSparseMemoryRequirements"], pSparseMemoryRequirements, json_options);
    WriteBlockEnd("vkGetDeviceImageSparseMemoryRequirements");
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineStipple(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["lineStippleFactor"], lineStippleFactor, json_options);
    FieldToJson(args["lineStipplePattern"], lineStipplePattern, json_options);
    util::DiveFunctionData function_data("vkCmdSetLineStipple", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkMapMemory2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryMapInfo>* pMemoryMapInfo,
    PointerDecoder<uint64_t, void*>*            ppData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pMemoryMapInfo"], pMemoryMapInfo, json_options);
    FieldToJsonAsHex(args["ppData"], ppData, json_options);
    WriteBlockEnd("vkMapMemory2");
}

void VulkanExportDiveConsumer::Process_vkUnmapMemory2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryUnmapInfo>* pMemoryUnmapInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pMemoryUnmapInfo"], pMemoryUnmapInfo, json_options);
    WriteBlockEnd("vkUnmapMemory2");
}

void VulkanExportDiveConsumer::Process_vkCmdBindIndexBuffer2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkIndexType                                 indexType)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    FieldToJson(args["size"], size, json_options);
    FieldToJson(args["indexType"], indexType, json_options);
    util::DiveFunctionData function_data("vkCmdBindIndexBuffer2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetRenderingAreaGranularity(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderingAreaInfo>* pRenderingAreaInfo,
    StructPointerDecoder<Decoded_VkExtent2D>*   pGranularity)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pRenderingAreaInfo"], pRenderingAreaInfo, json_options);
    FieldToJson(args["pGranularity"], pGranularity, json_options);
    WriteBlockEnd("vkGetRenderingAreaGranularity");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageSubresourceLayout(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageSubresourceInfo>* pInfo,
    StructPointerDecoder<Decoded_VkSubresourceLayout2>* pLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pLayout"], pLayout, json_options);
    WriteBlockEnd("vkGetDeviceImageSubresourceLayout");
}

void VulkanExportDiveConsumer::Process_vkGetImageSubresourceLayout2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkImageSubresource2>* pSubresource,
    StructPointerDecoder<Decoded_VkSubresourceLayout2>* pLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["image"], image, json_options);
    FieldToJson(args["pSubresource"], pSubresource, json_options);
    FieldToJson(args["pLayout"], pLayout, json_options);
    WriteBlockEnd("vkGetImageSubresourceLayout2");
}

void VulkanExportDiveConsumer::Process_vkCmdPushDescriptorSet(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    format::HandleId                            layout,
    uint32_t                                    set,
    uint32_t                                    descriptorWriteCount,
    StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pipelineBindPoint"], pipelineBindPoint, json_options);
    HandleToJson(args["layout"], layout, json_options);
    FieldToJson(args["set"], set, json_options);
    FieldToJson(args["descriptorWriteCount"], descriptorWriteCount, json_options);
    FieldToJson(args["pDescriptorWrites"], pDescriptorWrites, json_options);
    util::DiveFunctionData function_data("vkCmdPushDescriptorSet", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRenderingAttachmentLocations(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingAttachmentLocationInfo>* pLocationInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pLocationInfo"], pLocationInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetRenderingAttachmentLocations", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRenderingInputAttachmentIndices(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInputAttachmentIndexInfo>* pInputAttachmentIndexInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pInputAttachmentIndexInfo"], pInputAttachmentIndexInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetRenderingInputAttachmentIndices", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBindDescriptorSets2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBindDescriptorSetsInfo>* pBindDescriptorSetsInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pBindDescriptorSetsInfo"], pBindDescriptorSetsInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBindDescriptorSets2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdPushConstants2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPushConstantsInfo>* pPushConstantsInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pPushConstantsInfo"], pPushConstantsInfo, json_options);
    util::DiveFunctionData function_data("vkCmdPushConstants2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdPushDescriptorSet2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPushDescriptorSetInfo>* pPushDescriptorSetInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pPushDescriptorSetInfo"], pPushDescriptorSetInfo, json_options);
    util::DiveFunctionData function_data("vkCmdPushDescriptorSet2", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCopyMemoryToImage(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyMemoryToImageInfo>* pCopyMemoryToImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCopyMemoryToImageInfo"], pCopyMemoryToImageInfo, json_options);
    WriteBlockEnd("vkCopyMemoryToImage");
}

void VulkanExportDiveConsumer::Process_vkCopyImageToMemory(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyImageToMemoryInfo>* pCopyImageToMemoryInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCopyImageToMemoryInfo"], pCopyImageToMemoryInfo, json_options);
    WriteBlockEnd("vkCopyImageToMemory");
}

void VulkanExportDiveConsumer::Process_vkCopyImageToImage(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyImageToImageInfo>* pCopyImageToImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCopyImageToImageInfo"], pCopyImageToImageInfo, json_options);
    WriteBlockEnd("vkCopyImageToImage");
}

void VulkanExportDiveConsumer::Process_vkTransitionImageLayout(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    transitionCount,
    StructPointerDecoder<Decoded_VkHostImageLayoutTransitionInfo>* pTransitions)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["transitionCount"], transitionCount, json_options);
    FieldToJson(args["pTransitions"], pTransitions, json_options);
    WriteBlockEnd("vkTransitionImageLayout");
}

void VulkanExportDiveConsumer::Process_vkDestroySurfaceKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    format::HandleId                            surface,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    HandleToJson(args["surface"], surface, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroySurfaceKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceSupportKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    format::HandleId                            surface,
    PointerDecoder<VkBool32>*                   pSupported)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["queueFamilyIndex"], queueFamilyIndex, json_options);
    HandleToJson(args["surface"], surface, json_options);
    Bool32ToJson(args["pSupported"], pSupported, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSurfaceSupportKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            surface,
    StructPointerDecoder<Decoded_VkSurfaceCapabilitiesKHR>* pSurfaceCapabilities)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["surface"], surface, json_options);
    FieldToJson(args["pSurfaceCapabilities"], pSurfaceCapabilities, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceFormatsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            surface,
    PointerDecoder<uint32_t>*                   pSurfaceFormatCount,
    StructPointerDecoder<Decoded_VkSurfaceFormatKHR>* pSurfaceFormats)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["surface"], surface, json_options);
    FieldToJson(args["pSurfaceFormatCount"], pSurfaceFormatCount, json_options);
    FieldToJson(args["pSurfaceFormats"], pSurfaceFormats, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSurfaceFormatsKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfacePresentModesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            surface,
    PointerDecoder<uint32_t>*                   pPresentModeCount,
    PointerDecoder<VkPresentModeKHR>*           pPresentModes)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["surface"], surface, json_options);
    FieldToJson(args["pPresentModeCount"], pPresentModeCount, json_options);
    FieldToJson(args["pPresentModes"], pPresentModes, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSurfacePresentModesKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateSwapchainKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSwapchainCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSwapchainKHR>*       pSwapchain)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSwapchain"], pSwapchain, json_options);
    WriteBlockEnd("vkCreateSwapchainKHR");
}

void VulkanExportDiveConsumer::Process_vkDestroySwapchainKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroySwapchainKHR");
}

void VulkanExportDiveConsumer::Process_vkGetSwapchainImagesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    PointerDecoder<uint32_t>*                   pSwapchainImageCount,
    HandlePointerDecoder<VkImage>*              pSwapchainImages)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["pSwapchainImageCount"], pSwapchainImageCount, json_options);
    HandleToJson(args["pSwapchainImages"], pSwapchainImages, json_options);
    WriteBlockEnd("vkGetSwapchainImagesKHR");
}

void VulkanExportDiveConsumer::Process_vkAcquireNextImageKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    uint64_t                                    timeout,
    format::HandleId                            semaphore,
    format::HandleId                            fence,
    PointerDecoder<uint32_t>*                   pImageIndex)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["timeout"], timeout, json_options);
    HandleToJson(args["semaphore"], semaphore, json_options);
    HandleToJson(args["fence"], fence, json_options);
    FieldToJson(args["pImageIndex"], pImageIndex, json_options);
    WriteBlockEnd("vkAcquireNextImageKHR");
}

void VulkanExportDiveConsumer::Process_vkQueuePresentKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    StructPointerDecoder<Decoded_VkPresentInfoKHR>* pPresentInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    FieldToJson(args["pPresentInfo"], pPresentInfo, json_options);
    WriteBlockEnd("vkQueuePresentKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceGroupPresentCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceGroupPresentCapabilitiesKHR>* pDeviceGroupPresentCapabilities)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pDeviceGroupPresentCapabilities"], pDeviceGroupPresentCapabilities, json_options);
    WriteBlockEnd("vkGetDeviceGroupPresentCapabilitiesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceGroupSurfacePresentModesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            surface,
    PointerDecoder<VkDeviceGroupPresentModeFlagsKHR>* pModes)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["surface"], surface, json_options);
    FieldToJson(args["pModes"], pModes, json_options);
    WriteBlockEnd("vkGetDeviceGroupSurfacePresentModesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDevicePresentRectanglesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            surface,
    PointerDecoder<uint32_t>*                   pRectCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pRects)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["surface"], surface, json_options);
    FieldToJson(args["pRectCount"], pRectCount, json_options);
    FieldToJson(args["pRects"], pRects, json_options);
    WriteBlockEnd("vkGetPhysicalDevicePresentRectanglesKHR");
}

void VulkanExportDiveConsumer::Process_vkAcquireNextImage2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAcquireNextImageInfoKHR>* pAcquireInfo,
    PointerDecoder<uint32_t>*                   pImageIndex)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pAcquireInfo"], pAcquireInfo, json_options);
    FieldToJson(args["pImageIndex"], pImageIndex, json_options);
    WriteBlockEnd("vkAcquireNextImage2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceDisplayPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayPropertiesKHR>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceDisplayPropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayPlanePropertiesKHR>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDisplayPlaneSupportedDisplaysKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    planeIndex,
    PointerDecoder<uint32_t>*                   pDisplayCount,
    HandlePointerDecoder<VkDisplayKHR>*         pDisplays)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["planeIndex"], planeIndex, json_options);
    FieldToJson(args["pDisplayCount"], pDisplayCount, json_options);
    HandleToJson(args["pDisplays"], pDisplays, json_options);
    WriteBlockEnd("vkGetDisplayPlaneSupportedDisplaysKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDisplayModePropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            display,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayModePropertiesKHR>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["display"], display, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetDisplayModePropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateDisplayModeKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            display,
    StructPointerDecoder<Decoded_VkDisplayModeCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDisplayModeKHR>*     pMode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["display"], display, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pMode"], pMode, json_options);
    WriteBlockEnd("vkCreateDisplayModeKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDisplayPlaneCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            mode,
    uint32_t                                    planeIndex,
    StructPointerDecoder<Decoded_VkDisplayPlaneCapabilitiesKHR>* pCapabilities)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["mode"], mode, json_options);
    FieldToJson(args["planeIndex"], planeIndex, json_options);
    FieldToJson(args["pCapabilities"], pCapabilities, json_options);
    WriteBlockEnd("vkGetDisplayPlaneCapabilitiesKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateDisplayPlaneSurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkDisplaySurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateDisplayPlaneSurfaceKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateSharedSwapchainsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    swapchainCount,
    StructPointerDecoder<Decoded_VkSwapchainCreateInfoKHR>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSwapchainKHR>*       pSwapchains)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["swapchainCount"], swapchainCount, json_options);
    FieldToJson(args["pCreateInfos"], pCreateInfos, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSwapchains"], pSwapchains, json_options);
    WriteBlockEnd("vkCreateSharedSwapchainsKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateXlibSurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkXlibSurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateXlibSurfaceKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceXlibPresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint64_t                                    dpy,
    size_t                                      visualID)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["queueFamilyIndex"], queueFamilyIndex, json_options);
    FieldToJson(args["dpy"], dpy, json_options);
    FieldToJson(args["visualID"], visualID, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceXlibPresentationSupportKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateXcbSurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkXcbSurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateXcbSurfaceKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceXcbPresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint64_t                                    connection,
    uint32_t                                    visual_id)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["queueFamilyIndex"], queueFamilyIndex, json_options);
    FieldToJson(args["connection"], connection, json_options);
    FieldToJson(args["visual_id"], visual_id, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceXcbPresentationSupportKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateWaylandSurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkWaylandSurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateWaylandSurfaceKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint64_t                                    display)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["queueFamilyIndex"], queueFamilyIndex, json_options);
    FieldToJson(args["display"], display, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceWaylandPresentationSupportKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateAndroidSurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkAndroidSurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateAndroidSurfaceKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateWin32SurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkWin32SurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateWin32SurfaceKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceWin32PresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["queueFamilyIndex"], queueFamilyIndex, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceWin32PresentationSupportKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceVideoCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkVideoProfileInfoKHR>* pVideoProfile,
    StructPointerDecoder<Decoded_VkVideoCapabilitiesKHR>* pCapabilities)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pVideoProfile"], pVideoProfile, json_options);
    FieldToJson(args["pCapabilities"], pCapabilities, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceVideoCapabilitiesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceVideoFormatPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceVideoFormatInfoKHR>* pVideoFormatInfo,
    PointerDecoder<uint32_t>*                   pVideoFormatPropertyCount,
    StructPointerDecoder<Decoded_VkVideoFormatPropertiesKHR>* pVideoFormatProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pVideoFormatInfo"], pVideoFormatInfo, json_options);
    FieldToJson(args["pVideoFormatPropertyCount"], pVideoFormatPropertyCount, json_options);
    FieldToJson(args["pVideoFormatProperties"], pVideoFormatProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceVideoFormatPropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateVideoSessionKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkVideoSessionCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkVideoSessionKHR>*    pVideoSession)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pVideoSession"], pVideoSession, json_options);
    WriteBlockEnd("vkCreateVideoSessionKHR");
}

void VulkanExportDiveConsumer::Process_vkDestroyVideoSessionKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            videoSession,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["videoSession"], videoSession, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyVideoSessionKHR");
}

void VulkanExportDiveConsumer::Process_vkGetVideoSessionMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            videoSession,
    PointerDecoder<uint32_t>*                   pMemoryRequirementsCount,
    StructPointerDecoder<Decoded_VkVideoSessionMemoryRequirementsKHR>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["videoSession"], videoSession, json_options);
    FieldToJson(args["pMemoryRequirementsCount"], pMemoryRequirementsCount, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetVideoSessionMemoryRequirementsKHR");
}

void VulkanExportDiveConsumer::Process_vkBindVideoSessionMemoryKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            videoSession,
    uint32_t                                    bindSessionMemoryInfoCount,
    StructPointerDecoder<Decoded_VkBindVideoSessionMemoryInfoKHR>* pBindSessionMemoryInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["videoSession"], videoSession, json_options);
    FieldToJson(args["bindSessionMemoryInfoCount"], bindSessionMemoryInfoCount, json_options);
    FieldToJson(args["pBindSessionMemoryInfos"], pBindSessionMemoryInfos, json_options);
    WriteBlockEnd("vkBindVideoSessionMemoryKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkVideoSessionParametersCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkVideoSessionParametersKHR>* pVideoSessionParameters)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pVideoSessionParameters"], pVideoSessionParameters, json_options);
    WriteBlockEnd("vkCreateVideoSessionParametersKHR");
}

void VulkanExportDiveConsumer::Process_vkUpdateVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            videoSessionParameters,
    StructPointerDecoder<Decoded_VkVideoSessionParametersUpdateInfoKHR>* pUpdateInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["videoSessionParameters"], videoSessionParameters, json_options);
    FieldToJson(args["pUpdateInfo"], pUpdateInfo, json_options);
    WriteBlockEnd("vkUpdateVideoSessionParametersKHR");
}

void VulkanExportDiveConsumer::Process_vkDestroyVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            videoSessionParameters,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["videoSessionParameters"], videoSessionParameters, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyVideoSessionParametersKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdBeginVideoCodingKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkVideoBeginCodingInfoKHR>* pBeginInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pBeginInfo"], pBeginInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBeginVideoCodingKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndVideoCodingKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkVideoEndCodingInfoKHR>* pEndCodingInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pEndCodingInfo"], pEndCodingInfo, json_options);
    util::DiveFunctionData function_data("vkCmdEndVideoCodingKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdControlVideoCodingKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkVideoCodingControlInfoKHR>* pCodingControlInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pCodingControlInfo"], pCodingControlInfo, json_options);
    util::DiveFunctionData function_data("vkCmdControlVideoCodingKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDecodeVideoKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkVideoDecodeInfoKHR>* pDecodeInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pDecodeInfo"], pDecodeInfo, json_options);
    util::DiveFunctionData function_data("vkCmdDecodeVideoKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginRenderingKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInfo>* pRenderingInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pRenderingInfo"], pRenderingInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBeginRenderingKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndRenderingKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    util::DiveFunctionData function_data("vkCmdEndRenderingKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFeatures2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceFeatures2>* pFeatures)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pFeatures"], pFeatures, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceFeatures2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceProperties2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceProperties2>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceProperties2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFormatProperties2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    VkFormat                                    format,
    StructPointerDecoder<Decoded_VkFormatProperties2>* pFormatProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["format"], format, json_options);
    FieldToJson(args["pFormatProperties"], pFormatProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceFormatProperties2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceImageFormatProperties2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceImageFormatInfo2>* pImageFormatInfo,
    StructPointerDecoder<Decoded_VkImageFormatProperties2>* pImageFormatProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pImageFormatInfo"], pImageFormatInfo, json_options);
    FieldToJson(args["pImageFormatProperties"], pImageFormatProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceImageFormatProperties2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceQueueFamilyProperties2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pQueueFamilyPropertyCount,
    StructPointerDecoder<Decoded_VkQueueFamilyProperties2>* pQueueFamilyProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pQueueFamilyPropertyCount"], pQueueFamilyPropertyCount, json_options);
    FieldToJson(args["pQueueFamilyProperties"], pQueueFamilyProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceQueueFamilyProperties2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceMemoryProperties2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceMemoryProperties2>* pMemoryProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pMemoryProperties"], pMemoryProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceMemoryProperties2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSparseImageFormatInfo2>* pFormatInfo,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkSparseImageFormatProperties2>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pFormatInfo"], pFormatInfo, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSparseImageFormatProperties2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceGroupPeerMemoryFeaturesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    uint32_t                                    heapIndex,
    uint32_t                                    localDeviceIndex,
    uint32_t                                    remoteDeviceIndex,
    PointerDecoder<VkPeerMemoryFeatureFlags>*   pPeerMemoryFeatures)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["heapIndex"], heapIndex, json_options);
    FieldToJson(args["localDeviceIndex"], localDeviceIndex, json_options);
    FieldToJson(args["remoteDeviceIndex"], remoteDeviceIndex, json_options);
    FieldToJson(args["pPeerMemoryFeatures"], pPeerMemoryFeatures, json_options);
    WriteBlockEnd("vkGetDeviceGroupPeerMemoryFeaturesKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdSetDeviceMaskKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    deviceMask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["deviceMask"], deviceMask, json_options);
    util::DiveFunctionData function_data("vkCmdSetDeviceMaskKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDispatchBaseKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    baseGroupX,
    uint32_t                                    baseGroupY,
    uint32_t                                    baseGroupZ,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["baseGroupX"], baseGroupX, json_options);
    FieldToJson(args["baseGroupY"], baseGroupY, json_options);
    FieldToJson(args["baseGroupZ"], baseGroupZ, json_options);
    FieldToJson(args["groupCountX"], groupCountX, json_options);
    FieldToJson(args["groupCountY"], groupCountY, json_options);
    FieldToJson(args["groupCountZ"], groupCountZ, json_options);
    util::DiveFunctionData function_data("vkCmdDispatchBaseKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkTrimCommandPoolKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            commandPool,
    VkCommandPoolTrimFlags                      flags)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["commandPool"], commandPool, json_options);
    FieldToJson(VkCommandPoolTrimFlags_t(), args["flags"], flags, json_options);
    WriteBlockEnd("vkTrimCommandPoolKHR");
}

void VulkanExportDiveConsumer::Process_vkEnumeratePhysicalDeviceGroupsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    PointerDecoder<uint32_t>*                   pPhysicalDeviceGroupCount,
    StructPointerDecoder<Decoded_VkPhysicalDeviceGroupProperties>* pPhysicalDeviceGroupProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pPhysicalDeviceGroupCount"], pPhysicalDeviceGroupCount, json_options);
    FieldToJson(args["pPhysicalDeviceGroupProperties"], pPhysicalDeviceGroupProperties, json_options);
    WriteBlockEnd("vkEnumeratePhysicalDeviceGroupsKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalBufferPropertiesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalBufferInfo>* pExternalBufferInfo,
    StructPointerDecoder<Decoded_VkExternalBufferProperties>* pExternalBufferProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pExternalBufferInfo"], pExternalBufferInfo, json_options);
    FieldToJson(args["pExternalBufferProperties"], pExternalBufferProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceExternalBufferPropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetMemoryWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetWin32HandleInfoKHR>* pGetWin32HandleInfo,
    PointerDecoder<uint64_t, void*>*            pHandle)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pGetWin32HandleInfo"], pGetWin32HandleInfo, json_options);
    FieldToJson(args["pHandle"], pHandle, json_options);
    WriteBlockEnd("vkGetMemoryWin32HandleKHR");
}

void VulkanExportDiveConsumer::Process_vkGetMemoryWin32HandlePropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    uint64_t                                    handle,
    StructPointerDecoder<Decoded_VkMemoryWin32HandlePropertiesKHR>* pMemoryWin32HandleProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["handleType"], handleType, json_options);
    FieldToJson(args["handle"], handle, json_options);
    FieldToJson(args["pMemoryWin32HandleProperties"], pMemoryWin32HandleProperties, json_options);
    WriteBlockEnd("vkGetMemoryWin32HandlePropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetMemoryFdKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetFdInfoKHR>* pGetFdInfo,
    PointerDecoder<int>*                        pFd)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pGetFdInfo"], pGetFdInfo, json_options);
    FieldToJson(args["pFd"], pFd, json_options);
    WriteBlockEnd("vkGetMemoryFdKHR");
}

void VulkanExportDiveConsumer::Process_vkGetMemoryFdPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    int                                         fd,
    StructPointerDecoder<Decoded_VkMemoryFdPropertiesKHR>* pMemoryFdProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["handleType"], handleType, json_options);
    FieldToJson(args["fd"], fd, json_options);
    FieldToJson(args["pMemoryFdProperties"], pMemoryFdProperties, json_options);
    WriteBlockEnd("vkGetMemoryFdPropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalSemaphoreInfo>* pExternalSemaphoreInfo,
    StructPointerDecoder<Decoded_VkExternalSemaphoreProperties>* pExternalSemaphoreProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pExternalSemaphoreInfo"], pExternalSemaphoreInfo, json_options);
    FieldToJson(args["pExternalSemaphoreProperties"], pExternalSemaphoreProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceExternalSemaphorePropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkImportSemaphoreWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImportSemaphoreWin32HandleInfoKHR>* pImportSemaphoreWin32HandleInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pImportSemaphoreWin32HandleInfo"], pImportSemaphoreWin32HandleInfo, json_options);
    WriteBlockEnd("vkImportSemaphoreWin32HandleKHR");
}

void VulkanExportDiveConsumer::Process_vkGetSemaphoreWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreGetWin32HandleInfoKHR>* pGetWin32HandleInfo,
    PointerDecoder<uint64_t, void*>*            pHandle)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pGetWin32HandleInfo"], pGetWin32HandleInfo, json_options);
    FieldToJson(args["pHandle"], pHandle, json_options);
    WriteBlockEnd("vkGetSemaphoreWin32HandleKHR");
}

void VulkanExportDiveConsumer::Process_vkImportSemaphoreFdKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImportSemaphoreFdInfoKHR>* pImportSemaphoreFdInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pImportSemaphoreFdInfo"], pImportSemaphoreFdInfo, json_options);
    WriteBlockEnd("vkImportSemaphoreFdKHR");
}

void VulkanExportDiveConsumer::Process_vkGetSemaphoreFdKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreGetFdInfoKHR>* pGetFdInfo,
    PointerDecoder<int>*                        pFd)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pGetFdInfo"], pGetFdInfo, json_options);
    FieldToJson(args["pFd"], pFd, json_options);
    WriteBlockEnd("vkGetSemaphoreFdKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdPushDescriptorSetKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    format::HandleId                            layout,
    uint32_t                                    set,
    uint32_t                                    descriptorWriteCount,
    StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pipelineBindPoint"], pipelineBindPoint, json_options);
    HandleToJson(args["layout"], layout, json_options);
    FieldToJson(args["set"], set, json_options);
    FieldToJson(args["descriptorWriteCount"], descriptorWriteCount, json_options);
    FieldToJson(args["pDescriptorWrites"], pDescriptorWrites, json_options);
    util::DiveFunctionData function_data("vkCmdPushDescriptorSetKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCreateDescriptorUpdateTemplateKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorUpdateTemplateCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorUpdateTemplate>* pDescriptorUpdateTemplate)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pDescriptorUpdateTemplate"], pDescriptorUpdateTemplate, json_options);
    WriteBlockEnd("vkCreateDescriptorUpdateTemplateKHR");
}

void VulkanExportDiveConsumer::Process_vkDestroyDescriptorUpdateTemplateKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            descriptorUpdateTemplate,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["descriptorUpdateTemplate"], descriptorUpdateTemplate, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyDescriptorUpdateTemplateKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateRenderPass2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderPassCreateInfo2>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkRenderPass>*         pRenderPass)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pRenderPass"], pRenderPass, json_options);
    WriteBlockEnd("vkCreateRenderPass2KHR");
}

void VulkanExportDiveConsumer::Process_vkCmdBeginRenderPass2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderPassBeginInfo>* pRenderPassBegin,
    StructPointerDecoder<Decoded_VkSubpassBeginInfo>* pSubpassBeginInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pRenderPassBegin"], pRenderPassBegin, json_options);
    FieldToJson(args["pSubpassBeginInfo"], pSubpassBeginInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBeginRenderPass2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdNextSubpass2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSubpassBeginInfo>* pSubpassBeginInfo,
    StructPointerDecoder<Decoded_VkSubpassEndInfo>* pSubpassEndInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pSubpassBeginInfo"], pSubpassBeginInfo, json_options);
    FieldToJson(args["pSubpassEndInfo"], pSubpassEndInfo, json_options);
    util::DiveFunctionData function_data("vkCmdNextSubpass2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndRenderPass2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSubpassEndInfo>* pSubpassEndInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pSubpassEndInfo"], pSubpassEndInfo, json_options);
    util::DiveFunctionData function_data("vkCmdEndRenderPass2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetSwapchainStatusKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    WriteBlockEnd("vkGetSwapchainStatusKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalFencePropertiesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalFenceInfo>* pExternalFenceInfo,
    StructPointerDecoder<Decoded_VkExternalFenceProperties>* pExternalFenceProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pExternalFenceInfo"], pExternalFenceInfo, json_options);
    FieldToJson(args["pExternalFenceProperties"], pExternalFenceProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceExternalFencePropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkImportFenceWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImportFenceWin32HandleInfoKHR>* pImportFenceWin32HandleInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pImportFenceWin32HandleInfo"], pImportFenceWin32HandleInfo, json_options);
    WriteBlockEnd("vkImportFenceWin32HandleKHR");
}

void VulkanExportDiveConsumer::Process_vkGetFenceWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkFenceGetWin32HandleInfoKHR>* pGetWin32HandleInfo,
    PointerDecoder<uint64_t, void*>*            pHandle)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pGetWin32HandleInfo"], pGetWin32HandleInfo, json_options);
    FieldToJson(args["pHandle"], pHandle, json_options);
    WriteBlockEnd("vkGetFenceWin32HandleKHR");
}

void VulkanExportDiveConsumer::Process_vkImportFenceFdKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImportFenceFdInfoKHR>* pImportFenceFdInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pImportFenceFdInfo"], pImportFenceFdInfo, json_options);
    WriteBlockEnd("vkImportFenceFdKHR");
}

void VulkanExportDiveConsumer::Process_vkGetFenceFdKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkFenceGetFdInfoKHR>* pGetFdInfo,
    PointerDecoder<int>*                        pFd)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pGetFdInfo"], pGetFdInfo, json_options);
    FieldToJson(args["pFd"], pFd, json_options);
    WriteBlockEnd("vkGetFenceFdKHR");
}

void VulkanExportDiveConsumer::Process_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    PointerDecoder<uint32_t>*                   pCounterCount,
    StructPointerDecoder<Decoded_VkPerformanceCounterKHR>* pCounters,
    StructPointerDecoder<Decoded_VkPerformanceCounterDescriptionKHR>* pCounterDescriptions)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["queueFamilyIndex"], queueFamilyIndex, json_options);
    FieldToJson(args["pCounterCount"], pCounterCount, json_options);
    FieldToJson(args["pCounters"], pCounters, json_options);
    FieldToJson(args["pCounterDescriptions"], pCounterDescriptions, json_options);
    WriteBlockEnd("vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkQueryPoolPerformanceCreateInfoKHR>* pPerformanceQueryCreateInfo,
    PointerDecoder<uint32_t>*                   pNumPasses)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pPerformanceQueryCreateInfo"], pPerformanceQueryCreateInfo, json_options);
    FieldToJson(args["pNumPasses"], pNumPasses, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
}

void VulkanExportDiveConsumer::Process_vkAcquireProfilingLockKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAcquireProfilingLockInfoKHR>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkAcquireProfilingLockKHR");
}

void VulkanExportDiveConsumer::Process_vkReleaseProfilingLockKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    WriteBlockEnd("vkReleaseProfilingLockKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceCapabilities2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSurfaceInfo2KHR>* pSurfaceInfo,
    StructPointerDecoder<Decoded_VkSurfaceCapabilities2KHR>* pSurfaceCapabilities)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pSurfaceInfo"], pSurfaceInfo, json_options);
    FieldToJson(args["pSurfaceCapabilities"], pSurfaceCapabilities, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSurfaceCapabilities2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceFormats2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSurfaceInfo2KHR>* pSurfaceInfo,
    PointerDecoder<uint32_t>*                   pSurfaceFormatCount,
    StructPointerDecoder<Decoded_VkSurfaceFormat2KHR>* pSurfaceFormats)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pSurfaceInfo"], pSurfaceInfo, json_options);
    FieldToJson(args["pSurfaceFormatCount"], pSurfaceFormatCount, json_options);
    FieldToJson(args["pSurfaceFormats"], pSurfaceFormats, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSurfaceFormats2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceDisplayProperties2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayProperties2KHR>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceDisplayProperties2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceDisplayPlaneProperties2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayPlaneProperties2KHR>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceDisplayPlaneProperties2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetDisplayModeProperties2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            display,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayModeProperties2KHR>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["display"], display, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetDisplayModeProperties2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetDisplayPlaneCapabilities2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkDisplayPlaneInfo2KHR>* pDisplayPlaneInfo,
    StructPointerDecoder<Decoded_VkDisplayPlaneCapabilities2KHR>* pCapabilities)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pDisplayPlaneInfo"], pDisplayPlaneInfo, json_options);
    FieldToJson(args["pCapabilities"], pCapabilities, json_options);
    WriteBlockEnd("vkGetDisplayPlaneCapabilities2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetImageMemoryRequirements2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageMemoryRequirementsInfo2>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetImageMemoryRequirements2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetBufferMemoryRequirements2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferMemoryRequirementsInfo2>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetBufferMemoryRequirements2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetImageSparseMemoryRequirements2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageSparseMemoryRequirementsInfo2>* pInfo,
    PointerDecoder<uint32_t>*                   pSparseMemoryRequirementCount,
    StructPointerDecoder<Decoded_VkSparseImageMemoryRequirements2>* pSparseMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pSparseMemoryRequirementCount"], pSparseMemoryRequirementCount, json_options);
    FieldToJson(args["pSparseMemoryRequirements"], pSparseMemoryRequirements, json_options);
    WriteBlockEnd("vkGetImageSparseMemoryRequirements2KHR");
}

void VulkanExportDiveConsumer::Process_vkCreateSamplerYcbcrConversionKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSamplerYcbcrConversionCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSamplerYcbcrConversion>* pYcbcrConversion)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pYcbcrConversion"], pYcbcrConversion, json_options);
    WriteBlockEnd("vkCreateSamplerYcbcrConversionKHR");
}

void VulkanExportDiveConsumer::Process_vkDestroySamplerYcbcrConversionKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            ycbcrConversion,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["ycbcrConversion"], ycbcrConversion, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroySamplerYcbcrConversionKHR");
}

void VulkanExportDiveConsumer::Process_vkBindBufferMemory2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindBufferMemoryInfo>* pBindInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["bindInfoCount"], bindInfoCount, json_options);
    FieldToJson(args["pBindInfos"], pBindInfos, json_options);
    WriteBlockEnd("vkBindBufferMemory2KHR");
}

void VulkanExportDiveConsumer::Process_vkBindImageMemory2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindImageMemoryInfo>* pBindInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["bindInfoCount"], bindInfoCount, json_options);
    FieldToJson(args["pBindInfos"], pBindInfos, json_options);
    WriteBlockEnd("vkBindImageMemory2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetDescriptorSetLayoutSupportKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutSupport>* pSupport)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pSupport"], pSupport, json_options);
    WriteBlockEnd("vkGetDescriptorSetLayoutSupportKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndirectCountKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    format::HandleId                            countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    HandleToJson(args["countBuffer"], countBuffer, json_options);
    FieldToJson(args["countBufferOffset"], countBufferOffset, json_options);
    FieldToJson(args["maxDrawCount"], maxDrawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawIndirectCountKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndexedIndirectCountKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    format::HandleId                            countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    HandleToJson(args["countBuffer"], countBuffer, json_options);
    FieldToJson(args["countBufferOffset"], countBufferOffset, json_options);
    FieldToJson(args["maxDrawCount"], maxDrawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawIndexedIndirectCountKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetSemaphoreCounterValueKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            semaphore,
    PointerDecoder<uint64_t>*                   pValue)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["semaphore"], semaphore, json_options);
    FieldToJson(args["pValue"], pValue, json_options);
    WriteBlockEnd("vkGetSemaphoreCounterValueKHR");
}

void VulkanExportDiveConsumer::Process_vkWaitSemaphoresKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
    uint64_t                                    timeout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pWaitInfo"], pWaitInfo, json_options);
    FieldToJson(args["timeout"], timeout, json_options);
    WriteBlockEnd("vkWaitSemaphoresKHR");
}

void VulkanExportDiveConsumer::Process_vkSignalSemaphoreKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pSignalInfo"], pSignalInfo, json_options);
    WriteBlockEnd("vkSignalSemaphoreKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFragmentShadingRatesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pFragmentShadingRateCount,
    StructPointerDecoder<Decoded_VkPhysicalDeviceFragmentShadingRateKHR>* pFragmentShadingRates)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pFragmentShadingRateCount"], pFragmentShadingRateCount, json_options);
    FieldToJson(args["pFragmentShadingRates"], pFragmentShadingRates, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceFragmentShadingRatesKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdSetFragmentShadingRateKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkExtent2D>*   pFragmentSize,
    PointerDecoder<VkFragmentShadingRateCombinerOpKHR>* combinerOps)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pFragmentSize"], pFragmentSize, json_options);
    FieldToJson(args["combinerOps"], combinerOps, json_options);
    util::DiveFunctionData function_data("vkCmdSetFragmentShadingRateKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRenderingAttachmentLocationsKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingAttachmentLocationInfo>* pLocationInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pLocationInfo"], pLocationInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetRenderingAttachmentLocationsKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRenderingInputAttachmentIndicesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInputAttachmentIndexInfo>* pInputAttachmentIndexInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pInputAttachmentIndexInfo"], pInputAttachmentIndexInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetRenderingInputAttachmentIndicesKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkWaitForPresentKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    uint64_t                                    presentId,
    uint64_t                                    timeout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["presentId"], presentId, json_options);
    FieldToJson(args["timeout"], timeout, json_options);
    WriteBlockEnd("vkWaitForPresentKHR");
}

void VulkanExportDiveConsumer::Process_vkGetBufferDeviceAddressKHR(
    const ApiCallInfo&                          call_info,
    VkDeviceAddress                             returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferDeviceAddressInfo>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetBufferDeviceAddressKHR");
}

void VulkanExportDiveConsumer::Process_vkGetBufferOpaqueCaptureAddressKHR(
    const ApiCallInfo&                          call_info,
    uint64_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferDeviceAddressInfo>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetBufferOpaqueCaptureAddressKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceMemoryOpaqueCaptureAddressKHR(
    const ApiCallInfo&                          call_info,
    uint64_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceMemoryOpaqueCaptureAddressInfo>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetDeviceMemoryOpaqueCaptureAddressKHR");
}

void VulkanExportDiveConsumer::Process_vkCreateDeferredOperationKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDeferredOperationKHR>* pDeferredOperation)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pDeferredOperation"], pDeferredOperation, json_options);
    WriteBlockEnd("vkCreateDeferredOperationKHR");
}

void VulkanExportDiveConsumer::Process_vkDestroyDeferredOperationKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            operation,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["operation"], operation, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyDeferredOperationKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDeferredOperationMaxConcurrencyKHR(
    const ApiCallInfo&                          call_info,
    uint32_t                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            operation)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["operation"], operation, json_options);
    WriteBlockEnd("vkGetDeferredOperationMaxConcurrencyKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDeferredOperationResultKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            operation)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["operation"], operation, json_options);
    WriteBlockEnd("vkGetDeferredOperationResultKHR");
}

void VulkanExportDiveConsumer::Process_vkDeferredOperationJoinKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            operation)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["operation"], operation, json_options);
    WriteBlockEnd("vkDeferredOperationJoinKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPipelineExecutablePropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineInfoKHR>* pPipelineInfo,
    PointerDecoder<uint32_t>*                   pExecutableCount,
    StructPointerDecoder<Decoded_VkPipelineExecutablePropertiesKHR>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pPipelineInfo"], pPipelineInfo, json_options);
    FieldToJson(args["pExecutableCount"], pExecutableCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPipelineExecutablePropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPipelineExecutableStatisticsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineExecutableInfoKHR>* pExecutableInfo,
    PointerDecoder<uint32_t>*                   pStatisticCount,
    StructPointerDecoder<Decoded_VkPipelineExecutableStatisticKHR>* pStatistics)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pExecutableInfo"], pExecutableInfo, json_options);
    FieldToJson(args["pStatisticCount"], pStatisticCount, json_options);
    FieldToJson(args["pStatistics"], pStatistics, json_options);
    WriteBlockEnd("vkGetPipelineExecutableStatisticsKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPipelineExecutableInternalRepresentationsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineExecutableInfoKHR>* pExecutableInfo,
    PointerDecoder<uint32_t>*                   pInternalRepresentationCount,
    StructPointerDecoder<Decoded_VkPipelineExecutableInternalRepresentationKHR>* pInternalRepresentations)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pExecutableInfo"], pExecutableInfo, json_options);
    FieldToJson(args["pInternalRepresentationCount"], pInternalRepresentationCount, json_options);
    FieldToJson(args["pInternalRepresentations"], pInternalRepresentations, json_options);
    WriteBlockEnd("vkGetPipelineExecutableInternalRepresentationsKHR");
}

void VulkanExportDiveConsumer::Process_vkMapMemory2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryMapInfo>* pMemoryMapInfo,
    PointerDecoder<uint64_t, void*>*            ppData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pMemoryMapInfo"], pMemoryMapInfo, json_options);
    FieldToJsonAsHex(args["ppData"], ppData, json_options);
    WriteBlockEnd("vkMapMemory2KHR");
}

void VulkanExportDiveConsumer::Process_vkUnmapMemory2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryUnmapInfo>* pMemoryUnmapInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pMemoryUnmapInfo"], pMemoryUnmapInfo, json_options);
    WriteBlockEnd("vkUnmapMemory2KHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR>* pQualityLevelInfo,
    StructPointerDecoder<Decoded_VkVideoEncodeQualityLevelPropertiesKHR>* pQualityLevelProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pQualityLevelInfo"], pQualityLevelInfo, json_options);
    FieldToJson(args["pQualityLevelProperties"], pQualityLevelProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetEncodedVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkVideoEncodeSessionParametersGetInfoKHR>* pVideoSessionParametersInfo,
    StructPointerDecoder<Decoded_VkVideoEncodeSessionParametersFeedbackInfoKHR>* pFeedbackInfo,
    PointerDecoder<size_t>*                     pDataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pVideoSessionParametersInfo"], pVideoSessionParametersInfo, json_options);
    FieldToJson(args["pFeedbackInfo"], pFeedbackInfo, json_options);
    FieldToJson(args["pDataSize"], pDataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    WriteBlockEnd("vkGetEncodedVideoSessionParametersKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdEncodeVideoKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkVideoEncodeInfoKHR>* pEncodeInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pEncodeInfo"], pEncodeInfo, json_options);
    util::DiveFunctionData function_data("vkCmdEncodeVideoKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetEvent2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["event"], event, json_options);
    FieldToJson(args["pDependencyInfo"], pDependencyInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetEvent2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdResetEvent2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    VkPipelineStageFlags2                       stageMask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["event"], event, json_options);
    FieldToJson(VkPipelineStageFlags2_t(), args["stageMask"], stageMask, json_options);
    util::DiveFunctionData function_data("vkCmdResetEvent2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdWaitEvents2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    eventCount,
    HandlePointerDecoder<VkEvent>*              pEvents,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["eventCount"], eventCount, json_options);
    HandleToJson(args["pEvents"], pEvents, json_options);
    FieldToJson(args["pDependencyInfos"], pDependencyInfos, json_options);
    util::DiveFunctionData function_data("vkCmdWaitEvents2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdPipelineBarrier2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pDependencyInfo"], pDependencyInfo, json_options);
    util::DiveFunctionData function_data("vkCmdPipelineBarrier2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdWriteTimestamp2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlags2                       stage,
    format::HandleId                            queryPool,
    uint32_t                                    query)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkPipelineStageFlags2_t(), args["stage"], stage, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["query"], query, json_options);
    util::DiveFunctionData function_data("vkCmdWriteTimestamp2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkQueueSubmit2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    uint32_t                                    submitCount,
    StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
    format::HandleId                            fence)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    FieldToJson(args["submitCount"], submitCount, json_options);
    FieldToJson(args["pSubmits"], pSubmits, json_options);
    HandleToJson(args["fence"], fence, json_options);
    WriteBlockEnd("vkQueueSubmit2KHR");
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBuffer2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferInfo2>* pCopyBufferInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pCopyBufferInfo"], pCopyBufferInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyBuffer2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyImage2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageInfo2>* pCopyImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pCopyImageInfo"], pCopyImageInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyImage2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBufferToImage2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferToImageInfo2>* pCopyBufferToImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pCopyBufferToImageInfo"], pCopyBufferToImageInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyBufferToImage2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyImageToBuffer2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageToBufferInfo2>* pCopyImageToBufferInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pCopyImageToBufferInfo"], pCopyImageToBufferInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyImageToBuffer2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBlitImage2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBlitImageInfo2>* pBlitImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pBlitImageInfo"], pBlitImageInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBlitImage2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdResolveImage2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkResolveImageInfo2>* pResolveImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pResolveImageInfo"], pResolveImageInfo, json_options);
    util::DiveFunctionData function_data("vkCmdResolveImage2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdTraceRaysIndirect2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkDeviceAddress                             indirectDeviceAddress)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJsonAsHex(args["indirectDeviceAddress"], indirectDeviceAddress, json_options);
    util::DiveFunctionData function_data("vkCmdTraceRaysIndirect2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceBufferMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceBufferMemoryRequirements>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetDeviceBufferMemoryRequirementsKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageMemoryRequirements>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetDeviceImageMemoryRequirementsKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageSparseMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageMemoryRequirements>* pInfo,
    PointerDecoder<uint32_t>*                   pSparseMemoryRequirementCount,
    StructPointerDecoder<Decoded_VkSparseImageMemoryRequirements2>* pSparseMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pSparseMemoryRequirementCount"], pSparseMemoryRequirementCount, json_options);
    FieldToJson(args["pSparseMemoryRequirements"], pSparseMemoryRequirements, json_options);
    WriteBlockEnd("vkGetDeviceImageSparseMemoryRequirementsKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdBindIndexBuffer2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkIndexType                                 indexType)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    FieldToJson(args["size"], size, json_options);
    FieldToJson(args["indexType"], indexType, json_options);
    util::DiveFunctionData function_data("vkCmdBindIndexBuffer2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetRenderingAreaGranularityKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderingAreaInfo>* pRenderingAreaInfo,
    StructPointerDecoder<Decoded_VkExtent2D>*   pGranularity)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pRenderingAreaInfo"], pRenderingAreaInfo, json_options);
    FieldToJson(args["pGranularity"], pGranularity, json_options);
    WriteBlockEnd("vkGetRenderingAreaGranularityKHR");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageSubresourceLayoutKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageSubresourceInfo>* pInfo,
    StructPointerDecoder<Decoded_VkSubresourceLayout2>* pLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pLayout"], pLayout, json_options);
    WriteBlockEnd("vkGetDeviceImageSubresourceLayoutKHR");
}

void VulkanExportDiveConsumer::Process_vkGetImageSubresourceLayout2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkImageSubresource2>* pSubresource,
    StructPointerDecoder<Decoded_VkSubresourceLayout2>* pLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["image"], image, json_options);
    FieldToJson(args["pSubresource"], pSubresource, json_options);
    FieldToJson(args["pLayout"], pLayout, json_options);
    WriteBlockEnd("vkGetImageSubresourceLayout2KHR");
}

void VulkanExportDiveConsumer::Process_vkCreatePipelineBinariesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineBinaryCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    StructPointerDecoder<Decoded_VkPipelineBinaryHandlesInfoKHR>* pBinaries)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    FieldToJson(args["pBinaries"], pBinaries, json_options);
    WriteBlockEnd("vkCreatePipelineBinariesKHR");
}

void VulkanExportDiveConsumer::Process_vkDestroyPipelineBinaryKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            pipelineBinary,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipelineBinary"], pipelineBinary, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyPipelineBinaryKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPipelineKeyKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineCreateInfoKHR>* pPipelineCreateInfo,
    StructPointerDecoder<Decoded_VkPipelineBinaryKeyKHR>* pPipelineKey)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pPipelineCreateInfo"], pPipelineCreateInfo, json_options);
    FieldToJson(args["pPipelineKey"], pPipelineKey, json_options);
    WriteBlockEnd("vkGetPipelineKeyKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPipelineBinaryDataKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineBinaryDataInfoKHR>* pInfo,
    StructPointerDecoder<Decoded_VkPipelineBinaryKeyKHR>* pPipelineBinaryKey,
    PointerDecoder<size_t>*                     pPipelineBinaryDataSize,
    PointerDecoder<uint8_t>*                    pPipelineBinaryData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pPipelineBinaryKey"], pPipelineBinaryKey, json_options);
    FieldToJson(args["pPipelineBinaryDataSize"], pPipelineBinaryDataSize, json_options);
    FieldToJson(args["pPipelineBinaryData"], pPipelineBinaryData, json_options);
    WriteBlockEnd("vkGetPipelineBinaryDataKHR");
}

void VulkanExportDiveConsumer::Process_vkReleaseCapturedPipelineDataKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkReleaseCapturedPipelineDataInfoKHR>* pInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkReleaseCapturedPipelineDataKHR");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkCooperativeMatrixPropertiesKHR>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineStippleKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["lineStippleFactor"], lineStippleFactor, json_options);
    FieldToJson(args["lineStipplePattern"], lineStipplePattern, json_options);
    util::DiveFunctionData function_data("vkCmdSetLineStippleKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pTimeDomainCount,
    PointerDecoder<VkTimeDomainKHR>*            pTimeDomains)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pTimeDomainCount"], pTimeDomainCount, json_options);
    FieldToJson(args["pTimeDomains"], pTimeDomains, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceCalibrateableTimeDomainsKHR");
}

void VulkanExportDiveConsumer::Process_vkGetCalibratedTimestampsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    timestampCount,
    StructPointerDecoder<Decoded_VkCalibratedTimestampInfoKHR>* pTimestampInfos,
    PointerDecoder<uint64_t>*                   pTimestamps,
    PointerDecoder<uint64_t>*                   pMaxDeviation)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["timestampCount"], timestampCount, json_options);
    FieldToJson(args["pTimestampInfos"], pTimestampInfos, json_options);
    FieldToJson(args["pTimestamps"], pTimestamps, json_options);
    FieldToJson(args["pMaxDeviation"], pMaxDeviation, json_options);
    WriteBlockEnd("vkGetCalibratedTimestampsKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdBindDescriptorSets2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBindDescriptorSetsInfo>* pBindDescriptorSetsInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pBindDescriptorSetsInfo"], pBindDescriptorSetsInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBindDescriptorSets2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdPushConstants2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPushConstantsInfo>* pPushConstantsInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pPushConstantsInfo"], pPushConstantsInfo, json_options);
    util::DiveFunctionData function_data("vkCmdPushConstants2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdPushDescriptorSet2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPushDescriptorSetInfo>* pPushDescriptorSetInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pPushDescriptorSetInfo"], pPushDescriptorSetInfo, json_options);
    util::DiveFunctionData function_data("vkCmdPushDescriptorSet2KHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDescriptorBufferOffsets2EXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSetDescriptorBufferOffsetsInfoEXT>* pSetDescriptorBufferOffsetsInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pSetDescriptorBufferOffsetsInfo"], pSetDescriptorBufferOffsetsInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetDescriptorBufferOffsets2EXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBindDescriptorBufferEmbeddedSamplersInfoEXT>* pBindDescriptorBufferEmbeddedSamplersInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pBindDescriptorBufferEmbeddedSamplersInfo"], pBindDescriptorBufferEmbeddedSamplersInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBindDescriptorBufferEmbeddedSamplers2EXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkFrameBoundaryANDROID(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            semaphore,
    format::HandleId                            image)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["semaphore"], semaphore, json_options);
    HandleToJson(args["image"], image, json_options);
    WriteBlockEnd("vkFrameBoundaryANDROID");
}

void VulkanExportDiveConsumer::Process_vkCreateDebugReportCallbackEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkDebugReportCallbackCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDebugReportCallbackEXT>* pCallback)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pCallback"], pCallback, json_options);
    WriteBlockEnd("vkCreateDebugReportCallbackEXT");
}

void VulkanExportDiveConsumer::Process_vkDestroyDebugReportCallbackEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    format::HandleId                            callback,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    HandleToJson(args["callback"], callback, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyDebugReportCallbackEXT");
}

void VulkanExportDiveConsumer::Process_vkDebugReportMessageEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    VkDebugReportFlagsEXT                       flags,
    VkDebugReportObjectTypeEXT                  objectType,
    uint64_t                                    object,
    size_t                                      location,
    int32_t                                     messageCode,
    StringDecoder*                              pLayerPrefix,
    StringDecoder*                              pMessage)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(VkDebugReportFlagsEXT_t(), args["flags"], flags, json_options);
    FieldToJson(args["objectType"], objectType, json_options);
    FieldToJson(args["object"], object, json_options);
    FieldToJson(args["location"], location, json_options);
    FieldToJson(args["messageCode"], messageCode, json_options);
    FieldToJson(args["pLayerPrefix"], pLayerPrefix, json_options);
    FieldToJson(args["pMessage"], pMessage, json_options);
    WriteBlockEnd("vkDebugReportMessageEXT");
}

void VulkanExportDiveConsumer::Process_vkDebugMarkerSetObjectTagEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDebugMarkerObjectTagInfoEXT>* pTagInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pTagInfo"], pTagInfo, json_options);
    WriteBlockEnd("vkDebugMarkerSetObjectTagEXT");
}

void VulkanExportDiveConsumer::Process_vkDebugMarkerSetObjectNameEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDebugMarkerObjectNameInfoEXT>* pNameInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pNameInfo"], pNameInfo, json_options);
    WriteBlockEnd("vkDebugMarkerSetObjectNameEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdDebugMarkerBeginEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDebugMarkerMarkerInfoEXT>* pMarkerInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pMarkerInfo"], pMarkerInfo, json_options);
    util::DiveFunctionData function_data("vkCmdDebugMarkerBeginEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDebugMarkerEndEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    util::DiveFunctionData function_data("vkCmdDebugMarkerEndEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDebugMarkerInsertEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDebugMarkerMarkerInfoEXT>* pMarkerInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pMarkerInfo"], pMarkerInfo, json_options);
    util::DiveFunctionData function_data("vkCmdDebugMarkerInsertEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBindTransformFeedbackBuffersEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    HandlePointerDecoder<VkBuffer>*             pBuffers,
    PointerDecoder<VkDeviceSize>*               pOffsets,
    PointerDecoder<VkDeviceSize>*               pSizes)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstBinding"], firstBinding, json_options);
    FieldToJson(args["bindingCount"], bindingCount, json_options);
    HandleToJson(args["pBuffers"], pBuffers, json_options);
    FieldToJson(args["pOffsets"], pOffsets, json_options);
    FieldToJson(args["pSizes"], pSizes, json_options);
    util::DiveFunctionData function_data("vkCmdBindTransformFeedbackBuffersEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginTransformFeedbackEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstCounterBuffer,
    uint32_t                                    counterBufferCount,
    HandlePointerDecoder<VkBuffer>*             pCounterBuffers,
    PointerDecoder<VkDeviceSize>*               pCounterBufferOffsets)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstCounterBuffer"], firstCounterBuffer, json_options);
    FieldToJson(args["counterBufferCount"], counterBufferCount, json_options);
    HandleToJson(args["pCounterBuffers"], pCounterBuffers, json_options);
    FieldToJson(args["pCounterBufferOffsets"], pCounterBufferOffsets, json_options);
    util::DiveFunctionData function_data("vkCmdBeginTransformFeedbackEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndTransformFeedbackEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstCounterBuffer,
    uint32_t                                    counterBufferCount,
    HandlePointerDecoder<VkBuffer>*             pCounterBuffers,
    PointerDecoder<VkDeviceSize>*               pCounterBufferOffsets)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstCounterBuffer"], firstCounterBuffer, json_options);
    FieldToJson(args["counterBufferCount"], counterBufferCount, json_options);
    HandleToJson(args["pCounterBuffers"], pCounterBuffers, json_options);
    FieldToJson(args["pCounterBufferOffsets"], pCounterBufferOffsets, json_options);
    util::DiveFunctionData function_data("vkCmdEndTransformFeedbackEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginQueryIndexedEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    query,
    VkQueryControlFlags                         flags,
    uint32_t                                    index)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["query"], query, json_options);
    FieldToJson(VkQueryControlFlags_t(), args["flags"], flags, json_options);
    FieldToJson(args["index"], index, json_options);
    util::DiveFunctionData function_data("vkCmdBeginQueryIndexedEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndQueryIndexedEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    query,
    uint32_t                                    index)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["query"], query, json_options);
    FieldToJson(args["index"], index, json_options);
    util::DiveFunctionData function_data("vkCmdEndQueryIndexedEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndirectByteCountEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    format::HandleId                            counterBuffer,
    VkDeviceSize                                counterBufferOffset,
    uint32_t                                    counterOffset,
    uint32_t                                    vertexStride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["instanceCount"], instanceCount, json_options);
    FieldToJson(args["firstInstance"], firstInstance, json_options);
    HandleToJson(args["counterBuffer"], counterBuffer, json_options);
    FieldToJson(args["counterBufferOffset"], counterBufferOffset, json_options);
    FieldToJson(args["counterOffset"], counterOffset, json_options);
    FieldToJson(args["vertexStride"], vertexStride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawIndirectByteCountEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetImageViewHandleNVX(
    const ApiCallInfo&                          call_info,
    uint32_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageViewHandleInfoNVX>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetImageViewHandleNVX");
}

void VulkanExportDiveConsumer::Process_vkGetImageViewHandle64NVX(
    const ApiCallInfo&                          call_info,
    uint64_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageViewHandleInfoNVX>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetImageViewHandle64NVX");
}

void VulkanExportDiveConsumer::Process_vkGetImageViewAddressNVX(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            imageView,
    StructPointerDecoder<Decoded_VkImageViewAddressPropertiesNVX>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["imageView"], imageView, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetImageViewAddressNVX");
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndirectCountAMD(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    format::HandleId                            countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    HandleToJson(args["countBuffer"], countBuffer, json_options);
    FieldToJson(args["countBufferOffset"], countBufferOffset, json_options);
    FieldToJson(args["maxDrawCount"], maxDrawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawIndirectCountAMD", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndexedIndirectCountAMD(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    format::HandleId                            countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    HandleToJson(args["countBuffer"], countBuffer, json_options);
    FieldToJson(args["countBufferOffset"], countBufferOffset, json_options);
    FieldToJson(args["maxDrawCount"], maxDrawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawIndexedIndirectCountAMD", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetShaderInfoAMD(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            pipeline,
    VkShaderStageFlagBits                       shaderStage,
    VkShaderInfoTypeAMD                         infoType,
    PointerDecoder<size_t>*                     pInfoSize,
    PointerDecoder<uint8_t>*                    pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipeline"], pipeline, json_options);
    FieldToJson(args["shaderStage"], shaderStage, json_options);
    FieldToJson(args["infoType"], infoType, json_options);
    FieldToJson(args["pInfoSize"], pInfoSize, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetShaderInfoAMD");
}

void VulkanExportDiveConsumer::Process_vkCreateStreamDescriptorSurfaceGGP(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkStreamDescriptorSurfaceCreateInfoGGP>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateStreamDescriptorSurfaceGGP");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalImageFormatPropertiesNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    VkFormat                                    format,
    VkImageType                                 type,
    VkImageTiling                               tiling,
    VkImageUsageFlags                           usage,
    VkImageCreateFlags                          flags,
    VkExternalMemoryHandleTypeFlagsNV           externalHandleType,
    StructPointerDecoder<Decoded_VkExternalImageFormatPropertiesNV>* pExternalImageFormatProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["format"], format, json_options);
    FieldToJson(args["type"], type, json_options);
    FieldToJson(args["tiling"], tiling, json_options);
    FieldToJson(VkImageUsageFlags_t(), args["usage"], usage, json_options);
    FieldToJson(VkImageCreateFlags_t(), args["flags"], flags, json_options);
    FieldToJson(VkExternalMemoryHandleTypeFlagsNV_t(), args["externalHandleType"], externalHandleType, json_options);
    FieldToJson(args["pExternalImageFormatProperties"], pExternalImageFormatProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceExternalImageFormatPropertiesNV");
}

void VulkanExportDiveConsumer::Process_vkGetMemoryWin32HandleNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            memory,
    VkExternalMemoryHandleTypeFlagsNV           handleType,
    PointerDecoder<uint64_t, void*>*            pHandle)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["memory"], memory, json_options);
    FieldToJson(VkExternalMemoryHandleTypeFlagsNV_t(), args["handleType"], handleType, json_options);
    FieldToJson(args["pHandle"], pHandle, json_options);
    WriteBlockEnd("vkGetMemoryWin32HandleNV");
}

void VulkanExportDiveConsumer::Process_vkCreateViSurfaceNN(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkViSurfaceCreateInfoNN>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateViSurfaceNN");
}

void VulkanExportDiveConsumer::Process_vkCmdBeginConditionalRenderingEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkConditionalRenderingBeginInfoEXT>* pConditionalRenderingBegin)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pConditionalRenderingBegin"], pConditionalRenderingBegin, json_options);
    util::DiveFunctionData function_data("vkCmdBeginConditionalRenderingEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndConditionalRenderingEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    util::DiveFunctionData function_data("vkCmdEndConditionalRenderingEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportWScalingNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkViewportWScalingNV>* pViewportWScalings)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstViewport"], firstViewport, json_options);
    FieldToJson(args["viewportCount"], viewportCount, json_options);
    FieldToJson(args["pViewportWScalings"], pViewportWScalings, json_options);
    util::DiveFunctionData function_data("vkCmdSetViewportWScalingNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkReleaseDisplayEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            display)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["display"], display, json_options);
    WriteBlockEnd("vkReleaseDisplayEXT");
}

void VulkanExportDiveConsumer::Process_vkAcquireXlibDisplayEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint64_t                                    dpy,
    format::HandleId                            display)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["dpy"], dpy, json_options);
    HandleToJson(args["display"], display, json_options);
    WriteBlockEnd("vkAcquireXlibDisplayEXT");
}

void VulkanExportDiveConsumer::Process_vkGetRandROutputDisplayEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint64_t                                    dpy,
    size_t                                      rrOutput,
    HandlePointerDecoder<VkDisplayKHR>*         pDisplay)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["dpy"], dpy, json_options);
    FieldToJson(args["rrOutput"], rrOutput, json_options);
    HandleToJson(args["pDisplay"], pDisplay, json_options);
    WriteBlockEnd("vkGetRandROutputDisplayEXT");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceCapabilities2EXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            surface,
    StructPointerDecoder<Decoded_VkSurfaceCapabilities2EXT>* pSurfaceCapabilities)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["surface"], surface, json_options);
    FieldToJson(args["pSurfaceCapabilities"], pSurfaceCapabilities, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSurfaceCapabilities2EXT");
}

void VulkanExportDiveConsumer::Process_vkDisplayPowerControlEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            display,
    StructPointerDecoder<Decoded_VkDisplayPowerInfoEXT>* pDisplayPowerInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["display"], display, json_options);
    FieldToJson(args["pDisplayPowerInfo"], pDisplayPowerInfo, json_options);
    WriteBlockEnd("vkDisplayPowerControlEXT");
}

void VulkanExportDiveConsumer::Process_vkRegisterDeviceEventEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceEventInfoEXT>* pDeviceEventInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkFence>*              pFence)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pDeviceEventInfo"], pDeviceEventInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pFence"], pFence, json_options);
    WriteBlockEnd("vkRegisterDeviceEventEXT");
}

void VulkanExportDiveConsumer::Process_vkRegisterDisplayEventEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            display,
    StructPointerDecoder<Decoded_VkDisplayEventInfoEXT>* pDisplayEventInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkFence>*              pFence)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["display"], display, json_options);
    FieldToJson(args["pDisplayEventInfo"], pDisplayEventInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pFence"], pFence, json_options);
    WriteBlockEnd("vkRegisterDisplayEventEXT");
}

void VulkanExportDiveConsumer::Process_vkGetSwapchainCounterEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    VkSurfaceCounterFlagBitsEXT                 counter,
    PointerDecoder<uint64_t>*                   pCounterValue)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["counter"], counter, json_options);
    FieldToJson(args["pCounterValue"], pCounterValue, json_options);
    WriteBlockEnd("vkGetSwapchainCounterEXT");
}

void VulkanExportDiveConsumer::Process_vkGetRefreshCycleDurationGOOGLE(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkRefreshCycleDurationGOOGLE>* pDisplayTimingProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["pDisplayTimingProperties"], pDisplayTimingProperties, json_options);
    WriteBlockEnd("vkGetRefreshCycleDurationGOOGLE");
}

void VulkanExportDiveConsumer::Process_vkGetPastPresentationTimingGOOGLE(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    PointerDecoder<uint32_t>*                   pPresentationTimingCount,
    StructPointerDecoder<Decoded_VkPastPresentationTimingGOOGLE>* pPresentationTimings)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["pPresentationTimingCount"], pPresentationTimingCount, json_options);
    FieldToJson(args["pPresentationTimings"], pPresentationTimings, json_options);
    WriteBlockEnd("vkGetPastPresentationTimingGOOGLE");
}

void VulkanExportDiveConsumer::Process_vkCmdSetDiscardRectangleEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstDiscardRectangle,
    uint32_t                                    discardRectangleCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pDiscardRectangles)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstDiscardRectangle"], firstDiscardRectangle, json_options);
    FieldToJson(args["discardRectangleCount"], discardRectangleCount, json_options);
    FieldToJson(args["pDiscardRectangles"], pDiscardRectangles, json_options);
    util::DiveFunctionData function_data("vkCmdSetDiscardRectangleEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDiscardRectangleEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    discardRectangleEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["discardRectangleEnable"], discardRectangleEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDiscardRectangleEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDiscardRectangleModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkDiscardRectangleModeEXT                   discardRectangleMode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["discardRectangleMode"], discardRectangleMode, json_options);
    util::DiveFunctionData function_data("vkCmdSetDiscardRectangleModeEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkSetHdrMetadataEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    uint32_t                                    swapchainCount,
    HandlePointerDecoder<VkSwapchainKHR>*       pSwapchains,
    StructPointerDecoder<Decoded_VkHdrMetadataEXT>* pMetadata)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["swapchainCount"], swapchainCount, json_options);
    HandleToJson(args["pSwapchains"], pSwapchains, json_options);
    FieldToJson(args["pMetadata"], pMetadata, json_options);
    WriteBlockEnd("vkSetHdrMetadataEXT");
}

void VulkanExportDiveConsumer::Process_vkCreateIOSSurfaceMVK(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkIOSSurfaceCreateInfoMVK>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateIOSSurfaceMVK");
}

void VulkanExportDiveConsumer::Process_vkCreateMacOSSurfaceMVK(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkMacOSSurfaceCreateInfoMVK>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateMacOSSurfaceMVK");
}

void VulkanExportDiveConsumer::Process_vkSetDebugUtilsObjectNameEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDebugUtilsObjectNameInfoEXT>* pNameInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pNameInfo"], pNameInfo, json_options);
    WriteBlockEnd("vkSetDebugUtilsObjectNameEXT");
}

void VulkanExportDiveConsumer::Process_vkSetDebugUtilsObjectTagEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDebugUtilsObjectTagInfoEXT>* pTagInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pTagInfo"], pTagInfo, json_options);
    WriteBlockEnd("vkSetDebugUtilsObjectTagEXT");
}

void VulkanExportDiveConsumer::Process_vkQueueBeginDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue,
    StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    FieldToJson(args["pLabelInfo"], pLabelInfo, json_options);
    WriteBlockEnd("vkQueueBeginDebugUtilsLabelEXT");
}

void VulkanExportDiveConsumer::Process_vkQueueEndDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    WriteBlockEnd("vkQueueEndDebugUtilsLabelEXT");
}

void VulkanExportDiveConsumer::Process_vkQueueInsertDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue,
    StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    FieldToJson(args["pLabelInfo"], pLabelInfo, json_options);
    WriteBlockEnd("vkQueueInsertDebugUtilsLabelEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdBeginDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pLabelInfo"], pLabelInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBeginDebugUtilsLabelEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdEndDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    util::DiveFunctionData function_data("vkCmdEndDebugUtilsLabelEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdInsertDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pLabelInfo"], pLabelInfo, json_options);
    util::DiveFunctionData function_data("vkCmdInsertDebugUtilsLabelEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCreateDebugUtilsMessengerEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkDebugUtilsMessengerCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDebugUtilsMessengerEXT>* pMessenger)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pMessenger"], pMessenger, json_options);
    WriteBlockEnd("vkCreateDebugUtilsMessengerEXT");
}

void VulkanExportDiveConsumer::Process_vkDestroyDebugUtilsMessengerEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    format::HandleId                            messenger,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    HandleToJson(args["messenger"], messenger, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyDebugUtilsMessengerEXT");
}

void VulkanExportDiveConsumer::Process_vkSubmitDebugUtilsMessageEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
    StructPointerDecoder<Decoded_VkDebugUtilsMessengerCallbackDataEXT>* pCallbackData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["messageSeverity"], messageSeverity, json_options);
    FieldToJson(VkDebugUtilsMessageTypeFlagsEXT_t(), args["messageTypes"], messageTypes, json_options);
    FieldToJson(args["pCallbackData"], pCallbackData, json_options);
    WriteBlockEnd("vkSubmitDebugUtilsMessageEXT");
}

void VulkanExportDiveConsumer::Process_vkGetAndroidHardwareBufferPropertiesANDROID(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint64_t                                    buffer,
    StructPointerDecoder<Decoded_VkAndroidHardwareBufferPropertiesANDROID>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetAndroidHardwareBufferPropertiesANDROID");
}

void VulkanExportDiveConsumer::Process_vkGetMemoryAndroidHardwareBufferANDROID(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetAndroidHardwareBufferInfoANDROID>* pInfo,
    PointerDecoder<uint64_t, void*>*            pBuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pBuffer"], pBuffer, json_options);
    WriteBlockEnd("vkGetMemoryAndroidHardwareBufferANDROID");
}

void VulkanExportDiveConsumer::Process_vkCmdSetSampleLocationsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSampleLocationsInfoEXT>* pSampleLocationsInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pSampleLocationsInfo"], pSampleLocationsInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetSampleLocationsEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceMultisamplePropertiesEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    VkSampleCountFlagBits                       samples,
    StructPointerDecoder<Decoded_VkMultisamplePropertiesEXT>* pMultisampleProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["samples"], samples, json_options);
    FieldToJson(args["pMultisampleProperties"], pMultisampleProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceMultisamplePropertiesEXT");
}

void VulkanExportDiveConsumer::Process_vkGetImageDrmFormatModifierPropertiesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkImageDrmFormatModifierPropertiesEXT>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["image"], image, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetImageDrmFormatModifierPropertiesEXT");
}

void VulkanExportDiveConsumer::Process_vkCreateValidationCacheEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkValidationCacheCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkValidationCacheEXT>* pValidationCache)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pValidationCache"], pValidationCache, json_options);
    WriteBlockEnd("vkCreateValidationCacheEXT");
}

void VulkanExportDiveConsumer::Process_vkDestroyValidationCacheEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            validationCache,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["validationCache"], validationCache, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyValidationCacheEXT");
}

void VulkanExportDiveConsumer::Process_vkMergeValidationCachesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            dstCache,
    uint32_t                                    srcCacheCount,
    HandlePointerDecoder<VkValidationCacheEXT>* pSrcCaches)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["dstCache"], dstCache, json_options);
    FieldToJson(args["srcCacheCount"], srcCacheCount, json_options);
    HandleToJson(args["pSrcCaches"], pSrcCaches, json_options);
    WriteBlockEnd("vkMergeValidationCachesEXT");
}

void VulkanExportDiveConsumer::Process_vkGetValidationCacheDataEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            validationCache,
    PointerDecoder<size_t>*                     pDataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["validationCache"], validationCache, json_options);
    FieldToJson(args["pDataSize"], pDataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    WriteBlockEnd("vkGetValidationCacheDataEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdBindShadingRateImageNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            imageView,
    VkImageLayout                               imageLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["imageView"], imageView, json_options);
    FieldToJson(args["imageLayout"], imageLayout, json_options);
    util::DiveFunctionData function_data("vkCmdBindShadingRateImageNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportShadingRatePaletteNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkShadingRatePaletteNV>* pShadingRatePalettes)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstViewport"], firstViewport, json_options);
    FieldToJson(args["viewportCount"], viewportCount, json_options);
    FieldToJson(args["pShadingRatePalettes"], pShadingRatePalettes, json_options);
    util::DiveFunctionData function_data("vkCmdSetViewportShadingRatePaletteNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoarseSampleOrderNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCoarseSampleOrderTypeNV                   sampleOrderType,
    uint32_t                                    customSampleOrderCount,
    StructPointerDecoder<Decoded_VkCoarseSampleOrderCustomNV>* pCustomSampleOrders)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["sampleOrderType"], sampleOrderType, json_options);
    FieldToJson(args["customSampleOrderCount"], customSampleOrderCount, json_options);
    FieldToJson(args["pCustomSampleOrders"], pCustomSampleOrders, json_options);
    util::DiveFunctionData function_data("vkCmdSetCoarseSampleOrderNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCreateAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAccelerationStructureCreateInfoNV>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkAccelerationStructureNV>* pAccelerationStructure)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pAccelerationStructure"], pAccelerationStructure, json_options);
    WriteBlockEnd("vkCreateAccelerationStructureNV");
}

void VulkanExportDiveConsumer::Process_vkDestroyAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            accelerationStructure,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["accelerationStructure"], accelerationStructure, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyAccelerationStructureNV");
}

void VulkanExportDiveConsumer::Process_vkGetAccelerationStructureMemoryRequirementsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAccelerationStructureMemoryRequirementsInfoNV>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2KHR>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetAccelerationStructureMemoryRequirementsNV");
}

void VulkanExportDiveConsumer::Process_vkBindAccelerationStructureMemoryNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindAccelerationStructureMemoryInfoNV>* pBindInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["bindInfoCount"], bindInfoCount, json_options);
    FieldToJson(args["pBindInfos"], pBindInfos, json_options);
    WriteBlockEnd("vkBindAccelerationStructureMemoryNV");
}

void VulkanExportDiveConsumer::Process_vkCmdBuildAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkAccelerationStructureInfoNV>* pInfo,
    format::HandleId                            instanceData,
    VkDeviceSize                                instanceOffset,
    VkBool32                                    update,
    format::HandleId                            dst,
    format::HandleId                            src,
    format::HandleId                            scratch,
    VkDeviceSize                                scratchOffset)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    HandleToJson(args["instanceData"], instanceData, json_options);
    FieldToJson(args["instanceOffset"], instanceOffset, json_options);
    Bool32ToJson(args["update"], update, json_options);
    HandleToJson(args["dst"], dst, json_options);
    HandleToJson(args["src"], src, json_options);
    HandleToJson(args["scratch"], scratch, json_options);
    FieldToJson(args["scratchOffset"], scratchOffset, json_options);
    util::DiveFunctionData function_data("vkCmdBuildAccelerationStructureNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            dst,
    format::HandleId                            src,
    VkCopyAccelerationStructureModeKHR          mode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["dst"], dst, json_options);
    HandleToJson(args["src"], src, json_options);
    FieldToJson(args["mode"], mode, json_options);
    util::DiveFunctionData function_data("vkCmdCopyAccelerationStructureNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdTraceRaysNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            raygenShaderBindingTableBuffer,
    VkDeviceSize                                raygenShaderBindingOffset,
    format::HandleId                            missShaderBindingTableBuffer,
    VkDeviceSize                                missShaderBindingOffset,
    VkDeviceSize                                missShaderBindingStride,
    format::HandleId                            hitShaderBindingTableBuffer,
    VkDeviceSize                                hitShaderBindingOffset,
    VkDeviceSize                                hitShaderBindingStride,
    format::HandleId                            callableShaderBindingTableBuffer,
    VkDeviceSize                                callableShaderBindingOffset,
    VkDeviceSize                                callableShaderBindingStride,
    uint32_t                                    width,
    uint32_t                                    height,
    uint32_t                                    depth)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["raygenShaderBindingTableBuffer"], raygenShaderBindingTableBuffer, json_options);
    FieldToJson(args["raygenShaderBindingOffset"], raygenShaderBindingOffset, json_options);
    HandleToJson(args["missShaderBindingTableBuffer"], missShaderBindingTableBuffer, json_options);
    FieldToJson(args["missShaderBindingOffset"], missShaderBindingOffset, json_options);
    FieldToJson(args["missShaderBindingStride"], missShaderBindingStride, json_options);
    HandleToJson(args["hitShaderBindingTableBuffer"], hitShaderBindingTableBuffer, json_options);
    FieldToJson(args["hitShaderBindingOffset"], hitShaderBindingOffset, json_options);
    FieldToJson(args["hitShaderBindingStride"], hitShaderBindingStride, json_options);
    HandleToJson(args["callableShaderBindingTableBuffer"], callableShaderBindingTableBuffer, json_options);
    FieldToJson(args["callableShaderBindingOffset"], callableShaderBindingOffset, json_options);
    FieldToJson(args["callableShaderBindingStride"], callableShaderBindingStride, json_options);
    FieldToJson(args["width"], width, json_options);
    FieldToJson(args["height"], height, json_options);
    FieldToJson(args["depth"], depth, json_options);
    util::DiveFunctionData function_data("vkCmdTraceRaysNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCreateRayTracingPipelinesNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            pipelineCache,
    uint32_t                                    createInfoCount,
    StructPointerDecoder<Decoded_VkRayTracingPipelineCreateInfoNV>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipeline>*           pPipelines)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipelineCache"], pipelineCache, json_options);
    FieldToJson(args["createInfoCount"], createInfoCount, json_options);
    FieldToJson(args["pCreateInfos"], pCreateInfos, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pPipelines"], pPipelines, json_options);
    WriteBlockEnd("vkCreateRayTracingPipelinesNV");
}

void VulkanExportDiveConsumer::Process_vkGetRayTracingShaderGroupHandlesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            pipeline,
    uint32_t                                    firstGroup,
    uint32_t                                    groupCount,
    size_t                                      dataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipeline"], pipeline, json_options);
    FieldToJson(args["firstGroup"], firstGroup, json_options);
    FieldToJson(args["groupCount"], groupCount, json_options);
    FieldToJson(args["dataSize"], dataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    WriteBlockEnd("vkGetRayTracingShaderGroupHandlesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetRayTracingShaderGroupHandlesNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            pipeline,
    uint32_t                                    firstGroup,
    uint32_t                                    groupCount,
    size_t                                      dataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipeline"], pipeline, json_options);
    FieldToJson(args["firstGroup"], firstGroup, json_options);
    FieldToJson(args["groupCount"], groupCount, json_options);
    FieldToJson(args["dataSize"], dataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    WriteBlockEnd("vkGetRayTracingShaderGroupHandlesNV");
}

void VulkanExportDiveConsumer::Process_vkGetAccelerationStructureHandleNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            accelerationStructure,
    size_t                                      dataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["accelerationStructure"], accelerationStructure, json_options);
    FieldToJson(args["dataSize"], dataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    WriteBlockEnd("vkGetAccelerationStructureHandleNV");
}

void VulkanExportDiveConsumer::Process_vkCmdWriteAccelerationStructuresPropertiesNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    accelerationStructureCount,
    HandlePointerDecoder<VkAccelerationStructureNV>* pAccelerationStructures,
    VkQueryType                                 queryType,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["accelerationStructureCount"], accelerationStructureCount, json_options);
    HandleToJson(args["pAccelerationStructures"], pAccelerationStructures, json_options);
    FieldToJson(args["queryType"], queryType, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["firstQuery"], firstQuery, json_options);
    util::DiveFunctionData function_data("vkCmdWriteAccelerationStructuresPropertiesNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCompileDeferredNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            pipeline,
    uint32_t                                    shader)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipeline"], pipeline, json_options);
    FieldToJson(args["shader"], shader, json_options);
    WriteBlockEnd("vkCompileDeferredNV");
}

void VulkanExportDiveConsumer::Process_vkGetMemoryHostPointerPropertiesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    uint64_t                                    pHostPointer,
    StructPointerDecoder<Decoded_VkMemoryHostPointerPropertiesEXT>* pMemoryHostPointerProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["handleType"], handleType, json_options);
    FieldToJson(args["pHostPointer"], pHostPointer, json_options);
    FieldToJson(args["pMemoryHostPointerProperties"], pMemoryHostPointerProperties, json_options);
    WriteBlockEnd("vkGetMemoryHostPointerPropertiesEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdWriteBufferMarkerAMD(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlagBits                     pipelineStage,
    format::HandleId                            dstBuffer,
    VkDeviceSize                                dstOffset,
    uint32_t                                    marker)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pipelineStage"], pipelineStage, json_options);
    HandleToJson(args["dstBuffer"], dstBuffer, json_options);
    FieldToJson(args["dstOffset"], dstOffset, json_options);
    FieldToJson(args["marker"], marker, json_options);
    util::DiveFunctionData function_data("vkCmdWriteBufferMarkerAMD", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdWriteBufferMarker2AMD(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlags2                       stage,
    format::HandleId                            dstBuffer,
    VkDeviceSize                                dstOffset,
    uint32_t                                    marker)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkPipelineStageFlags2_t(), args["stage"], stage, json_options);
    HandleToJson(args["dstBuffer"], dstBuffer, json_options);
    FieldToJson(args["dstOffset"], dstOffset, json_options);
    FieldToJson(args["marker"], marker, json_options);
    util::DiveFunctionData function_data("vkCmdWriteBufferMarker2AMD", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pTimeDomainCount,
    PointerDecoder<VkTimeDomainKHR>*            pTimeDomains)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pTimeDomainCount"], pTimeDomainCount, json_options);
    FieldToJson(args["pTimeDomains"], pTimeDomains, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceCalibrateableTimeDomainsEXT");
}

void VulkanExportDiveConsumer::Process_vkGetCalibratedTimestampsEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    timestampCount,
    StructPointerDecoder<Decoded_VkCalibratedTimestampInfoKHR>* pTimestampInfos,
    PointerDecoder<uint64_t>*                   pTimestamps,
    PointerDecoder<uint64_t>*                   pMaxDeviation)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["timestampCount"], timestampCount, json_options);
    FieldToJson(args["pTimestampInfos"], pTimestampInfos, json_options);
    FieldToJson(args["pTimestamps"], pTimestamps, json_options);
    FieldToJson(args["pMaxDeviation"], pMaxDeviation, json_options);
    WriteBlockEnd("vkGetCalibratedTimestampsEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMeshTasksNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    taskCount,
    uint32_t                                    firstTask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["taskCount"], taskCount, json_options);
    FieldToJson(args["firstTask"], firstTask, json_options);
    util::DiveFunctionData function_data("vkCmdDrawMeshTasksNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMeshTasksIndirectNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    FieldToJson(args["drawCount"], drawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawMeshTasksIndirectNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMeshTasksIndirectCountNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    format::HandleId                            countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    HandleToJson(args["countBuffer"], countBuffer, json_options);
    FieldToJson(args["countBufferOffset"], countBufferOffset, json_options);
    FieldToJson(args["maxDrawCount"], maxDrawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawMeshTasksIndirectCountNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetExclusiveScissorEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstExclusiveScissor,
    uint32_t                                    exclusiveScissorCount,
    PointerDecoder<VkBool32>*                   pExclusiveScissorEnables)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstExclusiveScissor"], firstExclusiveScissor, json_options);
    FieldToJson(args["exclusiveScissorCount"], exclusiveScissorCount, json_options);
    Bool32ToJson(args["pExclusiveScissorEnables"], pExclusiveScissorEnables, json_options);
    util::DiveFunctionData function_data("vkCmdSetExclusiveScissorEnableNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetExclusiveScissorNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstExclusiveScissor,
    uint32_t                                    exclusiveScissorCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pExclusiveScissors)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstExclusiveScissor"], firstExclusiveScissor, json_options);
    FieldToJson(args["exclusiveScissorCount"], exclusiveScissorCount, json_options);
    FieldToJson(args["pExclusiveScissors"], pExclusiveScissors, json_options);
    util::DiveFunctionData function_data("vkCmdSetExclusiveScissorNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCheckpointNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint64_t                                    pCheckpointMarker)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pCheckpointMarker"], pCheckpointMarker, json_options);
    util::DiveFunctionData function_data("vkCmdSetCheckpointNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetQueueCheckpointDataNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue,
    PointerDecoder<uint32_t>*                   pCheckpointDataCount,
    StructPointerDecoder<Decoded_VkCheckpointDataNV>* pCheckpointData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    FieldToJson(args["pCheckpointDataCount"], pCheckpointDataCount, json_options);
    FieldToJson(args["pCheckpointData"], pCheckpointData, json_options);
    WriteBlockEnd("vkGetQueueCheckpointDataNV");
}

void VulkanExportDiveConsumer::Process_vkGetQueueCheckpointData2NV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue,
    PointerDecoder<uint32_t>*                   pCheckpointDataCount,
    StructPointerDecoder<Decoded_VkCheckpointData2NV>* pCheckpointData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    FieldToJson(args["pCheckpointDataCount"], pCheckpointDataCount, json_options);
    FieldToJson(args["pCheckpointData"], pCheckpointData, json_options);
    WriteBlockEnd("vkGetQueueCheckpointData2NV");
}

void VulkanExportDiveConsumer::Process_vkInitializePerformanceApiINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkInitializePerformanceApiInfoINTEL>* pInitializeInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInitializeInfo"], pInitializeInfo, json_options);
    WriteBlockEnd("vkInitializePerformanceApiINTEL");
}

void VulkanExportDiveConsumer::Process_vkUninitializePerformanceApiINTEL(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    WriteBlockEnd("vkUninitializePerformanceApiINTEL");
}

void VulkanExportDiveConsumer::Process_vkCmdSetPerformanceMarkerINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPerformanceMarkerInfoINTEL>* pMarkerInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pMarkerInfo"], pMarkerInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetPerformanceMarkerINTEL", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPerformanceStreamMarkerINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPerformanceStreamMarkerInfoINTEL>* pMarkerInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pMarkerInfo"], pMarkerInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetPerformanceStreamMarkerINTEL", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPerformanceOverrideINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPerformanceOverrideInfoINTEL>* pOverrideInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pOverrideInfo"], pOverrideInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetPerformanceOverrideINTEL", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkAcquirePerformanceConfigurationINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPerformanceConfigurationAcquireInfoINTEL>* pAcquireInfo,
    HandlePointerDecoder<VkPerformanceConfigurationINTEL>* pConfiguration)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pAcquireInfo"], pAcquireInfo, json_options);
    HandleToJson(args["pConfiguration"], pConfiguration, json_options);
    WriteBlockEnd("vkAcquirePerformanceConfigurationINTEL");
}

void VulkanExportDiveConsumer::Process_vkReleasePerformanceConfigurationINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            configuration)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["configuration"], configuration, json_options);
    WriteBlockEnd("vkReleasePerformanceConfigurationINTEL");
}

void VulkanExportDiveConsumer::Process_vkQueueSetPerformanceConfigurationINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    format::HandleId                            configuration)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    HandleToJson(args["configuration"], configuration, json_options);
    WriteBlockEnd("vkQueueSetPerformanceConfigurationINTEL");
}

void VulkanExportDiveConsumer::Process_vkGetPerformanceParameterINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkPerformanceParameterTypeINTEL             parameter,
    StructPointerDecoder<Decoded_VkPerformanceValueINTEL>* pValue)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["parameter"], parameter, json_options);
    FieldToJson(args["pValue"], pValue, json_options);
    WriteBlockEnd("vkGetPerformanceParameterINTEL");
}

void VulkanExportDiveConsumer::Process_vkSetLocalDimmingAMD(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            swapChain,
    VkBool32                                    localDimmingEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapChain"], swapChain, json_options);
    Bool32ToJson(args["localDimmingEnable"], localDimmingEnable, json_options);
    WriteBlockEnd("vkSetLocalDimmingAMD");
}

void VulkanExportDiveConsumer::Process_vkCreateImagePipeSurfaceFUCHSIA(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkImagePipeSurfaceCreateInfoFUCHSIA>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateImagePipeSurfaceFUCHSIA");
}

void VulkanExportDiveConsumer::Process_vkCreateMetalSurfaceEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkMetalSurfaceCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateMetalSurfaceEXT");
}

void VulkanExportDiveConsumer::Process_vkGetBufferDeviceAddressEXT(
    const ApiCallInfo&                          call_info,
    VkDeviceAddress                             returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferDeviceAddressInfo>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetBufferDeviceAddressEXT");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceToolPropertiesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pToolCount,
    StructPointerDecoder<Decoded_VkPhysicalDeviceToolProperties>* pToolProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pToolCount"], pToolCount, json_options);
    FieldToJson(args["pToolProperties"], pToolProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceToolPropertiesEXT");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkCooperativeMatrixPropertiesNV>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceCooperativeMatrixPropertiesNV");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pCombinationCount,
    StructPointerDecoder<Decoded_VkFramebufferMixedSamplesCombinationNV>* pCombinations)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pCombinationCount"], pCombinationCount, json_options);
    FieldToJson(args["pCombinations"], pCombinations, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfacePresentModes2EXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSurfaceInfo2KHR>* pSurfaceInfo,
    PointerDecoder<uint32_t>*                   pPresentModeCount,
    PointerDecoder<VkPresentModeKHR>*           pPresentModes)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pSurfaceInfo"], pSurfaceInfo, json_options);
    FieldToJson(args["pPresentModeCount"], pPresentModeCount, json_options);
    FieldToJson(args["pPresentModes"], pPresentModes, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceSurfacePresentModes2EXT");
}

void VulkanExportDiveConsumer::Process_vkAcquireFullScreenExclusiveModeEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    WriteBlockEnd("vkAcquireFullScreenExclusiveModeEXT");
}

void VulkanExportDiveConsumer::Process_vkReleaseFullScreenExclusiveModeEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    WriteBlockEnd("vkReleaseFullScreenExclusiveModeEXT");
}

void VulkanExportDiveConsumer::Process_vkGetDeviceGroupSurfacePresentModes2EXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSurfaceInfo2KHR>* pSurfaceInfo,
    PointerDecoder<VkDeviceGroupPresentModeFlagsKHR>* pModes)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pSurfaceInfo"], pSurfaceInfo, json_options);
    FieldToJson(args["pModes"], pModes, json_options);
    WriteBlockEnd("vkGetDeviceGroupSurfacePresentModes2EXT");
}

void VulkanExportDiveConsumer::Process_vkCreateHeadlessSurfaceEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkHeadlessSurfaceCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateHeadlessSurfaceEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineStippleEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["lineStippleFactor"], lineStippleFactor, json_options);
    FieldToJson(args["lineStipplePattern"], lineStipplePattern, json_options);
    util::DiveFunctionData function_data("vkCmdSetLineStippleEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkResetQueryPoolEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["firstQuery"], firstQuery, json_options);
    FieldToJson(args["queryCount"], queryCount, json_options);
    WriteBlockEnd("vkResetQueryPoolEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdSetCullModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCullModeFlags                             cullMode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkCullModeFlags_t(), args["cullMode"], cullMode, json_options);
    util::DiveFunctionData function_data("vkCmdSetCullModeEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetFrontFaceEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkFrontFace                                 frontFace)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["frontFace"], frontFace, json_options);
    util::DiveFunctionData function_data("vkCmdSetFrontFaceEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPrimitiveTopologyEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPrimitiveTopology                         primitiveTopology)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["primitiveTopology"], primitiveTopology, json_options);
    util::DiveFunctionData function_data("vkCmdSetPrimitiveTopologyEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportWithCountEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkViewport>*   pViewports)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["viewportCount"], viewportCount, json_options);
    FieldToJson(args["pViewports"], pViewports, json_options);
    util::DiveFunctionData function_data("vkCmdSetViewportWithCountEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetScissorWithCountEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    scissorCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pScissors)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["scissorCount"], scissorCount, json_options);
    FieldToJson(args["pScissors"], pScissors, json_options);
    util::DiveFunctionData function_data("vkCmdSetScissorWithCountEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBindVertexBuffers2EXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    HandlePointerDecoder<VkBuffer>*             pBuffers,
    PointerDecoder<VkDeviceSize>*               pOffsets,
    PointerDecoder<VkDeviceSize>*               pSizes,
    PointerDecoder<VkDeviceSize>*               pStrides)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstBinding"], firstBinding, json_options);
    FieldToJson(args["bindingCount"], bindingCount, json_options);
    HandleToJson(args["pBuffers"], pBuffers, json_options);
    FieldToJson(args["pOffsets"], pOffsets, json_options);
    FieldToJson(args["pSizes"], pSizes, json_options);
    FieldToJson(args["pStrides"], pStrides, json_options);
    util::DiveFunctionData function_data("vkCmdBindVertexBuffers2EXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthTestEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthTestEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["depthTestEnable"], depthTestEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthTestEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthWriteEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthWriteEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["depthWriteEnable"], depthWriteEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthWriteEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthCompareOpEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCompareOp                                 depthCompareOp)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["depthCompareOp"], depthCompareOp, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthCompareOpEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBoundsTestEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthBoundsTestEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["depthBoundsTestEnable"], depthBoundsTestEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthBoundsTestEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilTestEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    stencilTestEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["stencilTestEnable"], stencilTestEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetStencilTestEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilOpEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkStencilFaceFlags                          faceMask,
    VkStencilOp                                 failOp,
    VkStencilOp                                 passOp,
    VkStencilOp                                 depthFailOp,
    VkCompareOp                                 compareOp)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkStencilFaceFlags_t(), args["faceMask"], faceMask, json_options);
    FieldToJson(args["failOp"], failOp, json_options);
    FieldToJson(args["passOp"], passOp, json_options);
    FieldToJson(args["depthFailOp"], depthFailOp, json_options);
    FieldToJson(args["compareOp"], compareOp, json_options);
    util::DiveFunctionData function_data("vkCmdSetStencilOpEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCopyMemoryToImageEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyMemoryToImageInfo>* pCopyMemoryToImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCopyMemoryToImageInfo"], pCopyMemoryToImageInfo, json_options);
    WriteBlockEnd("vkCopyMemoryToImageEXT");
}

void VulkanExportDiveConsumer::Process_vkCopyImageToMemoryEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyImageToMemoryInfo>* pCopyImageToMemoryInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCopyImageToMemoryInfo"], pCopyImageToMemoryInfo, json_options);
    WriteBlockEnd("vkCopyImageToMemoryEXT");
}

void VulkanExportDiveConsumer::Process_vkCopyImageToImageEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyImageToImageInfo>* pCopyImageToImageInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCopyImageToImageInfo"], pCopyImageToImageInfo, json_options);
    WriteBlockEnd("vkCopyImageToImageEXT");
}

void VulkanExportDiveConsumer::Process_vkTransitionImageLayoutEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    transitionCount,
    StructPointerDecoder<Decoded_VkHostImageLayoutTransitionInfo>* pTransitions)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["transitionCount"], transitionCount, json_options);
    FieldToJson(args["pTransitions"], pTransitions, json_options);
    WriteBlockEnd("vkTransitionImageLayoutEXT");
}

void VulkanExportDiveConsumer::Process_vkGetImageSubresourceLayout2EXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkImageSubresource2>* pSubresource,
    StructPointerDecoder<Decoded_VkSubresourceLayout2>* pLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["image"], image, json_options);
    FieldToJson(args["pSubresource"], pSubresource, json_options);
    FieldToJson(args["pLayout"], pLayout, json_options);
    WriteBlockEnd("vkGetImageSubresourceLayout2EXT");
}

void VulkanExportDiveConsumer::Process_vkReleaseSwapchainImagesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkReleaseSwapchainImagesInfoEXT>* pReleaseInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pReleaseInfo"], pReleaseInfo, json_options);
    WriteBlockEnd("vkReleaseSwapchainImagesEXT");
}

void VulkanExportDiveConsumer::Process_vkGetGeneratedCommandsMemoryRequirementsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkGeneratedCommandsMemoryRequirementsInfoNV>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetGeneratedCommandsMemoryRequirementsNV");
}

void VulkanExportDiveConsumer::Process_vkCmdPreprocessGeneratedCommandsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkGeneratedCommandsInfoNV>* pGeneratedCommandsInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pGeneratedCommandsInfo"], pGeneratedCommandsInfo, json_options);
    util::DiveFunctionData function_data("vkCmdPreprocessGeneratedCommandsNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdExecuteGeneratedCommandsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    isPreprocessed,
    StructPointerDecoder<Decoded_VkGeneratedCommandsInfoNV>* pGeneratedCommandsInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["isPreprocessed"], isPreprocessed, json_options);
    FieldToJson(args["pGeneratedCommandsInfo"], pGeneratedCommandsInfo, json_options);
    util::DiveFunctionData function_data("vkCmdExecuteGeneratedCommandsNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdBindPipelineShaderGroupNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    format::HandleId                            pipeline,
    uint32_t                                    groupIndex)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pipelineBindPoint"], pipelineBindPoint, json_options);
    HandleToJson(args["pipeline"], pipeline, json_options);
    FieldToJson(args["groupIndex"], groupIndex, json_options);
    util::DiveFunctionData function_data("vkCmdBindPipelineShaderGroupNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCreateIndirectCommandsLayoutNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkIndirectCommandsLayoutCreateInfoNV>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkIndirectCommandsLayoutNV>* pIndirectCommandsLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pIndirectCommandsLayout"], pIndirectCommandsLayout, json_options);
    WriteBlockEnd("vkCreateIndirectCommandsLayoutNV");
}

void VulkanExportDiveConsumer::Process_vkDestroyIndirectCommandsLayoutNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            indirectCommandsLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["indirectCommandsLayout"], indirectCommandsLayout, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyIndirectCommandsLayoutNV");
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBias2EXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDepthBiasInfoEXT>* pDepthBiasInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pDepthBiasInfo"], pDepthBiasInfo, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthBias2EXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkAcquireDrmDisplayEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    int32_t                                     drmFd,
    format::HandleId                            display)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["drmFd"], drmFd, json_options);
    HandleToJson(args["display"], display, json_options);
    WriteBlockEnd("vkAcquireDrmDisplayEXT");
}

void VulkanExportDiveConsumer::Process_vkGetDrmDisplayEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    int32_t                                     drmFd,
    uint32_t                                    connectorId,
    HandlePointerDecoder<VkDisplayKHR>*         display)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["drmFd"], drmFd, json_options);
    FieldToJson(args["connectorId"], connectorId, json_options);
    HandleToJson(args["display"], display, json_options);
    WriteBlockEnd("vkGetDrmDisplayEXT");
}

void VulkanExportDiveConsumer::Process_vkCreatePrivateDataSlotEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPrivateDataSlotCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPrivateDataSlot>*    pPrivateDataSlot)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pPrivateDataSlot"], pPrivateDataSlot, json_options);
    WriteBlockEnd("vkCreatePrivateDataSlotEXT");
}

void VulkanExportDiveConsumer::Process_vkDestroyPrivateDataSlotEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            privateDataSlot,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["privateDataSlot"], privateDataSlot, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyPrivateDataSlotEXT");
}

void VulkanExportDiveConsumer::Process_vkSetPrivateDataEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    format::HandleId                            privateDataSlot,
    uint64_t                                    data)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["objectType"], objectType, json_options);
    HandleToJson(args["objectHandle"], objectHandle, json_options);
    HandleToJson(args["privateDataSlot"], privateDataSlot, json_options);
    FieldToJson(args["data"], data, json_options);
    WriteBlockEnd("vkSetPrivateDataEXT");
}

void VulkanExportDiveConsumer::Process_vkGetPrivateDataEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    format::HandleId                            privateDataSlot,
    PointerDecoder<uint64_t>*                   pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["objectType"], objectType, json_options);
    HandleToJson(args["objectHandle"], objectHandle, json_options);
    HandleToJson(args["privateDataSlot"], privateDataSlot, json_options);
    FieldToJson(args["pData"], pData, json_options);
    WriteBlockEnd("vkGetPrivateDataEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdSetFragmentShadingRateEnumNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkFragmentShadingRateNV                     shadingRate,
    PointerDecoder<VkFragmentShadingRateCombinerOpKHR>* combinerOps)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["shadingRate"], shadingRate, json_options);
    FieldToJson(args["combinerOps"], combinerOps, json_options);
    util::DiveFunctionData function_data("vkCmdSetFragmentShadingRateEnumNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceFaultInfoEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceFaultCountsEXT>* pFaultCounts,
    StructPointerDecoder<Decoded_VkDeviceFaultInfoEXT>* pFaultInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pFaultCounts"], pFaultCounts, json_options);
    FieldToJson(args["pFaultInfo"], pFaultInfo, json_options);
    WriteBlockEnd("vkGetDeviceFaultInfoEXT");
}

void VulkanExportDiveConsumer::Process_vkAcquireWinrtDisplayNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            display)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    HandleToJson(args["display"], display, json_options);
    WriteBlockEnd("vkAcquireWinrtDisplayNV");
}

void VulkanExportDiveConsumer::Process_vkGetWinrtDisplayNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    HandlePointerDecoder<VkDisplayKHR>*         pDisplay)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["deviceRelativeId"], deviceRelativeId, json_options);
    HandleToJson(args["pDisplay"], pDisplay, json_options);
    WriteBlockEnd("vkGetWinrtDisplayNV");
}

void VulkanExportDiveConsumer::Process_vkCreateDirectFBSurfaceEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkDirectFBSurfaceCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateDirectFBSurfaceEXT");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceDirectFBPresentationSupportEXT(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint64_t                                    dfb)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["queueFamilyIndex"], queueFamilyIndex, json_options);
    FieldToJson(args["dfb"], dfb, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceDirectFBPresentationSupportEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdSetVertexInputEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    vertexBindingDescriptionCount,
    StructPointerDecoder<Decoded_VkVertexInputBindingDescription2EXT>* pVertexBindingDescriptions,
    uint32_t                                    vertexAttributeDescriptionCount,
    StructPointerDecoder<Decoded_VkVertexInputAttributeDescription2EXT>* pVertexAttributeDescriptions)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["vertexBindingDescriptionCount"], vertexBindingDescriptionCount, json_options);
    FieldToJson(args["pVertexBindingDescriptions"], pVertexBindingDescriptions, json_options);
    FieldToJson(args["vertexAttributeDescriptionCount"], vertexAttributeDescriptionCount, json_options);
    FieldToJson(args["pVertexAttributeDescriptions"], pVertexAttributeDescriptions, json_options);
    util::DiveFunctionData function_data("vkCmdSetVertexInputEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryZirconHandleFUCHSIA(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetZirconHandleInfoFUCHSIA>* pGetZirconHandleInfo,
    PointerDecoder<uint32_t>*                   pZirconHandle)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pGetZirconHandleInfo"], pGetZirconHandleInfo, json_options);
    FieldToJson(args["pZirconHandle"], pZirconHandle, json_options);
    WriteBlockEnd("vkGetMemoryZirconHandleFUCHSIA");
}

void VulkanExportDiveConsumer::Process_vkGetMemoryZirconHandlePropertiesFUCHSIA(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    uint32_t                                    zirconHandle,
    StructPointerDecoder<Decoded_VkMemoryZirconHandlePropertiesFUCHSIA>* pMemoryZirconHandleProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["handleType"], handleType, json_options);
    FieldToJson(args["zirconHandle"], zirconHandle, json_options);
    FieldToJson(args["pMemoryZirconHandleProperties"], pMemoryZirconHandleProperties, json_options);
    WriteBlockEnd("vkGetMemoryZirconHandlePropertiesFUCHSIA");
}

void VulkanExportDiveConsumer::Process_vkImportSemaphoreZirconHandleFUCHSIA(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImportSemaphoreZirconHandleInfoFUCHSIA>* pImportSemaphoreZirconHandleInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pImportSemaphoreZirconHandleInfo"], pImportSemaphoreZirconHandleInfo, json_options);
    WriteBlockEnd("vkImportSemaphoreZirconHandleFUCHSIA");
}

void VulkanExportDiveConsumer::Process_vkGetSemaphoreZirconHandleFUCHSIA(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreGetZirconHandleInfoFUCHSIA>* pGetZirconHandleInfo,
    PointerDecoder<uint32_t>*                   pZirconHandle)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pGetZirconHandleInfo"], pGetZirconHandleInfo, json_options);
    FieldToJson(args["pZirconHandle"], pZirconHandle, json_options);
    WriteBlockEnd("vkGetSemaphoreZirconHandleFUCHSIA");
}

void VulkanExportDiveConsumer::Process_vkCmdBindInvocationMaskHUAWEI(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            imageView,
    VkImageLayout                               imageLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["imageView"], imageView, json_options);
    FieldToJson(args["imageLayout"], imageLayout, json_options);
    util::DiveFunctionData function_data("vkCmdBindInvocationMaskHUAWEI", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryRemoteAddressNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetRemoteAddressInfoNV>* pMemoryGetRemoteAddressInfo,
    PointerDecoder<uint64_t, void*>*            pAddress)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pMemoryGetRemoteAddressInfo"], pMemoryGetRemoteAddressInfo, json_options);
    FieldToJson(args["pAddress"], pAddress, json_options);
    WriteBlockEnd("vkGetMemoryRemoteAddressNV");
}

void VulkanExportDiveConsumer::Process_vkCmdSetPatchControlPointsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    patchControlPoints)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["patchControlPoints"], patchControlPoints, json_options);
    util::DiveFunctionData function_data("vkCmdSetPatchControlPointsEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRasterizerDiscardEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    rasterizerDiscardEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["rasterizerDiscardEnable"], rasterizerDiscardEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetRasterizerDiscardEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBiasEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthBiasEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["depthBiasEnable"], depthBiasEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthBiasEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLogicOpEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkLogicOp                                   logicOp)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["logicOp"], logicOp, json_options);
    util::DiveFunctionData function_data("vkCmdSetLogicOpEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPrimitiveRestartEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    primitiveRestartEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["primitiveRestartEnable"], primitiveRestartEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetPrimitiveRestartEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCreateScreenSurfaceQNX(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkScreenSurfaceCreateInfoQNX>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["instance"], instance, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSurface"], pSurface, json_options);
    WriteBlockEnd("vkCreateScreenSurfaceQNX");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceScreenPresentationSupportQNX(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint64_t                                    window)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["queueFamilyIndex"], queueFamilyIndex, json_options);
    FieldToJson(args["window"], window, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceScreenPresentationSupportQNX");
}

void VulkanExportDiveConsumer::Process_vkCmdSetColorWriteEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    attachmentCount,
    PointerDecoder<VkBool32>*                   pColorWriteEnables)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["attachmentCount"], attachmentCount, json_options);
    Bool32ToJson(args["pColorWriteEnables"], pColorWriteEnables, json_options);
    util::DiveFunctionData function_data("vkCmdSetColorWriteEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMultiEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    drawCount,
    StructPointerDecoder<Decoded_VkMultiDrawInfoEXT>* pVertexInfo,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["drawCount"], drawCount, json_options);
    FieldToJson(args["pVertexInfo"], pVertexInfo, json_options);
    FieldToJson(args["instanceCount"], instanceCount, json_options);
    FieldToJson(args["firstInstance"], firstInstance, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawMultiEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMultiIndexedEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    drawCount,
    StructPointerDecoder<Decoded_VkMultiDrawIndexedInfoEXT>* pIndexInfo,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    uint32_t                                    stride,
    PointerDecoder<int32_t>*                    pVertexOffset)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["drawCount"], drawCount, json_options);
    FieldToJson(args["pIndexInfo"], pIndexInfo, json_options);
    FieldToJson(args["instanceCount"], instanceCount, json_options);
    FieldToJson(args["firstInstance"], firstInstance, json_options);
    FieldToJson(args["stride"], stride, json_options);
    FieldToJson(args["pVertexOffset"], pVertexOffset, json_options);
    util::DiveFunctionData function_data("vkCmdDrawMultiIndexedEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCreateMicromapEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMicromapCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkMicromapEXT>*        pMicromap)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pMicromap"], pMicromap, json_options);
    WriteBlockEnd("vkCreateMicromapEXT");
}

void VulkanExportDiveConsumer::Process_vkDestroyMicromapEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            micromap,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["micromap"], micromap, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyMicromapEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdBuildMicromapsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    infoCount,
    StructPointerDecoder<Decoded_VkMicromapBuildInfoEXT>* pInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["infoCount"], infoCount, json_options);
    FieldToJson(args["pInfos"], pInfos, json_options);
    util::DiveFunctionData function_data("vkCmdBuildMicromapsEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkBuildMicromapsEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    uint32_t                                    infoCount,
    StructPointerDecoder<Decoded_VkMicromapBuildInfoEXT>* pInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["deferredOperation"], deferredOperation, json_options);
    FieldToJson(args["infoCount"], infoCount, json_options);
    FieldToJson(args["pInfos"], pInfos, json_options);
    WriteBlockEnd("vkBuildMicromapsEXT");
}

void VulkanExportDiveConsumer::Process_vkCopyMicromapEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    StructPointerDecoder<Decoded_VkCopyMicromapInfoEXT>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["deferredOperation"], deferredOperation, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkCopyMicromapEXT");
}

void VulkanExportDiveConsumer::Process_vkCopyMicromapToMemoryEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    StructPointerDecoder<Decoded_VkCopyMicromapToMemoryInfoEXT>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["deferredOperation"], deferredOperation, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkCopyMicromapToMemoryEXT");
}

void VulkanExportDiveConsumer::Process_vkCopyMemoryToMicromapEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    StructPointerDecoder<Decoded_VkCopyMemoryToMicromapInfoEXT>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["deferredOperation"], deferredOperation, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkCopyMemoryToMicromapEXT");
}

void VulkanExportDiveConsumer::Process_vkWriteMicromapsPropertiesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    micromapCount,
    HandlePointerDecoder<VkMicromapEXT>*        pMicromaps,
    VkQueryType                                 queryType,
    size_t                                      dataSize,
    PointerDecoder<uint8_t>*                    pData,
    size_t                                      stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["micromapCount"], micromapCount, json_options);
    HandleToJson(args["pMicromaps"], pMicromaps, json_options);
    FieldToJson(args["queryType"], queryType, json_options);
    FieldToJson(args["dataSize"], dataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    FieldToJson(args["stride"], stride, json_options);
    WriteBlockEnd("vkWriteMicromapsPropertiesEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdCopyMicromapEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyMicromapInfoEXT>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyMicromapEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyMicromapToMemoryEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyMicromapToMemoryInfoEXT>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyMicromapToMemoryEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyMemoryToMicromapEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyMemoryToMicromapInfoEXT>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyMemoryToMicromapEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdWriteMicromapsPropertiesEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    micromapCount,
    HandlePointerDecoder<VkMicromapEXT>*        pMicromaps,
    VkQueryType                                 queryType,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["micromapCount"], micromapCount, json_options);
    HandleToJson(args["pMicromaps"], pMicromaps, json_options);
    FieldToJson(args["queryType"], queryType, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["firstQuery"], firstQuery, json_options);
    util::DiveFunctionData function_data("vkCmdWriteMicromapsPropertiesEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceMicromapCompatibilityEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMicromapVersionInfoEXT>* pVersionInfo,
    PointerDecoder<VkAccelerationStructureCompatibilityKHR>* pCompatibility)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pVersionInfo"], pVersionInfo, json_options);
    FieldToJson(args["pCompatibility"], pCompatibility, json_options);
    WriteBlockEnd("vkGetDeviceMicromapCompatibilityEXT");
}

void VulkanExportDiveConsumer::Process_vkGetMicromapBuildSizesEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    VkAccelerationStructureBuildTypeKHR         buildType,
    StructPointerDecoder<Decoded_VkMicromapBuildInfoEXT>* pBuildInfo,
    StructPointerDecoder<Decoded_VkMicromapBuildSizesInfoEXT>* pSizeInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["buildType"], buildType, json_options);
    FieldToJson(args["pBuildInfo"], pBuildInfo, json_options);
    FieldToJson(args["pSizeInfo"], pSizeInfo, json_options);
    WriteBlockEnd("vkGetMicromapBuildSizesEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdDrawClusterHUAWEI(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["groupCountX"], groupCountX, json_options);
    FieldToJson(args["groupCountY"], groupCountY, json_options);
    FieldToJson(args["groupCountZ"], groupCountZ, json_options);
    util::DiveFunctionData function_data("vkCmdDrawClusterHUAWEI", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawClusterIndirectHUAWEI(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    util::DiveFunctionData function_data("vkCmdDrawClusterIndirectHUAWEI", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkSetDeviceMemoryPriorityEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            memory,
    float                                       priority)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["memory"], memory, json_options);
    FieldToJson(args["priority"], priority, json_options);
    WriteBlockEnd("vkSetDeviceMemoryPriorityEXT");
}

void VulkanExportDiveConsumer::Process_vkGetDescriptorSetLayoutHostMappingInfoVALVE(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorSetBindingReferenceVALVE>* pBindingReference,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutHostMappingInfoVALVE>* pHostMapping)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pBindingReference"], pBindingReference, json_options);
    FieldToJson(args["pHostMapping"], pHostMapping, json_options);
    WriteBlockEnd("vkGetDescriptorSetLayoutHostMappingInfoVALVE");
}

void VulkanExportDiveConsumer::Process_vkGetDescriptorSetHostMappingVALVE(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            descriptorSet,
    PointerDecoder<uint64_t, void*>*            ppData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["descriptorSet"], descriptorSet, json_options);
    FieldToJsonAsHex(args["ppData"], ppData, json_options);
    WriteBlockEnd("vkGetDescriptorSetHostMappingVALVE");
}

void VulkanExportDiveConsumer::Process_vkGetPipelineIndirectMemoryRequirementsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkComputePipelineCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetPipelineIndirectMemoryRequirementsNV");
}

void VulkanExportDiveConsumer::Process_vkCmdUpdatePipelineIndirectBufferNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    format::HandleId                            pipeline)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pipelineBindPoint"], pipelineBindPoint, json_options);
    HandleToJson(args["pipeline"], pipeline, json_options);
    util::DiveFunctionData function_data("vkCmdUpdatePipelineIndirectBufferNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetPipelineIndirectDeviceAddressNV(
    const ApiCallInfo&                          call_info,
    VkDeviceAddress                             returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineIndirectDeviceAddressInfoNV>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetPipelineIndirectDeviceAddressNV");
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthClampEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthClampEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["depthClampEnable"], depthClampEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthClampEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPolygonModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPolygonMode                               polygonMode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["polygonMode"], polygonMode, json_options);
    util::DiveFunctionData function_data("vkCmdSetPolygonModeEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRasterizationSamplesEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkSampleCountFlagBits                       rasterizationSamples)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["rasterizationSamples"], rasterizationSamples, json_options);
    util::DiveFunctionData function_data("vkCmdSetRasterizationSamplesEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetSampleMaskEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkSampleCountFlagBits                       samples,
    PointerDecoder<VkSampleMask>*               pSampleMask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["samples"], samples, json_options);
    FieldToJson(args["pSampleMask"], pSampleMask, json_options);
    util::DiveFunctionData function_data("vkCmdSetSampleMaskEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetAlphaToCoverageEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    alphaToCoverageEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["alphaToCoverageEnable"], alphaToCoverageEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetAlphaToCoverageEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetAlphaToOneEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    alphaToOneEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["alphaToOneEnable"], alphaToOneEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetAlphaToOneEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLogicOpEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    logicOpEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["logicOpEnable"], logicOpEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetLogicOpEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetColorBlendEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    PointerDecoder<VkBool32>*                   pColorBlendEnables)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstAttachment"], firstAttachment, json_options);
    FieldToJson(args["attachmentCount"], attachmentCount, json_options);
    Bool32ToJson(args["pColorBlendEnables"], pColorBlendEnables, json_options);
    util::DiveFunctionData function_data("vkCmdSetColorBlendEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetColorBlendEquationEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    StructPointerDecoder<Decoded_VkColorBlendEquationEXT>* pColorBlendEquations)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstAttachment"], firstAttachment, json_options);
    FieldToJson(args["attachmentCount"], attachmentCount, json_options);
    FieldToJson(args["pColorBlendEquations"], pColorBlendEquations, json_options);
    util::DiveFunctionData function_data("vkCmdSetColorBlendEquationEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetColorWriteMaskEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    PointerDecoder<VkColorComponentFlags>*      pColorWriteMasks)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstAttachment"], firstAttachment, json_options);
    FieldToJson(args["attachmentCount"], attachmentCount, json_options);
    FieldToJson(args["pColorWriteMasks"], pColorWriteMasks, json_options);
    util::DiveFunctionData function_data("vkCmdSetColorWriteMaskEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetTessellationDomainOriginEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkTessellationDomainOrigin                  domainOrigin)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["domainOrigin"], domainOrigin, json_options);
    util::DiveFunctionData function_data("vkCmdSetTessellationDomainOriginEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRasterizationStreamEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    rasterizationStream)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["rasterizationStream"], rasterizationStream, json_options);
    util::DiveFunctionData function_data("vkCmdSetRasterizationStreamEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetConservativeRasterizationModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkConservativeRasterizationModeEXT          conservativeRasterizationMode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["conservativeRasterizationMode"], conservativeRasterizationMode, json_options);
    util::DiveFunctionData function_data("vkCmdSetConservativeRasterizationModeEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetExtraPrimitiveOverestimationSizeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    float                                       extraPrimitiveOverestimationSize)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["extraPrimitiveOverestimationSize"], extraPrimitiveOverestimationSize, json_options);
    util::DiveFunctionData function_data("vkCmdSetExtraPrimitiveOverestimationSizeEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthClipEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthClipEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["depthClipEnable"], depthClipEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthClipEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetSampleLocationsEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    sampleLocationsEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["sampleLocationsEnable"], sampleLocationsEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetSampleLocationsEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetColorBlendAdvancedEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    StructPointerDecoder<Decoded_VkColorBlendAdvancedEXT>* pColorBlendAdvanced)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstAttachment"], firstAttachment, json_options);
    FieldToJson(args["attachmentCount"], attachmentCount, json_options);
    FieldToJson(args["pColorBlendAdvanced"], pColorBlendAdvanced, json_options);
    util::DiveFunctionData function_data("vkCmdSetColorBlendAdvancedEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetProvokingVertexModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkProvokingVertexModeEXT                    provokingVertexMode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["provokingVertexMode"], provokingVertexMode, json_options);
    util::DiveFunctionData function_data("vkCmdSetProvokingVertexModeEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineRasterizationModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkLineRasterizationModeEXT                  lineRasterizationMode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["lineRasterizationMode"], lineRasterizationMode, json_options);
    util::DiveFunctionData function_data("vkCmdSetLineRasterizationModeEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineStippleEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    stippledLineEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["stippledLineEnable"], stippledLineEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetLineStippleEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthClipNegativeOneToOneEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    negativeOneToOne)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["negativeOneToOne"], negativeOneToOne, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthClipNegativeOneToOneEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportWScalingEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    viewportWScalingEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["viewportWScalingEnable"], viewportWScalingEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetViewportWScalingEnableNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportSwizzleNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkViewportSwizzleNV>* pViewportSwizzles)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["firstViewport"], firstViewport, json_options);
    FieldToJson(args["viewportCount"], viewportCount, json_options);
    FieldToJson(args["pViewportSwizzles"], pViewportSwizzles, json_options);
    util::DiveFunctionData function_data("vkCmdSetViewportSwizzleNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageToColorEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    coverageToColorEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["coverageToColorEnable"], coverageToColorEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetCoverageToColorEnableNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageToColorLocationNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    coverageToColorLocation)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["coverageToColorLocation"], coverageToColorLocation, json_options);
    util::DiveFunctionData function_data("vkCmdSetCoverageToColorLocationNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageModulationModeNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCoverageModulationModeNV                  coverageModulationMode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["coverageModulationMode"], coverageModulationMode, json_options);
    util::DiveFunctionData function_data("vkCmdSetCoverageModulationModeNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageModulationTableEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    coverageModulationTableEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["coverageModulationTableEnable"], coverageModulationTableEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetCoverageModulationTableEnableNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageModulationTableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    coverageModulationTableCount,
    PointerDecoder<float>*                      pCoverageModulationTable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["coverageModulationTableCount"], coverageModulationTableCount, json_options);
    FieldToJson(args["pCoverageModulationTable"], pCoverageModulationTable, json_options);
    util::DiveFunctionData function_data("vkCmdSetCoverageModulationTableNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetShadingRateImageEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    shadingRateImageEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["shadingRateImageEnable"], shadingRateImageEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetShadingRateImageEnableNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRepresentativeFragmentTestEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    representativeFragmentTestEnable)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["representativeFragmentTestEnable"], representativeFragmentTestEnable, json_options);
    util::DiveFunctionData function_data("vkCmdSetRepresentativeFragmentTestEnableNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageReductionModeNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCoverageReductionModeNV                   coverageReductionMode)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["coverageReductionMode"], coverageReductionMode, json_options);
    util::DiveFunctionData function_data("vkCmdSetCoverageReductionModeNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetShaderModuleIdentifierEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            shaderModule,
    StructPointerDecoder<Decoded_VkShaderModuleIdentifierEXT>* pIdentifier)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["shaderModule"], shaderModule, json_options);
    FieldToJson(args["pIdentifier"], pIdentifier, json_options);
    WriteBlockEnd("vkGetShaderModuleIdentifierEXT");
}

void VulkanExportDiveConsumer::Process_vkGetShaderModuleCreateInfoIdentifierEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkShaderModuleCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkShaderModuleIdentifierEXT>* pIdentifier)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pIdentifier"], pIdentifier, json_options);
    WriteBlockEnd("vkGetShaderModuleCreateInfoIdentifierEXT");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceOpticalFlowImageFormatsNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkOpticalFlowImageFormatInfoNV>* pOpticalFlowImageFormatInfo,
    PointerDecoder<uint32_t>*                   pFormatCount,
    StructPointerDecoder<Decoded_VkOpticalFlowImageFormatPropertiesNV>* pImageFormatProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pOpticalFlowImageFormatInfo"], pOpticalFlowImageFormatInfo, json_options);
    FieldToJson(args["pFormatCount"], pFormatCount, json_options);
    FieldToJson(args["pImageFormatProperties"], pImageFormatProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceOpticalFlowImageFormatsNV");
}

void VulkanExportDiveConsumer::Process_vkCreateOpticalFlowSessionNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkOpticalFlowSessionCreateInfoNV>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkOpticalFlowSessionNV>* pSession)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pSession"], pSession, json_options);
    WriteBlockEnd("vkCreateOpticalFlowSessionNV");
}

void VulkanExportDiveConsumer::Process_vkDestroyOpticalFlowSessionNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            session,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["session"], session, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyOpticalFlowSessionNV");
}

void VulkanExportDiveConsumer::Process_vkBindOpticalFlowSessionImageNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            session,
    VkOpticalFlowSessionBindingPointNV          bindingPoint,
    format::HandleId                            view,
    VkImageLayout                               layout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["session"], session, json_options);
    FieldToJson(args["bindingPoint"], bindingPoint, json_options);
    HandleToJson(args["view"], view, json_options);
    FieldToJson(args["layout"], layout, json_options);
    WriteBlockEnd("vkBindOpticalFlowSessionImageNV");
}

void VulkanExportDiveConsumer::Process_vkCmdOpticalFlowExecuteNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            session,
    StructPointerDecoder<Decoded_VkOpticalFlowExecuteInfoNV>* pExecuteInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["session"], session, json_options);
    FieldToJson(args["pExecuteInfo"], pExecuteInfo, json_options);
    util::DiveFunctionData function_data("vkCmdOpticalFlowExecuteNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkAntiLagUpdateAMD(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAntiLagDataAMD>* pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pData"], pData, json_options);
    WriteBlockEnd("vkAntiLagUpdateAMD");
}

void VulkanExportDiveConsumer::Process_vkCreateShadersEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    createInfoCount,
    StructPointerDecoder<Decoded_VkShaderCreateInfoEXT>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkShaderEXT>*          pShaders)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["createInfoCount"], createInfoCount, json_options);
    FieldToJson(args["pCreateInfos"], pCreateInfos, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pShaders"], pShaders, json_options);
    WriteBlockEnd("vkCreateShadersEXT");
}

void VulkanExportDiveConsumer::Process_vkDestroyShaderEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            shader,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["shader"], shader, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyShaderEXT");
}

void VulkanExportDiveConsumer::Process_vkGetShaderBinaryDataEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            shader,
    PointerDecoder<size_t>*                     pDataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["shader"], shader, json_options);
    FieldToJson(args["pDataSize"], pDataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    WriteBlockEnd("vkGetShaderBinaryDataEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdBindShadersEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    stageCount,
    PointerDecoder<VkShaderStageFlagBits>*      pStages,
    HandlePointerDecoder<VkShaderEXT>*          pShaders)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["stageCount"], stageCount, json_options);
    FieldToJson(args["pStages"], pStages, json_options);
    HandleToJson(args["pShaders"], pShaders, json_options);
    util::DiveFunctionData function_data("vkCmdBindShadersEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthClampRangeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkDepthClampModeEXT                         depthClampMode,
    StructPointerDecoder<Decoded_VkDepthClampRangeEXT>* pDepthClampRange)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["depthClampMode"], depthClampMode, json_options);
    FieldToJson(args["pDepthClampRange"], pDepthClampRange, json_options);
    util::DiveFunctionData function_data("vkCmdSetDepthClampRangeEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetFramebufferTilePropertiesQCOM(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            framebuffer,
    PointerDecoder<uint32_t>*                   pPropertiesCount,
    StructPointerDecoder<Decoded_VkTilePropertiesQCOM>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["framebuffer"], framebuffer, json_options);
    FieldToJson(args["pPropertiesCount"], pPropertiesCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetFramebufferTilePropertiesQCOM");
}

void VulkanExportDiveConsumer::Process_vkGetDynamicRenderingTilePropertiesQCOM(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderingInfo>* pRenderingInfo,
    StructPointerDecoder<Decoded_VkTilePropertiesQCOM>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pRenderingInfo"], pRenderingInfo, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetDynamicRenderingTilePropertiesQCOM");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCooperativeVectorPropertiesNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkCooperativeVectorPropertiesNV>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceCooperativeVectorPropertiesNV");
}

void VulkanExportDiveConsumer::Process_vkConvertCooperativeVectorMatrixNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkConvertCooperativeVectorMatrixInfoNV>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkConvertCooperativeVectorMatrixNV");
}

void VulkanExportDiveConsumer::Process_vkCmdConvertCooperativeVectorMatrixNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    infoCount,
    StructPointerDecoder<Decoded_VkConvertCooperativeVectorMatrixInfoNV>* pInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["infoCount"], infoCount, json_options);
    FieldToJson(args["pInfos"], pInfos, json_options);
    util::DiveFunctionData function_data("vkCmdConvertCooperativeVectorMatrixNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkSetLatencySleepModeNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkLatencySleepModeInfoNV>* pSleepModeInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["pSleepModeInfo"], pSleepModeInfo, json_options);
    WriteBlockEnd("vkSetLatencySleepModeNV");
}

void VulkanExportDiveConsumer::Process_vkLatencySleepNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkLatencySleepInfoNV>* pSleepInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["pSleepInfo"], pSleepInfo, json_options);
    WriteBlockEnd("vkLatencySleepNV");
}

void VulkanExportDiveConsumer::Process_vkSetLatencyMarkerNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkSetLatencyMarkerInfoNV>* pLatencyMarkerInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["pLatencyMarkerInfo"], pLatencyMarkerInfo, json_options);
    WriteBlockEnd("vkSetLatencyMarkerNV");
}

void VulkanExportDiveConsumer::Process_vkGetLatencyTimingsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkGetLatencyMarkerInfoNV>* pLatencyMarkerInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["swapchain"], swapchain, json_options);
    FieldToJson(args["pLatencyMarkerInfo"], pLatencyMarkerInfo, json_options);
    WriteBlockEnd("vkGetLatencyTimingsNV");
}

void VulkanExportDiveConsumer::Process_vkQueueNotifyOutOfBandNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue,
    StructPointerDecoder<Decoded_VkOutOfBandQueueTypeInfoNV>* pQueueTypeInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["queue"], queue, json_options);
    FieldToJson(args["pQueueTypeInfo"], pQueueTypeInfo, json_options);
    WriteBlockEnd("vkQueueNotifyOutOfBandNV");
}

void VulkanExportDiveConsumer::Process_vkCmdSetAttachmentFeedbackLoopEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkImageAspectFlags                          aspectMask)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(VkImageAspectFlags_t(), args["aspectMask"], aspectMask, json_options);
    util::DiveFunctionData function_data("vkCmdSetAttachmentFeedbackLoopEnableEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetPartitionedAccelerationStructuresBuildSizesNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPartitionedAccelerationStructureInstancesInputNV>* pInfo,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildSizesInfoKHR>* pSizeInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pSizeInfo"], pSizeInfo, json_options);
    WriteBlockEnd("vkGetPartitionedAccelerationStructuresBuildSizesNV");
}

void VulkanExportDiveConsumer::Process_vkCmdBuildPartitionedAccelerationStructuresNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBuildPartitionedAccelerationStructureInfoNV>* pBuildInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pBuildInfo"], pBuildInfo, json_options);
    util::DiveFunctionData function_data("vkCmdBuildPartitionedAccelerationStructuresNV", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetGeneratedCommandsMemoryRequirementsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkGeneratedCommandsMemoryRequirementsInfoEXT>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    FieldToJson(args["pMemoryRequirements"], pMemoryRequirements, json_options);
    WriteBlockEnd("vkGetGeneratedCommandsMemoryRequirementsEXT");
}

void VulkanExportDiveConsumer::Process_vkCmdPreprocessGeneratedCommandsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkGeneratedCommandsInfoEXT>* pGeneratedCommandsInfo,
    format::HandleId                            stateCommandBuffer)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pGeneratedCommandsInfo"], pGeneratedCommandsInfo, json_options);
    HandleToJson(args["stateCommandBuffer"], stateCommandBuffer, json_options);
    util::DiveFunctionData function_data("vkCmdPreprocessGeneratedCommandsEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdExecuteGeneratedCommandsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    isPreprocessed,
    StructPointerDecoder<Decoded_VkGeneratedCommandsInfoEXT>* pGeneratedCommandsInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    Bool32ToJson(args["isPreprocessed"], isPreprocessed, json_options);
    FieldToJson(args["pGeneratedCommandsInfo"], pGeneratedCommandsInfo, json_options);
    util::DiveFunctionData function_data("vkCmdExecuteGeneratedCommandsEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCreateIndirectCommandsLayoutEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkIndirectCommandsLayoutCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkIndirectCommandsLayoutEXT>* pIndirectCommandsLayout)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pIndirectCommandsLayout"], pIndirectCommandsLayout, json_options);
    WriteBlockEnd("vkCreateIndirectCommandsLayoutEXT");
}

void VulkanExportDiveConsumer::Process_vkDestroyIndirectCommandsLayoutEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            indirectCommandsLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["indirectCommandsLayout"], indirectCommandsLayout, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyIndirectCommandsLayoutEXT");
}

void VulkanExportDiveConsumer::Process_vkCreateIndirectExecutionSetEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkIndirectExecutionSetCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkIndirectExecutionSetEXT>* pIndirectExecutionSet)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pIndirectExecutionSet"], pIndirectExecutionSet, json_options);
    WriteBlockEnd("vkCreateIndirectExecutionSetEXT");
}

void VulkanExportDiveConsumer::Process_vkDestroyIndirectExecutionSetEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            indirectExecutionSet,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["indirectExecutionSet"], indirectExecutionSet, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyIndirectExecutionSetEXT");
}

void VulkanExportDiveConsumer::Process_vkUpdateIndirectExecutionSetPipelineEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            indirectExecutionSet,
    uint32_t                                    executionSetWriteCount,
    StructPointerDecoder<Decoded_VkWriteIndirectExecutionSetPipelineEXT>* pExecutionSetWrites)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["indirectExecutionSet"], indirectExecutionSet, json_options);
    FieldToJson(args["executionSetWriteCount"], executionSetWriteCount, json_options);
    FieldToJson(args["pExecutionSetWrites"], pExecutionSetWrites, json_options);
    WriteBlockEnd("vkUpdateIndirectExecutionSetPipelineEXT");
}

void VulkanExportDiveConsumer::Process_vkUpdateIndirectExecutionSetShaderEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            indirectExecutionSet,
    uint32_t                                    executionSetWriteCount,
    StructPointerDecoder<Decoded_VkWriteIndirectExecutionSetShaderEXT>* pExecutionSetWrites)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["indirectExecutionSet"], indirectExecutionSet, json_options);
    FieldToJson(args["executionSetWriteCount"], executionSetWriteCount, json_options);
    FieldToJson(args["pExecutionSetWrites"], pExecutionSetWrites, json_options);
    WriteBlockEnd("vkUpdateIndirectExecutionSetShaderEXT");
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkCooperativeMatrixFlexibleDimensionsPropertiesNV>* pProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["physicalDevice"], physicalDevice, json_options);
    FieldToJson(args["pPropertyCount"], pPropertyCount, json_options);
    FieldToJson(args["pProperties"], pProperties, json_options);
    WriteBlockEnd("vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV");
}

void VulkanExportDiveConsumer::Process_vkGetMemoryMetalHandleEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetMetalHandleInfoEXT>* pGetMetalHandleInfo,
    PointerDecoder<uint64_t, void*>*            pHandle)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pGetMetalHandleInfo"], pGetMetalHandleInfo, json_options);
    FieldToJson(args["pHandle"], pHandle, json_options);
    WriteBlockEnd("vkGetMemoryMetalHandleEXT");
}

void VulkanExportDiveConsumer::Process_vkGetMemoryMetalHandlePropertiesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    uint64_t                                    pHandle,
    StructPointerDecoder<Decoded_VkMemoryMetalHandlePropertiesEXT>* pMemoryMetalHandleProperties)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["handleType"], handleType, json_options);
    FieldToJson(args["pHandle"], pHandle, json_options);
    FieldToJson(args["pMemoryMetalHandleProperties"], pMemoryMetalHandleProperties, json_options);
    WriteBlockEnd("vkGetMemoryMetalHandlePropertiesEXT");
}

void VulkanExportDiveConsumer::Process_vkCreateAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAccelerationStructureCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkAccelerationStructureKHR>* pAccelerationStructure)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pCreateInfo"], pCreateInfo, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pAccelerationStructure"], pAccelerationStructure, json_options);
    WriteBlockEnd("vkCreateAccelerationStructureKHR");
}

void VulkanExportDiveConsumer::Process_vkDestroyAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            accelerationStructure,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["accelerationStructure"], accelerationStructure, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    WriteBlockEnd("vkDestroyAccelerationStructureKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdBuildAccelerationStructuresKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    infoCount,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppBuildRangeInfos)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["infoCount"], infoCount, json_options);
    FieldToJson(args["pInfos"], pInfos, json_options);
    FieldToJson(args["ppBuildRangeInfos"], ppBuildRangeInfos, json_options);
    util::DiveFunctionData function_data("vkCmdBuildAccelerationStructuresKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCopyAccelerationStructureToMemoryKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureToMemoryInfoKHR>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["deferredOperation"], deferredOperation, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkCopyAccelerationStructureToMemoryKHR");
}

void VulkanExportDiveConsumer::Process_vkCopyMemoryToAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    StructPointerDecoder<Decoded_VkCopyMemoryToAccelerationStructureInfoKHR>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["deferredOperation"], deferredOperation, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkCopyMemoryToAccelerationStructureKHR");
}

void VulkanExportDiveConsumer::Process_vkWriteAccelerationStructuresPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    accelerationStructureCount,
    HandlePointerDecoder<VkAccelerationStructureKHR>* pAccelerationStructures,
    VkQueryType                                 queryType,
    size_t                                      dataSize,
    PointerDecoder<uint8_t>*                    pData,
    size_t                                      stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["accelerationStructureCount"], accelerationStructureCount, json_options);
    HandleToJson(args["pAccelerationStructures"], pAccelerationStructures, json_options);
    FieldToJson(args["queryType"], queryType, json_options);
    FieldToJson(args["dataSize"], dataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    FieldToJson(args["stride"], stride, json_options);
    WriteBlockEnd("vkWriteAccelerationStructuresPropertiesKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdCopyAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyAccelerationStructureKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyAccelerationStructureToMemoryKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureToMemoryInfoKHR>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyAccelerationStructureToMemoryKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyMemoryToAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyMemoryToAccelerationStructureInfoKHR>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    util::DiveFunctionData function_data("vkCmdCopyMemoryToAccelerationStructureKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetAccelerationStructureDeviceAddressKHR(
    const ApiCallInfo&                          call_info,
    VkDeviceAddress                             returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAccelerationStructureDeviceAddressInfoKHR>* pInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pInfo"], pInfo, json_options);
    WriteBlockEnd("vkGetAccelerationStructureDeviceAddressKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdWriteAccelerationStructuresPropertiesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    accelerationStructureCount,
    HandlePointerDecoder<VkAccelerationStructureKHR>* pAccelerationStructures,
    VkQueryType                                 queryType,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["accelerationStructureCount"], accelerationStructureCount, json_options);
    HandleToJson(args["pAccelerationStructures"], pAccelerationStructures, json_options);
    FieldToJson(args["queryType"], queryType, json_options);
    HandleToJson(args["queryPool"], queryPool, json_options);
    FieldToJson(args["firstQuery"], firstQuery, json_options);
    util::DiveFunctionData function_data("vkCmdWriteAccelerationStructuresPropertiesKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceAccelerationStructureCompatibilityKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAccelerationStructureVersionInfoKHR>* pVersionInfo,
    PointerDecoder<VkAccelerationStructureCompatibilityKHR>* pCompatibility)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["pVersionInfo"], pVersionInfo, json_options);
    FieldToJson(args["pCompatibility"], pCompatibility, json_options);
    WriteBlockEnd("vkGetDeviceAccelerationStructureCompatibilityKHR");
}

void VulkanExportDiveConsumer::Process_vkGetAccelerationStructureBuildSizesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    VkAccelerationStructureBuildTypeKHR         buildType,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pBuildInfo,
    PointerDecoder<uint32_t>*                   pMaxPrimitiveCounts,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildSizesInfoKHR>* pSizeInfo)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    FieldToJson(args["buildType"], buildType, json_options);
    FieldToJson(args["pBuildInfo"], pBuildInfo, json_options);
    FieldToJson(args["pMaxPrimitiveCounts"], pMaxPrimitiveCounts, json_options);
    FieldToJson(args["pSizeInfo"], pSizeInfo, json_options);
    WriteBlockEnd("vkGetAccelerationStructureBuildSizesKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdTraceRaysKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pRaygenShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pMissShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pHitShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pCallableShaderBindingTable,
    uint32_t                                    width,
    uint32_t                                    height,
    uint32_t                                    depth)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pRaygenShaderBindingTable"], pRaygenShaderBindingTable, json_options);
    FieldToJson(args["pMissShaderBindingTable"], pMissShaderBindingTable, json_options);
    FieldToJson(args["pHitShaderBindingTable"], pHitShaderBindingTable, json_options);
    FieldToJson(args["pCallableShaderBindingTable"], pCallableShaderBindingTable, json_options);
    FieldToJson(args["width"], width, json_options);
    FieldToJson(args["height"], height, json_options);
    FieldToJson(args["depth"], depth, json_options);
    util::DiveFunctionData function_data("vkCmdTraceRaysKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCreateRayTracingPipelinesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    format::HandleId                            pipelineCache,
    uint32_t                                    createInfoCount,
    StructPointerDecoder<Decoded_VkRayTracingPipelineCreateInfoKHR>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipeline>*           pPipelines)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["deferredOperation"], deferredOperation, json_options);
    HandleToJson(args["pipelineCache"], pipelineCache, json_options);
    FieldToJson(args["createInfoCount"], createInfoCount, json_options);
    FieldToJson(args["pCreateInfos"], pCreateInfos, json_options);
    FieldToJson(args["pAllocator"], pAllocator, json_options);
    HandleToJson(args["pPipelines"], pPipelines, json_options);
    WriteBlockEnd("vkCreateRayTracingPipelinesKHR");
}

void VulkanExportDiveConsumer::Process_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            pipeline,
    uint32_t                                    firstGroup,
    uint32_t                                    groupCount,
    size_t                                      dataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipeline"], pipeline, json_options);
    FieldToJson(args["firstGroup"], firstGroup, json_options);
    FieldToJson(args["groupCount"], groupCount, json_options);
    FieldToJson(args["dataSize"], dataSize, json_options);
    FieldToJson(args["pData"], pData, json_options);
    WriteBlockEnd("vkGetRayTracingCaptureReplayShaderGroupHandlesKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdTraceRaysIndirectKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pRaygenShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pMissShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pHitShaderBindingTable,
    StructPointerDecoder<Decoded_VkStridedDeviceAddressRegionKHR>* pCallableShaderBindingTable,
    VkDeviceAddress                             indirectDeviceAddress)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pRaygenShaderBindingTable"], pRaygenShaderBindingTable, json_options);
    FieldToJson(args["pMissShaderBindingTable"], pMissShaderBindingTable, json_options);
    FieldToJson(args["pHitShaderBindingTable"], pHitShaderBindingTable, json_options);
    FieldToJson(args["pCallableShaderBindingTable"], pCallableShaderBindingTable, json_options);
    FieldToJsonAsHex(args["indirectDeviceAddress"], indirectDeviceAddress, json_options);
    util::DiveFunctionData function_data("vkCmdTraceRaysIndirectKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkGetRayTracingShaderGroupStackSizeKHR(
    const ApiCallInfo&                          call_info,
    VkDeviceSize                                returnValue,
    format::HandleId                            device,
    format::HandleId                            pipeline,
    uint32_t                                    group,
    VkShaderGroupShaderKHR                      groupShader)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["device"], device, json_options);
    HandleToJson(args["pipeline"], pipeline, json_options);
    FieldToJson(args["group"], group, json_options);
    FieldToJson(args["groupShader"], groupShader, json_options);
    WriteBlockEnd("vkGetRayTracingShaderGroupStackSizeKHR");
}

void VulkanExportDiveConsumer::Process_vkCmdSetRayTracingPipelineStackSizeKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    pipelineStackSize)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["pipelineStackSize"], pipelineStackSize, json_options);
    util::DiveFunctionData function_data("vkCmdSetRayTracingPipelineStackSizeKHR", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMeshTasksEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    FieldToJson(args["groupCountX"], groupCountX, json_options);
    FieldToJson(args["groupCountY"], groupCountY, json_options);
    FieldToJson(args["groupCountZ"], groupCountZ, json_options);
    util::DiveFunctionData function_data("vkCmdDrawMeshTasksEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMeshTasksIndirectEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    FieldToJson(args["drawCount"], drawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawMeshTasksIndirectEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMeshTasksIndirectCountEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    format::HandleId                            countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride)
{
    nlohmann::ordered_json dive_data;
    const JsonOptions json_options;
    auto& args = dive_data["args"];
    HandleToJson(args["commandBuffer"], commandBuffer, json_options);
    HandleToJson(args["buffer"], buffer, json_options);
    FieldToJson(args["offset"], offset, json_options);
    HandleToJson(args["countBuffer"], countBuffer, json_options);
    FieldToJson(args["countBufferOffset"], countBufferOffset, json_options);
    FieldToJson(args["maxDrawCount"], maxDrawCount, json_options);
    FieldToJson(args["stride"], stride, json_options);
    util::DiveFunctionData function_data("vkCmdDrawMeshTasksIndirectCountEXT", GetCommandBufferRecordIndex(commandBuffer), call_info.index, args);
    WriteBlockEnd(function_data);
}
GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
