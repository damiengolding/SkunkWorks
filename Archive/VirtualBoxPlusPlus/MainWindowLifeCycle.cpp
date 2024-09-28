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

#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "MetricsMonitor.hpp"
#include <QThread>
#include <QSettings>

// Entry stuff
void MainWindow::doEntryHousekeeping(){
    qDebug()<<"Starting housekeeping on entry ";
    progressDialog = new QProgressDialog("Initializing Virtual Box++ . . . please wait","Cancel",0,100,this);
    restoreApplicationSignature(qApp);
    if(progressDialog->wasCanceled()) return;
    progressDialog->setValue(10);
    restoreSettings();
    if(progressDialog->wasCanceled()) return;
    progressDialog->setValue(20);
    restoreTables();
    if(progressDialog->wasCanceled()) return;
    progressDialog->setValue(40);
    restorePlugins();
    if(progressDialog->wasCanceled()) return;
    progressDialog->setValue(50);
    restorePlaylists();
    if(progressDialog->wasCanceled()) return;
    progressDialog->setValue(60);
    restoreToolbars();
    if(progressDialog->wasCanceled()) return;
    progressDialog->setValue(70);
    onRefreshMetricsWindowCalled(); // REFACT is there a tidier equivalent to the non-existent QString::empty()?
    if(progressDialog->wasCanceled()) return;
    progressDialog->setValue(80);
    restoreUserInterfaceStrings();
    if(progressDialog->wasCanceled()) return;
    progressDialog->setValue(90);
    if(progressDialog->wasCanceled()) return;
    startWorkerThreads();
    progressDialog->setLabelText( "Finished initializing Virtual Box++");
    progressDialog->setCancelButtonText("Exit");
    progressDialog->setValue(100);
    qDebug()<<"Finishing housekeeping on entry ";
    emit setUpComplete();
}

void MainWindow::startWorkerThreads() {
    metricsMonitor = new MetricsMonitor();
    //MetricsMonitor *mm = new MetricsMonitor();
    connect(metricsMonitor,
            SIGNAL(metricsUpdated(QList<QList<MachineMetrics*>>)),
            this,
            SLOT(onMetricsUpdated(QList<QList<MachineMetrics*>>)));

    connect(metricsMonitor,
            SIGNAL(maxReadErrorsReached(int)),
            this,
            SLOT(onMetricsMaxReadErrorReached(int)));

    metricsMonitor->vboxmanageExecutablePath = vboxmanageExe;
    metricsMonitor->setRunningMachines(runningMachineList);
    metricsMonitor->setMaxMetricsErrors(maxMetricsErrors);
    metricsMonitor->setStartMetricsOnOpen( startMetricsOnOpen );
    metricsMonitor->setSampleCount(sampleCount);
    metricsMonitor->setSampleInterval(sampleInterval);
    metricsMonitor->start();
//    qDebug()<<"Started monitor thread";
    startFileSystemWatchers();
}

// TODO QFileWatchers on all source directories
void MainWindow::startFileSystemWatchers(){
    qDebug()<<"Starting file system watchers";
    playlistFileSystemWatcher = new QFileSystemWatcher();
    playlistFileSystemWatcher->addPath(playlistsDirectory.absolutePath());
    playlistFileSystemWatcher->addPaths(additionalPlaylistDirectories);
    connect(playlistFileSystemWatcher,
            SIGNAL(fileChanged(const QString&)),
                   this,
                   SLOT(playlistFileChanged(const QString&))
                        );

            connect(playlistFileSystemWatcher,
                    SIGNAL(directoryChanged(const QString&)),
                           this,
                           SLOT(playlistDirectoryChanged(const QString&))
                                );

                    pluginFileSystemWatcher = new QFileSystemWatcher();

            pluginFileSystemWatcher = new QFileSystemWatcher();
            pluginFileSystemWatcher->addPath(pluginsDirectory.absolutePath());
            pluginFileSystemWatcher->addPaths(additionalPluginDirectories);
            connect(pluginFileSystemWatcher,
                    SIGNAL(fileChanged(const QString&)),
                           this,
                           SLOT(pluginFileChanged(const QString&))
                                );

                    connect(pluginFileSystemWatcher,
                            SIGNAL(directoryChanged(const QString&)),
                                   this,
                                   SLOT(pluginDirectoryChanged(const QString&))
                                        );
}

