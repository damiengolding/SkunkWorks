/* 
   Copyright (C) Damien Golding
   
   This is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this software; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA

  Don't use it to find and eat babies ... unless you're really REALLY hungry ;-)

*/

#ifndef SETTINGSDIALOG_HPP
#define SETTINGSDIALOG_HPP

#include <QDialog>
#include <QSettings>
#include <QMenu>

#include "MainWindow.hpp"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    QString vboxmanageExe;
    QDir homeDirectory;
    QDir playlistDirectory;
    QDir pluginDirectory;
    QDir commandDirectory;
    QStringList additionalPlaylistDirectories;
    QStringList additionalPluginDirectories;
    bool startMetricsOnOpen = true;
    int sampleInterval = 2;
    int sampleCount = 1800;

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private:
    Ui::SettingsDialog *ui;
    QSettings *settings;
    void setUpData();
    void saveData();
    void setUpConnections();
    void setUpTables();

private slots:
    void onVBoxManageExeChanged(const QString &text);
    void onHomeDirectoryChanged(const QString &text);
    void onPlaylistDirectoryChanged(const QString &text);
    void onPluginDirectoryChanged(const QString &text);
    void onVBoxManagePushButton();
    void onHomePushButton();
    void onPlaylistPushButton();
    void onPluginPushButton();

    void onCCMRAddPluginsDirectoryCalled(const QPoint &point);
   void onCCMRAddPlaylistsDirectoryCalled(const QPoint& point);
    void doCCMRMenu(int i);

    void onPlaylistDirectoriesChanged(const QString &dir,bool added);
    void onPluginDirectoriesChanged(const QString &dir,bool added);

    void onMetricsFromStartupRadioButtonChanged(bool checked);
    void onSampleIntervalSpinBoxChanged(int value);
    void onSampleCountSpinBoxChanged(int value);

    void onTabBarDoubleClicked(int i );
};

#endif // SETTINGSDIALOG_HPP
