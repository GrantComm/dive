/*
Copyright 2025 Google Inc.

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

#include <vulkan/vk_layer.h>
#include <vulkan/vulkan.h>
#include <deque>
#include <limits>
#include <numeric>
#include <set>
#include <unordered_map>
#include <vector>

#include "gpu_time.h"

namespace DiveLayer
{

class DiveRuntimeLayer
{
public:
    DiveRuntimeLayer();
    ~DiveRuntimeLayer();
    VkResult QueuePresentKHR(PFN_vkQueuePresentKHR   pfn,
                             VkQueue                 queue,
                             const VkPresentInfoKHR* pPresentInfo);

    VkResult CreateImage(PFN_vkCreateImage            pfn,
                         VkDevice                     device,
                         const VkImageCreateInfo*     pCreateInfo,
                         const VkAllocationCallbacks* pAllocator,
                         VkImage*                     pImage);

    void CmdDrawIndexed(PFN_vkCmdDrawIndexed pfn,
                        VkCommandBuffer      commandBuffer,
                        uint32_t             indexCount,
                        uint32_t             instanceCount,
                        uint32_t             firstIndex,
                        int32_t              vertexOffset,
                        uint32_t             firstInstance);

    void CmdResetQueryPool(PFN_vkCmdResetQueryPool pfn,
                           VkCommandBuffer         commandBuffer,
                           VkQueryPool             queryPool,
                           uint32_t                firstQuery,
                           uint32_t                queryCount);

    void CmdWriteTimestamp(PFN_vkCmdWriteTimestamp pfn,
                           VkCommandBuffer         commandBuffer,
                           VkPipelineStageFlagBits pipelineStage,
                           VkQueryPool             queryPool,
                           uint32_t                query);

    VkResult GetQueryPoolResults(PFN_vkGetQueryPoolResults pfn,
                                 VkDevice                  device,
                                 VkQueryPool               queryPool,
                                 uint32_t                  firstQuery,
                                 uint32_t                  queryCount,
                                 size_t                    dataSize,
                                 void*                     pData,
                                 VkDeviceSize              stride,
                                 VkQueryResultFlags        flags);

    void DestroyCommandPool(PFN_vkDestroyCommandPool     pfn,
                            VkDevice                     device,
                            VkCommandPool                commandPool,
                            const VkAllocationCallbacks* pAllocator);

    VkResult AllocateCommandBuffers(PFN_vkAllocateCommandBuffers       pfn,
                                    VkDevice                           device,
                                    const VkCommandBufferAllocateInfo* pAllocateInfo,
                                    VkCommandBuffer*                   pCommandBuffers);

    void FreeCommandBuffers(PFN_vkFreeCommandBuffers pfn,
                            VkDevice                 device,
                            VkCommandPool            commandPool,
                            uint32_t                 commandBufferCount,
                            const VkCommandBuffer*   pCommandBuffers);

    VkResult ResetCommandBuffer(PFN_vkResetCommandBuffer  pfn,
                                VkCommandBuffer           commandBuffer,
                                VkCommandBufferResetFlags flags);

    VkResult ResetCommandPool(PFN_vkResetCommandPool  pfn,
                              VkDevice                device,
                              VkCommandPool           commandPool,
                              VkCommandPoolResetFlags flags);

    VkResult BeginCommandBuffer(PFN_vkBeginCommandBuffer        pfn,
                                VkCommandBuffer                 commandBuffer,
                                const VkCommandBufferBeginInfo* pBeginInfo);

    VkResult EndCommandBuffer(PFN_vkEndCommandBuffer pfn, VkCommandBuffer commandBuffer);

    VkResult CreateDevice(PFN_vkGetDeviceProcAddr      pa,
                          PFN_vkCreateDevice           pfn,
                          float                        timestampPeriod,
                          VkPhysicalDevice             physicalDevice,
                          const VkDeviceCreateInfo*    pCreateInfo,
                          const VkAllocationCallbacks* pAllocator,
                          VkDevice*                    pDevice);

    void DestroyDevice(PFN_vkDestroyDevice          pfn,
                       VkDevice                     device,
                       const VkAllocationCallbacks* pAllocator);

    VkResult AcquireNextImageKHR(PFN_vkAcquireNextImageKHR pfn,
                                 VkDevice                  device,
                                 VkSwapchainKHR            swapchain,
                                 uint64_t                  timeout,
                                 VkSemaphore               semaphore,
                                 VkFence                   fence,
                                 uint32_t*                 pImageIndex);

    VkResult QueueSubmit(PFN_vkQueueSubmit   pfn,
                         VkQueue             queue,
                         uint32_t            submitCount,
                         const VkSubmitInfo* pSubmits,
                         VkFence             fence);

    void GetDeviceQueue2(PFN_vkGetDeviceQueue2     pfn,
                         VkDevice                  device,
                         const VkDeviceQueueInfo2* pQueueInfo,
                         VkQueue*                  pQueue);

    void GetDeviceQueue(PFN_vkGetDeviceQueue pfn,
                        VkDevice             device,
                        uint32_t             queueFamilyIndex,
                        uint32_t             queueIndex,
                        VkQueue*             pQueue);

    void CmdInsertDebugUtilsLabel(PFN_vkCmdInsertDebugUtilsLabelEXT pfn,
                                  VkCommandBuffer                   commandBuffer,
                                  const VkDebugUtilsLabelEXT*       pLabelInfo);

private:
    Dive::GPUTime           m_gpu_time;
    PFN_vkGetDeviceProcAddr m_device_proc_addr;
};

}  // namespace DiveLayer