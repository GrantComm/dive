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
#include "main_window.h"
#include "main_window_p.h"

#include <QApplication>
#include <QCoreApplication>
#include <QFileDialog>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>
#include <QReadLocker>
#include <QReadWriteLock>
#include <QScrollBar>
#include <QShortcut>
#include <QSplitter>
#include <QTemporaryDir>
#include <QThread>
#include <QTimer>
#include <QToolButton>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>
#include <QWriteLocker>
#include <cstdlib>
#include <filesystem>

#include "absl/status/statusor.h"
#include "absl/types/span.h"
#include "capture_service/constants.h"
#include "dive/ui/components/overlay/overlay.h"
#include "dive/ui/components/settings/settings.h"
#include "dive/ui/types/file_path.h"
#include "dive/utils/device_resources.h"
#include "dive/utils/device_resources_constants.h"
#include "trace_stats/trace_stats.h"
#include "ui/about_window.h"
#include "ui/analyze_window.h"
#include "ui/application_controller.h"
#include "ui/capture_file_manager.h"
#include "ui/command_buffer_model.h"
#include "ui/command_buffer_view.h"
#include "ui/command_model.h"
#include "ui/command_tab_view.h"
#include "ui/dive_tree_view.h"
#include "ui/error_dialog.h"
#include "ui/event_selection_model.h"
#include "ui/event_state_view.h"
#include "ui/frame_tab_view.h"
#include "ui/gfxr_vulkan_command_arguments_filter_proxy_model.h"
#include "ui/gfxr_vulkan_command_arguments_tab_view.h"
#include "ui/gfxr_vulkan_command_filter.h"
#include "ui/gfxr_vulkan_command_filter_proxy_model.h"
#include "ui/gfxr_vulkan_command_model.h"
#include "ui/gpu_timing_model.h"
#include "ui/gpu_timing_tab_view.h"
#include "ui/hover_help_model.h"
#include "ui/object_names.h"
#include "ui/overview_tab_view.h"
#include "ui/perf_counter_model.h"
#include "ui/perf_counter_tab_view.h"
#include "ui/property_panel.h"
#include "ui/search_bar.h"
#include "ui/shader_view.h"
#include "ui/shortcuts.h"
#include "ui/shortcuts_window.h"
#include "ui/text_file_view.h"
#include "ui/trace_window.h"
#include "ui/what_if_configure_dialog.h"
#include "ui/what_if_setup_dialog.h"
#include "dive_core/cross_ref.h"
#include "dive_core/available_metrics.h"
#include "trace_stats/trace_stats.h"

namespace
{
constexpr int kMessageTimeoutMs = 2500;

constexpr int kViewModeStringCount = 2;
constexpr int kEventViewModeStringCount = 1;
constexpr int kFrameTitleStringCount = 3;

constexpr const char* kViewModeStrings[kViewModeStringCount] = {"Submit", "Events"};
constexpr const char* kEventViewModeStrings[kEventViewModeStringCount] = {"GPU Events"};
constexpr const char* kFrameTitleStrings[kFrameTitleStringCount] = {
    "No File Loaded", "Gfxr Capture", "Adreno Rd Capture"};
constexpr const char* kFilterStrings[DiveFilterModel::kFilterModeCount] = {
    "None", "BinningPassOnly", "FirstTilePassOnly", "BinningAndFirstTilePass"};
constexpr DiveFilterModel::FilterMode kDefaultFilterMode = DiveFilterModel::kFirstTilePassOnly;

enum class DrawCallContextMenuOption : int
{
    kUnknown,
    kArguments,
    kBinningPassOnly,
    kFirstTilePassOnly,
    kPerfCounterData,
    kGpuTimeData,
};

constexpr std::array kCorrelatedContextOptions{
    DrawCallContextMenuOption::kArguments,          //
    DrawCallContextMenuOption::kBinningPassOnly,    //
    DrawCallContextMenuOption::kFirstTilePassOnly,  //
    DrawCallContextMenuOption::kPerfCounterData,    //
    DrawCallContextMenuOption::kGpuTimeData,        //
};

constexpr std::array kNonCorrelatedContextOptions{
    DrawCallContextMenuOption::kArguments,        //
    DrawCallContextMenuOption::kPerfCounterData,  //
    DrawCallContextMenuOption::kGpuTimeData,      //
};

constexpr std::array kCommandBufferContextOptions{
    DrawCallContextMenuOption::kArguments,    //
    DrawCallContextMenuOption::kGpuTimeData,  //
};

QString ToQString(DrawCallContextMenuOption opt)
{
    switch (opt)
    {
        case DrawCallContextMenuOption::kUnknown:
            break;
        case DrawCallContextMenuOption::kArguments:
            return "Arguments";
        case DrawCallContextMenuOption::kBinningPassOnly:
            return "PM4 Events with BinningPassOnly Filter";
        case DrawCallContextMenuOption::kFirstTilePassOnly:
            return "PM4 Events with FirstTilePassOnly Filter";
        case DrawCallContextMenuOption::kPerfCounterData:
            return "Perf Counter Data";
        case DrawCallContextMenuOption::kGpuTimeData:
            return "Gpu Time Data";
    }
    return "Unknown";
}

}  // namespace

void SetTabAvailable(QTabWidget* widget, int index, bool available)
{
    if (index < 0) return;

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    widget->setTabVisible(index, available);
#else
    widget->setTabEnabled(index, available);
#endif
}

MainWindow::MainWindow(ApplicationController& controller)
    : m_impl(std::make_unique<MainWindowPrivate>(this, controller))
{
    m_impl->Initialize();
}

MainWindow::~MainWindow() = default;
 
MainWindowPrivate::MainWindowPrivate(MainWindow* host, ApplicationController& controller)
    : m_main_window_ptr(host),
      m_controller(controller)
{
}

MainWindowPrivate::~MainWindowPrivate() = default;
 
 void MainWindow::closeEvent(QCloseEvent* event)
 {
     m_impl->OnCloseEvent(event);
 }

TraceDialog& MainWindow::GetTraceDialog()
{
    return *m_impl->m_trace_dig;
}

ProgressTrackerCallback& MainWindow::GetProgressTracker() { return m_impl->m_progress_tracker; }

bool MainWindow::LoadFile(const std::string& file_name, bool is_temp_file, bool async) { return m_impl->LoadFile(file_name, is_temp_file, async); }
void MainWindow::OnCapture(bool is_capture_delayed) { m_impl->OnCapture(is_capture_delayed); }
void MainWindow::OnCaptureUpdated(const QString& file_path) { m_impl->OnCaptureUpdated(file_path); }
void MainWindow::OnSwitchToShaderTab() { m_impl->OnSwitchToShaderTab(); }
void MainWindow::OnOpenVulkanDrawCallMenu(const QPoint& pos) { m_impl->OnOpenVulkanDrawCallMenu(pos); }
void MainWindow::OnOpenVulkanCallMenu(const QPoint& pos) { m_impl->OnOpenVulkanCallMenu(pos); }
void MainWindow::OnCorrelateVulkanDrawCall(const QModelIndex& index) { m_impl->OnCorrelateVulkanDrawCall(index); }
void MainWindow::OnCorrelatePm4DrawCall(const QModelIndex& index) { m_impl->OnCorrelatePm4DrawCall(index); }
void MainWindow::OnCounterSelected(uint64_t row_index) { m_impl->OnCounterSelected(row_index); }
void MainWindow::OnGpuTimingDataSelected(uint64_t node_index) { m_impl->OnGpuTimingDataSelected(node_index); }
void MainWindow::OnCorrelationFilterApplied(uint64_t gfxr_draw_call_index, const QModelIndex& index) { m_impl->OnCorrelationFilterApplied(gfxr_draw_call_index, index); }
void MainWindow::OnPendingPerfCounterResults(const QString& file_name) { m_impl->OnPendingPerfCounterResults(file_name); }
void MainWindow::OnPendingGpuTimingResults(const QString& file_name) { m_impl->OnPendingGpuTimingResults(file_name); }
void MainWindow::OnPendingScreenshot(const QString& file_name) { m_impl->OnPendingScreenshot(file_name); }
void MainWindow::OnHideOverlay() { m_impl->OnHideOverlay(); }
void MainWindow::OnAddWhatIfModification() { m_impl->OnAddWhatIfModification(); }
void MainWindow::OnWhatIfSetupTrigger() { m_impl->OnWhatIfSetupTrigger(); }
void MainWindow::OnCommandViewModeChange(const QString& view_mode) { m_impl->OnCommandViewModeChange(view_mode); }
void MainWindow::OnCommandViewModeComboBoxHover(const QString& view_mode) { m_impl->OnCommandViewModeComboBoxHover(view_mode); }
void MainWindow::OnSelectionChanged(const QModelIndex& index) { m_impl->OnSelectionChanged(index); }
void MainWindow::OnFilterModeChange(const QString& filter_mode) { m_impl->OnFilterModeChange(filter_mode); }
void MainWindow::OnGfxrFilterModeChange() { m_impl->OnGfxrFilterModeChange(); }
void MainWindow::OnOpenFile() { m_impl->OnOpenFile(); }
void MainWindow::OnNormalCapture() { m_impl->OnNormalCapture(); }
void MainWindow::OnCaptureTrigger() { m_impl->OnCaptureTrigger(); }
void MainWindow::OnAnalyzeCapture() { m_impl->OnAnalyzeCapture(); }
void MainWindow::OnExpandToLevel() { m_impl->OnExpandToLevel(); }
void MainWindow::OnAbout() { m_impl->OnAbout(); }
void MainWindow::OnShortcuts() { m_impl->OnShortcuts(); }
void MainWindow::OnSaveCapture() { m_impl->OnSaveCapture(); }
void MainWindow::OnSearchTrigger() { m_impl->OnSearchTrigger(); }
void MainWindow::OpenRecentFile() { m_impl->OpenRecentFile(); }
void MainWindow::UpdateOverlay(const QString& message) { m_impl->UpdateOverlay(message); }
void MainWindow::OnCrossReference(Dive::CrossRef ref) { m_impl->OnCrossReference(ref); }
void MainWindow::OnFileLoaded(const LoadFileResult& result) { m_impl->OnFileLoaded(result); }
void MainWindow::OnTraceAvailable(const QString& path) { m_impl->OnTraceAvailable(path); }
void MainWindow::OnTabViewSearchBarVisibilityChange(bool isHidden) { m_impl->OnTabViewSearchBarVisibilityChange(isHidden); }
void MainWindow::OnTabViewChange() { m_impl->OnTabViewChange(); }
void MainWindow::OnTraceStatsUpdated() { m_impl->OnTraceStatsUpdated(); }
void MainWindow::ConnectDiveFileTabs() { m_impl->ConnectDiveFileTabs(); }
void MainWindow::ConnectAdrenoRdFileTabs() { m_impl->ConnectAdrenoRdFileTabs(); }
void MainWindow::ConnectGfxrFileTabs() { m_impl->ConnectGfxrFileTabs(); }
void MainWindow::ConnectSearchBar() { m_impl->ConnectSearchBar(); }
void MainWindow::DisconnectSearchBar() { m_impl->DisconnectSearchBar(); }
void MainWindow::ConnectPm4SearchBar() { m_impl->ConnectPm4SearchBar(); }
void MainWindow::DisconnectPm4SearchBar() { m_impl->DisconnectPm4SearchBar(); }
void MainWindow::DisconnectAllTabs() { m_impl->DisconnectAllTabs(); }

