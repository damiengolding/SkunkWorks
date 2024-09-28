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

void MainWindow::onAvailableMachinesDataRefreshCalled(){
    QMutexLocker locker(&availableMachinesMutex);
    ui->applicationOutputTextEdit->append("Refreshing available machines");
    QFileInfo fi(vboxmanageExe);
    if( !fi.exists() ){
        qDebug()<<"VBoxManage.exe not found at: " << fi.absoluteFilePath();
        return;
    }
    QStringList args;
    args << "list" << "vms";
    QProcess *proc = new QProcess();
    proc->start(vboxmanageExe,args);
    proc->waitForReadyRead();

    QString result = proc->readAllStandardOutput();
    if(result.length()==0){
        ui->applicationOutputTextEdit->append("No registered virtual machines found");
    }
    else{
        qDebug()<< QString::number(result.split("\r\n").count()) << " registered virtual machines found";
        availableMachineList = onVBoxManageListOutputAvailable(DataUpdateType::AVAILABLE_VMS, result);
        emit dataUpdateAvailable(DataUpdateType::AVAILABLE_VMS, availableMachineList);
    }
}

// REFACT I don't like the way that the if-elseif thing is going . . .
void MainWindow::onCCMRAvailableMachinesCalled(const QPoint &point){
    QList<QTableWidgetItem*> items = ui->availableMachinesTableWidget->selectedItems();
    if(items.length() !=1){
        return;
    }
    QTableWidgetItem *item = items.at(0);
    QMenu *cm = new QMenu();
    cm->addAction("Copy");
    cm->addSeparator();
    cm->addAction("Start machine");
    QAction *selectedAction = cm->exec(QCursor::pos());
    if(!selectedAction){
        return;
    }

    QString actStr = selectedAction->text();

    if(actStr.toLower() == "copy" ){
        QGuiApplication::clipboard()->setText( item->text() );
    }
    else if(actStr.toLower() == "start machine"){
        QMessageBox::information(this,dialogTitle,"Starting machine " + item->text() );
    }
}
