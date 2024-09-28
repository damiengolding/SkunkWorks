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

#include "MetricsVisualization.hpp"
#include "ui_MetricsVisualization.h"

MetricsVisualization::MetricsVisualization(QWidget *parent) ://const QString &name, const QString &uuid,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MetricsVisualization)
{
    //    Name = name;
    //    UUID=uuid;
    ui->setupUi(this);
    setupMetricsMonitors();
    connect(this,SIGNAL(UpdateChartsReady(const QString&)),this,SLOT(updateCharts(const QString&)));
    connect(this,
            SIGNAL(UpdateCPULoadUserReady(MachineMetrics*)),
            this,
            SLOT(updateCPULoadUser(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateCPULoadKernelReady(MachineMetrics*)),
            this,
            SLOT(updateCPULoadKernel(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateRAMUsageUsedReady(MachineMetrics*)),
            this,
            SLOT(updateRAMUsageUsed(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateDiskUsageUsedReady(MachineMetrics*)),
            this,
            SLOT(updateDiskUsageUsed(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateNetRateTxReady(MachineMetrics*)),
            this,
            SLOT(updateNetRateTX(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateNetRateRxReady(MachineMetrics*)),
            this,
            SLOT(updateNetRateRX(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateGuestCPULoadUserReady(MachineMetrics*)),
            this,
            SLOT(updateGuestCPULoadUser(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateGuestCPULoadKernelReady(MachineMetrics*)),
            this,
            SLOT(updateGuestCPULoadKernel(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateGuestCPULoadIdleReady(MachineMetrics*)),
            this,
            SLOT(updateGuestCPULoadIdle(MachineMetrics*)
                 ));
    connect(this,
            SIGNAL(UpdateGuestRAMUsageTotalReady(MachineMetrics*)),
            this,
            SLOT(updateGuestRAMUsageTotal(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateGuestRAMUsageFreeReady(MachineMetrics*)),
            this,
            SLOT(updateGuestRAMUsageFree(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateGuestRAMUsageBalloonReady(MachineMetrics*)),
            this,
            SLOT(updateGuestRAMUsageBalloon(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateGuestRAMUsageSharedReady(MachineMetrics*)),
            this,
            SLOT(updateGuestRAMUsageShared(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateGuestRAMUsageCacheReady(MachineMetrics*)),
            this,
            SLOT(updateGuestRAMUsageCache(MachineMetrics*)
                 ));

    connect(this,
            SIGNAL(UpdateGuestPagefileUsageTotalReady(MachineMetrics*)),
            this,
            SLOT(updateGuestPagefileUsageTotal(MachineMetrics*)
                 ));
}

MetricsVisualization::~MetricsVisualization()
{
    delete ui;
}

void MetricsVisualization::setupMetricsMonitors(){
    centralLayout = new QGridLayout(this);
    int margin = 5;
    centralLayout->setContentsMargins(margin,margin,margin,margin);
    machineCPULoadUserCounter = new MetricsCounter();
    machineCPULoadUserCounter->setObjectName("machineCPULoadUserCounter");
    centralLayout->addWidget(machineCPULoadUserCounter);
    machineCPULoadUserCounter->setTitle("CPU/Load/User");

    machineCPULoadKernelCounter = new MetricsCounter();
    machineCPULoadKernelCounter->setObjectName("machineCPULoadKernelCounter");
    centralLayout->addWidget(machineCPULoadKernelCounter);
    machineCPULoadKernelCounter->setTitle("CPU/Load/Kernel");

    machineRAMUsageUsedCounter = new MetricsCounter();
    machineRAMUsageUsedCounter->setObjectName("machineRAMUsageUsedCounter");
    centralLayout->addWidget(machineRAMUsageUsedCounter);
    machineRAMUsageUsedCounter->setTitle("RAM/Usage/Used");

    machineDiskUsageUsedCounter = new MetricsCounter();
    machineDiskUsageUsedCounter->setObjectName("machineDiskUsageUsedCounter");
    centralLayout->addWidget(machineDiskUsageUsedCounter);
    machineDiskUsageUsedCounter->setTitle("Disk/Usage/Used");

    machineNetRateTxCounter = new MetricsCounter();
    machineNetRateTxCounter->setObjectName("machineNetRateTxCounter");
    centralLayout->addWidget(machineNetRateTxCounter);
    machineNetRateTxCounter->setTitle("Net/Rate/Tx");

    machineNetRateRxCounter = new MetricsCounter();
    machineNetRateRxCounter->setObjectName("machineNetRateRxCounter");
    centralLayout->addWidget(machineNetRateRxCounter);
    machineNetRateRxCounter->setTitle("Net/Rate/Rx");

    machineGuestCPULoadUserCounter = new MetricsCounter();
    machineGuestCPULoadUserCounter->setObjectName("machineGuestCPULoadUserCounter");
    centralLayout->addWidget(machineGuestCPULoadUserCounter);
    machineGuestCPULoadUserCounter->setTitle("Guest/CPU/Load");

    machineGuestCPULoadKernelCounter = new MetricsCounter();
    machineGuestCPULoadKernelCounter->setObjectName("machineGuestCPULoadKernelCounter");
    centralLayout->addWidget(machineGuestCPULoadKernelCounter);
    machineGuestCPULoadKernelCounter->setTitle("Guest/CPU/Load/Kernel");

    machineGuestCPULoadIdleCounter = new MetricsCounter();
    machineGuestCPULoadIdleCounter->setObjectName("machineGuestCPULoadIdleCounter");
    centralLayout->addWidget(machineGuestCPULoadIdleCounter);
    machineGuestCPULoadIdleCounter->setTitle("Guest/CPU/Load/Idle");

    machineGuestRAMUsageTotalCounter = new MetricsCounter();
    machineGuestRAMUsageTotalCounter->setObjectName("machineGuestRAMUsageTotalCounter");
    centralLayout->addWidget(machineGuestRAMUsageTotalCounter);
    machineGuestRAMUsageTotalCounter->setTitle("Guest/RAM/Usage/Total");

    machineGuestRAMUsageFreeCounter = new MetricsCounter();
    machineGuestRAMUsageFreeCounter->setObjectName("machineGuestRAMUsageFreeCounter");
    centralLayout->addWidget(machineGuestRAMUsageFreeCounter);
    machineGuestRAMUsageFreeCounter->setTitle("Guest/RAM/Usage/Free");

    machineGuestRAMUsageBalloonCounter = new MetricsCounter();
    machineGuestRAMUsageBalloonCounter->setObjectName("machineGuestRAMUsageBalloonCounter");
    centralLayout->addWidget(machineGuestRAMUsageBalloonCounter);
    machineGuestRAMUsageBalloonCounter->setTitle("Guest/RAM/Usage/Balloon");

    machineGuestRAMUsageSharedCounter = new MetricsCounter();
    machineGuestRAMUsageSharedCounter->setObjectName("machineGuestRAMUsageSharedCounter");
    centralLayout->addWidget(machineGuestRAMUsageSharedCounter);
    machineGuestRAMUsageSharedCounter->setTitle("Guest/RAM/Usage/Shared");

    machineGuestRAMUsageCacheCounter = new MetricsCounter();
    machineGuestRAMUsageCacheCounter->setObjectName("machineGuestRAMUsageCacheCounter");
    centralLayout->addWidget(machineGuestRAMUsageCacheCounter);
    machineGuestRAMUsageCacheCounter->setTitle("Guest/RAM/Usage/Cache");

    machineGuestPagefileUsageTotalCounter = new MetricsCounter();
    machineGuestPagefileUsageTotalCounter->setObjectName("machineGuestPagefileUsageTotalCounter");
    centralLayout->addWidget(machineGuestPagefileUsageTotalCounter);
    machineGuestPagefileUsageTotalCounter->setTitle("Guest/Pagefile/Usage/Total");

}

void MetricsVisualization::onMetricsUpdateAvailable(QList<QList<MachineMetrics*>> metricsList){
    //    qDebug()<<"Starting MetricsVisualization::onMetricsUpdateAvailable ";
    internalMetricsList = metricsList;
    QList<QList<MachineMetrics*>> listOfLists = internalMetricsList;
    updateCharts(Name);
}

void MetricsVisualization::onSelectedMachineChanged(const QString &machineName, const QString &uuid){
    Name = machineName;
    UUID = uuid;
    updateCharts(machineName);
}

void MetricsVisualization::updateCharts(const QString &machineName){
    if( machineName.isNull() || machineName.isEmpty()  ){
        //        qDebug()<<"Starting MetricsVisualization::updateCharts: empty MachineName";
        return;
    }

    if( !metricsIsRunningVM(machineName) ){
        //        qDebug()<< "Machinename: " << machineName << " is not running";
        clearCharts();
    }

    //    qDebug()<<"Starting MetricsVisualization::updateCharts: " + machineName;
    for(auto metricsList : internalMetricsList){
        for(auto metrics : metricsList){
            if(metrics->getMachineName().toLower() == machineName.toLower() ){
                if( metrics->getMetricName().toLower().startsWith(QString("CPU/Load/User").toLower() )){
                    emit UpdateCPULoadUserReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("CPU/Load/Kernel").toLower() )){
                    emit UpdateCPULoadKernelReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("RAM/Usage/Used").toLower() )){
                    emit UpdateRAMUsageUsedReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Disk/Usage/Used").toLower() )){
                    emit UpdateDiskUsageUsedReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Net/Rate/Tx").toLower() )){
                    emit UpdateNetRateTxReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Net/Rate/Rx").toLower() )){
                    emit UpdateNetRateRxReady(metrics);
                }
                else if( metrics->getMetricName().toLower().startsWith(QString("Guest/CPU/Load/User").toLower() )){
                    emit UpdateGuestCPULoadUserReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Guest/CPU/Load/Kernel").toLower() )){
                    emit UpdateGuestCPULoadKernelReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Guest/CPU/Load/Idle").toLower() )){
                    emit UpdateGuestCPULoadIdleReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Guest/RAM/Usage/Total").toLower() )){
                    emit UpdateGuestRAMUsageTotalReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Guest/RAM/Usage/Free").toLower() )){
                    emit UpdateGuestRAMUsageFreeReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Guest/RAM/Usage/Balloon").toLower() )){
                    emit UpdateGuestRAMUsageBalloonReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Guest/RAM/Usage/Shared").toLower() )){
                    emit UpdateGuestRAMUsageSharedReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Guest/RAM/Usage/Cache").toLower() )){
                    emit UpdateGuestRAMUsageCacheReady(metrics);
                }
                else  if(metrics->getMetricName().toLower().startsWith(QString("Guest/Pagefile/Usage/Total").toLower() )){
                    emit UpdateGuestPagefileUsageTotalReady(metrics);
                }
            }
        }
    }
}

void MetricsVisualization::clearCharts(){
    machineCPULoadUserCounter->clear();
    machineCPULoadKernelCounter->clear();
    machineRAMUsageUsedCounter->clear();
    machineDiskUsageUsedCounter->clear();
    machineNetRateTxCounter->clear();
    machineNetRateRxCounter->clear();
    machineGuestCPULoadUserCounter->clear();
    machineGuestCPULoadKernelCounter->clear();
    machineGuestCPULoadIdleCounter->clear();
    machineGuestRAMUsageTotalCounter->clear();
    machineGuestRAMUsageFreeCounter->clear();
    machineGuestRAMUsageBalloonCounter->clear();
    machineGuestRAMUsageSharedCounter->clear();
    machineGuestRAMUsageCacheCounter->clear();
    machineGuestPagefileUsageTotalCounter->clear();
}

bool MetricsVisualization::metricsIsRunningVM(const QString &machineName){
//    qDebug()<<"Checking if " << machineName << "  is running";
//    qDebug()<<"Number of running machines: " << runningMachines.count();
    for( auto machine : runningMachines){
//        qDebug()<< "Checking against " << machine->getName();
        if(machine->getName() == machineName){
            return(true);
        }
    }
    return(false);
}

void MetricsVisualization::updateCPULoadUser(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "CPU/Load/User"){ // series
        machineCPULoadUserCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineCPULoadUserCounter->getSeriesChart()->chart()->addSeries(ls);
        machineCPULoadUserCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineCPULoadUserCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineCPULoadUserCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineCPULoadUserCounter->getSeriesChart()->chart()->axisY()->setTitleText("Per cent");
        machineCPULoadUserCounter->getSeriesChart()->chart()->setTitle("CPU/Load/User (%)");
        machineCPULoadUserCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineCPULoadUserCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineCPULoadUserCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineCPULoadUserCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
}

void MetricsVisualization::updateCPULoadKernel(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "CPU/Load/Kernel"){ // series
        machineCPULoadKernelCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineCPULoadKernelCounter->getSeriesChart()->chart()->addSeries(ls);
        machineCPULoadKernelCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineCPULoadKernelCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineCPULoadKernelCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineCPULoadKernelCounter->getSeriesChart()->chart()->axisY()->setTitleText("Per cent");
        machineCPULoadKernelCounter->getSeriesChart()->chart()->setTitle("CPU/Load/Kernel (%)");
        machineCPULoadKernelCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineCPULoadKernelCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineCPULoadKernelCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineCPULoadKernelCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
}

void MetricsVisualization::updateRAMUsageUsed(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "RAM/Usage/Used"){ // series
        machineRAMUsageUsedCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineRAMUsageUsedCounter->getSeriesChart()->chart()->addSeries(ls);
        machineRAMUsageUsedCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineRAMUsageUsedCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineRAMUsageUsedCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineRAMUsageUsedCounter->getSeriesChart()->chart()->axisY()->setTitleText("KB");
        machineRAMUsageUsedCounter->getSeriesChart()->chart()->setTitle("RAM/Usage/Used (KB)");
        machineRAMUsageUsedCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineRAMUsageUsedCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineRAMUsageUsedCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineRAMUsageUsedCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
}

void MetricsVisualization::updateDiskUsageUsed(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Disk/Usage/Used"){ // series
        machineDiskUsageUsedCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineDiskUsageUsedCounter->getSeriesChart()->chart()->addSeries(ls);
        machineDiskUsageUsedCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineDiskUsageUsedCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineDiskUsageUsedCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineDiskUsageUsedCounter->getSeriesChart()->chart()->axisY()->setTitleText("MB");
        machineDiskUsageUsedCounter->getSeriesChart()->chart()->setTitle("Disk/Usage/Used (MB)");
        machineDiskUsageUsedCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineDiskUsageUsedCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + " MB");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineDiskUsageUsedCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + " MB");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineDiskUsageUsedCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + " MB");
    }
}

void MetricsVisualization::updateNetRateTX(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Net/Rate/Tx"){ // series
        machineNetRateTxCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineNetRateTxCounter->getSeriesChart()->chart()->addSeries(ls);
        machineNetRateTxCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineNetRateTxCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineNetRateTxCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineNetRateTxCounter->getSeriesChart()->chart()->axisY()->setTitleText("B/s");
        machineNetRateTxCounter->getSeriesChart()->chart()->setTitle("Net/Rate/Tx (B/s)");
        machineNetRateTxCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineNetRateTxCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + " B/s");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineNetRateTxCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + " B/s");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineNetRateTxCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + " B/s");
    }
}

void MetricsVisualization::updateNetRateRX(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Net/Rate/Rx"){ // series
        machineNetRateRxCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineNetRateRxCounter->getSeriesChart()->chart()->addSeries(ls);
        machineNetRateRxCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineNetRateRxCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineNetRateRxCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineNetRateRxCounter->getSeriesChart()->chart()->axisY()->setTitleText("B/s");
        machineNetRateRxCounter->getSeriesChart()->chart()->setTitle("Net/Rate/Rx (B/s)");
        machineNetRateRxCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineNetRateRxCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + " B/s");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineNetRateRxCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + " B/s");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineNetRateRxCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + " B/s");
    }
}

