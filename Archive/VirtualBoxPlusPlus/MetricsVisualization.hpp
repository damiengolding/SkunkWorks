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

  Don't use it to find and eat babies ... unless you're really REALLY hungry

*/

#ifndef METRICSVISUALIZATION_HPP
#define METRICSVISUALIZATION_HPP

#include <QWidget>
#include <QGridLayout>
#include <QMessageBox>
#include <QtConcurrent>
#include <QLineSeries>
#include <QCategoryAxis>
#include <QValueAxis>
#include <QBarSet>
#include <QBarSeries>

#include "MetricsCounter.hpp"
#include "MachineMetrics.hpp"
#include "VirtualMachine.hpp"

namespace Ui {
class MetricsVisualization;
}

class MetricsVisualization : public QWidget
{
    Q_OBJECT

public:
    explicit MetricsVisualization(QWidget *parent = nullptr);
    ~MetricsVisualization();

    QString getName() const;
    void setName(const QString &newName);

    QString getUUID() const;
    void setUUID(const QString &newUUID);

    QList<VirtualMachine *> getRunningMachines() const;
    void setRunningMachines(const QList<VirtualMachine *> &newRunningMachines);

private:
    QList<QList<MachineMetrics*>> internalMetricsList;
    QList<VirtualMachine*> runningMachines;

public slots:
    void onMetricsUpdateAvailable(QList<QList<MachineMetrics*>> metricsList);
    void onSelectedMachineChanged(const QString &machineName, const QString &uuid);

private slots: // Chart update funcs
    void clearCharts();
    void updateCharts(const QString &machineName);
    void updateCPULoadUser(MachineMetrics * metrics);
    void updateCPULoadKernel(MachineMetrics * metrics);
    void updateRAMUsageUsed(MachineMetrics * metrics);
    void updateDiskUsageUsed(MachineMetrics * metrics);
    void updateNetRateTX(MachineMetrics * metrics);
    void updateNetRateRX(MachineMetrics * metrics);
    void updateGuestCPULoadUser(MachineMetrics * metrics);
    void updateGuestCPULoadKernel(MachineMetrics * metrics);
    void updateGuestCPULoadIdle(MachineMetrics * metrics);
    void updateGuestRAMUsageTotal(MachineMetrics * metrics);
    void updateGuestRAMUsageFree(MachineMetrics * metrics);
    void updateGuestRAMUsageBalloon(MachineMetrics * metrics);
    void updateGuestRAMUsageShared(MachineMetrics * metrics);
    void updateGuestRAMUsageCache(MachineMetrics * metrics);
    void updateGuestPagefileUsageTotal(MachineMetrics * metrics);

signals:
    void NameChanged();
    void UUIDChanged();
    // Charts
    void UpdateChartsReady(const QString &machineName);
    void UpdateCPULoadUserReady(MachineMetrics *metrics);
    void UpdateCPULoadKernelReady(MachineMetrics *metrics);
    void UpdateRAMUsageUsedReady(MachineMetrics *metrics);
    void UpdateDiskUsageUsedReady(MachineMetrics *metrics);
    void UpdateNetRateTxReady(MachineMetrics *metrics);
    void UpdateNetRateRxReady(MachineMetrics *metrics);
    void UpdateGuestCPULoadUserReady(MachineMetrics *metrics);
    void UpdateGuestCPULoadKernelReady(MachineMetrics *metrics);
    void UpdateGuestCPULoadIdleReady(MachineMetrics *metrics);
    void UpdateGuestRAMUsageTotalReady(MachineMetrics *metrics);
    void UpdateGuestRAMUsageFreeReady(MachineMetrics *metrics);
    void UpdateGuestRAMUsageBalloonReady(MachineMetrics *metrics);
    void UpdateGuestRAMUsageSharedReady(MachineMetrics *metrics);
    void UpdateGuestRAMUsageCacheReady(MachineMetrics *metrics);
    void UpdateGuestPagefileUsageTotalReady(MachineMetrics *metrics);

    void runningMachinesChanged();

private:
    Ui::MetricsVisualization *ui;
    QGridLayout *centralLayout;
    MetricsCounter *machineCPULoadUserCounter;
    MetricsCounter *machineCPULoadKernelCounter;
    MetricsCounter *machineRAMUsageUsedCounter;
    MetricsCounter *machineDiskUsageUsedCounter;
    MetricsCounter *machineNetRateTxCounter;
    MetricsCounter *machineNetRateRxCounter;
    MetricsCounter *machineGuestCPULoadUserCounter;
    MetricsCounter *machineGuestCPULoadKernelCounter;
    MetricsCounter *machineGuestCPULoadIdleCounter;
    MetricsCounter *machineGuestRAMUsageTotalCounter;
    MetricsCounter *machineGuestRAMUsageFreeCounter;
    MetricsCounter *machineGuestRAMUsageBalloonCounter;
    MetricsCounter *machineGuestRAMUsageSharedCounter;
    MetricsCounter *machineGuestRAMUsageCacheCounter;
    MetricsCounter *machineGuestPagefileUsageTotalCounter;

    QString Name;
    QString UUID;

    void setupMetricsMonitors();
    bool metricsIsRunningVM(const QString &machineName);

    Q_PROPERTY(QString Name READ getName WRITE setName NOTIFY NameChanged)
    Q_PROPERTY(QString UUID READ getUUID WRITE setUUID NOTIFY UUIDChanged)
    Q_PROPERTY(QList<VirtualMachine *> runningMachines READ getRunningMachines WRITE setRunningMachines NOTIFY runningMachinesChanged)
};

#endif // METRICSVISUALIZATION_HPP
