/*
** Copyright (c) 2018-2021 Valve Corporation
** Copyright (c) 2018-2021 LunarG, Inc.
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

#ifndef GFXRECON_DECODE_VULKAN_OBJECT_MAPPER_BASE_H
#define GFXRECON_DECODE_VULKAN_OBJECT_MAPPER_BASE_H

#include "decode/vulkan_object_info.h"
#include "format/format.h"
#include "util/defines.h"

#include "vulkan/vulkan.h"

#include <cassert>
#include <functional>
#include <type_traits>
#include <unordered_map>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

template <typename T, typename = int>
struct has_handle_future : std::false_type
{};

template <typename T>
struct has_handle_future<T, decltype((void)T::future, 0)>
    : std::is_same<decltype(T::future), std::shared_future<handle_create_result_t<typename T::HandleType>>>
{};

template <typename T>
inline constexpr bool has_handle_future_v = has_handle_future<T>::value;

// NOTE: There's nothing VulkanSpecific in these utilities
// TODO: Find a better home for these

// Utility functors to implement const and non-const versions of getters in a common impl
template <typename Container>
using ConstCorrectMappedTypePtr = decltype(&(std::declval<Container>().begin()->second));

struct ObjectInfoGetterBase
{
    template <typename Map, typename MappedTypePtr>
    MappedTypePtr GetObjectInfoImpl(format::HandleId id, Map* map)
    {
        assert(map != nullptr);

        MappedTypePtr object_info = nullptr;

        if (id != 0)
        {
            const auto entry = map->find(id);

            if (entry != map->end())
            {
                object_info = &entry->second;
            }
        }

        return object_info;
    }
    template <typename Map, typename MappedTypePtr>
    MappedTypePtr GetAliasingObjectInfoImpl(format::HandleId id, Map* map)
    {
        MappedTypePtr object_info = GetObjectInfoImpl<Map, MappedTypePtr>(id, map);
        if (object_info && (object_info->vulkan_alias != format::kNullHandleId))
        {
            object_info = GetObjectInfoImpl<Map, MappedTypePtr>(object_info->vulkan_alias, map);
            // Note: if id has an alias and the alias is valid, the alias must not alias. Aliasing is single level.
            assert(!object_info || (object_info->vulkan_alias == format::kNullHandleId));
        }
        return object_info;
    }
};

// Because of " explicit specialization in non-namespace scope" these must be implemented outside the class below
template <typename T>
struct ObjectInfoGetter : public ObjectInfoGetterBase
{
    template <typename Map, typename MappedTypePtr = ConstCorrectMappedTypePtr<Map>>
    MappedTypePtr operator()(format::HandleId id, Map* map)
    {
        return GetObjectInfoImpl<Map, MappedTypePtr>(id, map);
    }
};

// Specialize to handle physical device aliasing. See comments for VulkanPhysicalDeviceInfo::vulkan_alias
// Note: could do SFINAE a "has member" check on vulkan_alias, but as only physical device needs aliasing support at
//       this time, it's simpler just to specialize for VulkanPhysicalDeviceInfo
template <>
struct ObjectInfoGetter<VulkanPhysicalDeviceInfo> : public ObjectInfoGetterBase
{
    template <typename Map, typename MappedTypePtr = ConstCorrectMappedTypePtr<Map>>
    MappedTypePtr operator()(format::HandleId id, Map* map)
    {
        return GetAliasingObjectInfoImpl<Map, MappedTypePtr>(id, map);
    }
};

class VulkanObjectInfoTableBase
{
  protected:
    template <typename T>
    void AddVkObjectInfo(T&& info, std::unordered_map<format::HandleId, T>* map)
    {
        assert(map != nullptr);

        // either the handle or it's (potentially existing) future need to be valid
        bool valid_handle = info.handle != VK_NULL_HANDLE;
        if constexpr (has_handle_future_v<T>)
        {
            valid_handle = info.handle || info.future.valid();
        }

        if ((info.capture_id != 0) && valid_handle)
        {
            auto result = map->emplace(info.capture_id, std::forward<T>(info));

            if (!result.second)
            {
                // There are two expected cases where a capture ID would already be in the map. The first case is for
                // handles that are retrieved, such as VkPhysicalDevice, which can be processed more than once. For
                // this case we a have a duplicate info structure with the same ID and handle value, and do not need
                // to update the map entry. The existing entry may even contain additional info that would be lost if
                // replaced with this newly created, default initialized, info structure. The second case is for
                // temporary objects created during the trimmed file state setup. IDs may be reused when creating these
                // temporary objects, creating a case where we have a new handle that is not a duplicate of the existing
                // map entry. In this case, the map entry needs to be updated with the new object's info.
                auto iter = result.first;
                if (iter->second.handle != info.handle)
                {
                    iter->second = std::forward<T>(info);
                }
            }
        }
    }

    // Specialization template for SurfaceKHRInfo.
    //
    // Currently there is a workaround applied for Android apps that create more than 1 surface. For those apps there is
    // a command line option (--surface-index) with which the user can choose which of the surface to use, while the
    // rest simply will not be created at all. For those surfaces that are not created we still need the SurfaceKHRInfo
    // to be inserted in the map in order to be able to tell the difference whether the surface was not created because
    // of the said workaround or the user is passing a VK_NULL_HANDLE as a surface on purpose
    // (VK_GOOGLE_surfaceless_query).
    //
    // Once support for multiple Android surfaces is implemented and the workaround is
    // removed, this function should also be removed.
    //
    // Note: the "dummy" template parameter is here for the sole purpose of working around a gcc issue which does
    // not allow full specialization in non-namespace scope (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85282)
    template <typename dummy>
    void AddVkObjectInfo(VulkanSurfaceKHRInfo&& info, std::unordered_map<format::HandleId, VulkanSurfaceKHRInfo>* map)
    {
        assert(map != nullptr);

        if (info.capture_id != 0)
        {
            auto result = map->emplace(info.capture_id, std::forward<VulkanSurfaceKHRInfo>(info));

            if (!result.second)
            {
                // There are two expected cases where a capture ID would already be in the map. The first case is for
                // handles that are retrieved, such as VkPhysicalDevice, which can be processed more than once. For
                // this case we a have a duplicate info structure with the same ID and handle value, and do not need
                // to update the map entry. The existing entry may even contain additional info that would be lost if
                // replaced with this newly created, default initialized, info structure. The second case is for
                // temporary objects created during the trimmed file state setup. IDs may be reused when creating these
                // temporary objects, creating a case where we have a new handle that is not a duplicate of the existing
                // map entry. In this case, the map entry needs to be updated with the new object's info.
                auto iter = result.first;
                if (iter->second.handle != info.handle)
                {
                    iter->second = std::forward<VulkanSurfaceKHRInfo>(info);
                }
            }
        }
    }

    template <typename T>
    const T* GetVkObjectInfo(format::HandleId id, const std::unordered_map<format::HandleId, T>* map) const
    {
        return ObjectInfoGetter<T>()(id, map);
    }

    template <typename T>
    T* GetVkObjectInfo(format::HandleId id, std::unordered_map<format::HandleId, T>* map)
    {
        return ObjectInfoGetter<T>()(id, map);
    }
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_VULKAN_OBJECT_MAPPER_BASE_H
