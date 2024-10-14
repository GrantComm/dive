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

#include <QDialog>
#include <qevent.h>
#include <unordered_set>

#pragma once

// Forward declarations
class QCheckBox;
class QPushButton;

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    FilterDialog(QWidget* parent = nullptr);

public slots:
    void selectAllEventsFilter(int state);
    void selectFilter(int state);
    void applyFilters();
    void onReject();

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void FiltersUpdated(QSet<QString> active_filters);

private:
    const std::size_t kTotalFilterCount = 4;
    QCheckBox   *m_all_filter = nullptr;
    QCheckBox   *m_blit_filter = nullptr;
    QCheckBox   *m_draw_filter = nullptr;
    QCheckBox   *m_write_filter = nullptr;
    QPushButton *m_apply = nullptr;
    
    std::unordered_set<QCheckBox*> m_active_filters;
    std::unordered_set<QCheckBox*> m_filters;
    bool m_submitted;
};