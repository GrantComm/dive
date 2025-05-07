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
#include "generated/generated_vulkan_dive_consumer.h"
#include "decode/custom_vulkan_struct_to_dive.h"
#include "decode/decode_dive_util.h"

#include "vulkan/vulkan.h"
#include "vk_video/vulkan_video_codec_h264std.h"
#include "vk_video/vulkan_video_codec_h264std_decode.h"
#include "vk_video/vulkan_video_codec_h264std_encode.h"
#include "vk_video/vulkan_video_codec_h265std.h"
#include "vk_video/vulkan_video_codec_h265std_decode.h"
#include "vk_video/vulkan_video_codec_h265std_encode.h"
#include "vk_video/vulkan_video_codecs_common.h"

#include <string>
#include <map>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

void VulkanExportDiveConsumer::Process_vkCreateInstance(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    StructPointerDecoder<Decoded_VkInstanceCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkInstance>*           pInstance)
{
    std::string name = "vkCreateInstance";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyInstance(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyInstance";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkEnumeratePhysicalDevices(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    PointerDecoder<uint32_t>*                   pPhysicalDeviceCount,
    HandlePointerDecoder<VkPhysicalDevice>*     pPhysicalDevices)
{
    std::string name = "vkEnumeratePhysicalDevices";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFeatures(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceFeatures>* pFeatures)
{
    std::string name = "vkGetPhysicalDeviceFeatures";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFormatProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    VkFormat                                    format,
    StructPointerDecoder<Decoded_VkFormatProperties>* pFormatProperties)
{
    std::string name = "vkGetPhysicalDeviceFormatProperties";
    WriteBlockEnd(name);
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
    std::string name = "vkGetPhysicalDeviceImageFormatProperties";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceProperties>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceProperties";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceQueueFamilyProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pQueueFamilyPropertyCount,
    StructPointerDecoder<Decoded_VkQueueFamilyProperties>* pQueueFamilyProperties)
{
    std::string name = "vkGetPhysicalDeviceQueueFamilyProperties";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceMemoryProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceMemoryProperties>* pMemoryProperties)
{
    std::string name = "vkGetPhysicalDeviceMemoryProperties";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateDevice(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkDeviceCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDevice>*             pDevice)
{
    std::string name = "vkCreateDevice";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyDevice(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyDevice";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceQueue(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    uint32_t                                    queueFamilyIndex,
    uint32_t                                    queueIndex,
    HandlePointerDecoder<VkQueue>*              pQueue)
{
    std::string name = "vkGetDeviceQueue";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkQueueSubmit(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    uint32_t                                    submitCount,
    StructPointerDecoder<Decoded_VkSubmitInfo>* pSubmits,
    format::HandleId                            fence)
{
    std::string name = "vkQueueSubmit";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkQueueWaitIdle(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue)
{
    std::string name = "vkQueueWaitIdle";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDeviceWaitIdle(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device)
{
    std::string name = "vkDeviceWaitIdle";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkAllocateMemory(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryAllocateInfo>* pAllocateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDeviceMemory>*       pMemory)
{
    std::string name = "vkAllocateMemory";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkFreeMemory(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            memory,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkFreeMemory";
    WriteBlockEnd(name);
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
    std::string name = "vkMapMemory";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkUnmapMemory(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            memory)
{
    std::string name = "vkUnmapMemory";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkFlushMappedMemoryRanges(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    memoryRangeCount,
    StructPointerDecoder<Decoded_VkMappedMemoryRange>* pMemoryRanges)
{
    std::string name = "vkFlushMappedMemoryRanges";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkInvalidateMappedMemoryRanges(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    memoryRangeCount,
    StructPointerDecoder<Decoded_VkMappedMemoryRange>* pMemoryRanges)
{
    std::string name = "vkInvalidateMappedMemoryRanges";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceMemoryCommitment(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            memory,
    PointerDecoder<VkDeviceSize>*               pCommittedMemoryInBytes)
{
    std::string name = "vkGetDeviceMemoryCommitment";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkBindBufferMemory(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            buffer,
    format::HandleId                            memory,
    VkDeviceSize                                memoryOffset)
{
    std::string name = "vkBindBufferMemory";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkBindImageMemory(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            image,
    format::HandleId                            memory,
    VkDeviceSize                                memoryOffset)
{
    std::string name = "vkBindImageMemory";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetBufferMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            buffer,
    StructPointerDecoder<Decoded_VkMemoryRequirements>* pMemoryRequirements)
{
    std::string name = "vkGetBufferMemoryRequirements";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkMemoryRequirements>* pMemoryRequirements)
{
    std::string name = "vkGetImageMemoryRequirements";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageSparseMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    PointerDecoder<uint32_t>*                   pSparseMemoryRequirementCount,
    StructPointerDecoder<Decoded_VkSparseImageMemoryRequirements>* pSparseMemoryRequirements)
{
    std::string name = "vkGetImageSparseMemoryRequirements";
    WriteBlockEnd(name);
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
    std::string name = "vkGetPhysicalDeviceSparseImageFormatProperties";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkQueueBindSparse(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindSparseInfo>* pBindInfo,
    format::HandleId                            fence)
{
    std::string name = "vkQueueBindSparse";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateFence(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkFenceCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkFence>*              pFence)
{
    std::string name = "vkCreateFence";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyFence(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            fence,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyFence";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkResetFences(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    fenceCount,
    HandlePointerDecoder<VkFence>*              pFences)
{
    std::string name = "vkResetFences";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetFenceStatus(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            fence)
{
    std::string name = "vkGetFenceStatus";
    WriteBlockEnd(name);
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
    std::string name = "vkWaitForFences";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateSemaphore(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSemaphore>*          pSemaphore)
{
    std::string name = "vkCreateSemaphore";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroySemaphore(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            semaphore,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroySemaphore";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateEvent(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkEventCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkEvent>*              pEvent)
{
    std::string name = "vkCreateEvent";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyEvent(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            event,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyEvent";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetEventStatus(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            event)
{
    std::string name = "vkGetEventStatus";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkSetEvent(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            event)
{
    std::string name = "vkSetEvent";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkResetEvent(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            event)
{
    std::string name = "vkResetEvent";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateQueryPool(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkQueryPoolCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkQueryPool>*          pQueryPool)
{
    std::string name = "vkCreateQueryPool";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyQueryPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            queryPool,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyQueryPool";
    WriteBlockEnd(name);
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
    std::string name = "vkGetQueryPoolResults";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateBuffer(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkBuffer>*             pBuffer)
{
    std::string name = "vkCreateBuffer";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            buffer,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyBuffer";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateBufferView(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferViewCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkBufferView>*         pView)
{
    std::string name = "vkCreateBufferView";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyBufferView(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            bufferView,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyBufferView";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateImage(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkImage>*              pImage)
{
    std::string name = "vkCreateImage";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyImage(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyImage";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageSubresourceLayout(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkImageSubresource>* pSubresource,
    StructPointerDecoder<Decoded_VkSubresourceLayout>* pLayout)
{
    std::string name = "vkGetImageSubresourceLayout";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateImageView(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageViewCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkImageView>*          pView)
{
    std::string name = "vkCreateImageView";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyImageView(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            imageView,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyImageView";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyShaderModule(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            shaderModule,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyShaderModule";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyPipelineCache(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            pipelineCache,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyPipelineCache";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkMergePipelineCaches(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            dstCache,
    uint32_t                                    srcCacheCount,
    HandlePointerDecoder<VkPipelineCache>*      pSrcCaches)
{
    std::string name = "vkMergePipelineCaches";
    WriteBlockEnd(name);
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
    std::string name = "vkCreateGraphicsPipelines";
    WriteBlockEnd(name);
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
    std::string name = "vkCreateComputePipelines";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyPipeline(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            pipeline,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyPipeline";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreatePipelineLayout(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineLayoutCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipelineLayout>*     pPipelineLayout)
{
    std::string name = "vkCreatePipelineLayout";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyPipelineLayout(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            pipelineLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyPipelineLayout";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateSampler(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSamplerCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSampler>*            pSampler)
{
    std::string name = "vkCreateSampler";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroySampler(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            sampler,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroySampler";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateDescriptorSetLayout(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorSetLayout>* pSetLayout)
{
    std::string name = "vkCreateDescriptorSetLayout";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyDescriptorSetLayout(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            descriptorSetLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyDescriptorSetLayout";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateDescriptorPool(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorPoolCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorPool>*     pDescriptorPool)
{
    std::string name = "vkCreateDescriptorPool";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyDescriptorPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            descriptorPool,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyDescriptorPool";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkResetDescriptorPool(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            descriptorPool,
    VkDescriptorPoolResetFlags                  flags)
{
    std::string name = "vkResetDescriptorPool";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkAllocateDescriptorSets(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorSetAllocateInfo>* pAllocateInfo,
    HandlePointerDecoder<VkDescriptorSet>*      pDescriptorSets)
{
    std::string name = "vkAllocateDescriptorSets";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkFreeDescriptorSets(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            descriptorPool,
    uint32_t                                    descriptorSetCount,
    HandlePointerDecoder<VkDescriptorSet>*      pDescriptorSets)
{
    std::string name = "vkFreeDescriptorSets";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkUpdateDescriptorSets(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    uint32_t                                    descriptorWriteCount,
    StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites,
    uint32_t                                    descriptorCopyCount,
    StructPointerDecoder<Decoded_VkCopyDescriptorSet>* pDescriptorCopies)
{
    std::string name = "vkUpdateDescriptorSets";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateFramebuffer(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkFramebufferCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkFramebuffer>*        pFramebuffer)
{
    std::string name = "vkCreateFramebuffer";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyFramebuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            framebuffer,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyFramebuffer";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateRenderPass(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderPassCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkRenderPass>*         pRenderPass)
{
    std::string name = "vkCreateRenderPass";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyRenderPass(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            renderPass,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyRenderPass";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetRenderAreaGranularity(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            renderPass,
    StructPointerDecoder<Decoded_VkExtent2D>*   pGranularity)
{
    std::string name = "vkGetRenderAreaGranularity";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateCommandPool(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCommandPoolCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkCommandPool>*        pCommandPool)
{
    std::string name = "vkCreateCommandPool";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyCommandPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            commandPool,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyCommandPool";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkResetCommandPool(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            commandPool,
    VkCommandPoolResetFlags                     flags)
{
    std::string name = "vkResetCommandPool";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkAllocateCommandBuffers(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCommandBufferAllocateInfo>* pAllocateInfo,
    HandlePointerDecoder<VkCommandBuffer>*      pCommandBuffers)
{
    std::string name = "vkAllocateCommandBuffers";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkFreeCommandBuffers(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            commandPool,
    uint32_t                                    commandBufferCount,
    HandlePointerDecoder<VkCommandBuffer>*      pCommandBuffers)
{
    std::string name = "vkFreeCommandBuffers";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkBeginCommandBuffer(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCommandBufferBeginInfo>* pBeginInfo)
{
    std::string name = "vkBeginCommandBuffer";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkEndCommandBuffer(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer)
{
    std::string name = "vkEndCommandBuffer";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkResetCommandBuffer(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer,
    VkCommandBufferResetFlags                   flags)
{
    std::string name = "vkResetCommandBuffer";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBindPipeline(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    format::HandleId                            pipeline)
{
    std::string name = "vkCmdBindPipeline";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewport(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkViewport>*   pViewports)
{
    std::string name = "vkCmdSetViewport";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetScissor(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstScissor,
    uint32_t                                    scissorCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pScissors)
{
    std::string name = "vkCmdSetScissor";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineWidth(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    float                                       lineWidth)
{
    std::string name = "vkCmdSetLineWidth";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBias(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    float                                       depthBiasConstantFactor,
    float                                       depthBiasClamp,
    float                                       depthBiasSlopeFactor)
{
    std::string name = "vkCmdSetDepthBias";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetBlendConstants(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    PointerDecoder<float>*                      blendConstants)
{
    std::string name = "vkCmdSetBlendConstants";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBounds(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    float                                       minDepthBounds,
    float                                       maxDepthBounds)
{
    std::string name = "vkCmdSetDepthBounds";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilCompareMask(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    compareMask)
{
    std::string name = "vkCmdSetStencilCompareMask";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilWriteMask(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    writeMask)
{
    std::string name = "vkCmdSetStencilWriteMask";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilReference(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    reference)
{
    std::string name = "vkCmdSetStencilReference";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdBindDescriptorSets";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBindIndexBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    VkIndexType                                 indexType)
{
    std::string name = "vkCmdBindIndexBuffer";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBindVertexBuffers(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    HandlePointerDecoder<VkBuffer>*             pBuffers,
    PointerDecoder<VkDeviceSize>*               pOffsets)
{
    std::string name = "vkCmdBindVertexBuffers";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDraw(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    vertexCount,
    uint32_t                                    instanceCount,
    uint32_t                                    firstVertex,
    uint32_t                                    firstInstance)
{
    std::string name = "vkCmdDraw";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDrawIndexed";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndirect(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride)
{
    std::string name = "vkCmdDrawIndirect";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawIndexedIndirect(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride)
{
    std::string name = "vkCmdDrawIndexedIndirect";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDispatch(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ)
{
    std::string name = "vkCmdDispatch";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDispatchIndirect(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset)
{
    std::string name = "vkCmdDispatchIndirect";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            srcBuffer,
    format::HandleId                            dstBuffer,
    uint32_t                                    regionCount,
    StructPointerDecoder<Decoded_VkBufferCopy>* pRegions)
{
    std::string name = "vkCmdCopyBuffer";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdCopyImage";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdBlitImage";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdCopyBufferToImage";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdCopyImageToBuffer";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdUpdateBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                dataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    std::string name = "vkCmdUpdateBuffer";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdFillBuffer(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                size,
    uint32_t                                    data)
{
    std::string name = "vkCmdFillBuffer";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdClearColorImage";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdClearDepthStencilImage";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdClearAttachments(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    attachmentCount,
    StructPointerDecoder<Decoded_VkClearAttachment>* pAttachments,
    uint32_t                                    rectCount,
    StructPointerDecoder<Decoded_VkClearRect>*  pRects)
{
    std::string name = "vkCmdClearAttachments";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdResolveImage";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetEvent(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    VkPipelineStageFlags                        stageMask)
{
    std::string name = "vkCmdSetEvent";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdResetEvent(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    VkPipelineStageFlags                        stageMask)
{
    std::string name = "vkCmdResetEvent";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdWaitEvents";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdPipelineBarrier";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginQuery(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    query,
    VkQueryControlFlags                         flags)
{
    std::string name = "vkCmdBeginQuery";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndQuery(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    query)
{
    std::string name = "vkCmdEndQuery";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdResetQueryPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount)
{
    std::string name = "vkCmdResetQueryPool";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdWriteTimestamp(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlagBits                     pipelineStage,
    format::HandleId                            queryPool,
    uint32_t                                    query)
{
    std::string name = "vkCmdWriteTimestamp";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdCopyQueryPoolResults";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginRenderPass(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderPassBeginInfo>* pRenderPassBegin,
    VkSubpassContents                           contents)
{
    std::string name = "vkCmdBeginRenderPass";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdNextSubpass(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkSubpassContents                           contents)
{
    std::string name = "vkCmdNextSubpass";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndRenderPass(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    std::string name = "vkCmdEndRenderPass";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdExecuteCommands(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    commandBufferCount,
    HandlePointerDecoder<VkCommandBuffer>*      pCommandBuffers)
{
    std::string name = "vkCmdExecuteCommands";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkBindBufferMemory2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindBufferMemoryInfo>* pBindInfos)
{
    std::string name = "vkBindBufferMemory2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkBindImageMemory2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindImageMemoryInfo>* pBindInfos)
{
    std::string name = "vkBindImageMemory2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceGroupPeerMemoryFeatures(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    uint32_t                                    heapIndex,
    uint32_t                                    localDeviceIndex,
    uint32_t                                    remoteDeviceIndex,
    PointerDecoder<VkPeerMemoryFeatureFlags>*   pPeerMemoryFeatures)
{
    std::string name = "vkGetDeviceGroupPeerMemoryFeatures";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDeviceMask(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    deviceMask)
{
    std::string name = "vkCmdSetDeviceMask";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDispatchBase";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkEnumeratePhysicalDeviceGroups(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    PointerDecoder<uint32_t>*                   pPhysicalDeviceGroupCount,
    StructPointerDecoder<Decoded_VkPhysicalDeviceGroupProperties>* pPhysicalDeviceGroupProperties)
{
    std::string name = "vkEnumeratePhysicalDeviceGroups";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageMemoryRequirements2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageMemoryRequirementsInfo2>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetImageMemoryRequirements2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetBufferMemoryRequirements2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferMemoryRequirementsInfo2>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetBufferMemoryRequirements2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageSparseMemoryRequirements2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageSparseMemoryRequirementsInfo2>* pInfo,
    PointerDecoder<uint32_t>*                   pSparseMemoryRequirementCount,
    StructPointerDecoder<Decoded_VkSparseImageMemoryRequirements2>* pSparseMemoryRequirements)
{
    std::string name = "vkGetImageSparseMemoryRequirements2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFeatures2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceFeatures2>* pFeatures)
{
    std::string name = "vkGetPhysicalDeviceFeatures2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceProperties2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceProperties2>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceProperties2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFormatProperties2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    VkFormat                                    format,
    StructPointerDecoder<Decoded_VkFormatProperties2>* pFormatProperties)
{
    std::string name = "vkGetPhysicalDeviceFormatProperties2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceImageFormatProperties2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceImageFormatInfo2>* pImageFormatInfo,
    StructPointerDecoder<Decoded_VkImageFormatProperties2>* pImageFormatProperties)
{
    std::string name = "vkGetPhysicalDeviceImageFormatProperties2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceQueueFamilyProperties2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pQueueFamilyPropertyCount,
    StructPointerDecoder<Decoded_VkQueueFamilyProperties2>* pQueueFamilyProperties)
{
    std::string name = "vkGetPhysicalDeviceQueueFamilyProperties2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceMemoryProperties2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceMemoryProperties2>* pMemoryProperties)
{
    std::string name = "vkGetPhysicalDeviceMemoryProperties2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSparseImageFormatProperties2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSparseImageFormatInfo2>* pFormatInfo,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkSparseImageFormatProperties2>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceSparseImageFormatProperties2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkTrimCommandPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            commandPool,
    VkCommandPoolTrimFlags                      flags)
{
    std::string name = "vkTrimCommandPool";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceQueue2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceQueueInfo2>* pQueueInfo,
    HandlePointerDecoder<VkQueue>*              pQueue)
{
    std::string name = "vkGetDeviceQueue2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateSamplerYcbcrConversion(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSamplerYcbcrConversionCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSamplerYcbcrConversion>* pYcbcrConversion)
{
    std::string name = "vkCreateSamplerYcbcrConversion";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroySamplerYcbcrConversion(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            ycbcrConversion,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroySamplerYcbcrConversion";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateDescriptorUpdateTemplate(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorUpdateTemplateCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorUpdateTemplate>* pDescriptorUpdateTemplate)
{
    std::string name = "vkCreateDescriptorUpdateTemplate";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyDescriptorUpdateTemplate(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            descriptorUpdateTemplate,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyDescriptorUpdateTemplate";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalBufferProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalBufferInfo>* pExternalBufferInfo,
    StructPointerDecoder<Decoded_VkExternalBufferProperties>* pExternalBufferProperties)
{
    std::string name = "vkGetPhysicalDeviceExternalBufferProperties";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalFenceProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalFenceInfo>* pExternalFenceInfo,
    StructPointerDecoder<Decoded_VkExternalFenceProperties>* pExternalFenceProperties)
{
    std::string name = "vkGetPhysicalDeviceExternalFenceProperties";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalSemaphoreProperties(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalSemaphoreInfo>* pExternalSemaphoreInfo,
    StructPointerDecoder<Decoded_VkExternalSemaphoreProperties>* pExternalSemaphoreProperties)
{
    std::string name = "vkGetPhysicalDeviceExternalSemaphoreProperties";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDescriptorSetLayoutSupport(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutSupport>* pSupport)
{
    std::string name = "vkGetDescriptorSetLayoutSupport";
    WriteBlockEnd(name);
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
    std::string name = "vkCmdDrawIndirectCount";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDrawIndexedIndirectCount";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCreateRenderPass2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderPassCreateInfo2>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkRenderPass>*         pRenderPass)
{
    std::string name = "vkCreateRenderPass2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginRenderPass2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderPassBeginInfo>* pRenderPassBegin,
    StructPointerDecoder<Decoded_VkSubpassBeginInfo>* pSubpassBeginInfo)
{
    std::string name = "vkCmdBeginRenderPass2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdNextSubpass2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSubpassBeginInfo>* pSubpassBeginInfo,
    StructPointerDecoder<Decoded_VkSubpassEndInfo>* pSubpassEndInfo)
{
    std::string name = "vkCmdNextSubpass2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndRenderPass2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSubpassEndInfo>* pSubpassEndInfo)
{
    std::string name = "vkCmdEndRenderPass2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkResetQueryPool(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount)
{
    std::string name = "vkResetQueryPool";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetSemaphoreCounterValue(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            semaphore,
    PointerDecoder<uint64_t>*                   pValue)
{
    std::string name = "vkGetSemaphoreCounterValue";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkWaitSemaphores(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
    uint64_t                                    timeout)
{
    std::string name = "vkWaitSemaphores";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkSignalSemaphore(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo)
{
    std::string name = "vkSignalSemaphore";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetBufferDeviceAddress(
    const ApiCallInfo&                          call_info,
    VkDeviceAddress                             returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferDeviceAddressInfo>* pInfo)
{
    std::string name = "vkGetBufferDeviceAddress";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetBufferOpaqueCaptureAddress(
    const ApiCallInfo&                          call_info,
    uint64_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferDeviceAddressInfo>* pInfo)
{
    std::string name = "vkGetBufferOpaqueCaptureAddress";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceMemoryOpaqueCaptureAddress(
    const ApiCallInfo&                          call_info,
    uint64_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceMemoryOpaqueCaptureAddressInfo>* pInfo)
{
    std::string name = "vkGetDeviceMemoryOpaqueCaptureAddress";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceToolProperties(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pToolCount,
    StructPointerDecoder<Decoded_VkPhysicalDeviceToolProperties>* pToolProperties)
{
    std::string name = "vkGetPhysicalDeviceToolProperties";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreatePrivateDataSlot(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPrivateDataSlotCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPrivateDataSlot>*    pPrivateDataSlot)
{
    std::string name = "vkCreatePrivateDataSlot";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyPrivateDataSlot(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            privateDataSlot,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyPrivateDataSlot";
    WriteBlockEnd(name);
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
    std::string name = "vkSetPrivateData";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPrivateData(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    format::HandleId                            privateDataSlot,
    PointerDecoder<uint64_t>*                   pData)
{
    std::string name = "vkGetPrivateData";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetEvent2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfo)
{
    std::string name = "vkCmdSetEvent2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdResetEvent2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    VkPipelineStageFlags2                       stageMask)
{
    std::string name = "vkCmdResetEvent2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdWaitEvents2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    eventCount,
    HandlePointerDecoder<VkEvent>*              pEvents,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfos)
{
    std::string name = "vkCmdWaitEvents2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdPipelineBarrier2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfo)
{
    std::string name = "vkCmdPipelineBarrier2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdWriteTimestamp2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlags2                       stage,
    format::HandleId                            queryPool,
    uint32_t                                    query)
{
    std::string name = "vkCmdWriteTimestamp2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkQueueSubmit2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    uint32_t                                    submitCount,
    StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
    format::HandleId                            fence)
{
    std::string name = "vkQueueSubmit2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBuffer2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferInfo2>* pCopyBufferInfo)
{
    std::string name = "vkCmdCopyBuffer2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyImage2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageInfo2>* pCopyImageInfo)
{
    std::string name = "vkCmdCopyImage2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBufferToImage2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferToImageInfo2>* pCopyBufferToImageInfo)
{
    std::string name = "vkCmdCopyBufferToImage2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyImageToBuffer2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageToBufferInfo2>* pCopyImageToBufferInfo)
{
    std::string name = "vkCmdCopyImageToBuffer2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBlitImage2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBlitImageInfo2>* pBlitImageInfo)
{
    std::string name = "vkCmdBlitImage2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdResolveImage2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkResolveImageInfo2>* pResolveImageInfo)
{
    std::string name = "vkCmdResolveImage2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginRendering(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInfo>* pRenderingInfo)
{
    std::string name = "vkCmdBeginRendering";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndRendering(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    std::string name = "vkCmdEndRendering";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCullMode(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCullModeFlags                             cullMode)
{
    std::string name = "vkCmdSetCullMode";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetFrontFace(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkFrontFace                                 frontFace)
{
    std::string name = "vkCmdSetFrontFace";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPrimitiveTopology(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPrimitiveTopology                         primitiveTopology)
{
    std::string name = "vkCmdSetPrimitiveTopology";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportWithCount(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkViewport>*   pViewports)
{
    std::string name = "vkCmdSetViewportWithCount";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetScissorWithCount(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    scissorCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pScissors)
{
    std::string name = "vkCmdSetScissorWithCount";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdBindVertexBuffers2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthTestEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthTestEnable)
{
    std::string name = "vkCmdSetDepthTestEnable";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthWriteEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthWriteEnable)
{
    std::string name = "vkCmdSetDepthWriteEnable";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthCompareOp(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCompareOp                                 depthCompareOp)
{
    std::string name = "vkCmdSetDepthCompareOp";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBoundsTestEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthBoundsTestEnable)
{
    std::string name = "vkCmdSetDepthBoundsTestEnable";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilTestEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    stencilTestEnable)
{
    std::string name = "vkCmdSetStencilTestEnable";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdSetStencilOp";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRasterizerDiscardEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    rasterizerDiscardEnable)
{
    std::string name = "vkCmdSetRasterizerDiscardEnable";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBiasEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthBiasEnable)
{
    std::string name = "vkCmdSetDepthBiasEnable";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPrimitiveRestartEnable(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    primitiveRestartEnable)
{
    std::string name = "vkCmdSetPrimitiveRestartEnable";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceBufferMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceBufferMemoryRequirements>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetDeviceBufferMemoryRequirements";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageMemoryRequirements>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetDeviceImageMemoryRequirements";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageSparseMemoryRequirements(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageMemoryRequirements>* pInfo,
    PointerDecoder<uint32_t>*                   pSparseMemoryRequirementCount,
    StructPointerDecoder<Decoded_VkSparseImageMemoryRequirements2>* pSparseMemoryRequirements)
{
    std::string name = "vkGetDeviceImageSparseMemoryRequirements";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineStipple(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern)
{
    std::string name = "vkCmdSetLineStipple";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkMapMemory2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryMapInfo>* pMemoryMapInfo,
    PointerDecoder<uint64_t, void*>*            ppData)
{
    std::string name = "vkMapMemory2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkUnmapMemory2(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryUnmapInfo>* pMemoryUnmapInfo)
{
    std::string name = "vkUnmapMemory2";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBindIndexBuffer2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkIndexType                                 indexType)
{
    std::string name = "vkCmdBindIndexBuffer2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetRenderingAreaGranularity(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderingAreaInfo>* pRenderingAreaInfo,
    StructPointerDecoder<Decoded_VkExtent2D>*   pGranularity)
{
    std::string name = "vkGetRenderingAreaGranularity";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageSubresourceLayout(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageSubresourceInfo>* pInfo,
    StructPointerDecoder<Decoded_VkSubresourceLayout2>* pLayout)
{
    std::string name = "vkGetDeviceImageSubresourceLayout";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageSubresourceLayout2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkImageSubresource2>* pSubresource,
    StructPointerDecoder<Decoded_VkSubresourceLayout2>* pLayout)
{
    std::string name = "vkGetImageSubresourceLayout2";
    WriteBlockEnd(name);
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
    std::string name = "vkCmdPushDescriptorSet";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRenderingAttachmentLocations(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingAttachmentLocationInfo>* pLocationInfo)
{
    std::string name = "vkCmdSetRenderingAttachmentLocations";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRenderingInputAttachmentIndices(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInputAttachmentIndexInfo>* pInputAttachmentIndexInfo)
{
    std::string name = "vkCmdSetRenderingInputAttachmentIndices";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBindDescriptorSets2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBindDescriptorSetsInfo>* pBindDescriptorSetsInfo)
{
    std::string name = "vkCmdBindDescriptorSets2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdPushConstants2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPushConstantsInfo>* pPushConstantsInfo)
{
    std::string name = "vkCmdPushConstants2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdPushDescriptorSet2(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPushDescriptorSetInfo>* pPushDescriptorSetInfo)
{
    std::string name = "vkCmdPushDescriptorSet2";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCopyMemoryToImage(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyMemoryToImageInfo>* pCopyMemoryToImageInfo)
{
    std::string name = "vkCopyMemoryToImage";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCopyImageToMemory(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyImageToMemoryInfo>* pCopyImageToMemoryInfo)
{
    std::string name = "vkCopyImageToMemory";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCopyImageToImage(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyImageToImageInfo>* pCopyImageToImageInfo)
{
    std::string name = "vkCopyImageToImage";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkTransitionImageLayout(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    transitionCount,
    StructPointerDecoder<Decoded_VkHostImageLayoutTransitionInfo>* pTransitions)
{
    std::string name = "vkTransitionImageLayout";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroySurfaceKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    format::HandleId                            surface,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroySurfaceKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceSupportKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    format::HandleId                            surface,
    PointerDecoder<VkBool32>*                   pSupported)
{
    std::string name = "vkGetPhysicalDeviceSurfaceSupportKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            surface,
    StructPointerDecoder<Decoded_VkSurfaceCapabilitiesKHR>* pSurfaceCapabilities)
{
    std::string name = "vkGetPhysicalDeviceSurfaceCapabilitiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceFormatsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            surface,
    PointerDecoder<uint32_t>*                   pSurfaceFormatCount,
    StructPointerDecoder<Decoded_VkSurfaceFormatKHR>* pSurfaceFormats)
{
    std::string name = "vkGetPhysicalDeviceSurfaceFormatsKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfacePresentModesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            surface,
    PointerDecoder<uint32_t>*                   pPresentModeCount,
    PointerDecoder<VkPresentModeKHR>*           pPresentModes)
{
    std::string name = "vkGetPhysicalDeviceSurfacePresentModesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateSwapchainKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSwapchainCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSwapchainKHR>*       pSwapchain)
{
    std::string name = "vkCreateSwapchainKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroySwapchainKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroySwapchainKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetSwapchainImagesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    PointerDecoder<uint32_t>*                   pSwapchainImageCount,
    HandlePointerDecoder<VkImage>*              pSwapchainImages)
{
    std::string name = "vkGetSwapchainImagesKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkAcquireNextImageKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkQueuePresentKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    StructPointerDecoder<Decoded_VkPresentInfoKHR>* pPresentInfo)
{
    std::string name = "vkQueuePresentKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceGroupPresentCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceGroupPresentCapabilitiesKHR>* pDeviceGroupPresentCapabilities)
{
    std::string name = "vkGetDeviceGroupPresentCapabilitiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceGroupSurfacePresentModesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            surface,
    PointerDecoder<VkDeviceGroupPresentModeFlagsKHR>* pModes)
{
    std::string name = "vkGetDeviceGroupSurfacePresentModesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDevicePresentRectanglesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            surface,
    PointerDecoder<uint32_t>*                   pRectCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pRects)
{
    std::string name = "vkGetPhysicalDevicePresentRectanglesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkAcquireNextImage2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAcquireNextImageInfoKHR>* pAcquireInfo,
    PointerDecoder<uint32_t>*                   pImageIndex)
{
    std::string name = "vkAcquireNextImage2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceDisplayPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayPropertiesKHR>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceDisplayPropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayPlanePropertiesKHR>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceDisplayPlanePropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDisplayPlaneSupportedDisplaysKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    planeIndex,
    PointerDecoder<uint32_t>*                   pDisplayCount,
    HandlePointerDecoder<VkDisplayKHR>*         pDisplays)
{
    std::string name = "vkGetDisplayPlaneSupportedDisplaysKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDisplayModePropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            display,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayModePropertiesKHR>* pProperties)
{
    std::string name = "vkGetDisplayModePropertiesKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkCreateDisplayModeKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDisplayPlaneCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            mode,
    uint32_t                                    planeIndex,
    StructPointerDecoder<Decoded_VkDisplayPlaneCapabilitiesKHR>* pCapabilities)
{
    std::string name = "vkGetDisplayPlaneCapabilitiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateDisplayPlaneSurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkDisplaySurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateDisplayPlaneSurfaceKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkCreateSharedSwapchainsKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateXlibSurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkXlibSurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateXlibSurfaceKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceXlibPresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint64_t                                    dpy,
    size_t                                      visualID)
{
    std::string name = "vkGetPhysicalDeviceXlibPresentationSupportKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateXcbSurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkXcbSurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateXcbSurfaceKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceXcbPresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint64_t                                    connection,
    uint32_t                                    visual_id)
{
    std::string name = "vkGetPhysicalDeviceXcbPresentationSupportKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateWaylandSurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkWaylandSurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateWaylandSurfaceKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint64_t                                    display)
{
    std::string name = "vkGetPhysicalDeviceWaylandPresentationSupportKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateAndroidSurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkAndroidSurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateAndroidSurfaceKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateWin32SurfaceKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkWin32SurfaceCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateWin32SurfaceKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceWin32PresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex)
{
    std::string name = "vkGetPhysicalDeviceWin32PresentationSupportKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceVideoCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkVideoProfileInfoKHR>* pVideoProfile,
    StructPointerDecoder<Decoded_VkVideoCapabilitiesKHR>* pCapabilities)
{
    std::string name = "vkGetPhysicalDeviceVideoCapabilitiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceVideoFormatPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceVideoFormatInfoKHR>* pVideoFormatInfo,
    PointerDecoder<uint32_t>*                   pVideoFormatPropertyCount,
    StructPointerDecoder<Decoded_VkVideoFormatPropertiesKHR>* pVideoFormatProperties)
{
    std::string name = "vkGetPhysicalDeviceVideoFormatPropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateVideoSessionKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkVideoSessionCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkVideoSessionKHR>*    pVideoSession)
{
    std::string name = "vkCreateVideoSessionKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyVideoSessionKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            videoSession,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyVideoSessionKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetVideoSessionMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            videoSession,
    PointerDecoder<uint32_t>*                   pMemoryRequirementsCount,
    StructPointerDecoder<Decoded_VkVideoSessionMemoryRequirementsKHR>* pMemoryRequirements)
{
    std::string name = "vkGetVideoSessionMemoryRequirementsKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkBindVideoSessionMemoryKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            videoSession,
    uint32_t                                    bindSessionMemoryInfoCount,
    StructPointerDecoder<Decoded_VkBindVideoSessionMemoryInfoKHR>* pBindSessionMemoryInfos)
{
    std::string name = "vkBindVideoSessionMemoryKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkVideoSessionParametersCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkVideoSessionParametersKHR>* pVideoSessionParameters)
{
    std::string name = "vkCreateVideoSessionParametersKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkUpdateVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            videoSessionParameters,
    StructPointerDecoder<Decoded_VkVideoSessionParametersUpdateInfoKHR>* pUpdateInfo)
{
    std::string name = "vkUpdateVideoSessionParametersKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            videoSessionParameters,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyVideoSessionParametersKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginVideoCodingKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkVideoBeginCodingInfoKHR>* pBeginInfo)
{
    std::string name = "vkCmdBeginVideoCodingKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndVideoCodingKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkVideoEndCodingInfoKHR>* pEndCodingInfo)
{
    std::string name = "vkCmdEndVideoCodingKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdControlVideoCodingKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkVideoCodingControlInfoKHR>* pCodingControlInfo)
{
    std::string name = "vkCmdControlVideoCodingKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDecodeVideoKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkVideoDecodeInfoKHR>* pDecodeInfo)
{
    std::string name = "vkCmdDecodeVideoKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginRenderingKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInfo>* pRenderingInfo)
{
    std::string name = "vkCmdBeginRenderingKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndRenderingKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    std::string name = "vkCmdEndRenderingKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFeatures2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceFeatures2>* pFeatures)
{
    std::string name = "vkGetPhysicalDeviceFeatures2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceProperties2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceProperties2>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceProperties2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFormatProperties2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    VkFormat                                    format,
    StructPointerDecoder<Decoded_VkFormatProperties2>* pFormatProperties)
{
    std::string name = "vkGetPhysicalDeviceFormatProperties2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceImageFormatProperties2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceImageFormatInfo2>* pImageFormatInfo,
    StructPointerDecoder<Decoded_VkImageFormatProperties2>* pImageFormatProperties)
{
    std::string name = "vkGetPhysicalDeviceImageFormatProperties2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceQueueFamilyProperties2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pQueueFamilyPropertyCount,
    StructPointerDecoder<Decoded_VkQueueFamilyProperties2>* pQueueFamilyProperties)
{
    std::string name = "vkGetPhysicalDeviceQueueFamilyProperties2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceMemoryProperties2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceMemoryProperties2>* pMemoryProperties)
{
    std::string name = "vkGetPhysicalDeviceMemoryProperties2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSparseImageFormatInfo2>* pFormatInfo,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkSparseImageFormatProperties2>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceSparseImageFormatProperties2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceGroupPeerMemoryFeaturesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    uint32_t                                    heapIndex,
    uint32_t                                    localDeviceIndex,
    uint32_t                                    remoteDeviceIndex,
    PointerDecoder<VkPeerMemoryFeatureFlags>*   pPeerMemoryFeatures)
{
    std::string name = "vkGetDeviceGroupPeerMemoryFeaturesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDeviceMaskKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    deviceMask)
{
    std::string name = "vkCmdSetDeviceMaskKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDispatchBaseKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkTrimCommandPoolKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            commandPool,
    VkCommandPoolTrimFlags                      flags)
{
    std::string name = "vkTrimCommandPoolKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkEnumeratePhysicalDeviceGroupsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    PointerDecoder<uint32_t>*                   pPhysicalDeviceGroupCount,
    StructPointerDecoder<Decoded_VkPhysicalDeviceGroupProperties>* pPhysicalDeviceGroupProperties)
{
    std::string name = "vkEnumeratePhysicalDeviceGroupsKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalBufferPropertiesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalBufferInfo>* pExternalBufferInfo,
    StructPointerDecoder<Decoded_VkExternalBufferProperties>* pExternalBufferProperties)
{
    std::string name = "vkGetPhysicalDeviceExternalBufferPropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetWin32HandleInfoKHR>* pGetWin32HandleInfo,
    PointerDecoder<uint64_t, void*>*            pHandle)
{
    std::string name = "vkGetMemoryWin32HandleKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryWin32HandlePropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    uint64_t                                    handle,
    StructPointerDecoder<Decoded_VkMemoryWin32HandlePropertiesKHR>* pMemoryWin32HandleProperties)
{
    std::string name = "vkGetMemoryWin32HandlePropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryFdKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetFdInfoKHR>* pGetFdInfo,
    PointerDecoder<int>*                        pFd)
{
    std::string name = "vkGetMemoryFdKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryFdPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    int                                         fd,
    StructPointerDecoder<Decoded_VkMemoryFdPropertiesKHR>* pMemoryFdProperties)
{
    std::string name = "vkGetMemoryFdPropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalSemaphoreInfo>* pExternalSemaphoreInfo,
    StructPointerDecoder<Decoded_VkExternalSemaphoreProperties>* pExternalSemaphoreProperties)
{
    std::string name = "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkImportSemaphoreWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImportSemaphoreWin32HandleInfoKHR>* pImportSemaphoreWin32HandleInfo)
{
    std::string name = "vkImportSemaphoreWin32HandleKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetSemaphoreWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreGetWin32HandleInfoKHR>* pGetWin32HandleInfo,
    PointerDecoder<uint64_t, void*>*            pHandle)
{
    std::string name = "vkGetSemaphoreWin32HandleKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkImportSemaphoreFdKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImportSemaphoreFdInfoKHR>* pImportSemaphoreFdInfo)
{
    std::string name = "vkImportSemaphoreFdKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetSemaphoreFdKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreGetFdInfoKHR>* pGetFdInfo,
    PointerDecoder<int>*                        pFd)
{
    std::string name = "vkGetSemaphoreFdKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkCmdPushDescriptorSetKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCreateDescriptorUpdateTemplateKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorUpdateTemplateCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorUpdateTemplate>* pDescriptorUpdateTemplate)
{
    std::string name = "vkCreateDescriptorUpdateTemplateKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyDescriptorUpdateTemplateKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            descriptorUpdateTemplate,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyDescriptorUpdateTemplateKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateRenderPass2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderPassCreateInfo2>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkRenderPass>*         pRenderPass)
{
    std::string name = "vkCreateRenderPass2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginRenderPass2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderPassBeginInfo>* pRenderPassBegin,
    StructPointerDecoder<Decoded_VkSubpassBeginInfo>* pSubpassBeginInfo)
{
    std::string name = "vkCmdBeginRenderPass2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdNextSubpass2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSubpassBeginInfo>* pSubpassBeginInfo,
    StructPointerDecoder<Decoded_VkSubpassEndInfo>* pSubpassEndInfo)
{
    std::string name = "vkCmdNextSubpass2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndRenderPass2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSubpassEndInfo>* pSubpassEndInfo)
{
    std::string name = "vkCmdEndRenderPass2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetSwapchainStatusKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain)
{
    std::string name = "vkGetSwapchainStatusKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceExternalFencePropertiesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceExternalFenceInfo>* pExternalFenceInfo,
    StructPointerDecoder<Decoded_VkExternalFenceProperties>* pExternalFenceProperties)
{
    std::string name = "vkGetPhysicalDeviceExternalFencePropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkImportFenceWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImportFenceWin32HandleInfoKHR>* pImportFenceWin32HandleInfo)
{
    std::string name = "vkImportFenceWin32HandleKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetFenceWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkFenceGetWin32HandleInfoKHR>* pGetWin32HandleInfo,
    PointerDecoder<uint64_t, void*>*            pHandle)
{
    std::string name = "vkGetFenceWin32HandleKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkImportFenceFdKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImportFenceFdInfoKHR>* pImportFenceFdInfo)
{
    std::string name = "vkImportFenceFdKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetFenceFdKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkFenceGetFdInfoKHR>* pGetFdInfo,
    PointerDecoder<int>*                        pFd)
{
    std::string name = "vkGetFenceFdKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkQueryPoolPerformanceCreateInfoKHR>* pPerformanceQueryCreateInfo,
    PointerDecoder<uint32_t>*                   pNumPasses)
{
    std::string name = "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkAcquireProfilingLockKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAcquireProfilingLockInfoKHR>* pInfo)
{
    std::string name = "vkAcquireProfilingLockKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkReleaseProfilingLockKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device)
{
    std::string name = "vkReleaseProfilingLockKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceCapabilities2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSurfaceInfo2KHR>* pSurfaceInfo,
    StructPointerDecoder<Decoded_VkSurfaceCapabilities2KHR>* pSurfaceCapabilities)
{
    std::string name = "vkGetPhysicalDeviceSurfaceCapabilities2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceFormats2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSurfaceInfo2KHR>* pSurfaceInfo,
    PointerDecoder<uint32_t>*                   pSurfaceFormatCount,
    StructPointerDecoder<Decoded_VkSurfaceFormat2KHR>* pSurfaceFormats)
{
    std::string name = "vkGetPhysicalDeviceSurfaceFormats2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceDisplayProperties2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayProperties2KHR>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceDisplayProperties2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceDisplayPlaneProperties2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayPlaneProperties2KHR>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceDisplayPlaneProperties2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDisplayModeProperties2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            display,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkDisplayModeProperties2KHR>* pProperties)
{
    std::string name = "vkGetDisplayModeProperties2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDisplayPlaneCapabilities2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkDisplayPlaneInfo2KHR>* pDisplayPlaneInfo,
    StructPointerDecoder<Decoded_VkDisplayPlaneCapabilities2KHR>* pCapabilities)
{
    std::string name = "vkGetDisplayPlaneCapabilities2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageMemoryRequirements2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageMemoryRequirementsInfo2>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetImageMemoryRequirements2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetBufferMemoryRequirements2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferMemoryRequirementsInfo2>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetBufferMemoryRequirements2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageSparseMemoryRequirements2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageSparseMemoryRequirementsInfo2>* pInfo,
    PointerDecoder<uint32_t>*                   pSparseMemoryRequirementCount,
    StructPointerDecoder<Decoded_VkSparseImageMemoryRequirements2>* pSparseMemoryRequirements)
{
    std::string name = "vkGetImageSparseMemoryRequirements2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateSamplerYcbcrConversionKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSamplerYcbcrConversionCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSamplerYcbcrConversion>* pYcbcrConversion)
{
    std::string name = "vkCreateSamplerYcbcrConversionKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroySamplerYcbcrConversionKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            ycbcrConversion,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroySamplerYcbcrConversionKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkBindBufferMemory2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindBufferMemoryInfo>* pBindInfos)
{
    std::string name = "vkBindBufferMemory2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkBindImageMemory2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindImageMemoryInfo>* pBindInfos)
{
    std::string name = "vkBindImageMemory2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDescriptorSetLayoutSupportKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutSupport>* pSupport)
{
    std::string name = "vkGetDescriptorSetLayoutSupportKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkCmdDrawIndirectCountKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDrawIndexedIndirectCountKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetSemaphoreCounterValueKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            semaphore,
    PointerDecoder<uint64_t>*                   pValue)
{
    std::string name = "vkGetSemaphoreCounterValueKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkWaitSemaphoresKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
    uint64_t                                    timeout)
{
    std::string name = "vkWaitSemaphoresKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkSignalSemaphoreKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo)
{
    std::string name = "vkSignalSemaphoreKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceFragmentShadingRatesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pFragmentShadingRateCount,
    StructPointerDecoder<Decoded_VkPhysicalDeviceFragmentShadingRateKHR>* pFragmentShadingRates)
{
    std::string name = "vkGetPhysicalDeviceFragmentShadingRatesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetFragmentShadingRateKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkExtent2D>*   pFragmentSize,
    PointerDecoder<VkFragmentShadingRateCombinerOpKHR>* combinerOps)
{
    std::string name = "vkCmdSetFragmentShadingRateKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRenderingAttachmentLocationsKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingAttachmentLocationInfo>* pLocationInfo)
{
    std::string name = "vkCmdSetRenderingAttachmentLocationsKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRenderingInputAttachmentIndicesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInputAttachmentIndexInfo>* pInputAttachmentIndexInfo)
{
    std::string name = "vkCmdSetRenderingInputAttachmentIndicesKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkWaitForPresentKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    uint64_t                                    presentId,
    uint64_t                                    timeout)
{
    std::string name = "vkWaitForPresentKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetBufferDeviceAddressKHR(
    const ApiCallInfo&                          call_info,
    VkDeviceAddress                             returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferDeviceAddressInfo>* pInfo)
{
    std::string name = "vkGetBufferDeviceAddressKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetBufferOpaqueCaptureAddressKHR(
    const ApiCallInfo&                          call_info,
    uint64_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferDeviceAddressInfo>* pInfo)
{
    std::string name = "vkGetBufferOpaqueCaptureAddressKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceMemoryOpaqueCaptureAddressKHR(
    const ApiCallInfo&                          call_info,
    uint64_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceMemoryOpaqueCaptureAddressInfo>* pInfo)
{
    std::string name = "vkGetDeviceMemoryOpaqueCaptureAddressKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateDeferredOperationKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDeferredOperationKHR>* pDeferredOperation)
{
    std::string name = "vkCreateDeferredOperationKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyDeferredOperationKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            operation,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyDeferredOperationKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeferredOperationMaxConcurrencyKHR(
    const ApiCallInfo&                          call_info,
    uint32_t                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            operation)
{
    std::string name = "vkGetDeferredOperationMaxConcurrencyKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeferredOperationResultKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            operation)
{
    std::string name = "vkGetDeferredOperationResultKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDeferredOperationJoinKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            operation)
{
    std::string name = "vkDeferredOperationJoinKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPipelineExecutablePropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineInfoKHR>* pPipelineInfo,
    PointerDecoder<uint32_t>*                   pExecutableCount,
    StructPointerDecoder<Decoded_VkPipelineExecutablePropertiesKHR>* pProperties)
{
    std::string name = "vkGetPipelineExecutablePropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPipelineExecutableStatisticsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineExecutableInfoKHR>* pExecutableInfo,
    PointerDecoder<uint32_t>*                   pStatisticCount,
    StructPointerDecoder<Decoded_VkPipelineExecutableStatisticKHR>* pStatistics)
{
    std::string name = "vkGetPipelineExecutableStatisticsKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPipelineExecutableInternalRepresentationsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineExecutableInfoKHR>* pExecutableInfo,
    PointerDecoder<uint32_t>*                   pInternalRepresentationCount,
    StructPointerDecoder<Decoded_VkPipelineExecutableInternalRepresentationKHR>* pInternalRepresentations)
{
    std::string name = "vkGetPipelineExecutableInternalRepresentationsKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkMapMemory2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryMapInfo>* pMemoryMapInfo,
    PointerDecoder<uint64_t, void*>*            ppData)
{
    std::string name = "vkMapMemory2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkUnmapMemory2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryUnmapInfo>* pMemoryUnmapInfo)
{
    std::string name = "vkUnmapMemory2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR>* pQualityLevelInfo,
    StructPointerDecoder<Decoded_VkVideoEncodeQualityLevelPropertiesKHR>* pQualityLevelProperties)
{
    std::string name = "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkGetEncodedVideoSessionParametersKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdEncodeVideoKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkVideoEncodeInfoKHR>* pEncodeInfo)
{
    std::string name = "vkCmdEncodeVideoKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetEvent2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfo)
{
    std::string name = "vkCmdSetEvent2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdResetEvent2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            event,
    VkPipelineStageFlags2                       stageMask)
{
    std::string name = "vkCmdResetEvent2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdWaitEvents2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    eventCount,
    HandlePointerDecoder<VkEvent>*              pEvents,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfos)
{
    std::string name = "vkCmdWaitEvents2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdPipelineBarrier2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDependencyInfo>* pDependencyInfo)
{
    std::string name = "vkCmdPipelineBarrier2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdWriteTimestamp2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlags2                       stage,
    format::HandleId                            queryPool,
    uint32_t                                    query)
{
    std::string name = "vkCmdWriteTimestamp2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkQueueSubmit2KHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    uint32_t                                    submitCount,
    StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
    format::HandleId                            fence)
{
    std::string name = "vkQueueSubmit2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBuffer2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferInfo2>* pCopyBufferInfo)
{
    std::string name = "vkCmdCopyBuffer2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyImage2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageInfo2>* pCopyImageInfo)
{
    std::string name = "vkCmdCopyImage2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyBufferToImage2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferToImageInfo2>* pCopyBufferToImageInfo)
{
    std::string name = "vkCmdCopyBufferToImage2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyImageToBuffer2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageToBufferInfo2>* pCopyImageToBufferInfo)
{
    std::string name = "vkCmdCopyImageToBuffer2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBlitImage2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBlitImageInfo2>* pBlitImageInfo)
{
    std::string name = "vkCmdBlitImage2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdResolveImage2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkResolveImageInfo2>* pResolveImageInfo)
{
    std::string name = "vkCmdResolveImage2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdTraceRaysIndirect2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkDeviceAddress                             indirectDeviceAddress)
{
    std::string name = "vkCmdTraceRaysIndirect2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceBufferMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceBufferMemoryRequirements>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetDeviceBufferMemoryRequirementsKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageMemoryRequirements>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetDeviceImageMemoryRequirementsKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageSparseMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageMemoryRequirements>* pInfo,
    PointerDecoder<uint32_t>*                   pSparseMemoryRequirementCount,
    StructPointerDecoder<Decoded_VkSparseImageMemoryRequirements2>* pSparseMemoryRequirements)
{
    std::string name = "vkGetDeviceImageSparseMemoryRequirementsKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBindIndexBuffer2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkIndexType                                 indexType)
{
    std::string name = "vkCmdBindIndexBuffer2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetRenderingAreaGranularityKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderingAreaInfo>* pRenderingAreaInfo,
    StructPointerDecoder<Decoded_VkExtent2D>*   pGranularity)
{
    std::string name = "vkGetRenderingAreaGranularityKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceImageSubresourceLayoutKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceImageSubresourceInfo>* pInfo,
    StructPointerDecoder<Decoded_VkSubresourceLayout2>* pLayout)
{
    std::string name = "vkGetDeviceImageSubresourceLayoutKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageSubresourceLayout2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkImageSubresource2>* pSubresource,
    StructPointerDecoder<Decoded_VkSubresourceLayout2>* pLayout)
{
    std::string name = "vkGetImageSubresourceLayout2KHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreatePipelineBinariesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineBinaryCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    StructPointerDecoder<Decoded_VkPipelineBinaryHandlesInfoKHR>* pBinaries)
{
    std::string name = "vkCreatePipelineBinariesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyPipelineBinaryKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            pipelineBinary,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyPipelineBinaryKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPipelineKeyKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineCreateInfoKHR>* pPipelineCreateInfo,
    StructPointerDecoder<Decoded_VkPipelineBinaryKeyKHR>* pPipelineKey)
{
    std::string name = "vkGetPipelineKeyKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkGetPipelineBinaryDataKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkReleaseCapturedPipelineDataKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkReleaseCapturedPipelineDataInfoKHR>* pInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkReleaseCapturedPipelineDataKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkCooperativeMatrixPropertiesKHR>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineStippleKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern)
{
    std::string name = "vkCmdSetLineStippleKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pTimeDomainCount,
    PointerDecoder<VkTimeDomainKHR>*            pTimeDomains)
{
    std::string name = "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkGetCalibratedTimestampsKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBindDescriptorSets2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBindDescriptorSetsInfo>* pBindDescriptorSetsInfo)
{
    std::string name = "vkCmdBindDescriptorSets2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdPushConstants2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPushConstantsInfo>* pPushConstantsInfo)
{
    std::string name = "vkCmdPushConstants2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdPushDescriptorSet2KHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPushDescriptorSetInfo>* pPushDescriptorSetInfo)
{
    std::string name = "vkCmdPushDescriptorSet2KHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDescriptorBufferOffsets2EXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSetDescriptorBufferOffsetsInfoEXT>* pSetDescriptorBufferOffsetsInfo)
{
    std::string name = "vkCmdSetDescriptorBufferOffsets2EXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBindDescriptorBufferEmbeddedSamplersInfoEXT>* pBindDescriptorBufferEmbeddedSamplersInfo)
{
    std::string name = "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkFrameBoundaryANDROID(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            semaphore,
    format::HandleId                            image)
{
    std::string name = "vkFrameBoundaryANDROID";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateDebugReportCallbackEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkDebugReportCallbackCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDebugReportCallbackEXT>* pCallback)
{
    std::string name = "vkCreateDebugReportCallbackEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyDebugReportCallbackEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    format::HandleId                            callback,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyDebugReportCallbackEXT";
    WriteBlockEnd(name);
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
    std::string name = "vkDebugReportMessageEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDebugMarkerSetObjectTagEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDebugMarkerObjectTagInfoEXT>* pTagInfo)
{
    std::string name = "vkDebugMarkerSetObjectTagEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDebugMarkerSetObjectNameEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDebugMarkerObjectNameInfoEXT>* pNameInfo)
{
    std::string name = "vkDebugMarkerSetObjectNameEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdDebugMarkerBeginEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDebugMarkerMarkerInfoEXT>* pMarkerInfo)
{
    std::string name = "vkCmdDebugMarkerBeginEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDebugMarkerEndEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    std::string name = "vkCmdDebugMarkerEndEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDebugMarkerInsertEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDebugMarkerMarkerInfoEXT>* pMarkerInfo)
{
    std::string name = "vkCmdDebugMarkerInsertEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdBindTransformFeedbackBuffersEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginTransformFeedbackEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstCounterBuffer,
    uint32_t                                    counterBufferCount,
    HandlePointerDecoder<VkBuffer>*             pCounterBuffers,
    PointerDecoder<VkDeviceSize>*               pCounterBufferOffsets)
{
    std::string name = "vkCmdBeginTransformFeedbackEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndTransformFeedbackEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstCounterBuffer,
    uint32_t                                    counterBufferCount,
    HandlePointerDecoder<VkBuffer>*             pCounterBuffers,
    PointerDecoder<VkDeviceSize>*               pCounterBufferOffsets)
{
    std::string name = "vkCmdEndTransformFeedbackEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginQueryIndexedEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    query,
    VkQueryControlFlags                         flags,
    uint32_t                                    index)
{
    std::string name = "vkCmdBeginQueryIndexedEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndQueryIndexedEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            queryPool,
    uint32_t                                    query,
    uint32_t                                    index)
{
    std::string name = "vkCmdEndQueryIndexedEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDrawIndirectByteCountEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetImageViewHandleNVX(
    const ApiCallInfo&                          call_info,
    uint32_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageViewHandleInfoNVX>* pInfo)
{
    std::string name = "vkGetImageViewHandleNVX";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageViewHandle64NVX(
    const ApiCallInfo&                          call_info,
    uint64_t                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImageViewHandleInfoNVX>* pInfo)
{
    std::string name = "vkGetImageViewHandle64NVX";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageViewAddressNVX(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            imageView,
    StructPointerDecoder<Decoded_VkImageViewAddressPropertiesNVX>* pProperties)
{
    std::string name = "vkGetImageViewAddressNVX";
    WriteBlockEnd(name);
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
    std::string name = "vkCmdDrawIndirectCountAMD";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDrawIndexedIndirectCountAMD";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkGetShaderInfoAMD";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateStreamDescriptorSurfaceGGP(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkStreamDescriptorSurfaceCreateInfoGGP>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateStreamDescriptorSurfaceGGP";
    WriteBlockEnd(name);
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
    std::string name = "vkGetPhysicalDeviceExternalImageFormatPropertiesNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryWin32HandleNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            memory,
    VkExternalMemoryHandleTypeFlagsNV           handleType,
    PointerDecoder<uint64_t, void*>*            pHandle)
{
    std::string name = "vkGetMemoryWin32HandleNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateViSurfaceNN(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkViSurfaceCreateInfoNN>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateViSurfaceNN";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginConditionalRenderingEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkConditionalRenderingBeginInfoEXT>* pConditionalRenderingBegin)
{
    std::string name = "vkCmdBeginConditionalRenderingEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndConditionalRenderingEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    std::string name = "vkCmdEndConditionalRenderingEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportWScalingNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkViewportWScalingNV>* pViewportWScalings)
{
    std::string name = "vkCmdSetViewportWScalingNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkReleaseDisplayEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            display)
{
    std::string name = "vkReleaseDisplayEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkAcquireXlibDisplayEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint64_t                                    dpy,
    format::HandleId                            display)
{
    std::string name = "vkAcquireXlibDisplayEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetRandROutputDisplayEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint64_t                                    dpy,
    size_t                                      rrOutput,
    HandlePointerDecoder<VkDisplayKHR>*         pDisplay)
{
    std::string name = "vkGetRandROutputDisplayEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfaceCapabilities2EXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            surface,
    StructPointerDecoder<Decoded_VkSurfaceCapabilities2EXT>* pSurfaceCapabilities)
{
    std::string name = "vkGetPhysicalDeviceSurfaceCapabilities2EXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDisplayPowerControlEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            display,
    StructPointerDecoder<Decoded_VkDisplayPowerInfoEXT>* pDisplayPowerInfo)
{
    std::string name = "vkDisplayPowerControlEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkRegisterDeviceEventEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceEventInfoEXT>* pDeviceEventInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkFence>*              pFence)
{
    std::string name = "vkRegisterDeviceEventEXT";
    WriteBlockEnd(name);
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
    std::string name = "vkRegisterDisplayEventEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetSwapchainCounterEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    VkSurfaceCounterFlagBitsEXT                 counter,
    PointerDecoder<uint64_t>*                   pCounterValue)
{
    std::string name = "vkGetSwapchainCounterEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetRefreshCycleDurationGOOGLE(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkRefreshCycleDurationGOOGLE>* pDisplayTimingProperties)
{
    std::string name = "vkGetRefreshCycleDurationGOOGLE";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPastPresentationTimingGOOGLE(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    PointerDecoder<uint32_t>*                   pPresentationTimingCount,
    StructPointerDecoder<Decoded_VkPastPresentationTimingGOOGLE>* pPresentationTimings)
{
    std::string name = "vkGetPastPresentationTimingGOOGLE";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDiscardRectangleEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstDiscardRectangle,
    uint32_t                                    discardRectangleCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pDiscardRectangles)
{
    std::string name = "vkCmdSetDiscardRectangleEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDiscardRectangleEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    discardRectangleEnable)
{
    std::string name = "vkCmdSetDiscardRectangleEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDiscardRectangleModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkDiscardRectangleModeEXT                   discardRectangleMode)
{
    std::string name = "vkCmdSetDiscardRectangleModeEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkSetHdrMetadataEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    uint32_t                                    swapchainCount,
    HandlePointerDecoder<VkSwapchainKHR>*       pSwapchains,
    StructPointerDecoder<Decoded_VkHdrMetadataEXT>* pMetadata)
{
    std::string name = "vkSetHdrMetadataEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateIOSSurfaceMVK(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkIOSSurfaceCreateInfoMVK>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateIOSSurfaceMVK";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateMacOSSurfaceMVK(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkMacOSSurfaceCreateInfoMVK>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateMacOSSurfaceMVK";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkSetDebugUtilsObjectNameEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDebugUtilsObjectNameInfoEXT>* pNameInfo)
{
    std::string name = "vkSetDebugUtilsObjectNameEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkSetDebugUtilsObjectTagEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDebugUtilsObjectTagInfoEXT>* pTagInfo)
{
    std::string name = "vkSetDebugUtilsObjectTagEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkQueueBeginDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue,
    StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo)
{
    std::string name = "vkQueueBeginDebugUtilsLabelEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkQueueEndDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue)
{
    std::string name = "vkQueueEndDebugUtilsLabelEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkQueueInsertDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue,
    StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo)
{
    std::string name = "vkQueueInsertDebugUtilsLabelEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBeginDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo)
{
    std::string name = "vkCmdBeginDebugUtilsLabelEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdEndDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer)
{
    std::string name = "vkCmdEndDebugUtilsLabelEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdInsertDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo)
{
    std::string name = "vkCmdInsertDebugUtilsLabelEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCreateDebugUtilsMessengerEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkDebugUtilsMessengerCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDebugUtilsMessengerEXT>* pMessenger)
{
    std::string name = "vkCreateDebugUtilsMessengerEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyDebugUtilsMessengerEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    format::HandleId                            messenger,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyDebugUtilsMessengerEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkSubmitDebugUtilsMessageEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            instance,
    VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
    StructPointerDecoder<Decoded_VkDebugUtilsMessengerCallbackDataEXT>* pCallbackData)
{
    std::string name = "vkSubmitDebugUtilsMessageEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetAndroidHardwareBufferPropertiesANDROID(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint64_t                                    buffer,
    StructPointerDecoder<Decoded_VkAndroidHardwareBufferPropertiesANDROID>* pProperties)
{
    std::string name = "vkGetAndroidHardwareBufferPropertiesANDROID";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryAndroidHardwareBufferANDROID(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetAndroidHardwareBufferInfoANDROID>* pInfo,
    PointerDecoder<uint64_t, void*>*            pBuffer)
{
    std::string name = "vkGetMemoryAndroidHardwareBufferANDROID";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetSampleLocationsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkSampleLocationsInfoEXT>* pSampleLocationsInfo)
{
    std::string name = "vkCmdSetSampleLocationsEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceMultisamplePropertiesEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            physicalDevice,
    VkSampleCountFlagBits                       samples,
    StructPointerDecoder<Decoded_VkMultisamplePropertiesEXT>* pMultisampleProperties)
{
    std::string name = "vkGetPhysicalDeviceMultisamplePropertiesEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageDrmFormatModifierPropertiesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkImageDrmFormatModifierPropertiesEXT>* pProperties)
{
    std::string name = "vkGetImageDrmFormatModifierPropertiesEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateValidationCacheEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkValidationCacheCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkValidationCacheEXT>* pValidationCache)
{
    std::string name = "vkCreateValidationCacheEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyValidationCacheEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            validationCache,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyValidationCacheEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkMergeValidationCachesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            dstCache,
    uint32_t                                    srcCacheCount,
    HandlePointerDecoder<VkValidationCacheEXT>* pSrcCaches)
{
    std::string name = "vkMergeValidationCachesEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetValidationCacheDataEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            validationCache,
    PointerDecoder<size_t>*                     pDataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    std::string name = "vkGetValidationCacheDataEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBindShadingRateImageNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            imageView,
    VkImageLayout                               imageLayout)
{
    std::string name = "vkCmdBindShadingRateImageNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportShadingRatePaletteNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkShadingRatePaletteNV>* pShadingRatePalettes)
{
    std::string name = "vkCmdSetViewportShadingRatePaletteNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoarseSampleOrderNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCoarseSampleOrderTypeNV                   sampleOrderType,
    uint32_t                                    customSampleOrderCount,
    StructPointerDecoder<Decoded_VkCoarseSampleOrderCustomNV>* pCustomSampleOrders)
{
    std::string name = "vkCmdSetCoarseSampleOrderNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCreateAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAccelerationStructureCreateInfoNV>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkAccelerationStructureNV>* pAccelerationStructure)
{
    std::string name = "vkCreateAccelerationStructureNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            accelerationStructure,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyAccelerationStructureNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetAccelerationStructureMemoryRequirementsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAccelerationStructureMemoryRequirementsInfoNV>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2KHR>* pMemoryRequirements)
{
    std::string name = "vkGetAccelerationStructureMemoryRequirementsNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkBindAccelerationStructureMemoryNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    bindInfoCount,
    StructPointerDecoder<Decoded_VkBindAccelerationStructureMemoryInfoNV>* pBindInfos)
{
    std::string name = "vkBindAccelerationStructureMemoryNV";
    WriteBlockEnd(name);
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
    std::string name = "vkCmdBuildAccelerationStructureNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            dst,
    format::HandleId                            src,
    VkCopyAccelerationStructureModeKHR          mode)
{
    std::string name = "vkCmdCopyAccelerationStructureNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdTraceRaysNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCreateRayTracingPipelinesNV";
    WriteBlockEnd(name);
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
    std::string name = "vkGetRayTracingShaderGroupHandlesKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkGetRayTracingShaderGroupHandlesNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetAccelerationStructureHandleNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            accelerationStructure,
    size_t                                      dataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    std::string name = "vkGetAccelerationStructureHandleNV";
    WriteBlockEnd(name);
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
    std::string name = "vkCmdWriteAccelerationStructuresPropertiesNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCompileDeferredNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            pipeline,
    uint32_t                                    shader)
{
    std::string name = "vkCompileDeferredNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryHostPointerPropertiesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    uint64_t                                    pHostPointer,
    StructPointerDecoder<Decoded_VkMemoryHostPointerPropertiesEXT>* pMemoryHostPointerProperties)
{
    std::string name = "vkGetMemoryHostPointerPropertiesEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdWriteBufferMarkerAMD(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlagBits                     pipelineStage,
    format::HandleId                            dstBuffer,
    VkDeviceSize                                dstOffset,
    uint32_t                                    marker)
{
    std::string name = "vkCmdWriteBufferMarkerAMD";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdWriteBufferMarker2AMD(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineStageFlags2                       stage,
    format::HandleId                            dstBuffer,
    VkDeviceSize                                dstOffset,
    uint32_t                                    marker)
{
    std::string name = "vkCmdWriteBufferMarker2AMD";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pTimeDomainCount,
    PointerDecoder<VkTimeDomainKHR>*            pTimeDomains)
{
    std::string name = "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT";
    WriteBlockEnd(name);
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
    std::string name = "vkGetCalibratedTimestampsEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMeshTasksNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    taskCount,
    uint32_t                                    firstTask)
{
    std::string name = "vkCmdDrawMeshTasksNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMeshTasksIndirectNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride)
{
    std::string name = "vkCmdDrawMeshTasksIndirectNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDrawMeshTasksIndirectCountNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetExclusiveScissorEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstExclusiveScissor,
    uint32_t                                    exclusiveScissorCount,
    PointerDecoder<VkBool32>*                   pExclusiveScissorEnables)
{
    std::string name = "vkCmdSetExclusiveScissorEnableNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetExclusiveScissorNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstExclusiveScissor,
    uint32_t                                    exclusiveScissorCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pExclusiveScissors)
{
    std::string name = "vkCmdSetExclusiveScissorNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCheckpointNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint64_t                                    pCheckpointMarker)
{
    std::string name = "vkCmdSetCheckpointNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetQueueCheckpointDataNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue,
    PointerDecoder<uint32_t>*                   pCheckpointDataCount,
    StructPointerDecoder<Decoded_VkCheckpointDataNV>* pCheckpointData)
{
    std::string name = "vkGetQueueCheckpointDataNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetQueueCheckpointData2NV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue,
    PointerDecoder<uint32_t>*                   pCheckpointDataCount,
    StructPointerDecoder<Decoded_VkCheckpointData2NV>* pCheckpointData)
{
    std::string name = "vkGetQueueCheckpointData2NV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkInitializePerformanceApiINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkInitializePerformanceApiInfoINTEL>* pInitializeInfo)
{
    std::string name = "vkInitializePerformanceApiINTEL";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkUninitializePerformanceApiINTEL(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device)
{
    std::string name = "vkUninitializePerformanceApiINTEL";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPerformanceMarkerINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPerformanceMarkerInfoINTEL>* pMarkerInfo)
{
    std::string name = "vkCmdSetPerformanceMarkerINTEL";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPerformanceStreamMarkerINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPerformanceStreamMarkerInfoINTEL>* pMarkerInfo)
{
    std::string name = "vkCmdSetPerformanceStreamMarkerINTEL";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPerformanceOverrideINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkPerformanceOverrideInfoINTEL>* pOverrideInfo)
{
    std::string name = "vkCmdSetPerformanceOverrideINTEL";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkAcquirePerformanceConfigurationINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPerformanceConfigurationAcquireInfoINTEL>* pAcquireInfo,
    HandlePointerDecoder<VkPerformanceConfigurationINTEL>* pConfiguration)
{
    std::string name = "vkAcquirePerformanceConfigurationINTEL";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkReleasePerformanceConfigurationINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            configuration)
{
    std::string name = "vkReleasePerformanceConfigurationINTEL";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkQueueSetPerformanceConfigurationINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            queue,
    format::HandleId                            configuration)
{
    std::string name = "vkQueueSetPerformanceConfigurationINTEL";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPerformanceParameterINTEL(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkPerformanceParameterTypeINTEL             parameter,
    StructPointerDecoder<Decoded_VkPerformanceValueINTEL>* pValue)
{
    std::string name = "vkGetPerformanceParameterINTEL";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkSetLocalDimmingAMD(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            swapChain,
    VkBool32                                    localDimmingEnable)
{
    std::string name = "vkSetLocalDimmingAMD";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateImagePipeSurfaceFUCHSIA(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkImagePipeSurfaceCreateInfoFUCHSIA>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateImagePipeSurfaceFUCHSIA";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateMetalSurfaceEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkMetalSurfaceCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateMetalSurfaceEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetBufferDeviceAddressEXT(
    const ApiCallInfo&                          call_info,
    VkDeviceAddress                             returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkBufferDeviceAddressInfo>* pInfo)
{
    std::string name = "vkGetBufferDeviceAddressEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceToolPropertiesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pToolCount,
    StructPointerDecoder<Decoded_VkPhysicalDeviceToolProperties>* pToolProperties)
{
    std::string name = "vkGetPhysicalDeviceToolPropertiesEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkCooperativeMatrixPropertiesNV>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pCombinationCount,
    StructPointerDecoder<Decoded_VkFramebufferMixedSamplesCombinationNV>* pCombinations)
{
    std::string name = "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceSurfacePresentModes2EXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSurfaceInfo2KHR>* pSurfaceInfo,
    PointerDecoder<uint32_t>*                   pPresentModeCount,
    PointerDecoder<VkPresentModeKHR>*           pPresentModes)
{
    std::string name = "vkGetPhysicalDeviceSurfacePresentModes2EXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkAcquireFullScreenExclusiveModeEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain)
{
    std::string name = "vkAcquireFullScreenExclusiveModeEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkReleaseFullScreenExclusiveModeEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain)
{
    std::string name = "vkReleaseFullScreenExclusiveModeEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceGroupSurfacePresentModes2EXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPhysicalDeviceSurfaceInfo2KHR>* pSurfaceInfo,
    PointerDecoder<VkDeviceGroupPresentModeFlagsKHR>* pModes)
{
    std::string name = "vkGetDeviceGroupSurfacePresentModes2EXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateHeadlessSurfaceEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkHeadlessSurfaceCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateHeadlessSurfaceEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineStippleEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern)
{
    std::string name = "vkCmdSetLineStippleEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkResetQueryPoolEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount)
{
    std::string name = "vkResetQueryPoolEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCullModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCullModeFlags                             cullMode)
{
    std::string name = "vkCmdSetCullModeEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetFrontFaceEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkFrontFace                                 frontFace)
{
    std::string name = "vkCmdSetFrontFaceEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPrimitiveTopologyEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPrimitiveTopology                         primitiveTopology)
{
    std::string name = "vkCmdSetPrimitiveTopologyEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportWithCountEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkViewport>*   pViewports)
{
    std::string name = "vkCmdSetViewportWithCountEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetScissorWithCountEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    scissorCount,
    StructPointerDecoder<Decoded_VkRect2D>*     pScissors)
{
    std::string name = "vkCmdSetScissorWithCountEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdBindVertexBuffers2EXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthTestEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthTestEnable)
{
    std::string name = "vkCmdSetDepthTestEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthWriteEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthWriteEnable)
{
    std::string name = "vkCmdSetDepthWriteEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthCompareOpEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCompareOp                                 depthCompareOp)
{
    std::string name = "vkCmdSetDepthCompareOpEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBoundsTestEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthBoundsTestEnable)
{
    std::string name = "vkCmdSetDepthBoundsTestEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetStencilTestEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    stencilTestEnable)
{
    std::string name = "vkCmdSetStencilTestEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdSetStencilOpEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCopyMemoryToImageEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyMemoryToImageInfo>* pCopyMemoryToImageInfo)
{
    std::string name = "vkCopyMemoryToImageEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCopyImageToMemoryEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyImageToMemoryInfo>* pCopyImageToMemoryInfo)
{
    std::string name = "vkCopyImageToMemoryEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCopyImageToImageEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkCopyImageToImageInfo>* pCopyImageToImageInfo)
{
    std::string name = "vkCopyImageToImageEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkTransitionImageLayoutEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    uint32_t                                    transitionCount,
    StructPointerDecoder<Decoded_VkHostImageLayoutTransitionInfo>* pTransitions)
{
    std::string name = "vkTransitionImageLayoutEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetImageSubresourceLayout2EXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            image,
    StructPointerDecoder<Decoded_VkImageSubresource2>* pSubresource,
    StructPointerDecoder<Decoded_VkSubresourceLayout2>* pLayout)
{
    std::string name = "vkGetImageSubresourceLayout2EXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkReleaseSwapchainImagesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkReleaseSwapchainImagesInfoEXT>* pReleaseInfo)
{
    std::string name = "vkReleaseSwapchainImagesEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetGeneratedCommandsMemoryRequirementsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkGeneratedCommandsMemoryRequirementsInfoNV>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetGeneratedCommandsMemoryRequirementsNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdPreprocessGeneratedCommandsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkGeneratedCommandsInfoNV>* pGeneratedCommandsInfo)
{
    std::string name = "vkCmdPreprocessGeneratedCommandsNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdExecuteGeneratedCommandsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    isPreprocessed,
    StructPointerDecoder<Decoded_VkGeneratedCommandsInfoNV>* pGeneratedCommandsInfo)
{
    std::string name = "vkCmdExecuteGeneratedCommandsNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdBindPipelineShaderGroupNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    format::HandleId                            pipeline,
    uint32_t                                    groupIndex)
{
    std::string name = "vkCmdBindPipelineShaderGroupNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCreateIndirectCommandsLayoutNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkIndirectCommandsLayoutCreateInfoNV>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkIndirectCommandsLayoutNV>* pIndirectCommandsLayout)
{
    std::string name = "vkCreateIndirectCommandsLayoutNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyIndirectCommandsLayoutNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            indirectCommandsLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyIndirectCommandsLayoutNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBias2EXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkDepthBiasInfoEXT>* pDepthBiasInfo)
{
    std::string name = "vkCmdSetDepthBias2EXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkAcquireDrmDisplayEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    int32_t                                     drmFd,
    format::HandleId                            display)
{
    std::string name = "vkAcquireDrmDisplayEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDrmDisplayEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    int32_t                                     drmFd,
    uint32_t                                    connectorId,
    HandlePointerDecoder<VkDisplayKHR>*         display)
{
    std::string name = "vkGetDrmDisplayEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreatePrivateDataSlotEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPrivateDataSlotCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPrivateDataSlot>*    pPrivateDataSlot)
{
    std::string name = "vkCreatePrivateDataSlotEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyPrivateDataSlotEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            privateDataSlot,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyPrivateDataSlotEXT";
    WriteBlockEnd(name);
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
    std::string name = "vkSetPrivateDataEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPrivateDataEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    VkObjectType                                objectType,
    uint64_t                                    objectHandle,
    format::HandleId                            privateDataSlot,
    PointerDecoder<uint64_t>*                   pData)
{
    std::string name = "vkGetPrivateDataEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetFragmentShadingRateEnumNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkFragmentShadingRateNV                     shadingRate,
    PointerDecoder<VkFragmentShadingRateCombinerOpKHR>* combinerOps)
{
    std::string name = "vkCmdSetFragmentShadingRateEnumNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceFaultInfoEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDeviceFaultCountsEXT>* pFaultCounts,
    StructPointerDecoder<Decoded_VkDeviceFaultInfoEXT>* pFaultInfo)
{
    std::string name = "vkGetDeviceFaultInfoEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkAcquireWinrtDisplayNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    format::HandleId                            display)
{
    std::string name = "vkAcquireWinrtDisplayNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetWinrtDisplayNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    HandlePointerDecoder<VkDisplayKHR>*         pDisplay)
{
    std::string name = "vkGetWinrtDisplayNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateDirectFBSurfaceEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkDirectFBSurfaceCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateDirectFBSurfaceEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceDirectFBPresentationSupportEXT(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint64_t                                    dfb)
{
    std::string name = "vkGetPhysicalDeviceDirectFBPresentationSupportEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetVertexInputEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    vertexBindingDescriptionCount,
    StructPointerDecoder<Decoded_VkVertexInputBindingDescription2EXT>* pVertexBindingDescriptions,
    uint32_t                                    vertexAttributeDescriptionCount,
    StructPointerDecoder<Decoded_VkVertexInputAttributeDescription2EXT>* pVertexAttributeDescriptions)
{
    std::string name = "vkCmdSetVertexInputEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryZirconHandleFUCHSIA(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetZirconHandleInfoFUCHSIA>* pGetZirconHandleInfo,
    PointerDecoder<uint32_t>*                   pZirconHandle)
{
    std::string name = "vkGetMemoryZirconHandleFUCHSIA";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryZirconHandlePropertiesFUCHSIA(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    uint32_t                                    zirconHandle,
    StructPointerDecoder<Decoded_VkMemoryZirconHandlePropertiesFUCHSIA>* pMemoryZirconHandleProperties)
{
    std::string name = "vkGetMemoryZirconHandlePropertiesFUCHSIA";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkImportSemaphoreZirconHandleFUCHSIA(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkImportSemaphoreZirconHandleInfoFUCHSIA>* pImportSemaphoreZirconHandleInfo)
{
    std::string name = "vkImportSemaphoreZirconHandleFUCHSIA";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetSemaphoreZirconHandleFUCHSIA(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkSemaphoreGetZirconHandleInfoFUCHSIA>* pGetZirconHandleInfo,
    PointerDecoder<uint32_t>*                   pZirconHandle)
{
    std::string name = "vkGetSemaphoreZirconHandleFUCHSIA";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBindInvocationMaskHUAWEI(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            imageView,
    VkImageLayout                               imageLayout)
{
    std::string name = "vkCmdBindInvocationMaskHUAWEI";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryRemoteAddressNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetRemoteAddressInfoNV>* pMemoryGetRemoteAddressInfo,
    PointerDecoder<uint64_t, void*>*            pAddress)
{
    std::string name = "vkGetMemoryRemoteAddressNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPatchControlPointsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    patchControlPoints)
{
    std::string name = "vkCmdSetPatchControlPointsEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRasterizerDiscardEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    rasterizerDiscardEnable)
{
    std::string name = "vkCmdSetRasterizerDiscardEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthBiasEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthBiasEnable)
{
    std::string name = "vkCmdSetDepthBiasEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLogicOpEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkLogicOp                                   logicOp)
{
    std::string name = "vkCmdSetLogicOpEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPrimitiveRestartEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    primitiveRestartEnable)
{
    std::string name = "vkCmdSetPrimitiveRestartEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCreateScreenSurfaceQNX(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            instance,
    StructPointerDecoder<Decoded_VkScreenSurfaceCreateInfoQNX>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSurfaceKHR>*         pSurface)
{
    std::string name = "vkCreateScreenSurfaceQNX";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceScreenPresentationSupportQNX(
    const ApiCallInfo&                          call_info,
    VkBool32                                    returnValue,
    format::HandleId                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint64_t                                    window)
{
    std::string name = "vkGetPhysicalDeviceScreenPresentationSupportQNX";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetColorWriteEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    attachmentCount,
    PointerDecoder<VkBool32>*                   pColorWriteEnables)
{
    std::string name = "vkCmdSetColorWriteEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDrawMultiEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDrawMultiIndexedEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCreateMicromapEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMicromapCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkMicromapEXT>*        pMicromap)
{
    std::string name = "vkCreateMicromapEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyMicromapEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            micromap,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyMicromapEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBuildMicromapsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    infoCount,
    StructPointerDecoder<Decoded_VkMicromapBuildInfoEXT>* pInfos)
{
    std::string name = "vkCmdBuildMicromapsEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkBuildMicromapsEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    uint32_t                                    infoCount,
    StructPointerDecoder<Decoded_VkMicromapBuildInfoEXT>* pInfos)
{
    std::string name = "vkBuildMicromapsEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCopyMicromapEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    StructPointerDecoder<Decoded_VkCopyMicromapInfoEXT>* pInfo)
{
    std::string name = "vkCopyMicromapEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCopyMicromapToMemoryEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    StructPointerDecoder<Decoded_VkCopyMicromapToMemoryInfoEXT>* pInfo)
{
    std::string name = "vkCopyMicromapToMemoryEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCopyMemoryToMicromapEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    StructPointerDecoder<Decoded_VkCopyMemoryToMicromapInfoEXT>* pInfo)
{
    std::string name = "vkCopyMemoryToMicromapEXT";
    WriteBlockEnd(name);
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
    std::string name = "vkWriteMicromapsPropertiesEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyMicromapEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyMicromapInfoEXT>* pInfo)
{
    std::string name = "vkCmdCopyMicromapEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyMicromapToMemoryEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyMicromapToMemoryInfoEXT>* pInfo)
{
    std::string name = "vkCmdCopyMicromapToMemoryEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyMemoryToMicromapEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyMemoryToMicromapInfoEXT>* pInfo)
{
    std::string name = "vkCmdCopyMemoryToMicromapEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdWriteMicromapsPropertiesEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceMicromapCompatibilityEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMicromapVersionInfoEXT>* pVersionInfo,
    PointerDecoder<VkAccelerationStructureCompatibilityKHR>* pCompatibility)
{
    std::string name = "vkGetDeviceMicromapCompatibilityEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMicromapBuildSizesEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    VkAccelerationStructureBuildTypeKHR         buildType,
    StructPointerDecoder<Decoded_VkMicromapBuildInfoEXT>* pBuildInfo,
    StructPointerDecoder<Decoded_VkMicromapBuildSizesInfoEXT>* pSizeInfo)
{
    std::string name = "vkGetMicromapBuildSizesEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawClusterHUAWEI(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ)
{
    std::string name = "vkCmdDrawClusterHUAWEI";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawClusterIndirectHUAWEI(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset)
{
    std::string name = "vkCmdDrawClusterIndirectHUAWEI";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkSetDeviceMemoryPriorityEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            memory,
    float                                       priority)
{
    std::string name = "vkSetDeviceMemoryPriorityEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDescriptorSetLayoutHostMappingInfoVALVE(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkDescriptorSetBindingReferenceVALVE>* pBindingReference,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutHostMappingInfoVALVE>* pHostMapping)
{
    std::string name = "vkGetDescriptorSetLayoutHostMappingInfoVALVE";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDescriptorSetHostMappingVALVE(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            descriptorSet,
    PointerDecoder<uint64_t, void*>*            ppData)
{
    std::string name = "vkGetDescriptorSetHostMappingVALVE";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPipelineIndirectMemoryRequirementsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkComputePipelineCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetPipelineIndirectMemoryRequirementsNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdUpdatePipelineIndirectBufferNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    format::HandleId                            pipeline)
{
    std::string name = "vkCmdUpdatePipelineIndirectBufferNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetPipelineIndirectDeviceAddressNV(
    const ApiCallInfo&                          call_info,
    VkDeviceAddress                             returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPipelineIndirectDeviceAddressInfoNV>* pInfo)
{
    std::string name = "vkGetPipelineIndirectDeviceAddressNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthClampEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthClampEnable)
{
    std::string name = "vkCmdSetDepthClampEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetPolygonModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkPolygonMode                               polygonMode)
{
    std::string name = "vkCmdSetPolygonModeEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRasterizationSamplesEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkSampleCountFlagBits                       rasterizationSamples)
{
    std::string name = "vkCmdSetRasterizationSamplesEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetSampleMaskEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkSampleCountFlagBits                       samples,
    PointerDecoder<VkSampleMask>*               pSampleMask)
{
    std::string name = "vkCmdSetSampleMaskEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetAlphaToCoverageEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    alphaToCoverageEnable)
{
    std::string name = "vkCmdSetAlphaToCoverageEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetAlphaToOneEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    alphaToOneEnable)
{
    std::string name = "vkCmdSetAlphaToOneEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLogicOpEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    logicOpEnable)
{
    std::string name = "vkCmdSetLogicOpEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetColorBlendEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    PointerDecoder<VkBool32>*                   pColorBlendEnables)
{
    std::string name = "vkCmdSetColorBlendEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetColorBlendEquationEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    StructPointerDecoder<Decoded_VkColorBlendEquationEXT>* pColorBlendEquations)
{
    std::string name = "vkCmdSetColorBlendEquationEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetColorWriteMaskEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    PointerDecoder<VkColorComponentFlags>*      pColorWriteMasks)
{
    std::string name = "vkCmdSetColorWriteMaskEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetTessellationDomainOriginEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkTessellationDomainOrigin                  domainOrigin)
{
    std::string name = "vkCmdSetTessellationDomainOriginEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRasterizationStreamEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    rasterizationStream)
{
    std::string name = "vkCmdSetRasterizationStreamEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetConservativeRasterizationModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkConservativeRasterizationModeEXT          conservativeRasterizationMode)
{
    std::string name = "vkCmdSetConservativeRasterizationModeEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetExtraPrimitiveOverestimationSizeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    float                                       extraPrimitiveOverestimationSize)
{
    std::string name = "vkCmdSetExtraPrimitiveOverestimationSizeEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthClipEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    depthClipEnable)
{
    std::string name = "vkCmdSetDepthClipEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetSampleLocationsEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    sampleLocationsEnable)
{
    std::string name = "vkCmdSetSampleLocationsEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetColorBlendAdvancedEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstAttachment,
    uint32_t                                    attachmentCount,
    StructPointerDecoder<Decoded_VkColorBlendAdvancedEXT>* pColorBlendAdvanced)
{
    std::string name = "vkCmdSetColorBlendAdvancedEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetProvokingVertexModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkProvokingVertexModeEXT                    provokingVertexMode)
{
    std::string name = "vkCmdSetProvokingVertexModeEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineRasterizationModeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkLineRasterizationModeEXT                  lineRasterizationMode)
{
    std::string name = "vkCmdSetLineRasterizationModeEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetLineStippleEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    stippledLineEnable)
{
    std::string name = "vkCmdSetLineStippleEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthClipNegativeOneToOneEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    negativeOneToOne)
{
    std::string name = "vkCmdSetDepthClipNegativeOneToOneEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportWScalingEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    viewportWScalingEnable)
{
    std::string name = "vkCmdSetViewportWScalingEnableNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetViewportSwizzleNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    StructPointerDecoder<Decoded_VkViewportSwizzleNV>* pViewportSwizzles)
{
    std::string name = "vkCmdSetViewportSwizzleNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageToColorEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    coverageToColorEnable)
{
    std::string name = "vkCmdSetCoverageToColorEnableNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageToColorLocationNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    coverageToColorLocation)
{
    std::string name = "vkCmdSetCoverageToColorLocationNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageModulationModeNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCoverageModulationModeNV                  coverageModulationMode)
{
    std::string name = "vkCmdSetCoverageModulationModeNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageModulationTableEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    coverageModulationTableEnable)
{
    std::string name = "vkCmdSetCoverageModulationTableEnableNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageModulationTableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    coverageModulationTableCount,
    PointerDecoder<float>*                      pCoverageModulationTable)
{
    std::string name = "vkCmdSetCoverageModulationTableNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetShadingRateImageEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    shadingRateImageEnable)
{
    std::string name = "vkCmdSetShadingRateImageEnableNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRepresentativeFragmentTestEnableNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    representativeFragmentTestEnable)
{
    std::string name = "vkCmdSetRepresentativeFragmentTestEnableNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetCoverageReductionModeNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkCoverageReductionModeNV                   coverageReductionMode)
{
    std::string name = "vkCmdSetCoverageReductionModeNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetShaderModuleIdentifierEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            shaderModule,
    StructPointerDecoder<Decoded_VkShaderModuleIdentifierEXT>* pIdentifier)
{
    std::string name = "vkGetShaderModuleIdentifierEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetShaderModuleCreateInfoIdentifierEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkShaderModuleCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkShaderModuleIdentifierEXT>* pIdentifier)
{
    std::string name = "vkGetShaderModuleCreateInfoIdentifierEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceOpticalFlowImageFormatsNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    StructPointerDecoder<Decoded_VkOpticalFlowImageFormatInfoNV>* pOpticalFlowImageFormatInfo,
    PointerDecoder<uint32_t>*                   pFormatCount,
    StructPointerDecoder<Decoded_VkOpticalFlowImageFormatPropertiesNV>* pImageFormatProperties)
{
    std::string name = "vkGetPhysicalDeviceOpticalFlowImageFormatsNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateOpticalFlowSessionNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkOpticalFlowSessionCreateInfoNV>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkOpticalFlowSessionNV>* pSession)
{
    std::string name = "vkCreateOpticalFlowSessionNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyOpticalFlowSessionNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            session,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyOpticalFlowSessionNV";
    WriteBlockEnd(name);
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
    std::string name = "vkBindOpticalFlowSessionImageNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdOpticalFlowExecuteNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            session,
    StructPointerDecoder<Decoded_VkOpticalFlowExecuteInfoNV>* pExecuteInfo)
{
    std::string name = "vkCmdOpticalFlowExecuteNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkAntiLagUpdateAMD(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAntiLagDataAMD>* pData)
{
    std::string name = "vkAntiLagUpdateAMD";
    WriteBlockEnd(name);
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
    std::string name = "vkCreateShadersEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyShaderEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            shader,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyShaderEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetShaderBinaryDataEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            shader,
    PointerDecoder<size_t>*                     pDataSize,
    PointerDecoder<uint8_t>*                    pData)
{
    std::string name = "vkGetShaderBinaryDataEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBindShadersEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    stageCount,
    PointerDecoder<VkShaderStageFlagBits>*      pStages,
    HandlePointerDecoder<VkShaderEXT>*          pShaders)
{
    std::string name = "vkCmdBindShadersEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdSetDepthClampRangeEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkDepthClampModeEXT                         depthClampMode,
    StructPointerDecoder<Decoded_VkDepthClampRangeEXT>* pDepthClampRange)
{
    std::string name = "vkCmdSetDepthClampRangeEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetFramebufferTilePropertiesQCOM(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            framebuffer,
    PointerDecoder<uint32_t>*                   pPropertiesCount,
    StructPointerDecoder<Decoded_VkTilePropertiesQCOM>* pProperties)
{
    std::string name = "vkGetFramebufferTilePropertiesQCOM";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetDynamicRenderingTilePropertiesQCOM(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkRenderingInfo>* pRenderingInfo,
    StructPointerDecoder<Decoded_VkTilePropertiesQCOM>* pProperties)
{
    std::string name = "vkGetDynamicRenderingTilePropertiesQCOM";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCooperativeVectorPropertiesNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkCooperativeVectorPropertiesNV>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceCooperativeVectorPropertiesNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkConvertCooperativeVectorMatrixNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkConvertCooperativeVectorMatrixInfoNV>* pInfo)
{
    std::string name = "vkConvertCooperativeVectorMatrixNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdConvertCooperativeVectorMatrixNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    infoCount,
    StructPointerDecoder<Decoded_VkConvertCooperativeVectorMatrixInfoNV>* pInfos)
{
    std::string name = "vkCmdConvertCooperativeVectorMatrixNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkSetLatencySleepModeNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkLatencySleepModeInfoNV>* pSleepModeInfo)
{
    std::string name = "vkSetLatencySleepModeNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkLatencySleepNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkLatencySleepInfoNV>* pSleepInfo)
{
    std::string name = "vkLatencySleepNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkSetLatencyMarkerNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkSetLatencyMarkerInfoNV>* pLatencyMarkerInfo)
{
    std::string name = "vkSetLatencyMarkerNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetLatencyTimingsNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            swapchain,
    StructPointerDecoder<Decoded_VkGetLatencyMarkerInfoNV>* pLatencyMarkerInfo)
{
    std::string name = "vkGetLatencyTimingsNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkQueueNotifyOutOfBandNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            queue,
    StructPointerDecoder<Decoded_VkOutOfBandQueueTypeInfoNV>* pQueueTypeInfo)
{
    std::string name = "vkQueueNotifyOutOfBandNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetAttachmentFeedbackLoopEnableEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkImageAspectFlags                          aspectMask)
{
    std::string name = "vkCmdSetAttachmentFeedbackLoopEnableEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetPartitionedAccelerationStructuresBuildSizesNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkPartitionedAccelerationStructureInstancesInputNV>* pInfo,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildSizesInfoKHR>* pSizeInfo)
{
    std::string name = "vkGetPartitionedAccelerationStructuresBuildSizesNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBuildPartitionedAccelerationStructuresNV(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkBuildPartitionedAccelerationStructureInfoNV>* pBuildInfo)
{
    std::string name = "vkCmdBuildPartitionedAccelerationStructuresNV";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetGeneratedCommandsMemoryRequirementsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkGeneratedCommandsMemoryRequirementsInfoEXT>* pInfo,
    StructPointerDecoder<Decoded_VkMemoryRequirements2>* pMemoryRequirements)
{
    std::string name = "vkGetGeneratedCommandsMemoryRequirementsEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdPreprocessGeneratedCommandsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkGeneratedCommandsInfoEXT>* pGeneratedCommandsInfo,
    format::HandleId                            stateCommandBuffer)
{
    std::string name = "vkCmdPreprocessGeneratedCommandsEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdExecuteGeneratedCommandsEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    VkBool32                                    isPreprocessed,
    StructPointerDecoder<Decoded_VkGeneratedCommandsInfoEXT>* pGeneratedCommandsInfo)
{
    std::string name = "vkCmdExecuteGeneratedCommandsEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCreateIndirectCommandsLayoutEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkIndirectCommandsLayoutCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkIndirectCommandsLayoutEXT>* pIndirectCommandsLayout)
{
    std::string name = "vkCreateIndirectCommandsLayoutEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyIndirectCommandsLayoutEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            indirectCommandsLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyIndirectCommandsLayoutEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateIndirectExecutionSetEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkIndirectExecutionSetCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkIndirectExecutionSetEXT>* pIndirectExecutionSet)
{
    std::string name = "vkCreateIndirectExecutionSetEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyIndirectExecutionSetEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            indirectExecutionSet,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyIndirectExecutionSetEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkUpdateIndirectExecutionSetPipelineEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            indirectExecutionSet,
    uint32_t                                    executionSetWriteCount,
    StructPointerDecoder<Decoded_VkWriteIndirectExecutionSetPipelineEXT>* pExecutionSetWrites)
{
    std::string name = "vkUpdateIndirectExecutionSetPipelineEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkUpdateIndirectExecutionSetShaderEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            indirectExecutionSet,
    uint32_t                                    executionSetWriteCount,
    StructPointerDecoder<Decoded_VkWriteIndirectExecutionSetShaderEXT>* pExecutionSetWrites)
{
    std::string name = "vkUpdateIndirectExecutionSetShaderEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            physicalDevice,
    PointerDecoder<uint32_t>*                   pPropertyCount,
    StructPointerDecoder<Decoded_VkCooperativeMatrixFlexibleDimensionsPropertiesNV>* pProperties)
{
    std::string name = "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryMetalHandleEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkMemoryGetMetalHandleInfoEXT>* pGetMetalHandleInfo,
    PointerDecoder<uint64_t, void*>*            pHandle)
{
    std::string name = "vkGetMemoryMetalHandleEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetMemoryMetalHandlePropertiesEXT(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    uint64_t                                    pHandle,
    StructPointerDecoder<Decoded_VkMemoryMetalHandlePropertiesEXT>* pMemoryMetalHandleProperties)
{
    std::string name = "vkGetMemoryMetalHandlePropertiesEXT";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCreateAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAccelerationStructureCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkAccelerationStructureKHR>* pAccelerationStructure)
{
    std::string name = "vkCreateAccelerationStructureKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkDestroyAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    format::HandleId                            accelerationStructure,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator)
{
    std::string name = "vkDestroyAccelerationStructureKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdBuildAccelerationStructuresKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    infoCount,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppBuildRangeInfos)
{
    std::string name = "vkCmdBuildAccelerationStructuresKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCopyAccelerationStructureToMemoryKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureToMemoryInfoKHR>* pInfo)
{
    std::string name = "vkCopyAccelerationStructureToMemoryKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCopyMemoryToAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    VkResult                                    returnValue,
    format::HandleId                            device,
    format::HandleId                            deferredOperation,
    StructPointerDecoder<Decoded_VkCopyMemoryToAccelerationStructureInfoKHR>* pInfo)
{
    std::string name = "vkCopyMemoryToAccelerationStructureKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkWriteAccelerationStructuresPropertiesKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR>* pInfo)
{
    std::string name = "vkCmdCopyAccelerationStructureKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyAccelerationStructureToMemoryKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureToMemoryInfoKHR>* pInfo)
{
    std::string name = "vkCmdCopyAccelerationStructureToMemoryKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdCopyMemoryToAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    StructPointerDecoder<Decoded_VkCopyMemoryToAccelerationStructureInfoKHR>* pInfo)
{
    std::string name = "vkCmdCopyMemoryToAccelerationStructureKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetAccelerationStructureDeviceAddressKHR(
    const ApiCallInfo&                          call_info,
    VkDeviceAddress                             returnValue,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAccelerationStructureDeviceAddressInfoKHR>* pInfo)
{
    std::string name = "vkGetAccelerationStructureDeviceAddressKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkCmdWriteAccelerationStructuresPropertiesKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetDeviceAccelerationStructureCompatibilityKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    StructPointerDecoder<Decoded_VkAccelerationStructureVersionInfoKHR>* pVersionInfo,
    PointerDecoder<VkAccelerationStructureCompatibilityKHR>* pCompatibility)
{
    std::string name = "vkGetDeviceAccelerationStructureCompatibilityKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkGetAccelerationStructureBuildSizesKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            device,
    VkAccelerationStructureBuildTypeKHR         buildType,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pBuildInfo,
    PointerDecoder<uint32_t>*                   pMaxPrimitiveCounts,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildSizesInfoKHR>* pSizeInfo)
{
    std::string name = "vkGetAccelerationStructureBuildSizesKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkCmdTraceRaysKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCreateRayTracingPipelinesKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR";
    WriteBlockEnd(name);
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
    std::string name = "vkCmdTraceRaysIndirectKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkGetRayTracingShaderGroupStackSizeKHR(
    const ApiCallInfo&                          call_info,
    VkDeviceSize                                returnValue,
    format::HandleId                            device,
    format::HandleId                            pipeline,
    uint32_t                                    group,
    VkShaderGroupShaderKHR                      groupShader)
{
    std::string name = "vkGetRayTracingShaderGroupStackSizeKHR";
    WriteBlockEnd(name);
}

void VulkanExportDiveConsumer::Process_vkCmdSetRayTracingPipelineStackSizeKHR(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    pipelineStackSize)
{
    std::string name = "vkCmdSetRayTracingPipelineStackSizeKHR";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMeshTasksEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ)
{
    std::string name = "vkCmdDrawMeshTasksEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}

void VulkanExportDiveConsumer::Process_vkCmdDrawMeshTasksIndirectEXT(
    const ApiCallInfo&                          call_info,
    format::HandleId                            commandBuffer,
    format::HandleId                            buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride)
{
    std::string name = "vkCmdDrawMeshTasksIndirectEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
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
    std::string name = "vkCmdDrawMeshTasksIndirectCountEXT";
    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);
    uint64_t block_index = call_info.index;
    WriteBlockEnd(name, cmd_buffer_index);
}
GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
