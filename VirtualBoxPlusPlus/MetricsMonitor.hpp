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

#pragma once

#include <QThread>
#include <QDebug>
#include "MachineMetrics.hpp"
#include "VirtualMachine.hpp"

#include <vector>
using namespace std;

class MetricsMonitor  : public QThread
{
	Q_OBJECT
        void run() override;
public:
	MetricsMonitor(QObject *parent = nullptr);
	~MetricsMonitor();
	
    int maxMetricsErrors = 0;
	QString vboxmanageExecutablePath = "C:\\Program Files\\Oracle\\VirtualBox\\VBoxManage.exe";


    int getMaxMetricsErrors() const;
    void setMaxMetricsErrors(int newMaxMetricsErrors);

    QString getVboxmanageExecutablePath() const;
    void setVboxmanageExecutablePath(const QString &newVboxmanageExecutablePath);

    QList<VirtualMachine *> getRunningMachines() const;
    void setRunningMachines(const QList<VirtualMachine *> &newRunningMachines);

    bool getStartMetricsOnOpen() const;
    void setStartMetricsOnOpen(bool newStartMetricsOnOpen);

    int getSampleInterval() const;
    void setSampleInterval(int newSampleInterval);

    int getSampleCount() const;
    void setSampleCount(int newSampleCount);

private:
    QList<MachineMetrics*> parseMetrics(QStringList metricStrings);
    MachineMetrics* getMachineMetrics(QList<MachineMetrics*>& metricsList, const QString &machineName, const QString &metricName, const QString &metricData);
    MachineMetrics::MeasureType stringToMeasureType(const QString &typeStr, QString &out);
    QList<VirtualMachine*> runningMachines;

    bool startMetricsOnOpen = true;
    int sampleInterval = 2;
    int sampleCount = 1800;

    Q_PROPERTY(QList<VirtualMachine *> runningMachines READ getRunningMachines WRITE setRunningMachines NOTIFY runningMachinesChanged)
    Q_PROPERTY(bool startMetricsOnOpen READ getStartMetricsOnOpen WRITE setStartMetricsOnOpen NOTIFY startMetricsOnOpenChanged)
    Q_PROPERTY(int sampleInterval READ getSampleInterval WRITE setSampleInterval NOTIFY sampleIntervalChanged)
    Q_PROPERTY(int sampleCount READ getSampleCount WRITE setSampleCount NOTIFY sampleCountChanged)
    Q_PROPERTY(int maxMetricsErrors READ getMaxMetricsErrors WRITE setMaxMetricsErrors NOTIFY maxMetricsErrorsChanged)
    Q_PROPERTY(QString vboxmanageExecutablePath READ getVboxmanageExecutablePath WRITE setVboxmanageExecutablePath NOTIFY vboxmanageExecutablePathChanged)

signals:
    void metricsUpdated(QList<QList<MachineMetrics*>> metrics);
	void metricsUpdated(QString metrics);
    void maxReadErrorsReached(int errors);
    void maxMetricsErrorsChanged();
    void vboxmanageExecutablePathChanged();
    void delayChanged();
    void runningMachinesChanged();
    void startMetricsOnOpenChanged();
    void sampleIntervalChanged();
    void sampleCountChanged();
};