void MainWindowPrivate::Initialize()
{
    m_controller.Register(*m_main_window_ptr);

    // Output logs to both the "record" as well as console output
    m_log_compound.AddLog(&m_log_record);
    m_log_compound.AddLog(&m_log_console);

    m_error_dialog = new ErrorDialog(m_main_window_ptr);

    m_data_core = std::make_shared<Dive::DataCore>(&m_progress_tracker);

    m_capture_manager = new CaptureFileManager(m_main_window_ptr);
    m_capture_manager->Start(m_data_core);
    m_capture_manager->GetDataCoreLock().lockForRead();
    m_capture_acquired = true;

    QObject::connect(m_capture_manager, &CaptureFileManager::FileLoadingFinished, m_main_window_ptr,
                     &MainWindow::OnFileLoaded);
    QObject::connect(m_capture_manager, &CaptureFileManager::TraceStatsUpdated, m_main_window_ptr,
                     &MainWindow::OnTraceStatsUpdated);

    m_event_selection = new EventSelection(m_data_core->GetCommandHierarchy());

    // Left side panel
    m_left_group_box = new QGroupBox(kFrameTitleStrings[0]);
    m_left_group_box->setAlignment(Qt::AlignHCenter);
    m_view_mode_combo_box = new TreeViewComboBox();

    {
        QVBoxLayout* left_vertical_layout = new QVBoxLayout();

        QFrame* text_combo_box_frame = new QFrame();

        QHBoxLayout* text_combo_box_layout = new QHBoxLayout();

        QLabel* combo_box_label = new QLabel(m_main_window_ptr->tr("Mode:"));

        // Set model for the view mode combo box
        QStandardItemModel* combo_box_model = new QStandardItemModel();
        for (int i = 0; i < kViewModeStringCount; i++)
        {
            QStandardItem* item = new QStandardItem(kViewModeStrings[i]);
            combo_box_model->appendRow(item);
        }

        QModelIndex event_item_index = combo_box_model->index(1, 0, QModelIndex());
        QStandardItem* event_item = combo_box_model->itemFromIndex(event_item_index);
        event_item->setSelectable(false);
        for (int i = 0; i < kEventViewModeStringCount; i++)
        {
            QStandardItem* item = new QStandardItem(kEventViewModeStrings[i]);
            event_item->appendRow(item);
        }
        m_view_mode_combo_box->setModel(combo_box_model);

        QModelIndex vulkan_event_item_index = combo_box_model->index(0, 0, event_item_index);
        m_view_mode_combo_box->setRootModelIndex(vulkan_event_item_index.parent());
        m_view_mode_combo_box->setCurrentIndex(vulkan_event_item_index.row());

        text_combo_box_layout->addWidget(combo_box_label);
        text_combo_box_layout->addWidget(m_view_mode_combo_box, 1);

        QLabel* filter_combo_box_label = new QLabel(m_main_window_ptr->tr("Filter:"));
        m_filter_mode_combo_box = new TreeViewComboBox();

        // Set model for the filter combo box
        QStandardItemModel* filter_combo_box_model = new QStandardItemModel();
        for (uint32_t i = 0; i < DiveFilterModel::kFilterModeCount; i++)
        {
            QStandardItem* item = new QStandardItem(kFilterStrings[i]);
            filter_combo_box_model->appendRow(item);
        }
        m_filter_mode_combo_box->setModel(filter_combo_box_model);
        m_filter_mode_combo_box->setCurrentIndex(kDefaultFilterMode);

        text_combo_box_layout->addWidget(filter_combo_box_label);
        text_combo_box_layout->addWidget(m_filter_mode_combo_box, 1);

        m_event_search_bar = new SearchBar(m_main_window_ptr);
        m_event_search_bar->setObjectName("Event Search Bar");

        QHBoxLayout* search_layout = new QHBoxLayout;
        search_layout->addWidget(m_event_search_bar);
        m_event_search_bar->hide();

        m_command_hierarchy_model = new CommandModel(m_data_core->GetCommandHierarchy());
        m_gfxr_vulkan_command_hierarchy_model =
            new GfxrVulkanCommandModel(m_data_core->GetCommandHierarchy());

        m_command_hierarchy_view = new DiveTreeView(m_data_core->GetCommandHierarchy());
        m_command_hierarchy_view->SetDataCore(m_data_core.get());
        m_event_search_bar->setView(m_command_hierarchy_view);

        m_gfxr_vulkan_commands_filter_proxy_model = new GfxrVulkanCommandFilterProxyModel(
            m_data_core->GetCommandHierarchy(), m_command_hierarchy_view);

        m_gfxr_vulkan_commands_arguments_filter_proxy_model =
            new GfxrVulkanCommandArgumentsFilterProxyModel(m_command_hierarchy_view,
                                                           &m_data_core->GetCommandHierarchy());

        m_filter_model = new DiveFilterModel(m_data_core->GetCommandHierarchy(), m_main_window_ptr);
        m_filter_model->setSourceModel(m_command_hierarchy_model);
        // Set the proxy model as the view's model
        m_command_hierarchy_view->setModel(m_filter_model);
        m_command_hierarchy_view->setContextMenuPolicy(Qt::CustomContextMenu);
        m_filter_model->SetMode(kDefaultFilterMode);

        m_filter_gfxr_commands_combo_box = new GfxrVulkanCommandFilter(
            *m_command_hierarchy_view, *m_gfxr_vulkan_commands_filter_proxy_model);
        text_combo_box_layout->addWidget(m_filter_gfxr_commands_combo_box, 1);
        m_filter_gfxr_commands_combo_box->hide();

        m_search_trigger_button = new QPushButton;
        m_search_trigger_button->setIcon(QIcon(":/images/search.png"));
        text_combo_box_layout->addWidget(m_search_trigger_button);

        text_combo_box_layout->addStretch();
        text_combo_box_frame->setLayout(text_combo_box_layout);

        m_perf_counter_model = new PerfCounterModel();

        m_gpu_timing_model = new GpuTimingModel(m_main_window_ptr);

        QLabel* goto_draw_call_label = new QLabel(m_main_window_ptr->tr("Go To:"));
        m_prev_event_button = new QPushButton("Prev Event");
        m_next_event_button = new QPushButton("Next Event");

        QHBoxLayout* goto_draw_call_layout = new QHBoxLayout();
        goto_draw_call_layout->addWidget(goto_draw_call_label);
        goto_draw_call_layout->addWidget(m_prev_event_button);
        goto_draw_call_layout->addWidget(m_next_event_button);
        goto_draw_call_layout->addStretch();

        QLabel* expand_to_lvl_label = new QLabel(m_main_window_ptr->tr("Expand to level:"));
        for (int i = 1; i <= 3; i++)
        {
            auto button = new QPushButton{QString::number(i)};
            m_expand_to_lvl_buttons << button;
        }

        QHBoxLayout* expand_to_lvl_layout = new QHBoxLayout();
        expand_to_lvl_layout->addWidget(expand_to_lvl_label);
        foreach (auto expand_to_lvl_button, m_expand_to_lvl_buttons)
            expand_to_lvl_layout->addWidget(expand_to_lvl_button);
        expand_to_lvl_layout->addStretch();

        left_vertical_layout->addWidget(m_event_search_bar);
        left_vertical_layout->addWidget(text_combo_box_frame);
        left_vertical_layout->addWidget(m_command_hierarchy_view);
        left_vertical_layout->addLayout(goto_draw_call_layout);
        left_vertical_layout->addLayout(expand_to_lvl_layout);
        m_left_group_box->setLayout(left_vertical_layout);
    }

    // Middle panel
    m_middle_group_box = new QGroupBox(kFrameTitleStrings[0]);
    m_middle_group_box->setAlignment(Qt::AlignHCenter);
    m_pm4_view_mode_combo_box = new TreeViewComboBox();
    {
        QVBoxLayout* middle_vertical_layout = new QVBoxLayout();

        QFrame* text_combo_box_frame = new QFrame();

        QHBoxLayout* text_combo_box_layout = new QHBoxLayout();

        QLabel* combo_box_label = new QLabel(m_main_window_ptr->tr("Mode:"));

        // Set model for the view mode combo box
        QStandardItemModel* combo_box_model = new QStandardItemModel();
        for (int i = 0; i < kViewModeStringCount; i++)
        {
            QStandardItem* item = new QStandardItem(kViewModeStrings[i]);
            combo_box_model->appendRow(item);
        }

        QModelIndex event_item_index = combo_box_model->index(1, 0, QModelIndex());
        QStandardItem* event_item = combo_box_model->itemFromIndex(event_item_index);
        event_item->setSelectable(false);
        for (int i = 0; i < kEventViewModeStringCount; i++)
        {
            QStandardItem* item = new QStandardItem(kEventViewModeStrings[i]);
            event_item->appendRow(item);
        }
        m_pm4_view_mode_combo_box->setModel(combo_box_model);

        QModelIndex vulkan_event_item_index = combo_box_model->index(0, 0, event_item_index);
        m_pm4_view_mode_combo_box->setRootModelIndex(vulkan_event_item_index.parent());
        m_pm4_view_mode_combo_box->setCurrentIndex(vulkan_event_item_index.row());

        text_combo_box_layout->addWidget(combo_box_label);
        text_combo_box_layout->addWidget(m_pm4_view_mode_combo_box, 1);

        QLabel* filter_combo_box_label = new QLabel(m_main_window_ptr->tr("Filter:"));
        m_pm4_filter_mode_combo_box = new TreeViewComboBox();

        // Set model for the filter combo box
        QStandardItemModel* filter_combo_box_model = new QStandardItemModel();
        for (uint32_t i = 0; i < DiveFilterModel::kFilterModeCount; i++)
        {
            QStandardItem* item = new QStandardItem(kFilterStrings[i]);
            filter_combo_box_model->appendRow(item);
        }
        m_pm4_filter_mode_combo_box->setModel(filter_combo_box_model);
        m_pm4_filter_mode_combo_box->setCurrentIndex(kDefaultFilterMode);

        text_combo_box_layout->addWidget(filter_combo_box_label);
        text_combo_box_layout->addWidget(m_pm4_filter_mode_combo_box, 1);

        m_pm4_search_trigger_button = new QPushButton;
        m_pm4_search_trigger_button->setIcon(QIcon(":/images/search.png"));
        text_combo_box_layout->addWidget(m_pm4_search_trigger_button);

        text_combo_box_layout->addStretch();
        text_combo_box_frame->setLayout(text_combo_box_layout);

        m_pm4_event_search_bar = new SearchBar(m_main_window_ptr);
        m_pm4_event_search_bar->setObjectName("Event Search Bar");

        QHBoxLayout* search_layout = new QHBoxLayout;
        search_layout->addWidget(m_pm4_event_search_bar);
        m_pm4_event_search_bar->hide();

        m_pm4_command_hierarchy_view = new DiveTreeView(m_data_core->GetCommandHierarchy());
        m_pm4_command_hierarchy_view->SetDataCore(m_data_core.get());
        m_pm4_event_search_bar->setView(m_pm4_command_hierarchy_view);

        // Set the proxy model as the view's model
        m_pm4_command_hierarchy_view->setModel(m_filter_model);
        m_pm4_command_hierarchy_view->setContextMenuPolicy(Qt::CustomContextMenu);
        m_filter_model->SetMode(kDefaultFilterMode);
        //
        QLabel* pm4_goto_draw_call_label = new QLabel(m_main_window_ptr->tr("Go To:"));
        m_pm4_prev_event_button = new QPushButton("Prev Event");
        m_pm4_next_event_button = new QPushButton("Next Event");
        QHBoxLayout* pm4_goto_draw_call_layout = new QHBoxLayout();
        pm4_goto_draw_call_layout->addWidget(pm4_goto_draw_call_label);
        pm4_goto_draw_call_layout->addWidget(m_pm4_prev_event_button);
        pm4_goto_draw_call_layout->addWidget(m_pm4_next_event_button);
        pm4_goto_draw_call_layout->addStretch();

        QLabel* expand_to_lvl_label = new QLabel(m_main_window_ptr->tr("Expand to level:"));
        for (int i = 1; i <= 3; i++)
        {
            auto button = new QPushButton{QString::number(i)};
            m_pm4_expand_to_lvl_buttons << button;
        }

        QHBoxLayout* pm4_expand_to_lvl_layout = new QHBoxLayout();
        pm4_expand_to_lvl_layout->addWidget(expand_to_lvl_label);
        foreach (auto expand_to_lvl_button, m_pm4_expand_to_lvl_buttons)
            pm4_expand_to_lvl_layout->addWidget(expand_to_lvl_button);
        pm4_expand_to_lvl_layout->addStretch();

        middle_vertical_layout->addWidget(m_pm4_event_search_bar);
        middle_vertical_layout->addWidget(text_combo_box_frame);
        middle_vertical_layout->addWidget(m_pm4_command_hierarchy_view);
        middle_vertical_layout->addLayout(pm4_goto_draw_call_layout);
        middle_vertical_layout->addLayout(pm4_expand_to_lvl_layout);
        m_middle_group_box->setLayout(middle_vertical_layout);
    }

    // Tabbed View
    m_tab_widget = new QTabWidget();
    {
        m_command_tab_view = new CommandTabView(m_data_core->GetCommandHierarchy());
        m_shader_view = new ShaderView(*m_data_core);

        m_capture_stats = std::make_unique<Dive::CaptureStats>();
        m_overview_tab_view =
            new OverviewTabView(m_data_core->GetCaptureMetadata(), *m_capture_stats);
        m_event_state_view = new EventStateView(*m_data_core);

        m_perf_counter_tab_view = new PerfCounterTabView(*m_perf_counter_model, m_main_window_ptr);
        m_gfxr_vulkan_command_arguments_tab_view = new GfxrVulkanCommandArgumentsTabView(
            m_data_core->GetCommandHierarchy(), m_gfxr_vulkan_commands_arguments_filter_proxy_model,
            m_gfxr_vulkan_command_hierarchy_model);
        m_gpu_timing_tab_view =
            new GpuTimingTabView(*m_gpu_timing_model, m_data_core->GetCommandHierarchy(), m_main_window_ptr);

        m_frame_tab_view = new FrameTabView(m_main_window_ptr);

        m_text_file_view = new TextFileView(*m_data_core);

        m_tabs.gfxr_vulkan_command_arguments =
            m_tab_widget->addTab(m_gfxr_vulkan_command_arguments_tab_view, "Arguments");
        m_tabs.frame = m_tab_widget->addTab(m_frame_tab_view, "Frame View");
        m_tabs.command = m_tab_widget->addTab(m_command_tab_view, "PM4 Packets");
        m_tabs.event_state = m_tab_widget->addTab(m_event_state_view, "Event State");
        m_tabs.gpu_timing = m_tab_widget->addTab(m_gpu_timing_tab_view, "Gpu Timing");
        m_tabs.perf_counter = m_tab_widget->addTab(m_perf_counter_tab_view, "Perf Counters");
        m_tabs.text_file = m_tab_widget->addTab(m_text_file_view, "Text File");
        m_tabs.shader = m_tab_widget->addTab(m_shader_view, "Shaders");
        // Note: qt bug, the last widget can't be set as invisible, otherwise navagation breaks
        //       when widget width is smaller than required to show all tabs.
        //       Workaround: keep overview tab always visible.
        m_tabs.overview = m_tab_widget->addTab(m_overview_tab_view, "Overview");

        UpdateTabAvailability(TabMaskBits::kNone);
    }
    // Side panel
    // TODO (b/445754645) Remove the PropertyPanel and replace with a tooltip or overlay.
    m_property_panel = new PropertyPanel();
    m_property_panel->setMinimumWidth(350);
    m_hover_help = HoverHelp::Get();
    m_shader_view->SetupHoverHelp(*m_hover_help);

    m_left_group_box->setMinimumSize(QSize(50, 0));
    m_middle_group_box->setMinimumSize(QSize(50, 0));
    m_tab_widget->setMinimumSize(QSize(50, 0));

    // The main horizontal splitter (Left, Middle, and Right panels, with a 1:1:1 size ratio)
    QSplitter* horizontal_splitter = new QSplitter(Qt::Horizontal, m_main_window_ptr);
    horizontal_splitter->addWidget(m_left_group_box);
    horizontal_splitter->addWidget(m_middle_group_box);
    horizontal_splitter->addWidget(m_tab_widget);
    horizontal_splitter->setStretchFactor(0, 1);
    horizontal_splitter->setStretchFactor(1, 1);
    horizontal_splitter->setStretchFactor(2, 1);

    QList<int> equal_sizes;
    equal_sizes << 1 << 1 << 1;
    horizontal_splitter->setSizes(equal_sizes);

    // Retrieve the available metrics
    LoadAvailableMetrics();

    m_trace_dig = new TraceDialog(m_controller, m_main_window_ptr);
    m_analyze_dig = new AnalyzeDialog(m_controller, m_available_metrics.get(), m_main_window_ptr);
    m_what_if_setup_dig = new WhatIfSetupDialog(m_main_window_ptr);
    m_what_if_configure_dig = new WhatIfConfigureDialog(m_what_if_setup_dig);

    m_overlay = new OverlayHelper(m_main_window_ptr);
    m_overlay->Initialize(horizontal_splitter);

    // Main Window requires a central widget.
    auto central_widget = new QWidget;
    central_widget->setLayout(m_overlay->GetLayout());
    m_main_window_ptr->setCentralWidget(central_widget);

    m_middle_group_box->hide();

    // Connections
    QObject::connect(m_hover_help, SIGNAL(CurrStringChanged(const QString&)), m_property_panel,
                     SLOT(OnHoverStringChange(const QString&)));
    // Event selection connections
    QObject::connect(m_event_selection, &EventSelection::vulkanParams, m_property_panel,
                     &PropertyPanel::OnVulkanParams);
    QObject::connect(m_trace_dig, &TraceDialog::TraceAvailable, m_main_window_ptr,
                     &MainWindow::OnTraceAvailable);

    QObject::connect(m_main_window_ptr, &MainWindow::FileLoaded, m_text_file_view, &TextFileView::OnFileLoaded);
    QObject::connect(m_search_trigger_button, SIGNAL(clicked()), m_main_window_ptr, SLOT(OnSearchTrigger()));

    QObject::connect(m_event_search_bar, SIGNAL(hide_search_bar(bool)), m_main_window_ptr,
                     SLOT(OnTabViewSearchBarVisibilityChange(bool)));

    QObject::connect(m_tab_widget, &QTabWidget::currentChanged, m_main_window_ptr, &MainWindow::OnTabViewChange);

    QObject::connect(m_main_window_ptr, &MainWindow::AnalyzeCaptureStarted, m_analyze_dig,
                     &AnalyzeDialog::OnAnalyzeCaptureStarted);
    QObject::connect(m_analyze_dig, &AnalyzeDialog::CaptureUpdated, m_main_window_ptr,
                     &MainWindow::OnCaptureUpdated);
    QObject::connect(m_analyze_dig, &AnalyzeDialog::DisplayPerfCounterResults, m_main_window_ptr,
                     &MainWindow::OnPendingPerfCounterResults);
    QObject::connect(m_analyze_dig, &AnalyzeDialog::DisplayGpuTimingResults, m_main_window_ptr,
                     &MainWindow::OnPendingGpuTimingResults);

    QObject::connect(m_main_window_ptr, &MainWindow::PendingGpuTimingResults, m_main_window_ptr,
                     &MainWindow::OnPendingGpuTimingResults);
    QObject::connect(m_main_window_ptr, &MainWindow::PendingPerfCounterResults, m_main_window_ptr,
                     &MainWindow::OnPendingPerfCounterResults);
    QObject::connect(m_main_window_ptr, &MainWindow::PendingScreenshot, m_main_window_ptr,
                     &MainWindow::OnPendingScreenshot);

    // Filter mode change connections
    QObject::connect(m_filter_model, &DiveFilterModel::FilterModeChanged,
                     m_pm4_command_hierarchy_view, &DiveTreeView::OnFilterModeChanged);
    QObject::connect(m_filter_model, &DiveFilterModel::FilterModeChanged, m_command_hierarchy_view,
                     &DiveTreeView::OnFilterModeChanged);

    // What-If connections
    QObject::connect(m_what_if_setup_dig, &WhatIfSetupDialog::AddModification, m_main_window_ptr,
                     &MainWindow::OnAddWhatIfModification);
    QObject::connect(m_what_if_setup_dig, &QDialog::rejected, m_what_if_configure_dig,
                     &QWidget::close);
    QObject::connect(m_what_if_configure_dig, &WhatIfConfigureDialog::AddModification,
                     m_what_if_setup_dig, &WhatIfSetupDialog::OnAddModificationToList);

    CreateActions();
    CreateMenus();
    CreateStatusBar();
    CreateShortcuts();
    CreateToolBars();
    UpdateRecentFileActions(Settings::Get()->ReadRecentFiles());

    // Capture overlay widget
    QObject::connect(&m_progress_tracker, SIGNAL(sendMessageSignal(const QString&)), m_main_window_ptr,
                     SLOT(UpdateOverlay(const QString&)));
    QObject::connect(m_main_window_ptr, &MainWindow::HideOverlay, m_main_window_ptr, &MainWindow::OnHideOverlay);

    // Set default view mode
    m_main_window_ptr->OnCommandViewModeChange(m_main_window_ptr->tr(kEventViewModeStrings[0]));
    m_hover_help->SetCurItem(HoverHelp::Item::kNone);
    m_hover_help->SetDataCore(m_data_core.get());
    m_main_window_ptr->setAccessibleName("DiveMainWindow");

    m_controller.MainWindowInitialized();
}



