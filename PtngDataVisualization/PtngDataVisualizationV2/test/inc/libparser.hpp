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
#pragma once

#include <QTest>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDomDocument>
#include <QDomNode>
#include <QDomNodeList>
#include <QDomElement>

#include "testutilities.hpp"

class LibParser : public QObject
{
    Q_OBJECT

public:
    LibParser();
    ~LibParser();
    QString runControl = "parserlib_test.xml";

private slots:
    void initTestCase();
    void cleanupTestCase();

#pragma All tests - decl {
#pragma PtngIdent {
    void MustRecogniseRuncontrol_data();
    void MustRecogniseRuncontrol();
#pragma PtngIdent }

#pragma PtnigInputParser {
    // nmap & nessus
    void MustCountNmapHosts_data();
    void MustCountNessusHosts_data();
    void MustCountNessusIssues_data();
    void MustCountNessusSeverities_data();

    void MustCountNmapHosts();
    void MustCountNessusHosts();
    void MustCountNessusIssues();
    void MustCountNessusSeverities();

    // AXFR files
    void MustCountDnsreconAXFRHosts_data();
    void MustCountNmapAXFRHosts_data();
    void MustCountNslookupWindowsAXFRHosts_data();
    void MustCountNslookupLinuxAXFRHosts_data();
    void MustCountArpscanAXFRHosts_data();
    void MustCountNbtscanAXFRHosts_data();
    void MustCountHostAXFRHosts_data();

    void MustCountDnsreconAXFRHosts();
    void MustCountNmapAXFRHosts();
    void MustCountNslookupWindowsAXFRHosts();
    void MustCountNslookupLinuxAXFRHosts();
    void MustCountArpscanAXFRHosts();
    void MustCountNbtscanAXFRHosts();
    void MustCountHostAXFRHosts();
#pragma PtnigInputParser }

#pragma PtngDgmlBuilder {
    void MustCreateDGMLFromNmap_data();
    void MustCreateDGMLFromNessus_data();
    void MustCreateDGMLFromSimple_data();
    void MustCreateDGMLFromNmap();
    void MustCreateDGMLFromNessus();
    void MustCreateDGMLFromSimple();
#pragma PtngDGMLBuilder }

#pragma PtngDGMLConv {
    void MustCreateDotrunControl_data();
    void MustCreateDotrunControl();
#pragma PtngDGMLConv }

#pragma All tests - decl }


};
