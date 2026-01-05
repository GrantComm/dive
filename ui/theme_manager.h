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

#pragma once

#include <QObject>
#include <QApplication>
#include <QPalette>
#include <cstddef>
#include <QtDBus/QDBusVariant>

class ThemeManager : public QObject {
    Q_OBJECT
public:
    enum class Theme { Light, Dark, Native };

    explicit ThemeManager(QApplication* app);

    void SetTheme(Theme theme);
    Theme CurrentTheme() const { return m_currentTheme; }
    bool IsDark() const;

signals:
    void ThemeChanged(Theme theme);

public slots:
    void onSystemSettingChanged(QString group, QString key, QDBusVariant value);
private:
    void ApplyDarkPalette();
    void ApplyLightPalette();
    void LoadStyleSheet(const QString& path);

    QApplication* m_app;
    Theme m_currentTheme = Theme::Native;
};