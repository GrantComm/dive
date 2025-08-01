/*
** Copyright (c) 2018-2023 Valve Corporation
** Copyright (c) 2018-2025 LunarG, Inc.
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

#include PROJECT_VERSION_HEADER_FILE

#include "layer/layer_vulkan_entry.h"

#include "encode/custom_vulkan_layer_func_table.h"
#include "encode/vulkan_capture_manager.h"
#include "encode/vulkan_handle_wrapper_util.h"
#include "generated/generated_vulkan_api_call_encoders.h"
#include "generated/generated_vulkan_layer_func_table.h"
#if ENABLE_OPENXR_SUPPORT
#include "generated/generated_openxr_layer_func_table.h"
#endif
#include "util/platform.h"

#include "vulkan/vk_layer.h"
#include "vulkan/vulkan_ohos.h"
#if ENABLE_OPENXR_SUPPORT
#include "openxr/openxr_loader_negotiation.h"
#endif

#include <array>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(vulkan_layer)

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL GetInstanceProcAddr(VkInstance instance, const char* pName)
{
    return LayerVulkanEntry::Get()->GetInstanceProcAddr(instance, pName);
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL GetDeviceProcAddr(VkDevice device, const char* pName)
{
    return LayerVulkanEntry::Get()->GetDeviceProcAddr(device, pName);
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL GetPhysicalDeviceProcAddr(VkInstance ourInstanceWrapper, const char* pName)
{
    return LayerVulkanEntry::Get()->GetPhysicalDeviceProcAddr(ourInstanceWrapper, pName);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceExtensionProperties(VkPhysicalDevice       physicalDevice,
                                                                  const char*            pLayerName,
                                                                  uint32_t*              pPropertyCount,
                                                                  VkExtensionProperties* pProperties)
{
    return LayerVulkanEntry::Get()->EnumerateDeviceExtensionProperties(
        physicalDevice, pLayerName, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceExtensionProperties(const char*            pLayerName,
                                                                    uint32_t*              pPropertyCount,
                                                                    VkExtensionProperties* pProperties)
{
    return LayerVulkanEntry::Get()->EnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceLayerProperties(uint32_t*          pPropertyCount,
                                                                VkLayerProperties* pProperties)
{
    return LayerVulkanEntry::Get()->EnumerateInstanceLayerProperties(pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceLayerProperties(VkPhysicalDevice   physicalDevice,
                                                              uint32_t*          pPropertyCount,
                                                              VkLayerProperties* pProperties)
{
    return LayerVulkanEntry::Get()->EnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL dispatch_CreateInstance(const VkInstanceCreateInfo*  pCreateInfo,
                                                       const VkAllocationCallbacks* pAllocator,
                                                       VkInstance*                  pInstance)
{
    return LayerVulkanEntry::Get()->dispatch_CreateInstance(pCreateInfo, pAllocator, pInstance);
}

VKAPI_ATTR VkResult VKAPI_CALL dispatch_CreateDevice(VkPhysicalDevice             physicalDevice,
                                                     const VkDeviceCreateInfo*    pCreateInfo,
                                                     const VkAllocationCallbacks* pAllocator,
                                                     VkDevice*                    pDevice)
{
    return LayerVulkanEntry::Get()->dispatch_CreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
}

encode::VulkanEntryBase* LayerVulkanEntry::InitSingleton()
{
    return VulkanEntryBase::InitSingleton<LayerVulkanEntry>(GetVulkanLayerFuncTable());
}

LayerVulkanEntry::LayerVulkanEntry(const encode::VulkanFunctionTable& vulkan_function_table) :
    VulkanEntryBase(vulkan_function_table)
{}

LayerVulkanEntry::~LayerVulkanEntry() {}

VkResult LayerVulkanEntry::dispatch_CreateInstance(const VkInstanceCreateInfo*  pCreateInfo,
                                                   const VkAllocationCallbacks* pAllocator,
                                                   VkInstance*                  pInstance)
{
    VkResult result = VK_ERROR_INITIALIZATION_FAILED;

    VkLayerInstanceCreateInfo* chain_info =
        const_cast<VkLayerInstanceCreateInfo*>(GetInstanceChainInfo(pCreateInfo, VK_LAYER_LINK_INFO));

    if (chain_info && chain_info->u.pLayerInfo)
    {
        PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr = chain_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;

        if (fpGetInstanceProcAddr)
        {
            PFN_vkCreateInstance fpCreateInstance =
                reinterpret_cast<PFN_vkCreateInstance>(fpGetInstanceProcAddr(VK_NULL_HANDLE, "vkCreateInstance"));

            if (fpCreateInstance)
            {
                // Advance the link info for the next element on the chain
                auto pLayerInfo          = chain_info->u.pLayerInfo;
                chain_info->u.pLayerInfo = chain_info->u.pLayerInfo->pNext;

                result = fpCreateInstance(pCreateInfo, pAllocator, pInstance);

                if ((result == VK_SUCCESS) && pInstance && (*pInstance != nullptr))
                {
                    AddInstanceHandle(*pInstance);
                    VkInstance unwrapped_instance = *pInstance;

                    encode::VulkanCaptureManager* manager = encode::VulkanCaptureManager::Get();
                    assert(manager != nullptr);
                    manager->InitVkInstance(pInstance, fpGetInstanceProcAddr);

                    // Register the next layer's GetPhysicalDeviceProcAddr func only after *pInstance
                    // has been updated to our wrapper in manager->InitVkInstance() above:
                    auto fpNextGetPhysicalDeviceProcAddr = reinterpret_cast<PFN_GetPhysicalDeviceProcAddr>(
                        fpGetInstanceProcAddr(unwrapped_instance, "vk_layerGetPhysicalDeviceProcAddr"));
                    SetInstanceNextGPDPA(*pInstance, fpNextGetPhysicalDeviceProcAddr);
                }
            }
        }
    }

    return result;
}

VkResult LayerVulkanEntry::dispatch_CreateDevice(VkPhysicalDevice             physicalDevice,
                                                 const VkDeviceCreateInfo*    pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator,
                                                 VkDevice*                    pDevice)
{
    VkResult                 result = VK_ERROR_INITIALIZATION_FAILED;
    VkLayerDeviceCreateInfo* chain_info =
        const_cast<VkLayerDeviceCreateInfo*>(GetDeviceChainInfo(pCreateInfo, VK_LAYER_LINK_INFO));

    if (chain_info && chain_info->u.pLayerInfo)
    {
        VkInstance layer_instance = GetInstanceHandle(physicalDevice);

        PFN_vkGetInstanceProcAddr fpGetInstanceProcAddr = chain_info->u.pLayerInfo->pfnNextGetInstanceProcAddr;
        PFN_vkGetDeviceProcAddr   fpGetDeviceProcAddr   = chain_info->u.pLayerInfo->pfnNextGetDeviceProcAddr;

        if (fpGetInstanceProcAddr && fpGetDeviceProcAddr && layer_instance)
        {
            PFN_vkCreateDevice fpCreateDevice =
                reinterpret_cast<PFN_vkCreateDevice>(fpGetInstanceProcAddr(layer_instance, "vkCreateDevice"));

            if (fpCreateDevice)
            {
                // Advance the link info for the next element on the chain
                chain_info->u.pLayerInfo = chain_info->u.pLayerInfo->pNext;

                result = fpCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);

                if ((result == VK_SUCCESS) && pDevice && (*pDevice != nullptr))
                {
                    encode::VulkanCaptureManager* manager = encode::VulkanCaptureManager::Get();
                    assert(manager != nullptr);
                    manager->InitVkDevice(pDevice, fpGetDeviceProcAddr);
                }
            }
        }
    }

    return result;
}

PFN_vkVoidFunction LayerVulkanEntry::GetInstanceProcAddr(VkInstance instance, const char* pName)
{
    PFN_vkVoidFunction result = nullptr;

    // This is required by the loader and is called directly with an "instance" actually
    // set to the internal "loader_instance".  Detect that case and return
    if (!strcmp(pName, "vkCreateInstance"))
    {
        return reinterpret_cast<PFN_vkVoidFunction>(encode::vkCreateInstance);
    }

    bool has_implementation = false;

    // Check for implementation in the next level
    if (instance != VK_NULL_HANDLE)
    {
        auto table = encode::vulkan_wrappers::GetInstanceTable(instance);
        if ((table != nullptr) && (table->GetInstanceProcAddr != nullptr))
        {
            has_implementation = (table->GetInstanceProcAddr(instance, pName) != nullptr);
        }
    }

    // Check for implementation in the layer itself
    if (!has_implementation)
    {
        for (const auto& ext_props : kVulkanDeviceExtensionProps)
        {
            if (std::find(ext_props.instance_funcs.begin(), ext_props.instance_funcs.end(), pName) !=
                ext_props.instance_funcs.end())
            {
                has_implementation = true;
                break;
            }
        }
    }

    // Only intercept the requested function if there is an implementation available, or if
    // the instance handle is null and we can't determine if it is available from the next level.
    if (has_implementation || (instance == VK_NULL_HANDLE))
    {
        const auto entry = vulkan_function_table_.find(pName);

        if (entry != vulkan_function_table_.end())
        {
            result = entry->second;
        }
    }

    // Lastly check custom GFXR exposed functions
    if (result == nullptr)
    {
        const auto entry = custom_func_table.find(pName);

        if (entry != custom_func_table.end())
        {
            result = entry->second;
        }
    }

    return result;
}

PFN_vkVoidFunction LayerVulkanEntry::GetDeviceProcAddr(VkDevice device, const char* pName)
{
    PFN_vkVoidFunction result = nullptr;

    if (device != VK_NULL_HANDLE)
    {
        bool has_implementation = false;

        // Check for implementation in the next level
        auto table = encode::vulkan_wrappers::GetDeviceTable(device);
        if ((table != nullptr) && (table->GetDeviceProcAddr != nullptr))
        {
            has_implementation = (table->GetDeviceProcAddr(device, pName) != nullptr);
        }

        // Check for implementation in the layer itself
        if (!has_implementation)
        {
            for (const auto& ext_props : kVulkanDeviceExtensionProps)
            {
                if (std::find(ext_props.device_funcs.begin(), ext_props.device_funcs.end(), pName) !=
                    ext_props.device_funcs.end())
                {
                    has_implementation = true;
                    break;
                }
            }
        }

        // Only intercept the requested function if there is an implementation available
        if (has_implementation)
        {
            const auto entry = vulkan_function_table_.find(pName);
            if (entry != vulkan_function_table_.end())
            {
                result = entry->second;
            }
        }
    }

    return result;
}

/**
 * We don't actually need to do anything for this function,
 * but we do need to unwrap the instance before the downstream layer
 * sees it.
 */
