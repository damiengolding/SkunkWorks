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

void MainWindow::onRefreshRegisteredMediaCalled(){
    QMutexLocker locker(&registeredMediaMutex);
    QStandardItemModel *ret = new QStandardItemModel();
    QStandardItem *root = ret->invisibleRootItem();
    QStandardItem *media = new QStandardItem("Registered media");
    root->appendRow(media);

    ui->applicationOutputTextEdit->append("Refreshing registered media");
    QFileInfo fi(vboxmanageExe);
    if( !fi.exists() ){
        qDebug()<<"VBoxManage.exe not found at: " << fi.absoluteFilePath();
        return;
    }
    media->appendRow(getDriveList(1));
    media->appendRow(getDriveList(2));
    media->appendRow(getDriveList(3));
    emit registeredMediaRefreshed(ret);
}

void MainWindow::updateRegisteredMedia(QStandardItemModel* model){
    ui->registeredMediaTreeView->setModel(model);
}

QStandardItem* MainWindow::getDriveList(int type){
    QStandardItem *ret;
    QString listType;
    switch(type){
    case 1:{
        ret = new QStandardItem(QIcon(":/Resources/Images/HDD.png"),"Hard drives");
        listType = "hdds";
        break;
    }
    case 2:{
        ret = new QStandardItem(QIcon(":/Resources/Images/DVD.png"),"DVD drives");
        listType = "dvds";
        break;
    }
    case 3:{
        ret = new QStandardItem(QIcon(":/Resources/Images/FLOPPY.png"),"Floppy drives");
        listType = "floppies";
        break;
    }
    default:
        qDebug()<<"Incorrect argument to MainWindow::getDriveList(int type): "<<type;
        return(new QStandardItem("Incorrect argument to drive listing"));
    };

    QStringList args;
    args << "list" << listType;
    QProcess *proc = new QProcess();
    proc->start(vboxmanageExe,args);
    proc->waitForReadyRead();
    QString result = proc->readAllStandardOutput();
    if(result.length()==0){
        ui->applicationOutputTextEdit->append("No drives found with: "+ listType);
        return(new QStandardItem("No drives found with list type: " + listType));
    }

    // Parse the text into RegisteredMediaInfo objects
    QStringList resultList = result.split("\n");
    QList<RegisteredMediaInfo*> registeredMediaList;
    RegisteredMediaInfo *info = new RegisteredMediaInfo();
    for(auto result : resultList){
        if( result == "\r"){
            registeredMediaList.append(info);
            info = new RegisteredMediaInfo();
            continue;
        }
        result = result.remove(' ');
        if( result.toLower().startsWith("uuid") ){
            info->setUUID(result.split(':').at(1));
        }
        else if( result.toLower().startsWith("parent") ){
            info->setParentUUID(result.split(':').at(1));
        }
        else if( result.toLower().startsWith("state") ){
            info->setState(result.split(':').at(1));
        }
        else if( result.toLower().startsWith("type") ){
            info->setType(result.split(':').at(1));
        }
        else if( result.toLower().startsWith("location") ){
            int start = result.indexOf(":") + 1;
            int chars = result.length() - start;
            info->setLocation( result.sliced(start,chars) );
        }
        else if( result.toLower().startsWith("storage") ){
            info->setStorageFormat(result.split(':').at(1));
        }
        else if( result.toLower().startsWith("capacity") ){
            info->setCapacity(result.split(':').at(1));
        }
        else if( result.toLower().startsWith("encryption") ){
            info->setEncryption(result.split(':').at(1));
        }
        else{
            continue;
        }
    }
    for(auto info : registeredMediaList){
        QFileInfo fi( info->getLocation() );
        QStandardItem *item = new QStandardItem( fi.absoluteFilePath() );
        item->appendRow(new QStandardItem("UUID: " + info->getUUID()));
        item->appendRow(new QStandardItem("Parent UUID: " + info->getParentUUID()));
        item->appendRow(new QStandardItem("State: " + info->getState()));
        item->appendRow(new QStandardItem("Type: " + info->getType()));
        item->appendRow(new QStandardItem("Stroage format: " + info->getStorageFormat()));
        item->appendRow(new QStandardItem("Capacity: " + info->getCapacity()));
        item->appendRow(new QStandardItem("Encryption: " + info->getEncryption() ));
        ret->appendRow(item);
    }
    return(ret);
}
