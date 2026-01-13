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

#include "ui/application_controller.h"

#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QMenu>
#include <QMessageBox>
#include <QStyle>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusMessage>

#include "dive/plugin/loader/plugin_loader.h"
#include "ui/main_window.h"

namespace
{

QPalette GetDarkPalette()
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

    return darkPalette;
}

QPalette GetStandardPalette() { return QApplication::style()->standardPalette(); }

}  // namespace

struct ApplicationController::Impl
{
    MainWindow* m_main_window = nullptr;
    QAction* m_advanced_option = nullptr;

    Dive::PluginLoader m_plugin_manager;

    std::optional<QString> m_style_sheet;
    bool m_is_native_style = false;
    bool m_dark_mode_enabled = false;
};

ApplicationController::ApplicationController()
{
#if defined(__linux__)
    qRegisterMetaType<QDBusVariant>("QDBusVariant");

    QDBusConnection::sessionBus().connect(
        "org.freedesktop.portal.Desktop", "/org/freedesktop/portal/desktop",
        "org.freedesktop.portal.Settings", "SettingChanged", this,
        SLOT(OnSystemSettingChanged(QString, QString, QDBusVariant)));
#endif
}

ApplicationController::~ApplicationController() {}

void ApplicationController::Register(MainWindow& main_window)
{
    m_impl->m_plugin_manager.Bridge().SetQObject(Dive::DiveUIObjectNames::kMainWindow,
                                                 &main_window);
    m_impl->m_main_window = &main_window;
}

bool ApplicationController::AdvancedOptionEnabled() const
{
    return m_impl->m_advanced_option ? m_impl->m_advanced_option->isChecked() : false;
}

void ApplicationController::MainWindowInitialized()
{
    m_impl->m_advanced_option = new QAction(tr("Show Advanced Options"), this);
    m_impl->m_advanced_option->setCheckable(true);
    m_impl->m_advanced_option->setChecked(false);

    m_impl->m_main_window->m_file_menu->insertAction(m_impl->m_main_window->m_exit_action,
                                                     m_impl->m_advanced_option);

    QObject::connect(m_impl->m_advanced_option, &QAction::toggled, this,
                     &ApplicationController::AdvancedOptionToggled);
}

void ApplicationController::MainWindowClosed() { m_impl->m_plugin_manager.UnloadPlugins(); }

bool ApplicationController::InitializePlugins()
{
    if (!m_impl->m_main_window)
    {
        return false;
    }
    // This assumes plugins are in a 'plugins' subdirectory relative to the executable's directory.
    std::string plugin_path = QCoreApplication::applicationDirPath().toStdString() + "/plugins";

    std::filesystem::path plugins_dir_path(plugin_path);

    if (absl::Status load_status = m_impl->m_plugin_manager.LoadPlugins(plugins_dir_path);
        !load_status.ok())
    {
        QMessageBox::warning(m_impl->m_main_window, tr("Plugin Loading Failed"),
                             tr("Failed to load plugins from '%1'. \nError: %2")
                                 .arg(QString::fromStdString(plugin_path))
                                 .arg(QString::fromStdString(std::string(load_status.message()))));
        return false;
    }
    return true;
}

void ApplicationController::SetTheme(bool dark_mode_enabled)
{
    QFile style_sheet;

    if (dark_mode_enabled)
    {
        QApplication::setPalette(GetDarkPalette());
        style_sheet.setFileName(":/stylesheet_dark.qss");
    }
    else
    {
        QApplication::setPalette(GetStandardPalette());
        style_sheet.setFileName(":/stylesheet_light.qss");
    }

    style_sheet.open(QFile::ReadOnly);
    m_impl->m_style_sheet = style_sheet.readAll();
    m_impl->m_dark_mode_enabled = dark_mode_enabled;
    emit ThemeChanged();
}

QIcon ApplicationController::GetMenuItemIcon(const QString& base_icon_name) const
{
    QString suffix = m_impl->m_dark_mode_enabled ? "_icon_dark_mode.png" : "_icon_light_mode.png";
    return QIcon(":/images/" + base_icon_name + suffix);
}

std::optional<QString> ApplicationController::GetStyleSheet() const
{
    return m_impl->m_style_sheet;
}

bool ApplicationController::IsDarkModeEnabled() const { return m_impl->m_dark_mode_enabled; }

void ApplicationController::SetIsNativeStyle(bool is_native_style)
{
    m_impl->m_is_native_style = is_native_style;
}

void ApplicationController::OnSystemSettingChanged(QString group, QString key, QDBusVariant value)
{
    if (!m_impl->m_is_native_style)
    {
        return;
    }

    if (group == "org.freedesktop.appearance" && key == "color-scheme")
    {
        QVariant v = value.variant();

        // Handle cases where the variant is nested
        while (v.canConvert<QDBusVariant>())
        {
            v = v.value<QDBusVariant>().variant();
        }

        bool is_dark = (v.toUInt() == 1);
        SetTheme(is_dark);
    }
}
