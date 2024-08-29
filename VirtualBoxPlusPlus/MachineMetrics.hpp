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

#include <QObject>

class MachineMetrics  : public QObject
{
	Q_OBJECT

public:
	MachineMetrics(QObject *parent = nullptr);
	~MachineMetrics();

	enum MeasureType {
		PC,
		KB,
		MB,
        BS,
        DY,
		NUM_MEASURE_TYPES
    };

    QList<int> MetricIntValues;
    QStringList MetricStringValues;

    QString getMachineName() const;
    void setMachineName(const QString &newMachineName);

    QString getMetricName() const;
    void setMetricName(const QString &newMetricName);

    MachineMetrics::MeasureType getMetricMeasure() const;
    void setMetricMeasure(MachineMetrics::MeasureType newMetricMeasure);

    bool getReadSucceeded() const;
    void setReadSucceeded(bool newReadError);

    QString getMetricData() const;
    void setMetricData(const QString &newMetricData);

private:
    QString MachineName;
    QString MetricName;
    QString MetricData;
    MeasureType MetricMeasure;
    bool ReadSucceeded = false;

signals:
    void MachineNameChanged();
    void MetricNameChanged();
    void MetricMeasureChanged();
    void ReadSucceededChanged();

    void MetricDataChanged();

private:
    Q_PROPERTY(QString MachineName READ getMachineName WRITE setMachineName NOTIFY MachineNameChanged)
    Q_PROPERTY(QString MetricName READ getMetricName WRITE setMetricName NOTIFY MetricNameChanged)
    Q_PROPERTY(MeasureType MetricMeasure READ getMetricMeasure WRITE setMetricMeasure NOTIFY MetricMeasureChanged)
    Q_PROPERTY(bool ReadSucceeded READ getReadSucceeded WRITE setReadSucceeded NOTIFY ReadSucceededChanged)
    Q_PROPERTY(QString MetricData READ getMetricData WRITE setMetricData NOTIFY MetricDataChanged)
};
