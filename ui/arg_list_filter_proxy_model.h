#ifndef ARGLISTFILTERPROXYMODEL_H
#define ARGLISTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "dive_core/command_hierarchy.h"
#include "gfxr_vulkan_command_model.h"
#include "args_filter_proxy_model.h"

namespace Dive
{
class CommandHierarchy;
class Topology;
};  // namespace Dive

class ArgListFilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    ArgListFilterProxyModel(QObject *parent = nullptr, const Dive::CommandHierarchy *command_hierarchy = nullptr);

    Q_INVOKABLE void setTargetParentSourceIndex(const QModelIndex &sourceIndex);
    // void setFilterFunctionNodeIndex(int functionNodeIndex);


protected:
    // This is the key method to override for filtering rows
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    // Optional: if you need to filter based on column data, this is the one
    // bool filterAcceptsColumn(int sourceColumn, const QModelIndex &sourceParent) const override;

private:
    // You can add member variables to control the filter logic dynamically
    // For example, if you want to hide specific types:
    // bool m_hideArguments = false;
    // QString m_filterText;
    // You'd add public slots/methods to set these variables and then call invalidateFilter()
    GfxrVulkanCommandModel* getSourceGfxrModel() const;
    QPersistentModelIndex m_targetParentSourceIndex;
    bool isAncestorOfTarget(const QModelIndex &sourceParent) const;

    const Dive::CommandHierarchy *m_command_hierarchy;
    int m_filterFunctionNodeIndex;
};

#endif // ARGLISTFILTERPROXYMODEL_H