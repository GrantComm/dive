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

#include "ui/dive_application.h"

#include <QDebug>
#include <QFile>
#include <QPalette>
#include <QScopedValueRollback>
#include <QString>
#include <QStyle>
#ifdef __linux__
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#elif __APPLE__
#include <QProcess>
#elif _WIN32
#include <QSettings>
#endif

#include "ui/application_controller.h"

struct DiveApplication::Impl
{
    ApplicationController m_controller;

    std::optional<QString> m_style_sheet;

    bool m_is_native_style = false;
};

DiveApplication::DiveApplication(int& argc, char** argv) : QApplication(argc, argv) {}

DiveApplication::~DiveApplication()
{
    // For m_impl.~ImplPointer()
}

ApplicationController& DiveApplication::GetController() { return m_impl->m_controller; }

#if defined(__linux__)
bool DiveApplication::IsLinuxSystemDark()
{
    qRegisterMetaType<QDBusVariant>("QDBusVariant");

    QDBusInterface portal("org.freedesktop.portal.Desktop", "/org/freedesktop/portal/desktop",
                          "org.freedesktop.portal.Settings", QDBusConnection::sessionBus());

    if (portal.isValid())
    {
        QDBusMessage reply = portal.call("Read", "org.freedesktop.appearance", "color-scheme");

        if (reply.type() != QDBusMessage::ErrorMessage && !reply.arguments().isEmpty())
        {
            QVariant v = reply.arguments().at(0);

            while (v.canConvert<QDBusVariant>())
            {
                v = v.value<QDBusVariant>().variant();
            }

            uint32_t value = v.toUInt();
            return (value == 1);
        }
    }

    return qgetenv("GTK_THEME").toLower().contains("-dark");
}
#endif

#if defined(__APPLE__)
bool DiveApplication::IsMacSystemDark()
{
    QProcess process;
    process.start("defaults", {"read", "-g", "AppleInterfaceStyle"});
    process.waitForFinished();
    QString output = process.readAllStandardOutput().trimmed();
    return output == "Dark";
}
#endif

#if defined(_WIN32)
bool IsWindowsSystemDark()
{
    QSettings settings(
        "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        QSettings::NativeFormat);
    // Force QSettings to re-read from the registry hive
    settings.sync();
    // AppsUseLightTheme = 0 means Dark Mode
    return settings.value("AppsUseLightTheme", 1).toUInt() == 0;
}
#endif

void DiveApplication::SetIsNativeStyle(bool is_native_style)
{
    m_impl->m_is_native_style = is_native_style;
}

void DiveApplication::ApplyCustomStyle()
{
    bool is_system_dark = true;

    if (m_impl->m_is_native_style)
    {
#if defined(__linux__)
        is_system_dark = IsLinuxSystemDark();
#elif defined(__APPLE__)
        is_system_dark = IsMacSystemDark();
#elif defined(_WIN32)
        is_system_dark = IsWindowsSystemDark();

        // Reset the palette, which allows
        // the Windows DWM to correctly paint the native window
        // background and title bar in Dark or Light mode.
        QApplication::setPalette(QPalette());
#else
        is_system_dark = (QGuiApplication::palette().color(QPalette::Window).value() < 128);
#endif
    }

    m_impl->m_controller.SetTheme(is_system_dark);

    m_impl->m_style_sheet = m_impl->m_controller.GetStyleSheet();

    setStyleSheet(*m_impl->m_style_sheet);
}

bool DiveApplication::event(QEvent* e)
{
    // Only process dynamic theme changes if we are in Native Mode
    if (m_impl->m_is_native_style &&
        (e->type() == QEvent::ApplicationPaletteChange || e->type() == QEvent::ThemeChange))
    {
        // Make sure we don't recursively calling setPalette.
        // Note event handling only happen on the UI thread.
        static bool guard = false;
        if (!guard && m_impl->m_style_sheet)
        {
            QScopedValueRollback guard_scope(guard, true);
            // Re-apply custom style.
            bool is_dark = false;
#if defined(__linux__)
            is_dark = IsLinuxSystemDark();
#elif defined(__APPLE__)
            is_dark = IsMacSystemDark();
#elif defined(_WIN32)
            is_dark = IsWindowsSystemDark();
#else
            is_dark = (QGuiApplication::palette().color(QPalette::Window).value() < 128);
#endif
            if (is_dark != m_impl->m_controller.IsDarkModeEnabled())
            {
                ApplyCustomStyle();
            }
        }
    }
    return QApplication::event(e);
}