void MetricsVisualization::updateGuestCPULoadUser(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Guest/CPU/Load/User"){ // series
        machineGuestCPULoadUserCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineGuestCPULoadUserCounter->getSeriesChart()->chart()->addSeries(ls);
        machineGuestCPULoadUserCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineGuestCPULoadUserCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineGuestCPULoadUserCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineGuestCPULoadUserCounter->getSeriesChart()->chart()->axisY()->setTitleText("Per cent");
        machineGuestCPULoadUserCounter->getSeriesChart()->chart()->setTitle("Guest/CPU/Load/User (%)");
        machineGuestCPULoadUserCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestCPULoadUserCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestCPULoadUserCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestCPULoadUserCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
}

void MetricsVisualization::updateGuestCPULoadKernel(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Guest/CPU/Load/Kernel"){ // series
        machineGuestCPULoadKernelCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineGuestCPULoadKernelCounter->getSeriesChart()->chart()->addSeries(ls);
        machineGuestCPULoadKernelCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineGuestCPULoadKernelCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineGuestCPULoadKernelCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineGuestCPULoadKernelCounter->getSeriesChart()->chart()->axisY()->setTitleText("Per cent");
        machineGuestCPULoadKernelCounter->getSeriesChart()->chart()->setTitle("Guest/CPU/Load/Kernel (%)");
        machineGuestCPULoadKernelCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestCPULoadKernelCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestCPULoadKernelCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestCPULoadKernelCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
}

