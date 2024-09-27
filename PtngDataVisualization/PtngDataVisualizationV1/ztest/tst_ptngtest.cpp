/*
MIT License

Copyright (c) Damien Golding 2024

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
*/
#include <QtTest>

// add necessary includes here
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>

#include "PtngDGMLBuilder.hpp"
#include "PtngDGMLConv.hpp"
#include "PtngHostBuilder.hpp"
#include "PtngEnums.hpp"
#include "PtngIP4Address.hpp"
#include "PtngIdent.hpp"
#include "PtngSpecifications.hpp"
#include "PtngDGMLBuilder.hpp"
#include "PtngDGMLConv.hpp"
#include "PtngInputParser.hpp"

using namespace ptng;

class PtngTest : public QObject
{
    Q_OBJECT

public:
    PtngTest();
    ~PtngTest();

    // QString runControl = "C:/Users/damie/source/repos/PtngDataVisualization/testfiles/parserlib_test.xml";
    QString runControl = "parserlib_test.xml";

private slots:
#pragma All tests - decl {
#pragma PtngIdent {
    void shouldRecogniseFile_data();
    void shouldRecogniseFile();
#pragma PtngIdent }

#pragma PtnigInputParser {
    // nmap & nessus
    void shouldCountNmapHosts_data();
    void shouldCountNessusHosts_data();
    void shouldCountNessusIssues_data();
    void shouldCountNessusSeverities_data();

    void shouldCountNmapHosts();
    void shouldCountNessusHosts();
    void shouldCountNessusIssues();
    void shouldCountNessusSeverities();

    // AXFR files
    void shouldCountDnsreconAXFRHosts_data();
    void shouldCountNmapAXFRHosts_data();
    void shouldCountNslookupWindowsAXFRHosts_data();
    void shouldCountNslookupLinuxAXFRHosts_data();
    void shouldCountArpscanAXFRHosts_data();
    void shouldCountNbtscanAXFRHosts_data();
    void shouldCountHostAXFRHosts_data();

    void shouldCountDnsreconAXFRHosts();
    void shouldCountNmapAXFRHosts();
    void shouldCountNslookupWindowsAXFRHosts();
    void shouldCountNslookupLinuxAXFRHosts();
    void shouldCountArpscanAXFRHosts();
    void shouldCountNbtscanAXFRHosts();
    void shouldCountHostAXFRHosts();
#pragma PtnigInputParser }

#pragma PtngDgmlBuilder {
    void shouldCreateDGMLFromNmap_data();
    void shouldCreateDGMLFromNessus_data();
    void shouldCreateDGMLFromSimple_data();
    void shouldCreateDGMLFromNmap();
    void shouldCreateDGMLFromNessus();
    void shouldCreateDGMLFromSimple();
#pragma PtngDGMLBuilder }

#pragma PtngDGMLConv {
    void shouldCreateDotrunControl_data();
    void shouldCreateDotrunControl();
#pragma PtngDGMLConv }

#pragma All tests - decl }

};

#pragma All tests - impl {

#pragma PtngIdent {
void PtngTest::shouldRecogniseFile_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptngident");
    // qInfo() << "ptngident elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldRecogniseFile()
{
    QFETCH(QString,tool);
    QFETCH(QString,file);
    if( !QFile::exists(file) ){
        QString message = QString(file % " does not exist. ");
        QFAIL(qPrintable(message));
    }
    PtngEnums::SupportedInputTypes type = PtngIdent::checkFile(file);
    if( tool == "unsupported" ){
        QVERIFY( type == PtngEnums::NUM_SUPPORTED_INPUT_TYPES );
    }
    else{
        QVERIFY( type != PtngEnums::NUM_SUPPORTED_INPUT_TYPES );
    }
}
#pragma PtngIdent }

#pragma PtnigInputParser {
void PtngTest::shouldCountNmapHosts_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    // qInfo() << "ptnginputparser nmap elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "nmap" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountNessusHosts_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    // qInfo() << "ptnginputparser elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "nessus" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountNessusIssues_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    // qInfo() << "ptnginputparser elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "nessus" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountNessusSeverities_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    // qInfo() << "ptnginputparser elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "nessus" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountNmapHosts()
{
    QFETCH(QString,file);
    QList<PtngHostBuilder*> hosts = PtngInputParser::parseNmap(file);
    QVERIFY(hosts.count() == 7);
}

void PtngTest::shouldCountNessusHosts()
{
    QFETCH(QString,file);
    QList<PtngHostBuilder*> hosts = PtngInputParser::parseNessus(file);
    QVERIFY(hosts.count() == 7);
}

