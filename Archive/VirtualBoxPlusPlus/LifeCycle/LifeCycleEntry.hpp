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

#ifndef LIFECYCLEENTRY_HPP
#define LIFECYCLEENTRY_HPP

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QObject>

#include "PlaylistManager.hpp"

class LifeCycleEntry : public QObject
{
    Q_OBJECT
public:
    explicit LifeCycleEntry(MainWindow *mainWindow, QObject *parent = nullptr);
    MainWindow *getMainWindow() const;
    void setMainWindow(MainWindow *newMainWindow);

public slots:
    void doEntryHousekeeping();
    void connectObjects();
    void restoreTables();
    //void restoreWindowState();
    void restoreApplicationSignature(QApplication *app);
    void restoreSettings();
//    void restoreEnvironment();
    void restorePlugins();
    void restorePlaylists();
    void restoreUserInterfaceStrings();
    void restoreToolbars();
    void startWorkerThreads();
    void startFileSystemWatchers();

signals:
    void mainWindowChanged();
    void setUpComplete();

private:
    MainWindow *mainWindow;
    Q_PROPERTY(MainWindow *mainWindow READ getMainWindow WRITE setMainWindow NOTIFY mainWindowChanged)

private:
    QToolBar *internalActions = new QToolBar();
    QAction *settingsToolbarAction;
    QAction *playlistManagerToolbarAction;
    QAction *playlistRunnerToolbarAction;
    QAction *playlistSchedulerToolbarAction;
    QAction *interfaceRefreshToolbarAction;
    MetricsMonitor *metricsMonitor;
    QFileSystemWatcher *playlistFileSystemWatcher;
    QFileSystemWatcher *pluginFileSystemWatcher;
};

#endif // LIFECYCLEENTRY_HPP
