/*
 Copyright 2026 Google LLC
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

#include <QWidget>
#pragma once

// Forward declaration
class QCheckBox;
class QLabel;
class QListWidget;
class QPushButton;
class SearchBar;

class WhatIfModificationItem : public QWidget {
    Q_OBJECT
public:
    explicit WhatIfModificationItem(const QString &title, QWidget *parent = nullptr);

signals:
    void WhatIfModificationSelectionChanged(const QString &itemText);

private:
    QCheckBox *m_check_box;
    QLabel *m_modification_title_label;
    QString m_currentText;
};

class WhatIfModificationTabView : public QWidget
{
    Q_OBJECT
 public:
    explicit WhatIfModificationTabView(QWidget* parent = nullptr);

 public slots:
    void OnModificationAdded(const QString& title);

 private slots:
    void OnClearModifications();
    void OnSearchModifications();
    void OnTestModifications();

signals:
    void HideOtherSearchBars();


 private:
    void ConnectSearchBar();
    void DisconnectSearchBar();

    QPushButton* m_search_trigger_button;
    QPushButton* m_clear_modifications_button;
    QPushButton* m_test_modifications_button;
    QListWidget* m_modifications_list_widget;
    SearchBar*   m_search_bar = nullptr;
};
