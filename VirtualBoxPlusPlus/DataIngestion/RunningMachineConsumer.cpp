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

#include "RunningMachineConsumer.hpp"

RunningMachineConsumer::RunningMachineConsumer(MainWindow* mainWindow, QObject *parent)
    : mainWindow(mainWindow), QObject{parent}
{

}

void RunningMachineConsumer::RefreshRunningMachines()
{
    QMutexLocker locker(&mainWindow->runningMachinesMutex);
    mainWindow->ui->applicationOutputTextEdit->append("Refreshing running machines");
    QFileInfo fi(mainWindow->vboxmanageExe);
    if( fi.exists() ){
        mainWindow->ui->applicationOutputTextEdit->append("VBoxManage.exe found at: " + fi.absoluteFilePath());
    }
    else{
        mainWindow->ui->applicationOutputTextEdit->append("VBoxManage.exe not found at: " + fi.absoluteFilePath());
        return;
    }
    QStringList args;
    args << "list" << "runningvms";
    QProcess *proc = new QProcess();
    proc->start(mainWindow->vboxmanageExe,args);
    proc->waitForReadyRead();
    QString result = proc->readAllStandardOutput();
    if(result.length()==0){
        mainWindow->ui->applicationOutputTextEdit->append("No running virtual machines found");
    }
    else{
        QString message = QString::number(result.split("\r\n").count());
        message += " running virtual machines found";
        mainWindow->ui->applicationOutputTextEdit->append(message);
        QStringList lineSplit = result.split("\n");
        QString trimQuotes;
        for( auto line : lineSplit){
            QStringList parts = line.split(" ");
            if( parts.count() != 2 ){
                continue;
            }
            VirtualMachine *vm = new VirtualMachine();
            trimQuotes = MainWindow::unQuote(parts[0]);
            vm->setName(trimQuotes);
            vm->setUuid(parts[1]);
            machineInfoList.append(vm);
        }
        emit RunningMachinesUpdateAvailable(machineInfoList);
        createTableModel();
    }
}

void RunningMachineConsumer::createTableModel()
{
    tableModel = new QStandardItemModel();
    int counter = 0;
    for(auto info : machineInfoList){
        QStandardItem *name = new QStandardItem(info->getName());
        QStandardItem *uuid = new QStandardItem(info->getUuid());
        tableModel->setItem(counter,0,name);
        tableModel->setItem(counter,1,uuid);
        ++counter;
    }
    emit RunningMachinesUpdateAvailable(tableModel);
}

QList<VirtualMachine *> RunningMachineConsumer::getMachineInfoList() const
{
    return machineInfoList;
}

void RunningMachineConsumer::setMachineInfoList(const QList<VirtualMachine *> &newMachineInfoList)
{
    if (machineInfoList == newMachineInfoList)
        return;
    machineInfoList = newMachineInfoList;
    emit machineInfoListChanged();
}

MainWindow *RunningMachineConsumer::getMainWindow() const
{
    return mainWindow;
}

void RunningMachineConsumer::setMainWindow(MainWindow *newMainWindow)
{
    if (mainWindow == newMainWindow)
        return;
    mainWindow = newMainWindow;
    emit mainWindowChanged();
}