//--------------------------------------------------------------------------------------------------




//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnTraceAvailable(const QString& path)
{
    qDebug() << "Trace is at " << path;
    // Figure out what do we do if we get repeated trigger of LoadFile before async call is done.
    m_main_window_ptr->LoadFile(path.toStdString().c_str(), /*is_temp_file*/ true, /*async*/ false);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnCommandViewModeChange(const QString& view_mode)
{
    QObject* sender_object = m_main_window_ptr->sender();
    if (sender_object == m_pm4_view_mode_combo_box)
    {
        m_pm4_command_hierarchy_view->header()->reset();
    }
    else
    {
        m_command_hierarchy_view->header()->reset();
    }

    const Dive::CommandHierarchy& command_hierarchy = m_data_core->GetCommandHierarchy();
    if (view_mode == m_main_window_ptr->tr(kViewModeStrings[0]))  // Submit
    {
        const Dive::SharedNodeTopology& topology = command_hierarchy.GetSubmitHierarchyTopology();
        m_command_hierarchy_model->SetTopologyToView(&topology);
        m_command_tab_view->SetTopologyToView(&topology);
    }
    else  // All Vulkan Calls + GPU Events
    {
        const Dive::SharedNodeTopology& topology = command_hierarchy.GetAllEventHierarchyTopology();
        if (m_gfxr_capture_loaded)
        {
            m_gfxr_vulkan_command_hierarchy_model->SetTopologyToView(&topology);
        }
        else
        {
            m_gfxr_vulkan_command_hierarchy_model->SetTopologyToView(&topology);
            m_command_hierarchy_model->SetTopologyToView(&topology);
            m_command_tab_view->SetTopologyToView(&topology);
        }

        // Put EventID column to the left of the tree. This forces the expand/collapse icon to be
        // part of the 2nd column (originally 1st)
        if (m_prev_command_view_mode.isEmpty() ||
            m_prev_command_view_mode == m_main_window_ptr->tr(kViewModeStrings[0]) ||
            m_prev_command_view_mode == m_main_window_ptr->tr(kViewModeStrings[1]))
        {
            if (sender_object == m_pm4_view_mode_combo_box)
            {
                m_pm4_command_hierarchy_view->header()->moveSection(1, 0);
            }
            else
            {
                m_command_hierarchy_view->header()->moveSection(1, 0);
            }
        }
    }

    m_prev_command_view_mode = view_mode;
    if (sender_object == m_pm4_view_mode_combo_box)
    {
        ExpandResizeHierarchyView(*m_pm4_command_hierarchy_view, *m_filter_model);
    }
    else if (m_gfxr_capture_loaded)
    {
        ExpandResizeHierarchyView(*m_command_hierarchy_view,
                                  *m_gfxr_vulkan_commands_filter_proxy_model);
    }
    else
    {
        ExpandResizeHierarchyView(*m_command_hierarchy_view, *m_filter_model);
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnCommandViewModeComboBoxHover(const QString& view_mode)
{
    if (view_mode == m_main_window_ptr->tr(kViewModeStrings[0]))  // Engine
        m_hover_help->SetCurItem(HoverHelp::Item::kEngineView);
    else if (view_mode == m_main_window_ptr->tr(kViewModeStrings[1]))  // Submit
        m_hover_help->SetCurItem(HoverHelp::Item::kSubmitView);
    else if (view_mode == m_main_window_ptr->tr(kEventViewModeStrings[0]))  // GPU Events
        m_hover_help->SetCurItem(HoverHelp::Item::kAllVulkanCallsGpuEventsView);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnSelectionChanged(const QModelIndex& index)
{
    // Determine which node it is, and emit m_main_window_ptr->m_main_window_ptr signal
    const Dive::CommandHierarchy& command_hierarchy = m_data_core->GetCommandHierarchy();
    uint64_t selected_item_node_index = 0;

    if (m_gfxr_capture_loaded)
    {
        QModelIndex source_index = m_gfxr_vulkan_commands_filter_proxy_model->mapToSource(index);
        selected_item_node_index = source_index.internalId();
    }
    else
    {
        QModelIndex source_model_index = m_filter_model->mapToSource(index);
        selected_item_node_index = source_model_index.internalId();
    }

    Dive::NodeType node_type = command_hierarchy.GetNodeType(selected_item_node_index);
    if (node_type == Dive::NodeType::kEventNode || node_type == Dive::NodeType::kMarkerNode)
    {
        emit m_main_window_ptr->EventSelected(selected_item_node_index);
    }
    else
    {
        emit m_main_window_ptr->EventSelected(UINT64_MAX);
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnFilterModeChange(const QString& filter_mode)
{
    DiveFilterModel::FilterMode new_mode = DiveFilterModel::kNone;

    if (filter_mode == kFilterStrings[DiveFilterModel::kNone])
    {
        new_mode = DiveFilterModel::kNone;
    }
    else if (filter_mode == kFilterStrings[DiveFilterModel::kBinningPassOnly])
    {
        new_mode = DiveFilterModel::kBinningPassOnly;
    }
    else if (filter_mode == kFilterStrings[DiveFilterModel::kFirstTilePassOnly])
    {
        new_mode = DiveFilterModel::kFirstTilePassOnly;
    }
    else if (filter_mode == kFilterStrings[DiveFilterModel::kBinningAndFirstTilePass])
    {
        new_mode = DiveFilterModel::kBinningAndFirstTilePass;
    }

    if (m_filter_model)
    {
        m_filter_model->SetMode(new_mode);
    }

    if (m_command_hierarchy_view)
    {
        ResetVerticalScroll(*m_command_hierarchy_view);
        m_command_hierarchy_view->scrollToTop();
    }

    m_perf_counter_tab_view->ClearSelection();
    m_gpu_timing_tab_view->ClearSelection();

    if (m_correlated_capture_loaded)
    {
        ClearViewModelSelection(*m_command_hierarchy_view, true);
        ClearViewModelSelection(*m_pm4_command_hierarchy_view, false);
        ExpandResizeHierarchyView(*m_pm4_command_hierarchy_view, *m_filter_model);
    }
    else
    {
        ClearViewModelSelection(*m_command_hierarchy_view, true);
        ExpandResizeHierarchyView(*m_command_hierarchy_view, *m_filter_model);
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnGfxrFilterModeChange()
{
    ClearViewModelSelection(*m_command_hierarchy_view, false);

    m_perf_counter_tab_view->ClearSelection();
    m_gpu_timing_tab_view->ClearSelection();

    ResetVerticalScroll(*m_command_hierarchy_view);
    m_command_hierarchy_view->scrollToTop();
    if (m_correlated_capture_loaded)
    {
        m_pm4_command_hierarchy_view->scrollToTop();
        ClearViewModelSelection(*m_pm4_command_hierarchy_view, false);
        ExpandResizeHierarchyView(*m_pm4_command_hierarchy_view, *m_filter_model);
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnDiveFileLoaded()
{
    // Reset models and views that display data from the capture
    m_left_group_box->setTitle(kFrameTitleStrings[1]);
    m_middle_group_box->show();
    m_middle_group_box->setTitle(kFrameTitleStrings[2]);
    m_gfxr_vulkan_command_arguments_tab_view->ResetModel();
    m_gfxr_vulkan_command_hierarchy_model->Reset();
    m_command_tab_view->ResetModel();
    m_command_hierarchy_model->Reset();
    m_event_selection->Reset();
    m_shader_view->Reset();
    m_text_file_view->Reset();
    m_prev_command_view_mode = QString();
    m_filter_gfxr_commands_combo_box->Reset();

    m_gfxr_vulkan_commands_filter_proxy_model->setSourceModel(
        m_gfxr_vulkan_command_hierarchy_model);

    m_command_hierarchy_model->BeginResetModel();

    UpdateTabAvailability(TabMaskBits::kViewsForCorrelated);

    // Left Panel contains gfxr display
    m_command_hierarchy_view->setModel(m_gfxr_vulkan_commands_filter_proxy_model);
    // Reset and enable the gfxr command filter
    m_filter_gfxr_commands_combo_box->Reset();
    m_filter_gfxr_commands_combo_box->setEnabled(true);
    m_filter_gfxr_commands_combo_box->show();
    // Disable the view mode combo box and filter
    m_filter_model->SetMode(kDefaultFilterMode);
    m_filter_mode_combo_box->setCurrentIndex(kDefaultFilterMode);
    m_view_mode_combo_box->setEnabled(false);
    m_filter_mode_combo_box->hide();

    // Middle Panel contains pm4 display
    m_pm4_command_hierarchy_view->setModel(m_filter_model);
    m_pm4_filter_mode_combo_box->setEnabled(true);
    m_pm4_filter_mode_combo_box->show();
    m_pm4_filter_mode_combo_box->setCurrentIndex(kDefaultFilterMode);

    ConnectDiveFileTabs();

    {
        m_main_window_ptr->OnCommandViewModeChange(m_main_window_ptr->tr(kEventViewModeStrings[0]));
        // TODO (b/185579518): disable the dropdown list for vulkan events.
    }
    m_command_hierarchy_model->EndResetModel();
    m_gfxr_vulkan_command_hierarchy_model->EndResetModel();

    // Collect the gfxr draw call indices
    m_gfxr_vulkan_commands_filter_proxy_model->CollectGfxrDrawCallIndices();

    // Collect the PM4 draw call indices for the current filter
    m_filter_model->CollectPm4DrawCallIndices(QModelIndex());

    // Iterate m_gfxr_vulkan_command_hierarchy_model to collect the indices of the vulkan events
    // where gpu timing data will be collected
    m_gpu_timing_tab_view->CollectIndicesFromModel(*m_gfxr_vulkan_command_hierarchy_model,
                                                   QModelIndex());

    // Ensure there is no previous tab index set
    m_previous_tab_index = -1;

    StartTraceStats();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnAdrenoRdFileLoaded()
{
    // Reset models and views that display data from the capture
    m_left_group_box->setTitle(kFrameTitleStrings[2]);
    m_middle_group_box->setTitle(kFrameTitleStrings[0]);
    m_middle_group_box->hide();
    m_command_tab_view->ResetModel();
    m_command_hierarchy_model->Reset();
    m_event_selection->Reset();
    m_shader_view->Reset();
    m_text_file_view->Reset();
    m_prev_command_view_mode = QString();

    m_command_hierarchy_model->BeginResetModel();

    UpdateTabAvailability(TabMaskBits::kViewsForRdFile);

    m_filter_model->SetMode(kDefaultFilterMode);
    m_command_hierarchy_view->setModel(m_filter_model);

    m_filter_mode_combo_box->setEnabled(true);
    m_filter_mode_combo_box->show();
    m_filter_mode_combo_box->setCurrentIndex(kDefaultFilterMode);
    m_filter_gfxr_commands_combo_box->Reset();
    m_filter_gfxr_commands_combo_box->setEnabled(false);
    m_filter_gfxr_commands_combo_box->hide();
    m_view_mode_combo_box->setEnabled(true);
    m_pm4_filter_mode_combo_box->setEnabled(false);

    ConnectAdrenoRdFileTabs();

    {
        m_main_window_ptr->OnCommandViewModeChange(m_main_window_ptr->tr(kEventViewModeStrings[0]));
        // TODO (b/185579518): disable the dropdown list for vulkan events.
    }
    m_command_hierarchy_model->EndResetModel();

    // Collect the PM4 draw call indices for the current filter
    m_filter_model->CollectPm4DrawCallIndices(QModelIndex());

    // Ensure there is no previous tab index set
    m_previous_tab_index = -1;

    StartTraceStats();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnGfxrFileLoaded()
{
    // Reset models and views that display data from the capture
    m_left_group_box->setTitle(kFrameTitleStrings[1]);
    m_middle_group_box->setTitle(kFrameTitleStrings[0]);
    m_middle_group_box->hide();
    m_gfxr_vulkan_command_hierarchy_model->Reset();
    m_prev_command_view_mode = QString();
    m_filter_gfxr_commands_combo_box->Reset();

    m_gfxr_vulkan_command_hierarchy_model->BeginResetModel();

    m_gfxr_vulkan_commands_filter_proxy_model->setSourceModel(
        m_gfxr_vulkan_command_hierarchy_model);
    m_command_hierarchy_view->setModel(m_gfxr_vulkan_commands_filter_proxy_model);

    UpdateTabAvailability(TabMaskBits::kViewsForGfxrFile);

    ConnectGfxrFileTabs();

    // Ensure the All Event topology is displayed.
    m_main_window_ptr->OnCommandViewModeChange(m_main_window_ptr->tr(kEventViewModeStrings[0]));
    // Disable the Mode and Filter combo boxes.
    m_view_mode_combo_box->setEnabled(false);
    m_filter_mode_combo_box->setEnabled(false);
    m_filter_mode_combo_box->hide();
    m_filter_gfxr_commands_combo_box->setEnabled(true);
    m_filter_gfxr_commands_combo_box->show();
    m_pm4_filter_mode_combo_box->setEnabled(false);

    m_gfxr_vulkan_command_hierarchy_model->EndResetModel();

    // Iterate m_gfxr_vulkan_command_hierarchy_model to collect the indices of the vulkan events
    // where gpu timing data will be collected
    m_gpu_timing_tab_view->CollectIndicesFromModel(*m_gfxr_vulkan_command_hierarchy_model,
                                                   QModelIndex());

    // Ensure there is no previous tab index set
    m_previous_tab_index = -1;
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::StartTraceStats()
{
    *m_capture_stats = {};
    m_overview_tab_view->setProperty("is_loading", true);
    m_overview_tab_view->LoadStatistics();
    m_capture_manager->GatherTraceStats();
}

void MainWindowPrivate::OnTraceStatsUpdated()
{
    m_capture_manager->FillCaptureStatsResult(*m_capture_stats);
    m_overview_tab_view->setProperty("is_loading", false);
    m_overview_tab_view->LoadStatistics();
}

//--------------------------------------------------------------------------------------------------
bool MainWindowPrivate::LoadFile(const std::string& file_name, bool is_temp_file, bool async)
{
    bool release_capture = m_capture_acquired;
    m_capture_acquired = false;

    m_gfxr_capture_loaded = false;
    m_correlated_capture_loaded = false;

    if (release_capture)
    {
        // We don't want other UI interaction as they cause race conditions.
        m_main_window_ptr->setDisabled(true);

        m_log_record.Reset();

        m_command_hierarchy_view->setCurrentIndex(QModelIndex());

        // Disconnect the signals for all of the possible tabs.
        DisconnectAllTabs();

        // Clear vectors of draw call indices as they are only used for a correlated view.
        m_filter_model->ClearDrawCallIndices();

        // Discard associated timing results.
        m_perf_counter_model->OnPerfCounterResultsGenerated("", std::nullopt);
        m_gpu_timing_model->OnGpuTimingResultsGenerated("");
        m_capture_manager->GetDataCoreLock().unlock();

        // Reset the command buffer model and view.
        m_command_tab_view->ResetModel();

        *m_capture_stats = {};
        m_overview_tab_view->LoadStatistics();
    }

    m_progress_tracker.sendMessage("Loading " + file_name);
    m_last_request = LastRequest{.file_name = file_name, .is_temp_file = is_temp_file};

    auto reference = Dive::FilePath{file_name};
    auto components = m_capture_manager->ResolveComponents(reference);
    m_capture_manager->LoadFile(reference, components);
    // Clear task queue for fresh capture.
    m_loading_pending_task.clear();
    EmitLoadAssociatedFileTasks(components);
    return true;
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnPendingPerfCounterResults(const QString& file_name)
{
    if (!(m_perf_counter_model && m_available_metrics))
    {
        return;
    }

    auto file_path = std::filesystem::path(file_name.toStdString());
    auto task = [this, file_path]() {
        m_perf_counter_model->OnPerfCounterResultsGenerated(file_path, *m_available_metrics);
        if (!file_path.empty())
        {
            qDebug() << "Loaded: " << file_path.string().c_str();
        }
    };
    if (!m_capture_acquired)
    {
        m_loading_pending_task.push_back(task);
        return;
    }
    task();
}

void MainWindowPrivate::OnPendingGpuTimingResults(const QString& file_name)
{
    if (!m_gpu_timing_model)
    {
        return;
    }
    auto task = [this, file_name]() {
        m_gpu_timing_model->OnGpuTimingResultsGenerated(file_name);
        if (!file_name.isEmpty())
        {
            qDebug() << "Loaded: " << file_name;
        }
    };
    if (!m_capture_acquired)
    {
        m_loading_pending_task.push_back(task);
        return;
    }
    task();
}

void MainWindowPrivate::OnPendingScreenshot(const QString& file_name)
{
    if (!m_frame_tab_view)
    {
        return;
    }
    auto task = [this, file_name]() {
        m_frame_tab_view->OnCaptureScreenshotLoaded(file_name);
        if (!file_name.isEmpty())
        {
            qDebug() << "Loaded: " << file_name;
        }
    };
    if (!m_capture_acquired)
    {
        m_loading_pending_task.push_back(task);
        return;
    }
    task();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::EmitLoadAssociatedFileTasks(const Dive::ComponentFilePaths& components)
{
    if (!components.perf_counter_csv.empty() &&
        std::filesystem::exists(components.perf_counter_csv))
    {
        qDebug() << "Attempting to load perf counter data from: "
                 << components.perf_counter_csv.string().c_str();
        m_main_window_ptr->PendingPerfCounterResults(QString::fromStdString(components.perf_counter_csv.string()));
    }
    else
    {
        m_main_window_ptr->PendingPerfCounterResults("");
    }

    if (!components.gpu_timing_csv.empty() && std::filesystem::exists(components.gpu_timing_csv))
    {
        qDebug() << "Attempting to load gpu timing data from: "
                 << components.gpu_timing_csv.string().c_str();
        m_main_window_ptr->PendingGpuTimingResults(QString::fromStdWString(components.gpu_timing_csv.wstring()));
    }
    else
    {
        m_main_window_ptr->PendingGpuTimingResults("");
    }

    if (!components.screenshot_png.empty() && std::filesystem::exists(components.screenshot_png))
    {
        qDebug() << "Attempting to load screenshot from: "
                 << components.screenshot_png.string().c_str();
        m_main_window_ptr->PendingScreenshot(QString::fromStdWString(components.screenshot_png.wstring()));
    }
    else
    {
        m_main_window_ptr->PendingScreenshot("");
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnFileLoaded(const LoadFileResult& loaded_file)
{
    DIVE_ASSERT(!m_capture_acquired);
    m_capture_manager->GetDataCoreLock().lockForRead();
    m_capture_acquired = true;

    bool load_succeed = (loaded_file.status == LoadFileResult::Status::kSuccess);
    if (!load_succeed)
    {
        m_loading_pending_task.clear();
        m_error_dialog->OnLoadingFailure(loaded_file);
    }

    std::vector<std::function<void()>> tasks;
    std::swap(tasks, m_loading_pending_task);
    for (auto& task : tasks)
    {
        task();
    }

    // Re-enable UI interaction now we are done async loading.
    m_main_window_ptr->setEnabled(true);
    m_main_window_ptr->HideOverlay();

    if (load_succeed)
    {
        switch (loaded_file.file_type)
        {
            case LoadFileResult::FileType::kUnknown:
                break;
            case LoadFileResult::FileType::kCorrelatedFiles:
                m_correlated_capture_loaded = true;
                OnDiveFileLoaded();
                ExpandResizeHierarchyView(*m_command_hierarchy_view,
                                          *m_gfxr_vulkan_commands_filter_proxy_model);
                ExpandResizeHierarchyView(*m_pm4_command_hierarchy_view, *m_filter_model);
                break;
            case LoadFileResult::FileType::kRdFile:
                OnAdrenoRdFileLoaded();
                ExpandResizeHierarchyView(*m_command_hierarchy_view, *m_filter_model);
                break;
            case LoadFileResult::FileType::kGfxrFile:
                m_gfxr_capture_loaded = true;
                OnGfxrFileLoaded();
                ExpandResizeHierarchyView(*m_command_hierarchy_view,
                                          *m_gfxr_vulkan_commands_filter_proxy_model);
                break;
        }

        m_analyze_action->setEnabled(m_gfxr_capture_loaded || m_correlated_capture_loaded);
        m_hover_help->SetCurItem(HoverHelp::Item::kNone);
        m_capture_file = QString(m_last_request.file_name.c_str());
        qDebug() << "MainWindow::OnFileLoaded: m_capture_file: " << m_capture_file;
        QFileInfo file_info(m_capture_file);
        SetCurrentFile(m_capture_file, m_last_request.is_temp_file);
        emit m_main_window_ptr->SetSaveAsMenuStatus(true);
        if (m_unsaved_capture_path.empty())
        {
            emit m_main_window_ptr->SetSaveMenuStatus(false);
        }
        else
        {
            emit m_main_window_ptr->SetSaveMenuStatus(true);
        }
        ShowTempStatus(m_main_window_ptr->tr("File loaded successfully"));
    }
    else
    {
        SetCurrentFile("", false);
    }

    emit m_main_window_ptr->FileLoaded();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnOpenFile()
{
    QString supported_files = QStringLiteral(
        "Supported Files (*.rd *.gfxr);;Dive files (*.rd);;GFXR files (*.gfxr);;All files (*.*)");
    QString file_name = QFileDialog::getOpenFileName(
        m_main_window_ptr, "Open Document", Settings::Get()->ReadLastFilePath(), supported_files);

    if (!file_name.isEmpty())
    {
        QString last_file_path = file_name.left(file_name.lastIndexOf('/'));
        Settings::Get()->WriteLastFilePath(last_file_path);
        if (!m_main_window_ptr->LoadFile(file_name.toStdString().c_str()))
        {
            QMessageBox::critical(m_main_window_ptr, QString("Error opening file"),
                                  (QString("Unable to open file: ") + file_name));
        }
    }
}

// =================================================================================================
// OnNormalCapture is triggered for captures without counters.
// =================================================================================================
void MainWindowPrivate::OnNormalCapture() { emit m_main_window_ptr->OnCapture(false); }

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnAnalyzeCapture()
{
    qDebug() << "Launching AnalyzeDialog with: " << m_capture_file;
    m_main_window_ptr->AnalyzeCaptureStarted(m_capture_file);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnCaptureTrigger()
{
    if (!m_capture_saved && !m_unsaved_capture_path.empty())
    {
        QMessageBox warning_box;
        warning_box.setText("The current capture is not saved.");
        warning_box.setInformativeText("Do you want to proceed with a new capture?");
        warning_box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        warning_box.setDefaultButton(QMessageBox::Ok);
        warning_box.setModal(true);
        int ret = warning_box.exec();

        if (ret == QMessageBox::Cancel) return;
    }

    QInputDialog input_dialog;
    input_dialog.setWindowTitle("Capture with delay");
    input_dialog.setLabelText("Enter capture delay (in seconds)");
    input_dialog.setInputMode(QInputDialog::IntInput);
    input_dialog.setOkButtonText("Start Capture");
    input_dialog.setIntRange(0, INT_MAX);
    input_dialog.setIntValue(Settings::Get()->ReadCaptureDelay());

    bool ok = input_dialog.exec();
    if (ok)
    {
        uint32_t capture_delay = input_dialog.intValue();
        QTimer::singleShot(capture_delay * 1000, m_main_window_ptr, SLOT(m_main_window_ptr->OnCapture(true)));
        Settings::Get()->WriteCaptureDelay(capture_delay);
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnCapture(bool is_capture_delayed)
{
    m_trace_dig->UpdateDeviceList();
    m_trace_dig->show();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnWhatIfSetupTrigger()
{
    m_what_if_setup_dig->UpdateDeviceList();
    m_what_if_setup_dig->show();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnAddWhatIfModification()
{
    m_what_if_configure_dig->SetTcpClient(m_what_if_setup_dig->GetConnectedTcpClient());
    m_what_if_configure_dig->show();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnExpandToLevel()
{
    QObject* sender_obj = m_main_window_ptr->sender();
    if (sender_obj->isWidgetType())
    {
        QPushButton* button = qobject_cast<QPushButton*>(sender_obj);
        if (button)
        {
            int level = button->text().toInt();
            DiveTreeView* target_view = nullptr;

            if (m_expand_to_lvl_buttons.contains(button))
            {
                target_view = m_command_hierarchy_view;
            }
            else
            {
                target_view = m_pm4_command_hierarchy_view;
            }

            if (target_view)
            {
                target_view->ExpandToLevel(level);
                target_view->RetainCurrentNode();
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnAbout()
{
    AboutDialog* about = new AboutDialog();
    QObject::connect(about, &AboutDialog::finished, about, &AboutDialog::deleteLater);
    about->open();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnShortcuts()
{
    ShortcutsDialog* shortcuts = new ShortcutsDialog();
    QObject::connect(shortcuts, &ShortcutsDialog::finished, shortcuts,
                     &ShortcutsDialog::deleteLater);
    shortcuts->open();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnCloseEvent(QCloseEvent* closeEvent)
{
    if (!m_capture_saved && !m_unsaved_capture_path.empty())
    {
        switch (QMessageBox::question(m_main_window_ptr, QString("Save current capture"),
                                      (QString("Do you want to save current capture")),
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
        {
            case QMessageBox::Yes:
                OnSaveCapture();
                break;
            case QMessageBox::No:
            {
                // Remove unsaved capture files.
                if (!m_unsaved_capture_path.empty())
                {
                    std::filesystem::remove(m_unsaved_capture_path);
                    m_unsaved_capture_path.clear();
                }
                break;
            }
            default:
                DIVE_ASSERT(false);
        }
    }
    if (m_trace_dig)
    {
        m_trace_dig->Cleanup();
    }
    if (m_what_if_setup_dig)
    {
        m_what_if_setup_dig->Cleanup();
    }
    closeEvent->accept();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OpenRecentFile()
{
    QAction* action = qobject_cast<QAction*>(m_main_window_ptr->sender());
    if (action)
    {
        m_main_window_ptr->LoadFile(action->data().toString().toStdString().c_str());
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnSaveCapture()
{
    if (m_capture_file.isEmpty())
    {
        return;
    }
    QString file_name = QFileDialog::getSaveFileName(m_main_window_ptr, m_main_window_ptr->tr("Save the current capture"),
                                                     QDir::currentPath(), m_main_window_ptr->tr("Dive files (*.dive)"),
                                                     nullptr, QFileDialog::DontConfirmOverwrite);
    if (file_name.isNull() || file_name.isEmpty() || file_name == m_capture_file)
    {
        return;
    }

    if (!file_name.endsWith(".dive"))
    {
        file_name += ".dive";
    }
    QFile target_file(file_name);
    if (target_file.exists())
    {
        switch (QMessageBox::question(m_main_window_ptr, QString("File already exists"),
                                      (QString("Do you want to replace the existing capture?")),
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
        {
            case QMessageBox::Yes:
                target_file.remove();
                break;
            case QMessageBox::No:
                return OnSaveCapture();
            default:
                DIVE_ASSERT(false);
        }
    }

    bool save_result = false;
    bool is_saving_new_capture = m_unsaved_capture_path == m_capture_file.toStdString();
    // Save the newly captured file by rename and existing capture by copy.
    if (is_saving_new_capture)
    {
        save_result = QFile::rename(m_capture_file, file_name);
    }
    else
    {
        save_result = QFile::copy(m_capture_file, file_name);
    }

    if (save_result)
    {
        QMessageBox::information(m_main_window_ptr, m_main_window_ptr->tr("Save capture succeed"), m_main_window_ptr->tr("Save capture succeed."));
    }
    else
    {
        QMessageBox::critical(m_main_window_ptr, m_main_window_ptr->tr("Save capture file failed"),
                              m_main_window_ptr->tr("Save capture file failed."));
        return;
    }
    if (is_saving_new_capture)
    {
        m_unsaved_capture_path.clear();
        // Disable the "Save" menu after the new capture saved.
        emit m_main_window_ptr->SetSaveMenuStatus(false);
    }
    m_capture_saved = true;
    m_capture_file = file_name;
    SetCurrentFile(m_capture_file);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ResetEventSearchBar()
{
    m_event_search_bar->clearSearch();
    m_event_search_bar->hide();
    m_search_trigger_button->show();
    DisconnectSearchBar();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ResetPm4EventSearchBar()
{
    m_pm4_event_search_bar->clearSearch();
    m_pm4_event_search_bar->hide();
    m_pm4_search_trigger_button->show();
    DisconnectPm4SearchBar();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ResetHorizontalScroll(const DiveTreeView& tree_view)
{
    QScrollBar* h_scroll_bar = tree_view.horizontalScrollBar();
    if (h_scroll_bar)
    {
        h_scroll_bar->triggerAction(QAbstractSlider::SliderToMinimum);
    }
}

void MainWindowPrivate::ResetVerticalScroll(const DiveTreeView& tree_view)
{
    QScrollBar* v_scroll_bar = tree_view.verticalScrollBar();
    if (v_scroll_bar)
    {
        v_scroll_bar->triggerAction(QAbstractSlider::SliderToMinimum);
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnSearchTrigger()
{
    QObject* sender_object = m_main_window_ptr->sender();

    if (sender_object == m_search_trigger_button)
    {
        if (m_event_search_bar->isVisible())
        {
            ResetEventSearchBar();
        }
        else
        {
            ConnectSearchBar();
            m_search_trigger_button->hide();
            m_event_search_bar->positionCurser();
            m_event_search_bar->show();

            if (m_pm4_event_search_bar->isVisible())
            {
                ResetPm4EventSearchBar();
            }
        }
    }
    else if (sender_object == m_pm4_search_trigger_button)
    {
        if (m_pm4_event_search_bar->isVisible())
        {
            ResetPm4EventSearchBar();
        }
        else
        {
            ConnectPm4SearchBar();
            m_pm4_search_trigger_button->hide();
            m_pm4_event_search_bar->positionCurser();
            m_pm4_event_search_bar->show();

            if (m_event_search_bar->isVisible())
            {
                ResetEventSearchBar();
            }
        }
    }

    int current_index = m_tab_widget->currentIndex();
    QWidget* current_tab = m_tab_widget->widget(current_index);
    SearchBar* tab_wiget_search_bar = nullptr;
    QPushButton* tab_wiget_search_button = nullptr;

    if (current_index == m_tabs.command)
    {
        tab_wiget_search_bar = current_tab->findChild<SearchBar*>(kCommandBufferSearchBarName);
        tab_wiget_search_button =
            current_tab->findChild<QPushButton*>(kCommandBufferSearchButtonName);
        if (!tab_wiget_search_bar->isHidden())
        {
            tab_wiget_search_bar->clearSearch();
            tab_wiget_search_bar->hide();
        }
        tab_wiget_search_button->show();
    }
    else if (current_index == m_tabs.gfxr_vulkan_command_arguments)
    {
        tab_wiget_search_bar =
            current_tab->findChild<SearchBar*>(kGfxrVulkanCommandArgumentsSearchBarName);
        tab_wiget_search_button =
            current_tab->findChild<QPushButton*>(kGfxrVulkanCommandArgumentsSearchButtonName);

        if (!tab_wiget_search_bar->isHidden())
        {
            tab_wiget_search_bar->clearSearch();
            tab_wiget_search_bar->hide();
        }
        tab_wiget_search_button->show();
    }
    else if (current_index == m_tabs.perf_counter)
    {
        tab_wiget_search_bar = current_tab->findChild<SearchBar*>(kPerfCounterSearchBarName);
        tab_wiget_search_button =
            current_tab->findChild<QPushButton*>(kPerfCounterSearchButtonName);

        if (!tab_wiget_search_bar->isHidden())
        {
            tab_wiget_search_bar->clearSearch();
            tab_wiget_search_bar->hide();
        }
        tab_wiget_search_button->show();
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::LoadAvailableMetrics()
{
    std::filesystem::path metrics_file_path =
        Dive::DeviceResourcesConstants::kProfilingPluginMetricsFileName;
    {
        absl::StatusOr<std::filesystem::path> ret =
            Dive::ResolveProfilingResourcesLocalPath(metrics_file_path);
        if (!ret.ok())
        {
            std::string err_msg = absl::StrFormat(
                "No available metrics CSV file to load, checked: %s", ret.status().message());
            qDebug() << err_msg.c_str();
            return;
        }
        metrics_file_path = *ret;
    }

    m_available_metrics = Dive::AvailableMetrics::LoadFromCsv(metrics_file_path);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::CreateActions()
{
    // Open file action
    m_open_action = new QAction(m_main_window_ptr->tr("&Open"), m_main_window_ptr);
    m_open_action->setIcon(QIcon(":/images/open.png"));
    m_open_action->setShortcuts(QKeySequence::Open);
    m_open_action->setStatusTip(m_main_window_ptr->tr("Open an existing capture"));
    QObject::connect(m_open_action, &QAction::triggered, m_main_window_ptr, &MainWindow::OnOpenFile);
    m_exit_action = new QAction(m_main_window_ptr->tr("E&xit"), m_main_window_ptr);
    m_exit_action->setShortcut(m_main_window_ptr->tr("Ctrl+Q"));
    m_exit_action->setStatusTip(m_main_window_ptr->tr("Exit the application"));
    QObject::connect(m_exit_action, SIGNAL(triggered()), m_main_window_ptr, SLOT(close()));

    // Save file action
    m_save_action = new QAction(m_main_window_ptr->tr("&Save"), m_main_window_ptr);
    m_save_action->setStatusTip(m_main_window_ptr->tr("Save the current capture"));
    m_save_action->setIcon(QIcon(":/images/save.png"));
    m_save_action->setShortcut(QKeySequence::Save);
    m_save_action->setEnabled(false);
    QObject::connect(m_save_action, &QAction::triggered, m_main_window_ptr, &MainWindow::OnSaveCapture);
    QObject::connect(m_main_window_ptr, &MainWindow::SetSaveMenuStatus, m_save_action, &QAction::setEnabled);
 
    // TODO (b/447422197) Show m_main_window_ptr action when the save/load system has been implemented.
    m_save_as_action = new QAction(m_main_window_ptr->tr("&Save As"), m_main_window_ptr);
    m_save_as_action->setStatusTip(m_main_window_ptr->tr("Save the current capture"));
    QObject::connect(m_save_as_action, &QAction::triggered, m_main_window_ptr, &MainWindow::OnSaveCapture);
    QObject::connect(m_main_window_ptr, &MainWindow::SetSaveAsMenuStatus, m_save_as_action, &QAction::setEnabled);

    // Recent file actions
    for (auto& action : m_recent_file_actions)
    {
        action = new QAction(m_main_window_ptr);
        action->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon));
        action->setVisible(false);
        QObject::connect(action, SIGNAL(triggered()), m_main_window_ptr, SLOT(OpenRecentFile()));
    }

    // Capture action
    m_capture_action = new QAction(m_main_window_ptr->tr("&Capture"), m_main_window_ptr);
    m_capture_action->setStatusTip(m_main_window_ptr->tr("Capture a Dive trace"));
    m_capture_action->setIcon(QIcon(":/images/capture.png"));
    m_capture_action->setShortcut(QKeySequence("f5"));
    QObject::connect(m_capture_action, &QAction::triggered, m_main_window_ptr, &MainWindow::OnNormalCapture);

    // Capture with delay action
    m_capture_delay_action = new QAction(m_main_window_ptr->tr("Capture with delay"), m_main_window_ptr);
    m_capture_delay_action->setStatusTip(m_main_window_ptr->tr("Capture a Dive trace after a delay"));
    m_capture_delay_action->setShortcut(QKeySequence("Ctrl+f5"));
    QObject::connect(m_capture_delay_action, &QAction::triggered, m_main_window_ptr, &MainWindow::OnCaptureTrigger);

    // Analyze action
    m_analyze_action = new QAction(m_main_window_ptr->tr("Analyze GFXR Capture"), m_main_window_ptr);
    m_analyze_action->setStatusTip(m_main_window_ptr->tr("Analyze currently loaded GFXR capture"));
    m_analyze_action->setIcon(QIcon(":/images/analyze.png"));
    m_analyze_action->setEnabled(false);
    m_analyze_action->setShortcut(QKeySequence("f7"));
    QObject::connect(m_analyze_action, &QAction::triggered, m_main_window_ptr, &MainWindow::OnAnalyzeCapture);

    // What If Setup action
    m_what_if_setup_action = new QAction(m_main_window_ptr->tr("What Ifs"), m_main_window_ptr);
    m_what_if_setup_action->setStatusTip(m_main_window_ptr->tr("Setup What If scenarios"));
    m_what_if_setup_action->setIcon(QIcon(":/images/what-if-light-bulb.svg"));
    m_what_if_setup_action->setShortcut(QKeySequence("f8"));
    QObject::connect(m_what_if_setup_action, &QAction::triggered, m_main_window_ptr, &MainWindow::OnWhatIfSetupTrigger);

    // Shortcuts action
    m_shortcuts_action = new QAction(m_main_window_ptr->tr("&Shortcuts"), m_main_window_ptr);
    m_shortcuts_action->setStatusTip(m_main_window_ptr->tr("Display application keyboard shortcuts"));
    QObject::connect(m_shortcuts_action, &QAction::triggered, m_main_window_ptr, &MainWindow::OnShortcuts);

    // About action
    m_about_action = new QAction(m_main_window_ptr->tr("&About Dive"), m_main_window_ptr);
    m_about_action->setStatusTip(m_main_window_ptr->tr("Display application version information"));
    QObject::connect(m_about_action, &QAction::triggered, m_main_window_ptr, &MainWindow::OnAbout);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::CreateMenus()
{
    // File Menu
    m_file_menu = m_main_window_ptr->menuBar()->addMenu(m_main_window_ptr->tr("&File"));
    m_file_menu->addAction(m_open_action);
    m_file_menu->addAction(m_save_action);

    // TODO (b/447422197) Show m_main_window_ptr action when the save/load system has been implemented.
    // m_file_menu->addAction(m_save_as_action);
    m_file_menu->addSeparator();
    m_recent_captures_menu = m_file_menu->addMenu(m_main_window_ptr->tr("Recent captures"));
    for (auto action : m_recent_file_actions) m_recent_captures_menu->addAction(action);
    m_file_menu->addSeparator();
    m_file_menu->addAction(m_exit_action);

    m_capture_menu = m_main_window_ptr->menuBar()->addMenu(m_main_window_ptr->tr("&Capture"));
    m_capture_menu->addAction(m_capture_action);

    m_analyze_menu = m_main_window_ptr->menuBar()->addMenu(m_main_window_ptr->tr("&Analyze"));
    m_analyze_menu->addAction(m_analyze_action);

    m_what_if_menu = m_main_window_ptr->menuBar()->addMenu(m_main_window_ptr->tr("&What Ifs"));
    m_what_if_menu->addAction(m_what_if_setup_action);

    m_help_menu = m_main_window_ptr->menuBar()->addMenu(m_main_window_ptr->tr("&Help"));
    m_help_menu->addAction(m_shortcuts_action);
    m_help_menu->addAction(m_about_action);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::CreateToolBars()
{
    QToolButton* open_button = new QToolButton(m_main_window_ptr);
    open_button->setPopupMode(QToolButton::MenuButtonPopup);
    open_button->setDefaultAction(m_open_action);
    open_button->setMenu(m_recent_captures_menu);

    m_file_tool_bar = m_main_window_ptr->addToolBar(m_main_window_ptr->tr("&File"));
    m_file_tool_bar->addWidget(open_button);
    m_file_tool_bar->addAction(m_save_action);
    m_file_tool_bar->addAction(m_capture_action);
    m_file_tool_bar->addAction(m_analyze_action);
    m_file_tool_bar->addAction(m_what_if_setup_action);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::CreateShortcuts()
{
    // Search Shortcut
    auto* search_shortcut = new QShortcut(QKeySequence(SHORTCUT_EVENTS_SEARCH), m_main_window_ptr);
    QObject::connect(search_shortcut, &QShortcut::activated, m_main_window_ptr, &MainWindow::OnSearchTrigger);

    // TabView Search Shortcut
    auto* search_tab_view_shortcut = new QShortcut(QKeySequence(SHORTCUT_TAB_VIEW_SEARCH), m_main_window_ptr);
    QObject::connect(search_tab_view_shortcut, &QShortcut::activated, [this]() {
        int current_tab_index = m_tab_widget->currentIndex();
        if (current_tab_index == m_tabs.command)
        {
            m_command_tab_view->OnSearchCommandBuffer();
        }
        else if (current_tab_index == m_tabs.gfxr_vulkan_command_arguments)
        {
            m_gfxr_vulkan_command_arguments_tab_view->OnSearchCommandArgs();
        }
        else if (current_tab_index == m_tabs.perf_counter)
        {
            m_perf_counter_tab_view->OnSearchCounters();
        }
        else
        {
            m_tab_widget->setCurrentIndex(m_tabs.command);
            m_command_tab_view->OnSearchCommandBuffer();
        }
        ResetEventSearchBar();
        if (m_correlated_capture_loaded)
        {
            ResetPm4EventSearchBar();
        }
    });

    // Overview Shortcut
    auto* overview_tab_shortcut = new QShortcut(QKeySequence(SHORTCUT_OVERVIEW_TAB), m_main_window_ptr);
    QObject::connect(overview_tab_shortcut, &QShortcut::activated,
            [this]() { m_tab_widget->setCurrentIndex(m_tabs.overview); });
    // Commands Shortcut
    auto* command_tab_shortcut = new QShortcut(QKeySequence(SHORTCUT_COMMANDS_TAB), m_main_window_ptr);
    QObject::connect(command_tab_shortcut, &QShortcut::activated,
            [this]() { m_tab_widget->setCurrentIndex(m_tabs.command); });
    // Shaders Shortcut
    auto* shader_tab_shortcut = new QShortcut(QKeySequence(SHORTCUT_SHADERS_TAB), m_main_window_ptr);
    QObject::connect(shader_tab_shortcut, &QShortcut::activated,
            [this]() { m_tab_widget->setCurrentIndex(m_tabs.shader); });
    // Event State Shortcut
    auto* event_state_tab_shortcut = new QShortcut(QKeySequence(SHORTCUT_EVENT_STATE_TAB), m_main_window_ptr);
    QObject::connect(event_state_tab_shortcut, &QShortcut::activated,
            [this]() { m_tab_widget->setCurrentIndex(m_tabs.event_state); });
    // Gfxr Vulkan Command Arguments Shortcut
    auto* gfxr_vulkan_command_arguments_tab_shortcut =
        new QShortcut(QKeySequence(SHORTCUT_GFXR_VULKAN_COMMAND_ARGUMENTS_TAB), m_main_window_ptr);
    QObject::connect(gfxr_vulkan_command_arguments_tab_shortcut, &QShortcut::activated, [this]() {
        if (m_tabs.gfxr_vulkan_command_arguments != -1)
        {
            m_tab_widget->setCurrentIndex(m_tabs.gfxr_vulkan_command_arguments);
        }
    });
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::CreateStatusBar()
{
    // Create status bar on the main window.
    m_status_bar = new QStatusBar(m_main_window_ptr);
    m_main_window_ptr->setStatusBar(m_status_bar);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::UpdateOverlay(const QString& message) { m_overlay->SetMessage(message); }

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnHideOverlay() { m_overlay->Clear(); }

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ShowTempStatus(const QString& status_message)
{
    m_status_bar->showMessage(status_message, kMessageTimeoutMs);
    m_status_bar->repaint();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ExpandResizeHierarchyView(DiveTreeView& tree_view,
                                           const QSortFilterProxyModel& model)
{
    tree_view.expandAll();
    // Set to -1 so that resizeColumnToContents() will consider *all* rows to determine amount
    // to resize. This can potentially be slow!
    // Then resize each column. This will also auto-adjust horizontal scroll bar size.
    tree_view.header()->setResizeContentsPrecision(-1);
    uint32_t column_count = (uint32_t)model.columnCount(QModelIndex());
    for (uint32_t column = 0; column < column_count; ++column)
        tree_view.resizeColumnToContents(column);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::SetCurrentFile(const QString& file_name, bool is_temp_file)
{
    QString shownName = m_main_window_ptr->tr("Untitled");
    if (!file_name.isEmpty() && is_temp_file == false)
    {
        shownName = StrippedName(file_name);

        QStringList recent_files = Settings::Get()->ReadRecentFiles();
        recent_files.removeAll(file_name);
        recent_files.prepend(file_name);
        Settings::Get()->WriteRecentFiles(recent_files);
        UpdateRecentFileActions(recent_files);
    }

    m_main_window_ptr->setWindowTitle(m_main_window_ptr->tr("%1[*] - %2").arg(shownName).arg(m_main_window_ptr->tr("Dive")));
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::UpdateRecentFileActions(QStringList recent_files)
{
    int next_file_index = 0;
    for (auto action : m_recent_file_actions)
    {
        int file_index = next_file_index++;
        if (file_index < recent_files.count())
        {
            QString text = m_main_window_ptr->tr("%1").arg(StrippedName(recent_files[file_index]));
            action->setText(text);
            action->setData(recent_files[file_index]);
            action->setVisible(true);
        }
        else
        {
            action->setVisible(false);
        }
    }
}

//--------------------------------------------------------------------------------------------------
QString MainWindowPrivate::StrippedName(const QString& fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::UpdateTabAvailability(TabMask mask)
{
    m_tabs_updating = true;
    SetTabAvailable(m_tab_widget, m_tabs.command, mask & TabMaskBits::kCommand);
    SetTabAvailable(m_tab_widget, m_tabs.shader, mask & TabMaskBits::kShader);
    SetTabAvailable(m_tab_widget, m_tabs.event_state, mask & TabMaskBits::kEventState);
    SetTabAvailable(m_tab_widget, m_tabs.gfxr_vulkan_command_arguments,
                    mask & TabMaskBits::kGfxrVulkanCommandArguments);
    SetTabAvailable(m_tab_widget, m_tabs.perf_counter, mask & TabMaskBits::kPerfCounters);
    SetTabAvailable(m_tab_widget, m_tabs.gpu_timing, mask & TabMaskBits::kGpuTiming);
    SetTabAvailable(m_tab_widget, m_tabs.frame, mask & TabMaskBits::kFrame);
    bool has_text = m_data_core->GetPm4CaptureData().GetNumText() > 0;
    SetTabAvailable(m_tab_widget, m_tabs.text_file, (mask & TabMaskBits::kTextFile) && has_text);
    // Disable overview at the end, so qt end up with a disabled tab instead of invisible one.
    if (m_tabs.overview >= 0)
    {
        m_tab_widget->setTabEnabled(m_tabs.overview, (mask & TabMaskBits::kOverview) > 0);
    }
    m_tabs_updating = false;

    m_main_window_ptr->OnTabViewChange();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnCrossReference(Dive::CrossRef ref)
{
    switch (ref.Type())
    {
        case Dive::CrossRefType::kShaderAddress:
            if (m_shader_view->OnCrossReference(ref)) m_tab_widget->setCurrentIndex(m_tabs.shader);
            break;
        case Dive::CrossRefType::kGFRIndex:
            m_command_hierarchy_view->setCurrentNode(ref.Id());
            break;
        default:
            // Ignore
            break;
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnSwitchToShaderTab()
{
    DIVE_ASSERT(m_tabs.shader >= 0);
    m_tab_widget->setCurrentIndex(m_tabs.shader);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnTabViewSearchBarVisibilityChange(bool isHidden)
{
    if (isHidden)
    {
        ResetEventSearchBar();
        if (m_correlated_capture_loaded)
        {
            ResetPm4EventSearchBar();
        }
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnTabViewChange()
{
    if (m_tabs_updating)
    {
        return;
    }

    int current_index = m_tab_widget->currentIndex();

    // If no current index is selected, return.
    if (current_index == -1)
    {
        return;
    }

    // Check if there was a previous tab search that needs to be disabled.
    if (m_previous_tab_index != -1 && m_previous_tab_index != current_index)
    {
        QWidget* previous_tab = m_tab_widget->widget(m_previous_tab_index);
        if (previous_tab)
        {
            if (m_previous_tab_index == m_tabs.command)
            {
                m_command_tab_view->OnSearchBarVisibilityChange(true);
            }
            else if (m_previous_tab_index == m_tabs.gfxr_vulkan_command_arguments)
            {
                m_gfxr_vulkan_command_arguments_tab_view->OnSearchBarVisibilityChange(true);
            }
            else if (m_previous_tab_index == m_tabs.perf_counter)
            {
                m_perf_counter_tab_view->OnSearchBarVisibilityChange(true);
            }
        }
    }

    QWidget* current_tab = m_tab_widget->widget(current_index);
    if (current_index == m_tabs.command &&
        !current_tab->findChild<SearchBar*>(kCommandBufferSearchBarName)->isHidden())
    {
        ResetEventSearchBar();
        if (m_correlated_capture_loaded)
        {
            ResetPm4EventSearchBar();
        }
    }
    else if (current_index == m_tabs.gfxr_vulkan_command_arguments &&
             current_tab->findChild<SearchBar*>(kGfxrVulkanCommandArgumentsSearchBarName))
    {
        if (!current_tab->findChild<SearchBar*>(kGfxrVulkanCommandArgumentsSearchBarName)
                 ->isHidden())
        {
            ResetEventSearchBar();
            if (m_correlated_capture_loaded)
            {
                ResetPm4EventSearchBar();
            }
        }
    }
    else if (current_index == m_tabs.perf_counter &&
             current_tab->findChild<SearchBar*>(kPerfCounterSearchBarName))
    {
        if (!current_tab->findChild<SearchBar*>(kPerfCounterSearchBarName)->isHidden())
        {
            ResetEventSearchBar();
            if (m_correlated_capture_loaded)
            {
                ResetPm4EventSearchBar();
            }
        }
    }
    else
    {
        m_command_tab_view->OnSearchBarVisibilityChange(true);
    }

    m_previous_tab_index = current_index;
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ConnectSearchBar()
{
    QObject::connect(m_event_search_bar, SIGNAL(new_search(const QString&)),
                     m_command_hierarchy_view, SLOT(searchNodeByText(const QString&)));
    QObject::connect(m_event_search_bar, &SearchBar::next_search, m_command_hierarchy_view,
                     &DiveTreeView::nextNodeInSearch);
    QObject::connect(m_event_search_bar, &SearchBar::prev_search, m_command_hierarchy_view,
                     &DiveTreeView::prevNodeInSearch);
    QObject::connect(m_command_hierarchy_view, &DiveTreeView::updateSearch, m_event_search_bar,
                     &SearchBar::updateSearchResults);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::DisconnectSearchBar()
{
    QObject::disconnect(m_event_search_bar, SIGNAL(new_search(const QString&)),
                        m_command_hierarchy_view, SLOT(searchNodeByText(const QString&)));
    QObject::disconnect(m_event_search_bar, &SearchBar::next_search, m_command_hierarchy_view,
                        &DiveTreeView::nextNodeInSearch);
    QObject::disconnect(m_event_search_bar, &SearchBar::prev_search, m_command_hierarchy_view,
                        &DiveTreeView::prevNodeInSearch);
    QObject::disconnect(m_command_hierarchy_view, &DiveTreeView::updateSearch, m_event_search_bar,
                        &SearchBar::updateSearchResults);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ConnectPm4SearchBar()
{
    QObject::connect(m_pm4_event_search_bar, SIGNAL(new_search(const QString&)),
                     m_pm4_command_hierarchy_view, SLOT(searchNodeByText(const QString&)));
    QObject::connect(m_pm4_event_search_bar, &SearchBar::next_search, m_pm4_command_hierarchy_view,
                     &DiveTreeView::nextNodeInSearch);
    QObject::connect(m_pm4_event_search_bar, &SearchBar::prev_search, m_pm4_command_hierarchy_view,
                     &DiveTreeView::prevNodeInSearch);
    QObject::connect(m_pm4_command_hierarchy_view, &DiveTreeView::updateSearch,
                     m_pm4_event_search_bar, &SearchBar::updateSearchResults);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::DisconnectPm4SearchBar()
{
    QObject::disconnect(m_pm4_event_search_bar, SIGNAL(new_search(const QString&)),
                        m_pm4_command_hierarchy_view, SLOT(searchNodeByText(const QString&)));
    QObject::disconnect(m_pm4_event_search_bar, &SearchBar::next_search,
                        m_pm4_command_hierarchy_view, &DiveTreeView::nextNodeInSearch);
    QObject::disconnect(m_pm4_event_search_bar, &SearchBar::prev_search,
                        m_pm4_command_hierarchy_view, &DiveTreeView::prevNodeInSearch);
    QObject::disconnect(m_pm4_command_hierarchy_view, &DiveTreeView::updateSearch,
                        m_pm4_event_search_bar, &SearchBar::updateSearchResults);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::DisconnectAllTabs()
{
    // Get the current selection models before they potentially change.
    QItemSelectionModel* current_selection_model = m_command_hierarchy_view->selectionModel();
    QItemSelectionModel* current_pm4_selection_model =
        m_pm4_command_hierarchy_view->selectionModel();

    // Disconnect ALL signals from the selection models to all slots.
    if (current_selection_model)
    {
        QObject::disconnect(current_selection_model, nullptr, nullptr, nullptr);
    }

    if (current_pm4_selection_model)
    {
        QObject::disconnect(current_pm4_selection_model, nullptr, nullptr, nullptr);
    }

    foreach (auto expand_to_lvl_button, m_expand_to_lvl_buttons)
    {
        QObject::disconnect(expand_to_lvl_button, SIGNAL(clicked()), m_main_window_ptr, SLOT(m_main_window_ptr->OnExpandToLevel()));
    }

    QObject::disconnect(m_view_mode_combo_box, SIGNAL(currentTextChanged(const QString&)), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnCommandViewModeChange(const QString&)));
    QObject::disconnect(m_view_mode_combo_box, SIGNAL(textHighlighted(const QString&)), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnCommandViewModeComboBoxHover(const QString&)));

    QObject::disconnect(m_command_hierarchy_view, &DiveTreeView::expanded, m_command_hierarchy_view,
                        &DiveTreeView::expandNode);
    QObject::disconnect(m_command_hierarchy_view, &DiveTreeView::collapsed,
                        m_command_hierarchy_view, &DiveTreeView::collapseNode);
    QObject::disconnect(m_prev_event_button, &QPushButton::clicked, m_command_hierarchy_view,
                        &DiveTreeView::gotoPrevEvent);
    QObject::disconnect(m_next_event_button, &QPushButton::clicked, m_command_hierarchy_view,
                        &DiveTreeView::gotoNextEvent);

    QObject::disconnect(m_property_panel, &PropertyPanel::crossReference, m_main_window_ptr,
                        &MainWindow::OnCrossReference);
    QObject::disconnect(m_event_selection, &EventSelection::crossReference, m_main_window_ptr,
                        &MainWindow::OnCrossReference);
    QObject::disconnect(m_event_selection, &EventSelection::currentNodeChanged,
                        m_command_hierarchy_view, &DiveTreeView::setCurrentNode);

    QObject::disconnect(m_command_hierarchy_view,
                        SIGNAL(sourceCurrentChanged(const QModelIndex&, const QModelIndex&)),
                        m_command_tab_view, SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::disconnect(m_command_hierarchy_view->selectionModel(),
                        SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::disconnect(m_command_hierarchy_view, &QTreeView::customContextMenuRequested, m_main_window_ptr,
                        &MainWindow::OnOpenVulkanDrawCallMenu);

    foreach (auto expand_to_lvl_button, m_pm4_expand_to_lvl_buttons)
    {
        QObject::disconnect(expand_to_lvl_button, SIGNAL(clicked()), m_main_window_ptr, SLOT(m_main_window_ptr->OnExpandToLevel()));
    }

    QObject::disconnect(m_pm4_view_mode_combo_box, SIGNAL(currentTextChanged(const QString&)), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnCommandViewModeChange(const QString&)));
    QObject::disconnect(m_pm4_view_mode_combo_box, SIGNAL(textHighlighted(const QString&)), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnCommandViewModeComboBoxHover(const QString&)));

    QObject::disconnect(m_pm4_filter_mode_combo_box, SIGNAL(currentTextChanged(const QString&)),
                        m_main_window_ptr, SLOT(m_main_window_ptr->OnFilterModeChange(const QString&)));

    QObject::disconnect(m_pm4_search_trigger_button, SIGNAL(clicked()), m_main_window_ptr,
                        SLOT(OnSearchTrigger()));

    QObject::disconnect(m_pm4_command_hierarchy_view, &DiveTreeView::expanded,
                        m_pm4_command_hierarchy_view, &DiveTreeView::expandNode);
    QObject::disconnect(m_pm4_command_hierarchy_view, &DiveTreeView::collapsed,
                        m_pm4_command_hierarchy_view, &DiveTreeView::collapseNode);
    QObject::disconnect(m_event_selection, &EventSelection::currentNodeChanged,
                        m_pm4_command_hierarchy_view, &DiveTreeView::setCurrentNode);
    QObject::disconnect(m_pm4_prev_event_button, &QPushButton::clicked,
                        m_pm4_command_hierarchy_view, &DiveTreeView::gotoPrevEvent);
    QObject::disconnect(m_pm4_next_event_button, &QPushButton::clicked,
                        m_pm4_command_hierarchy_view, &DiveTreeView::gotoNextEvent);

    QObject::disconnect(m_pm4_command_hierarchy_view,
                        SIGNAL(sourceCurrentChanged(const QModelIndex&, const QModelIndex&)),
                        m_command_tab_view, SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::disconnect(m_pm4_command_hierarchy_view->selectionModel(),
                        SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
                        m_command_tab_view, SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::disconnect(m_pm4_command_hierarchy_view->selectionModel(),
                        SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::disconnect(m_pm4_command_hierarchy_view->selectionModel(),
                        SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnCorrelatePm4DrawCall(const QModelIndex&)));

    QObject::disconnect(m_command_tab_view, SIGNAL(HideOtherSearchBars()), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnTabViewChange()));

    QObject::disconnect(m_command_tab_view, SIGNAL(SendNodeProperty(const QString&)),
                        m_property_panel, SLOT(OnSelectionInfoChange(const QString&)));

    QObject::disconnect(m_main_window_ptr, SIGNAL(m_main_window_ptr->EventSelected(uint64_t)), m_shader_view,
                        SLOT(OnEventSelected(uint64_t)));

    QObject::disconnect(m_main_window_ptr, SIGNAL(m_main_window_ptr->EventSelected(uint64_t)), m_event_state_view,
                        SLOT(OnEventSelected(uint64_t)));

    QObject::disconnect(m_command_hierarchy_view->selectionModel(),
                        SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
                        m_gfxr_vulkan_command_arguments_tab_view,
                        SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::disconnect(m_command_hierarchy_view->selectionModel(),
                        SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnCorrelateVulkanDrawCall(const QModelIndex&)));

    QObject::disconnect(m_gfxr_vulkan_command_arguments_tab_view, SIGNAL(HideOtherSearchBars()),
                        m_main_window_ptr, SLOT(m_main_window_ptr->OnTabViewChange()));

    QObject::disconnect(m_perf_counter_tab_view, SIGNAL(HideOtherSearchBars()), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnTabViewChange()));

    QObject::disconnect(m_perf_counter_tab_view, &PerfCounterTabView::CounterSelected, m_main_window_ptr,
                        &MainWindow::OnCounterSelected);

    QObject::disconnect(m_gpu_timing_tab_view, &GpuTimingTabView::GpuTimingDataSelected, m_main_window_ptr,
                        &MainWindow::OnGpuTimingDataSelected);

    QObject::disconnect(m_filter_mode_combo_box, SIGNAL(currentTextChanged(const QString&)), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnFilterModeChange(const QString&)));

    QObject::disconnect(m_filter_gfxr_commands_combo_box, SIGNAL(FilterChanged()), m_main_window_ptr,
                        SLOT(m_main_window_ptr->OnGfxrFilterModeChange()));

    // Temporarily set the model to nullptr and clear selection/current index
    // before loading new data. This forces a clean break.
    m_command_hierarchy_view->setModel(nullptr);
    m_pm4_command_hierarchy_view->setModel(nullptr);

    if (current_selection_model)
    {
        current_selection_model->clearSelection();
    }

    if (current_pm4_selection_model)
    {
        current_pm4_selection_model->clearSelection();
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ConnectDiveFileTabs()
{
    // Left Panel
    foreach (auto expand_to_lvl_button, m_expand_to_lvl_buttons)
    {
        QObject::connect(expand_to_lvl_button, SIGNAL(clicked()), m_main_window_ptr, SLOT(m_main_window_ptr->OnExpandToLevel()));
    }

    QObject::connect(m_command_hierarchy_view, &DiveTreeView::expanded, m_command_hierarchy_view,
                     &DiveTreeView::expandNode);

    QObject::connect(m_command_hierarchy_view, &DiveTreeView::collapsed, m_command_hierarchy_view,
                     &DiveTreeView::collapseNode);

    QObject::connect(m_event_selection, &EventSelection::currentNodeChanged,
                     m_command_hierarchy_view, &DiveTreeView::setCurrentNode);

    // Buttons
    QObject::connect(m_prev_event_button, &QPushButton::clicked, m_command_hierarchy_view,
                     &DiveTreeView::gotoPrevEvent);
    QObject::connect(m_next_event_button, &QPushButton::clicked, m_command_hierarchy_view,
                     &DiveTreeView::gotoNextEvent);

    // Tabs
    QObject::connect(m_command_hierarchy_view,
                     SIGNAL(sourceCurrentChanged(const QModelIndex&, const QModelIndex&)),
                     m_gfxr_vulkan_command_arguments_tab_view,
                     SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::connect(m_command_hierarchy_view->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
                     m_gfxr_vulkan_command_arguments_tab_view,
                     SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    // Correlate between two calls
    QObject::connect(m_command_hierarchy_view->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnCorrelateVulkanDrawCall(const QModelIndex&)));

    QObject::connect(m_command_hierarchy_view, &QTreeView::customContextMenuRequested, m_main_window_ptr,
                     &MainWindow::OnOpenVulkanDrawCallMenu);

    QObject::connect(m_property_panel, &PropertyPanel::crossReference, m_main_window_ptr,
                     &MainWindow::OnCrossReference);
    QObject::connect(m_event_selection, &EventSelection::crossReference, m_main_window_ptr,
                     &MainWindow::OnCrossReference);

    // Middle Panel
    foreach (auto expand_to_lvl_button, m_pm4_expand_to_lvl_buttons)
    {
        QObject::connect(expand_to_lvl_button, SIGNAL(clicked()), m_main_window_ptr, SLOT(m_main_window_ptr->OnExpandToLevel()));
    }

    QObject::connect(m_pm4_command_hierarchy_view->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::connect(m_pm4_command_hierarchy_view, &DiveTreeView::expanded,
                     m_pm4_command_hierarchy_view, &DiveTreeView::expandNode);
    QObject::connect(m_pm4_command_hierarchy_view, &DiveTreeView::collapsed,
                     m_pm4_command_hierarchy_view, &DiveTreeView::collapseNode);
    QObject::connect(m_event_selection, &EventSelection::currentNodeChanged,
                     m_pm4_command_hierarchy_view, &DiveTreeView::setCurrentNode);

    // Combo Boxes
    QObject::connect(m_pm4_view_mode_combo_box, SIGNAL(currentTextChanged(const QString&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnCommandViewModeChange(const QString&)));

    QObject::connect(m_pm4_view_mode_combo_box, SIGNAL(textHighlighted(const QString&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnCommandViewModeComboBoxHover(const QString&)));

    QObject::connect(m_pm4_filter_mode_combo_box, SIGNAL(currentTextChanged(const QString&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnFilterModeChange(const QString&)));

    QObject::connect(m_filter_gfxr_commands_combo_box, SIGNAL(FilterChanged()), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnGfxrFilterModeChange()));

    // Buttons
    QObject::connect(m_pm4_search_trigger_button, SIGNAL(clicked()), m_main_window_ptr, SLOT(OnSearchTrigger()));

    QObject::connect(m_pm4_prev_event_button, &QPushButton::clicked, m_pm4_command_hierarchy_view,
                     &DiveTreeView::gotoPrevEvent);

    QObject::connect(m_pm4_next_event_button, &QPushButton::clicked, m_pm4_command_hierarchy_view,
                     &DiveTreeView::gotoNextEvent);

    // Tabs
    QObject::connect(m_pm4_command_hierarchy_view,
                     SIGNAL(sourceCurrentChanged(const QModelIndex&, const QModelIndex&)),
                     m_command_tab_view, SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::connect(m_pm4_command_hierarchy_view->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
                     m_command_tab_view, SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::connect(m_command_tab_view, SIGNAL(HideOtherSearchBars()), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnTabViewChange()));

    QObject::connect(m_perf_counter_tab_view, SIGNAL(HideOtherSearchBars()), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnTabViewChange()));

    QObject::connect(m_command_tab_view, SIGNAL(SendNodeProperty(const QString&)), m_property_panel,
                     SLOT(OnSelectionInfoChange(const QString&)));

    QObject::connect(m_main_window_ptr, SIGNAL(m_main_window_ptr->EventSelected(uint64_t)), m_shader_view,
                     SLOT(OnEventSelected(uint64_t)));

    QObject::connect(m_main_window_ptr, SIGNAL(m_main_window_ptr->EventSelected(uint64_t)), m_event_state_view,
                     SLOT(OnEventSelected(uint64_t)));

    QObject::connect(m_gfxr_vulkan_command_arguments_tab_view, SIGNAL(HideOtherSearchBars()), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnTabViewChange()));

    QObject::connect(m_perf_counter_tab_view, &PerfCounterTabView::CounterSelected, m_main_window_ptr,
                     &MainWindow::OnCounterSelected);

    QObject::connect(m_gpu_timing_tab_view, &GpuTimingTabView::GpuTimingDataSelected, m_main_window_ptr,
                     &MainWindow::OnGpuTimingDataSelected);

    // Correlate between two calls
    QObject::connect(m_pm4_command_hierarchy_view->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnCorrelatePm4DrawCall(const QModelIndex&)));
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ConnectAdrenoRdFileTabs()
{
    foreach (auto expand_to_lvl_button, m_expand_to_lvl_buttons)
    {
        QObject::connect(expand_to_lvl_button, SIGNAL(clicked()), m_main_window_ptr, SLOT(m_main_window_ptr->OnExpandToLevel()));
    }

    QObject::connect(m_command_hierarchy_view, &DiveTreeView::expanded, m_command_hierarchy_view,
                     &DiveTreeView::expandNode);
    QObject::connect(m_command_hierarchy_view, &DiveTreeView::collapsed, m_command_hierarchy_view,
                     &DiveTreeView::collapseNode);
    QObject::connect(m_event_selection, &EventSelection::currentNodeChanged,
                     m_command_hierarchy_view, &DiveTreeView::setCurrentNode);

    // Combo Boxes
    QObject::connect(m_view_mode_combo_box, SIGNAL(currentTextChanged(const QString&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnCommandViewModeChange(const QString&)));
    QObject::connect(m_view_mode_combo_box, SIGNAL(textHighlighted(const QString&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnCommandViewModeComboBoxHover(const QString&)));
    QObject::connect(m_filter_mode_combo_box, SIGNAL(currentTextChanged(const QString&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnFilterModeChange(const QString&)));

    // Tabs
    QObject::connect(m_command_hierarchy_view,
                     SIGNAL(sourceCurrentChanged(const QModelIndex&, const QModelIndex&)),
                     m_command_tab_view, SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::connect(m_command_hierarchy_view->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::connect(m_command_tab_view, SIGNAL(HideOtherSearchBars()), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnTabViewChange()));

    QObject::connect(m_command_tab_view, SIGNAL(SendNodeProperty(const QString&)), m_property_panel,
                     SLOT(OnSelectionInfoChange(const QString&)));

    QObject::connect(m_main_window_ptr, SIGNAL(m_main_window_ptr->EventSelected(uint64_t)), m_shader_view,
                     SLOT(OnEventSelected(uint64_t)));

    QObject::connect(m_main_window_ptr, SIGNAL(m_main_window_ptr->EventSelected(uint64_t)), m_event_state_view,
                     SLOT(OnEventSelected(uint64_t)));

    // Buttons
    QObject::connect(m_prev_event_button, &QPushButton::clicked, m_command_hierarchy_view,
                     &DiveTreeView::gotoPrevEvent);
    QObject::connect(m_next_event_button, &QPushButton::clicked, m_command_hierarchy_view,
                     &DiveTreeView::gotoNextEvent);

    QObject::connect(m_property_panel, &PropertyPanel::crossReference, m_main_window_ptr,
                     &MainWindow::OnCrossReference);
    QObject::connect(m_event_selection, &EventSelection::crossReference, m_main_window_ptr,
                     &MainWindow::OnCrossReference);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ConnectGfxrFileTabs()
{
    QObject::connect(m_command_hierarchy_view,
                     SIGNAL(sourceCurrentChanged(const QModelIndex&, const QModelIndex&)),
                     m_gfxr_vulkan_command_arguments_tab_view,
                     SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::connect(m_command_hierarchy_view->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
                     m_gfxr_vulkan_command_arguments_tab_view,
                     SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    QObject::connect(m_command_hierarchy_view->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnSelectionChanged(const QModelIndex&)));

    // Tabs
    QObject::connect(m_gfxr_vulkan_command_arguments_tab_view, SIGNAL(HideOtherSearchBars()), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnTabViewChange()));

    QObject::connect(m_perf_counter_tab_view, SIGNAL(HideOtherSearchBars()), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnTabViewChange()));

    QObject::connect(m_perf_counter_tab_view, &PerfCounterTabView::CounterSelected, m_main_window_ptr,
                     &MainWindow::OnCounterSelected);

    QObject::connect(m_gpu_timing_tab_view, &GpuTimingTabView::GpuTimingDataSelected, m_main_window_ptr,
                     &MainWindow::OnGpuTimingDataSelected);

    // Combo Boxes
    QObject::connect(m_filter_gfxr_commands_combo_box, SIGNAL(FilterChanged()), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnGfxrFilterModeChange()));
    // Buttons
    QObject::connect(m_command_hierarchy_view, &DiveTreeView::expanded, m_command_hierarchy_view,
                     &DiveTreeView::expandNode);

    QObject::connect(m_command_hierarchy_view, &DiveTreeView::collapsed, m_command_hierarchy_view,
                     &DiveTreeView::collapseNode);

    QObject::connect(m_event_selection, &EventSelection::currentNodeChanged,
                     m_command_hierarchy_view, &DiveTreeView::setCurrentNode);

    QObject::connect(m_prev_event_button, &QPushButton::clicked, m_command_hierarchy_view,
                     &DiveTreeView::gotoPrevEvent);

    QObject::connect(m_next_event_button, &QPushButton::clicked, m_command_hierarchy_view,
                     &DiveTreeView::gotoNextEvent);

    // Correlate calls
    QObject::connect(m_command_hierarchy_view->selectionModel(),
                     SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), m_main_window_ptr,
                     SLOT(m_main_window_ptr->OnCorrelateVulkanDrawCall(const QModelIndex&)));

    // Menus
    QObject::connect(m_command_hierarchy_view, &QTreeView::customContextMenuRequested, m_main_window_ptr,
                     &MainWindow::OnOpenVulkanDrawCallMenu);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnCaptureUpdated(const QString& file_path)
{
    const std::string file_path_std_str = file_path.toStdString();
    const char* file_path_str = file_path_std_str.c_str();
    if (!m_main_window_ptr->LoadFile(file_path_str, /*is_temp_file*/ false, /*async*/ true))
    {
        return;
    }
    qDebug() << "Successfully updated capture to: " << file_path;
}

//--------------------------------------------------------------------------------------------------

QModelIndex MainWindowPrivate::FindSourceIndexFromNode(QAbstractItemModel* model,
                                                 uint64_t target_node_index)
{
    return FindSourceIndexFromNode(model, target_node_index, QModelIndex());
}
QModelIndex MainWindowPrivate::FindSourceIndexFromNode(QAbstractItemModel* model,
                                                 uint64_t target_node_index,
                                                 const QModelIndex& parent)
{
    if (!model) return QModelIndex();

    for (int r = 0; r < model->rowCount(parent); ++r)
    {
        QModelIndex index = model->index(r, 0, parent);
        if (index.isValid() && index.internalId() == target_node_index)
        {
            return index;
        }
        if (model->hasChildren(index))
        {
            QModelIndex result = FindSourceIndexFromNode(model, target_node_index, index);
            if (result.isValid())
            {
                return result;
            }
        }
    }
    return QModelIndex();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnOpenVulkanDrawCallMenu(const QPoint& pos)
{
    m_gfxr_vulkan_commands_filter_proxy_model->CollectGfxrDrawCallIndices();
    QModelIndex vulkan_draw_call_index = m_command_hierarchy_view->indexAt(pos);
    QModelIndex source_index =
        m_gfxr_vulkan_commands_filter_proxy_model->mapToSource(vulkan_draw_call_index);
    uint64_t node_index = source_index.internalId();

    if ((!source_index.isValid()) || (m_data_core->GetCommandHierarchy().GetNodeType(node_index) !=
                                      Dive::NodeType::kGfxrVulkanDrawCommandNode))
    {
        // Check if requesting a menu for a BeginCommandBuffer or BeginRenderPass node.
        m_main_window_ptr->OnOpenVulkanCallMenu(pos);
        return;
    }

    std::vector<uint64_t> gfxr_draw_call_indices =
        qobject_cast<GfxrVulkanCommandFilterProxyModel*>(m_command_hierarchy_view->model())
            ->GetGfxrDrawCallIndices();
    auto it = std::find(gfxr_draw_call_indices.begin(), gfxr_draw_call_indices.end(), node_index);

    if (it == gfxr_draw_call_indices.end())
    {
        QMessageBox::critical(m_main_window_ptr, "Correlation Failed", "Corresponding perf counter not found.");
        return;
    }

    uint64_t found_gfxr_draw_call_index = std::distance(gfxr_draw_call_indices.begin(), it);

    QMenu context_menu;

    auto context_menu_options = m_correlated_capture_loaded
                                    ? absl::MakeSpan(kCorrelatedContextOptions)
                                    : absl::MakeSpan(kNonCorrelatedContextOptions);
    for (auto opt : context_menu_options)
    {
        QAction* action = context_menu.addAction(ToQString(opt));
        action->setData(static_cast<int>(opt));
    }

    QAction* selected_action =
        context_menu.exec(m_command_hierarchy_view->viewport()->mapToGlobal(pos));

    // Ensures that if the user clicks outside of the context menu, a seg fault does not occur since
    // it is interpreted as a selection.
    if (selected_action == nullptr)
    {
        return;
    }

    QVariant selected_action_data = selected_action->data();
    switch (static_cast<DrawCallContextMenuOption>(selected_action_data.toInt()))
    {
        case DrawCallContextMenuOption::kUnknown:
            break;
        case DrawCallContextMenuOption::kArguments:
            m_tab_widget->setCurrentIndex(m_tabs.gfxr_vulkan_command_arguments);
            m_main_window_ptr->OnCorrelationFilterApplied(found_gfxr_draw_call_index, vulkan_draw_call_index);
            break;
        case DrawCallContextMenuOption::kBinningPassOnly:
            m_pm4_filter_mode_combo_box->setCurrentIndex(DiveFilterModel::kBinningPassOnly);
            m_main_window_ptr->OnCorrelationFilterApplied(found_gfxr_draw_call_index, vulkan_draw_call_index);
            break;
        case DrawCallContextMenuOption::kFirstTilePassOnly:
            m_pm4_filter_mode_combo_box->setCurrentIndex(DiveFilterModel::kFirstTilePassOnly);
            m_main_window_ptr->OnCorrelationFilterApplied(found_gfxr_draw_call_index, vulkan_draw_call_index);
            break;
        case DrawCallContextMenuOption::kPerfCounterData:
            m_tab_widget->setCurrentIndex(m_tabs.perf_counter);
            break;
        case DrawCallContextMenuOption::kGpuTimeData:
            m_tab_widget->setCurrentIndex(m_tabs.gpu_timing);
            break;
    }
}

void MainWindowPrivate::OnCorrelationFilterApplied(uint64_t gfxr_draw_call_index,
                                            const QModelIndex& vulkan_draw_call_model_index)
{
    std::vector<uint64_t> pm4_draw_call_indices =
        qobject_cast<DiveFilterModel*>(m_pm4_command_hierarchy_view->model())
            ->GetPm4DrawCallIndices();

    uint64_t corresponding_pm4_draw_call_index = pm4_draw_call_indices.at(gfxr_draw_call_index);

    QAbstractItemModel* source_model = m_filter_model->sourceModel();

    QModelIndex source_index =
        FindSourceIndexFromNode(source_model, corresponding_pm4_draw_call_index);

    if (source_index.isValid())
    {
        QModelIndex proxy_index = m_filter_model->mapFromSource(source_index);

        if (proxy_index.isValid())
        {
            QItemSelectionModel* selection_model = m_pm4_command_hierarchy_view->selectionModel();
            QSignalBlocker pm4_view_blocker(selection_model);

            QItemSelectionModel::SelectionFlags flags =
                QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows;

            selection_model->setCurrentIndex(proxy_index, flags);
            m_command_tab_view->OnSelectionChanged(proxy_index);

            m_pm4_command_hierarchy_view->scrollTo(proxy_index,
                                                   QAbstractItemView::PositionAtCenter);
            m_pm4_command_hierarchy_view->expand(proxy_index);

            m_pm4_command_hierarchy_view->viewport()->update();
        }
    }

    QItemSelectionModel* gfxr_selection_model = m_command_hierarchy_view->selectionModel();
    QSignalBlocker gfxr_view_blocker(gfxr_selection_model);

    QItemSelectionModel::SelectionFlags flags =
        QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows;

    gfxr_selection_model->setCurrentIndex(vulkan_draw_call_model_index, flags);

    ResetVerticalScroll(*m_command_hierarchy_view);
    m_command_hierarchy_view->scrollTo(vulkan_draw_call_model_index,
                                       QAbstractItemView::PositionAtCenter);
    m_command_hierarchy_view->expand(vulkan_draw_call_model_index);

    m_command_hierarchy_view->viewport()->update();

    CorrelateCounter(vulkan_draw_call_model_index, true);

    ResetHorizontalScroll(*m_pm4_command_hierarchy_view);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnOpenVulkanCallMenu(const QPoint& pos)
{
    QModelIndex source_index = m_gfxr_vulkan_commands_filter_proxy_model->mapToSource(
        m_command_hierarchy_view->indexAt(pos));
    uint64_t node_index = source_index.internalId();

    std::string node_desc = m_data_core->GetCommandHierarchy().GetNodeDesc(node_index);
    Dive::NodeType node_type = m_data_core->GetCommandHierarchy().GetNodeType(node_index);

    // Only the BeginCommandBuffer and BeginRenderPass calls are used for correlation
    if ((!source_index.isValid()) ||
        ((node_type != Dive::NodeType::kGfxrVulkanBeginCommandBufferNode) &&
         (node_type != Dive::NodeType::kGfxrVulkanBeginRenderPassCommandNode) &&
         (node_type != Dive::NodeType::kGfxrRootFrameNode)))
    {
        return;
    }

    QMenu context_menu;
    for (auto opt : kCommandBufferContextOptions)
    {
        QAction* action = context_menu.addAction(ToQString(opt));
        action->setData(static_cast<int>(opt));
    }

    QAction* selected_action =
        context_menu.exec(m_command_hierarchy_view->viewport()->mapToGlobal(pos));

    // Ensures that if the user clicks outside of the context menu, a seg fault does not occur since
    // it is interpreted as a selection.
    if (selected_action == nullptr)
    {
        return;
    }

    QVariant selected_action_data = selected_action->data();
    switch (static_cast<DrawCallContextMenuOption>(selected_action_data.toInt()))
    {
        case DrawCallContextMenuOption::kUnknown:
        case DrawCallContextMenuOption::kBinningPassOnly:
        case DrawCallContextMenuOption::kFirstTilePassOnly:
        case DrawCallContextMenuOption::kPerfCounterData:
            break;
        case DrawCallContextMenuOption::kArguments:
            m_tab_widget->setCurrentIndex(m_tabs.gfxr_vulkan_command_arguments);
            break;
        case DrawCallContextMenuOption::kGpuTimeData:
            m_tab_widget->setCurrentIndex(m_tabs.gpu_timing);
            break;
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::ClearViewModelSelection(DiveTreeView& tree_view, bool should_clear_tab)
{
    QItemSelectionModel* selection_model = tree_view.selectionModel();
    if (selection_model)
    {
        QSignalBlocker blocker(selection_model);
        selection_model->clear();
        QItemSelectionModel::SelectionFlags flags =
            QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows;
        selection_model->setCurrentIndex(QModelIndex(), flags);
    }

    if (should_clear_tab && (m_correlated_capture_loaded || m_gfxr_capture_loaded))
    {
        m_perf_counter_tab_view->ClearSelection();
    }

    tree_view.viewport()->update();
}

//--------------------------------------------------------------------------------------------------
std::optional<uint64_t> MainWindowPrivate::GetDrawCallIndexFromProxyIndex(
    const QModelIndex& proxy_index, const QAbstractProxyModel& proxy_model,
    const std::vector<uint64_t>& draw_call_indices, CorrelationTarget target)
{
    QModelIndex source_index = proxy_model.mapToSource(proxy_index);
    if (!source_index.isValid())
    {
        return std::nullopt;
    }

    uint64_t node_index = source_index.internalId();
    const Dive::CommandHierarchy& command_hierarchy = m_data_core->GetCommandHierarchy();
    Dive::NodeType node_type = command_hierarchy.GetNodeType(node_index);
    bool type_is_valid = false;

    if (target == CorrelationTarget::kGfxrDrawCall)
    {
        type_is_valid = (node_type == Dive::NodeType::kGfxrVulkanDrawCommandNode);
    }
    else if (target == CorrelationTarget::kPm4DrawCall)
    {
        type_is_valid = false;
        if (node_type == Dive::NodeType::kEventNode)
        {
            Dive::Util::EventType type = command_hierarchy.GetEventNodeType(node_index);
            if (type == Dive::Util::EventType::kDraw || type == Dive::Util::EventType::kDispatch)
                type_is_valid = true;
        }
    }

    if (!type_is_valid)
    {
        return std::nullopt;
    }

    auto it = std::find(draw_call_indices.begin(), draw_call_indices.end(), node_index);

    if (it == draw_call_indices.end())
    {
        return std::nullopt;
    }

    return std::distance(draw_call_indices.begin(), it);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnCorrelateVulkanDrawCall(const QModelIndex& index)
{
    m_gpu_timing_tab_view->ClearSelection();
    m_perf_counter_tab_view->ClearSelection();
    QModelIndex source_index = m_gfxr_vulkan_commands_filter_proxy_model->mapToSource(index);

    // Check if the selected node is a GPU timing node. If so, do not correlate with the PM4 view
    // and performance counters. Only correlate with GPU timing view.
    uint64_t source_node_index = source_index.internalId();
    Dive::NodeType node_type = m_data_core->GetCommandHierarchy().GetNodeType(source_node_index);

    bool is_gpu_timing_node =
        (node_type == Dive::NodeType::kGfxrRootFrameNode) ||
        (node_type == Dive::NodeType::kGfxrVulkanBeginRenderPassCommandNode) ||
        (node_type == Dive::NodeType::kGfxrVulkanBeginCommandBufferNode);

    if (is_gpu_timing_node)
    {
        ClearViewModelSelection(*m_pm4_command_hierarchy_view, false);
        m_gpu_timing_tab_view->OnEventSelectionChanged(source_index);
        return;
    }

    if (m_correlated_capture_loaded &&
        (m_pm4_filter_mode_combo_box->currentIndex() != DiveFilterModel::kBinningPassOnly &&
         m_pm4_filter_mode_combo_box->currentIndex() != DiveFilterModel::kFirstTilePassOnly))
    {
        CorrelateCounter(index, true);
        ClearViewModelSelection(*m_pm4_command_hierarchy_view, false);
        return;
    }
    else if (m_gfxr_capture_loaded)
    {
        CorrelateCounter(index, true);
        return;
    }

    m_gfxr_vulkan_commands_filter_proxy_model->CollectGfxrDrawCallIndices();
    std::vector<uint64_t> gfxr_draw_call_indices =
        qobject_cast<GfxrVulkanCommandFilterProxyModel*>(m_command_hierarchy_view->model())
            ->GetGfxrDrawCallIndices();

    std::optional<uint64_t> found_gfxr_draw_call_index =
        GetDrawCallIndexFromProxyIndex(index, *m_gfxr_vulkan_commands_filter_proxy_model,
                                       gfxr_draw_call_indices, CorrelationTarget::kGfxrDrawCall);

    if (!found_gfxr_draw_call_index.has_value())
    {
        ClearViewModelSelection(*m_pm4_command_hierarchy_view, true);
        m_command_tab_view->ResetModel();
        return;
    }

    std::vector<uint64_t> pm4_draw_call_indices =
        qobject_cast<DiveFilterModel*>(m_pm4_command_hierarchy_view->model())
            ->GetPm4DrawCallIndices();

    uint64_t corresponding_pm4_draw_call_index =
        pm4_draw_call_indices.at(found_gfxr_draw_call_index.value());

    QAbstractItemModel* source_model = m_filter_model->sourceModel();
    QModelIndex pm4_draw_call_index_from_source =
        FindSourceIndexFromNode(source_model, corresponding_pm4_draw_call_index);

    if (pm4_draw_call_index_from_source.isValid())
    {
        QModelIndex proxy_index = m_filter_model->mapFromSource(pm4_draw_call_index_from_source);

        if (proxy_index.isValid())
        {
            QItemSelectionModel* selection_model = m_pm4_command_hierarchy_view->selectionModel();
            QSignalBlocker blocker(selection_model);
            QItemSelectionModel::SelectionFlags flags =
                QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows;

            selection_model->setCurrentIndex(proxy_index, flags);
            m_command_tab_view->OnSelectionChanged(proxy_index);
            m_gfxr_vulkan_command_arguments_tab_view->OnSelectionChanged(source_index);

            m_pm4_command_hierarchy_view->scrollTo(proxy_index,
                                                   QAbstractItemView::PositionAtCenter);
            m_pm4_command_hierarchy_view->expand(proxy_index);

            m_pm4_command_hierarchy_view->viewport()->update();

            CorrelateCounter(index, true);
            emit m_main_window_ptr->EventSelected(corresponding_pm4_draw_call_index);
        }
    }

    ResetHorizontalScroll(*m_pm4_command_hierarchy_view);
    m_command_tab_view->ResetHorizontalScroll();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnCorrelatePm4DrawCall(const QModelIndex& index)
{
    m_gpu_timing_tab_view->ClearSelection();
    m_perf_counter_tab_view->ClearSelection();
    m_gfxr_vulkan_command_arguments_tab_view->OnSelectionChanged(QModelIndex());

    QItemSelectionModel* gfxr_selection_model = m_command_hierarchy_view->selectionModel();
    QSignalBlocker blocker(gfxr_selection_model);

    if (m_pm4_filter_mode_combo_box->currentIndex() != DiveFilterModel::kBinningPassOnly &&
        m_pm4_filter_mode_combo_box->currentIndex() != DiveFilterModel::kFirstTilePassOnly)
    {
        ResetHorizontalScroll(*m_pm4_command_hierarchy_view);
        ClearViewModelSelection(*m_command_hierarchy_view, false);
        return;
    }

    m_gfxr_vulkan_commands_filter_proxy_model->CollectGfxrDrawCallIndices();

    std::vector<uint64_t> pm4_draw_call_indices =
        qobject_cast<DiveFilterModel*>(m_pm4_command_hierarchy_view->model())
            ->GetPm4DrawCallIndices();

    std::optional<uint64_t> found_pm4_draw_call_index = GetDrawCallIndexFromProxyIndex(
        index, *m_filter_model, pm4_draw_call_indices, CorrelationTarget::kPm4DrawCall);

    if (!found_pm4_draw_call_index.has_value())
    {
        ClearViewModelSelection(*m_command_hierarchy_view, false);
        return;
    }

    std::vector<uint64_t> gfxr_draw_call_indices =
        qobject_cast<GfxrVulkanCommandFilterProxyModel*>(m_command_hierarchy_view->model())
            ->GetGfxrDrawCallIndices();

    uint64_t corresponding_gfxr_draw_call_index =
        gfxr_draw_call_indices.at(found_pm4_draw_call_index.value());

    QAbstractItemModel* source_model = m_gfxr_vulkan_commands_filter_proxy_model->sourceModel();
    QModelIndex gfxr_draw_call_index_from_source =
        FindSourceIndexFromNode(source_model, corresponding_gfxr_draw_call_index);

    if (gfxr_draw_call_index_from_source.isValid())
    {
        QModelIndex proxy_index = m_gfxr_vulkan_commands_filter_proxy_model->mapFromSource(
            gfxr_draw_call_index_from_source);
        if (proxy_index.isValid())
        {
            QItemSelectionModel::SelectionFlags flags =
                QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows;

            gfxr_selection_model->setCurrentIndex(proxy_index, flags);
            m_gfxr_vulkan_command_arguments_tab_view->OnSelectionChanged(
                gfxr_draw_call_index_from_source);

            ResetVerticalScroll(*m_command_hierarchy_view);
            m_command_hierarchy_view->scrollTo(proxy_index, QAbstractItemView::PositionAtCenter);
            m_command_hierarchy_view->expand(proxy_index);

            m_command_hierarchy_view->viewport()->update();

            CorrelateCounter(index, false);
        }
    }

    ResetHorizontalScroll(*m_pm4_command_hierarchy_view);
    m_command_tab_view->ResetHorizontalScroll();
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnCounterSelected(uint64_t row_index)
{
    m_gpu_timing_tab_view->ClearSelection();
    m_gfxr_vulkan_commands_filter_proxy_model->CollectGfxrDrawCallIndices();
    std::vector<uint64_t> gfxr_draw_call_indices =
        qobject_cast<GfxrVulkanCommandFilterProxyModel*>(m_command_hierarchy_view->model())
            ->GetGfxrDrawCallIndices();

    if (row_index >= gfxr_draw_call_indices.size())
    {
        QMessageBox::critical(m_main_window_ptr, "Correlation Failed",
                              "Selected row does not correlate with current loaded capture.");
        ClearViewModelSelection(*m_command_hierarchy_view, false);
        ClearViewModelSelection(*m_pm4_command_hierarchy_view, false);
        return;
    }

    QAbstractItemModel* gfxr_source_model =
        m_gfxr_vulkan_commands_filter_proxy_model->sourceModel();
    QModelIndex gfxr_draw_call_index_from_source =
        FindSourceIndexFromNode(gfxr_source_model, gfxr_draw_call_indices.at(row_index));
    QModelIndex proxy_index;
    QItemSelectionModel* selection_model = nullptr;
    QItemSelectionModel::SelectionFlags flags;
    if (gfxr_draw_call_index_from_source.isValid())
    {
        proxy_index = m_gfxr_vulkan_commands_filter_proxy_model->mapFromSource(
            gfxr_draw_call_index_from_source);
        if (proxy_index.isValid())
        {
            selection_model = m_command_hierarchy_view->selectionModel();
            QSignalBlocker main_view_blocker(selection_model);
            flags = QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows;

            selection_model->setCurrentIndex(proxy_index, flags);
            m_gfxr_vulkan_command_arguments_tab_view->OnSelectionChanged(
                gfxr_draw_call_index_from_source);

            ResetVerticalScroll(*m_command_hierarchy_view);
            m_command_hierarchy_view->scrollTo(proxy_index, QAbstractItemView::PositionAtCenter);
            m_command_hierarchy_view->expand(proxy_index);

            m_command_hierarchy_view->viewport()->update();
        }
    }

    if (m_pm4_filter_mode_combo_box->isEnabled() &&
        (m_pm4_filter_mode_combo_box->currentIndex() == DiveFilterModel::kBinningPassOnly ||
         m_pm4_filter_mode_combo_box->currentIndex() == DiveFilterModel::kFirstTilePassOnly))
    {
        std::vector<uint64_t> pm4_draw_call_indices =
            qobject_cast<DiveFilterModel*>(m_pm4_command_hierarchy_view->model())
                ->GetPm4DrawCallIndices();
        QAbstractItemModel* pm4_source_model = m_filter_model->sourceModel();
        QModelIndex pm4_draw_call_index_from_source =
            FindSourceIndexFromNode(pm4_source_model, pm4_draw_call_indices.at(row_index));

        if (pm4_draw_call_index_from_source.isValid())
        {
            proxy_index = m_filter_model->mapFromSource(pm4_draw_call_index_from_source);
            if (proxy_index.isValid())
            {
                selection_model = m_pm4_command_hierarchy_view->selectionModel();
                QSignalBlocker main_view_blocker(selection_model);
                flags = QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows;

                selection_model->setCurrentIndex(proxy_index, flags);

                m_pm4_command_hierarchy_view->scrollTo(proxy_index,
                                                       QAbstractItemView::PositionAtCenter);
                m_pm4_command_hierarchy_view->expand(proxy_index);

                m_pm4_command_hierarchy_view->viewport()->update();
            }
        }
    }
    else
    {
        ClearViewModelSelection(*m_pm4_command_hierarchy_view, false);
    }

    ResetHorizontalScroll(*m_pm4_command_hierarchy_view);
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::CorrelateCounter(const QModelIndex& index, bool called_from_gfxr_view)
{
    m_perf_counter_tab_view->ClearSelection();

    std::optional<uint64_t> found_draw_call_index = 0;
    bool found = false;

    if (!called_from_gfxr_view)
    {
        m_gpu_timing_tab_view->ClearSelection();

        if (m_pm4_filter_mode_combo_box->currentIndex() == DiveFilterModel::kBinningPassOnly ||
            m_pm4_filter_mode_combo_box->currentIndex() == DiveFilterModel::kFirstTilePassOnly)
        {
            std::vector<uint64_t> pm4_draw_call_indices =
                qobject_cast<DiveFilterModel*>(m_pm4_command_hierarchy_view->model())
                    ->GetPm4DrawCallIndices();

            found_draw_call_index = GetDrawCallIndexFromProxyIndex(
                index, *m_filter_model, pm4_draw_call_indices, CorrelationTarget::kPm4DrawCall);

            if (found_draw_call_index.has_value())
            {
                found = true;
            }
        }
    }
    else
    {
        m_gfxr_vulkan_commands_filter_proxy_model->CollectGfxrDrawCallIndices();
        std::vector<uint64_t> gfxr_draw_call_indices =
            qobject_cast<GfxrVulkanCommandFilterProxyModel*>(m_command_hierarchy_view->model())
                ->GetGfxrDrawCallIndices();

        // Use helper for GFXR sender
        found_draw_call_index = GetDrawCallIndexFromProxyIndex(
            index, *m_gfxr_vulkan_commands_filter_proxy_model, gfxr_draw_call_indices,
            CorrelationTarget::kGfxrDrawCall);

        if (found_draw_call_index.has_value())
        {
            found = true;
        }
        else
        {
            uint64_t source_node_index =
                m_gfxr_vulkan_commands_filter_proxy_model->mapToSource(index).internalId();
            Dive::NodeType node_type =
                m_data_core->GetCommandHierarchy().GetNodeType(source_node_index);
            bool is_gpu_timing_node =
                (node_type == Dive::NodeType::kGfxrRootFrameNode) ||
                (node_type == Dive::NodeType::kGfxrVulkanBeginRenderPassCommandNode) ||
                (node_type == Dive::NodeType::kGfxrVulkanBeginCommandBufferNode);

            if (is_gpu_timing_node)
            {
                return;
            }

            m_gpu_timing_tab_view->ClearSelection();
        }
    }

    if (found)
    {
        m_perf_counter_tab_view->CorrelateCounter(found_draw_call_index.value());
    }
}

//--------------------------------------------------------------------------------------------------
void MainWindowPrivate::OnGpuTimingDataSelected(uint64_t node_index)
{
    if (m_correlated_capture_loaded)
    {
        QItemSelectionModel* pm4_selection_model = m_pm4_command_hierarchy_view->selectionModel();
        QSignalBlocker pm4_blocker(pm4_selection_model);
        ClearViewModelSelection(*m_pm4_command_hierarchy_view, true);
    }

    QItemSelectionModel* gfxr_selection_model = m_command_hierarchy_view->selectionModel();
    QSignalBlocker gfxr_blocker(gfxr_selection_model);
    ClearViewModelSelection(*m_command_hierarchy_view, true);

    QAbstractItemModel* gfxr_source_model =
        m_gfxr_vulkan_commands_filter_proxy_model->sourceModel();
    QModelIndex gfxr_draw_call_index_from_source =
        FindSourceIndexFromNode(gfxr_source_model, node_index);
    QItemSelectionModel::SelectionFlags flags;
    QModelIndex proxy_index =
        m_gfxr_vulkan_commands_filter_proxy_model->mapFromSource(gfxr_draw_call_index_from_source);
    if (proxy_index.isValid())
    {
        QItemSelectionModel* selection_model = m_command_hierarchy_view->selectionModel();

        flags = QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows;

        selection_model->setCurrentIndex(proxy_index, flags);
        m_gfxr_vulkan_command_arguments_tab_view->OnSelectionChanged(
            gfxr_draw_call_index_from_source);

        ResetVerticalScroll(*m_command_hierarchy_view);
        m_command_hierarchy_view->scrollTo(proxy_index, QAbstractItemView::PositionAtCenter);
        m_command_hierarchy_view->expand(proxy_index);

        m_command_hierarchy_view->viewport()->update();
    }
}
