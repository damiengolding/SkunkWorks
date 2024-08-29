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

#include "MetricsAggregateWidget.hpp"
#include "ui_MetricsAggregateWidget.h"

MetricsAggregateWidget::MetricsAggregateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MetricsAggregateWidget)
{
    ui->setupUi(this);
}

MetricsAggregateWidget::~MetricsAggregateWidget()
{
    delete ui;
}

QString MetricsAggregateWidget::getMinimum()
{
    minimum = ui->minimumLineEdit->text();
    return minimum;
}

void MetricsAggregateWidget::setMinimum(const QString &newMinimum)
{
//    if (minimum == newMinimum)
//        return;
    minimum = newMinimum;
    ui->minimumLineEdit->setText(minimum);
    emit minimumChanged();
}

QString MetricsAggregateWidget::getMaximum()
{
    maximum = ui->maximumLineEdit->text();
    return maximum;
}

void MetricsAggregateWidget::setMaximum(const QString &newMaximum)
{
//    if (maximum == newMaximum)
//        return;
    maximum = newMaximum;
    ui->maximumLineEdit->setText(maximum);
    emit maximumChanged();
}

QString MetricsAggregateWidget::getAverage()
{
    average = ui->averageLineEdit->text();
    return average;
}

void MetricsAggregateWidget::setAverage(const QString &newAverage)
{
//    if (average == newAverage)
//        return;
    average = newAverage;
    ui->averageLineEdit->setText(average);;
    emit averageChanged();
}

void MetricsAggregateWidget::clear()
{
setAverage("");
ui->averageLineEdit->setText(average);

setMinimum("");
ui->minimumLineEdit->setText(minimum);

setMaximum("");
ui->maximumLineEdit->setText(maximum);
}
