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
#include "SettingsDialog.hpp"
#include "PlaylistDialog.hpp"
#include <QProcess>

void MainWindow::onShowSettingsDialog(){
    SettingsDialog *sd = new SettingsDialog(this);
    int ret = sd->exec();
    if(ret == 1){
        //qDebug()<<"onShowSettingsDialog";
        vboxmanageExe = sd->vboxmanageExe;
        homeDirectory = sd->homeDirectory;
        playlistsDirectory = sd->playlistDirectory;
        pluginsDirectory = sd->pluginDirectory;
        QSettings s(qApp->organizationName(),qApp->applicationName());
        startMetricsOnOpen = sd->startMetricsOnOpen;
        sampleInterval = sd->sampleInterval;
        sampleCount = sd->sampleCount;

        additionalPlaylistDirectories = sd->additionalPlaylistDirectories;//.split(';');
        additionalPluginDirectories = sd->additionalPluginDirectories;//.split(';');

        restorePlaylists();
        restorePlugins();
        saveSettings(s);
    }
}

void MainWindow::onShowPlaylistDialog(){
    PlaylistDialog *pld = new PlaylistDialog(this);
    pld->setAvailableMachineList(availableMachineList);
    pld->setPlaylistsDirectory(playlistsDirectory);
    pld->setCurrentFile(QFileInfo("C:/Users/damie/AppData/Roaming/Golding's Gym/Virtual Box++/Playlists/playlist1.vbpl"));
    if(pld->exec() == QDialog::Accepted){
        restorePlaylists();
    }
}

void MainWindow::restoreUserInterfaceStrings(){
    ui->goldingsGymLabel->setText(applicationBanner);
    ui->versionLabel->setText(versionString);
    QString noMachineSelected = "No machine selected";
    ui->vminfoCountersLabel->setText(noMachineSelected);
    ui->metricsCountersLabel->setText(noMachineSelected);
    ui->snapshotsLabel->setText(noMachineSelected);
}

void MainWindow::restoreTables()
{
    ui->availableMachinesTableWidget->setHorizontalHeaderLabels(QStringList() <<"UUID"<<"Name");
    ui->runningMachinesTableWidget->setHorizontalHeaderLabels(QStringList() <<"UUID"<<"Name");
    ui->playlistsTableWidget->setHorizontalHeaderLabels(QStringList() << "Playlists"<< "Location");
    // TODO reimplement for QTreeView
//    ui->machineInfoTableView->setHorizontalHeaderLabels(QStringList() << "Name" << "Value");
    ui->pluginsTableWidget->setHorizontalHeaderLabels(QStringList()<<"Plugin name" << "Location");

    // Table contents
    this->onAvailableMachinesDataRefreshCalled();
    this->onRunningMachinesDataRefreshCalled();
    this->onVMInfoDataRefreshCalled(availableMachineList);
    this->onRefreshRegisteredMediaCalled();
    this->onRefreshConfiguredNetworksCalled();
}

void MainWindow::restoreToolbars(){

    // Create and add to menu bar
    playlistManagerToolbarAction = new QAction(QIcon(":/Resources/Images/PLAYLIST.png"),"Playlist manager");
    ui->menuView->addAction(playlistManagerToolbarAction);
    connect(playlistManagerToolbarAction,SIGNAL(triggered()),this,SLOT(onShowPlaylistDialog()));

    interfaceRefreshToolbarAction = new QAction(QIcon(":/Resources/Images/REFRESH.png"),"Refresh UI");
    ui->menuView->addAction(interfaceRefreshToolbarAction);
    connect(interfaceRefreshToolbarAction,SIGNAL(triggered()),this,SLOT(onRefreshAllUi()));
    ui->menuView->addSeparator();
    playlistRunnerToolbarAction = new QAction(QIcon(":/Resources/Images/PLAYLIST_RUN.png"),"Execute a playlist");
    ui->menuView->addAction(playlistRunnerToolbarAction);

    playlistSchedulerToolbarAction = new QAction(QIcon(":/Resources/Images/PLAYLIST_SCHEDULER.png"),"Schedule a playlist to run regularly through the Windows Task Scheduler (taskschd)");
    ui->menuView->addAction(playlistSchedulerToolbarAction);

//    //addToolBar(Qt::LeftToolBarArea, internalActions);
//    addToolBar(internalActions);
//    internalActions->setAllowedAreas(Qt::AllToolBarAreas);
//    //internalActions->setMovable(false);
//    internalActions->setObjectName("internalActions");
//    settingsToolbarAction = new QAction(QIcon(":/Resources/Images/SETTINGS.png"),"Settings");
//    internalActions->addAction(settingsToolbarAction);
//    connect(settingsToolbarAction,SIGNAL(triggered()),this,SLOT(onShowSettingsDialog()));

//    internalActions->addSeparator();

}