void MetricsVisualization::updateGuestCPULoadIdle(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Guest/CPU/Load/Idle"){ // series
        machineGuestCPULoadIdleCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineGuestCPULoadIdleCounter->getSeriesChart()->chart()->addSeries(ls);
        machineGuestCPULoadIdleCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineGuestCPULoadIdleCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineGuestCPULoadIdleCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineGuestCPULoadIdleCounter->getSeriesChart()->chart()->axisY()->setTitleText("Per cent");
        machineGuestCPULoadIdleCounter->getSeriesChart()->chart()->setTitle("Guest/CPU/Load/Idle (%)");
        machineGuestCPULoadIdleCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestCPULoadIdleCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestCPULoadIdleCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestCPULoadIdleCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + "%");
    }
}

void MetricsVisualization::updateGuestRAMUsageTotal(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Guest/RAM/Usage/Total"){ // series
        machineGuestRAMUsageTotalCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineGuestRAMUsageTotalCounter->getSeriesChart()->chart()->addSeries(ls);
        machineGuestRAMUsageTotalCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineGuestRAMUsageTotalCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineGuestRAMUsageTotalCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineGuestRAMUsageTotalCounter->getSeriesChart()->chart()->axisY()->setTitleText("KB");
        machineGuestRAMUsageTotalCounter->getSeriesChart()->chart()->setTitle("Guest/RAM/Usage/Total (KB)");
        machineGuestRAMUsageTotalCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageTotalCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageTotalCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageTotalCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
}

