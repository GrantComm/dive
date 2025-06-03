#ifndef GFXRVULKANCOMMANDARGFILTERPROXYMODEL_H
#define GFXRVULKANCOMMANDARGFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QColor>
#include "dive_core/command_hierarchy.h"

class GfxrVulkanCommandArgFilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    GfxrVulkanCommandArgFilterProxyModel(QObject *parent = nullptr, const Dive::CommandHierarchy *command_hierarchy = nullptr);

    Q_INVOKABLE void setTargetParentSourceIndex(const QModelIndex &sourceIndex);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QPersistentModelIndex m_targetParentSourceIndex;
    bool isDescendant(const QModelIndex& potentialDescendant, const QModelIndex& potentialAncestor) const;

    const Dive::CommandHierarchy *m_command_hierarchy;
    int m_filterFunctionNodeIndex;
};

#endif // GFXRVULKANCOMMANDARGFILTERPROXYMODEL_H