PFN_vkVoidFunction LayerVulkanEntry::GetPhysicalDeviceProcAddr(VkInstance ourInstanceWrapper, const char* pName)
{
    PFN_vkVoidFunction result = nullptr;

    if (ourInstanceWrapper != VK_NULL_HANDLE)
    {
        PFN_GetPhysicalDeviceProcAddr vulkan_next_gpdpa = GetNextGPDPA(ourInstanceWrapper);
        if (vulkan_next_gpdpa != nullptr)
        {
            result = vulkan_next_gpdpa(ourInstanceWrapper, pName);
        }
    }

    return result;
}

VkResult LayerVulkanEntry::EnumerateDeviceExtensionProperties(VkPhysicalDevice       physicalDevice,
                                                              const char*            pLayerName,
                                                              uint32_t*              pPropertyCount,
                                                              VkExtensionProperties* pProperties)
{
    VkResult result = VK_SUCCESS;

    if ((pLayerName != nullptr) && (util::platform::StringCompare(pLayerName, kLayerProps.layerName) == 0))
    {
        if (pPropertyCount != nullptr)
        {
            uint32_t extension_count = static_cast<uint32_t>(kVulkanDeviceExtensionProps.size());

            if (pProperties == nullptr)
            {
                *pPropertyCount = extension_count;
            }
            else
            {
                if ((*pPropertyCount) < extension_count)
                {
                    result          = VK_INCOMPLETE;
                    extension_count = *pPropertyCount;
                }
                else if ((*pPropertyCount) > extension_count)
                {
                    *pPropertyCount = extension_count;
                }

                for (uint32_t i = 0; i < extension_count; ++i)
                {
                    pProperties[i] = kVulkanDeviceExtensionProps[i].props;
                }
            }
        }
    }
    else
    {
        // If this function was not called with the layer's name, we expect to dispatch down the chain to obtain the ICD
        // provided extensions.
        // In order to screen out unsupported extensions, we always query the chain
        // twice, and remove those that are present from the count.
        auto     instance_table            = encode::vulkan_wrappers::GetInstanceTable(physicalDevice);
        uint32_t downstream_property_count = 0;

        result = instance_table->EnumerateDeviceExtensionProperties(
            physicalDevice, pLayerName, &downstream_property_count, nullptr);
        if (result != VK_SUCCESS)
        {
            return result;
        }

        std::vector<VkExtensionProperties> device_extension_properties(downstream_property_count);
        result = instance_table->EnumerateDeviceExtensionProperties(
            physicalDevice, pLayerName, &downstream_property_count, device_extension_properties.data());
        if (result != VK_SUCCESS)
        {
            return result;
        }

        RemoveExtensions(device_extension_properties,
                         kVulkanUnsupportedDeviceExtensions.data(),
                         std::end(kVulkanUnsupportedDeviceExtensions) - std::begin(kVulkanUnsupportedDeviceExtensions));

        // Append the extensions we provide in the list to the caller if they aren't already provided downstream.
        if (pLayerName == nullptr)
        {
            for (auto& provided_prop : kVulkanDeviceExtensionProps)
            {
                bool append_provided_prop =
                    std::find_if(device_extension_properties.begin(),
                                 device_extension_properties.end(),
                                 [&provided_prop](const VkExtensionProperties& downstream_prop) {
                                     return util::platform::StringCompare(provided_prop.props.extensionName,
                                                                          downstream_prop.extensionName,
                                                                          VK_MAX_EXTENSION_NAME_SIZE) == 0;
                                 }) == device_extension_properties.end();
                if (append_provided_prop)
                {
                    device_extension_properties.push_back(provided_prop.props);
                }
            }
        }

        // Output the reduced count or the reduced extension list:
        if (pProperties == nullptr)
        {
            *pPropertyCount = static_cast<uint32_t>(device_extension_properties.size());
        }
        else
        {
            if (*pPropertyCount < static_cast<uint32_t>(device_extension_properties.size()))
            {
                result = VK_INCOMPLETE;
            }
            *pPropertyCount = std::min(*pPropertyCount, static_cast<uint32_t>(device_extension_properties.size()));
            std::copy(device_extension_properties.begin(),
                      device_extension_properties.begin() + *pPropertyCount,
                      pProperties);
        }
    }

    return result;
}

