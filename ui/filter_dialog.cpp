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

#include "filter_dialog.h"
#include "QHBoxLayout"
#include "QCheckBox"
#include "QPushButton"
#include "QVBoxLayout"
#include <qevent.h>
#include <qnamespace.h>
#include <iostream>
#include <qobjectdefs.h>
#include <string>

//--------------------------------------------------------------------------------------------------
FilterDialog::FilterDialog(QWidget* parent) :
    QDialog(parent)

{
    m_all_filter = new QCheckBox("All Calls", this);
    m_all_filter->setCheckState(Qt::Checked);
    m_active_filters.insert(m_all_filter);
    m_blit_filter = new QCheckBox("Blit", this);
    m_draw_filter = new QCheckBox("Draw", this);
    m_write_filter = new QCheckBox("Write", this);
    m_apply = new QPushButton("Apply Filters", this);
    m_apply->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(this, SIGNAL(rejected()), this, SLOT(onReject()));
    connect(m_all_filter, SIGNAL(stateChanged(int)), this, SLOT(selectAllEventsFilter(int)));
    connect(m_blit_filter, SIGNAL(stateChanged(int)), this, SLOT(selectFilter(int)));
    connect(m_draw_filter, SIGNAL(stateChanged(int)), this, SLOT(selectFilter(int)));
    connect(m_write_filter, SIGNAL(stateChanged(int)), this, SLOT(selectFilter(int)));
    connect(m_apply, SIGNAL(clicked()), this, SLOT(applyFilters()));


    QHBoxLayout* filter_buttons_layout = new QHBoxLayout;
    filter_buttons_layout->addWidget(m_apply);

    QHBoxLayout* filter_options_layout = new QHBoxLayout;
    filter_options_layout->addWidget(m_all_filter);
    filter_options_layout->addWidget(m_blit_filter);
    filter_options_layout->addWidget(m_draw_filter);
    filter_options_layout->addWidget(m_write_filter);



    QVBoxLayout* dialog_layout = new QVBoxLayout;
    dialog_layout->addLayout(filter_options_layout);
    dialog_layout->addLayout(filter_buttons_layout);

    setWindowTitle("Event Filters");
    setWindowModality(Qt::NonModal);
    setLayout(dialog_layout);
}

//--------------------------------------------------------------------------------------------------
void FilterDialog::selectAllEventsFilter(int state) {
    if (state == Qt::Checked)
    {
        m_blit_filter->setCheckState(Qt::Unchecked);
        m_draw_filter->setCheckState(Qt::Unchecked);
        m_write_filter->setCheckState(Qt::Unchecked);
        m_filters.clear();
    }
}

//--------------------------------------------------------------------------------------------------
void FilterDialog::selectFilter(int state) {
    if (state == Qt::Checked)
    {
        m_all_filter->setCheckState(Qt::Unchecked);
        auto iterator = std::find_if(m_filters.begin(), m_filters.end(), 
                              [](const QCheckBox* checkBox) { 
                                  return checkBox->text() == "All Calls"; 
                              });
        if (iterator != m_filters.end())
        {
            m_filters.erase(iterator);
        }
        m_filters.insert(qobject_cast<QCheckBox*>(sender()));

        if (m_filters.size() == (kTotalFilterCount - 1) || m_active_filters.size() + 1 == (kTotalFilterCount - 1))
        {
            m_all_filter->setCheckState(Qt::Checked);
        }
    }
    else
    {
        m_filters.erase(qobject_cast<QCheckBox*>(sender()));
    }
}

//--------------------------------------------------------------------------------------------------
void FilterDialog::applyFilters() {
    m_active_filters.clear();
    
    if (m_filters.empty())
    {
        m_all_filter->setCheckState(Qt::Checked);
        m_active_filters.insert(m_all_filter);
        emit FiltersUpdated({m_all_filter->text()});
    }
    else 
    {
        QSet<QString> applied_filter_texts;
        for (QCheckBox* selectedCheckBox : m_filters) {
            if (selectedCheckBox->text() == "All Calls")
            {
                m_active_filters.clear();
                applied_filter_texts.clear();
                m_active_filters.insert(selectedCheckBox);
                applied_filter_texts.insert(selectedCheckBox->text());
                emit FiltersUpdated(applied_filter_texts);
                break;
            }
            m_active_filters.insert(selectedCheckBox);
            applied_filter_texts.insert(selectedCheckBox->text());
        }
        emit FiltersUpdated(applied_filter_texts);
        m_filters.clear();
        this->hide();
    }
}

//--------------------------------------------------------------------------------------------------
void FilterDialog::onReject() {
    close();
}

//--------------------------------------------------------------------------------------------------
void FilterDialog::closeEvent(QCloseEvent *event) 
{
    // Iterate over the copy of filters
    auto unappliedFilters = m_filters;
    for (QCheckBox* checkBox : unappliedFilters)
    {
        checkBox->setCheckState(m_active_filters.count(checkBox) ? Qt::Checked : Qt::Unchecked);
    }

    // Ensure all checkboxes in m_active_filters are checked
    for (QCheckBox* checkBox : m_active_filters)
    {
        if (!checkBox->isChecked())
        {
            checkBox->setCheckState(Qt::Checked);
        }
    }
}
