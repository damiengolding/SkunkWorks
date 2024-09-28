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

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>

void MainWindow::onRefreshMachinesDisplayCalled(DataUpdateType dataType, QList<VirtualMachine*> machines){
    qDebug()<<"Updating display tables";
    switch(dataType){
    case DataUpdateType::AVAILABLE_VMS:
    {
        qDebug()<<"Available VMs";
        // Clear the table first
        clearTableWidget(ui->availableMachinesTableWidget);
        // Then re-populate it
        int row = 0;
        for(auto machine : machines ){
            // TODO kludge to avoid duplication
            if ( tableHasUuid(ui->availableMachinesTableWidget,machine->getUuid()) ){
                continue;
            }
            QTableWidgetItem *item1 = new QTableWidgetItem();
            item1->setText(machine->getUuid());
            QTableWidgetItem *item2 = new QTableWidgetItem();
            item2->setText(machine->getName());
            ui->availableMachinesTableWidget->insertRow(row);
            ui->availableMachinesTableWidget->setItem(row,0,item1);
            ui->availableMachinesTableWidget->setItem(row,1,item2);
            ++row;
        }
        ui->availableMachinesTableWidget->sortByColumn(1,Qt::AscendingOrder);
        if (row>0) {
            ui->availableMachinesTableWidget->selectRow(0);// setCurrentCell(0,0);
        }
        break;
    }
    case DataUpdateType::RUNNING_VMS:
    {
        qDebug()<<"Running VMs";
        // Clear the table first
        clearTableWidget(ui->runningMachinesTableWidget);
        // Then re-populate it
        int row = 0;
        for(auto machine : machines ){
            // TODO kludge to avoid duplication
            if ( tableHasUuid(ui->runningMachinesTableWidget,machine->getUuid()) ){
                continue;
            }
            QTableWidgetItem *item1 = new QTableWidgetItem();
            item1->setText(machine->getUuid());
            QTableWidgetItem *item2 = new QTableWidgetItem();
            item2->setText(machine->getName());
            ui->runningMachinesTableWidget->insertRow(row);
            ui->runningMachinesTableWidget->setItem(row,0,item1);
            ui->runningMachinesTableWidget->setItem(row,1,item2);
            ++row;
        }
        ui->runningMachinesTableWidget->sortByColumn(1,Qt::AscendingOrder);
        if (row>0) {
            ui->runningMachinesTableWidget->selectRow(0);// setCurrentCell(0,0);
        }
        break;
    }
    default:
        ui->applicationOutputTextEdit->append("Unknown data refresh");
    };
}

// REFACT the name/uuid change probably needs to be turned into a signal and handled by a slot
void MainWindow::onMachineSelectionChangeCalled(QTableWidgetItem* current, QTableWidgetItem* previous) {
    //ui->machineInfoTreeView->reset();
    QString str = current->text();
    MachineInfo* info;// = new MachineInfo();
    for (auto machineInfo : machineInfoList) {
        if (str == machineInfo->Name || str == machineInfo->UUID) {
            info = machineInfo;
            onRefreshVMInfoDisplayCalled(machineInfo);
            // TODO this is where the MetricsVisualization is updated from the machineinfo list data
            metricsVisualization->onSelectedMachineChanged(machineInfo->Name,machineInfo->UUID);
            emit machineSelectionChanged(machineInfo->Name, machineInfo->UUID);
        }
    }
}

void MainWindow::onRefreshVMInfoDisplayCalled(MachineInfo* machineInfo){
//    qDebug()<<"Starting MainWindow::onRefreshVMInfoDisplayCalled for machine name: " << machineInfo->Name << " uuid " << machineInfo->UUID;
    // TODO reimplement for QTreeView
//    ui->machineInfoTreeView->reset();
    // TOIDO thsi is where the QTreeView is repopulated directly from the MachinInfo
    ui->machineInfoTreeView->setModel(machineInfo->getVirtualBoxTreeModel());
    ui->machineSnapshotsTreeView->setModel(machineInfo->getVirtualBoxSnapshotsTreeModel());
}

void MainWindow::restorePlugins(){
//    qDebug()<<"restorePlugins";
    // Clear the table first
    ui-> pluginsTableWidget->clearContents();
    ui->pluginsTableWidget->setRowCount(0);
    int rc = ui->pluginsTableWidget->rowCount();
    for (int i = rc - 1; i > 0; --i) {
        ui->pluginsTableWidget->removeRow(i);
    }
    // Then re-populate it
    onRefreshPluginsCalled(pluginsDirectory);
    for(QDir dir : additionalPluginDirectories){
        onRefreshPluginsCalled(dir);
    }
}

