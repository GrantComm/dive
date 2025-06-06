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

#pragma once

// Forward declarations
class QLabel;
class QHBoxLayout;
class QIcon;
class QPlainTextEdit;
class QPushButton;
class QVBoxLayout;

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    AboutDialog(QWidget *parent = 0);

private:
    QIcon          *m_icon;                  // The Dive icon
    QLabel         *m_icon_label;            // A label widget to hold the icon.
    QLabel         *m_build_information;     // The build info and version string.
    QLabel         *m_third_party_licenses;  // The NOTICE file text.
    QPlainTextEdit *m_license_notice;        // An edit box to hold the NOTICE text.
    QPushButton    *m_close_button;          // A button to close the dialog.
    QHBoxLayout *m_version_layout;  // The version layout is Icon + Build Info arranged horizontally
    QHBoxLayout *m_button_layout;   // The button layout is stretch + Close Button
    QVBoxLayout *m_main_layout;     // The main layout Version + Text + Licenses arranged vertically
};