void MainWindow::onRefreshMetricsWindowCalled(){//const QString &name, const QString &uuid){
    metricsVisualization = new MetricsVisualization();//name,uuid);
    metricsVisualization->setRunningMachines(runningMachineList);
    ui->metricsScrollArea->setWidget(metricsVisualization);
}

// TODO Implement this
void MainWindow::onRefreshSnapshotsWindowCalled(const QString &name, const QString &uuid){

}

void MainWindow::onCCMRPlaylistsCalled(const QPoint& point){
//    QMessageBox::information(this,"Virtual Box++","MainWindow::onCCMRPlaylistsCalled");
    QList<QTableWidgetItem*> items = ui->playlistsTableWidget->selectedItems();
    if( items.count() != 1 )
        return;
    QMenu *menu = new QMenu();
    menu->addAction("Show details");
    QAction *selectedAction = menu->exec(QCursor::pos());
    if(!selectedAction)
        return;

    QTableWidgetItem *item = items.at(0);
    int itemColumn = item->column();
    if(itemColumn < 1){
    item = ui->playlistsTableWidget->item(item->row(),item->column()+1 );
    }
    QString fileName = item->text();
    if( fileName.endsWith(".vbpl") ){
//        QMessageBox::information(this,"Virtual Box++","MainWindow::onCCMRPlaylistsCalled" + fileName);
    }
    QFile script(fileName);
    PlaylistDialog *pd = new PlaylistDialog();
    pd->setPlaylistsDirectory(playlistsDirectory);
    pd->loadPlaylistFile(QFileInfo(fileName));
    pd->exec();
}

void MainWindow::onCCMRPluginsCalled(const QPoint& point){
    QMessageBox::information(this,"Virtual Box++","MainWindow::onCCMRPluginsCalled");
}

void MainWindow::showHideExplorerDock(){
    if(ui->explorerDockWidget->isVisible()){
        ui->explorerDockWidget->setVisible(false);
    }
    else{
        ui->explorerDockWidget->setVisible(true);
    }
}

void MainWindow::showHideOutputDock(){
    if(ui->outputDockWidget->isVisible()){
        ui->outputDockWidget->setVisible(false);
    }
    else{
        ui->outputDockWidget->setVisible(true);
    }
}

void MainWindow::onMachineSelectionChanged(const QString &name, const QString &uuid){
    QString tempLabel = metricsCountersLabelText;
    tempLabel.replace("{0}",name);
    tempLabel = tempLabel.replace("{1}",uuid);
    ui->metricsCountersLabel->setText(tempLabel);

    tempLabel = vminfoCountersLabelText;
    tempLabel.replace("{0}",uuid);
    tempLabel = tempLabel.replace("{1}",name);
    ui->vminfoCountersLabel->setText(tempLabel);

    tempLabel = snapshotsLabelText;
    tempLabel.replace("{0}",uuid);
    tempLabel = tempLabel.replace("{1}",name);
    ui->snapshotsLabel->setText(tempLabel);
}
