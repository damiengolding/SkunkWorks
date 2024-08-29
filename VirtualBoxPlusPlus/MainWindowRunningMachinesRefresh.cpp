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

 // WWKGDO QScopedPointer on *proc?
void MainWindow::onRunningMachinesDataRefreshCalled(){
    QMutexLocker locker(&runningMachinesMutex);
    ui->applicationOutputTextEdit->append("Refreshing running machines");
    QFileInfo fi(vboxmanageExe);
    if( fi.exists() ){
        ui->applicationOutputTextEdit->append("VBoxManage.exe found at: " + fi.absoluteFilePath());
    }
    else{
        ui->applicationOutputTextEdit->append("VBoxManage.exe not found at: " + fi.absoluteFilePath());
        return;
    }
    QStringList args;
    args << "list" << "runningvms";
    QProcess *proc = new QProcess();
    proc->start(vboxmanageExe,args);
    proc->waitForReadyRead();
    QString result = proc->readAllStandardOutput();
    if(result.length()==0){
        ui->applicationOutputTextEdit->append("No running virtual machines found");
    }
    else{
        QString message = QString::number(result.split("\r\n").count());
        message += " running virtual machines found";
        ui->applicationOutputTextEdit->append(message);
        runningMachineList = onVBoxManageListOutputAvailable(DataUpdateType::RUNNING_VMS, result);
        emit dataUpdateAvailable(DataUpdateType::RUNNING_VMS, runningMachineList);
    }
}

// REFACT I don't like the way that the if-elseif thing is going . . .
void MainWindow::onCCMRRunningMachinesCalled(const QPoint& point) {
    QList<QTableWidgetItem*> items = ui->runningMachinesTableWidget->selectedItems();
    if (items.length() != 1) {
        return;
    }
    QTableWidgetItem* item = items.at(0);
    QMenu* cm = new QMenu();
    cm->addAction("Copy");
    cm->addSeparator();
    cm->addAction("Stop machine");
    QAction* selectedAction = cm->exec(QCursor::pos());
    if (!selectedAction) {
        return;
    }
    QString actStr = selectedAction->text();
    if (actStr.toLower() == "copy") {
        QGuiApplication::clipboard()->setText(item->text());
    }
    else if (actStr.toLower() == "stop machine") {
        QMessageBox::information(this, dialogTitle, "Stopping machine " + item->text());
    }
}