void PtngTest::shouldCountNessusIssues()
{
    QFETCH(QString,file);
    QList<PtngIssue> issues = PtngInputParser::parseNesusIssues(file);
    QVERIFY(issues.count() == 3126);
}

void PtngTest::shouldCountNessusSeverities()
{
    QFETCH(QString,file);
    QMap<QString,QString> severities = PtngInputParser::parseNesusSeverities(file);
    QVERIFY(severities.count() == 7);

    for( auto [address,severity] : severities.asKeyValueRange()){
        // qInfo() << "Name:"<<name<<"Value"<<value;
        if( address == "192.168.4.29" ){
            QVERIFY(severity == "CRITICAL");
        }
        else if( address == "192.168.4.32" ){
            QVERIFY(severity == "CRITICAL");
        }
        else if( address == "192.168.4.36" ){
            QVERIFY(severity == "CRITICAL");
        }
        else if( address == "192.168.4.42" ){
            QVERIFY(severity == "CRITICAL");
        }
        else if( address == "192.168.4.43" ){
            QVERIFY(severity == "CRITICAL");
        }
        else if( address == "192.168.4.45" ){
            QVERIFY(severity == "CRITICAL");
        }
        else if( address == "192.168.4.46" ){
            QVERIFY(severity == "CRITICAL");
        }
        else{
            QString message = QString( "Unrecognised IP address: %1").arg(address);
            QWARN(qPrintable(message));
        }
    }
}

void PtngTest::shouldCountDnsreconAXFRHosts_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    // qInfo() << "ptnginputparser elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "dnsrecon" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountNmapAXFRHosts_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "nmap_axfr" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountNslookupWindowsAXFRHosts_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    // qInfo() << "ptnginputparser elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "nslookup_windows" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountNslookupLinuxAXFRHosts_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    // qInfo() << "ptnginputparser elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "nslookup_linux" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountArpscanAXFRHosts_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    // qInfo() << "ptnginputparser elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "arpscan" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountNbtscanAXFRHosts_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    // qInfo() << "ptnginputparser elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "nbtscan" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountHostAXFRHosts_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptnginputparser");
    // qInfo() << "ptnginputparser elements:"<<testFiles.count();
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "host" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCountDnsreconAXFRHosts()
{
    PtngInputParser p;
    QFETCH(QString,file);
    QMap<QString,QString> nv = p.parseAxfrDnsRecon(file);
    QVERIFY(nv.count() == 8);
}

void PtngTest::shouldCountNmapAXFRHosts()
{
    PtngInputParser p;
    QFETCH(QString,file);
    QMap<QString,QString> nv = p.parseAxfrNmap(file);
    QVERIFY(nv.count() == 8);
}

void PtngTest::shouldCountNslookupWindowsAXFRHosts()
{
    PtngInputParser p;
    QFETCH(QString,file);
    QMap<QString,QString> nv = p.parseAxfrNslookupWin(file);
    QVERIFY(nv.count() == 8);
}

void PtngTest::shouldCountNslookupLinuxAXFRHosts()
{
    PtngInputParser p;
    QFETCH(QString,file);
    QMap<QString,QString> nv = p.parseAxfrNslookupLin(file);
    QVERIFY(nv.count() == 28);
}

void PtngTest::shouldCountArpscanAXFRHosts()
{
    PtngInputParser p;
    QFETCH(QString,file);
    QMap<QString,QString> nv = p.parseAxfrArpscan(file);
    QVERIFY(nv.count() == 12);
}

void PtngTest::shouldCountNbtscanAXFRHosts()
{
    PtngInputParser p;
    QFETCH(QString,file);
    QMap<QString,QString> nv = p.parseAxfrNbtscan(file);
    QVERIFY(nv.count() == 7);
}

void PtngTest::shouldCountHostAXFRHosts()
{
    PtngInputParser p;
    QFETCH(QString,file);
    QMap<QString,QString> nv = p.parseAxfrHostScan(file);
    QVERIFY(nv.count() == 8);
}
#pragma PtnigInputParser }

