/*
 Copyright 2019 Google LLC

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
#include "gfxr_vulkan_command_view.h"
#include <QPainter>
#include "gfxr_vulkan_command_model.h"
#include "dive_core/command_hierarchy.h"

static_assert(sizeof(void *) == sizeof(uint64_t),
              "Unable to store a uint64_t into internalPointer()!");

// =================================================================================================
// GfxrVulkanCommandViewDelegate
// =================================================================================================
GfxrVulkanCommandViewDelegate::GfxrVulkanCommandViewDelegate(
const GfxrVulkanCommandView *gfxr_vulkan_command_view_ptr) :
    QStyledItemDelegate(0),
    m_gfxr_vulkan_command_view_ptr(gfxr_vulkan_command_view_ptr)
{
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandViewDelegate::paint(QPainter                   *painter,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex          &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

// =================================================================================================
// GfxrVulkanCommandView
// =================================================================================================
GfxrVulkanCommandView::GfxrVulkanCommandView(const Dive::CommandHierarchy &vulkan_command_hierarchy,
                                     QWidget                      *parent) :
    DiveTreeView(vulkan_command_hierarchy, parent)
{
    setItemDelegate(new GfxrVulkanCommandViewDelegate(this));
    setAccessibleName("DiveGfxrVulkanCommandView");
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandView::setAndScrollToIndex(QModelIndex &idx)
{
    auto m = dynamic_cast<GfxrVulkanCommandModel *>(model());
    idx = m->index(idx.row(), 1, idx.parent());
    scrollTo(idx);
    setCurrentIndex(idx);
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandView::Reset()
{
    search_indexes.clear();
    search_index_it = search_indexes.begin();
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandView::searchGfxrCommandByText(const QString &search_text)
{
    search_indexes.clear();
    search_index_it = search_indexes.begin();

    if (search_text.isEmpty())
        return;

    auto m = dynamic_cast<GfxrVulkanCommandModel *>(model());
    search_indexes = m->search(m->index(0, 0), QVariant::fromValue(search_text));
    search_index_it = search_indexes.begin();

    if (!search_indexes.isEmpty())
    {
        QModelIndex curr_idx = currentIndex();
        if (curr_idx.isValid() && curr_idx != *search_index_it)
        {
            search_index_it = search_indexes.begin() +
                              getNearestSearchItem((uint64_t)(curr_idx.internalPointer()));
        }
        setAndScrollToIndex(*search_index_it);
    }
    emit updateSearch(0, search_indexes.isEmpty() ? 0 : search_indexes.size());
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandView::nextItemInSearch()
{
    if (!search_indexes.isEmpty() && search_index_it != search_indexes.end() &&
        (search_index_it + 1) != search_indexes.end())
    {
        QModelIndex curr_idx = currentIndex();
        if (curr_idx.isValid() && curr_idx != *search_index_it)
        {
            search_index_it = search_indexes.begin() +
                              getNearestSearchItem((uint64_t)(curr_idx.internalPointer()));
            if (*search_index_it == curr_idx)
                ++search_index_it;
        }
        else
        {
            ++search_index_it;
        }
        setAndScrollToIndex(*search_index_it);
        emit updateSearch(search_index_it - search_indexes.begin(), search_indexes.size());
    }
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandView::prevItemInSearch()
{
    if (!search_indexes.isEmpty() && search_index_it != search_indexes.begin())
    {
        QModelIndex curr_idx = currentIndex();
        if (curr_idx.isValid() && curr_idx != *search_index_it)
        {
            search_index_it = search_indexes.begin() +
                              getNearestSearchItem((uint64_t)(curr_idx.internalPointer()));
            if (*search_index_it == curr_idx)
                --search_index_it;
        }
        else
        {
            --search_index_it;
        }
        setAndScrollToIndex(*search_index_it);
        emit updateSearch(search_index_it - search_indexes.begin(), search_indexes.size());
    }
}

//--------------------------------------------------------------------------------------------------
int GfxrVulkanCommandView::getNearestSearchItem(uint64_t target_index)
{
    auto get_internal_pointer = [this](int index) {
        return (uint64_t)(search_indexes[index].internalPointer());
    };

    auto get_nearest = [this](int x, int y, uint64_t target) {
        if (target - (uint64_t)(search_indexes[x].internalPointer()) >=
            (uint64_t)(search_indexes[y].internalPointer()) - target)
            return y;
        else
            return x;
    };

    int n = search_indexes.size();
    int left = 0, right = n, mid = 0;

    if (target_index <= get_internal_pointer(left))
        return left;

    if (target_index >= get_internal_pointer(right - 1))
        return right - 1;

    while (left < right)
    {
        mid = (left + right) / 2;

        if (target_index == get_internal_pointer(mid))
            return mid;
        if (target_index < get_internal_pointer(mid))
        {
            if (mid > 0 && target_index > get_internal_pointer(mid - 1))
                return get_nearest(mid - 1, mid, target_index);
            right = mid;
        }
        else
        {
            if (mid < n - 1 && target_index < get_internal_pointer(mid + 1))
                return get_nearest(mid, mid + 1, target_index);
            left = mid + 1;
        }
    }
    return mid;
}