void MetricsVisualization::updateGuestRAMUsageFree(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Guest/RAM/Usage/Free"){ // series
        machineGuestRAMUsageFreeCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineGuestRAMUsageFreeCounter->getSeriesChart()->chart()->addSeries(ls);
        machineGuestRAMUsageFreeCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineGuestRAMUsageFreeCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineGuestRAMUsageFreeCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineGuestRAMUsageFreeCounter->getSeriesChart()->chart()->axisY()->setTitleText("KB");
        machineGuestRAMUsageFreeCounter->getSeriesChart()->chart()->setTitle("Guest/RAM/Usage/Free (KB)");
        machineGuestRAMUsageFreeCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageFreeCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageFreeCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageFreeCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
}

void MetricsVisualization::updateGuestRAMUsageBalloon(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Guest/RAM/Usage/Balloon"){ // series
        machineGuestRAMUsageBalloonCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineGuestRAMUsageBalloonCounter->getSeriesChart()->chart()->addSeries(ls);
        machineGuestRAMUsageBalloonCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineGuestRAMUsageBalloonCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineGuestRAMUsageBalloonCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineGuestRAMUsageBalloonCounter->getSeriesChart()->chart()->axisY()->setTitleText("KB");
        machineGuestRAMUsageBalloonCounter->getSeriesChart()->chart()->setTitle("Guest/RAM/Usage/Balloon (KB)");
        machineGuestRAMUsageBalloonCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageBalloonCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageBalloonCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageBalloonCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
}

