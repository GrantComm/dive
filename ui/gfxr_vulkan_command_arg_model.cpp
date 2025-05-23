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
#include "gfxr_vulkan_command_arg_model.h"
#include "args_filter_proxy_model.h"
#include <QString>
#include <QStringList>
#include <QTreeWidget>

#include <iostream>
#include <sstream>
#include <string>
#include "dive_core/command_hierarchy.h"

static_assert(sizeof(void *) == sizeof(uint64_t),
              "Unable to store a uint64_t into internalPointer()!");

static const char *ColumnNames[] = {
    "Command",
    "Arguments",
};

static_assert(sizeof(ColumnNames) / sizeof(ColumnNames[0]) ==
              static_cast<size_t>(GfxrVulkanCommandArgModel::kColumnCount),
              "Mismatched GfxrVulkanCommandArg columns");

// =================================================================================================
// GfxrVulkanCommandArgModel
// =================================================================================================
GfxrVulkanCommandArgModel::GfxrVulkanCommandArgModel(const Dive::CommandHierarchy &vulkan_command_hierarchy) :
    m_vulkan_command_hierarchy(vulkan_command_hierarchy)
{
}

//--------------------------------------------------------------------------------------------------
GfxrVulkanCommandArgModel::~GfxrVulkanCommandArgModel() {}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandArgModel::Reset()
{
    emit beginResetModel();
    m_selected_node_index = UINT64_MAX;
    emit endResetModel();
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandArgModel::SetTopologyToView(const Dive::Topology *topology_ptr)
{
    emit beginResetModel();
    std::cout << "GfxrVulkanCommandArgModel::SetTopologyToView, &m_topology_ptr = " << &m_topology_ptr << std::endl;
    m_topology_ptr = topology_ptr;
    m_selected_node_index = UINT64_MAX;
    emit endResetModel();
}

//--------------------------------------------------------------------------------------------------
int GfxrVulkanCommandArgModel::columnCount(const QModelIndex &parent) const
{
    return kColumnCount;
}

//--------------------------------------------------------------------------------------------------
QModelIndex GfxrVulkanCommandArgModel::scrollToIndex() const
{
    return m_scroll_to_index;
}

//--------------------------------------------------------------------------------------------------
QVariant GfxrVulkanCommandArgModel::data(const QModelIndex &index, int role) const
{
    std::cout << "GfxrVulkanCommandArgModel, data() called" << std::endl;
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    }

    uint64_t node_index = (uint64_t)(index.internalPointer());
    if (role == Qt::ForegroundRole)
        return QColor(255, 128, 128);

    if (role != Qt::DisplayRole)
        return QVariant();

    Dive::NodeType node_type = m_vulkan_command_hierarchy.GetNodeType(node_index);

    if (index.column() == GfxrVulkanCommandArgModel::kColumnCommand)
    {
        if (node_type == Dive::NodeType::kPacketNode)
        {
            std::string           desc = m_vulkan_command_hierarchy.GetNodeDesc(node_index);
            return QString::fromStdString(desc);
        }
        else
        {
            return QVariant();
        }
    }
    return QVariant();
}

//--------------------------------------------------------------------------------------------------
Qt::ItemFlags GfxrVulkanCommandArgModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemFlags();

    return QAbstractItemModel::flags(index);
}

//--------------------------------------------------------------------------------------------------
QVariant GfxrVulkanCommandArgModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section < GfxrVulkanCommandArgModel::kColumnCount)
        {
            return QVariant(tr(ColumnNames[section]));
        }
    }
    else if (role == Qt::TextAlignmentRole)
    {
        if (section == GfxrVulkanCommandArgModel::kColumnArguments)
            return int(Qt::AlignHCenter | Qt::AlignVCenter);
        else
            return int(Qt::AlignLeft | Qt::AlignVCenter);
    }

    return QVariant();
}

//--------------------------------------------------------------------------------------------------
QModelIndex GfxrVulkanCommandArgModel::index(int row, int column, const QModelIndex &parent) const
{
    std::cout << "GfxrVulkanCommandArgModel, index called" << std::endl;
    if (!hasIndex(row, column, parent))
    {
        std::cout << "GfxrVulkanCommandArgModel, !hasIndex" << std::endl;
        return QModelIndex();
    }

    // Root level
    if (!parent.isValid())
    {
        return createIndex(row, column, (void *)m_selected_node_index);
    }

    return QModelIndex();
}

//--------------------------------------------------------------------------------------------------
QModelIndex GfxrVulkanCommandArgModel::parent(const QModelIndex &index) const
{
    std::cout << "GfxrVulkanCommandArgModel::parent called" << std::endl;
    if (!index.isValid())
        return QModelIndex();

    uint64_t child_node_index = (uint64_t)(index.internalPointer());
    std::cout << "GfxrVulkanCommandArgModel::parent child_node_index: " << std::to_string(child_node_index) << std::endl;
    return index;
}

