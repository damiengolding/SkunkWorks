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

#ifndef METRICSAGGREGATEWIDGET_HPP
#define METRICSAGGREGATEWIDGET_HPP

#include <QWidget>

namespace Ui {
class MetricsAggregateWidget;
}

class MetricsAggregateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MetricsAggregateWidget(QWidget *parent = nullptr);
    ~MetricsAggregateWidget();

    QString getMinimum();
    void setMinimum(const QString &newMinimum);

    QString getMaximum();
    void setMaximum(const QString &newMaxiimum);

    QString getAverage();
    void setAverage(const QString &newAverage);

public slots:
void clear();

signals:
    void minimumChanged();
    void maximumChanged();
    void averageChanged();

private:
    Ui::MetricsAggregateWidget *ui;

    QString minimum;
    QString maximum;
    QString average;
    Q_PROPERTY(QString minimum READ getMinimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(QString maximum READ getMaximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(QString average READ getAverage WRITE setAverage NOTIFY averageChanged)
};

#endif // METRICSAGGREGATEWIDGET_HPP
