/*
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

#include "test_app_base.h"
#include <iostream>

#if defined(_WIN32)
#include <fcntl.h>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif // _WIN32

#if defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>
#endif

#include <mutex>
#include <algorithm>
#include <fstream>
#include <Vulkan-Utility-Libraries/vk_enum_string_helper.h>
#include <filesystem>

#ifdef __ANDROID__
#include <vulkan/vulkan_android.h>
#include <android/looper.h>
#endif

#include <application/application.h>
#include <graphics/vulkan_util.h>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(test)
GFXRECON_BEGIN_NAMESPACE(detail)

GenericFeaturesPNextNode::GenericFeaturesPNextNode()
{
    memset(fields, UINT8_MAX, sizeof(VkBool32) * field_capacity);
}

bool GenericFeaturesPNextNode::match(GenericFeaturesPNextNode const& requested,
                                     GenericFeaturesPNextNode const& supported) noexcept
{
    assert(requested.sType == supported.sType && "Non-matching sTypes in features nodes!");
    for (uint32_t i = 0; i < field_capacity; i++)
    {
        if (requested.fields[i] && !supported.fields[i])
            return false;
    }
    return true;
}

void GenericFeaturesPNextNode::combine(GenericFeaturesPNextNode const& right) noexcept
{
    assert(sType == right.sType && "Non-matching sTypes in features nodes!");
    for (uint32_t i = 0; i < GenericFeaturesPNextNode::field_capacity; i++)
    {
        fields[i] = fields[i] || right.fields[i];
    }
}

bool GenericFeatureChain::match_all(GenericFeatureChain const& extension_requested) const noexcept
{
    // Should only be false if extension_supported was unable to be filled out, due to the
    // physical device not supporting vkGetPhysicalDeviceFeatures2 in any capacity.
    if (extension_requested.nodes.size() != nodes.size())
    {
        return false;
    }

    for (size_t i = 0; i < nodes.size() && i < nodes.size(); ++i)
    {
        if (!GenericFeaturesPNextNode::match(extension_requested.nodes[i], nodes[i]))
            return false;
    }
    return true;
}

bool GenericFeatureChain::find_and_match(GenericFeatureChain const& extensions_requested) const noexcept
{
    for (const auto& requested_extension_node : extensions_requested.nodes)
    {
        bool found = false;
        for (const auto& supported_node : nodes)
        {
            if (supported_node.sType == requested_extension_node.sType)
            {
                found = true;
                if (!GenericFeaturesPNextNode::match(requested_extension_node, supported_node))
                    return false;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void GenericFeatureChain::chain_up(VkPhysicalDeviceFeatures2& feats2) noexcept
{
    detail::GenericFeaturesPNextNode* prev = nullptr;
    for (auto& extension : nodes)
    {
        if (prev != nullptr)
        {
            prev->pNext = &extension;
        }
        prev = &extension;
    }
    feats2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    feats2.pNext = !nodes.empty() ? &nodes.at(0) : nullptr;
}

void GenericFeatureChain::combine(GenericFeatureChain const& right) noexcept
{
    for (const auto& right_node : right.nodes)
    {
        bool already_contained = false;
        for (auto& left_node : nodes)
        {
            if (left_node.sType == right_node.sType)
            {
                left_node.combine(right_node);
                already_contained = true;
            }
        }
        if (!already_contained)
        {
            nodes.push_back(right_node);
        }
    }
}

struct VulkanInstTable
{
    VulkanInstTable() { GFXRECON_ASSERT(init_vulkan_funcs()); }

    template <typename T>
    void get_inst_proc_addr(T& out_ptr, const char* func_name)
    {
        GFXRECON_ASSERT(ptr_vkGetInstanceProcAddr != nullptr);
        out_ptr = reinterpret_cast<T>(ptr_vkGetInstanceProcAddr(instance, func_name));
    }

    template <typename T>
    void get_device_proc_addr(VkDevice device, T& out_ptr, const char* func_name)
    {
        GFXRECON_ASSERT(fp_vkGetDeviceProcAddr != nullptr);
        out_ptr = reinterpret_cast<T>(fp_vkGetDeviceProcAddr(device, func_name));
    }

    void load_instance_table(VkInstance inst)
    {
        GFXRECON_ASSERT(inst != VK_NULL_HANDLE);
        GFXRECON_ASSERT(ptr_vkGetInstanceProcAddr != nullptr);
        instance = inst;
        graphics::LoadVulkanInstanceTable(ptr_vkGetInstanceProcAddr, inst, &inst_table);

        get_inst_proc_addr(fp_vkCreateDevice, "vkCreateDevice");
        get_inst_proc_addr(fp_vkGetDeviceProcAddr, "vkGetDeviceProcAddr");
    }

    bool load_vulkan_library()
    {
        // Can immediately return if it has already been loaded
        if (loader_handle_ != nullptr)
        {
            return true;
        }

        loader_handle_ = graphics::InitializeLoader(getenv("VULKAN_LIBRARY_PATH"));
        if (loader_handle_ == nullptr)
        {
            return false;
        }

        ptr_vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(
            util::platform::GetProcAddress(loader_handle_, "vkGetInstanceProcAddr"));
        return ptr_vkGetInstanceProcAddr != nullptr;
    }

    bool init_vulkan_funcs(PFN_vkGetInstanceProcAddr fp_vkGetInstanceProcAddr = nullptr)
    {
        if (fp_vkGetInstanceProcAddr != nullptr)
        {
            ptr_vkGetInstanceProcAddr = fp_vkGetInstanceProcAddr;
        }
        else
        {
            bool ret = load_vulkan_library();
            if (!ret)
                return false;
        }

        fp_vkEnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(
            ptr_vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties"));
        fp_vkEnumerateInstanceLayerProperties = reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(
            ptr_vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceLayerProperties"));
        fp_vkEnumerateInstanceVersion = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(
            ptr_vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceVersion"));
        fp_vkCreateInstance =
            reinterpret_cast<PFN_vkCreateInstance>(ptr_vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkCreateInstance"));
        return true;
    }

    util::platform::LibraryHandle loader_handle_ = nullptr;

    PFN_vkGetInstanceProcAddr ptr_vkGetInstanceProcAddr = nullptr;

    PFN_vkEnumerateInstanceExtensionProperties fp_vkEnumerateInstanceExtensionProperties = nullptr;
    PFN_vkEnumerateInstanceLayerProperties     fp_vkEnumerateInstanceLayerProperties     = nullptr;
    PFN_vkEnumerateInstanceVersion             fp_vkEnumerateInstanceVersion             = nullptr;
    PFN_vkCreateInstance                       fp_vkCreateInstance                       = nullptr;

    VkInstance instance = VK_NULL_HANDLE;

    PFN_vkCreateDevice      fp_vkCreateDevice      = nullptr;
    PFN_vkGetDeviceProcAddr fp_vkGetDeviceProcAddr = nullptr;

    graphics::VulkanInstanceTable inst_table;
};

static VulkanInstTable& get_instance_table()
{
    static VulkanInstTable inst_table;
    return inst_table;
}

// Helper for robustly executing the two-call pattern
template <typename T, typename F, typename... Ts>
auto get_vector(std::vector<T>& out, F&& f, Ts&&... ts) -> VkResult
{
    uint32_t count = 0;
    VkResult err;
    do
    {
        err = f(ts..., &count, nullptr);
        if (err != VK_SUCCESS)
        {
            return err;
        };
        out.resize(count);
        err = f(ts..., &count, out.data());
        out.resize(count);
    } while (err == VK_INCOMPLETE);
    return err;
}

template <typename T, typename F, typename... Ts>
auto get_vector_noerror(F&& f, Ts&&... ts) -> std::vector<T>
{
    uint32_t       count = 0;
    std::vector<T> results;
    f(ts..., &count, nullptr);
    results.resize(count);
    f(ts..., &count, results.data());
    results.resize(count);
    return results;
}

GFXRECON_END_NAMESPACE(detail)

const char* to_string_message_severity(VkDebugUtilsMessageSeverityFlagBitsEXT s)
{
    switch (s)
    {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            return "VERBOSE";
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            return "ERROR";
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            return "WARNING";
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            return "INFO";
        default:
            return "UNKNOWN";
    }
}
const char* to_string_message_type(VkDebugUtilsMessageTypeFlagsEXT s)
{
    if (s == 7)
        return "General | Validation | Performance";
    if (s == 6)
        return "Validation | Performance";
    if (s == 5)
        return "General | Performance";
    if (s == 4 /*VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT*/)
        return "Performance";
    if (s == 3)
        return "General | Validation";
    if (s == 2 /*VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT*/)
        return "Validation";
    if (s == 1 /*VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT*/)
        return "General";
    return "Unknown";
}

