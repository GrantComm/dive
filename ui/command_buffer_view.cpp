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
#include "command_buffer_view.h"

#include <QPainter>

#include "command_buffer_model.h"
#include "dive_core/command_hierarchy.h"

static_assert(sizeof(void*) == sizeof(uint64_t),
              "Unable to store a uint64_t into internalPointer()!");

// =================================================================================================
// CommandBufferViewDelegate
// =================================================================================================
CommandBufferViewDelegate::CommandBufferViewDelegate(
    const CommandBufferView* command_buffer_view_ptr)
    : QStyledItemDelegate(0), m_command_buffer_view_ptr(command_buffer_view_ptr)
{
}

//--------------------------------------------------------------------------------------------------
void CommandBufferViewDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                      const QModelIndex& index) const
{
    // Draw vertical border around a ib-level cell
    if (index.column() == CommandBufferModel::kColumnIbLevel)
    {
        painter->save();
        painter->setPen(QPen(Qt::darkGray, 1));
        painter->drawLine(option.rect.left(), option.rect.top(), option.rect.left(),
                          option.rect.bottom());
        painter->drawLine(option.rect.right(), option.rect.top(), option.rect.right(),
                          option.rect.bottom());

        painter->restore();
    }
    QStyledItemDelegate::paint(painter, option, index);
}

// =================================================================================================
// CommandBufferView
// =================================================================================================
CommandBufferView::CommandBufferView(const Dive::CommandHierarchy& command_hierarchy,
                                     QWidget* parent)
    : DiveTreeView(command_hierarchy, parent)
{
    setItemDelegate(new CommandBufferViewDelegate(this));
    setAccessibleName("DiveCommandBufferView");
}

//--------------------------------------------------------------------------------------------------
void CommandBufferView::setAndScrollToIndex(QModelIndex& idx)
{
    auto m = dynamic_cast<CommandBufferModel*>(model());
    idx = m->index(idx.row(), 1, idx.parent());
    scrollTo(idx);
    setCurrentIndex(idx);
}

//--------------------------------------------------------------------------------------------------
void CommandBufferView::Reset()
{
    search_indexes.clear();
    search_index_it = search_indexes.begin();
}

