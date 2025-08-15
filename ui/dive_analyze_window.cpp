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

#include "dive_analyze_window.h"

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
#include "settings.h"
#include "common/macros.h"

// =================================================================================================
// DiveAnalyzeDialog
// =================================================================================================
DiveAnalyzeDialog::DiveAnalyzeDialog(QWidget *parent)
{
    qDebug() << "DiveAnalyzeDialog created.";

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

    // Main Layout
    m_main_layout = new QVBoxLayout(this);
    m_main_layout->addLayout(m_device_layout);
    m_main_layout->addLayout(m_selected_file_layout);
    m_main_layout->addLayout(m_gpu_time_layout);
    m_main_layout->addLayout(m_frame_count_layout);
    m_main_layout->addLayout(m_button_layout);

    setLayout(m_main_layout);

    QObject::connect(m_device_box,
                     SIGNAL(currentIndexChanged(const QString &)),
                     this,
                     SLOT(OnDeviceSelected(const QString &)));
    QObject::connect(m_device_refresh_button,
                     &QPushButton::clicked,
                     this,
                     &DiveAnalyzeDialog::OnDeviceListRefresh);
    QObject::connect(m_open_files_button,
                     &QPushButton::clicked,
                     this,
                     &DiveAnalyzeDialog::OnOpenFile);
    QObject::connect(m_replay_button, &QPushButton::clicked, this, &DiveAnalyzeDialog::OnReplay);
}

DiveAnalyzeDialog::~DiveAnalyzeDialog()
{
    qDebug() << "DiveAnalyzeDialog destroyed.";
    Dive::GetDeviceManager().RemoveDevice();
}
