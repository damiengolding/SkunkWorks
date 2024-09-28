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

#include "MetricsMonitor.hpp"
#include <QProcess>

MetricsMonitor::MetricsMonitor(QObject* parent)
    : QThread(parent)
{}

MetricsMonitor::~MetricsMonitor()
{}

QString MetricsMonitor::getVboxmanageExecutablePath() const
{
    return vboxmanageExecutablePath;
}

void MetricsMonitor::setVboxmanageExecutablePath(const QString &newVboxmanageExecutablePath)
{
    if (vboxmanageExecutablePath == newVboxmanageExecutablePath)
        return;
    vboxmanageExecutablePath = newVboxmanageExecutablePath;
    emit vboxmanageExecutablePathChanged();
}

int MetricsMonitor::getMaxMetricsErrors() const
{
    return maxMetricsErrors;
}

void MetricsMonitor::setMaxMetricsErrors(int newMaxMetricsErrors)
{
    if (maxMetricsErrors == newMaxMetricsErrors)
        return;
    maxMetricsErrors = newMaxMetricsErrors;
    emit maxMetricsErrorsChanged();
}

// ALLMIG
void MetricsMonitor::run() {
    // Metrics gathering setup
    QProcess* metricsSetup = new QProcess();
    if( startMetricsOnOpen ){
        qDebug()<<"Starting metrics counter with " << sampleInterval << "s delay for " << sampleCount << " sample count";
        metricsSetup->start(vboxmanageExecutablePath, QStringList() << "metrics" << "setup" << "--period" << QString::number(sampleInterval) << "--samples" << QString::number(sampleCount));
    }

    // Metrics collection cycle
    QList<MachineMetrics*> metricsMachine;
    QList<QList<MachineMetrics*>> metricsCollection;
    QStringList args;
    args << "metrics" << "query" << "*";
    while (true) {
        metricsCollection.clear();
        metricsCollection.resize(0);
        QProcess* proc = new QProcess();
        proc->start(vboxmanageExecutablePath, args);
        proc->waitForFinished(5000);
        QString output = proc->readAllStandardOutput();
        QStringList entries = output.split("\r\n");
        QStringList machines;
        QString tempStr;
        for (auto entry : entries) {
            if (entry.toLower().startsWith("object") || entry.startsWith("-")) {
                continue;
            }
            tempStr = entry.simplified();
            QStringList parts = tempStr.split(" ");
            if (parts.count() < 3 || (tempStr.toLower().startsWith("host") && parts.count() >= 4)) {
                continue;
            }
            QString guestName = parts.at(0);
            if( guestName.toLower() == "host" ){
                continue;
            }
            if (!machines.contains(guestName)) {
                machines.append(guestName);
            }
        }
        int counter = 0;
        for(auto machine : machines){
            QStringList machineEntries = entries.filter(machine);
            QList<MachineMetrics*> ret = parseMetrics(machineEntries);
            metricsCollection.push_back(ret);
            ++counter;
        }
        int counter2 = 0;
        for(QList<MachineMetrics*> thing : metricsCollection){
            ++counter2;
        }
        emit metricsUpdated(metricsCollection);
        this->sleep(sampleInterval);
    }
}

QList<MachineMetrics*> MetricsMonitor::parseMetrics(QStringList metricStrings) {
    //    qDebug()<<"MetricsMonitor::parseMetrics: "<<metricStrings.count();
    QList<MachineMetrics*> metricsList;
    QStringList workingStringList;

    for(QString workingString : metricStrings){
        if(workingString.toLower().startsWith("host")){
            continue;
        }
        workingString = workingString.simplified();
        workingString = workingString.replace(", ","#");
        workingString = workingString.replace(" kB","KB");
        workingString = workingString.replace(" MB","MB");
        workingString = workingString.replace(" B/s","BS");
        workingStringList.append(workingString);
        //        qDebug()<<"Working string #1: " << workingString;
    }

    MachineMetrics* metric;
    QString machineName, measureName,metricData;
    QStringList workingStringSplit;
    for(QString workingString : workingStringList){
        workingStringSplit = workingString.split(' ');
        if(workingStringSplit.count()!=3){
            continue;
        }
        machineName = workingStringSplit.at(0);
        measureName = workingStringSplit.at(1);
        metricData = workingStringSplit.at(2);
        //        qDebug()<<"metricData: " << metricData;

        metric = getMachineMetrics(metricsList, machineName, measureName, metricData);

        QString metricValue;
        bool ok = false;
        // TODO implement this?
        //        qDebug()<<"Quick reminder of working string: "<<workingString;
        if(metricData.contains('#')){
            QStringList metricsValueList = metricData.split('#');
            for(auto entry : metricsValueList){
                //                qDebug()<<"Iterating on value list: "<< machineName << " - "<< entry;
                MachineMetrics::MeasureType type = stringToMeasureType(entry,metricValue);
                metric->setMetricMeasure(type);
                bool convOk = false;
                int intValue = metricValue.toInt(&convOk);
                if( convOk ){
                    //                    qDebug()<<"Conversion to int successful for: "<< metricValue;
                    metric->MetricIntValues.append(intValue);
                    metric->MetricStringValues.append(metricValue);
                }
                else{
                    //                    qDebug()<<"Conversion to int failed for: "<< metricValue;
                    // TODO need to come up with something useful
                    metric->MetricIntValues.append(0);
                    metric->MetricStringValues.append("0");
                }
            }
        }
        else{
            MachineMetrics::MeasureType type = stringToMeasureType(metricData,metricValue);
            metric->setMetricMeasure(type);
            bool convOk = false;
            int intValue = metricValue.toInt(&convOk);
            if( convOk ){
                //                qDebug()<<"Conversion to int successful for: "<< metricValue;
                metric->MetricIntValues.append(intValue);
                metric->MetricStringValues.append(metricValue);
            }
            else{
                //                qDebug()<<"Conversion to int failed for: "<< metricValue;
                // TODO need to come up with something useful
                metric->MetricIntValues.append(0);
                metric->MetricStringValues.append("0");
            }
            //            qDebug()<<"Measure type: " << type << " Measure data: " << out;
        }
    }
    //    qDebug()<<"metricsList count #1: "<< metricsList.count();
    return(metricsList);
}

