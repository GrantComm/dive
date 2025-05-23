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

#include "gfxr_vulkan_command_tab_view.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <string>
#include "args_filter_proxy_model.h"
#include "arg_list_filter_proxy_model.h"
#include "gfxr_vulkan_command_arg_model.h"
#include "gfxr_vulkan_command_view.h"
#include "search_bar.h"
#include "shortcuts.h"

#include "dive_core/vulkan_command_hierarchy.h"
#include "object_names.h"

// =================================================================================================
// GfxrVulkanCommandTabView
// =================================================================================================
GfxrVulkanCommandTabView::GfxrVulkanCommandTabView(const Dive::CommandHierarchy &vulkan_command_hierarchy, ArgsFilterProxyModel *args_model, GfxrVulkanCommandModel* command_hierarchy_model, QWidget *parent) :
    m_vulkan_command_hierarchy(vulkan_command_hierarchy),
    m_proxyModel(args_model),
    m_command_hierarchy_model(command_hierarchy_model)
{
    m_gfxr_vulkan_command_arg_model = new GfxrVulkanCommandArgModel(vulkan_command_hierarchy);
    if (m_proxyModel) {
        std::cout << "GfxrVulkanCommandTabView constructor m_proxyModel is not null" << std::endl;
    }
    else {
        std::cout << "GfxrVulkanCommandTabView constructor m_proxyModel is null" << std::endl;
    }
    m_gfxr_vulkan_command_arg_model->SetProxyModel(m_proxyModel);
    m_vulkan_command_view = new GfxrVulkanCommandView(vulkan_command_hierarchy);
    // m_vulkan_command_view->setModel(m_gfxr_vulkan_command_arg_model);

    // Show this view:
    m_command_hierarchy_view = new DiveTreeView(m_vulkan_command_hierarchy);
    m_listproxyModel = new ArgListFilterProxyModel(m_command_hierarchy_view, &m_vulkan_command_hierarchy);
    std::cout << "gfxrCommandtabview, model: " << &m_command_hierarchy_model << std::endl;
    m_listproxyModel->setSourceModel(m_command_hierarchy_model);
    m_command_hierarchy_view->setModel(m_listproxyModel);

    /*m_proxyModel->setSourceModel(m_command_hierarchy_model);
    m_command_hierarchy_view->setModel(m_listproxyModel);
    m_command_hierarchy_view->SetListProxyModel(m_listproxyModel);*/

    std::cout << "command tab view hierarchy view: " << m_command_hierarchy_view << std::endl;
    m_search_trigger_button = new QPushButton;
    m_search_trigger_button->setObjectName(kCommandBufferSearchButtonName);
    m_search_trigger_button->setIcon(QIcon(":/images/search.png"));

    QHBoxLayout *options_layout = new QHBoxLayout();
    options_layout->addWidget(m_search_trigger_button);
    options_layout->addStretch();

    m_search_bar = new SearchBar(this);
    m_search_bar->setObjectName(kCommandBufferSearchBarName);
    m_search_bar->hide();

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(options_layout);
    main_layout->addWidget(m_search_bar);
    main_layout->addWidget(m_command_hierarchy_view);
    setLayout(main_layout);

    QObject::connect(m_search_trigger_button,
                     SIGNAL(clicked()),
                     this,
                     SLOT(OnSearchCommandBuffer()));

    QObject::connect(m_search_bar,
                     SIGNAL(hide_search_bar(bool)),
                     this,
                     SLOT(OnSearchBarVisibilityChange(bool)));
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandTabView::SetTopologyToView(const Dive::Topology *topology_ptr)
{
    m_gfxr_vulkan_command_arg_model->SetTopologyToView(topology_ptr);
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandTabView::ResetModel()
{
    m_gfxr_vulkan_command_arg_model->Reset();

    // Reset search results
    m_vulkan_command_view->Reset();
    if (m_search_bar->isVisible())
    {
        m_search_bar->clearSearch();
    }
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandTabView::OnSelectionChanged(const QModelIndex &index)
{
    std::cout << "GfxrVulkanCommandTabView, OnSelectionChanged called" << std::endl;
    QModelIndex sourceIndex = m_proxyModel->mapToSource(index);
    uint64_t selected_item_node_index = (uint64_t)(sourceIndex.internalPointer());
    std::cout << "GfxrVulkanCommandTabView, OnSelectionChanged selected_item_node_index = " << std::to_string(selected_item_node_index) << std::endl;
    m_listproxyModel->setTargetParentSourceIndex(sourceIndex);
    // m_gfxr_vulkan_command_arg_model->OnSelectionChanged(index);
    // After m_vulkan_command_view is filled out in CommandBufferModel::OnSelectionChanged(), do NOT
    // expandAll. For huge trees (e.g. 20+ million nodes), it needs to traverse all expanded nodes
    // to figure out how to setup scrollbar. So the more collapsed it is, the less it has to
    // traverse
    // m_vulkan_command_view->expandAll();

    m_vulkan_command_view->scrollTo(m_gfxr_vulkan_command_arg_model->scrollToIndex(),
                                    QAbstractItemView::PositionAtBottom);

    // Resize columns to fit
    uint32_t column_count = (uint32_t)m_gfxr_vulkan_command_arg_model->columnCount(QModelIndex());
    std::cout << "GfxrVulkanCommandTabView, OnSelectionChanged, column count: " << std::to_string(column_count) << std::endl;
    for (uint32_t column = 0; column < column_count; ++column)
        m_vulkan_command_view->resizeColumnToContents(column);

        // Reset search results
    m_vulkan_command_view->Reset();
    if (m_search_bar->isVisible())
    {
        m_search_bar->clearSearch();
    }

}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandTabView::OnSearchCommandBuffer()
{
    if (m_search_bar->isVisible())
    {
        m_search_bar->clearSearch();
        m_search_bar->hide();
        m_search_trigger_button->show();

        DisconnectSearchBar();
    }
    else
    {
        ConnectSearchBar();

        m_search_trigger_button->hide();

        m_search_bar->positionCurser();
        m_search_bar->show();
        emit HideOtherSearchBars();
    }
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandTabView::OnSearchBarVisibilityChange(bool isHidden)
{
    if (isHidden)
    {
        m_search_bar->clearSearch();
        m_search_bar->hide();
        m_search_trigger_button->show();
        DisconnectSearchBar();
    }
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandTabView::ConnectSearchBar()
{
    QObject::connect(m_search_bar,
                     SIGNAL(new_search(const QString &)),
                     m_vulkan_command_view,
                     SLOT(searchCommandBufferByText(const QString &)));
    QObject::connect(m_search_bar,
                     &SearchBar::next_search,
                     m_vulkan_command_view,
                     &GfxrVulkanCommandView::nextItemInSearch);
    QObject::connect(m_search_bar,
                     &SearchBar::prev_search,
                     m_vulkan_command_view,
                     &GfxrVulkanCommandView::prevItemInSearch);
    QObject::connect(m_vulkan_command_view,
                     &GfxrVulkanCommandView::updateSearch,
                     m_search_bar,
                     &SearchBar::updateSearchResults);
}

//--------------------------------------------------------------------------------------------------
void GfxrVulkanCommandTabView::DisconnectSearchBar()
{
    QObject::disconnect(m_search_bar,
                        SIGNAL(new_search(const QString &)),
                        m_vulkan_command_view,
                        SLOT(searchCommandBufferByText(const QString &)));
    QObject::disconnect(m_search_bar,
                        &SearchBar::next_search,
                        m_vulkan_command_view,
                        &GfxrVulkanCommandView::nextItemInSearch);
    QObject::disconnect(m_search_bar,
                        &SearchBar::prev_search,
                        m_vulkan_command_view,
                        &GfxrVulkanCommandView::prevItemInSearch);
    QObject::disconnect(m_vulkan_command_view,
                        &GfxrVulkanCommandView::updateSearch,
                        m_search_bar,
                        &SearchBar::updateSearchResults);
}

ArgsFilterProxyModel GfxrVulkanCommandTabView::GetProxyModel() 
const {
    return m_proxyModel;
}
