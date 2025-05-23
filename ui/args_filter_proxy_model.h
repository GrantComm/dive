#ifndef ARGSFILTERPROXYMODEL_H
#define ARGSFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "dive_core/command_hierarchy.h"
#include "gfxr_vulkan_command_model.h"

namespace Dive
{
class CommandHierarchy;
class Topology;
};  // namespace Dive

class ArgsFilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    ArgsFilterProxyModel(QObject *parent = nullptr, const Dive::CommandHierarchy *command_hierarchy = nullptr);

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
    const Dive::CommandHierarchy *m_command_hierarchy;
};

#endif // ARGSFILTERPROXYMODEL_H