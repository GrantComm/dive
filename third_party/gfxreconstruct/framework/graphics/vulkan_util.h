/*
** Copyright (c) 2021-2023 LunarG, Inc.
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

#ifndef GFXRECON_GRAPHICS_VULKAN_UTIL_H
#define GFXRECON_GRAPHICS_VULKAN_UTIL_H

#include "generated/generated_vulkan_dispatch_table.h"
#include "util/defines.h"
#include "util/platform.h"

#include "vulkan/vulkan.h"

#if VK_USE_64_BIT_PTR_DEFINES == 1
#define VK_HANDLE_TO_UINT64(value) reinterpret_cast<uint64_t>(value)
#define UINT64_TO_VK_HANDLE(handle_type, value) reinterpret_cast<handle_type>(value)
#else
#define VK_HANDLE_TO_UINT64(value) (value)
#define UINT64_TO_VK_HANDLE(handle_type, value) static_cast<handle_type>(value)
#endif

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(graphics)

typedef uint64_t PresentId;

const std::vector<std::string> kLoaderLibNames = {
#if defined(WIN32)
    "vulkan-1.dll"
#elif defined(__APPLE__)
    "libvulkan.dylib", "libvulkan.1.dylib", "libMoltenVK.dylib"
#else
    "libvulkan.so.1", "libvulkan.so"
#endif
};

/// @brief Initialize the Vulkan loader by loading the Vulkan library.
/// @param loader_path Optional path to the Vulkan loader library. If not provided, the function will search for
/// `kLoaderLibNames` in the system library paths.
/// @return A handle to the loaded Vulkan library, or nullptr if the library could not be loaded.
util::platform::LibraryHandle InitializeLoader(const char* loader_path = nullptr);

void ReleaseLoader(util::platform::LibraryHandle loader_handle);

bool ImageHasUsage(VkImageUsageFlags usage_flags, VkImageUsageFlagBits bit);

/**
 * @brief   copy_dispatch_table_from_device can be used if a command-buffer was not allocated through the loader,
 *          in order to assign the dispatch table from an existing VkDevice.
 *
 * @param   device  a VkDevice handle
 * @param   handle  a VkCommandBuffer handle
 */
static inline void copy_dispatch_table_from_device(VkDevice device, VkCommandBuffer handle)
{
    // Because this command buffer was not allocated through the loader, it must be assigned a dispatch table.
    *reinterpret_cast<void**>(handle) = *reinterpret_cast<void**>(device);
}

[[maybe_unused]] static const char* kVulkanVrFrameDelimiterString = "vr-marker,frame_end,type,application";

GFXRECON_END_NAMESPACE(graphics)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_GRAPHICS_VULKAN_UTIL_H
