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

#include "what_if_modifications_tab_view.h"

#include <qobject.h>
#include <qtimer.h>

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPoint>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

#include "object_names.h"
#include "search_bar.h"

// =================================================================================================
// WhatIfModificationItem
// =================================================================================================
WhatIfModificationItem::WhatIfModificationItem(const QString &title, QWidget *parent)
    : QWidget(parent), m_currentText(title)
{
    m_check_box = new QCheckBox(this);
    m_check_box->setChecked(true);
    m_modification_title_label = new QLabel(title, this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_check_box);
    layout->addWidget(m_modification_title_label);
    layout->addStretch();
    setLayout(layout);

    connect(m_check_box, &QCheckBox::stateChanged, this, [this](int state) {
        emit WhatIfModificationSelectionChanged(m_currentText);
    });
}

// =================================================================================================
// WhatIfModificationTabView
// =================================================================================================
WhatIfModificationTabView::WhatIfModificationTabView(QWidget* parent) : QWidget(parent)
{
    // Search Button
    m_search_trigger_button = new QPushButton;
    m_search_trigger_button->setObjectName(kModificationsSearchButtonName);
    m_search_trigger_button->setIcon(QIcon(":/images/search.png"));

    // Search Bar
    m_search_bar = new SearchBar(this);
    m_search_bar->setObjectName(kModificationsSearchBarName);
    m_search_bar->hide();

    // Clear Modifications Button
    m_clear_modifications_button = new QPushButton("Clear Modifications", this);

    // Test Modifications Button
    m_test_modifications_button = new QPushButton("Test Modifications", this);

    QHBoxLayout* controls_layout = new QHBoxLayout();
    controls_layout->addWidget(m_search_trigger_button);
    controls_layout->addWidget(m_clear_modifications_button);
    controls_layout->addWidget(m_test_modifications_button);
    controls_layout->addStretch();

    // Modifications List
    m_modifications_list_widget = new QListWidget(this);
    m_modifications_list_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_modifications_list_widget->setSortingEnabled(false);


    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addWidget(m_search_bar);
    main_layout->addLayout(controls_layout);
    main_layout->addWidget(m_modifications_list_widget);

    QObject::connect(m_search_trigger_button, &QPushButton::clicked, this,
                     &WhatIfModificationTabView::OnSearchModifications);
    QObject::connect(m_clear_modifications_button, &QPushButton::clicked, this,
                     &WhatIfModificationTabView::OnClearModifications);
    QObject::connect(m_test_modifications_button, &QPushButton::clicked, this,
                     &WhatIfModificationTabView::OnTestModifications);
}

//--------------------------------------------------------------------------------------------------
void WhatIfModificationTabView::OnModificationAdded(const QString& title)
{
    WhatIfModificationItem* modification_item = new WhatIfModificationItem(title);

    QListWidgetItem* list_item = new QListWidgetItem();

    list_item->setSizeHint(modification_item->sizeHint());
    m_modifications_list_widget->insertItem(0, list_item);

    m_modifications_list_widget->setItemWidget(list_item, modification_item);
}

//--------------------------------------------------------------------------------------------------
void WhatIfModificationTabView::OnClearModifications()
{
    for (int i = 0; i < m_modifications_list_widget->count(); ++i) {
        QListWidgetItem* list_item = m_modifications_list_widget->item(i);
        QWidget* item_widget = m_modifications_list_widget->itemWidget(list_item);
        WhatIfModificationItem* modification_item = qobject_cast<WhatIfModificationItem*>(item_widget);
        if (modification_item) {
            if (modification_item->findChild<QCheckBox*>()->isChecked()) {
                delete list_item;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------
void WhatIfModificationTabView::OnSearchModifications()
{
    if (m_search_bar->isVisible())
    {
        m_search_bar->clearSearch();
        m_search_bar->hide();
        m_search_trigger_button->show();

        DisconnectSearchBar();
    }
    else
    {
        ConnectSearchBar();

        m_search_trigger_button->hide();
        m_search_bar->positionCurser();
        m_search_bar->show();
        emit HideOtherSearchBars();
    }
}

//--------------------------------------------------------------------------------------------------
void WhatIfModificationTabView::OnTestModifications()
{
    // Test modifications logic here
}

//--------------------------------------------------------------------------------------------------
void WhatIfModificationTabView::ConnectSearchBar()
{
    // Connect search bar signals to the modifications view here
}

//--------------------------------------------------------------------------------------------------
void WhatIfModificationTabView::DisconnectSearchBar()
{
    // Disconnect search bar signals from the modifications view here
}
