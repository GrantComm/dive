/*
 Copyright 2025 Google LLC

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

#include <QFrame>
#include <iostream>

#pragma once
// Forward declaration
class GfxrVulkanCommandView;
class GfxrVulkanCommandArgModel;
class QGroupBox;
class QLineEdit;
class QPushButton;
class SearchBar;
class ArgsFilterProxyModel;
class ArgListFilterProxyModel;
class DiveTreeView;
class GfxrVulkanCommandModel;
namespace Dive
{
class CommandHierarchy;
class Topology;
};  // namespace Dive

class GfxrVulkanCommandTabView : public QFrame
{
    Q_OBJECT

public:
    GfxrVulkanCommandTabView(const Dive::CommandHierarchy &vulkan_command_hierarchy, ArgsFilterProxyModel *proxy_model, GfxrVulkanCommandModel* command_hierarchy_model, QWidget *parent = nullptr);

    void SetTopologyToView(const Dive::Topology *topology_ptr);

    ArgsFilterProxyModel GetProxyModel() const;

    void SetProxyModel(ArgsFilterProxyModel *proxyModel) { this->m_proxyModel = proxyModel; }

    void SetCommandHierarchy(ArgsFilterProxyModel *proxyModel) { this->m_proxyModel = proxyModel; }

    void ResetModel();

public slots:
    void OnSelectionChanged(const QModelIndex &index);
    void OnSearchCommandBuffer();
    void OnSearchBarVisibilityChange(bool isHidden);
    void ConnectSearchBar();
    void DisconnectSearchBar();

signals:
    // Update property panel for node information.
    void SendNodeProperty(const QString &);
    void HideOtherSearchBars();

private:
    GfxrVulkanCommandView  *m_vulkan_command_view;
    DiveTreeView *m_command_hierarchy_view;
    GfxrVulkanCommandArgModel *m_gfxr_vulkan_command_arg_model;
    QPushButton        *m_search_trigger_button;
    SearchBar          *m_search_bar = nullptr;

    const Dive::CommandHierarchy &m_vulkan_command_hierarchy;
    ArgsFilterProxyModel        *m_proxyModel;
    ArgListFilterProxyModel     *m_listproxyModel;
    GfxrVulkanCommandModel      *m_command_hierarchy_model;

};
