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

#include "MachineMetrics.hpp"

MachineMetrics::MachineMetrics(QObject *parent)
	: QObject(parent)
{}

MachineMetrics::~MachineMetrics()
{}

QString MachineMetrics::getMetricName() const
{
    return MetricName;
}

void MachineMetrics::setMetricName(const QString &newMetricName)
{
    if (MetricName == newMetricName)
        return;
    MetricName = newMetricName;
    emit MetricNameChanged();
}

MachineMetrics::MeasureType MachineMetrics::getMetricMeasure() const
{
    return MetricMeasure;
}

void MachineMetrics::setMetricMeasure(MeasureType newMetricMeasure)
{
    if (MetricMeasure == newMetricMeasure)
        return;
    MetricMeasure = newMetricMeasure;
    emit MetricMeasureChanged();
}

bool MachineMetrics::getReadSucceeded() const
{
    return ReadSucceeded;
}

void MachineMetrics::setReadSucceeded(bool newReadError)
{
    if (ReadSucceeded == newReadError)
        return;
    ReadSucceeded = newReadError;
    emit ReadSucceededChanged();
}

QString MachineMetrics::getMetricData() const
{
    return MetricData;
}

void MachineMetrics::setMetricData(const QString &newMetricData)
{
    if (MetricData == newMetricData)
        return;
    MetricData = newMetricData;
    emit MetricDataChanged();
}

QString MachineMetrics::getMachineName() const
{
    return MachineName;
}

void MachineMetrics::setMachineName(const QString &newMachineName)
{
    if (MachineName == newMachineName)
        return;
    MachineName = newMachineName;
    emit MachineNameChanged();
}