VkResult LayerVulkanEntry::EnumerateInstanceExtensionProperties(const char*            pLayerName,
                                                                uint32_t*              pPropertyCount,
                                                                VkExtensionProperties* pProperties)
{
    VkResult result = VK_SUCCESS;

    if (pLayerName && (util::platform::StringCompare(pLayerName, kLayerProps.layerName) == 0))
    {
        if (pPropertyCount != nullptr)
        {
            *pPropertyCount = 0;
        }
    }
    else
    {
        result = VK_ERROR_LAYER_NOT_PRESENT;
    }

    return result;
}

VkResult LayerVulkanEntry::EnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
    VkResult result = VK_SUCCESS;

    if (pProperties == nullptr)
    {
        if (pPropertyCount != nullptr)
        {
            *pPropertyCount = 1;
        }
    }
    else
    {
        if ((pPropertyCount != nullptr) && (*pPropertyCount >= 1))
        {
            util::platform::MemoryCopy(pProperties, sizeof(*pProperties), &kLayerProps, sizeof(kLayerProps));
            *pPropertyCount = 1;
        }
        else
        {
            result = VK_INCOMPLETE;
        }
    }

    return result;
}

VkResult LayerVulkanEntry::EnumerateDeviceLayerProperties(VkPhysicalDevice   physicalDevice,
                                                          uint32_t*          pPropertyCount,
                                                          VkLayerProperties* pProperties)
{
    GFXRECON_UNREFERENCED_PARAMETER(physicalDevice);
    return EnumerateInstanceLayerProperties(pPropertyCount, pProperties);
}