MachineMetrics* MetricsMonitor::getMachineMetrics(QList<MachineMetrics*>& metricsList, const QString &machineName, const QString &metricName, const QString &metricData){
    //    qDebug()<<"MetricsMonitor::getMachineMetrics: " << name << " " <<measure;
    MachineMetrics* metrics;
    for(auto metric : metricsList){
        if(metric->getMachineName() == machineName && metric->getMetricName() == metricName){
            return(metric);
        }
    }
    metrics = new MachineMetrics();
    metrics->setMachineName(machineName);
    metrics->setMetricName(metricName);
    metrics->setMetricData(metricData);
    QString out;
    metrics->setMetricMeasure(stringToMeasureType(metricData,out));
    metricsList.append(metrics);
    return(metrics);
}

MachineMetrics::MeasureType MetricsMonitor::stringToMeasureType(const QString &typeStr, QString &out){
    //qDebug()<<"MetricsMonitor::stringToMeasureType: " << typeStr;
    QString testString = typeStr.simplified();

    QString tempValue;
    if(testString.endsWith('%')){
        tempValue = testString.remove('%').simplified();
        if(tempValue.contains("")){
            //            qDebug()<<"Before: "<<tempValue;
            tempValue = tempValue.remove(tempValue.length()-3,3);
            //            qDebug()<<"After: "<<tempValue;
        }
        out = tempValue;
        return(MachineMetrics::PC);
    }
    else if(testString.endsWith("KB")){
        tempValue = testString.remove("KB").simplified();
        out = tempValue;
        return(MachineMetrics::KB);
    }
    else if(testString.endsWith("MB")){
        tempValue = testString.remove("MB").simplified();
        out = tempValue;
        return(MachineMetrics::MB);
    }
    else if(testString.endsWith("BS")){
        tempValue = testString.remove("BS").simplified();
        out = tempValue;
        return(MachineMetrics::BS);
    }
    else if(testString.endsWith("DY")){
        tempValue = testString.remove("DY").simplified();
        out = tempValue;
        return(MachineMetrics::DY);
    }
    else{
        return(MachineMetrics::NUM_MEASURE_TYPES);
    }
}

int MetricsMonitor::getSampleCount() const
{
    return sampleCount;
}

void MetricsMonitor::setSampleCount(int newSampleCount)
{
    if (sampleCount == newSampleCount)
        return;
    sampleCount = newSampleCount;
    emit sampleCountChanged();
}

int MetricsMonitor::getSampleInterval() const
{
    return sampleInterval;
}

void MetricsMonitor::setSampleInterval(int newSampleInterval)
{
    if (sampleInterval == newSampleInterval)
        return;
    sampleInterval = newSampleInterval;
    emit sampleIntervalChanged();
}

bool MetricsMonitor::getStartMetricsOnOpen() const
{
    return startMetricsOnOpen;
}

void MetricsMonitor::setStartMetricsOnOpen(bool newStartMetricsOnOpen)
{
    if (startMetricsOnOpen == newStartMetricsOnOpen)
        return;
    startMetricsOnOpen = newStartMetricsOnOpen;
    emit startMetricsOnOpenChanged();
}

QList<VirtualMachine *> MetricsMonitor::getRunningMachines() const
{
    return runningMachines;
}

void MetricsMonitor::setRunningMachines(const QList<VirtualMachine *> &newRunningMachines)
{
    if (runningMachines == newRunningMachines)
        return;
    runningMachines = newRunningMachines;
    emit runningMachinesChanged();
}

