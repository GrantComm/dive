// ArgsFilterProxyModel.cpp
#include "args_filter_proxy_model.h"
#include <cstdint>
#include <iostream> // For debugging
#include <string>

ArgsFilterProxyModel::ArgsFilterProxyModel(QObject *parent, const Dive::CommandHierarchy *command_hierarchy)
    : QSortFilterProxyModel(parent), m_command_hierarchy(command_hierarchy)
{
}

bool ArgsFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    // Get the index of the item in the *source model*
    QModelIndex indexInSource = sourceModel()->index(sourceRow, 0, sourceParent); // Column 0 is arbitrary here

    // IMPORTANT: Make sure the index is valid and internalPointer is cast correctly
    if (!indexInSource.isValid()) {
        return true; // Or false, depending on how you want to handle invalid rows
    }

    uint64_t node_index = (uint64_t)indexInSource.internalPointer();
    std::cout << "ArgsFilterProxyModel::filterAcceptsRow, node_index: " << std::to_string(node_index) << std::endl;
    const GfxrVulkanCommandModel *sourceMyModel = qobject_cast<const GfxrVulkanCommandModel*>(sourceModel());
    if (!sourceMyModel) {
        // This should ideally not happen if you always set MyModel as the source.
        // Log an error or return false.
        std::cerr << "Error: Source model is not GfxrVulkanCommandModel in MyFilterProxyModel." << std::endl;
        return false;
    }

    // Basic sanity check to avoid out-of-bounds access
    if (node_index >= sourceMyModel->getNumNodes()) {
        return false; // Hide if node_index is out of valid range
    }
    std::cout << "ArgsFilterProxyModel::filterAcceptsRow, " << m_command_hierarchy << std::endl;
    // Example 1: Hide all Argument nodes
    if (m_command_hierarchy->GetNodeType(node_index) == Dive::NodeType::kArgNode) {
        return false; // This row (argument) will be hidden
    }

    return true;
}