void MainWindow::restorePlaylists(){
    playlistManager = new PlaylistManager();
    //    playlistManager->TestPlaylistText();
    //    qDebug()<<"restorePlaylists";
    // Clear the table first
    ui->playlistsTableWidget->clearContents();
    ui->playlistsTableWidget->setRowCount(0);
    int rc = ui->playlistsTableWidget->rowCount();
    for (int i = rc - 1; i > 0; --i) {
        ui->playlistsTableWidget->removeRow(i);
    }
    // Then re-populate it
    onRefreshPlaylistsCalled(playlistsDirectory);
    for(QDir dir : additionalPlaylistDirectories){
        onRefreshPlaylistsCalled(dir);
    }
}

// FIXME why isn't this displaying location for the second calls to aditional directories?
QList<QFileInfo> MainWindow::onRefreshPluginsCalled(QDir directory){
    QList<QFileInfo> files = directory.entryInfoList(QStringList()<<"*.dll");
    //qDebug()<<"Plugins: "<< files.count();
    int row = 0;
    for(auto file : files){
        QTableWidgetItem* item1 = new QTableWidgetItem();
        QTableWidgetItem* item2 = new QTableWidgetItem();
        item1->setText(file.fileName());
        item2->setText(file.absoluteFilePath());
        ui->pluginsTableWidget->insertRow(row);
        ui->pluginsTableWidget->setItem(row, 0, item1);
        ui->pluginsTableWidget->setItem(row, 1, item2);
        ++row;
    }
    ui->pluginsTableWidget->sortByColumn(0,Qt::AscendingOrder);
    if (row>0) {
        ui->pluginsTableWidget->selectRow(0);// setCurrentCell(0,0);
    }
    return(files);
}

// FIXME why isn't this displaying location for the second calls to aditional directories?
QList<QFileInfo> MainWindow::onRefreshPlaylistsCalled(QDir directory){
    QList<QFileInfo> files = directory.entryInfoList(QStringList()<<"*.vbpl");
    //    qDebug()<<"Playlists: "<< files.count();
    int row = 0;
    for(auto file : files){
        QString ifName = file.absoluteFilePath();
        QJsonObject jsonObject;
        QScopedPointer<PlaylistDefinition> playlistDefinition(new PlaylistDefinition());
        //QJsonDocument jsonDocument;
        QFile inputFile(ifName);
        if( !inputFile.open(QIODevice::ReadOnly | QIODevice::Text) ){
            qDebug()<<"Unable to open file " << ifName << " for opening";
            continue;
        }
        QTextStream inputStream(&inputFile);
        QString rawJson = inputStream.readAll();
        QString playlistName;
        jsonObject = QJsonDocument::fromJson(rawJson.toLatin1()).object();
        playlistDefinition->Read(jsonObject);
        if( jsonObject.contains("name") && jsonObject["name"].isString() ){
            playlistName = jsonObject["name"].toString();
        }
        else{
            qDebug()<< "The supplied playlist file doesn't appear to contain valid playlist JSON";
            continue;
        }
        //qDebug()<<"Playlist name at MainWindow::onRefreshPlaylistsCalled: "<<playlistName;
        QTableWidgetItem* item1 = new QTableWidgetItem();
        QTableWidgetItem* item2 = new QTableWidgetItem();
        item1->setText(playlistName);
        item2->setText(file.absoluteFilePath());
        ui->playlistsTableWidget->insertRow(row);
        ui->playlistsTableWidget->setItem(row, 0, item1);
        ui->playlistsTableWidget->setItem(row, 1, item2);
        ++row;
    }
    ui->playlistsTableWidget->sortByColumn(0,Qt::AscendingOrder);
    if (row>0) {
        ui->playlistsTableWidget->selectRow(0);// setCurrentCell(0,0);
    }
    return(files);
}

void MainWindow::onMetricsUpdated(QList<QList<MachineMetrics*>> metrics) {
    QMutexLocker locker(&machineMetricsMutex);
    currentMetrics = metrics;
//    qDebug()<<"Received updated metrics: " << QString::number(metrics.count());
    emit metricsUpdateAvailable(currentMetrics);

    QtConcurrent::run([=]{
        metricsVisualization->onMetricsUpdateAvailable(currentMetrics);
    });
}
