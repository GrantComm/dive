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

#include "theme_manager.h"
#include <QFile>
#include <QStyle>
#include <QStyleFactory>
#include <QtDBus/QDBusConnection>
#include <QDebug>
#include <QtDBus/QDBusMessage>
#include <iostream>

ThemeManager::ThemeManager(QApplication* app) : m_app(app) {
    qRegisterMetaType<QDBusVariant>("QDBusVariant");

    QDBusConnection::sessionBus().connect(
        "org.freedesktop.portal.Desktop",
        "/org/freedesktop/portal/desktop",
        "org.freedesktop.portal.Settings",
        "SettingChanged",
        this,
        SLOT(onSystemSettingChanged(QString,QString,QDBusVariant))
    );
}

void ThemeManager::SetTheme(Theme theme)
{
    m_currentTheme = theme;

    switch (theme) {
        case Theme::Dark:
            ApplyDarkPalette();
            {
                QFile file(":/stylesheet_dark.qss");
                if (file.open(QFile::ReadOnly)) {
                    m_app->setStyleSheet(file.readAll());
                }
            }
            break;

        case Theme::Light:
            ApplyLightPalette();
            {
                QFile file(":/stylesheet_light.qss");
                if (file.open(QFile::ReadOnly)) {
                    m_app->setStyleSheet(file.readAll());
                }
            }
            break;

        case Theme::Native:
            m_app->setStyleSheet("");
            m_app->setPalette(m_app->style()->standardPalette());
            break;
    }

    emit ThemeChanged(m_currentTheme);
}

bool ThemeManager::IsDark() const
{
    if (m_currentTheme == Theme::Native) {
        return m_app->palette().color(QPalette::Window).value() < 128;
    }
    return m_currentTheme == Theme::Dark;
}

void ThemeManager::ApplyDarkPalette()
{
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(40, 40, 40));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    darkPalette.setColor(QPalette::Disabled, QPalette::Window, QColor(90, 90, 90));
    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::Disabled, QPalette::Base, QColor(80, 80, 80));
    darkPalette.setColor(QPalette::Disabled, QPalette::AlternateBase, QColor(90, 90, 90));
    darkPalette.setColor(QPalette::Disabled, QPalette::ToolTipBase, QColor(90, 90, 90));
    darkPalette.setColor(QPalette::Disabled, QPalette::ToolTipText, QColor(160, 160, 160));
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::Disabled, QPalette::Button, QColor(80, 80, 80));
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::Disabled, QPalette::BrightText, QColor(160, 160, 160));
    darkPalette.setColor(QPalette::Disabled, QPalette::Link, QColor(160, 160, 160));
    darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(90, 90, 90));
    darkPalette.setColor(QPalette::Disabled, QPalette::Light, QColor(53, 53, 53));

    QApplication::setPalette(darkPalette);
}

void ThemeManager::ApplyLightPalette()
{
    m_app->setPalette(m_app->style()->standardPalette());
}

void ThemeManager::LoadStyleSheet(const QString& path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
        m_app->setStyleSheet(file.readAll());
    } else {
        m_app->setStyleSheet("");
    }
}

void ThemeManager::onSystemSettingChanged(QString group, QString key, QDBusVariant value) {
    if (group == "org.freedesktop.appearance" && key == "color-scheme") {
        QVariant v = value.variant();
        
        // Handle cases where the variant is nested
        while (v.canConvert<QDBusVariant>()) {
            v = v.value<QDBusVariant>().variant();
        }
        
        bool is_dark = (v.toUInt() == 1);
        SetTheme(is_dark ? Theme::Dark : Theme::Light);
    }
}