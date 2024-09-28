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

#ifndef RUNNINGMACHINECONSUMER_HPP
#define RUNNINGMACHINECONSUMER_HPP

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>

#include "MachineInfo.hpp"

#include <QObject>

class RunningMachineConsumer : public QObject
{
    Q_OBJECT
public:
    explicit RunningMachineConsumer(MainWindow* mainWindow, QObject *parent = nullptr);


    MainWindow *getMainWindow() const;
    void setMainWindow(MainWindow *newMainWindow);

    QList<VirtualMachine *> getMachineInfoList() const;
    void setMachineInfoList(const QList<VirtualMachine *> &newMachineInfoList);

public slots:
    void RefreshRunningMachines();

signals:
    void RunningMachinesUpdateAvailable(QStandardItemModel *tableModel);
    void RunningMachinesUpdateAvailable(QList<VirtualMachine*> machineInfoList);
    void mainWindowChanged();
    void tableModelChanged();
    void machineInfoListChanged();

private:
    QStandardItemModel *tableModel;
    QList<VirtualMachine*> machineInfoList;
    MainWindow* mainWindow;
    Q_PROPERTY(MainWindow *mainWindow READ getMainWindow WRITE setMainWindow NOTIFY mainWindowChanged)
    Q_PROPERTY(QList<VirtualMachine *> machineInfoList READ getMachineInfoList WRITE setMachineInfoList NOTIFY machineInfoListChanged)

private:
    void createTableModel();
};

#endif // RUNNINGMACHINECONSUMER_HPP
