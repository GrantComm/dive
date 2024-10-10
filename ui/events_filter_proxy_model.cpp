/*
 Copyright 2024 Google LLC
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
#include "events_filter_proxy_model.h"
#include <iostream>
#include <string>

//--------------------------------------------------------------------------------------------------
EventsFilterProxyModel::EventsFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {}

//--------------------------------------------------------------------------------------------------
void EventsFilterProxyModel::setFilterText(const std::unordered_set<QCheckBox*> &active_filters) {
        m_active_filters = active_filters;
        invalidateFilter(); 
}

//--------------------------------------------------------------------------------------------------
bool EventsFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    QString data = sourceModel()->data(index).toString();
    bool rowAccepted = false; 
    std::cout << "HERE, row count = " << std::to_string(sourceModel()->rowCount(index)) << std::endl;
    std::cout << "HERE, data = " << data.toStdString() << std::endl;

    // Assume the row is accepted if there are no active filters
    if (m_active_filters.empty()) {
        std::cout<< "HERE, no filters, row accepted" << std::endl;
        rowAccepted = true;
    } else {
        for (QCheckBox* checkBox : m_active_filters) {
            if (data.contains(checkBox->text(), Qt::CaseInsensitive)) {
                std::cout << "HERE, accepted data = " << data.toStdString() << std::endl;
                rowAccepted = true; 
                break; // If a checkbox matches, accept the row
            }
        }
    }

    // Recursively check child rows if not already accepted
    if (!rowAccepted) { 
        int childCount = sourceModel()->rowCount(index);
        for (int i = 0; i < childCount; ++i) {
            if (filterAcceptsRow(i, index)) {
                std::cout << "HERE, accepted data = " << data.toStdString() << std::endl;
                rowAccepted = true;
                break;
            }
        }
    }

    return rowAccepted;
}