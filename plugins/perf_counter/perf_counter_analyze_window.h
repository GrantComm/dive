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

#include "idive_plugin.h"
#include "ui/analyze_window.h"

#pragma once

namespace Dive
{
// The PluginTest class is a sample implementation of IDivePlugin.
// It adds a new menu item to the "Help" menu of the MainWindow and displays a message box when that
// action is triggered.

// Still need Q_OBJECT for signals/slots/meta-object features for Qt UI
class PerfCounterAnalyzeDialog : public AnalyzeDialog, public IDivePlugin
{
    // Data structure to hold a single item from a CSV
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
    PerfCounterAnalyzeDialog(QWidget *parent = 0);
    ~PerfCounterAnalyzeDialog();
    std::string PluginName() const override { return "Perf Counter Analyze Dialog"; }
    std::string PluginVersion() const override { return "1.0.0"; }

    bool Initialize(MainWindow &main_window) override;
    void Shutdown() override;

private:
    void PopulateSettings();
    void UpdateSelectedSettingsList();

    QLabel      *m_settings_list_label;
    QListWidget *m_settings_list;

    QLabel    *selected_setting_description_label;
    QTextEdit *selected_setting_description;

    QLabel      *m_enabled_settings_list_label;
    QListWidget *m_enabled_settings_list;

    QHBoxLayout      *m_main_layout;
    QVBoxLayout      *m_left_panel_layout;
    QVBoxLayout      *m_right_panel_layout;
    QVector<CsvItem> *m_csv_items;
};

}  // namespace Dive