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

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QSettings>

QString MainWindow::unQuote(const QString& quoted) {
    if ( !quoted.contains("\"")) return(quoted);
    QString ret = quoted;
    if ( ret.startsWith("\"") && ret.endsWith("\"")) {
        ret = ret.sliced(1,ret.length()-1);
        ret = ret.remove(ret.lastIndexOf("\""), 1);
    }
    return(ret);
}

QString MainWindow::measureTypeToString(MachineMetrics::MeasureType type){
    switch(type){
        case MachineMetrics::PC:{
            return("PC");
            break;
        }
        case MachineMetrics::KB:{
            return("KB");
            break;
        }
        case MachineMetrics::MB:{
            return("MB");
            break;
        }
        case MachineMetrics::BS:{
            return("B/s");
            break;
        }
        case MachineMetrics::DY:{
            return("DUMMY");
            break;
        }
        default:
            return("UNKNOWN");
    }
}

MachineMetrics::MeasureType MainWindow::stringToMeasureType(const QString &typeStr, QString &out){
    qDebug()<<"MetricsMonitor::stringToMeasureType";
    QString testString = typeStr.simplified().toLower();
    QString tempValue;
    if(testString.endsWith('%')){
        tempValue = testString.remove('%').simplified();
        if(!tempValue.contains('.')){
            tempValue += ".00";
        }
        out = tempValue;
        return(MachineMetrics::PC);
    }
    else if(testString.endsWith("KB")){
        tempValue = testString.remove("KB").simplified();
        if(!tempValue.contains('.')){
            tempValue += ".00";
        }
        out = tempValue;
        return(MachineMetrics::KB);
    }
    else if(testString.endsWith("MB")){
        tempValue = testString.remove("MB").simplified();
        if(!tempValue.contains('.')){
            tempValue += ".00";
        }
        out = tempValue;
        return(MachineMetrics::MB);
    }
    else if(testString.endsWith("BS")){
        tempValue = testString.remove("BS").simplified();
        if(!tempValue.contains('.')){
            tempValue += ".00";
        }
        out = tempValue;
        return(MachineMetrics::BS);
    }
    else if(testString.endsWith("DY")){
        tempValue = testString.remove("DY").simplified();
        if(!tempValue.contains('.')){
            tempValue += ".00";
        }
        out = tempValue;
        return(MachineMetrics::DY);
    }
    else{
        return(MachineMetrics::NUM_MEASURE_TYPES);
    }
}

void MainWindow::clearTableWidget(QTableWidget *tableWidget){
    qDebug()<<"MainWindow::clearTableWidget";
//   tableWidget->clearSelection();
//   tableWidget->clearContents();
//   tableWidget->setRowCount(0);
//    int rc = tableWidget->rowCount();
//    for (int i = rc; i > 0; --i) {
//        tableWidget->removeRow(i);
//    }

    if (tableWidget->model()->removeRows(0,tableWidget->rowCount()) ){
        qDebug()<<"TRUE: Rows remaining for: " << tableWidget->objectName() << " - " << tableWidget->rowCount();
    }
    else{
        qDebug()<<"FALSE: Rows remaining for: " << tableWidget->objectName() << " - " << tableWidget->rowCount();
    }
    qDebug()<<"Seems to have got this far";
}

bool MainWindow::tableHasUuid(QTableWidget* table, const QString &test){
    for( int i = 0; i < table->rowCount() ; ++i ){
        QTableWidgetItem *item = table->item(i, 0);
        if( item->text() == test ){
            return(true);
        }
    }
    return(false);
}

bool MainWindow::tableHasName(QTableWidget* table, const QString &test){
    for( int i = 0; i < table->rowCount() ; ++i ){
        QTableWidgetItem *item = table->item(i, 1);
        if( item->text() == test ){
            return(true);
        }
    }
    return(false);
}
