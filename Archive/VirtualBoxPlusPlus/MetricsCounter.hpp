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

#ifndef METRICSCOUNTER_HPP
#define METRICSCOUNTER_HPP

#include <QWidget>
#include <QChartView>
#include "MetricsAggregateWidget.hpp"

namespace Ui {
class MetricsCounter;
}

class MetricsCounter : public QWidget
{
    Q_OBJECT

public:
    explicit MetricsCounter(QWidget *parent = nullptr);
    ~MetricsCounter();

private:
    Ui::MetricsCounter *ui;
    QChartView *seriesChart;
    MetricsAggregateWidget *metricsAggregate;

public:
    void setTitle(const QString &title);

    QChartView *getSeriesChart() const;
    void setSeriesChart(QChartView *newSeriesChart);


    MetricsAggregateWidget *getMetricsAggregate() const;
    void setMetricsAggregate(MetricsAggregateWidget *newMetricsAggregate);

public slots:
    void clear();

signals:
    void seriesChartChanged();
    void metricsAggregateChanged();

private:
    void setupChartViews();
    Q_PROPERTY(QChartView *seriesChart READ getSeriesChart WRITE setSeriesChart NOTIFY seriesChartChanged)
    Q_PROPERTY(MetricsAggregateWidget *metricsAggregate READ getMetricsAggregate WRITE setMetricsAggregate NOTIFY metricsAggregateChanged)
};

#endif // METRICSCOUNTER_HPP
