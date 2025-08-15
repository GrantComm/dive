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

#include "perf_counter_analyze_window.h"

#include <QComboBox>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSizePolicy>
#include <QSpinBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <filesystem>
#include <string>

#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "capture_service/device_mgr.h"
#include "common/macros.h"
#include "ui/main_window.h"

namespace Dive
{
// =================================================================================================
// PerfCounterAnalyzeDialog
// =================================================================================================
PerfCounterAnalyzeDialog::PerfCounterAnalyzeDialog(QWidget *parent)
{
    qDebug() << "PerfCounterAnalyzeDialog created.";

    // Settings List
    m_settings_list_label = new QLabel(tr("Available Settings:"));
    m_settings_list = new QListWidget();
    m_csv_items = new QVector<CsvItem>();
    PopulateSettings();

    // Settings Description
    selected_setting_description_label = new QLabel(tr("Description:"));
    selected_setting_description = new QTextEdit();
    selected_setting_description->setReadOnly(true);
    selected_setting_description->setPlaceholderText("Select a setting to see its description...");

    // Enabled Settings
    m_enabled_settings_list_label = new QLabel(tr("Enabled Settings:"));
    m_enabled_settings_list = new QListWidget();

    // Device Selector
    m_device_layout = new QHBoxLayout();
    m_device_label = new QLabel(tr("Devices:"));
    m_device_model = new QStandardItemModel();
    m_device_box = new QComboBox();
    m_device_refresh_button = new QPushButton("&Refresh", this);
    m_devices = Dive::GetDeviceManager().ListDevice();
    UpdateDeviceList(false);
    m_device_box->setCurrentText("Please select a device");
    m_device_box->setModel(m_device_model);
    m_device_box->setCurrentIndex(0);
    m_device_layout->addWidget(m_device_label);
    m_device_layout->addWidget(m_device_box);
    m_device_layout->addWidget(m_device_refresh_button);

    // Selected File
    m_selected_file_layout = new QHBoxLayout();
    m_selected_file_label = new QLabel("Selected Capture file:");
    m_selected_file_input_box = new QLineEdit();
    m_selected_capture_file_string = "";
    m_selected_file_input_box->setText(m_selected_capture_file_string);
    m_selected_file_input_box->setReadOnly(true);
    m_open_files_button = new QPushButton(this);
    QIcon open_files_icon(":/images/open.png");
    m_open_files_button->setIcon(open_files_icon);
    m_selected_file_layout->addWidget(m_selected_file_label);
    m_selected_file_layout->addWidget(m_selected_file_input_box);
    m_selected_file_layout->addWidget(m_open_files_button);

    // Enable GPU Time
    m_gpu_time_layout = new QHBoxLayout();
    m_gpu_time_label = new QLabel(tr("GPU Time:"));
    m_gpu_time_layout->addWidget(m_gpu_time_label);
    m_gpu_time_box = new QComboBox();
    m_gpu_time_model = new QStandardItemModel();
    QStandardItem *enabled_item = new QStandardItem("Enabled");
    QStandardItem *disabled_item = new QStandardItem("Disabled");
    m_gpu_time_model->appendRow(enabled_item);
    m_gpu_time_model->appendRow(disabled_item);
    m_gpu_time_box->setModel(m_gpu_time_model);
    m_gpu_time_box->setCurrentIndex(1);
    m_gpu_time_layout->addWidget(m_gpu_time_box);

    // Single Frame Loop Count
    m_frame_count_layout = new QHBoxLayout();
    m_frame_count_label = new QLabel(tr("Loop Single Frame Count:"));
    m_frame_count_box = new QSpinBox(this);
    m_frame_count_box->setRange(0, std::numeric_limits<int>::max());
    m_frame_count_box->setSpecialValueText("Infinite");
    m_frame_count_box->setMinimum(-1);
    m_frame_count_box->setValue(-1);
    m_frame_count_layout->addWidget(m_frame_count_label);
    m_frame_count_layout->addWidget(m_frame_count_box);

    // Replay Button
    m_button_layout = new QHBoxLayout();
    m_replay_button = new QPushButton("&Replay", this);
    m_replay_button->setEnabled(true);
    m_button_layout->addWidget(m_replay_button);

    // Left Panel Layout
    m_left_panel_layout = new QVBoxLayout();
    m_left_panel_layout->addWidget(m_settings_list_label);
    m_left_panel_layout->addWidget(m_settings_list);

    // Right Panel Layout
    m_right_panel_layout = new QVBoxLayout();
    m_right_panel_layout->addWidget(selected_setting_description_label);
    m_right_panel_layout->addWidget(selected_setting_description);
    m_right_panel_layout->addWidget(m_enabled_settings_list_label);
    m_right_panel_layout->addWidget(m_enabled_settings_list);
    m_right_panel_layout->addLayout(m_device_layout);
    m_right_panel_layout->addLayout(m_selected_file_layout);
    m_right_panel_layout->addLayout(m_gpu_time_layout);
    m_right_panel_layout->addLayout(m_frame_count_layout);
    m_right_panel_layout->addLayout(m_button_layout);

    // Main Layout
    m_main_layout = new QHBoxLayout(this);
    m_main_layout->addLayout(m_left_panel_layout);
    m_main_layout->addLayout(m_right_panel_layout);

    setLayout(m_main_layout);

    // Connect the name list's selection change to a lambda
    QObject::connect(m_settings_list,
                     &QListWidget::currentItemChanged,
                     [&](QListWidgetItem *current, QListWidgetItem *previous) {
                         if (current)
                         {
                             int index = m_settings_list->row(current);
                             if (index >= 0 && index < m_csv_items->size())
                             {
                                 selected_setting_description->setText(
                                 m_csv_items->at(index).description);
                             }
                         }
                     });

    QObject::connect(m_settings_list, &QListWidget::itemChanged, [&](QListWidgetItem *item) {
        // This code will execute whenever an item's state changes
        // It will refresh the second list of selected items
        UpdateSelectedSettingsList();
    });

    QObject::connect(m_device_box,
                     SIGNAL(currentIndexChanged(const QString &)),
                     this,
                     SLOT(OnDeviceSelected(const QString &)));
    QObject::connect(m_device_refresh_button,
                     &QPushButton::clicked,
                     this,
                     &PerfCounterAnalyzeDialog::OnDeviceListRefresh);
    QObject::connect(m_open_files_button,
                     &QPushButton::clicked,
                     this,
                     &PerfCounterAnalyzeDialog::OnOpenFile);
    QObject::connect(m_replay_button,
                     &QPushButton::clicked,
                     this,
                     &PerfCounterAnalyzeDialog::OnReplay);
}

PerfCounterAnalyzeDialog::~PerfCounterAnalyzeDialog()
{
    qDebug() << "PerfCounterAnalyzeDialog destroyed.";
    Dive::GetDeviceManager().RemoveDevice();
}

void PerfCounterAnalyzeDialog::PopulateSettings()
{
    QFile file(":/resources/available_settings.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Could not open file:" << file.errorString().toStdString() << std::endl;
        qDebug() << "Could not open file:" << file.errorString();
        return;
    }

    QTextStream in(&file);

    // Read and discard the first line (headers)
    if (!in.atEnd())
    {
        in.readLine();
    }

    while (!in.atEnd())
    {
        QString     line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() == 5)
        {
            CsvItem item;
            item.id = fields[0].replace('"', "");
            ;
            item.type = fields[1].replace('"', "");
            ;
            item.key = fields[2].replace('"', "");
            ;
            item.name = fields[3].replace('"', "");
            ;
            item.description = fields[4].replace('"', "");
            ;
            m_csv_items->append(item);
        }
    }
    file.close();

