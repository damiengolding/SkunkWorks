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

#include "MetricsCounter.hpp"
#include "ui_MetricsCounter.h"

MetricsCounter::MetricsCounter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MetricsCounter)
{
    ui->setupUi(this);
    setupChartViews();
}

void MetricsCounter::setTitle(const QString &title){
    ui->counterGroupBox->setTitle(title);
}

void MetricsCounter::setupChartViews(){
    seriesChart = new QChartView();
    metricsAggregate = new MetricsAggregateWidget();
    seriesChart->setMinimumHeight(350);
    ui->groupBoxGridLayout->addWidget(seriesChart,0,0);
    ui->groupBoxGridLayout->addWidget(metricsAggregate,0,1);
    ui->groupBoxGridLayout->setAlignment(metricsAggregate,Qt::AlignBottom);
}

MetricsCounter::~MetricsCounter()
{
    delete ui;
}

MetricsAggregateWidget *MetricsCounter::getMetricsAggregate() const
{
    return metricsAggregate;
}

void MetricsCounter::setMetricsAggregate(MetricsAggregateWidget *newMetricsAggregate)
{
    if (metricsAggregate == newMetricsAggregate)
        return;
    metricsAggregate = newMetricsAggregate;
    emit metricsAggregateChanged();
}

void MetricsCounter::clear()
{
    seriesChart->chart()->removeAllSeries();
    metricsAggregate->clear();
}

QChartView *MetricsCounter::getSeriesChart() const
{
    return seriesChart;
}

void MetricsCounter::setSeriesChart(QChartView *newSeriesChart)
{
    if (seriesChart == newSeriesChart)
        return;
    seriesChart = newSeriesChart;
    emit seriesChartChanged();
}
