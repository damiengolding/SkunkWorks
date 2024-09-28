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

#include <QProcess>

void MainWindow::connectObjects()
{
    // Menu and tool bar actions
    connect(ui->actionAboutQt,SIGNAL(triggered()),this,SLOT(onShowAboutQt()));
    connect(ui->actionHelp,SIGNAL(triggered()),this,SLOT(onShowVBoxPlusPlusHelp()));
    connect(ui->actionAboutVirtualBoxPlusPlus,SIGNAL(triggered()),this,SLOT(onShowAboutVboxPlusPlus()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(onApplicationExitCalled()));
    connect(ui->actionSettings,SIGNAL(triggered()),this,SLOT(onShowSettingsDialog()));

    // Data ingestion and display actions
    connect(this,SIGNAL(dataUpdateAvailable(DataUpdateType, QList<VirtualMachine*>)),this,SLOT(onRefreshMachinesDisplayCalled(DataUpdateType, QList<VirtualMachine*>)));

    // Main menu actions
    connect(ui->actionExplorerDockWindow,SIGNAL(triggered()),this,SLOT(showHideExplorerDock()));
    connect(ui->actionOutputDockWindow,SIGNAL(triggered()),this,SLOT(showHideOutputDock()));

    //Context menu actions
    connect(ui->availableMachinesTableWidget,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(onCCMRAvailableMachinesCalled(const QPoint&)));
    connect(ui->runningMachinesTableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onCCMRRunningMachinesCalled(const QPoint&)));
    connect(ui->playlistsTableWidget,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(onCCMRPlaylistsCalled(const QPoint&)));
    connect(ui->pluginsTableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onCCMRPluginsCalled(const QPoint&)));
    connect(this,SIGNAL(machineSelectionChanged(const QString&, const QString&)),this,SLOT(onMachineSelectionChanged(const QString&, const QString&)));

    // Data display actions
    connect(ui->availableMachinesTableWidget,
            SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)),
            this,
            SLOT(onMachineSelectionChangeCalled(QTableWidgetItem*, QTableWidgetItem*)));
    connect(ui->runningMachinesTableWidget,
            SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)),
            this,
            SLOT(onMachineSelectionChangeCalled(QTableWidgetItem*, QTableWidgetItem*)));

    connect(this,
             SIGNAL(refreshUiRequested()),
             this,
             SLOT(onRefreshAllUi() ) );

    connect(this,
            SIGNAL(registeredMediaRefreshed(QStandardItemModel*)),
            this,
            SLOT(updateRegisteredMedia(QStandardItemModel*))
            );

    connect(this,
            SIGNAL(configuredNetworksRefreshed(QStandardItemModel*)),
            this,
            SLOT(updateConfiguredNetworks(QStandardItemModel*))
            );
}

// File system watcher slots
void MainWindow::playlistDirectoryChanged(const QString &path){
    qDebug()<<"MainWindow::pluginDirectoryChanged: "<<path;
}
void MainWindow::pluginDirectoryChanged(const QString &path){
    qDebug()<<"MainWindow::pluginDirectoryChanged: "<<path;
}
void MainWindow::playlistFileChanged(const QString &path){
    qDebug()<<"MainWindow::playlistFileChanged: "<<path;
}
void MainWindow::pluginFileChanged(const QString &path){
    qDebug()<<"MainWindow::pluginFileChanged: "<<path;
}
void MainWindow::addPlaylistDirectoryToFSW(const QString &path){
    qDebug()<<"MainWindow::addPlaylistDirectoryToFSW: "<<path;
}
void MainWindow::removePlaylistDirectoryFromFSW(const QString &path){
    qDebug()<<"MainWindow::removePlaylistDirectoryFromFSW: "<<path;
}
void MainWindow::addPluginDirectoryToFSW(const QString &path){
    qDebug()<<"MainWindow::addPluginDirectoryToFSW: "<<path;
}
void MainWindow::removePluginDirectoryFromFSW(const QString &path){
    qDebug()<<"MainWindow::removePluginDirectoryFromFSW: "<<path;
}

// Slots
void MainWindow::onShowAboutQt()
{
    QApplication::aboutQt();
}

void MainWindow::onShowAboutVboxPlusPlus(){
    QMessageBox::information(this,dialogTitle,"Author: Damien Golding\r\nVersion: 2023.1DEV\r\nProduct: Virtual Box++\r\nLicense: GPL > 2");
}

void MainWindow::onShowVBoxPlusPlusHelp(){
    QMessageBox::information(this, dialogTitle,"You've gotta be KIDDING!");

}

void MainWindow::closeEvent(QCloseEvent *event){
    //qDebug()<<"closeEvent";
    onApplicationExitCalled();
    event->accept();
}

void MainWindow::onApplicationExitCalled(){
    doExitHousekeeping();
    QMainWindow::close();
}

void MainWindow::onProcessFinished(int exitCode, QProcess::ExitStatus){
    qDebug()<<"A process has finished with exit code: "<<exitCode;
}

void MainWindow::onMetricsMaxReadErrorReached(int errors){
    //qDebug()<<"Metrics monitor reached max read errors: "<<errors;
}
