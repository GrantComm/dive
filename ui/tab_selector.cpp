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

#include "tab_selector.h"


void SetTabAvailable(QTabWidget *widget, int index, bool available)
{
    if (index < 0)
        return;

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    widget->setTabVisible(index, available);
#else
    widget->setTabEnabled(index, available);
#endif
}

// =================================================================================================
// TabSelector
// =================================================================================================
TabSelector::TabSelector(QWidget *parent)
{
    qDebug() << "TabSelector created.";
        m_event_selection = new EventSelection(m_data_core->GetCommandHierarchy());

#if defined(ENABLE_CAPTURE_BUFFERS)
        m_buffer_view = new BufferView(*m_data_core);
        this->addTab(m_buffer_view, "Buffers");
#endif
        m_command_tab_view = new CommandTabView(m_data_core->GetCommandHierarchy());
        m_event_state_view = new EventStateView(*m_data_core);
        m_gfxr_vulkan_command_arguments_tab_view =
        new GfxrVulkanCommandArgumentsTabView(m_data_core->GetCommandHierarchy(),
                                              m_gfxr_vulkan_commands_arguments_filter_proxy_model,
                                              m_gfxr_vulkan_command_hierarchy_model);
        m_overview_tab_view = new OverviewTabView(m_data_core->GetCaptureMetadata(), *m_event_selection);                                     
        m_shader_view = new ShaderView(*m_data_core);
                                      
        
        m_command_view_tab_index = this->addTab(m_command_tab_view, "Commands");
        m_event_state_view_tab_index = this->addTab(m_event_state_view, "Event State");
        m_gfxr_vulkan_command_arguments_view_tab_index = this->addTab(m_gfxr_vulkan_command_arguments_tab_view, "Command Arguments");
        m_overview_view_tab_index = this->addTab(m_overview_tab_view, "Overview");
        m_shader_view_tab_index = this->addTab(m_shader_view, "Shaders");

        m_text_file_view = new TextFileView(*m_data_core);
        m_text_file_view->setParent(this);

        // Set to not visible by default.
        SetTabAvailable(m_tab_widget, m_text_file_view_tab_index, false);
}

TabSelector::~TabSelector()
{
    qDebug() << "TabSelector destroyed.";
}

void TabSelector::ResetTabs()
{

}

void TabSelector::DisconnectTabs()
{
        // Get the current selection model before it potentially changes.
    QItemSelectionModel *currentSelectionModel = m_command_hierarchy_view->selectionModel();

    // Disconnect ALL signals from the selection model to ALL slots.
    if (currentSelectionModel)
    {
        QObject::disconnect(currentSelectionModel, nullptr, nullptr, nullptr);
    }

    QObject::disconnect(m_command_hierarchy_view,
                        SIGNAL(sourceCurrentChanged(const QModelIndex &, const QModelIndex &)),
                        m_command_tab_view,
                        SLOT(OnSelectionChanged(const QModelIndex &)));

    QObject::disconnect(m_command_hierarchy_view->selectionModel(),
                        SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
                        this->parent(),
                        SLOT(OnSelectionChanged(const QModelIndex &)));

    QObject::disconnect(m_command_tab_view,
                        SIGNAL(HideOtherSearchBars()),
                        this->parent(),
                        SLOT(OnTabViewChange()));

    QObject::disconnect(this->parent(),
                        SIGNAL(EventSelected(uint64_t)),
                        m_shader_view,
                        SLOT(OnEventSelected(uint64_t)));

    QObject::disconnect(this->parent(),
                        SIGNAL(EventSelected(uint64_t)),
                        m_event_state_view,
                        SLOT(OnEventSelected(uint64_t)));
#if defined(ENABLE_CAPTURE_BUFFERS)
    QObject::disconnect(this->parent(),
                        SIGNAL(EventSelected(uint64_t)),
                        m_buffer_view,
                        SLOT(OnEventSelected(uint64_t)));
#endif

    QObject::disconnect(m_command_hierarchy_view->selectionModel(),
                        SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
                        m_gfxr_vulkan_command_arguments_tab_view,
                        SLOT(OnSelectionChanged(const QModelIndex &)));

    QObject::disconnect(m_gfxr_vulkan_command_arguments_tab_view,
                        SIGNAL(HideOtherSearchBars()),
                        this->parent(),
                        SLOT(OnTabViewChange()));

    // Temporarily set the model to nullptr and clear selection/current index
    // before loading new data. This forces a clean break.
    m_command_hierarchy_view->setModel(nullptr);
    if (currentSelectionModel)
    {
        currentSelectionModel->clearSelection();
    }
}

void TabSelector::UpdateTabAvailability()
{
    m_overview_tab_view->UpdateTabAvailability();

    bool has_text = m_data_core->GetCaptureData().GetNumText() > 0;
    SetTabAvailable(m_tab_widget, m_text_file_view_tab_index, has_text);

    SetTabAvailable(m_tab_widget, m_event_state_view_tab_index, true);

#ifndef NDEBUG
    SetTabAvailable(m_tab_widget, m_event_timing_view_tab_index, true);
#endif
}