void MetricsVisualization::updateGuestRAMUsageShared(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Guest/RAM/Usage/Shared"){ // series
        machineGuestRAMUsageSharedCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineGuestRAMUsageSharedCounter->getSeriesChart()->chart()->addSeries(ls);
        machineGuestRAMUsageSharedCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineGuestRAMUsageSharedCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineGuestRAMUsageSharedCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineGuestRAMUsageSharedCounter->getSeriesChart()->chart()->axisY()->setTitleText("KB");
        machineGuestRAMUsageSharedCounter->getSeriesChart()->chart()->setTitle("Guest/RAM/Usage/Shared (KB)");
        machineGuestRAMUsageSharedCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageSharedCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageSharedCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageSharedCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
}

void MetricsVisualization::updateGuestRAMUsageCache(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Guest/RAM/Usage/Cache"){ // series
        machineGuestRAMUsageCacheCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineGuestRAMUsageCacheCounter->getSeriesChart()->chart()->addSeries(ls);
        machineGuestRAMUsageCacheCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineGuestRAMUsageCacheCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineGuestRAMUsageCacheCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineGuestRAMUsageCacheCounter->getSeriesChart()->chart()->axisY()->setTitleText("KB");
        machineGuestRAMUsageCacheCounter->getSeriesChart()->chart()->setTitle("Guest/RAM/Usage/Cache (KB)");
        machineGuestRAMUsageCacheCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageCacheCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageCacheCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestRAMUsageCacheCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
}