VkResult create_debug_utils_messenger(VkInstance                           instance,
                                      PFN_vkDebugUtilsMessengerCallbackEXT debug_callback,
                                      VkDebugUtilsMessageSeverityFlagsEXT  severity,
                                      VkDebugUtilsMessageTypeFlagsEXT      type,
                                      void*                                user_data_pointer,
                                      VkDebugUtilsMessengerEXT*            pDebugMessenger,
                                      VkAllocationCallbacks*               allocation_callbacks)
{

    if (debug_callback == nullptr)
        debug_callback = default_debug_callback;
    VkDebugUtilsMessengerCreateInfoEXT messengerCreateInfo = {};
    messengerCreateInfo.sType                              = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    messengerCreateInfo.pNext                              = nullptr;
    messengerCreateInfo.messageSeverity                    = severity;
    messengerCreateInfo.messageType                        = type;
    messengerCreateInfo.pfnUserCallback                    = debug_callback;
    messengerCreateInfo.pUserData                          = user_data_pointer;

    if (detail::get_instance_table().inst_table.CreateDebugUtilsMessengerEXT != nullptr)
    {
        return detail::get_instance_table().inst_table.CreateDebugUtilsMessengerEXT(
            instance, &messengerCreateInfo, allocation_callbacks, pDebugMessenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void destroy_debug_utils_messenger(VkInstance               instance,
                                   VkDebugUtilsMessengerEXT debugMessenger,
                                   VkAllocationCallbacks*   allocation_callbacks)
{

    if (detail::get_instance_table().inst_table.DestroyDebugUtilsMessengerEXT != nullptr)
    {
        detail::get_instance_table().inst_table.DestroyDebugUtilsMessengerEXT(
            instance, debugMessenger, allocation_callbacks);
    }
}

GFXRECON_BEGIN_NAMESPACE(detail)

bool check_layer_supported(std::vector<VkLayerProperties> const& available_layers, const char* layer_name)
{
    if (!layer_name)
        return false;
    for (const auto& layer_properties : available_layers)
    {
        if (strcmp(layer_name, layer_properties.layerName) == 0)
        {
            return true;
        }
    }
    return false;
}

bool check_layers_supported(std::vector<VkLayerProperties> const& available_layers,
                            std::vector<const char*> const&       layer_names)
{
    bool all_found = true;
    for (const auto& layer_name : layer_names)
    {
        bool found = check_layer_supported(available_layers, layer_name);
        if (!found)
            all_found = false;
    }
    return all_found;
}

bool check_extension_supported(std::vector<VkExtensionProperties> const& available_extensions,
                               const char*                               extension_name)
{
    if (!extension_name)
        return false;
    for (const auto& extension_properties : available_extensions)
    {
        if (strcmp(extension_name, extension_properties.extensionName) == 0)
        {
            return true;
        }
    }
    return false;
}

bool check_extensions_supported(std::vector<VkExtensionProperties> const& available_extensions,
                                std::vector<const char*> const&           extension_names)
{
    bool all_found = true;
    for (const auto& extension_name : extension_names)
    {
        bool found = check_extension_supported(available_extensions, extension_name);
        if (!found)
            all_found = false;
    }
    return all_found;
}

template <typename T>
void setup_pNext_chain(T& structure, std::vector<VkBaseOutStructure*> const& structs)
{
    structure.pNext = nullptr;
    if (structs.size() <= 0)
        return;
    for (size_t i = 0; i < structs.size() - 1; i++)
    {
        structs.at(i)->pNext = structs.at(i + 1);
    }
    structure.pNext = structs.at(0);
}
const char* validation_layer_name = "VK_LAYER_KHRONOS_validation";

GFXRECON_END_NAMESPACE(detail)

#define CASE_TO_STRING(CATEGORY, TYPE) \
    case CATEGORY::TYPE:               \
        return #TYPE;

const char* to_string(InstanceError err)
{
    switch (err)
    {
        CASE_TO_STRING(InstanceError, vulkan_unavailable)
        CASE_TO_STRING(InstanceError, vulkan_version_unavailable)
        CASE_TO_STRING(InstanceError, vulkan_version_1_1_unavailable)
        CASE_TO_STRING(InstanceError, vulkan_version_1_2_unavailable)
        CASE_TO_STRING(InstanceError, failed_create_debug_messenger)
        CASE_TO_STRING(InstanceError, failed_create_instance)
        CASE_TO_STRING(InstanceError, requested_layers_not_present)
        CASE_TO_STRING(InstanceError, requested_extensions_not_present)
        CASE_TO_STRING(InstanceError, windowing_extensions_not_present)
        default:
            return "";
    }
}
const char* to_string(PhysicalDeviceError err)
{
    switch (err)
    {
        CASE_TO_STRING(PhysicalDeviceError, no_surface_provided)
        CASE_TO_STRING(PhysicalDeviceError, failed_enumerate_physical_devices)
        CASE_TO_STRING(PhysicalDeviceError, no_physical_devices_found)
        CASE_TO_STRING(PhysicalDeviceError, no_suitable_device)
        default:
            return "";
    }
}
const char* to_string(QueueError err)
{
    switch (err)
    {
        CASE_TO_STRING(QueueError, present_unavailable)
        CASE_TO_STRING(QueueError, graphics_unavailable)
        CASE_TO_STRING(QueueError, compute_unavailable)
        CASE_TO_STRING(QueueError, transfer_unavailable)
        CASE_TO_STRING(QueueError, queue_index_out_of_range)
        CASE_TO_STRING(QueueError, invalid_queue_family_index)
        default:
            return "";
    }
}
const char* to_string(DeviceError err)
{
    switch (err)
    {
        CASE_TO_STRING(DeviceError, failed_create_device)
        default:
            return "";
    }
}
const char* to_string(SwapchainError err)
{
    switch (err)
    {
        CASE_TO_STRING(SwapchainError, surface_handle_not_provided)
        CASE_TO_STRING(SwapchainError, failed_query_surface_support_details)
        CASE_TO_STRING(SwapchainError, failed_create_swapchain)
        CASE_TO_STRING(SwapchainError, failed_get_swapchain_images)
        CASE_TO_STRING(SwapchainError, failed_create_swapchain_image_views)
        CASE_TO_STRING(SwapchainError, required_min_image_count_too_low)
        CASE_TO_STRING(SwapchainError, required_usage_not_supported)
        default:
            return "";
    }
}

std::runtime_error to_exception(InstanceError error)
{
    return std::runtime_error(to_string(error));
}
std::runtime_error to_exception(InstanceError error, VkResult result)
{
    std::string message{};
    message.append(to_string(error));
    message.append(": ");
    message.append(string_VkResult(result));
    return std::runtime_error(message);
}

std::runtime_error to_exception(PhysicalDeviceError error)
{
    return std::runtime_error(to_string(error));
}
std::runtime_error to_exception(PhysicalDeviceError error, VkResult result)
{
    std::string message{};
    message.append(to_string(error));
    message.append(": ");
    message.append(string_VkResult(result));
    return std::runtime_error(message);
}

std::runtime_error to_exception(QueueError error)
{
    return std::runtime_error(to_string(error));
}
std::runtime_error to_exception(QueueError error, VkResult result)
{
    std::string message{};
    message.append(to_string(error));
    message.append(": ");
    message.append(string_VkResult(result));
    return std::runtime_error(message);
}

std::runtime_error to_exception(DeviceError error)
{
    return std::runtime_error(to_string(error));
}
std::runtime_error to_exception(DeviceError error, VkResult result)
{
    std::string message{};
    message.append(to_string(error));
    message.append(": ");
    message.append(string_VkResult(result));
    return std::runtime_error(message);
}

std::runtime_error to_exception(SwapchainError error)
{
    return std::runtime_error(to_string(error));
}
std::runtime_error to_exception(SwapchainError error, VkResult result)
{
    std::string message{};
    message.append(to_string(error));
    message.append(": ");
    message.append(string_VkResult(result));
    return std::runtime_error(message);
}

SystemInfo SystemInfo::get_system_info(PFN_vkGetInstanceProcAddr fp_vkGetInstanceProcAddr = nullptr)
{
    // Using externally provided function pointers, assume the loader is available
    if (!detail::get_instance_table().init_vulkan_funcs(fp_vkGetInstanceProcAddr))
    {
        throw to_exception(InstanceError::vulkan_unavailable);
    }
    return SystemInfo();
}

SystemInfo::SystemInfo()
{
    auto available_layers_ret = detail::get_vector<VkLayerProperties>(
        available_layers, detail::get_instance_table().fp_vkEnumerateInstanceLayerProperties);
    if (available_layers_ret != VK_SUCCESS)
    {
        available_layers.clear();
    }

    for (auto& layer : available_layers)
        if (strcmp(layer.layerName, detail::validation_layer_name) == 0)
            validation_layers_available = true;

    auto available_extensions_ret = detail::get_vector<VkExtensionProperties>(
        available_extensions, detail::get_instance_table().fp_vkEnumerateInstanceExtensionProperties, nullptr);
    if (available_extensions_ret != VK_SUCCESS)
    {
        available_extensions.clear();
    }

    for (auto& ext : available_extensions)
    {
        if (strcmp(ext.extensionName, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0)
        {
            debug_utils_available = true;
        }
    }

    for (auto& layer : available_layers)
    {
        std::vector<VkExtensionProperties> layer_extensions;
        auto                               layer_extensions_ret = detail::get_vector<VkExtensionProperties>(
            layer_extensions, detail::get_instance_table().fp_vkEnumerateInstanceExtensionProperties, layer.layerName);
        if (layer_extensions_ret == VK_SUCCESS)
        {
            available_extensions.insert(available_extensions.end(), layer_extensions.begin(), layer_extensions.end());
            for (auto& ext : layer_extensions)
            {
                if (strcmp(ext.extensionName, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0)
                {
                    debug_utils_available = true;
                }
            }
        }
    }
}

bool SystemInfo::is_extension_available(const char* extension_name) const
{
    if (!extension_name)
        return false;
    return detail::check_extension_supported(available_extensions, extension_name);
}

bool SystemInfo::is_layer_available(const char* layer_name) const
{
    if (!layer_name)
        return false;
    return detail::check_layer_supported(available_layers, layer_name);
}

void destroy_surface(Instance const& instance, VkSurfaceKHR surface)
{
    if (instance.instance != VK_NULL_HANDLE && surface != VK_NULL_HANDLE)
    {
        detail::get_instance_table().inst_table.DestroySurfaceKHR(
            instance.instance, surface, instance.allocation_callbacks);
    }
}

void destroy_surface(VkInstance instance, VkSurfaceKHR surface, VkAllocationCallbacks* callbacks)
{
    if (instance != VK_NULL_HANDLE && surface != VK_NULL_HANDLE)
    {
        detail::get_instance_table().inst_table.DestroySurfaceKHR(instance, surface, callbacks);
    }
}

void destroy_instance(Instance const& instance)
{
    if (instance.instance != VK_NULL_HANDLE)
    {
        if (instance.debug_messenger != VK_NULL_HANDLE)
            destroy_debug_utils_messenger(instance.instance, instance.debug_messenger, instance.allocation_callbacks);
        detail::get_instance_table().inst_table.DestroyInstance(instance.instance, instance.allocation_callbacks);
    }
}

void destroy_window(decode::WindowFactory* window_factory, decode::Window* window)
{
    if (window_factory != nullptr)
    {
        window_factory->Destroy(window);
    }
}

Instance::operator VkInstance() const
{
    return instance;
}

vkb::InstanceDispatchTable Instance::make_table() const
{
    return { instance, fp_vkGetInstanceProcAddr };
}

InstanceBuilder::InstanceBuilder(PFN_vkGetInstanceProcAddr fp_vkGetInstanceProcAddr)
{
    info.fp_vkGetInstanceProcAddr = fp_vkGetInstanceProcAddr;
}
InstanceBuilder::InstanceBuilder() {}

Instance InstanceBuilder::build() const
{

    auto system = SystemInfo::get_system_info(info.fp_vkGetInstanceProcAddr);

    uint32_t instance_version = VKB_VK_API_VERSION_1_0;

    if (info.minimum_instance_version > VKB_VK_API_VERSION_1_0 || info.required_api_version > VKB_VK_API_VERSION_1_0 ||
        info.desired_api_version > VKB_VK_API_VERSION_1_0)
    {
        PFN_vkEnumerateInstanceVersion pfn_vkEnumerateInstanceVersion =
            detail::get_instance_table().fp_vkEnumerateInstanceVersion;

        if (pfn_vkEnumerateInstanceVersion != nullptr)
        {
            VkResult res = pfn_vkEnumerateInstanceVersion(&instance_version);
            // Should always return VK_SUCCESS
            if (res != VK_SUCCESS && info.required_api_version > 0)
                throw to_exception(InstanceError::vulkan_version_unavailable);
        }
        if (pfn_vkEnumerateInstanceVersion == nullptr || instance_version < info.minimum_instance_version ||
            (info.minimum_instance_version == 0 && instance_version < info.required_api_version))
        {
            if (VK_VERSION_MINOR(info.required_api_version) == 2)
                throw to_exception(InstanceError::vulkan_version_1_2_unavailable);
            else if (VK_VERSION_MINOR(info.required_api_version))
                throw to_exception(InstanceError::vulkan_version_1_1_unavailable);
            else
                throw to_exception(InstanceError::vulkan_version_unavailable);
        }
    }

    uint32_t api_version = instance_version < VKB_VK_API_VERSION_1_1 ? instance_version : info.required_api_version;

    if (info.desired_api_version > VKB_VK_API_VERSION_1_0 && instance_version >= info.desired_api_version)
    {
        instance_version = info.desired_api_version;
        api_version      = info.desired_api_version;
    }

    VkApplicationInfo app_info  = {};
    app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext              = nullptr;
    app_info.pApplicationName   = info.app_name != nullptr ? info.app_name : "";
    app_info.applicationVersion = info.application_version;
    app_info.pEngineName        = info.engine_name != nullptr ? info.engine_name : "";
    app_info.engineVersion      = info.engine_version;
    app_info.apiVersion         = api_version;

    std::vector<const char*> extensions;
    std::vector<const char*> layers;

    for (auto& ext : info.extensions) extensions.push_back(ext);
    if (info.debug_callback != nullptr && info.use_debug_messenger && system.debug_utils_available)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    bool properties2_ext_enabled =
        api_version < VKB_VK_API_VERSION_1_1 &&
        detail::check_extension_supported(system.available_extensions,
                                          VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    if (properties2_ext_enabled)
    {
        extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    }

#if defined(VK_KHR_portability_enumeration)
    bool portability_enumeration_support =
        detail::check_extension_supported(system.available_extensions, VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    if (portability_enumeration_support)
    {
        extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    }
#else
    bool portability_enumeration_support = false;
#endif

    if (!info.headless_context)
    {
        auto check_add_window_ext = [&](const char* name) -> bool {
            if (!detail::check_extension_supported(system.available_extensions, name))
                return false;
            extensions.push_back(name);
            return true;
        };
        bool khr_surface_added = check_add_window_ext("VK_KHR_surface");
        bool added_window_exts = false;
        if (std::getenv("GFXRECON_TESTAPP_HEADLESS") != nullptr)
        {
            added_window_exts = check_add_window_ext("VK_EXT_headless_surface");
        }
        else
        {
#if defined(_WIN32)
            added_window_exts = check_add_window_ext("VK_KHR_win32_surface");
#elif defined(__ANDROID__)
            added_window_exts = check_add_window_ext("VK_KHR_android_surface");
#elif defined(_DIRECT2DISPLAY)
            added_window_exts = check_add_window_ext("VK_KHR_display");
#elif defined(__linux__)
            // make sure all three calls to check_add_window_ext, don't allow short circuiting
            added_window_exts = check_add_window_ext("VK_KHR_xcb_surface");
            added_window_exts = check_add_window_ext("VK_KHR_xlib_surface") || added_window_exts;
            added_window_exts = check_add_window_ext("VK_KHR_wayland_surface") || added_window_exts;
#elif defined(__APPLE__)
            added_window_exts = check_add_window_ext("VK_EXT_metal_surface");
#endif
        }
        if (!khr_surface_added || !added_window_exts)
            throw to_exception(InstanceError::windowing_extensions_not_present);
    }
    bool all_extensions_supported = detail::check_extensions_supported(system.available_extensions, extensions);
    if (!all_extensions_supported)
    {
        throw to_exception(InstanceError::requested_extensions_not_present);
    }

    for (auto& layer : info.layers) layers.push_back(layer);

    if (info.enable_validation_layers || (info.request_validation_layers && system.validation_layers_available))
    {
        layers.push_back(detail::validation_layer_name);
    }
    bool all_layers_supported = detail::check_layers_supported(system.available_layers, layers);
    if (!all_layers_supported)
    {
        throw to_exception(InstanceError::requested_layers_not_present);
    }

    std::vector<VkBaseOutStructure*> pNext_chain;

    VkDebugUtilsMessengerCreateInfoEXT messengerCreateInfo = {};
    if (info.use_debug_messenger)
    {
        messengerCreateInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        messengerCreateInfo.pNext           = nullptr;
        messengerCreateInfo.messageSeverity = info.debug_message_severity;
        messengerCreateInfo.messageType     = info.debug_message_type;
        messengerCreateInfo.pfnUserCallback = info.debug_callback;
        messengerCreateInfo.pUserData       = info.debug_user_data_pointer;
        pNext_chain.push_back(reinterpret_cast<VkBaseOutStructure*>(&messengerCreateInfo));
    }

    VkValidationFeaturesEXT features{};
    if (info.enabled_validation_features.size() != 0 || info.disabled_validation_features.size())
    {
        features.sType                          = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
        features.pNext                          = nullptr;
        features.enabledValidationFeatureCount  = static_cast<uint32_t>(info.enabled_validation_features.size());
        features.pEnabledValidationFeatures     = info.enabled_validation_features.data();
        features.disabledValidationFeatureCount = static_cast<uint32_t>(info.disabled_validation_features.size());
        features.pDisabledValidationFeatures    = info.disabled_validation_features.data();
        pNext_chain.push_back(reinterpret_cast<VkBaseOutStructure*>(&features));
    }

    VkValidationFlagsEXT checks{};
    if (info.disabled_validation_checks.size() != 0)
    {
        checks.sType                        = VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT;
        checks.pNext                        = nullptr;
        checks.disabledValidationCheckCount = static_cast<uint32_t>(info.disabled_validation_checks.size());
        checks.pDisabledValidationChecks    = info.disabled_validation_checks.data();
        pNext_chain.push_back(reinterpret_cast<VkBaseOutStructure*>(&checks));
    }

    VkInstanceCreateInfo instance_create_info = {};
    instance_create_info.sType                = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    detail::setup_pNext_chain(instance_create_info, pNext_chain);
#if !defined(NDEBUG)
    for (auto& node : pNext_chain)
    {
        assert(node->sType != VK_STRUCTURE_TYPE_APPLICATION_INFO);
    }
#endif
    instance_create_info.flags                   = info.flags;
    if (portability_enumeration_support)
    {
        instance_create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    }
    instance_create_info.pApplicationInfo        = &app_info;
    instance_create_info.enabledExtensionCount   = static_cast<uint32_t>(extensions.size());
    instance_create_info.ppEnabledExtensionNames = extensions.data();
    instance_create_info.enabledLayerCount       = static_cast<uint32_t>(layers.size());
    instance_create_info.ppEnabledLayerNames     = layers.data();

    Instance instance;
    VkResult res = detail::get_instance_table().fp_vkCreateInstance(
        &instance_create_info, info.allocation_callbacks, &instance.instance);
    if (res != VK_SUCCESS)
        throw to_exception(InstanceError::failed_create_instance, res);

    detail::get_instance_table().load_instance_table(instance.instance);

    if (info.use_debug_messenger)
    {
        res = create_debug_utils_messenger(instance.instance,
                                           info.debug_callback,
                                           info.debug_message_severity,
                                           info.debug_message_type,
                                           info.debug_user_data_pointer,
                                           &instance.debug_messenger,
                                           info.allocation_callbacks);
        if (res != VK_SUCCESS)
            throw to_exception(InstanceError::failed_create_debug_messenger, res);
    }

    instance.headless                 = info.headless_context;
    instance.properties2_ext_enabled  = properties2_ext_enabled;
    instance.allocation_callbacks     = info.allocation_callbacks;
    instance.instance_version         = instance_version;
    instance.api_version              = api_version;
    instance.fp_vkGetInstanceProcAddr = detail::get_instance_table().ptr_vkGetInstanceProcAddr;
    instance.fp_vkGetDeviceProcAddr   = detail::get_instance_table().fp_vkGetDeviceProcAddr;
    return instance;
}

InstanceBuilder& InstanceBuilder::set_app_name(const char* app_name)
{
    if (!app_name)
        return *this;
    info.app_name = app_name;
    return *this;
}
InstanceBuilder& InstanceBuilder::set_engine_name(const char* engine_name)
{
    if (!engine_name)
        return *this;
    info.engine_name = engine_name;
    return *this;
}
InstanceBuilder& InstanceBuilder::set_app_version(uint32_t app_version)
{
    info.application_version = app_version;
    return *this;
}
InstanceBuilder& InstanceBuilder::set_app_version(uint32_t major, uint32_t minor, uint32_t patch)
{
    info.application_version = VKB_MAKE_VK_VERSION(0, major, minor, patch);
    return *this;
}
InstanceBuilder& InstanceBuilder::set_engine_version(uint32_t engine_version)
{
    info.engine_version = engine_version;
    return *this;
}
InstanceBuilder& InstanceBuilder::set_engine_version(uint32_t major, uint32_t minor, uint32_t patch)
{
    info.engine_version = VKB_MAKE_VK_VERSION(0, major, minor, patch);
    return *this;
}
InstanceBuilder& InstanceBuilder::require_api_version(uint32_t required_api_version)
{
    info.required_api_version = required_api_version;
    return *this;
}
InstanceBuilder& InstanceBuilder::require_api_version(uint32_t major, uint32_t minor, uint32_t patch)
{
    info.required_api_version = VKB_MAKE_VK_VERSION(0, major, minor, patch);
    return *this;
}
InstanceBuilder& InstanceBuilder::set_minimum_instance_version(uint32_t minimum_instance_version)
{
    info.minimum_instance_version = minimum_instance_version;
    return *this;
}
InstanceBuilder& InstanceBuilder::set_minimum_instance_version(uint32_t major, uint32_t minor, uint32_t patch)
{
    info.minimum_instance_version = VKB_MAKE_VK_VERSION(0, major, minor, patch);
    return *this;
}
InstanceBuilder& InstanceBuilder::desire_api_version(uint32_t preferred_vulkan_version)
{
    info.desired_api_version = preferred_vulkan_version;
    return *this;
}
InstanceBuilder& InstanceBuilder::desire_api_version(uint32_t major, uint32_t minor, uint32_t patch)
{
    info.desired_api_version = VKB_MAKE_VK_VERSION(0, major, minor, patch);
    return *this;
}
InstanceBuilder& InstanceBuilder::enable_layer(const char* layer_name)
{
    if (!layer_name)
        return *this;
    info.layers.push_back(layer_name);
    return *this;
}
InstanceBuilder& InstanceBuilder::enable_extension(const char* extension_name)
{
    if (!extension_name)
        return *this;
    info.extensions.push_back(extension_name);
    return *this;
}
InstanceBuilder& InstanceBuilder::enable_extensions(std::vector<const char*> const& extensions)
{
    for (const auto extension : extensions)
    {
        info.extensions.push_back(extension);
    }
    return *this;
}
InstanceBuilder& InstanceBuilder::enable_extensions(size_t count, const char* const* extensions)
{
    if (!extensions || count == 0)
        return *this;
    for (size_t i = 0; i < count; i++)
    {
        info.extensions.push_back(extensions[i]);
    }
    return *this;
}
InstanceBuilder& InstanceBuilder::enable_validation_layers(bool enable_validation)
{
    info.enable_validation_layers = enable_validation;
    return *this;
}
InstanceBuilder& InstanceBuilder::request_validation_layers(bool enable_validation)
{
    info.request_validation_layers = enable_validation;
    return *this;
}

InstanceBuilder& InstanceBuilder::use_default_debug_messenger()
{
    info.use_debug_messenger = true;
    info.debug_callback      = default_debug_callback;
    return *this;
}
InstanceBuilder& InstanceBuilder::set_debug_callback(PFN_vkDebugUtilsMessengerCallbackEXT callback)
{
    info.use_debug_messenger = true;
    info.debug_callback      = callback;
    return *this;
}
InstanceBuilder& InstanceBuilder::set_debug_callback_user_data_pointer(void* user_data_pointer)
{
    info.debug_user_data_pointer = user_data_pointer;
    return *this;
}
InstanceBuilder& InstanceBuilder::set_headless(bool headless)
{
    info.headless_context = headless;
    return *this;
}
InstanceBuilder& InstanceBuilder::set_debug_messenger_severity(VkDebugUtilsMessageSeverityFlagsEXT severity)
{
    info.debug_message_severity = severity;
    return *this;
}
InstanceBuilder& InstanceBuilder::add_debug_messenger_severity(VkDebugUtilsMessageSeverityFlagsEXT severity)
{
    info.debug_message_severity = info.debug_message_severity | severity;
    return *this;
}
InstanceBuilder& InstanceBuilder::set_debug_messenger_type(VkDebugUtilsMessageTypeFlagsEXT type)
{
    info.debug_message_type = type;
    return *this;
}
InstanceBuilder& InstanceBuilder::add_debug_messenger_type(VkDebugUtilsMessageTypeFlagsEXT type)
{
    info.debug_message_type = info.debug_message_type | type;
    return *this;
}
InstanceBuilder& InstanceBuilder::add_validation_disable(VkValidationCheckEXT check)
{
    info.disabled_validation_checks.push_back(check);
    return *this;
}
InstanceBuilder& InstanceBuilder::add_validation_feature_enable(VkValidationFeatureEnableEXT enable)
{
    info.enabled_validation_features.push_back(enable);
    return *this;
}
InstanceBuilder& InstanceBuilder::add_validation_feature_disable(VkValidationFeatureDisableEXT disable)
{
    info.disabled_validation_features.push_back(disable);
    return *this;
}
InstanceBuilder& InstanceBuilder::set_allocation_callbacks(VkAllocationCallbacks* callbacks)
{
    info.allocation_callbacks = callbacks;
    return *this;
}

void destroy_debug_messenger(VkInstance const instance, VkDebugUtilsMessengerEXT const messenger);

// ---- Physical Device ---- //

GFXRECON_BEGIN_NAMESPACE(detail)

std::vector<std::string> check_device_extension_support(std::vector<std::string> const& available_extensions,
                                                        std::vector<std::string> const& desired_extensions)
{
    std::vector<std::string> extensions_to_enable;
    for (const auto& avail_ext : available_extensions)
    {
        for (auto& req_ext : desired_extensions)
        {
            if (avail_ext == req_ext)
            {
                extensions_to_enable.push_back(req_ext);
                break;
            }
        }
    }
    return extensions_to_enable;
}

// clang-format off
void combine_features(VkPhysicalDeviceFeatures& dest, VkPhysicalDeviceFeatures src){
    dest.robustBufferAccess = dest.robustBufferAccess || src.robustBufferAccess;
	dest.fullDrawIndexUint32 = dest.fullDrawIndexUint32 || src.fullDrawIndexUint32;
	dest.imageCubeArray = dest.imageCubeArray || src.imageCubeArray;
	dest.independentBlend = dest.independentBlend || src.independentBlend;
	dest.geometryShader = dest.geometryShader || src.geometryShader;
	dest.tessellationShader = dest.tessellationShader || src.tessellationShader;
	dest.sampleRateShading = dest.sampleRateShading || src.sampleRateShading;
	dest.dualSrcBlend = dest.dualSrcBlend || src.dualSrcBlend;
	dest.logicOp = dest.logicOp || src.logicOp;
	dest.multiDrawIndirect = dest.multiDrawIndirect || src.multiDrawIndirect;
	dest.drawIndirectFirstInstance = dest.drawIndirectFirstInstance || src.drawIndirectFirstInstance;
	dest.depthClamp = dest.depthClamp || src.depthClamp;
	dest.depthBiasClamp = dest.depthBiasClamp || src.depthBiasClamp;
	dest.fillModeNonSolid = dest.fillModeNonSolid || src.fillModeNonSolid;
	dest.depthBounds = dest.depthBounds || src.depthBounds;
	dest.wideLines = dest.wideLines || src.wideLines;
	dest.largePoints = dest.largePoints || src.largePoints;
	dest.alphaToOne = dest.alphaToOne || src.alphaToOne;
	dest.multiViewport = dest.multiViewport || src.multiViewport;
	dest.samplerAnisotropy = dest.samplerAnisotropy || src.samplerAnisotropy;
	dest.textureCompressionETC2 = dest.textureCompressionETC2 || src.textureCompressionETC2;
	dest.textureCompressionASTC_LDR = dest.textureCompressionASTC_LDR || src.textureCompressionASTC_LDR;
	dest.textureCompressionBC = dest.textureCompressionBC || src.textureCompressionBC;
	dest.occlusionQueryPrecise = dest.occlusionQueryPrecise || src.occlusionQueryPrecise;
	dest.pipelineStatisticsQuery = dest.pipelineStatisticsQuery || src.pipelineStatisticsQuery;
	dest.vertexPipelineStoresAndAtomics = dest.vertexPipelineStoresAndAtomics || src.vertexPipelineStoresAndAtomics;
	dest.fragmentStoresAndAtomics = dest.fragmentStoresAndAtomics || src.fragmentStoresAndAtomics;
	dest.shaderTessellationAndGeometryPointSize = dest.shaderTessellationAndGeometryPointSize || src.shaderTessellationAndGeometryPointSize;
	dest.shaderImageGatherExtended = dest.shaderImageGatherExtended || src.shaderImageGatherExtended;
	dest.shaderStorageImageExtendedFormats = dest.shaderStorageImageExtendedFormats || src.shaderStorageImageExtendedFormats;
	dest.shaderStorageImageMultisample = dest.shaderStorageImageMultisample || src.shaderStorageImageMultisample;
	dest.shaderStorageImageReadWithoutFormat = dest.shaderStorageImageReadWithoutFormat || src.shaderStorageImageReadWithoutFormat;
	dest.shaderStorageImageWriteWithoutFormat = dest.shaderStorageImageWriteWithoutFormat || src.shaderStorageImageWriteWithoutFormat;
	dest.shaderUniformBufferArrayDynamicIndexing = dest.shaderUniformBufferArrayDynamicIndexing || src.shaderUniformBufferArrayDynamicIndexing;
	dest.shaderSampledImageArrayDynamicIndexing = dest.shaderSampledImageArrayDynamicIndexing || src.shaderSampledImageArrayDynamicIndexing;
	dest.shaderStorageBufferArrayDynamicIndexing = dest.shaderStorageBufferArrayDynamicIndexing || src.shaderStorageBufferArrayDynamicIndexing;
	dest.shaderStorageImageArrayDynamicIndexing = dest.shaderStorageImageArrayDynamicIndexing || src.shaderStorageImageArrayDynamicIndexing;
	dest.shaderClipDistance = dest.shaderClipDistance || src.shaderClipDistance;
	dest.shaderCullDistance = dest.shaderCullDistance || src.shaderCullDistance;
	dest.shaderFloat64 = dest.shaderFloat64 || src.shaderFloat64;
	dest.shaderInt64 = dest.shaderInt64 || src.shaderInt64;
	dest.shaderInt16 = dest.shaderInt16 || src.shaderInt16;
	dest.shaderResourceResidency = dest.shaderResourceResidency || src.shaderResourceResidency;
	dest.shaderResourceMinLod = dest.shaderResourceMinLod || src.shaderResourceMinLod;
	dest.sparseBinding = dest.sparseBinding || src.sparseBinding;
	dest.sparseResidencyBuffer = dest.sparseResidencyBuffer || src.sparseResidencyBuffer;
	dest.sparseResidencyImage2D = dest.sparseResidencyImage2D || src.sparseResidencyImage2D;
	dest.sparseResidencyImage3D = dest.sparseResidencyImage3D || src.sparseResidencyImage3D;
	dest.sparseResidency2Samples = dest.sparseResidency2Samples || src.sparseResidency2Samples;
	dest.sparseResidency4Samples = dest.sparseResidency4Samples || src.sparseResidency4Samples;
	dest.sparseResidency8Samples = dest.sparseResidency8Samples || src.sparseResidency8Samples;
	dest.sparseResidency16Samples = dest.sparseResidency16Samples || src.sparseResidency16Samples;
	dest.sparseResidencyAliased = dest.sparseResidencyAliased || src.sparseResidencyAliased;
	dest.variableMultisampleRate = dest.variableMultisampleRate || src.variableMultisampleRate;
	dest.inheritedQueries = dest.inheritedQueries || src.inheritedQueries;
}

bool supports_features(const VkPhysicalDeviceFeatures& supported,
					   const VkPhysicalDeviceFeatures& requested,
					   const GenericFeatureChain& extension_supported,
					   const GenericFeatureChain& extension_requested) {

	if (requested.robustBufferAccess && !supported.robustBufferAccess) return false;
	if (requested.fullDrawIndexUint32 && !supported.fullDrawIndexUint32) return false;
	if (requested.imageCubeArray && !supported.imageCubeArray) return false;
	if (requested.independentBlend && !supported.independentBlend) return false;
	if (requested.geometryShader && !supported.geometryShader) return false;
	if (requested.tessellationShader && !supported.tessellationShader) return false;
	if (requested.sampleRateShading && !supported.sampleRateShading) return false;
	if (requested.dualSrcBlend && !supported.dualSrcBlend) return false;
	if (requested.logicOp && !supported.logicOp) return false;
	if (requested.multiDrawIndirect && !supported.multiDrawIndirect) return false;
	if (requested.drawIndirectFirstInstance && !supported.drawIndirectFirstInstance) return false;
	if (requested.depthClamp && !supported.depthClamp) return false;
	if (requested.depthBiasClamp && !supported.depthBiasClamp) return false;
	if (requested.fillModeNonSolid && !supported.fillModeNonSolid) return false;
	if (requested.depthBounds && !supported.depthBounds) return false;
	if (requested.wideLines && !supported.wideLines) return false;
	if (requested.largePoints && !supported.largePoints) return false;
	if (requested.alphaToOne && !supported.alphaToOne) return false;
	if (requested.multiViewport && !supported.multiViewport) return false;
	if (requested.samplerAnisotropy && !supported.samplerAnisotropy) return false;
	if (requested.textureCompressionETC2 && !supported.textureCompressionETC2) return false;
	if (requested.textureCompressionASTC_LDR && !supported.textureCompressionASTC_LDR) return false;
	if (requested.textureCompressionBC && !supported.textureCompressionBC) return false;
	if (requested.occlusionQueryPrecise && !supported.occlusionQueryPrecise) return false;
	if (requested.pipelineStatisticsQuery && !supported.pipelineStatisticsQuery) return false;
	if (requested.vertexPipelineStoresAndAtomics && !supported.vertexPipelineStoresAndAtomics) return false;
	if (requested.fragmentStoresAndAtomics && !supported.fragmentStoresAndAtomics) return false;
	if (requested.shaderTessellationAndGeometryPointSize && !supported.shaderTessellationAndGeometryPointSize) return false;
	if (requested.shaderImageGatherExtended && !supported.shaderImageGatherExtended) return false;
	if (requested.shaderStorageImageExtendedFormats && !supported.shaderStorageImageExtendedFormats) return false;
	if (requested.shaderStorageImageMultisample && !supported.shaderStorageImageMultisample) return false;
	if (requested.shaderStorageImageReadWithoutFormat && !supported.shaderStorageImageReadWithoutFormat) return false;
	if (requested.shaderStorageImageWriteWithoutFormat && !supported.shaderStorageImageWriteWithoutFormat) return false;
	if (requested.shaderUniformBufferArrayDynamicIndexing && !supported.shaderUniformBufferArrayDynamicIndexing) return false;
	if (requested.shaderSampledImageArrayDynamicIndexing && !supported.shaderSampledImageArrayDynamicIndexing) return false;
	if (requested.shaderStorageBufferArrayDynamicIndexing && !supported.shaderStorageBufferArrayDynamicIndexing) return false;
	if (requested.shaderStorageImageArrayDynamicIndexing && !supported.shaderStorageImageArrayDynamicIndexing) return false;
	if (requested.shaderClipDistance && !supported.shaderClipDistance) return false;
	if (requested.shaderCullDistance && !supported.shaderCullDistance) return false;
	if (requested.shaderFloat64 && !supported.shaderFloat64) return false;
	if (requested.shaderInt64 && !supported.shaderInt64) return false;
	if (requested.shaderInt16 && !supported.shaderInt16) return false;
	if (requested.shaderResourceResidency && !supported.shaderResourceResidency) return false;
	if (requested.shaderResourceMinLod && !supported.shaderResourceMinLod) return false;
	if (requested.sparseBinding && !supported.sparseBinding) return false;
	if (requested.sparseResidencyBuffer && !supported.sparseResidencyBuffer) return false;
	if (requested.sparseResidencyImage2D && !supported.sparseResidencyImage2D) return false;
	if (requested.sparseResidencyImage3D && !supported.sparseResidencyImage3D) return false;
	if (requested.sparseResidency2Samples && !supported.sparseResidency2Samples) return false;
	if (requested.sparseResidency4Samples && !supported.sparseResidency4Samples) return false;
	if (requested.sparseResidency8Samples && !supported.sparseResidency8Samples) return false;
	if (requested.sparseResidency16Samples && !supported.sparseResidency16Samples) return false;
	if (requested.sparseResidencyAliased && !supported.sparseResidencyAliased) return false;
	if (requested.variableMultisampleRate && !supported.variableMultisampleRate) return false;
	if (requested.inheritedQueries && !supported.inheritedQueries) return false;

	return extension_supported.match_all(extension_requested);
}
// clang-format on
// Finds the first queue which supports the desired operations.
std::optional<uint32_t> get_first_queue_index(std::vector<VkQueueFamilyProperties> const& families,
                                              VkQueueFlags                                desired_flags)
{
    for (uint32_t i = 0; i < static_cast<uint32_t>(families.size()); i++)
    {
        if ((families[i].queueFlags & desired_flags) == desired_flags)
            return i;
    }
    return {};
}
// Finds the queue which is separate from the graphics queue and has the desired flag and not the
// undesired flag, but will select it if no better options are available compute support.
std::optional<uint32_t> get_separate_queue_index(std::vector<VkQueueFamilyProperties> const& families,
                                                 VkQueueFlags                                desired_flags,
                                                 VkQueueFlags                                undesired_flags)
{
    std::optional<uint32_t> index = {};
    for (uint32_t i = 0; i < static_cast<uint32_t>(families.size()); i++)
    {
        if ((families[i].queueFlags & desired_flags) == desired_flags &&
            ((families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0))
        {
            if ((families[i].queueFlags & undesired_flags) == 0)
            {
                return i;
            }
            else
            {
                index = i;
            }
        }
    }
    return index;
}

// finds the first queue which supports only the desired flag (not graphics or transfer).
std::optional<uint32_t> get_dedicated_queue_index(std::vector<VkQueueFamilyProperties> const& families,
                                                  VkQueueFlags                                desired_flags,
                                                  VkQueueFlags                                undesired_flags)
{
    for (uint32_t i = 0; i < static_cast<uint32_t>(families.size()); i++)
    {
        if ((families[i].queueFlags & desired_flags) == desired_flags &&
            (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0 && (families[i].queueFlags & undesired_flags) == 0)
            return i;
    }
    return {};
}

// finds the first queue which supports presenting.
std::optional<uint32_t> get_present_queue_index(VkPhysicalDevice const                      phys_device,
                                                VkSurfaceKHR const                          surface,
                                                std::vector<VkQueueFamilyProperties> const& families)
{
    for (uint32_t i = 0; i < static_cast<uint32_t>(families.size()); i++)
    {
        VkBool32 presentSupport = false;
        if (surface != VK_NULL_HANDLE)
        {
            VkResult res = detail::get_instance_table().inst_table.GetPhysicalDeviceSurfaceSupportKHR(
                phys_device, i, surface, &presentSupport);
            if (res != VK_SUCCESS)
                return {}; // TODO: determine if this should fail another way
        }
        if (presentSupport == VK_TRUE)
            return i;
    }
    return {};
}

GFXRECON_END_NAMESPACE(detail)

PhysicalDevice
PhysicalDeviceSelector::populate_device_details(VkPhysicalDevice                   vk_phys_device,
                                                detail::GenericFeatureChain const& src_extended_features_chain) const
{
    PhysicalDevice physical_device{};
    physical_device.physical_device              = vk_phys_device;
    physical_device.surface                      = instance_info.surface;
    physical_device.defer_surface_initialization = criteria.defer_surface_initialization;
    physical_device.instance_version             = instance_info.version;
    auto queue_families                          = detail::get_vector_noerror<VkQueueFamilyProperties>(
        detail::get_instance_table().inst_table.GetPhysicalDeviceQueueFamilyProperties, vk_phys_device);
    physical_device.queue_families = queue_families;

    detail::get_instance_table().inst_table.GetPhysicalDeviceProperties(vk_phys_device, &physical_device.properties);
    detail::get_instance_table().inst_table.GetPhysicalDeviceFeatures(vk_phys_device, &physical_device.features);
    detail::get_instance_table().inst_table.GetPhysicalDeviceMemoryProperties(vk_phys_device,
                                                                              &physical_device.memory_properties);

    physical_device.name = physical_device.properties.deviceName;

    std::vector<VkExtensionProperties> available_extensions;
    auto                               available_extensions_ret = detail::get_vector<VkExtensionProperties>(
        available_extensions,
        detail::get_instance_table().inst_table.EnumerateDeviceExtensionProperties,
        vk_phys_device,
        nullptr);
    if (available_extensions_ret != VK_SUCCESS)
        return physical_device;
    for (const auto& ext : available_extensions)
    {
        physical_device.available_extensions.push_back(&ext.extensionName[0]);
    }

    physical_device.properties2_ext_enabled = instance_info.properties2_ext_enabled;

    auto fill_chain = src_extended_features_chain;

    bool instance_is_1_1 = instance_info.version >= VKB_VK_API_VERSION_1_1;
    if (!fill_chain.nodes.empty() && (instance_is_1_1 || instance_info.properties2_ext_enabled))
    {
        VkPhysicalDeviceFeatures2 local_features{};
        fill_chain.chain_up(local_features);
        // Use KHR function if not able to use the core function
        if (instance_is_1_1)
        {
            detail::get_instance_table().inst_table.GetPhysicalDeviceFeatures2(vk_phys_device, &local_features);
        }
        else
        {
            detail::get_instance_table().inst_table.GetPhysicalDeviceFeatures2KHR(vk_phys_device, &local_features);
        }
        physical_device.extended_features_chain = fill_chain;
    }

    return physical_device;
}

PhysicalDevice::Suitable PhysicalDeviceSelector::is_device_suitable(PhysicalDevice const& pd) const
{
    PhysicalDevice::Suitable suitable = PhysicalDevice::Suitable::yes;

    if (criteria.name.size() > 0 && criteria.name != pd.properties.deviceName)
        return PhysicalDevice::Suitable::no;

    if (criteria.required_version > pd.properties.apiVersion)
        return PhysicalDevice::Suitable::no;
    if (criteria.desired_version > pd.properties.apiVersion)
        suitable = PhysicalDevice::Suitable::partial;

    bool dedicated_compute =
        detail::get_dedicated_queue_index(pd.queue_families, VK_QUEUE_COMPUTE_BIT, VK_QUEUE_TRANSFER_BIT).has_value();
    bool dedicated_transfer =
        detail::get_dedicated_queue_index(pd.queue_families, VK_QUEUE_TRANSFER_BIT, VK_QUEUE_COMPUTE_BIT).has_value();
    bool separate_compute =
        detail::get_separate_queue_index(pd.queue_families, VK_QUEUE_COMPUTE_BIT, VK_QUEUE_TRANSFER_BIT).has_value();
    bool separate_transfer =
        detail::get_separate_queue_index(pd.queue_families, VK_QUEUE_TRANSFER_BIT, VK_QUEUE_COMPUTE_BIT).has_value();

    bool present_queue =
        detail::get_present_queue_index(pd.physical_device, instance_info.surface, pd.queue_families).has_value();

    if (criteria.require_dedicated_compute_queue && !dedicated_compute)
    {
        return PhysicalDevice::Suitable::no;
    }
    if (criteria.require_dedicated_transfer_queue && !dedicated_transfer)
    {
        return PhysicalDevice::Suitable::no;
    }
    if (criteria.require_separate_compute_queue && !separate_compute)
    {
        return PhysicalDevice::Suitable::no;
    }
    if (criteria.require_separate_transfer_queue && !separate_transfer)
    {
        return PhysicalDevice::Suitable::no;
    }
    if (criteria.require_present && !present_queue && !criteria.defer_surface_initialization)
    {
        return PhysicalDevice::Suitable::no;
    }

    auto required_extensions_supported =
        detail::check_device_extension_support(pd.available_extensions, criteria.required_extensions);
    if (required_extensions_supported.size() != criteria.required_extensions.size())
        return PhysicalDevice::Suitable::no;

    auto desired_extensions_supported =
        detail::check_device_extension_support(pd.available_extensions, criteria.desired_extensions);
    if (desired_extensions_supported.size() != criteria.desired_extensions.size())
        suitable = PhysicalDevice::Suitable::partial;

    if (!criteria.defer_surface_initialization && criteria.require_present)
    {
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR>   present_modes;

        auto formats_ret = detail::get_vector<VkSurfaceFormatKHR>(
            formats,
            detail::get_instance_table().inst_table.GetPhysicalDeviceSurfaceFormatsKHR,
            pd.physical_device,
            instance_info.surface);
        auto present_modes_ret = detail::get_vector<VkPresentModeKHR>(
            present_modes,
            detail::get_instance_table().inst_table.GetPhysicalDeviceSurfacePresentModesKHR,
            pd.physical_device,
            instance_info.surface);

        if (formats_ret != VK_SUCCESS || present_modes_ret != VK_SUCCESS || formats.empty() || present_modes.empty())
        {
            return PhysicalDevice::Suitable::no;
        }
    }

    if (!criteria.allow_any_type &&
        pd.properties.deviceType != static_cast<VkPhysicalDeviceType>(criteria.preferred_type))
    {
        suitable = PhysicalDevice::Suitable::partial;
    }

    bool required_features_supported = detail::supports_features(
        pd.features, criteria.required_features, pd.extended_features_chain, criteria.extended_features_chain);
    if (!required_features_supported)
        return PhysicalDevice::Suitable::no;

    for (uint32_t i = 0; i < pd.memory_properties.memoryHeapCount; i++)
    {
        if (pd.memory_properties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
        {
            if (pd.memory_properties.memoryHeaps[i].size < criteria.required_mem_size)
            {
                return PhysicalDevice::Suitable::no;
            }
            else if (pd.memory_properties.memoryHeaps[i].size < criteria.desired_mem_size)
            {
                suitable = PhysicalDevice::Suitable::partial;
            }
        }
    }

    return suitable;
}
// delegate construction to the one with an explicit surface parameter
PhysicalDeviceSelector::PhysicalDeviceSelector(Instance const& instance) :
    PhysicalDeviceSelector(instance, VK_NULL_HANDLE)
{}

PhysicalDeviceSelector::PhysicalDeviceSelector(Instance const& instance, VkSurfaceKHR surface)
{
    instance_info.instance                = instance.instance;
    instance_info.version                 = instance.instance_version;
    instance_info.properties2_ext_enabled = instance.properties2_ext_enabled;
    instance_info.surface                 = surface;
    criteria.require_present              = !instance.headless;
    criteria.required_version             = instance.api_version;
    criteria.desired_version              = instance.api_version;
}

std::vector<PhysicalDevice> PhysicalDeviceSelector::select_impl(DeviceSelectionMode selection) const
{
#if !defined(NDEBUG)
    // Validation
    for (const auto& node : criteria.extended_features_chain.nodes)
    {
        assert(node.sType != static_cast<VkStructureType>(0) &&
               "Features struct sType must be filled with the struct's "
               "corresponding VkStructureType enum");
        assert(node.sType != VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 &&
               "Do not pass VkPhysicalDeviceFeatures2 as a required extension feature structure. An "
               "instance of this is managed internally for selection criteria and device creation.");
    }
#endif

    if (criteria.require_present && !criteria.defer_surface_initialization)
    {
        if (instance_info.surface == VK_NULL_HANDLE)
            throw to_exception(PhysicalDeviceError::no_surface_provided);
    }

    // Get the VkPhysicalDevice handles on the system
    std::vector<VkPhysicalDevice> vk_physical_devices;

    auto vk_physical_devices_ret = detail::get_vector<VkPhysicalDevice>(
        vk_physical_devices, detail::get_instance_table().inst_table.EnumeratePhysicalDevices, instance_info.instance);
    if (vk_physical_devices_ret != VK_SUCCESS)
    {
        throw to_exception(PhysicalDeviceError::failed_enumerate_physical_devices, vk_physical_devices_ret);
    }
    if (vk_physical_devices.size() == 0)
    {
        throw to_exception(PhysicalDeviceError::no_physical_devices_found);
    }

    auto fill_out_phys_dev_with_criteria = [&](PhysicalDevice& phys_dev) {
        phys_dev.features                = criteria.required_features;
        phys_dev.extended_features_chain = criteria.extended_features_chain;
        bool portability_ext_available   = false;
        for (const auto& ext : phys_dev.available_extensions)
            if (criteria.enable_portability_subset && ext == "VK_KHR_portability_subset")
                portability_ext_available = true;

        auto desired_extensions_supported =
            detail::check_device_extension_support(phys_dev.available_extensions, criteria.desired_extensions);

        phys_dev.extensions_to_enable.clear();
        phys_dev.extensions_to_enable.insert(phys_dev.extensions_to_enable.end(),
                                             criteria.required_extensions.begin(),
                                             criteria.required_extensions.end());
        phys_dev.extensions_to_enable.insert(phys_dev.extensions_to_enable.end(),
                                             desired_extensions_supported.begin(),
                                             desired_extensions_supported.end());
        if (portability_ext_available)
        {
            phys_dev.extensions_to_enable.push_back("VK_KHR_portability_subset");
        }
    };

    // if this option is set, always return only the first physical device found
    if (criteria.use_first_gpu_unconditionally && vk_physical_devices.size() > 0)
    {
        PhysicalDevice physical_device =
            populate_device_details(vk_physical_devices[0], criteria.extended_features_chain);
        fill_out_phys_dev_with_criteria(physical_device);
        return std::vector<PhysicalDevice>{ physical_device };
    }

    // Populate their details and check their suitability
    std::vector<PhysicalDevice> physical_devices;
    for (auto& vk_physical_device : vk_physical_devices)
    {
        PhysicalDevice phys_dev = populate_device_details(vk_physical_device, criteria.extended_features_chain);
        phys_dev.suitable       = is_device_suitable(phys_dev);
        if (phys_dev.suitable != PhysicalDevice::Suitable::no)
        {
            physical_devices.push_back(phys_dev);
        }
    }

    // sort the list into fully and partially suitable devices. use stable_partition to maintain relative order
    const auto partition_index =
        std::stable_partition(physical_devices.begin(), physical_devices.end(), [](auto const& pd) {
            return pd.suitable == PhysicalDevice::Suitable::yes;
        });

    // Remove the partially suitable elements if they aren't desired
    if (selection == DeviceSelectionMode::only_fully_suitable)
    {
        physical_devices.erase(partition_index, physical_devices.end());
    }

    // Make the physical device ready to be used to create a Device from it
    for (auto& physical_device : physical_devices)
    {
        fill_out_phys_dev_with_criteria(physical_device);
    }

    return physical_devices;
}

PhysicalDevice PhysicalDeviceSelector::select(DeviceSelectionMode selection) const
{
    auto const selected_devices = select_impl(selection);

    if (selected_devices.size() == 0)
    {
        throw to_exception(PhysicalDeviceError::no_suitable_device);
    }

    return selected_devices.at(0);
}

// Return all devices which are considered suitable - intended for applications which want to let the user pick the
// physical device
std::vector<PhysicalDevice> PhysicalDeviceSelector::select_devices(DeviceSelectionMode selection) const
{
    auto const selected_devices = select_impl(selection);
    if (selected_devices.size() == 0)
    {
        throw to_exception(PhysicalDeviceError::no_suitable_device);
    }
    return selected_devices;
}

std::vector<std::string> PhysicalDeviceSelector::select_device_names(DeviceSelectionMode selection) const
{
    auto const selected_devices = select_impl(selection);
    if (selected_devices.size() == 0)
    {
        throw to_exception(PhysicalDeviceError::no_suitable_device);
    }
    std::vector<std::string> names;
    for (const auto& pd : selected_devices)
    {
        names.push_back(pd.name);
    }
    return names;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::set_surface(VkSurfaceKHR surface)
{
    instance_info.surface = surface;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::set_name(std::string const& name)
{
    criteria.name = name;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::prefer_gpu_device_type(PreferredDeviceType type)
{
    criteria.preferred_type = type;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::allow_any_gpu_device_type(bool allow_any_type)
{
    criteria.allow_any_type = allow_any_type;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::require_present(bool require)
{
    criteria.require_present = require;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::require_dedicated_transfer_queue()
{
    criteria.require_dedicated_transfer_queue = true;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::require_dedicated_compute_queue()
{
    criteria.require_dedicated_compute_queue = true;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::require_separate_transfer_queue()
{
    criteria.require_separate_transfer_queue = true;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::require_separate_compute_queue()
{
    criteria.require_separate_compute_queue = true;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::required_device_memory_size(VkDeviceSize size)
{
    criteria.required_mem_size = size;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::desired_device_memory_size(VkDeviceSize size)
{
    criteria.desired_mem_size = size;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::add_required_extension(const char* extension)
{
    criteria.required_extensions.push_back(extension);
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::add_required_extensions(std::vector<const char*> const& extensions)
{
    for (const auto& ext : extensions)
    {
        criteria.required_extensions.push_back(ext);
    }
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::add_required_extensions(size_t count, const char* const* extensions)
{
    if (!extensions || count == 0)
        return *this;
    for (size_t i = 0; i < count; i++)
    {
        criteria.required_extensions.push_back(extensions[i]);
    }
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::add_desired_extension(const char* extension)
{
    criteria.desired_extensions.push_back(extension);
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::add_desired_extensions(const std::vector<const char*>& extensions)
{
    for (const auto& ext : extensions)
    {
        criteria.desired_extensions.push_back(ext);
    }
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::set_minimum_version(uint32_t major, uint32_t minor)
{
    criteria.required_version = VKB_MAKE_VK_VERSION(0, major, minor, 0);
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::set_desired_version(uint32_t major, uint32_t minor)
{
    criteria.desired_version = VKB_MAKE_VK_VERSION(0, major, minor, 0);
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::disable_portability_subset()
{
    criteria.enable_portability_subset = false;
    return *this;
}

PhysicalDeviceSelector& PhysicalDeviceSelector::set_required_features(VkPhysicalDeviceFeatures const& features)
{
    detail::combine_features(criteria.required_features, features);
    return *this;
}
#if defined(VKB_VK_API_VERSION_1_2)
// The implementation of the set_required_features_1X functions sets the sType manually. This was a poor choice since
// users of Vulkan should expect to fill out their structs properly. To make the functions take the struct parameter by
// const reference, a local copy must be made in order to set the sType.
PhysicalDeviceSelector&
PhysicalDeviceSelector::set_required_features_11(VkPhysicalDeviceVulkan11Features const& features_11)
{
    VkPhysicalDeviceVulkan11Features features_11_copy = features_11;
    features_11_copy.sType                            = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
    add_required_extension_features(features_11_copy);
    return *this;
}
PhysicalDeviceSelector&
PhysicalDeviceSelector::set_required_features_12(VkPhysicalDeviceVulkan12Features const& features_12)
{
    VkPhysicalDeviceVulkan12Features features_12_copy = features_12;
    features_12_copy.sType                            = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
    add_required_extension_features(features_12_copy);
    return *this;
}
#endif
#if defined(VKB_VK_API_VERSION_1_3)
PhysicalDeviceSelector&
PhysicalDeviceSelector::set_required_features_13(VkPhysicalDeviceVulkan13Features const& features_13)
{
    VkPhysicalDeviceVulkan13Features features_13_copy = features_13;
    features_13_copy.sType                            = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
    add_required_extension_features(features_13_copy);
    return *this;
}
#endif
PhysicalDeviceSelector& PhysicalDeviceSelector::defer_surface_initialization()
{
    criteria.defer_surface_initialization = true;
    return *this;
}
PhysicalDeviceSelector& PhysicalDeviceSelector::select_first_device_unconditionally(bool unconditionally)
{
    criteria.use_first_gpu_unconditionally = unconditionally;
    return *this;
}

// PhysicalDevice
bool PhysicalDevice::has_dedicated_compute_queue() const
{
    return detail::get_dedicated_queue_index(queue_families, VK_QUEUE_COMPUTE_BIT, VK_QUEUE_TRANSFER_BIT).has_value();
}
bool PhysicalDevice::has_separate_compute_queue() const
{
    return detail::get_separate_queue_index(queue_families, VK_QUEUE_COMPUTE_BIT, VK_QUEUE_TRANSFER_BIT).has_value();
}
bool PhysicalDevice::has_dedicated_transfer_queue() const
{
    return detail::get_dedicated_queue_index(queue_families, VK_QUEUE_TRANSFER_BIT, VK_QUEUE_COMPUTE_BIT).has_value();
}
bool PhysicalDevice::has_separate_transfer_queue() const
{
    return detail::get_separate_queue_index(queue_families, VK_QUEUE_TRANSFER_BIT, VK_QUEUE_COMPUTE_BIT).has_value();
}
std::vector<VkQueueFamilyProperties> PhysicalDevice::get_queue_families() const
{
    return queue_families;
}
std::vector<std::string> PhysicalDevice::get_extensions() const
{
    return extensions_to_enable;
}
std::vector<std::string> PhysicalDevice::get_available_extensions() const
{
    return available_extensions;
}
bool PhysicalDevice::is_extension_present(const char* ext) const
{
    return std::find_if(std::begin(available_extensions),
                        std::end(available_extensions),
                        [ext](std::string const& ext_name) { return ext_name == ext; }) !=
           std::end(available_extensions);
}
bool PhysicalDevice::enable_extension_if_present(const char* extension)
{
    auto it = std::find_if(std::begin(available_extensions),
                           std::end(available_extensions),
                           [extension](std::string const& ext_name) { return ext_name == extension; });
    if (it != std::end(available_extensions))
    {
        extensions_to_enable.push_back(extension);
        return true;
    }
    return false;
}
bool PhysicalDevice::enable_extensions_if_present(const std::vector<const char*>& extensions)
{
    for (const auto extension : extensions)
    {
        auto it = std::find_if(std::begin(available_extensions),
                               std::end(available_extensions),
                               [extension](std::string const& ext_name) { return ext_name == extension; });
        if (it == std::end(available_extensions))
            return false;
    }
    for (const auto extension : extensions) extensions_to_enable.push_back(extension);
    return true;
}

bool PhysicalDevice::enable_features_if_present(const VkPhysicalDeviceFeatures& features_to_enable)
{
    VkPhysicalDeviceFeatures actual_pdf{};
    detail::get_instance_table().inst_table.GetPhysicalDeviceFeatures(physical_device, &actual_pdf);

    bool required_features_supported = detail::supports_features(actual_pdf, features_to_enable, {}, {});
    if (required_features_supported)
    {
        detail::combine_features(features, features_to_enable);
    }
    return required_features_supported;
}

bool PhysicalDevice::is_features_node_present(detail::GenericFeaturesPNextNode const& node) const
{
    detail::GenericFeatureChain requested_features;
    requested_features.nodes.push_back(node);

    return extended_features_chain.find_and_match(requested_features);
}

bool PhysicalDevice::enable_features_node_if_present(detail::GenericFeaturesPNextNode const& node)
{
    VkPhysicalDeviceFeatures2 actual_pdf2{};

    detail::GenericFeatureChain requested_features;
    requested_features.nodes.push_back(node);

    detail::GenericFeatureChain fill_chain = requested_features;
    // Zero out supported features
    memset(fill_chain.nodes.front().fields,
           UINT8_MAX,
           sizeof(VkBool32) * detail::GenericFeaturesPNextNode::field_capacity);

    actual_pdf2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    fill_chain.chain_up(actual_pdf2);

    bool required_features_supported = false;
    bool instance_is_1_1             = instance_version >= VKB_VK_API_VERSION_1_1;
    if (instance_is_1_1 || properties2_ext_enabled)
    {
        if (instance_is_1_1)
        {
            detail::get_instance_table().inst_table.GetPhysicalDeviceFeatures2(physical_device, &actual_pdf2);
        }
        else
        {
            detail::get_instance_table().inst_table.GetPhysicalDeviceFeatures2KHR(physical_device, &actual_pdf2);
        }
        required_features_supported = fill_chain.match_all(requested_features);
        if (required_features_supported)
        {
            extended_features_chain.combine(requested_features);
        }
    }
    return required_features_supported;
}

PhysicalDevice::operator VkPhysicalDevice() const
{
    return physical_device;
}

// ---- Queues ---- //

std::optional<uint32_t> Device::get_queue_index(QueueType type) const
{
    switch (type)
    {
        case QueueType::present:
            return detail::get_present_queue_index(physical_device.physical_device, surface, queue_families);
            break;
        case QueueType::graphics:
            return detail::get_first_queue_index(queue_families, VK_QUEUE_GRAPHICS_BIT);
        case QueueType::compute:
            return detail::get_separate_queue_index(queue_families, VK_QUEUE_COMPUTE_BIT, VK_QUEUE_TRANSFER_BIT);
        case QueueType::transfer:
            return detail::get_separate_queue_index(queue_families, VK_QUEUE_TRANSFER_BIT, VK_QUEUE_COMPUTE_BIT);
        default:
            return {};
    }
}

std::optional<uint32_t> Device::get_dedicated_queue_index(QueueType type) const
{
    switch (type)
    {
        case QueueType::compute:
            return detail::get_dedicated_queue_index(queue_families, VK_QUEUE_COMPUTE_BIT, VK_QUEUE_TRANSFER_BIT);
        case QueueType::transfer:
            return detail::get_dedicated_queue_index(queue_families, VK_QUEUE_TRANSFER_BIT, VK_QUEUE_COMPUTE_BIT);
        default:
            return {};
    }
}

std::optional<VkQueue> Device::get_queue(QueueType type) const
{
    auto index = get_queue_index(type);
    if (!index.has_value())
        return {};
    VkQueue out_queue;
    internal_table.fp_vkGetDeviceQueue(device, *index, 0, &out_queue);
    return out_queue;
}

std::optional<VkQueue> Device::get_dedicated_queue(QueueType type) const
{
    auto index = get_dedicated_queue_index(type);
    if (!index.has_value())
        return {};
    VkQueue out_queue;
    internal_table.fp_vkGetDeviceQueue(device, *index, 0, &out_queue);
    return out_queue;
}

// ---- Dispatch ---- //

vkb::DispatchTable Device::make_table() const
{
    return { device, fp_vkGetDeviceProcAddr };
}

// ---- Device ---- //

Device::operator VkDevice() const
{
    return device;
}

CustomQueueDescription::CustomQueueDescription(uint32_t index, std::vector<float> priorities) :
    index(index), priorities(std::move(priorities))
{}

void destroy_device(Device const& device)
{
    device.internal_table.fp_vkDestroyDevice(device.device, device.allocation_callbacks);
}

DeviceBuilder::DeviceBuilder(PhysicalDevice phys_device)
{
    physical_device = std::move(phys_device);
}

Device DeviceBuilder::build() const
{
    std::vector<CustomQueueDescription> queue_descriptions;
    queue_descriptions.insert(queue_descriptions.end(), info.queue_descriptions.begin(), info.queue_descriptions.end());

    if (queue_descriptions.empty())
    {
        for (uint32_t i = 0; i < physical_device.queue_families.size(); i++)
        {
            queue_descriptions.emplace_back(i, std::vector<float>{ 1.0f });
        }
    }

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    for (auto& desc : queue_descriptions)
    {
        VkDeviceQueueCreateInfo queue_create_info = {};
        queue_create_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueFamilyIndex        = desc.index;
        queue_create_info.queueCount              = static_cast<std::uint32_t>(desc.priorities.size());
        queue_create_info.pQueuePriorities        = desc.priorities.data();
        queueCreateInfos.push_back(queue_create_info);
    }

    std::vector<const char*> extensions_to_enable;
    for (const auto& ext : physical_device.extensions_to_enable)
    {
        extensions_to_enable.push_back(ext.c_str());
    }
    if (physical_device.surface != VK_NULL_HANDLE || physical_device.defer_surface_initialization)
        extensions_to_enable.push_back({ VK_KHR_SWAPCHAIN_EXTENSION_NAME });

    std::vector<VkBaseOutStructure*> final_pnext_chain;
    VkDeviceCreateInfo               device_create_info = {};

    bool user_defined_phys_dev_features_2 = false;
    for (auto& pnext : info.pNext_chain)
    {
        if (pnext->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2)
        {
            user_defined_phys_dev_features_2 = true;
            break;
        }
    }

    if (user_defined_phys_dev_features_2 && !physical_device.extended_features_chain.nodes.empty())
    {
        throw to_exception(
            DeviceError::VkPhysicalDeviceFeatures2_in_pNext_chain_while_using_add_required_extension_features);
    }

    // These objects must be alive during the call to vkCreateDevice
    auto                      physical_device_extension_features_copy = physical_device.extended_features_chain;
    VkPhysicalDeviceFeatures2 local_features2{};
    local_features2.sType    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    local_features2.features = physical_device.features;

    if (!user_defined_phys_dev_features_2)
    {
        if (physical_device.instance_version >= VKB_VK_API_VERSION_1_1 || physical_device.properties2_ext_enabled)
        {
            final_pnext_chain.push_back(reinterpret_cast<VkBaseOutStructure*>(&local_features2));
            for (auto& features_node : physical_device_extension_features_copy.nodes)
            {
                final_pnext_chain.push_back(reinterpret_cast<VkBaseOutStructure*>(&features_node));
            }
        }
        else
        {
            // Only set device_create_info.pEnabledFeatures when the pNext chain does not contain a
            // VkPhysicalDeviceFeatures2 structure
            device_create_info.pEnabledFeatures = &physical_device.features;
        }
    }

    for (auto& pnext : info.pNext_chain)
    {
        final_pnext_chain.push_back(pnext);
    }

    detail::setup_pNext_chain(device_create_info, final_pnext_chain);
#if !defined(NDEBUG)
    for (auto& node : final_pnext_chain)
    {
        assert(node->sType != VK_STRUCTURE_TYPE_APPLICATION_INFO);
    }
#endif
    device_create_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.flags                   = info.flags;
    device_create_info.queueCreateInfoCount    = static_cast<uint32_t>(queueCreateInfos.size());
    device_create_info.pQueueCreateInfos       = queueCreateInfos.data();
    device_create_info.enabledExtensionCount   = static_cast<uint32_t>(extensions_to_enable.size());
    device_create_info.ppEnabledExtensionNames = extensions_to_enable.data();

    Device device;

    VkResult res = detail::get_instance_table().fp_vkCreateDevice(
        physical_device.physical_device, &device_create_info, info.allocation_callbacks, &device.device);
    if (res != VK_SUCCESS)
    {
        throw to_exception(DeviceError::failed_create_device, res);
    }

    device.physical_device        = physical_device;
    device.surface                = physical_device.surface;
    device.queue_families         = physical_device.queue_families;
    device.allocation_callbacks   = info.allocation_callbacks;
    device.fp_vkGetDeviceProcAddr = detail::get_instance_table().fp_vkGetDeviceProcAddr;
    detail::get_instance_table().get_device_proc_addr(
        device.device, device.internal_table.fp_vkGetDeviceQueue, "vkGetDeviceQueue");
    detail::get_instance_table().get_device_proc_addr(
        device.device, device.internal_table.fp_vkDestroyDevice, "vkDestroyDevice");
    device.instance_version = physical_device.instance_version;
    return device;
}

DeviceBuilder& DeviceBuilder::custom_queue_setup(std::vector<CustomQueueDescription> queue_descriptions)
{
    info.queue_descriptions = std::move(queue_descriptions);
    return *this;
}

DeviceBuilder& DeviceBuilder::set_allocation_callbacks(VkAllocationCallbacks* callbacks)
{
    info.allocation_callbacks = callbacks;
    return *this;
}

// ---- Swapchain ---- //

GFXRECON_BEGIN_NAMESPACE(detail)

struct SurfaceSupportDetails
{
    VkSurfaceCapabilitiesKHR        capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR>   present_modes;
};

enum class SurfaceSupportError
{
    surface_handle_null,
    failed_get_surface_capabilities,
    failed_enumerate_surface_formats,
    failed_enumerate_present_modes,
    no_suitable_desired_format
};

const char* to_string(SurfaceSupportError err)
{
    switch (err)
    {
        CASE_TO_STRING(SurfaceSupportError, surface_handle_null)
        CASE_TO_STRING(SurfaceSupportError, failed_get_surface_capabilities)
        CASE_TO_STRING(SurfaceSupportError, failed_enumerate_surface_formats)
        CASE_TO_STRING(SurfaceSupportError, failed_enumerate_present_modes)
        CASE_TO_STRING(SurfaceSupportError, no_suitable_desired_format)
        default:
            return "";
    }
}

std::runtime_error to_exception(SurfaceSupportError error)
{
    return std::runtime_error(to_string(error));
}
std::runtime_error to_exception(SurfaceSupportError error, VkResult result)
{
    std::string message{};
    message.append(to_string(error));
    message.append(": ");
    message.append(string_VkResult(result));
    return std::runtime_error(message);
}

SurfaceSupportDetails query_surface_support_details(VkPhysicalDevice phys_device, VkSurfaceKHR surface)
{
    if (surface == VK_NULL_HANDLE)
        throw to_exception(SurfaceSupportError::surface_handle_null);

    VkSurfaceCapabilitiesKHR capabilities;
    VkResult                 res = detail::get_instance_table().inst_table.GetPhysicalDeviceSurfaceCapabilitiesKHR(
        phys_device, surface, &capabilities);
    if (res != VK_SUCCESS)
    {
        throw to_exception(SurfaceSupportError::failed_get_surface_capabilities, res);
    }

    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR>   present_modes;

    auto formats_ret = detail::get_vector<VkSurfaceFormatKHR>(
        formats, detail::get_instance_table().inst_table.GetPhysicalDeviceSurfaceFormatsKHR, phys_device, surface);
    if (formats_ret != VK_SUCCESS)
        throw to_exception(SurfaceSupportError::failed_enumerate_surface_formats, formats_ret);
    auto present_modes_ret = detail::get_vector<VkPresentModeKHR>(
        present_modes,
        detail::get_instance_table().inst_table.GetPhysicalDeviceSurfacePresentModesKHR,
        phys_device,
        surface);
    if (present_modes_ret != VK_SUCCESS)
        throw to_exception(SurfaceSupportError::failed_enumerate_present_modes, present_modes_ret);

    return SurfaceSupportDetails{ capabilities, formats, present_modes };
}

std::optional<VkSurfaceFormatKHR> find_desired_surface_format(std::vector<VkSurfaceFormatKHR> const& available_formats,
                                                              std::vector<VkSurfaceFormatKHR> const& desired_formats)
{
    for (auto const& desired_format : desired_formats)
    {
        for (auto const& available_format : available_formats)
        {
            // finds the first format that is desired and available
            if (desired_format.format == available_format.format &&
                desired_format.colorSpace == available_format.colorSpace)
            {
                return desired_format;
            }
        }
    }

    return {};
}

VkSurfaceFormatKHR find_best_surface_format(std::vector<VkSurfaceFormatKHR> const& available_formats,
                                            std::vector<VkSurfaceFormatKHR> const& desired_formats)
{
    auto surface_format_ret = detail::find_desired_surface_format(available_formats, desired_formats);
    return surface_format_ret.value_or(available_formats[0]);
}

VkPresentModeKHR find_present_mode(std::vector<VkPresentModeKHR> const& available_resent_modes,
                                   std::vector<VkPresentModeKHR> const& desired_present_modes)
{
    for (auto const& desired_pm : desired_present_modes)
    {
        for (auto const& available_pm : available_resent_modes)
        {
            // finds the first present mode that is desired and available
            if (desired_pm == available_pm)
                return desired_pm;
        }
    }
    // only present mode required, use as a fallback
    return VK_PRESENT_MODE_FIFO_KHR;
}

template <typename T>
T minimum(T a, T b)
{
    return a < b ? a : b;
}
template <typename T>
T maximum(T a, T b)
{
    return a > b ? a : b;
}

VkExtent2D find_extent(VkSurfaceCapabilitiesKHR const& capabilities, uint32_t desired_width, uint32_t desired_height)
{
    if (capabilities.currentExtent.width != UINT32_MAX)
    {
        return capabilities.currentExtent;
    }
    else
    {
        VkExtent2D actualExtent = { desired_width, desired_height };

        actualExtent.width =
            maximum(capabilities.minImageExtent.width, minimum(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = maximum(capabilities.minImageExtent.height,
                                      minimum(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

GFXRECON_END_NAMESPACE(detail)

void destroy_swapchain(Swapchain const& swapchain)
{
    if (swapchain.device != VK_NULL_HANDLE && swapchain.swapchain != VK_NULL_HANDLE)
    {
        swapchain.internal_table.fp_vkDestroySwapchainKHR(
            swapchain.device, swapchain.swapchain, swapchain.allocation_callbacks);
    }
}

SwapchainBuilder::SwapchainBuilder(Device const& device)
{
    info.physical_device  = device.physical_device.physical_device;
    info.device           = device.device;
    info.surface          = device.surface;
    info.instance_version = device.instance_version;
    auto present          = device.get_queue_index(QueueType::present);
    auto graphics         = device.get_queue_index(QueueType::graphics);
    assert(graphics.has_value() && present.has_value() && "Graphics and Present queue indexes must be valid");
    info.graphics_queue_index = *present;
    info.present_queue_index  = *graphics;
    info.allocation_callbacks = device.allocation_callbacks;
}

SwapchainBuilder::SwapchainBuilder(Device const& device, VkSurfaceKHR const surface)
{
    info.physical_device  = device.physical_device.physical_device;
    info.device           = device.device;
    info.surface          = surface;
    info.instance_version = device.instance_version;
    Device temp_device    = device;
    temp_device.surface   = surface;
    auto present          = temp_device.get_queue_index(QueueType::present);
    auto graphics         = temp_device.get_queue_index(QueueType::graphics);
    assert(graphics.has_value() && present.has_value() && "Graphics and Present queue indexes must be valid");
    info.graphics_queue_index = *graphics;
    info.present_queue_index  = *present;
    info.allocation_callbacks = device.allocation_callbacks;
}
SwapchainBuilder::SwapchainBuilder(VkPhysicalDevice const  physical_device,
                                   VkDevice const          device,
                                   VkSurfaceKHR const      surface,
                                   std::optional<uint32_t> graphics_queue_index,
                                   std::optional<uint32_t> present_queue_index)
{
    info.physical_device      = physical_device;
    info.device               = device;
    info.surface              = surface;
    info.graphics_queue_index = graphics_queue_index;
    info.present_queue_index  = present_queue_index;
    if (!graphics_queue_index.has_value() || !present_queue_index.has_value())
    {
        auto queue_families = detail::get_vector_noerror<VkQueueFamilyProperties>(
            detail::get_instance_table().inst_table.GetPhysicalDeviceQueueFamilyProperties, physical_device);
        if (!graphics_queue_index.has_value())
            info.graphics_queue_index = detail::get_first_queue_index(queue_families, VK_QUEUE_GRAPHICS_BIT);
        if (!present_queue_index.has_value())
            info.present_queue_index = detail::get_present_queue_index(physical_device, surface, queue_families);
    }
}
Swapchain SwapchainBuilder::build() const
{
    if (info.surface == VK_NULL_HANDLE)
    {
        throw to_exception(SwapchainError::surface_handle_not_provided);
    }

    auto desired_formats = info.desired_formats;
    if (desired_formats.size() == 0)
        add_desired_formats(desired_formats);
    auto desired_present_modes = info.desired_present_modes;
    if (desired_present_modes.size() == 0)
        add_desired_present_modes(desired_present_modes);

    auto surface_support = detail::query_surface_support_details(info.physical_device, info.surface);

    uint32_t image_count = info.min_image_count;
    if (info.required_min_image_count >= 1)
    {
        if (info.required_min_image_count < surface_support.capabilities.minImageCount)
            throw to_exception(SwapchainError::required_min_image_count_too_low);

        image_count = info.required_min_image_count;
    }
    else if (info.min_image_count == 0)
    {
        // We intentionally use minImageCount + 1 to maintain existing behavior, even if it typically results in triple
        // buffering on most systems.
        image_count = surface_support.capabilities.minImageCount + 1;
    }
    else
    {
        image_count = info.min_image_count;
        if (image_count < surface_support.capabilities.minImageCount)
            image_count = surface_support.capabilities.minImageCount;
    }
    if (surface_support.capabilities.maxImageCount > 0 && image_count > surface_support.capabilities.maxImageCount)
    {
        image_count = surface_support.capabilities.maxImageCount;
    }

    VkSurfaceFormatKHR surface_format = detail::find_best_surface_format(surface_support.formats, desired_formats);

    VkExtent2D extent = detail::find_extent(surface_support.capabilities, info.desired_width, info.desired_height);

    uint32_t image_array_layers = info.array_layer_count;
    if (surface_support.capabilities.maxImageArrayLayers < info.array_layer_count)
        image_array_layers = surface_support.capabilities.maxImageArrayLayers;
    if (info.array_layer_count == 0)
        image_array_layers = 1;

    uint32_t queue_family_indices[] = { *info.graphics_queue_index, *info.present_queue_index };

    VkPresentModeKHR present_mode = detail::find_present_mode(surface_support.present_modes, desired_present_modes);

    // VkSurfaceCapabilitiesKHR::supportedUsageFlags is only only valid for some present modes. For shared present
    // modes, we should also check VkSharedPresentSurfaceCapabilitiesKHR::sharedPresentSupportedUsageFlags.
    auto is_unextended_present_mode = [](VkPresentModeKHR present_mode) {
        return (present_mode == VK_PRESENT_MODE_IMMEDIATE_KHR) || (present_mode == VK_PRESENT_MODE_MAILBOX_KHR) ||
               (present_mode == VK_PRESENT_MODE_FIFO_KHR) || (present_mode == VK_PRESENT_MODE_FIFO_RELAXED_KHR);
    };

    if (is_unextended_present_mode(present_mode) &&
        (info.image_usage_flags & surface_support.capabilities.supportedUsageFlags) != info.image_usage_flags)
    {
        throw to_exception(SwapchainError::required_usage_not_supported);
    }

    VkSurfaceTransformFlagBitsKHR pre_transform = info.pre_transform;
    if (info.pre_transform == static_cast<VkSurfaceTransformFlagBitsKHR>(0))
        pre_transform = surface_support.capabilities.currentTransform;

    VkSwapchainCreateInfoKHR swapchain_create_info = {};
    swapchain_create_info.sType                    = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    detail::setup_pNext_chain(swapchain_create_info, info.pNext_chain);
#if !defined(NDEBUG)
    for (auto& node : info.pNext_chain)
    {
        assert(node->sType != VK_STRUCTURE_TYPE_APPLICATION_INFO);
    }
#endif
    swapchain_create_info.flags            = info.create_flags;
    swapchain_create_info.surface          = info.surface;
    swapchain_create_info.minImageCount    = image_count;
    swapchain_create_info.imageFormat      = surface_format.format;
    swapchain_create_info.imageColorSpace  = surface_format.colorSpace;
    swapchain_create_info.imageExtent      = extent;
    swapchain_create_info.imageArrayLayers = image_array_layers;
    swapchain_create_info.imageUsage       = info.image_usage_flags;

    if (info.graphics_queue_index != info.present_queue_index)
    {
        swapchain_create_info.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
        swapchain_create_info.queueFamilyIndexCount = 2;
        swapchain_create_info.pQueueFamilyIndices   = queue_family_indices;
    }
    else
    {
        swapchain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    swapchain_create_info.preTransform   = pre_transform;
    swapchain_create_info.compositeAlpha = info.composite_alpha;
    swapchain_create_info.presentMode    = present_mode;
    swapchain_create_info.clipped        = info.clipped;
    swapchain_create_info.oldSwapchain   = info.old_swapchain;
    Swapchain                swapchain{};
    PFN_vkCreateSwapchainKHR swapchain_create_proc;
    detail::get_instance_table().get_device_proc_addr(info.device, swapchain_create_proc, "vkCreateSwapchainKHR");
    auto res =
        swapchain_create_proc(info.device, &swapchain_create_info, info.allocation_callbacks, &swapchain.swapchain);

    if (res != VK_SUCCESS)
    {
        throw to_exception(SwapchainError::failed_create_swapchain, res);
    }
    swapchain.device            = info.device;
    swapchain.image_format      = surface_format.format;
    swapchain.color_space       = surface_format.colorSpace;
    swapchain.image_usage_flags = info.image_usage_flags;
    swapchain.extent            = extent;
    detail::get_instance_table().get_device_proc_addr(
        info.device, swapchain.internal_table.fp_vkGetSwapchainImagesKHR, "vkGetSwapchainImagesKHR");
    detail::get_instance_table().get_device_proc_addr(
        info.device, swapchain.internal_table.fp_vkCreateImageView, "vkCreateImageView");
    detail::get_instance_table().get_device_proc_addr(
        info.device, swapchain.internal_table.fp_vkDestroyImageView, "vkDestroyImageView");
    detail::get_instance_table().get_device_proc_addr(
        info.device, swapchain.internal_table.fp_vkDestroySwapchainKHR, "vkDestroySwapchainKHR");
    auto images                         = swapchain.get_images();
    swapchain.requested_min_image_count = image_count;
    swapchain.present_mode              = present_mode;
    swapchain.image_count               = static_cast<uint32_t>(images.size());
    swapchain.instance_version          = info.instance_version;
    swapchain.allocation_callbacks      = info.allocation_callbacks;
    return swapchain;
}
std::vector<VkImage> Swapchain::get_images()
{
    std::vector<VkImage> swapchain_images;

    auto swapchain_images_ret =
        detail::get_vector<VkImage>(swapchain_images, internal_table.fp_vkGetSwapchainImagesKHR, device, swapchain);
    if (swapchain_images_ret != VK_SUCCESS)
    {
        throw to_exception(SwapchainError::failed_get_swapchain_images, swapchain_images_ret);
    }
    return swapchain_images;
}
std::vector<VkImageView> Swapchain::get_image_views()
{
    return get_image_views(nullptr);
}
std::vector<VkImageView> Swapchain::get_image_views(const void* pNext)
{
    const auto swapchain_images = get_images();

    bool already_contains_image_view_usage = false;
    while (pNext)
    {
        if (reinterpret_cast<const VkBaseInStructure*>(pNext)->sType == VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO)
        {
            already_contains_image_view_usage = true;
            break;
        }
        pNext = reinterpret_cast<const VkBaseInStructure*>(pNext)->pNext;
    }
    VkImageViewUsageCreateInfo desired_flags{};
    desired_flags.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO;
    desired_flags.pNext = pNext;
    desired_flags.usage = image_usage_flags;

    std::vector<VkImageView> views(swapchain_images.size());
    for (size_t i = 0; i < swapchain_images.size(); i++)
    {
        VkImageViewCreateInfo createInfo = {};
        createInfo.sType                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        if (instance_version >= VKB_VK_API_VERSION_1_1 && !already_contains_image_view_usage)
        {
            createInfo.pNext = &desired_flags;
        }
        else
        {
            createInfo.pNext = pNext;
        }

        createInfo.image                           = swapchain_images[i];
        createInfo.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format                          = image_format;
        createInfo.components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel   = 0;
        createInfo.subresourceRange.levelCount     = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount     = 1;
        VkResult res = internal_table.fp_vkCreateImageView(device, &createInfo, allocation_callbacks, &views[i]);
        if (res != VK_SUCCESS)
            throw to_exception(SwapchainError::failed_create_swapchain_image_views, res);
    }
    return views;
}
void Swapchain::destroy_image_views(std::vector<VkImageView> const& image_views)
{
    for (auto& image_view : image_views)
    {
        internal_table.fp_vkDestroyImageView(device, image_view, allocation_callbacks);
    }
}
Swapchain::operator VkSwapchainKHR() const
{
    return swapchain;
}
SwapchainBuilder& SwapchainBuilder::set_old_swapchain(VkSwapchainKHR old_swapchain)
{
    info.old_swapchain = old_swapchain;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_old_swapchain(Swapchain const& swapchain)
{
    info.old_swapchain = swapchain.swapchain;
    return *this;
}
bool SwapchainBuilder::get_destroy_old_swapchain() const
{
    return info.destroy_old_swapchain;
}
SwapchainBuilder& SwapchainBuilder::set_destroy_old_swapchain(bool destroy)
{
    info.destroy_old_swapchain = destroy;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_desired_extent(uint32_t width, uint32_t height)
{
    info.desired_width  = width;
    info.desired_height = height;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_desired_format(VkSurfaceFormatKHR format)
{
    info.desired_formats.insert(info.desired_formats.begin(), format);
    return *this;
}
SwapchainBuilder& SwapchainBuilder::add_fallback_format(VkSurfaceFormatKHR format)
{
    info.desired_formats.push_back(format);
    return *this;
}
SwapchainBuilder& SwapchainBuilder::use_default_format_selection()
{
    info.desired_formats.clear();
    add_desired_formats(info.desired_formats);
    return *this;
}

SwapchainBuilder& SwapchainBuilder::set_desired_present_mode(VkPresentModeKHR present_mode)
{
    info.desired_present_modes.insert(info.desired_present_modes.begin(), present_mode);
    return *this;
}
SwapchainBuilder& SwapchainBuilder::add_fallback_present_mode(VkPresentModeKHR present_mode)
{
    info.desired_present_modes.push_back(present_mode);
    return *this;
}
SwapchainBuilder& SwapchainBuilder::use_default_present_mode_selection()
{
    info.desired_present_modes.clear();
    add_desired_present_modes(info.desired_present_modes);
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_allocation_callbacks(VkAllocationCallbacks* callbacks)
{
    info.allocation_callbacks = callbacks;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_image_usage_flags(VkImageUsageFlags usage_flags)
{
    info.image_usage_flags = usage_flags;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::add_image_usage_flags(VkImageUsageFlags usage_flags)
{
    info.image_usage_flags = info.image_usage_flags | usage_flags;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::use_default_image_usage_flags()
{
    info.image_usage_flags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_image_array_layer_count(uint32_t array_layer_count)
{
    info.array_layer_count = array_layer_count;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_desired_min_image_count(uint32_t min_image_count)
{
    info.min_image_count = min_image_count;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_required_min_image_count(uint32_t required_min_image_count)
{
    info.required_min_image_count = required_min_image_count;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_clipped(bool clipped)
{
    info.clipped = clipped;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_create_flags(VkSwapchainCreateFlagBitsKHR create_flags)
{
    info.create_flags = create_flags;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_pre_transform_flags(VkSurfaceTransformFlagBitsKHR pre_transform_flags)
{
    info.pre_transform = pre_transform_flags;
    return *this;
}
SwapchainBuilder& SwapchainBuilder::set_composite_alpha_flags(VkCompositeAlphaFlagBitsKHR composite_alpha_flags)
{
    info.composite_alpha = composite_alpha_flags;
    return *this;
}

void SwapchainBuilder::add_desired_formats(std::vector<VkSurfaceFormatKHR>& formats) const
{
    formats.push_back({ VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR });
    formats.push_back({ VK_FORMAT_R8G8B8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR });
}
void SwapchainBuilder::add_desired_present_modes(std::vector<VkPresentModeKHR>& modes) const
{
    modes.push_back(VK_PRESENT_MODE_MAILBOX_KHR);
    modes.push_back(VK_PRESENT_MODE_FIFO_KHR);
}

#ifdef __ANDROID__
VkSurfaceKHR create_surface_android(VkInstance instance, vkb::InstanceDispatchTable const& dispatch, android_app* app)
{
    VkAndroidSurfaceCreateInfoKHR info{};
    info.sType  = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    info.window = app->window;
    VkSurfaceKHR surface;
    assert(dispatch.fp_vkCreateAndroidSurfaceKHR);
    auto fpCreateAndroidSurfaceKHR =
        reinterpret_cast<PFN_vkCreateAndroidSurfaceKHR>(dispatch.fp_vkCreateAndroidSurfaceKHR);
    auto result = fpCreateAndroidSurfaceKHR(instance, &info, nullptr, &surface);
    VERIFY_VK_RESULT("failed to create android surface", result);
    return surface;
}
#else
decode::WindowFactory* create_window_factory(application::Application& app)
{
    // auto select WSI extension
    auto wsi_context = app.GetWsiContext("", true);
    GFXRECON_ASSERT(wsi_context);
    auto window_factory = wsi_context->GetWindowFactory();
    GFXRECON_ASSERT(window_factory);
    return window_factory;
}

VkSurfaceKHR create_surface(InitInfo& init)
{
    VkSurfaceKHR surface    = VK_NULL_HANDLE;
    auto&        inst_table = detail::get_instance_table();
    auto         gpa        = inst_table.ptr_vkGetInstanceProcAddr;
    VkResult     result     = init.window->CreateSurface(&inst_table.inst_table, init.instance, 0, &surface);
    VERIFY_VK_RESULT("failed to create surface", result);
    return surface;
}
#endif

VkSurfaceKHR
create_surface_headless(VkInstance instance, vkb::InstanceDispatchTable& disp, VkAllocationCallbacks* callbacks)
{
    VkSurfaceKHR                   surface = VK_NULL_HANDLE;
    VkHeadlessSurfaceCreateInfoEXT create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT;
    VERIFY_VK_RESULT("failed to create headless surface",
                     disp.createHeadlessSurfaceEXT(&create_info, callbacks, &surface));
    return surface;
}

void create_swapchain(SwapchainBuilder& swapchain_builder, Swapchain& swapchain)
{
    auto new_swapchain = swapchain_builder.set_old_swapchain(swapchain).build();
    if (swapchain_builder.get_destroy_old_swapchain())
    {
        destroy_swapchain(swapchain);
    }
    swapchain = new_swapchain;
}

VkCommandPool create_command_pool(vkb::DispatchTable const& disp, uint32_t queue_family_index)
{
    VkCommandPoolCreateInfo pool_info = {};
    pool_info.sType                   = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.queueFamilyIndex        = queue_family_index;

    VkCommandPool command_pool;
    auto          result = disp.createCommandPool(&pool_info, nullptr, &command_pool);
    VERIFY_VK_RESULT("failed to create command pool", result);
    return command_pool;
}

Sync create_sync_objects(Swapchain const& swapchain, vkb::DispatchTable const& disp, const int max_frames_in_flight)
{
    Sync sync;

    sync.available_semaphores.resize(max_frames_in_flight);
    sync.finished_semaphore.resize(max_frames_in_flight);
    sync.in_flight_fences.resize(max_frames_in_flight);
    sync.image_in_flight.resize(swapchain.image_count, VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphore_info = {};
    semaphore_info.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fence_info = {};
    fence_info.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags             = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < max_frames_in_flight; i++)
    {
        VkResult result;
        result = disp.createSemaphore(&semaphore_info, nullptr, &sync.available_semaphores[i]);
        VERIFY_VK_RESULT("failed to create available semaphore", result);
        result = disp.createSemaphore(&semaphore_info, nullptr, &sync.finished_semaphore[i]);
        VERIFY_VK_RESULT("failed to create finished semaphore", result);
        result = disp.createFence(&fence_info, nullptr, &sync.in_flight_fences[i]);
        VERIFY_VK_RESULT("failed to create in flight fence", result);
    }
    return sync;
}

#ifdef __ANDROID__
std::vector<char> readFile(const std::string& filename, android_app* app)
{
    std::vector<char> data;
    AAsset*           file = AAssetManager_open(app->activity->assetManager, filename.c_str(), AASSET_MODE_BUFFER);
    if (file == nullptr)
    {
        throw std::runtime_error("failed to open file " + filename);
    }
    size_t fileLength = AAsset_getLength(file);
    data.resize(fileLength);
    AAsset_read(file, data.data(), fileLength);
    AAsset_close(file);
    return data;
}
#else
std::vector<char> readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open `" + filename + "`");
    }

    size_t            file_size = (size_t)file.tellg();
    std::vector<char> buffer(file_size);

    file.seekg(0);
    file.read(buffer.data(), static_cast<std::streamsize>(file_size));

    file.close();

    return buffer;
}
#endif

VkShaderModule createShaderModule(vkb::DispatchTable const& disp, const std::vector<char>& code)
{
    VkShaderModuleCreateInfo create_info = {};
    create_info.sType                    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize                 = code.size();
    create_info.pCode                    = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    auto           result = disp.createShaderModule(&create_info, nullptr, &shaderModule);
    VERIFY_VK_RESULT("failed to create shader module", result);

    return shaderModule;
}

#ifdef __ANDROID__
VkShaderModule readShaderFromFile(vkb::DispatchTable const& disp, const std::string& filename, android_app* app)
{
    std::vector<char> code = readFile(filename, app);
    return createShaderModule(disp, code);
}
#else
VkShaderModule readShaderFromFile(vkb::DispatchTable const& disp, const std::string& filename)
{
    std::vector<char> code = readFile(filename);
    return createShaderModule(disp, code);
}
#endif

std::runtime_error vulkan_exception(const char* message, VkResult result)
{
    std::string error_message;
    error_message.append(message);
    error_message.append(": ");
    error_message.append(string_VkResult(result));
    return std::runtime_error(error_message);
}

void device_initialization_phase_1(application::Application& app, InitInfo& init)
{
    if (std::getenv("GFXRECON_TESTAPP_HEADLESS") == nullptr)
    {
#ifdef __ANDROID__
        while (init.android_app->window == nullptr)
        {
            int                         events = 0;
            struct android_poll_source* source = nullptr;
            int result = ALooper_pollAll(-1, nullptr, &events, reinterpret_cast<void**>(&source));
            if (result >= 0 && source)
            {
                source->process(init.android_app, source);
            }
        }
#else
        init.window_factory = create_window_factory(app);
        // By default, the created window will be automatically in full screen mode, and its location will be set to 0,0
        // if the requested size exceeds or equals the current screen size. If the user specifies "--fw" or "--fwo" this
        // behavior will change, and replay will instead render in windowed mode.
        init.window = init.window_factory->Create(0, 0, 1024, 1024);
#endif
    }
}

void device_initialization_phase_2(InstanceBuilder const&    instance_builder,
                                   application::Application& app,
                                   InitInfo&                 init)
{
    init.instance = instance_builder.build();

    init.inst_disp = init.instance.make_table();

    if (!init.instance.is_headless())
    {
        if (std::getenv("GFXRECON_TESTAPP_HEADLESS") == nullptr)
        {
#ifdef __ANDROID__
            init.surface = create_surface_android(init.instance, init.inst_disp, init.android_app);
#else
            init.surface = create_surface(init);
#endif
        }
        else
        {
            init.surface = create_surface_headless(init.instance, init.inst_disp);
        }
    }
}

PhysicalDevice device_initialization_phase_3(PhysicalDeviceSelector& phys_device_selector, InitInfo& init)
{
    return phys_device_selector.set_surface(init.surface).select();
}

void device_initialization_phase_4(DeviceBuilder const& device_builder, InitInfo& init)
{
    init.device = device_builder.build();

    init.disp = init.device.make_table();
}

void device_initialization_phase_5(SwapchainBuilder& swapchain_builder, InitInfo& init)
{
    create_swapchain(swapchain_builder, init.swapchain);

    init.swapchain_images      = init.swapchain.get_images();
    init.swapchain_image_views = init.swapchain.get_image_views();
}

static vkmock::TestConfig* try_load_test_config()
{
    char const* mock_icd_location = std::getenv("GFXRECON_TESTAPP_MOCK_ICD");
    if (mock_icd_location == nullptr)
    {
        return nullptr;
    }
#if defined(__linux__) || defined(__APPLE__)
    auto library = dlopen(mock_icd_location, RTLD_NOW | RTLD_LOCAL);
    if (library == nullptr)
    {
        return nullptr;
    }
    PFN_mockICD_getTestConfig getTestConfig =
        reinterpret_cast<PFN_mockICD_getTestConfig>(dlsym(library, "mockICD_getTestConfig"));
#elif defined(_WIN32)
    auto module = LoadLibrary(TEXT(mock_icd_location));
    if (module == nullptr)
    {
        return nullptr;
    }
    PFN_mockICD_getTestConfig getTestConfig =
        reinterpret_cast<PFN_mockICD_getTestConfig>(GetProcAddress(module, "mockICD_getTestConfig"));
#else
    static_assert(false && "Unsupported platform");
#endif
    if (getTestConfig == nullptr)
    {
        return nullptr;
    }
    return getTestConfig();
}

void cleanup_init(InitInfo& init)
{
    init.swapchain.destroy_image_views(init.swapchain_image_views);

    destroy_swapchain(init.swapchain);
    destroy_device(init.device);
    destroy_surface(init.instance, init.surface);
    destroy_instance(init.instance);
    destroy_window(init.window_factory, init.window);
}

void recreate_init_swapchain(SwapchainBuilder& swapchain_builder, InitInfo& init, bool wait_for_idle)
{
    if (wait_for_idle)
        init.disp.deviceWaitIdle();

    init.swapchain.destroy_image_views(init.swapchain_image_views);

    create_swapchain(swapchain_builder, init.swapchain);

    init.swapchain_images      = init.swapchain.get_images();
    init.swapchain_image_views = init.swapchain.get_image_views();
}

TestAppBase::~TestAppBase() {}

void TestAppBase::run(const std::string& window_name)
{
    device_initialization_phase_1(*app, init);

    init.test_config = try_load_test_config();

    InstanceBuilder instance_builder;
    configure_instance_builder(instance_builder, init.test_config);
    device_initialization_phase_2(instance_builder, *app, init);

    PhysicalDeviceSelector phys_device_selector(init.instance);
    configure_physical_device_selector(phys_device_selector, init.test_config);
    init.physical_device = device_initialization_phase_3(phys_device_selector, init);

    DeviceBuilder device_builder{ init.physical_device };
    configure_device_builder(device_builder, init.physical_device, init.test_config);
    device_initialization_phase_4(device_builder, init);

    if (std::getenv("GFXRECON_TESTAPP_HEADLESS") == nullptr || !init.instance.is_headless())
    {
        SwapchainBuilder swapchain_builder{ init.device };
        configure_swapchain_builder(swapchain_builder, init.test_config);
        device_initialization_phase_5(swapchain_builder, init);
    }

    setup();

    bool running   = true;
    int  frame_num = 0;
    while (running)
    {
        app->ProcessEvents(false);

        running = frame(frame_num);
        ++frame_num;
    }

    init.disp.deviceWaitIdle();

    cleanup();

    cleanup_init(init);
}

void TestAppBase::recreate_swapchain(bool wait_for_idle)
{
    SwapchainBuilder swapchain_builder{ init.device };
    configure_swapchain_builder(swapchain_builder, init.test_config);
    recreate_init_swapchain(swapchain_builder, init, wait_for_idle);
}

void TestAppBase::setup() {}

void TestAppBase::cleanup() {}

void TestAppBase::configure_instance_builder(InstanceBuilder& instance_builder, vkmock::TestConfig* test_config)
{
    instance_builder.use_default_debug_messenger().request_validation_layers();
}

void TestAppBase::configure_physical_device_selector(PhysicalDeviceSelector& phys_device_selector,
                                                     vkmock::TestConfig*     test_config)
{}

void TestAppBase::configure_device_builder(DeviceBuilder&        device_builder,
                                           PhysicalDevice const& physical_device,
                                           vkmock::TestConfig*   test_config)
{}

void TestAppBase::configure_swapchain_builder(SwapchainBuilder& swapchain_builder, vkmock::TestConfig* test_config) {}

uint32_t TestAppBase::find_memory_type(uint32_t memoryTypeBits, VkMemoryPropertyFlags memory_property_flags)
{
    VkPhysicalDeviceMemoryProperties memory_properties;
    init.inst_disp.getPhysicalDeviceMemoryProperties(init.physical_device, &memory_properties);

    for (uint32_t i = 0; i < memory_properties.memoryTypeCount; ++i)
    {
        if ((memoryTypeBits & (1 << i)) && (memory_properties.memoryTypes[i].propertyFlags & memory_property_flags) > 0)
        {
            return i;
            break;
        }
    }

    throw std::runtime_error("failed to find memory type");
}

bool DeviceBuilder::enable_extension_if_present(const char* extension)
{
    return physical_device.enable_extension_if_present(extension);
}

bool DeviceBuilder::enable_extensions_if_present(const std::vector<const char*>& extensions)
{
    return physical_device.enable_extensions_if_present(extensions);
}

bool DeviceBuilder::enable_features_if_present(const VkPhysicalDeviceFeatures& features_to_enable)
{
    return physical_device.enable_features_if_present(features_to_enable);
}

#ifdef __ANDROID__
void TestAppBase::set_android_app(struct android_app* app)
{
    init.android_app = app;
}
#endif

GFXRECON_END_NAMESPACE(test)
GFXRECON_END_NAMESPACE(gfxrecon)
