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

#include "../inc/libparser.hpp"

LibParser::LibParser()
{}

LibParser::~LibParser()
{}

void LibParser::initTestCase()
{
    if( QFileInfo::exists(runControl) ){
        qInfo() << "Config file" << runControl << "exists";
    }
    else{
        QString msg = QString("Can't find runcontrol file: %1").arg(runControl);
        QFAIL( qPrintable(msg) );
    }
}

void LibParser::cleanupTestCase()
{

}

    /*
        --- Test implementations ---
    */

#pragma All tests - impl {

#pragma Miscellaneous {
void LibParser::MustRecogniseRuncontrol_data()
{
    // QFAIL("TDD");
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
    file->close();
    // QDomDocument* doc2 = TestUtilities::VerifiedDomDocument(runControl);
    // QVERIFY(doc2 != nullptr);

    QDomNodeList testFiles = doc->elementsByTagName("ptngident");
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

void LibParser::MustRecogniseRuncontrol()
{
    QFAIL("TDD");
    // QFETCH(QString,tool);
    // QFETCH(QString,file);
    // if( !QFile::exists(file) ){
    //     QString message = QString(file % " does not exist. ");
    //     QFAIL(qPrintable(message));
    // }
    // PtngEnums::SupportedInputTypes type = PtngIdent::checkFile(file);
    // if( tool == "unsupported" ){
    //     QVERIFY( type == PtngEnums::NUM_SUPPORTED_INPUT_TYPES );
    // }
    // else{
    //     QVERIFY( type != PtngEnums::NUM_SUPPORTED_INPUT_TYPES );
    // }
}

void LibParser::MustPopulateSylesheet_data()
{
    QFAIL("TDD");
}

void LibParser::MustPopulateSylesheet()
{
    QFAIL("TDD");
}
#pragma Miscellaneous }

#pragma PtngIdent {

void LibParser::MustRecogniseFiles_data(){
    QFAIL("TDD");
}

void LibParser::MustRecogniseFiles(){
    QFAIL("TDD");
}

#pragma PtngIdent }


#pragma PtnigInputParser {
void LibParser::MustCountNmapHosts_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountNessusHosts_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountNessusIssues_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountNessusSeverities_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountNmapHosts()
{
    QFAIL("TDD");
}

void LibParser::MustCountNessusHosts()
{
    QFAIL("TDD");
}

void LibParser::MustCountNessusIssues()
{
    QFAIL("TDD");
}

void LibParser::MustCountNessusSeverities()
{
   QFAIL("TDD");
}

void LibParser::MustCountDnsreconAXFRHosts_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountNmapAXFRHosts_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountNslookupWindowsAXFRHosts_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountNslookupLinuxAXFRHosts_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountArpscanAXFRHosts_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountNbtscanAXFRHosts_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountHostAXFRHosts_data()
{
    QFAIL("TDD");
}

void LibParser::MustCountDnsreconAXFRHosts()
{
    QFAIL("TDD");
}

void LibParser::MustCountNmapAXFRHosts()
{
    QFAIL("TDD");
}

void LibParser::MustCountNslookupWindowsAXFRHosts()
{
    QFAIL("TDD");
}

void LibParser::MustCountNslookupLinuxAXFRHosts()
{
    QFAIL("TDD");
}

void LibParser::MustCountArpscanAXFRHosts()
{
    QFAIL("TDD");
}

void LibParser::MustCountNbtscanAXFRHosts()
{
    QFAIL("TDD");
}

void LibParser::MustCountHostAXFRHosts()
{
    QFAIL("TDD");
}
#pragma PtnigInputParser }

#pragma PtngDgmlBuilder {
void LibParser::MustCreateDGMLFromNmap_data()
{
    QFAIL("TDD");
}

void LibParser::MustCreateDGMLFromNessus_data()
{
    QFAIL("TDD");
}

void LibParser::MustCreateDGMLFromSimple_data()
{
    QFAIL("TDD");
}

void LibParser::MustCreateDGMLFromNmap()
{
    QFAIL("TDD");
}

void LibParser::MustCreateDGMLFromNessus()
{
    QFAIL("TDD");
}

void LibParser::MustCreateDGMLFromSimple()
{
    QFAIL("TDD");
}
#pragma PtngDgmlBuilder }

#pragma PtngDGMLConv {
void LibParser::MustCreateDotrunControl_data()
{
    QFAIL("TDD");
}

void LibParser::MustCreateDotrunControl()
{
    QFAIL("TDD");
}
#pragma PtngDGMLConv }

#pragma All tests - impl }