#pragma PtngDgmlBuilder {
void PtngTest::shouldCreateDGMLFromNmap_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptngdgmlbuilder");
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "nmap" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCreateDGMLFromNessus_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptngdgmlbuilder");
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "nessus" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCreateDGMLFromSimple_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptngdgmlbuilder");
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "axfr" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCreateDGMLFromNmap()
{
    QFETCH(QString,file);
    QList<PtngHostBuilder*> hosts = PtngInputParser::parseNmap(file);
    PtngDGMLBuilder builder;
    builder.createFromNmap(hosts);
    QScopedPointer<QDomDocument> doc( new QDomDocument("input") );
    if( !doc->setContent(builder.toString())  ){
        QFAIL("Could not parse DGML");
    }
    QDomNodeList nodeList = doc->elementsByTagName("Node");
    QDomNodeList linkList = doc->elementsByTagName("Link");
    QDomNodeList categoryList = doc->elementsByTagName("Category");
    QVERIFY(nodeList.count() == 13);
    QVERIFY(linkList.count() == 12);
    QVERIFY(categoryList.count() ==  7);
}

void PtngTest::shouldCreateDGMLFromNessus()
{
    QFETCH(QString,file);
    QList<PtngHostBuilder*> hosts = PtngInputParser::parseNessus(file);
    PtngDGMLBuilder builder;
    builder.createFromNessus(hosts,file);
    QScopedPointer<QDomDocument> doc( new QDomDocument("input") );
    if( !doc->setContent(builder.toString())  ){
        QFAIL("Could not parse DGML");
    }
    QDomNodeList nodeList = doc->elementsByTagName("Node");
    QDomNodeList linkList = doc->elementsByTagName("Link");
    QDomNodeList categoryList = doc->elementsByTagName("Category");
    QVERIFY(nodeList.count() == 13);
    QVERIFY(linkList.count() == 12);
    QVERIFY(categoryList.count() == 7);
}

void PtngTest::shouldCreateDGMLFromSimple()
{
    QFETCH(QString,file);
    QMap<QString,QString> hosts = PtngInputParser::parseZoneTransfer(file);
    PtngDGMLBuilder builder;
    builder.createSimple(hosts);
    QScopedPointer<QDomDocument> doc( new QDomDocument("input") );
    if( !doc->setContent(builder.toString())  ){
        QFAIL("Could not parse DGML");
    }
    QDomNodeList nodeList = doc->elementsByTagName("Node");
    QDomNodeList linkList = doc->elementsByTagName("Link");
    QDomNodeList categoryList = doc->elementsByTagName("Category");
    QVERIFY(nodeList.count() == 14);
    QVERIFY(linkList.count() == 13);
    QVERIFY(categoryList.count() == 7);
}
#pragma PtngDgmlBuilder }

#pragma PtngDGMLConv {
void PtngTest::shouldCreateDotrunControl_data()
{
    QScopedPointer<QFile> file(new QFile(runControl));
    QScopedPointer<QDomDocument> doc(new QDomDocument(""));

    if( !file->open(QIODevice::ReadOnly) ){
        QString message = QString("Couldn't open the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    if( !doc->setContent(file->readAll()) ){
        QString message = QString("Couldn't parse the XML configuration file: %1").arg( runControl );
        QFAIL(qPrintable(message));
    }

    QDomNodeList testFiles = doc->elementsByTagName("ptngdgmlconv");
    QTest::addColumn<QString>("tool");
    QTest::addColumn<QString>("file");

    for( int i = 0; i< testFiles.count(); ++i ){
        QDomNode node = testFiles.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull()){
            continue;
        }
        QString name = elem.attribute("name");
        if( name != "dot" ){
            continue;
        }
        QString value = elem.attribute("value");
        QTest::addRow(qPrintable(name)) << name << value;
    }
}

void PtngTest::shouldCreateDotrunControl()
{
    QFETCH(QString,file);
    QScopedPointer<QFile> inputFile(new QFile(file));
    if( !inputFile->open(QIODevice::ReadOnly)){
        QString message = QString( "Could not open file %1 for reading" ).arg(file);
        QFAIL(qPrintable(message));
    }
    QString dotRuncontrol = inputFile->readAll();
    QVERIFY (dotRuncontrol.contains("0->2") );
    QVERIFY (dotRuncontrol.contains("2->4") );
    QVERIFY (dotRuncontrol.contains("4->5") );
    QVERIFY (dotRuncontrol.contains("5->6") );
    QVERIFY (dotRuncontrol.contains("5->7") );
    QVERIFY (dotRuncontrol.contains("5->8") );
    QVERIFY (dotRuncontrol.contains("5->9") );
    QVERIFY (dotRuncontrol.contains("5->10") );
    QVERIFY (dotRuncontrol.contains("5->11") );
    QVERIFY (dotRuncontrol.contains("5->12") );
}
#pragma PtngDGMLConv }

#pragma All tests - impl }

PtngTest::PtngTest()
{

}

PtngTest::~PtngTest()
{

}

QTEST_APPLESS_MAIN(PtngTest)

#include "tst_ptngtest.moc"
