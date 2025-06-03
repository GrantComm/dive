// GfxrVulkanCommandArgFilterProxyModel.cpp
#include "gfxr_vulkan_command_arg_filter_proxy_model.h"
#include <cstdint>
#include <iostream> // For debugging
#include <string>

GfxrVulkanCommandArgFilterProxyModel::GfxrVulkanCommandArgFilterProxyModel(QObject *parent, const Dive::CommandHierarchy *command_hierarchy)
    : QSortFilterProxyModel(parent), m_command_hierarchy(command_hierarchy)
{
}

void GfxrVulkanCommandArgFilterProxyModel::setTargetParentSourceIndex(const QModelIndex &sourceIndex)
{
    if (m_targetParentSourceIndex != sourceIndex) {
        beginResetModel();
        m_targetParentSourceIndex = sourceIndex;
        endResetModel();
    }

}

bool GfxrVulkanCommandArgFilterProxyModel::isDescendant(const QModelIndex& potentialDescendant, const QModelIndex& potentialAncestor) const
{
    if (!potentialAncestor.isValid()) {
        return false; // An invalid ancestor cannot have descendants
    }
    if (!potentialDescendant.isValid()) {
        return false; // An invalid descendant cannot be a descendant
    }
    if (potentialDescendant == potentialAncestor) {
        return true; // An item is considered a descendant of itself for this purpose
    }

    QModelIndex currentParent = potentialDescendant.parent();
    while (currentParent.isValid()) {
        if (currentParent == potentialAncestor) {
            return true;
        }
        currentParent = currentParent.parent();
    }
    return false;
}

QVariant GfxrVulkanCommandArgFilterProxyModel::data(const QModelIndex &index, int role) const
{
    // First, call the base class data method to get default values for all roles.
    QVariant value = QSortFilterProxyModel::data(index, role);

    if (role == Qt::ForegroundRole)
    {
        QModelIndex sourceIndex = mapToSource(index);

        if (!m_targetParentSourceIndex.isValid()) {
            // Explicitly construct QVariant from QColor
            return QVariant(QColor(Qt::gray));
        }

        if (isDescendant(sourceIndex, m_targetParentSourceIndex))
        {
            // Explicitly construct QVariant from QColor
            return QVariant(QColor(Qt::white)); // CORRECTED LINE
        }
        else
        {
            // Explicitly construct QVariant from QColor
            return QVariant(QColor(Qt::gray)); // CORRECTED LINE
        }
    }

    return value; // Return the default value for other roles
}



bool GfxrVulkanCommandArgFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    // If no target parent is set (nothing selected in the main view),
    // filter out everything. You might change this to 'true' if you
    // want to show the whole model by default when nothing is specifically selected.
    if (!m_targetParentSourceIndex.isValid()) {
        return false;
    }

    // Get the QModelIndex of the item currently being evaluated in the source model.
    QModelIndex currentSourceIndex = sourceModel()->index(source_row, 0, source_parent);

    // Condition 1: Accept the selected item itself.
    if (currentSourceIndex == m_targetParentSourceIndex) {
        return true;
    }

    // Condition 2: Accept all ancestors of the selected item.
    // This ensures that the path from the root to the selected item is visible.
    // Walk up from the target item's parent towards the root, checking if currentSourceIndex is on that path.
    QModelIndex ancestorOfTarget = m_targetParentSourceIndex.parent();
    while (ancestorOfTarget.isValid()) {
        if (ancestorOfTarget == currentSourceIndex) {
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
            return true;
        }
        parentOfCurrent = parentOfCurrent.parent();
    }

    return false;
}