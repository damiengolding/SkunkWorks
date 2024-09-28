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

// REFACT Tidy up zombie code here
void MainWindow::onVMInfoDataRefreshCalled(QList<VirtualMachine*> machines) {
    qDebug()<<"Starting MainWindow::onVMInfoDataRefreshCalled";
    QMutexLocker locker(&vmInfoMutex);
    QFileInfo fi(vboxmanageExe);
    if (fi.exists()) {
        ui->applicationOutputTextEdit->append("VBoxManage.exe found at: " + fi.absoluteFilePath());
    }
    else {
        ui->applicationOutputTextEdit->append("VBoxManage.exe not found at: " + fi.absoluteFilePath());
        return;
    }
    QStringList args;
    QProcess *proc;
    QString result;
    QList<MachineInfo*> infoList;

    for (auto machine : machines) {
        args.clear();
        args << "showvminfo" << machine->getName() << "--details" << "--machinereadable";
        proc = new QProcess();
        proc->start(vboxmanageExe, args);
        if(!proc->waitForReadyRead()){
//            qDebug()<<"waitforreadyread()";
            return;
        }
        else{
//            qDebug()<<"ready read";
        }

        if( !proc->waitForFinished() ){
//            qDebug()<<"waitforfinished()";
            return;
        }
        else{
//            qDebug()<<"finished";
        }
        result = proc->readAllStandardOutput();
        if (result.length() == 0) {
            ui->applicationOutputTextEdit->append("No machine information was disclosed for: " + machine->getName());
        }
        else {
            infoList.append( onVBoxManageVMInfoOutputAvailable(result, machine->getName(), machine->getUuid()));
        }
    }
    machineInfoList = infoList;
    emit infoUpdateAvailable(DataUpdateType::SHOW_VMINFO, machineInfoList);
}

MachineInfo* MainWindow::onVBoxManageVMInfoOutputAvailable(const QString& outputText, const QString& name, const QString& uuid) {
    MachineInfo* machineInfo = new MachineInfo();
    machineInfo->Name = name;
    machineInfo->UUID = uuid;
    machineInfo->parseFromShowVMInfoOutput(outputText);
//    machineInfo->createStandardModel(outputText);
    return(machineInfo);
}

// HPCOMP
QList<VirtualMachine*> MainWindow::onVBoxManageListOutputAvailable(DataUpdateType dataType, const QString &outputText){
    auto ret = QList<VirtualMachine*>();
    auto items = outputText.split("\r\n");
    QString trimQuotes;
    for(auto item : items){
        QStringList parts = item.split(" ");
        if(parts.length() != 2 ){
            continue;
        }
        VirtualMachine *vm = new VirtualMachine();
        trimQuotes = unQuote(parts[0]);
        vm->setName(trimQuotes);
        vm->setUuid(parts[1]);
        ret.append(vm);
    }
    return(ret);
}