    // Populate the settings list
    for (const auto &item : *m_csv_items)
    {
        QListWidgetItem *csv_item = new QListWidgetItem(item.name);
        csv_item->setFlags(csv_item->flags() | Qt::ItemIsUserCheckable);
        csv_item->setCheckState(Qt::Unchecked);
        m_settings_list->addItem(csv_item);
    }
}

void PerfCounterAnalyzeDialog::UpdateSelectedSettingsList()
{
    // Clear the existing items in the target list
    m_enabled_settings_list->clear();

    // Iterate through the source list to find checked items
    for (int i = 0; i < m_settings_list->count(); ++i)
    {
        QListWidgetItem *item = m_settings_list->item(i);

        // If the item is checked, add it to the target list
        if (item->checkState() == Qt::Checked)
        {
            m_enabled_settings_list->addItem(item->text());
        }
    }
}

bool PerfCounterAnalyzeDialog::Initialize(MainWindow &main_window)
{
    main_window.InitializeAnalyzeDialog(this);
    return true;
}

void PerfCounterAnalyzeDialog::Shutdown() {}

// This function must be exported from the shared library.
extern "C" DIVE_PLUGIN_EXPORT IDivePlugin *CreateDivePluginInstance()
{
    return new PerfCounterAnalyzeDialog();
}

}  // namespace Dive