// REFACT This is messy in a generalised but still irritating way
void MainWindow::restoreSettings()
{
    qDebug()<<"Restoring settings";
    QSettings settings(qApp->organizationName(), qApp->applicationName());
    // Geometry and position
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());

    // Create the directory structure if it doesn't exist
    if (!homeDirectory.exists()) {
        homeDirectory.mkpath(homeDirectory.absolutePath());
    }
    if (!pluginsDirectory.exists()) {
        pluginsDirectory.mkpath(pluginsDirectory.absolutePath());
    }
    if (!playlistsDirectory.exists()) {
        playlistsDirectory.mkpath(playlistsDirectory.absolutePath());
    }
    if (!themesDirectory.exists()) {
        themesDirectory.mkpath(themesDirectory.absolutePath());
    }
    if (!commandsDirectory.exists()) {
        commandsDirectory.mkpath(commandsDirectory.absolutePath());
    }

    // Now handle the QSettings
    vboxmanageExe = settings.value("vboxmanageExe","C:\\Program Files\\Oracle\\VirtualBox\\VBoxManage.exe").toString();
    homeDirectory = settings.value("homeDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++").toString();
    currentDirectory = settings.value("currentDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++").toString();
    playlistsDirectory = settings.value("playlistsDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Playlists").toString();
    pluginsDirectory = settings.value("pluginsDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Plugins").toString();
    commandsDirectory = settings.value("commandsDirectory",QDir::homePath() + "\\AppData\\Roaming\\Golding's Gym\\Virtual Box++\\Commands").toString();

    // REFACT this is a kludge, but it does work
    additionalPlaylistDirectories.clear();
    QStringList directories = settings.value("additionalPlaylistDirectories","dummy;dummy").toString().split(';');
    if(directories.at(0).toLower() != "dummy"){
        for( auto directory : directories){
            QDir d(directory);
            if(d.exists()){
                additionalPlaylistDirectories.append(d.absolutePath());
            }
        }
    }

    additionalPluginDirectories.clear();
    directories = settings.value("additionalPluginDirectories","dummy;dummy").toString().split(';');
    if(directories.at(0).toLower() != "dummy"){
        for( auto directory : directories){
            QDir d(directory);
            if(d.exists()){
                additionalPluginDirectories.append(d.absolutePath());
            }
        }
    }

    // Metrics
    startMetricsOnOpen = settings.value("startMetricsOnOpen",true).toBool();
    sampleInterval = settings.value("sampleInterval",2).toInt();
    sampleCount = settings.value("sampleCount",1800).toInt();
}

void MainWindow::restoreApplicationSignature(QApplication *app){
    app->setApplicationName("Virtual Box++");
    app->setApplicationVersion("2023.1DEV");
    app->setOrganizationName("Golding's Gym");
    app->setOrganizationDomain("https://www.linkedin.com/company/goldings-gym/");
}

// Exit stuff
void MainWindow::doExitHousekeeping(){
    qDebug()<<"Housekeeping on exit ";
    QSettings s(qApp->organizationName(),qApp->applicationName());
    saveSettings(s);
    //saveWindowState();
}

void MainWindow::saveSettings(QSettings &settings)
{
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());

    // Files and directories
    settings.setValue("vboxmanageExe", vboxmanageExe );
    settings.setValue("homeDirectory", homeDirectory.absolutePath() );
    settings.setValue("currentDirectory", currentDirectory.absolutePath() );
    settings.setValue("playlistsDirectory", playlistsDirectory.absolutePath() );
    settings.setValue("pluginsDirectory", pluginsDirectory.absolutePath() );
    settings.setValue("commandDirectory", commandsDirectory.absolutePath() );

    QStringList tempList;
    for(auto dir : additionalPlaylistDirectories){
        if(dir == QDir::currentPath()){
            continue;
        }
        tempList.append(dir);
    }
    if(tempList.count() > 0){
        settings.setValue("additionalPlaylistDirectories", tempList.join(';') );
    }

    tempList.clear();
    for(auto dir : additionalPluginDirectories){
        if(dir == QDir::currentPath()){
            continue;
        }
        tempList.append(dir);
    }
    if(tempList.count() > 0){
        settings.setValue("additionalPluginDirectories", tempList.join(';') );
    }

    // Metrics
    settings.setValue("startMetricsOnOpen",startMetricsOnOpen);
    settings.setValue("sampleInterval",sampleInterval);
    settings.setValue("sampleCount",sampleCount);
}

