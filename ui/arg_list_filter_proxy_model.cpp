// ArgListFilterProxyModel.cpp
#include "arg_list_filter_proxy_model.h"
#include <cstdint>
#include <iostream> // For debugging
#include <string>

ArgListFilterProxyModel::ArgListFilterProxyModel(QObject *parent, const Dive::CommandHierarchy *command_hierarchy)
    : QSortFilterProxyModel(parent), m_command_hierarchy(command_hierarchy)
{
}

GfxrVulkanCommandModel* ArgListFilterProxyModel::getSourceGfxrModel() const
{
    // It's crucial that sourceModel() returns a valid pointer and it's of the expected type.
    return qobject_cast<GfxrVulkanCommandModel*>(sourceModel());
}

void ArgListFilterProxyModel::setTargetParentSourceIndex(const QModelIndex &sourceIndex)
{
    if (m_targetParentSourceIndex != sourceIndex) {
        uint64_t selected_item_node_index = (uint64_t)(sourceIndex.internalPointer());
    std::cout << "ArgListFilterProxyModel::setTargetParentSourceIndex selected_item_node_index = " << std::to_string(selected_item_node_index) << std::endl;
        m_targetParentSourceIndex = sourceIndex;
        // Invalidate the filter so it re-evaluates all rows
        invalidateFilter();
    }

}


bool ArgListFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    // If no target parent is set (nothing selected in the main view),
    // filter out everything. You might change this to 'true' if you
    // want to show the whole model by default when nothing is specifically selected.
    if (!m_targetParentSourceIndex.isValid()) {
        return false;
    }

    // Get the QModelIndex of the item currently being evaluated in the source model.
    QModelIndex currentSourceIndex = sourceModel()->index(source_row, 0, source_parent);

    // --- Debugging logs (keep these for now, they are very helpful) ---
    std::cout << "--- filterAcceptsRow Call ---";
    std::cout << "  Evaluating: row=" << currentSourceIndex.row()
             << ", parent_row=" << currentSourceIndex.parent().row()
             << ", ptr=" << (uint64_t)currentSourceIndex.internalPointer()
             << ", data=" << currentSourceIndex.data(Qt::DisplayRole).data(); // Add this for easier identification

    std::cout << "  Target Parent: row=" << m_targetParentSourceIndex.row()
             << ", ptr=" << (uint64_t)m_targetParentSourceIndex.internalPointer()
             << ", data=" << m_targetParentSourceIndex.data(Qt::DisplayRole).data(); // Add this for easier identification
    // --- End Debugging logs ---


    // Condition 1: Accept the selected item itself.
    if (currentSourceIndex == m_targetParentSourceIndex) {
        std::cout << "  ACCEPTED: currentSourceIndex IS the target selected item.";
        return true;
    }

    // Condition 2: Accept all ancestors of the selected item.
    // This ensures that the path from the root to the selected item is visible.
    // Walk up from the target item's parent towards the root, checking if currentSourceIndex is on that path.
    QModelIndex ancestorOfTarget = m_targetParentSourceIndex.parent();
    while (ancestorOfTarget.isValid()) {
        if (ancestorOfTarget == currentSourceIndex) {
            std::cout << "  ACCEPTED: currentSourceIndex IS an ANCESTOR of the target selected item.";
            return true;
        }
        ancestorOfTarget = ancestorOfTarget.parent();
    }

    // Condition 3: Accept all descendants of the selected item (children, grandchildren, etc.).
    // Walk up from currentSourceIndex's parent towards the root, checking if the target item is on that path.
    // This means currentSourceIndex is somewhere within the subtree of m_targetParentSourceIndex.
    QModelIndex parentOfCurrent = currentSourceIndex.parent();
    while (parentOfCurrent.isValid()) {
        if (parentOfCurrent == m_targetParentSourceIndex) {
            std::cout << "  ACCEPTED: currentSourceIndex IS a DESCENDANT of the target selected item.";
            return true;
        }
        parentOfCurrent = parentOfCurrent.parent();
    }

    // If none of the conditions above are met, filter out this row.
    std::cout << "  REJECTED: Not the target item, an ancestor, or a descendant.";
    return false;
}