GFXRECON_END_NAMESPACE(vulkan_layer)

#if ENABLE_OPENXR_SUPPORT
GFXRECON_BEGIN_NAMESPACE(openxr_layer)

const XrApiLayerProperties kLayerProps = {
    XR_TYPE_API_LAYER_PROPERTIES,
    nullptr,
    GFXRECON_PROJECT_OPENXR_LAYER_NAME,
    XR_CURRENT_API_VERSION,
    VK_MAKE_VERSION(GFXRECON_PROJECT_VERSION_MAJOR, GFXRECON_PROJECT_VERSION_MINOR, GFXRECON_PROJECT_VERSION_PATCH),
    GFXRECON_PROJECT_DESCRIPTION
    " Version " GFXRECON_VERSION_STR(GFXRECON_PROJECT_VERSION_MAJOR) "." GFXRECON_VERSION_STR(
        GFXRECON_PROJECT_VERSION_MINOR) "." GFXRECON_VERSION_STR(GFXRECON_PROJECT_VERSION_PATCH)
        GFXRECON_PROJECT_VERSION_DESIGNATION
};

struct OpenXrInstanceInfo
{
    void*                     loader_instance;
    PFN_xrGetInstanceProcAddr next_gipa;
    std::vector<std::string>  enabled_extensions;
};
static std::unordered_map<XrInstance, OpenXrInstanceInfo> xr_instance_infos;