//--------------------------------------------------------------------------------------------------
static int FindNearestSearchCommand(const QList<QModelIndex>& search_indexes,
                                    const QModelIndex& target, bool prefer_previous = false)
{
    if (search_indexes.isEmpty() || !target.isValid()) return 0;

    auto get_path = [](QModelIndex idx) {
        QList<int> path;
        while (idx.isValid())
        {
            path.prepend(idx.row());
            idx = idx.parent();
        }
        return path;
    };

    auto compare_paths = [](const QList<int>& pathA, const QList<int>& pathB) {
        int minLen = std::min(pathA.size(), pathB.size());
        for (int i = 0; i < minLen; ++i)
        {
            if (pathA[i] < pathB[i]) return -1;
            if (pathA[i] > pathB[i]) return 1;
        }
        if (pathA.size() < pathB.size()) return -1;
        if (pathA.size() > pathB.size()) return 1;
        return 0;
    };

    QList<int> target_path = get_path(target);

    int left = 0;
    int right = search_indexes.size() - 1;
    int best_idx = 0;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        QList<int> mid_path = get_path(search_indexes[mid]);
        int cmp = compare_paths(mid_path, target_path);

        if (cmp == 0)
        {
            return mid;
        }
        else if (cmp < 0)
        {
            best_idx = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    QList<int> best_path = get_path(search_indexes[best_idx]);
    int cmp = compare_paths(best_path, target_path);

    if (cmp < 0)
    {
        if (!prefer_previous)
        {
            return (best_idx < search_indexes.size() - 1) ? best_idx + 1 : 0;
        }
    }
    else if (cmp > 0)
    {
        if (prefer_previous)
        {
            return (best_idx > 0) ? best_idx - 1 : search_indexes.size() - 1;
        }
    }
    return best_idx;
}

//--------------------------------------------------------------------------------------------------
void CommandBufferView::searchCommandBufferByText(const QString& search_text)
{
    search_indexes.clear();
    search_index_it = search_indexes.begin();

    if (search_text.isEmpty())
    {
        emit updateSearch(0, 0);
        return;
    }

    auto m = dynamic_cast<CommandBufferModel*>(model());
    search_indexes = m->search(m->index(0, 0), QVariant::fromValue(search_text));

    if (!search_indexes.isEmpty())
    {
        QModelIndex curr_idx = currentIndex();

        // If the current index is invalid or not within the highlighted section (lacks accent
        // color), default to the first highlighted match.
        if (m && (!curr_idx.isValid() || !curr_idx.data(Qt::ForegroundRole).isValid()))
        {
            QModelIndex highlighted_idx;
            for (int i = 0; i < search_indexes.size(); ++i)
            {
                if (search_indexes[i].data(Qt::ForegroundRole).isValid())
                {
                    highlighted_idx = search_indexes[i];
                    break;
                }
            }
            if (highlighted_idx.isValid())
            {
                curr_idx = highlighted_idx;
            }
            else if (!curr_idx.isValid())
            {
                curr_idx = m->scrollToIndex();
            }
        }

        if (curr_idx.isValid())
        {
            search_index_it =
                search_indexes.begin() + FindNearestSearchCommand(search_indexes, curr_idx);
        }
        else
        {
            search_index_it = search_indexes.begin();
        }
        setAndScrollToIndex(*search_index_it);
    }

    emit updateSearch(search_indexes.isEmpty() ? 0 : (search_index_it - search_indexes.begin()),
                      search_indexes.size());
}

//--------------------------------------------------------------------------------------------------
void CommandBufferView::nextCommandInSearch()
{
    if (search_indexes.isEmpty()) return;

    QModelIndex curr_idx = currentIndex();
    if (!curr_idx.isValid())
    {
        auto m = dynamic_cast<CommandBufferModel*>(model());
        if (m)
        {
            for (int i = 0; i < search_indexes.size(); ++i)
            {
                if (search_indexes[i].data(Qt::ForegroundRole).isValid())
                {
                    curr_idx = search_indexes[i];
                    break;
                }
            }
            if (!curr_idx.isValid()) curr_idx = m->scrollToIndex();
        }
    }

    if (curr_idx.isValid() && curr_idx.internalId() != search_index_it->internalId())
    {
        search_index_it =
            search_indexes.begin() + FindNearestSearchCommand(search_indexes, curr_idx);
        if (search_index_it->internalId() == curr_idx.internalId())
        {
            if ((search_index_it + 1) != search_indexes.end())
            {
                ++search_index_it;
            }
            else
            {
                search_index_it = search_indexes.begin();
            }
        }
    }
    else
    {
        if ((search_index_it + 1) != search_indexes.end())
        {
            ++search_index_it;
        }
        else
        {
            search_index_it = search_indexes.begin();
        }
    }

    setAndScrollToIndex(*search_index_it);
    emit updateSearch(search_index_it - search_indexes.begin(), search_indexes.size());
}

//--------------------------------------------------------------------------------------------------
void CommandBufferView::prevCommandInSearch()
{
    if (search_indexes.isEmpty()) return;

    QModelIndex curr_idx = currentIndex();
    if (!curr_idx.isValid())
    {
        auto m = dynamic_cast<CommandBufferModel*>(model());
        if (m) curr_idx = m->scrollToIndex();
    }

    if (curr_idx.isValid() && curr_idx.internalId() != search_index_it->internalId())
    {
        search_index_it =
            search_indexes.begin() + FindNearestSearchCommand(search_indexes, curr_idx, true);
        if (search_index_it->internalId() == curr_idx.internalId())
        {
            if (search_index_it != search_indexes.begin())
            {
                --search_index_it;
            }
            else
            {
                search_index_it = search_indexes.end() - 1;
            }
        }
    }
    else
    {
        if (search_index_it != search_indexes.begin())
        {
            --search_index_it;
        }
        else
        {
            search_index_it = search_indexes.end() - 1;
        }
    }

    setAndScrollToIndex(*search_index_it);
    emit updateSearch(search_index_it - search_indexes.begin(), search_indexes.size());
}
