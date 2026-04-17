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

#pragma once

#include <QMainWindow>
#include <memory>

#include "dive/ui/forward.h"
#include "dive_core/cross_ref.h"
#include "dive_ui_lib_export.h"

class ApplicationController;
class TraceDialog;
class ProgressTrackerCallback;
class MainWindowPrivate;

class DIVE_UI_LIB_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class ApplicationController;
    friend class MainWindowPrivate;

 public:
    explicit MainWindow(ApplicationController& controller);
    ~MainWindow() override;

    MainWindow(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;

    bool LoadFile(const std::string& file_name, bool is_temp_file = false, bool async = true);
    TraceDialog& GetTraceDialog();
    ProgressTrackerCallback& GetProgressTracker();

 protected:
    void closeEvent(QCloseEvent* closeEvent) Q_DECL_OVERRIDE;

 signals:
    void HideOverlay();
    void EventSelected(uint64_t node_index);
    void SetSaveMenuStatus(bool);
    void SetSaveAsMenuStatus(bool);
    void FileLoaded();
    void PendingPerfCounterResults(const QString& file_name);
    void PendingGpuTimingResults(const QString& file_name);
    void PendingScreenshot(const QString& file_name);
    void AsyncTraceStatsDone();
    void AnalyzeCaptureStarted(const QString& file_path);

 public slots:
    void OnCapture(bool is_capture_delayed = false);
    void OnCaptureUpdated(const QString& file_path);
    void OnSwitchToShaderTab();
    void OnOpenVulkanDrawCallMenu(const QPoint& pos);
    void OnOpenVulkanCallMenu(const QPoint& pos);
    void OnCorrelateVulkanDrawCall(const QModelIndex&);
    void OnCorrelatePm4DrawCall(const QModelIndex&);
    void OnCounterSelected(uint64_t);
    void OnGpuTimingDataSelected(uint64_t);
    void OnCorrelationFilterApplied(uint64_t, const QModelIndex&);
    void OnPendingPerfCounterResults(const QString& file_name);
    void OnPendingGpuTimingResults(const QString& file_name);
    void OnPendingScreenshot(const QString& file_name);
    void OnHideOverlay();
    void OnAddWhatIfModification();
    void OnWhatIfSetupTrigger();

 private slots:
    void OnCommandViewModeChange(const QString& string);
    void OnCommandViewModeComboBoxHover(const QString&);
    void OnSelectionChanged(const QModelIndex& index);
    void OnFilterModeChange(const QString& string);
    void OnGfxrFilterModeChange();
    void OnOpenFile();
    void OnNormalCapture();
    void OnCaptureTrigger();
    void OnAnalyzeCapture();
    void OnExpandToLevel();
    void OnAbout();
    void OnShortcuts();
    void OnSaveCapture();
    void OnSearchTrigger();
    void OpenRecentFile();
    void UpdateOverlay(const QString&);
    void OnCrossReference(Dive::CrossRef);
    void OnFileLoaded(const LoadFileResult& loaded_file);
    void OnTraceAvailable(const QString&);
    void OnTabViewSearchBarVisibilityChange(bool isHidden);
    void OnTabViewChange();
    void ConnectDiveFileTabs();
    void ConnectAdrenoRdFileTabs();
    void ConnectGfxrFileTabs();
    void ConnectSearchBar();
    void DisconnectSearchBar();
    void ConnectPm4SearchBar();
    void DisconnectPm4SearchBar();
    void DisconnectAllTabs();
    void OnTraceStatsUpdated();

 private:
    std::unique_ptr<MainWindowPrivate> m_impl;
};