XRAPI_ATTR XrResult XRAPI_CALL dispatch_CreateApiLayerInstance(const XrInstanceCreateInfo* info,
                                                               const XrApiLayerCreateInfo* apiLayerInfo,
                                                               XrInstance*                 instance)
{
    if (info == nullptr || apiLayerInfo == nullptr || apiLayerInfo->nextInfo == nullptr || instance == nullptr)
    {
        return XR_ERROR_VALIDATION_FAILURE;
    }
    XrApiLayerNextInfo* next_info = apiLayerInfo->nextInfo;
    if (strcmp(next_info->layerName, GFXRECON_PROJECT_OPENXR_LAYER_NAME))
    {
        return XR_ERROR_NAME_INVALID;
    }
    XrApiLayerCreateInfo next_layer_create_info;
    assert(apiLayerInfo->structSize == sizeof(XrApiLayerCreateInfo));
    memcpy(&next_layer_create_info, apiLayerInfo, sizeof(XrApiLayerCreateInfo));
    next_layer_create_info.nextInfo = next_info->next;
    XrResult result                 = next_info->nextCreateApiLayerInstance(info, &next_layer_create_info, instance);
    if (result == XR_SUCCESS)
    {
        OpenXrInstanceInfo cur_instance_info;
        cur_instance_info.loader_instance = apiLayerInfo->loaderInstance;
        cur_instance_info.next_gipa       = next_info->nextGetInstanceProcAddr;
        for (uint32_t iii = 0; iii < info->enabledExtensionCount; ++iii)
        {
            cur_instance_info.enabled_extensions.push_back(info->enabledExtensionNames[iii]);
        }
        xr_instance_infos[*instance] = std::move(cur_instance_info);
    }
    return result;
}

XRAPI_ATTR XrResult XRAPI_CALL EnumerateInstanceExtensionProperties(const char*            layerName,
                                                                    uint32_t               propertyCapacityInput,
                                                                    uint32_t*              propertyCountOutput,
                                                                    XrExtensionProperties* properties)
{
    if (strcmp(layerName, GFXRECON_PROJECT_OPENXR_LAYER_NAME))
    {
        return XR_ERROR_VALIDATION_FAILURE;
    }
    *propertyCountOutput = 0;
    return XR_SUCCESS;
}

XRAPI_ATTR XrResult XRAPI_CALL EnumerateApiLayerProperties(uint32_t              propertyCapacityInput,
                                                           uint32_t*             propertyCountOutput,
                                                           XrApiLayerProperties* properties)
{
    XrResult result = XR_ERROR_FUNCTION_UNSUPPORTED;

    if (properties == nullptr)
    {
        if (propertyCountOutput != nullptr)
        {
            *propertyCountOutput = 1;
        }
    }
    else
    {
        if (propertyCapacityInput >= 1)
        {
            util::platform::MemoryCopy(properties, sizeof(*properties), &kLayerProps, sizeof(kLayerProps));
            *propertyCountOutput = 1;
        }
    }

    return result;
}

