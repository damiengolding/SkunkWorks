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

#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include <QSettings>
#include <QFileInfo>
#include <QToolBar>
#include <QClipboard>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QScopedPointer>
#include <QDebug>
#include <QtConcurrent>
#include <QProgressDialog>
#include <QClipboard>

#include "VirtualMachine.hpp"
#include "MachineInfo.hpp"
#include "MachineMetrics.hpp"
#include "MetricsMonitor.hpp"
#include "MetricsVisualization.hpp"
#include "MetricsCounter.hpp"
#include "PlaylistManager.hpp"

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

using namespace VirtualBoxPlusPlus;

void MainWindow::onRefreshAllUi(){
    QMessageBox::information(this,"Virtual Box++","Refresh all ui called");
    onRefreshAvailableVMList();
    onRefreshRunningVMList();
}

void MainWindow::onRefreshAvailableVMList(){
    clearTableWidget( ui->availableMachinesTableWidget );
    onAvailableMachinesDataRefreshCalled();
    onRefreshRunningVMList();
}

void MainWindow::onRefreshRunningVMList(){
    clearTableWidget(ui->runningMachinesTableWidget);
    onRunningMachinesDataRefreshCalled();
//    qDebug()<< "MainWindow::onRefreshRunningVMList: Running machines count: " << runningMachineList.count();
    metricsVisualization->setRunningMachines(runningMachineList);
}