void MetricsVisualization::updateGuestPagefileUsageTotal(MachineMetrics *metrics)
{
    if( metrics->getMetricName() ==  "Guest/Pagefile/Usage/Total"){ // series
        machineGuestPagefileUsageTotalCounter->getSeriesChart()->chart()->removeAllSeries();
        QLineSeries *ls = new QLineSeries();
        int counter = 1;
        for( int observation : metrics->MetricIntValues){
            ls->append(counter, observation);
            ++counter;
        }
        machineGuestPagefileUsageTotalCounter->getSeriesChart()->chart()->addSeries(ls);
        machineGuestPagefileUsageTotalCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
        machineGuestPagefileUsageTotalCounter->getSeriesChart()->chart()->createDefaultAxes();
        machineGuestPagefileUsageTotalCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
        machineGuestPagefileUsageTotalCounter->getSeriesChart()->chart()->axisY()->setTitleText("KB");
        machineGuestPagefileUsageTotalCounter->getSeriesChart()->chart()->setTitle("Guest/Pagefile/Usage/Total (KB)");
        machineGuestPagefileUsageTotalCounter->getSeriesChart()->chart()->legend()->setVisible(false);
    }
    else if( metrics->getMetricName().endsWith("min") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestPagefileUsageTotalCounter->getMetricsAggregate()
                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("max") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestPagefileUsageTotalCounter->getMetricsAggregate()
                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
    else if( metrics->getMetricName().endsWith("avg") ){
        if(metrics->MetricIntValues.count() != 1){
            qDebug()<<"MetricIntValues.count() != 1";
            return;
        }
        machineGuestPagefileUsageTotalCounter->getMetricsAggregate()
                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + " KB");
    }
}

QString MetricsVisualization::getUUID() const
{
    return UUID;
}

void MetricsVisualization::setUUID(const QString &newUUID)
{
    if (UUID == newUUID)
        return;
    UUID = newUUID;
    emit UUIDChanged();
}

QList<VirtualMachine *> MetricsVisualization::getRunningMachines() const
{
    return runningMachines;
}

void MetricsVisualization::setRunningMachines(const QList<VirtualMachine *> &newRunningMachines)
{
    if (runningMachines == newRunningMachines)
        return;
    runningMachines = newRunningMachines;
    emit runningMachinesChanged();
}

QString MetricsVisualization::getName() const
{
    return Name;
}

void MetricsVisualization::setName(const QString &newName)
{
    if (Name == newName)
        return;
    Name = newName;
    emit NameChanged();
}

/* lather, rinse and repeat */
//void MetricsVisualization::updateCPULoadUser(MachineMetrics *metrics)
//{
//    if( metrics->getMetricName() ==  "CPU/Load/User"){ // series
//        machineCPULoadUserCounter->getSeriesChart()->chart()->removeAllSeries();
//        QLineSeries *ls = new QLineSeries();
//        int counter = 1;
//        for( int observation : metrics->MetricIntValues){
//            ls->append(counter, observation);
//            ++counter;
//        }
//        machineCPULoadUserCounter->getSeriesChart()->chart()->addSeries(ls);
//        machineCPULoadUserCounter->getSeriesChart()->setRenderHint(QPainter::Antialiasing);
//        machineCPULoadUserCounter->getSeriesChart()->chart()->createDefaultAxes();
//        machineCPULoadUserCounter->getSeriesChart()->chart()->axisX()->setTitleText("Observation");
//        machineCPULoadUserCounter->getSeriesChart()->chart()->axisY()->setTitleText("Per cent");
//        machineCPULoadUserCounter->getSeriesChart()->chart()->setTitle("CPU/Load/User (%)");
//        machineCPULoadUserCounter->getSeriesChart()->chart()->legend()->setVisible(false);
//    }
//    else if( metrics->getMetricName().endsWith("min") ){
//        if(metrics->MetricIntValues.count() != 1){
//            qDebug()<<"MetricIntValues.count() != 1";
//            return;
//        }
//        machineCPULoadUserCounter->getMetricsAggregate()
//                ->setMinimum(QString::number(metrics->MetricIntValues.at(0)) + "%");
//    }
//    else if( metrics->getMetricName().endsWith("max") ){
//        if(metrics->MetricIntValues.count() != 1){
//            qDebug()<<"MetricIntValues.count() != 1";
//            return;
//        }
//        machineCPULoadUserCounter->getMetricsAggregate()
//                ->setMaximum(QString::number(metrics->MetricIntValues.at(0)) + "%");
//    }
//    else if( metrics->getMetricName().endsWith("avg") ){
//        if(metrics->MetricIntValues.count() != 1){
//            qDebug()<<"MetricIntValues.count() != 1";
//            return;
//        }
//        machineCPULoadUserCounter->getMetricsAggregate()
//                ->setAverage(QString::number(metrics->MetricIntValues.at(0)) + "%");
//    }
//}