XRAPI_ATTR XrResult XRAPI_CALL GetInstanceProcAddr(XrInstance instance, const char* name, PFN_xrVoidFunction* function)
{
    XrResult result = XR_ERROR_FUNCTION_UNSUPPORTED;

    // These first functions are valid whether or not the instance is
    if (!strcmp(name, "xrGetInstanceProcAddr"))
    {
        *function = reinterpret_cast<PFN_xrVoidFunction>(GetInstanceProcAddr);
        result    = XR_SUCCESS;
    }
    else if (!strcmp(name, "xrInitializeLoaderKHR"))
    {
        *function = reinterpret_cast<PFN_xrVoidFunction>(encode::xrInitializeLoaderKHR);
        result    = XR_SUCCESS;
    }
    else if (!strcmp(name, "xrEnumerateInstanceExtensionProperties"))
    {
        *function = reinterpret_cast<PFN_xrVoidFunction>(EnumerateInstanceExtensionProperties);
        result    = XR_SUCCESS;
    }
    else if (!strcmp(name, "xrEnumerateApiLayerProperties"))
    {
        *function = reinterpret_cast<PFN_xrVoidFunction>(EnumerateApiLayerProperties);
        result    = XR_SUCCESS;
    }
    else if (!strcmp(name, "xrCreateApiLayerInstance"))
    {
        *function = reinterpret_cast<PFN_vkVoidFunction>(encode::xrCreateApiLayerInstance);
        result    = XR_SUCCESS;
    }
    else
    {
        // Everything past this point requires an instance, so if it's not valid by now,
        // return an error
        *function = nullptr;
        result    = XR_ERROR_HANDLE_INVALID;

        if (instance != XR_NULL_HANDLE)
        {
            auto table = encode::openxr_wrappers::GetInstanceTable(instance);
            // table will be null for invalid or null handles
            if (table != nullptr)
            {
                result = table->GetInstanceProcAddr(instance, name, function);
                // Only capture functions that are supported in the implementation, otherwise just pass on the
                // information
                if ((result == XR_SUCCESS) && (function != nullptr))
                {
                    const auto entry = openxr_layer_func_table.find(name);
                    if (entry != openxr_layer_func_table.cend())
                    {
                        *function = entry->second;
                        result    = XR_SUCCESS;
                    }
                }
            }
        }
    }
    return result;
}
GFXRECON_END_NAMESPACE(openxr_layer)
#endif // ENABLE_OPENXR_SUPPORT

GFXRECON_END_NAMESPACE(gfxrecon)

#if defined(__GNUC__) && __GNUC__ >= 4
#define GFXR_EXPORT __attribute__((visibility("default")))
#else
#define GFXR_EXPORT
#endif

// To be safe, we extern "C" these items to remove name mangling for all the items we want to export for Android and old
// loaders to find.
extern "C"
{

    GFXR_EXPORT VKAPI_ATTR VkResult VKAPI_CALL
    vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface* pVersionStruct)
    {
        assert(pVersionStruct != NULL);
        assert(pVersionStruct->sType == LAYER_NEGOTIATE_INTERFACE_STRUCT);

        // Fill in the function pointers if our version is at least capable of having the structure contain them.
        if (pVersionStruct->loaderLayerInterfaceVersion >= 2)
        {
            pVersionStruct->pfnGetInstanceProcAddr       = gfxrecon::vulkan_layer::GetInstanceProcAddr;
            pVersionStruct->pfnGetDeviceProcAddr         = gfxrecon::vulkan_layer::GetDeviceProcAddr;
            pVersionStruct->pfnGetPhysicalDeviceProcAddr = gfxrecon::vulkan_layer::GetPhysicalDeviceProcAddr;
        }

        if (pVersionStruct->loaderLayerInterfaceVersion > CURRENT_LOADER_LAYER_INTERFACE_VERSION)
        {
            pVersionStruct->loaderLayerInterfaceVersion = CURRENT_LOADER_LAYER_INTERFACE_VERSION;
        }

        return VK_SUCCESS;
    }

    // The following two functions are not directly invoked by the desktop loader, which instead uses the function
    // pointers returned by the negotiate function.
    GFXR_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* pName)
    {
        return gfxrecon::vulkan_layer::GetInstanceProcAddr(instance, pName);
    }

    GFXR_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice device, const char* pName)
    {
        return gfxrecon::vulkan_layer::GetDeviceProcAddr(device, pName);
    }

    // The following four functions are not invoked by the desktop loader, which retrieves the layer specific properties
    // and extensions from both the layer's JSON file and during the negotiation process.
    GFXR_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
                                                                                    const char*      pLayerName,
                                                                                    uint32_t*        pPropertyCount,
                                                                                    VkExtensionProperties* pProperties)
    {
        assert(physicalDevice == VK_NULL_HANDLE);
        return gfxrecon::vulkan_layer::EnumerateDeviceExtensionProperties(
            physicalDevice, pLayerName, pPropertyCount, pProperties);
    }

    GFXR_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceExtensionProperties(
        const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
    {
        return gfxrecon::vulkan_layer::EnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
    }

    GFXR_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceLayerProperties(uint32_t*          pPropertyCount,
                                                                                  VkLayerProperties* pProperties)
    {
        return gfxrecon::vulkan_layer::EnumerateInstanceLayerProperties(pPropertyCount, pProperties);
    }

    GFXR_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceLayerProperties(VkPhysicalDevice   physicalDevice,
                                                                                uint32_t*          pPropertyCount,
                                                                                VkLayerProperties* pProperties)
    {
        assert(physicalDevice == VK_NULL_HANDLE);
        return gfxrecon::vulkan_layer::EnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties);
    }

