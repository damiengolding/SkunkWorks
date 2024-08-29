/*
MIT License

Copyright (c) 2024 Damien Golding

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Don't use it to find and eat babies ... unless you're really REALLY hungry ;-)
*/

#pragma once

#include "inc/CommandLineHandler.hpp"
#include <QFontInfo>

// Nmap
void processNmap(const QString &inputFile,const QString &outputFile){
    qInfo() << "Starting to process nmap file:"<<inputFile<<"output stem:"<<outputFile;
    QString csvOFName = outputFile % ".csv";
    QString tsvOFName = outputFile % ".tsv";
    QScopedPointer<QFile> file( new QFile(inputFile) ) ;
    QScopedPointer<QDomDocument> doc(new QDomDocument());
    if( !file->open(QIODevice::ReadOnly)  ){
        qCritical() << "Could not open"<<inputFile<<"For reading";
        return;
    }
    if( !doc->setContent(file.data()) ){
        qCritical() << "Failed parsing"<<inputFile;
        file->close();
    }
    QString csv = "IP Address,Protocol,Port Number,Service,State,ID Method\n";
    QString tsv = "IP Address\tProtocol\tPort Number\tService\tState\tID Method\n";
    QDomElement root = doc->documentElement();
    QDomNodeList hostList = root.elementsByTagName("host");

    for( int i = 0; i<hostList.count();++i ){
        QDomNode node = hostList.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull() ){
#ifdef QT_DEBUG
            qDebug() << "Unable to cast node to element";
#endif
            continue;
        }
        QString ipAddress;
        QDomNodeList addresses = elem.elementsByTagName("address");
        for( int j = 0; j<addresses.count();++j){
            QDomNode addrNode = addresses.at(j);
            QDomElement addrElem = addrNode.toElement();
            if( addrElem.attribute("addrtype").toLower() == "ipv4" ){
                ipAddress = addrElem.attribute("addr");
            }
        }
        QDomNodeList ports = elem.elementsByTagName("port");
        for( int k = 0;k<ports.count();++k ){
            csv += ipAddress % ",";
            tsv += ipAddress % "\t";
            QDomNode portNode = ports.at(k);
            QDomElement portElem = portNode.toElement();
            // Protocol - TCP or UDP
            csv += portElem.attribute("protocol") % ",";
            tsv += portElem.attribute("protocol") % "\t";
            // Port number
            csv += portElem.attribute("portid") % ",";
            tsv += portElem.attribute("portid") % "\t";
            // Service
            QDomNode serviceNode = portElem.firstChildElement("service");
            QDomElement serviceElem = serviceNode.toElement();
            csv += serviceElem.attribute("name") % ",";
            tsv += serviceElem.attribute("name") % "\t";
            // State
            QDomNode stateNode = portElem.firstChildElement("state");
            QDomElement stateElem = stateNode.toElement();
            csv += stateElem.attribute("state") % ",";
            tsv += stateElem.attribute("state") % "\t";
            // ID Method
            csv += serviceElem.attribute("method") % "\n";
            tsv += serviceElem.attribute("method") % "\n";
        }
    }

    QScopedPointer<QFile> csvFile( new QFile(csvOFName) ) ;
    if( !csvFile->open(QIODevice::WriteOnly)  ){
        qCritical() << "Could not open"<<csvOFName<<"For reading";
    }
    else{
        QTextStream csvStream(csvFile.data());
        csvStream << csv;
        csvFile->close();
    }

    QScopedPointer<QFile> tsvFile( new QFile(tsvOFName) ) ;
    if( !tsvFile->open(QIODevice::WriteOnly)  ){
        qCritical() << "Could not open"<<tsvOFName<<"For reading";
    }
    else{
        QTextStream tsvStream(tsvFile.data());
        tsvStream << tsv;
        tsvFile->close();
    }

    qInfo() << "Completed processing input:";

}

// Nessus
void processNessus(const QString &inputFile,const QString &outputFile){
    qInfo() << "Starting to process nessus file:"<<inputFile;

    QScopedPointer<QDomDocument> doc(new QDomDocument());
    QString csvOFName = outputFile % ".csv";
    QString tsvOFName = outputFile % ".tsv";
    QString csv = "IP Address,Highest,Critical Count,High Count,Medium Count,Low Count,None Count\n";
    QString tsv = "IP Address\tHighest\tCritical Count\tHigh Count\tMedium Count\tLow Count\tNone Count\n";

    PtngDGMLBuilder builder;
    QList<PtngHostBuilder*> builders =  PtngInputParser::parseNessus(inputFile);
    builder.createFromNessus(builders,inputFile);
    if( !doc->setContent(builder.toString()) ){
        qCritical() << "Failed parsing DGML";
    }
    QDomElement root = doc->documentElement();
    QDomNodeList nodes = root.elementsByTagName("Node");

    for( int i = 0;i<nodes.count();++i){
        QDomNode node = nodes.at(i);
        QDomElement elem = node.toElement();
        QString address = elem.attribute("Id");
        if( address.contains("*") || address.toLower() == "attack_machine"){
            continue;
        }
        csv += address % ",";
        csv += elem.attribute("Category").toUpper() % ",";
        csv += elem.attribute("CriticalCount") % ",";
        csv += elem.attribute("HighCount") % ",";
        csv += elem.attribute("MediumCount") % ",";
        csv += elem.attribute("LowCount") % ",";
        csv += elem.attribute("NoneCount") % "\n";

        tsv += address % "\t";
        tsv += elem.attribute("Category").toUpper() % "\t";
        tsv += elem.attribute("CriticalCount") % "\t";
        tsv += elem.attribute("HighCount") % "\t";
        tsv += elem.attribute("MediumCount") % "\t";
        tsv += elem.attribute("LowCount") % "\t";
        tsv += elem.attribute("NoneCount") % "\n";
    }

    QScopedPointer<QFile> csvFile( new QFile(csvOFName) ) ;
    if( !csvFile->open(QIODevice::WriteOnly)  ){
        qCritical() << "Could not open"<<csvOFName<<"For reading";
    }
    else{
        QTextStream csvStream(csvFile.data());
        csvStream << csv;
        csvFile->close();
    }

    QScopedPointer<QFile> tsvFile( new QFile(tsvOFName) ) ;
    if( !tsvFile->open(QIODevice::WriteOnly)  ){
        qCritical() << "Could not open"<<tsvOFName<<"For reading";
    }
    else{
        QTextStream tsvStream(tsvFile.data());
        tsvStream << tsv;
        tsvFile->close();
    }

    qInfo() << "Completed processing input";
}