//--------------------------------------------------------------------------------------------------
int GfxrVulkanCommandArgModel::rowCount(const QModelIndex &parent) const
{
    std::cout << "GfxrVulkanCommandArgModel, rowCount called" << std::endl;    
    if (parent.column() > 0)
    {    
        return 0;
    }
    if (m_selected_node_index == UINT64_MAX)
    {
        return 0;
    }
    
    if (!parent.isValid())  // Root level
    {
        uint64_t num_children = m_topology_ptr->GetArgCount(m_selected_node_index);
        return num_children;
    }
    return 0;
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandArgModel::OnSelectionChanged(const QModelIndex &index)
{
    std::cout << "GfxrVulkanCommandArgModel::OnSelectionChanged called" << std::endl;
    // This is where the index for the selected item should be populated and the arguments found.
    if (m_proxyModel) {
        std::cout << "GfxrVulkanCommandArgModel::OnSelectionChanged m_proxyModel is not null" << std::endl;
    }
    else {
        std::cout << "GfxrVulkanCommandArgModel::OnSelectionChanged m_proxyModel is null" << std::endl;
    }
    QModelIndex sourceIndex = m_proxyModel->mapToSource(index);
    std::cout << "GfxrVulkanCommandArgModel::OnSelectionChanged sourceIndex created" << std::endl;
uint64_t selected_node_index = (uint64_t)(sourceIndex.internalPointer());
std::cout << "GfxrVulkanCommandArgModel::OnSelectionChanged selectedNodeIndex created" << std::endl;
std::cout << "GfxrVulkanCommandArgModel::OnSelectionChanged, index = " << std::to_string(selected_node_index) << std::endl;
    // uint64_t selected_node_index = (uint64_t)(index.internalPointer());
    if (m_selected_node_index == selected_node_index)  // Selected same item
        return;
    emit beginResetModel();
    m_selected_node_index = selected_node_index;

    emit endResetModel();
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandArgModel::searchAddressColumn(QList<QModelIndex>        &search_results,
                                             int                        row,
                                             const QModelIndex         &parent,
                                             const QString             &text,
                                             const Qt::CaseSensitivity &case_sensitivity) const
{
    QModelIndex command_buffer_address_idx = index(row, GfxrVulkanCommandArgModel::kColumnCommand, parent);

    if (!command_buffer_address_idx.isValid())
        return;

    QVariant command_buffer_address_variant = data(command_buffer_address_idx, Qt::DisplayRole);

    QString command_buffer_address_variant_string = command_buffer_address_variant.toString();

    if (command_buffer_address_variant_string.contains(text, case_sensitivity))
        search_results.append(command_buffer_address_idx);
}

//--------------------------------------------------------------------------------------------------
QList<QModelIndex> GfxrVulkanCommandArgModel::search(const QModelIndex &start, const QVariant &value) const
{
    std::cout << "GfxrVulkanCommandArgModel::search called" << std::endl;
    QList<QModelIndex>  result;
    Qt::CaseSensitivity cs = Qt::CaseInsensitive;

    QString     text;
    QModelIndex p = parent(start);
    int         from = start.row();
    int         to = rowCount(p);

    for (int r = from; r < to; ++r)
    {
        QModelIndex idx = index(r, start.column(), p);
        if (!idx.isValid())
            continue;
        QVariant v = data(idx, Qt::DisplayRole);

        if (text.isEmpty())
            text = value.toString();

        // Search the address column for the text and append the index if a match is found.
        searchAddressColumn(result, r, p, text, cs);

        QString t = v.toString();
        if (t.contains(text, cs))
            result.append(idx);

        // Search the hierarchy
        if (hasChildren(idx))
            result += search(index(0, idx.column(), idx), (text.isEmpty() ? value : text));
    }

    return result;
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandArgModel::SetIsSelected(uint64_t node_index)
{
    uint32_t array_index = node_index / 8;
    uint32_t bit_element = node_index % 8;
    uint8_t  mask = 0x1 << bit_element;
    m_node_is_selected_bit_list[array_index] |= mask;
}

//--------------------------------------------------------------------------------------------------
bool GfxrVulkanCommandArgModel::IsSelected(uint64_t node_index) const
{
    uint32_t array_index = node_index / 8;
    uint32_t bit_element = node_index % 8;
    uint8_t  mask = 0x1 << bit_element;
    return (m_node_is_selected_bit_list[array_index] & mask) != 0;
}

ArgsFilterProxyModel GfxrVulkanCommandArgModel::GetProxyModel() 
const {
    return m_proxyModel;
}