#if ENABLE_OPENXR_SUPPORT
    GFXR_EXPORT XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderApiLayerInterface(
        const XrNegotiateLoaderInfo* loaderInfo, const char* layerName, XrNegotiateApiLayerRequest* apiLayerRequest)
    {
        // Wrong layer name or something wrong with incoming structs
        if (layerName == nullptr || (strcmp(layerName, GFXRECON_PROJECT_OPENXR_LAYER_NAME) != 0) ||
            loaderInfo == nullptr || apiLayerRequest == nullptr ||
            loaderInfo->structType != XR_LOADER_INTERFACE_STRUCT_LOADER_INFO ||
            apiLayerRequest->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST)
        {
            GFXRECON_LOG_ERROR("xrNegotiateLoaderApiLayerInterface: Failed checking incoming structs");
            return XR_ERROR_VALIDATION_FAILURE;
        }

        const uint32_t layer_cur_interface_version = 1;
        const uint8_t  loader_min_major_version    = XR_VERSION_MAJOR(loaderInfo->minApiVersion);
        const uint8_t  loader_min_minor_version    = XR_VERSION_MINOR(loaderInfo->minApiVersion);
        const uint8_t  loader_max_major_version    = XR_VERSION_MAJOR(loaderInfo->maxApiVersion);
        const uint8_t  loader_max_minor_version    = XR_VERSION_MINOR(loaderInfo->maxApiVersion);
        const uint8_t  layer_cur_major_version     = XR_VERSION_MAJOR(XR_CURRENT_API_VERSION);
        const uint8_t  layer_cur_minor_version     = XR_VERSION_MAJOR(XR_CURRENT_API_VERSION);

        // Layer can't accept interface (we only support interface version 1 right now) or API version
        if ((layer_cur_interface_version < loaderInfo->minInterfaceVersion ||
             layer_cur_interface_version > loaderInfo->maxInterfaceVersion) ||
            (layer_cur_major_version < loader_min_major_version ||
             layer_cur_major_version > loader_max_major_version) ||
            (layer_cur_minor_version < loader_min_minor_version || layer_cur_major_version > loader_max_minor_version))
        {
            GFXRECON_LOG_ERROR(
                "xrNegotiateLoaderApiLayerInterface: Failed negotiating version (loader [%u.%u -> %u.%u], layer %u.%u)",
                loader_min_major_version,
                loader_min_minor_version,
                loader_max_major_version,
                loader_max_minor_version,
                layer_cur_major_version,
                layer_cur_minor_version);
            return XR_ERROR_API_VERSION_UNSUPPORTED;
        }

        apiLayerRequest->layerInterfaceVersion  = layer_cur_interface_version;
        apiLayerRequest->layerApiVersion        = XR_CURRENT_API_VERSION;
        apiLayerRequest->getInstanceProcAddr    = gfxrecon::openxr_layer::GetInstanceProcAddr;
        apiLayerRequest->createApiLayerInstance = gfxrecon::encode::xrCreateApiLayerInstance;
        return XR_SUCCESS;
    }
#else
    // TODO: This stub likely makes different trace_layer.def files unneeded, should simplify the CMake

    // This is a stub to satisfy Windows exports (in the .def file) when ENABLE_OPENXR_SUPPORT is false
    GFXR_EXPORT VKAPI_ATTR uint32_t VKAPI_CALL xrNegotiateLoaderApiLayerInterface(const void* loaderInfo,
                                                                                  const char* layerName,
                                                                                  void*       apiLayerRequest)
    {
        return -23; // XR_ERROR_LAYER_INVALID
    }

#endif
} // extern "C"
