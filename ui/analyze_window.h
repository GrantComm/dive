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

#include <QDialog>
#include <QThread>
#include <string>
#include "capture_service/device_mgr.h"
#include "package_filter.h"

#pragma once

// Forward declarations
class QLabel;
class QHBoxLayout;
class QPushButton;
class QVBoxLayout;
class QComboBox;
class QStandardItemModel;
class QLineEdit;
class QListWidget;
class QSpinBox;
class QTextEdit;
class MainWindow;

namespace Dive
{
class SelectedCaptureFiles;
const QString kStopReplayButtonText = "Stop Infinite Replay";
}  // namespace Dive

class GfxrReplayWorker;

class AnalyzeDialog : public QDialog
{
    // Data structure to hold a single item from the CSV
    struct CsvItem
    {
        QString id;
        QString type;
        QString key;
        QString name;
        QString description;
    };

    Q_OBJECT

public:
    AnalyzeDialog(QWidget *parent = 0);
    ~AnalyzeDialog();
    void UpdateDeviceList(bool is_initialized);
    void SetSelectedCaptureFile(const QString &file_path);

private slots:
    void OnDeviceSelected(const QString &);
    void OnDeviceListRefresh();
    void OnOpenFile();
    void OnReplayButtonClicked();
    void HandleReplayFinished(const QString &remote_file_path);
    void HandleReplayError(const QString &error_message);
    void HandleStatusUpdate(const QString &status_message, bool is_enabled);

signals:
    void OnNewFileOpened(const QString &file_path);
    void OnDisplayPerfCounterResults(const QString &file_path);
    void ReloadCapture(const QString &file_path);
    void ReplayFinished();
    void StartReplay(const QString                  &remote_file,
                     const QString                  &download_dir,
                     bool                            dump_pm4_enabled,
                     bool                            gpu_time_enabled,
                     int                             frame_count,
                     const std::vector<std::string> *enabled_settings_vector);

private:
    void                        ShowErrorMessage(const std::string &message);
    void                        SetReplayButton(const QString &message, bool is_enabled);
    void                        SetReplayDownloadDir();
    void                        PopulateSettings();
    void                        UpdateSelectedSettingsList();
    void                        UpdatePerfTabView(const std::string remote_file_name);
    absl::StatusOr<std::string> GetCaptureFileDirectory();
    absl::StatusOr<std::string> GetAssetFile();
    absl::StatusOr<std::string> PushFilesToDevice(const std::string &local_asset_file_path);

    // Member variables for the UI and state
    QLabel      *m_settings_list_label;
    QListWidget *m_settings_list;

    QLabel    *selected_setting_description_label;
    QTextEdit *selected_setting_description;

    QLabel      *m_enabled_settings_list_label;
    QListWidget *m_enabled_settings_list;

    QHBoxLayout        *m_device_layout;
    QLabel             *m_device_label;
    QStandardItemModel *m_device_model;
    QComboBox          *m_device_box;
    QPushButton        *m_device_refresh_button;

    QHBoxLayout *m_selected_file_layout;
    QLabel      *m_selected_file_label;
    QLineEdit   *m_selected_file_input_box;
    QPushButton *m_open_files_button;

    QHBoxLayout        *m_dump_pm4_layout;
    QLabel             *m_dump_pm4_label;
    QStandardItemModel *m_dump_pm4_model;
    QComboBox          *m_dump_pm4_box;

    QHBoxLayout        *m_gpu_time_layout;
    QLabel             *m_gpu_time_label;
    QStandardItemModel *m_gpu_time_model;
    QComboBox          *m_gpu_time_box;

    QHBoxLayout *m_frame_count_layout;
    QLabel      *m_frame_count_label;
    QSpinBox    *m_frame_count_box;

    QHBoxLayout *m_button_layout;
    QPushButton *m_replay_button;

    QHBoxLayout                  *m_main_layout;
    QVBoxLayout                  *m_left_panel_layout;
    QVBoxLayout                  *m_right_panel_layout;
    std::vector<Dive::DeviceInfo> m_devices;
    std::string                   m_cur_device;
    QString                       m_selected_capture_file_string;
    QVector<CsvItem>             *m_csv_items;
    std::vector<std::string>     *m_enabled_settings_vector;

    const int     kDataRole = Qt::UserRole + 1;
    const QString kDefaultReplayButtonText = "Replay";
    const QString kStopReplayButtonText = "Stop Infinite Replay";

    absl::StatusOr<std::string> m_capture_file_directory = "";

    bool m_dump_pm4_enabled;
    bool m_gpu_time_enabled;
    bool m_perf_counters_enabled;

    // The worker thread and its thread object are now initialized
    // to nullptr and created on demand in OnDeviceSelected.
    GfxrReplayWorker    *m_replay_worker = nullptr;
    QThread             *m_worker_thread = nullptr;
    Dive::AndroidDevice *m_device = nullptr;
};

// New or refactored worker class.
class GfxrReplayWorker : public QObject
{
    Q_OBJECT

public:
    GfxrReplayWorker(Dive::AndroidDevice *device, const std::string &device_serial);
    void SetReplayParams(const QString                  &remote_file,
                         const std::string              &download_dir,
                         bool                            dump_pm4_enabled,
                         bool                            gpu_time_enabled,
                         bool                            perf_counters_enabled,
                         int                             frame_count,
                         const std::vector<std::string> &enabled_settings_vector);
    void StopReplay();

public slots:
    void RunReplay();

signals:
    void ReplayFinished(const QString &remote_file_path);
    void ReplayError(const QString &error_message);
    void StatusUpdate(const QString &message, bool enable);
    void UpdateReplayButton(const QString &text, bool is_enabled);

private:
    absl::Status Pm4Replay(Dive::DeviceManager &device_manager,
                           const std::string   &remote_gfxr_file);
    absl::Status PerfCounterReplay(Dive::DeviceManager &device_manager,
                                   const std::string   &remote_gfxr_file);
    absl::Status GpuTimeReplay(Dive::DeviceManager &device_manager,
                               const std::string   &remote_gfxr_file);
    void         WaitForReplay();
    std::string  GetReplayArgs();

    // Replay parameters
    QString                  m_remote_file_path;
    bool                     m_dump_pm4_enabled;
    bool                     m_gpu_time_enabled;
    bool                     m_perf_counters_enabled;
    int                      m_frame_count;
    std::vector<std::string> m_enabled_settings_vector;
    bool                     m_is_infinite_replay = false;
    Dive::AndroidDevice     *m_device;
    std::string              m_device_serial;
    std::string              m_download_dir;
};
