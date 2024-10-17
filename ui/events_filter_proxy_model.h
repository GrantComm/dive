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

#include <QSortFilterProxyModel>
#include <QWidget>
#include <qcheckbox.h>
#include <QSet>

#pragma once

class EventsFilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT 

public:
    EventsFilterProxyModel(QObject *parent = nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    QList<QModelIndex> search(const QVariant &value) const;
    void searchRecursively(const QString &searchText, const QModelIndex &parent, QList<QModelIndex> &foundIndices) const;

public slots:
    void setFilterText(const QSet<QString> &active_filters);

private:
    QSet<QString> m_active_filters;
};