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

#include <QTabWidget>

// Forward declarations
class CommandTabView;
class EventStateView;
class GfxrVulkanCommandArgumentsTabView;
class OverviewTabView;
class ShaderView;

namespace Dive
{
class DataCore;
} // namespace Dive

class TabSelector : public QTabWidget
{

    Q_OBJECT

public:
    explicit TabSelector(QWidget *parent = 0);
    ~TabSelector();

    CommandTabView GetCommandTabView();
    EventStateView  GetEventStateView();
    GfxrVulkanCommandArgumentsTabView GetGfxrVulkanCommandArgumentsTabView();
    OverviewTabView GetOverviewTabView();
    ShaderView      GetShaderView();
    
protected slots:

signals:

protected:
    void ResetTabs();

    void DisconnectTabs();

    CommandTabView                    *m_command_tab_view;
    int                                m_command_view_tab_index;
    EventStateView                    *m_event_state_view;
    int                                m_event_state_view_tab_index;
    GfxrVulkanCommandArgumentsTabView *m_gfxr_vulkan_command_arguments_tab_view;
    int                                m_gfxr_vulkan_command_arguments_view_tab_index;
    OverviewTabView                   *m_overview_tab_view;
    int                                m_overview_view_tab_index;
    ShaderView                        *m_shader_view;
    int                                m_shader_view_tab_index;
private:
    Dive::DataCore &m_data_core;

};