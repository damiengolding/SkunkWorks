/*
MIT License

Copyright (c) %date% %author%

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
#include "ptngxmlwidget.hpp"
#include "qmenu.h"
#include "ui_ptngxmlwidget.h"
#include "PtngInputParser.hpp"
#include "PtngSpecifications.hpp"
using namespace ptng;

#include <QClipboard>
#include <QMessageBox>
#include <StyleSheet.hpp>

using namespace ptng;

PtngXmlWidget::PtngXmlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PtngXmlWidget)
{
    ui->setupUi(this);
    connect(ui->treeViewXml,
            SIGNAL( customContextMenuRequested(const QPoint&) ),
            this,
            SLOT( showCCMMenu(const QPoint& ) ),
            Qt::UniqueConnection
            );
}

PtngXmlWidget::~PtngXmlWidget()
{
    delete ui;
}

void PtngXmlWidget::display(const QString &inputFile)
{
    type = PtngIdent::checkFile(inputFile);
    // Specialist displays, selected nodes from the source XML
    if( type == PtngEnums::NMAP
            || type == PtngEnums::AXFR_NMAP
            || type == PtngEnums::NESSUS
            || type == PtngEnums::AXFR_DNS_RECON
            || type == PtngEnums::DGML
            || type == PtngEnums::SSL_SCAN
            || type == PtngEnums::METASPLOIT
            || type == PtngEnums::MASSCAN
            || type == PtngEnums::OWASP_ZAP
            || type == PtngEnums::NIKTO
            || type == PtngEnums::WAPITI
            ){

        QScopedPointer<QFile> file(new QFile(inputFile));
        QScopedPointer<QDomDocument> doc( new QDomDocument("input"));
        if( !file->open(QIODevice::ReadOnly) ){
            return;
        }
        if( !doc->setContent(file->readAll())){
            return;
        }

        // Parse and display the XML
        QProgressDialog progressDialog("Click \"Abort\" to return to the GUI","Abort",0,0,this);
        progressDialog.setWindowModality(Qt::WindowModal);
        // progressDialog.
        connect( this,
                 SIGNAL( loadCompleted() ),
                 &progressDialog,
                 SLOT( close() ),
                 Qt::UniqueConnection
                 );
        QStandardItemModel *xmlModel = new QStandardItemModel(this);
        switch (type){
        case PtngEnums::NMAP:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("nmap: " % fi.fileName());
            progressDialog.open();
            displayNmap(doc.data(), xmlModel);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        case PtngEnums::MASSCAN:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("masscan: " % fi.fileName());
            progressDialog.open();
            displayMasscan(doc.data(), xmlModel);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        case PtngEnums::AXFR_NMAP:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("nmap AXFR: " % fi.fileName());
            progressDialog.open();
            displayNmapAxfr(doc.data(), xmlModel);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        case PtngEnums::NESSUS:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("nessus: " % fi.fileName());
            progressDialog.open();
            displayNessus(doc.data(), xmlModel, inputFile);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        case PtngEnums::AXFR_DNS_RECON:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("dnsrecon: " % fi.fileName());
            progressDialog.open();
            displayDnsrecon(doc.data(), xmlModel);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        case PtngEnums::WAPITI:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("wapiti: " % fi.fileName());
            progressDialog.open();
            displayWapiti(doc.data(), xmlModel);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        case PtngEnums::NIKTO:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("nikto: " % fi.fileName());
            progressDialog.open();
            displayNikto(doc.data(), xmlModel);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        case PtngEnums::OWASP_ZAP:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("OWASP ZAP: " % fi.fileName());
            progressDialog.open();
            displayOwaspZap(doc.data(), xmlModel);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        case PtngEnums::SSL_SCAN:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("SslScan: " % fi.fileName());
            progressDialog.open();
            displaySslScan(doc.data(), xmlModel);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        case PtngEnums::METASPLOIT:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("Metasploit: " % fi.fileName());
            progressDialog.open();
            displayMetasploit(doc.data(), xmlModel);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        case PtngEnums::DGML:{
            QFileInfo fi(inputFile);
            ui->labelBanner->setToolTip(fi.absoluteFilePath());
            ui->labelBanner->setText("DGML: " % fi.fileName());
            progressDialog.open();
            displayDgml(doc.data(), xmlModel);
            hasFile = true;
            emit loadCompleted();
            break;
        }
        default:{
            break;
        }
        }
        ui->treeViewXml->setModel(xmlModel);
    }
    else{
        QString msg = QString( "Supplied file %1 is of an  unsupported type" ).arg(inputFile);
        QMessageBox::information(this,"PtngXmlWIdget",msg);
    }
}

// TODO - needs error handling for nodes
void PtngXmlWidget::displayDnsrecon(QDomDocument *doc, QStandardItemModel *model)
{
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Host" } );
    QString type;
    QString name;
    QString zone_server;
    QString address;
    QList<QDomElement> elements = ConversionUtils::domElementList(doc->elementsByTagName("record"));
    QStandardItem *ipv4List = new QStandardItem("IPv4");
    QStandardItem *ipv6List = new QStandardItem("IPv6");
    // IPV4 first
    for( auto element : elements ){
        type = element.attribute("type");
        if( type.toLower() != "a" ){
            continue;
        }
        name = element.attribute("name");
        if( name.startsWith("forestdnszones", Qt::CaseInsensitive)
                || name.startsWith("domaindnszones", Qt::CaseInsensitive)
                || name.startsWith("@")
                || name.startsWith("_")
                ){
            continue;
        }
        address = element.attribute("address");
        zone_server = element.attribute("zone_server");
        QStandardItem *entry = new QStandardItem(name);
        entry->appendRow(new QStandardItem("IPV6 address: " % address));
        entry->appendRow(new QStandardItem("Zone server: " % zone_server));
        ipv4List->appendRow(entry);
    }

    // IPV6 next
    for( auto element : elements ){
        type = element.attribute("type");
        if( type.toLower() != "aaaa" ){
            continue;
        }
        name = element.attribute("name");
        if( name.startsWith("forestdnszones", Qt::CaseInsensitive)
                || name.startsWith("domaindnszones", Qt::CaseInsensitive)
                || name.startsWith("@")
                || name.startsWith("_")
                ){
            continue;
        }
        address = element.attribute("address");
        zone_server = element.attribute("zone_server");
        QStandardItem *entry = new QStandardItem(name);
        entry->appendRow(new QStandardItem("IPV6 address: " % address));
        entry->appendRow(new QStandardItem("Zone server: " % zone_server));
        ipv6List->appendRow(entry);
    }
    root->appendRow(ipv4List);
    root->appendRow(ipv6List);
}

// HPCOMP 2 calls to PtngInputParser::parse*** means reading a large nessus file twice
// TODO - needs error handling for nodes
void PtngXmlWidget::displayNessus(QDomDocument *doc, QStandardItemModel *model, const QString &inputFile)
{    
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Host" } );
    QMap<QString,QString> severities = PtngInputParser::parseNesusSeverities( inputFile );
    QList<PtngIssue> issues = PtngInputParser::parseNesusIssues(inputFile);
    for ( auto [address,severity] : severities.asKeyValueRange()){
        QStandardItem *criticalltems = new QStandardItem("Critical");
        QStandardItem *highltems = new QStandardItem("High");
        QStandardItem *mediumItems = new QStandardItem("Medium");
        QStandardItem *lowltems = new QStandardItem("Low");
        QStandardItem *infoltems = new QStandardItem("Info");
        QString title(address % " - " % severity);
        QStandardItem *host = new QStandardItem(title);
        for( auto issue : issues ){
            if( issue.ipAddress != address ){
                continue;
            }
            QStandardItem *issueItem = new QStandardItem(issue.pluginName);
            QString riskFactor = issue.riskFactor;
            issueItem->appendRow( new QStandardItem("IP address: " + issue.ipAddress) );
            issueItem->appendRow( new QStandardItem("Risk factor: " + riskFactor ) );
            issueItem->appendRow( new QStandardItem("Plugin ID: " + issue.pluginId) );
            issueItem->appendRow( new QStandardItem("Protocol: " + issue.protocol) );
            issueItem->appendRow( new QStandardItem("Port: " + QString::number( issue.portNumber) )  );
            issueItem->appendRow( new QStandardItem("Service name: " + issue.serviceName) );
            issueItem->appendRow( new QStandardItem("Plugin family: " + issue.pluginFamily ) );
            issueItem->appendRow( new QStandardItem("Plugin type: " + issue.pluginType ) );
            issueItem->appendRow( new QStandardItem("Plugin synopsis: " + issue.synopsis ) );
            issueItem->appendRow( new QStandardItem("Plugin description: " + issue.description ) );
            issueItem->appendRow( new QStandardItem("Plugin solution: " + issue.solution ) );
            if( riskFactor.toLower() == "critical" ){
                criticalltems->appendRow(issueItem);
            }
            else if( riskFactor.toLower() == "high" ){
                highltems->appendRow(issueItem);
            }
            else if( riskFactor.toLower() == "medium" ){
                mediumItems->appendRow(issueItem);
            }
            else if( riskFactor.toLower() == "low" ){
                lowltems->appendRow(issueItem);
            }
            else if( riskFactor.toLower() == "none" ){
                infoltems->appendRow(issueItem);
            }
        }
        host->appendRow(criticalltems);
        host->appendRow(highltems);
        host->appendRow(mediumItems);
        host->appendRow(lowltems);
        host->appendRow(infoltems);

#pragma Set forecolor for host items {
        if( severity.toLower() == "critical" ){
            QBrush fontBrush( GoldingsGym::StyleSheet::colorCritical );
            host->setForeground(fontBrush);
        }
        else if( severity.toLower() == "high" ){
            QBrush fontBrush( GoldingsGym::StyleSheet::colorHigh );
            host->setForeground(fontBrush);
        }
        else if( severity.toLower() == "medium" ){
            QBrush fontBrush( GoldingsGym::StyleSheet::colorMedium );
            host->setForeground(fontBrush);
        }
        else if( severity.toLower() == "low" ){
            QBrush fontBrush( GoldingsGym::StyleSheet::colorLow );
            host->setForeground(fontBrush);
        }
        else if( severity.toLower() == "none" ){
            QBrush fontBrush( GoldingsGym::StyleSheet::colorInfo );
            host->setForeground(fontBrush);
        }
#pragma Set forecolor for host items }

        host->setToolTip(severity);
        root->appendRow(host);
    }
}

// TODO - needs error handling for nodes
void PtngXmlWidget::displayMasscan(QDomDocument *doc, QStandardItemModel *model)
{
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Host" } );
    QList<QDomElement> elements = ConversionUtils::domElementList(doc->elementsByTagName("host"));

    // Get list of unique hosts
    QStringList ipAddresses;
    for( auto element : elements ){
        QString addr = element.firstChildElement("address").attribute("addr");
        if( !ipAddresses.contains(addr) ){
            ipAddresses << addr;
        }
    }

    // Create the host node with all of it's ports
    for( auto ipAddress : ipAddresses ){
        QStandardItem *host = new QStandardItem( ipAddress );
        QList<QDomElement> elements = ConversionUtils::domElementList( doc->elementsByTagName("host") );
        for( auto element : elements ){
            QString addr = element.firstChildElement("address").attribute("addr");
            if( addr != ipAddress ){
                continue;
            }
            QDomElement portElem = element.elementsByTagName("port").at(0).toElement();
            QString title = QString( "Port (%1 : %2)" ).arg(portElem.attribute("protocol").toUpper() ).arg(portElem.attribute("portid") );
            QStandardItem *port = new QStandardItem(title);
            QDomElement state = element.elementsByTagName("state").at(0).toElement();
            port->appendRow( new QStandardItem( "State: " % state.attribute("state").toUpper() ) );
            port->appendRow( new QStandardItem( "Reason: " % state.attribute("reason").toUpper()  ) );
            port->appendRow( new QStandardItem( "Reason TTL: " % state.attribute("reason_ttl")  ) );

            host->appendRow(port);
        }
        root->appendRow(host);
    }
}

// TODO - needs error handling for nodes
void PtngXmlWidget::displayNmap(QDomDocument *doc, QStandardItemModel *model)
{
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Host" } );
    QString address;
    QString hostname;
    QString osmatch;
    QString protcol;
    QString portNumber;
    QList<QDomElement> elements = ConversionUtils::domElementList(doc->elementsByTagName("host"));
    for( auto element : elements ){
        // Get the address
        QList<QDomElement> addresses = ConversionUtils::domElementList(element.elementsByTagName("address"));
        for( auto addr : addresses ){
            if( addr.attribute("addrtype").toLower() == "ipv4" ){
                address = addr.attribute("addr");
                // host->appendRow( new QStandardItem( "IP Address: " + address ) );
            }
        }
        QStandardItem *host = new QStandardItem(address);
        // Get hostname and osmatch
        QList<QDomElement> hostnames = ConversionUtils::domElementList(element.elementsByTagName("hostname"));
        if( hostnames.count() > 0  ){
            QDomElement hnElem = hostnames.at(0);
            hostname = hnElem.attribute("name");
            host-> appendRow( new QStandardItem( "Host name: " + hostname ));
        }

        QList<QDomElement> osmatches = ConversionUtils::domElementList(element.elementsByTagName("osmatch"));
        if( osmatches.count() > 0  ){
            QDomElement osMatch = osmatches.at(0);
            osmatch = osMatch.attribute("name");
            host-> appendRow( new QStandardItem( "OS Match: " + osmatch ));
        }

        // Get ports
        QStandardItem *ports = new QStandardItem("Ports");
        QList<QDomElement> portList = ConversionUtils::domElementList( element.elementsByTagName("port") );
        for( auto port : portList ){
            // protocol, portid
            QString portID = QString("%1 : %2").arg( port.attribute("protocol").toUpper() ).arg( port.attribute( "portid") );
            QStandardItem *portSpec = new QStandardItem(portID);
            ports->appendRow(portSpec);
        }
        host->appendRow(ports);
        root->appendRow(host);
    }
}

// TODO - needs error handling for nodes
void PtngXmlWidget::displayNmapAxfr(QDomDocument *doc, QStandardItemModel *model)
{
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Host" } );
    QStandardItem *ipv4Items = new QStandardItem("IPv4");
    QStandardItem *ipv6Items = new QStandardItem("IPv6");
    QList<QDomElement> elements = ConversionUtils::domElementList(doc->elementsByTagName("script"));
    for( auto element : elements){
        if( element.attribute("id") == "dns-zone-transfer"){
            QStringList entries = element.attribute("output").split("\n", Qt::SkipEmptyParts);
            for( auto entry : entries){
                QString temp = entry.simplified();
                if( temp.startsWith("forestdnszones", Qt::CaseInsensitive)
                        || temp.startsWith("domaindnszones", Qt::CaseInsensitive)
                        || temp.startsWith("@", Qt::CaseInsensitive)
                        || temp.startsWith("_", Qt::CaseInsensitive)
                        ){
                    continue;
                }
                QStringList tempList = temp.split(" ");
                if( tempList.count() != 3){
                    continue;
                }
                if( tempList.at(1).toLower() == "a" ){
                    ipv4Items->appendRow( new QStandardItem( tempList.at(0) % " - " % tempList.at(2) ) );
                }
                else if( tempList.at(1).toLower() == "aaaa" ){
                    ipv6Items->appendRow( new QStandardItem( tempList.at(0) % " - " % tempList.at(2) ) );
                }
            }
        }
    }
    root->appendRow(ipv4Items);
    root->appendRow(ipv6Items);
}

// TODO - needs error handling for nodes
void PtngXmlWidget::displaySslScan(QDomDocument *doc, QStandardItemModel *model)
{
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Host" } );
    QStandardItem *hostItems = new QStandardItem("SslScan Results");
    QString sslScanVersion = doc->documentElement().attribute("version");
    QDomElement ssltest = ConversionUtils::domElementList( doc->elementsByTagName("ssltest") ).at(0);
    QString hostname = ssltest.attribute("host");
    QString sniname = ssltest.attribute("sniname");
    QString portNumber = ssltest.attribute("port");

    // renegotiation and compression
    QString renegotiationSupported = ssltest.firstChildElement("renegotiation").attribute("supported") == "0" ? "False" : "True";
    QString renegotiationSecure = ssltest.firstChildElement("renegotiation").attribute("secure") == "0" ? "False" : "True";
    QString compressionSupported  = ssltest.firstChildElement("compression").attribute("supported") == "0" ? "False" : "True";

    hostItems->appendRow( new QStandardItem(  "Host: " % hostname ) );
    hostItems->appendRow( new QStandardItem(  "SNI: " % sniname ) );
    hostItems->appendRow( new QStandardItem(  "Port: " % portNumber ) );

    QStandardItem *reneg = new QStandardItem("Renegotiation");
    reneg->appendRow( new QStandardItem(  "Supported: " % renegotiationSupported ) );
    reneg->appendRow( new QStandardItem(  "Secure: " % renegotiationSecure ) );
    QStandardItem *comp = new QStandardItem("Compression");
    comp->appendRow( new QStandardItem(  "Supported: " % compressionSupported ) );

    // Heartbleed
    QStandardItem *heartbleedItems = new QStandardItem("Heartbleed exposure");
    QList<QDomElement> heartbleeds = ConversionUtils::domElementList( doc->elementsByTagName("heartbleed") );

    for( auto heartbleed : heartbleeds ){
        QStandardItem *hb = new QStandardItem("Heartbleed");
        hb->appendRow( new QStandardItem("SSL Version: " % heartbleed.attribute("sslversion") ) );
        QString vulnBool = heartbleed.attribute("vulnerable") == "0" ? "False" : "True";
        QString vulnerable = "Vulnerable: " % vulnBool;
        hb->appendRow( new QStandardItem( vulnerable ) );
        heartbleedItems->appendRow(hb);
    }

    // Cipher
    QStandardItem *cipher = new QStandardItem("Cipher");
    QDomElement cipherElement = ssltest.firstChildElement("cipher");
    cipher->appendRow( new QStandardItem( "Status: " % cipherElement.attribute("status")) );
    cipher->appendRow( new QStandardItem( "SSL Version: " % cipherElement.attribute("sslversion")) );
    cipher->appendRow( new QStandardItem( "Bits: " % cipherElement.attribute("bits")) );
    cipher->appendRow( new QStandardItem( "Cipher: " % cipherElement.attribute("cipher")) );
    cipher->appendRow( new QStandardItem( "Id: " % cipherElement.attribute("id")) );

    // Certificate
    QDomElement certificateElement = ssltest.firstChildElement("certificate");
    QStandardItem *certificate = new QStandardItem("Certificate");
    QStandardItem *publicKey = new QStandardItem("Public key");
    QDomElement publicKeyElement = certificateElement.firstChildElement("pk");
    publicKey->appendRow( new QStandardItem( "Error: " % publicKeyElement.attribute("error") ) );
    publicKey->appendRow( new QStandardItem( "Type: " % publicKeyElement.attribute("type") ) );
    publicKey->appendRow( new QStandardItem( "Bits: " % publicKeyElement.attribute("bits") ) );
    certificate->appendRow(publicKey);
    certificate->appendRow( new QStandardItem( "Signature Algorithm: " % certificateElement.firstChildElement("signature-algorithm").text() ) );
    certificate->appendRow( new QStandardItem( "Subject: " % certificateElement.firstChildElement("subject").text() ) );
    certificate->appendRow( new QStandardItem( "Issuer: " % certificateElement.firstChildElement("issuer").text() ) );
    certificate->appendRow( new QStandardItem( "Self-signed: " % certificateElement.firstChildElement("self-signed").text() ) );
    certificate->appendRow( new QStandardItem( "Not valid before: " % certificateElement.firstChildElement("not-valid-before").text() ) );
    certificate->appendRow( new QStandardItem( "Not valid after: " % certificateElement.firstChildElement("not-valid-after").text() ) );
    certificate->appendRow( new QStandardItem( "Expired: " % certificateElement.firstChildElement("expired").text() ) );

    hostItems->appendRow(reneg);
    hostItems->appendRow(comp);
    hostItems->appendRow(heartbleedItems);
    hostItems->appendRow(cipher);
    hostItems->appendRow(certificate);
    root->appendRow(hostItems);
}

// TODO - needs error handling for nodes
void PtngXmlWidget::displayNikto(QDomDocument *doc, QStandardItemModel *model)
{
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Results" } );
    QStandardItem *scanResults = new QStandardItem("Scan results");
    QList<QDomElement> elements = ConversionUtils::domElementList( doc->elementsByTagName("item") ) ;
    for( auto element : elements ){
        QStandardItem *item = new QStandardItem( element.firstChildElement("description").text() );
        item->appendRow( new QStandardItem( "Item Id: " % element.attribute("id") ) );
        item->appendRow( new QStandardItem( "Method: " % element.attribute("method") ) );
        QStandardItem *description = new QStandardItem("Description");
        description->appendRow( new QStandardItem( element.firstChildElement("description").text() ) );
        QStandardItem *uri = new QStandardItem("URI");
        uri->appendRow( new QStandardItem( element.firstChildElement("uri").text() ) );
        QStandardItem *namelink = new QStandardItem("Name Link");
        namelink->appendRow( new QStandardItem( element.firstChildElement("namelink").text() ) );
        QStandardItem *iplink = new QStandardItem("IP Link");
        iplink->appendRow( new QStandardItem( element.firstChildElement("iplink").text() ) );
        QStandardItem *references = new QStandardItem("References");
        if( !element.firstChildElement("references").text().isEmpty() ){
            references->appendRow( new QStandardItem( element.firstChildElement("references").text() ) );
        }

        item->appendRow(description);
        item->appendRow(uri);
        item->appendRow(namelink);
        item->appendRow(iplink);
        item->appendRow(references);
        scanResults->appendRow(item);
    }
    root->appendRow(scanResults);
}

// TODO - needs error handling for nodes
void PtngXmlWidget::displayWapiti(QDomDocument *doc, QStandardItemModel *model)
{
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Host" } );
    QStandardItem *scanInfo = new QStandardItem("Scan info");

    QList<QDomElement> infoElements = ConversionUtils::domElementList(doc->elementsByTagName("info") );
    for( auto infoElement : infoElements ){
        if( infoElement.attribute("name") == "generatorVersion" ){
            scanInfo->appendRow( new QStandardItem( "Wapiti version: " % infoElement.text()) );
        }
        else if( infoElement.attribute("name") == "target" ){
            scanInfo->appendRow( new QStandardItem( "Target host: " % infoElement.text()) );
        }
        else if( infoElement.attribute("name") == "crawledPages" ){
            scanInfo->appendRow( new QStandardItem( "Pages crawled: " % infoElement.text()) );
        }
        else if( infoElement.attribute("name") == "scope" ){
            scanInfo->appendRow( new QStandardItem( "Scope: " % infoElement.text()) );
        }
        else if( infoElement.attribute("name") == "dateOfScan" ){
            scanInfo->appendRow( new QStandardItem( "Scan date: " % infoElement.text()) );
        }
    }

    QStandardItem *vulnerabilityInfo = new QStandardItem("Vulnerabilities");
    QList<QDomElement> elements = ConversionUtils::domElementList( doc->elementsByTagName("vulnerability") );

    for( auto element : elements ){
        QStandardItem *vulnerability = new QStandardItem(element.attribute("name"));
        QStandardItem *refs = new QStandardItem("References");
        QStandardItem *ents = new QStandardItem("Entries");

        // Descrption and solution
        QDomElement dElem = element.firstChildElement("description");
        QDomElement sElem = element.firstChildElement("solution");
        QStandardItem *description = new QStandardItem("Description");
        QStandardItem *solution = new QStandardItem("Solution");
        description->appendRow( new QStandardItem(dElem.text()) );
        solution->appendRow( new QStandardItem(sElem.text()) );
        vulnerability->appendRow(description);
        vulnerability->appendRow(solution);

        // References
        QList<QDomElement> references = ConversionUtils::domElementList(element.elementsByTagName("reference"));
        for( auto reference : references ){
            QStandardItem *ref = new QStandardItem( ConversionUtils::domElementList( reference.elementsByTagName("title") ).at(0).text() );
            QStandardItem *url = new QStandardItem( "URL" );
            QStandardItem *wstg = new QStandardItem( "WSTG" );

            url->appendRow( new QStandardItem( ConversionUtils::domElementList( reference.elementsByTagName("url") ).at(0).text() ) );
            wstg->appendRow( new QStandardItem( ConversionUtils::domElementList( reference.elementsByTagName("code") ).at(0).text() ) );

            ref->appendRow(url);
            ref->appendRow(wstg);
            refs->appendRow(ref);
        }
        vulnerability->appendRow(refs);

        // Entries
        QList<QDomElement> entries = ConversionUtils::domElementList(element.elementsByTagName("entry"));
        for( auto entry : entries ){
            QStandardItem *ent = new QStandardItem( ConversionUtils::domElementList( entry.elementsByTagName("info") ).at(0).text() );

            ent->appendRow( new QStandardItem( "Method: " % ConversionUtils::domElementList( entry.elementsByTagName("method") ).at(0).text()  ) );
            ent->appendRow( new QStandardItem( "Path: " % ConversionUtils::domElementList( entry.elementsByTagName("path") ).at(0).text()  ) );
            ent->appendRow( new QStandardItem( "Level: " % ConversionUtils::domElementList( entry.elementsByTagName("level") ).at(0).text()  ) );
            ent->appendRow( new QStandardItem( "Parameter: " % ConversionUtils::domElementList( entry.elementsByTagName("parameter") ).at(0).text()  ) );
            ent->appendRow( new QStandardItem( "Referer: " % ConversionUtils::domElementList( entry.elementsByTagName("referer") ).at(0).text()  ) );
            ent->appendRow( new QStandardItem( "Module: " % ConversionUtils::domElementList( entry.elementsByTagName("module") ).at(0).text()  ) );
            ent->appendRow( new QStandardItem( "Curl: " % ConversionUtils::domElementList( entry.elementsByTagName("curl_command") ).at(0).text()  ) );
            QStandardItem *wstg = new QStandardItem( "WSTG:" );

            QList<QDomElement> wstgCodes = ConversionUtils::domElementList( entry.elementsByTagName("code") );
            for( auto code : wstgCodes ){
                wstg->appendRow( new QStandardItem( "Code: " % code.text() ) );
            }

            QStandardItem *request = new QStandardItem( "HTTP Request:" );
            request->appendRow( new QStandardItem( ConversionUtils::domElementList( entry.elementsByTagName("http_request") ).at(0).text() ) );

            ent->appendRow( wstg );
            ent->appendRow( request );
            ents->appendRow(ent);
        }
        vulnerability->appendRow(ents);

        vulnerabilityInfo->appendRow(vulnerability);
    }

    root->appendRow(scanInfo);
    root->appendRow(vulnerabilityInfo);
}

// TODO - needs error handling for nodes
void PtngXmlWidget::displayOwaspZap(QDomDocument *doc, QStandardItemModel *model)
{
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Host" } );
    QStandardItem *scanInfo = new QStandardItem("OWASP Zap Report");
    QStandardItem *highItems = new QStandardItem("High severity");
    QStandardItem *mediumItems = new QStandardItem("Medium severity");
    QStandardItem *lowItems = new QStandardItem("Low  severity");
    QList<QDomElement> elements = ConversionUtils::domElementList( doc->elementsByTagName("alertitem") );
    for( auto element : elements ){
        // Report meta info
        QList<QDomElement> tempElemList = ConversionUtils::domElementList(element.elementsByTagName("name") );
        QStandardItem *reportInfo = new QStandardItem(tempElemList.at(0).text());
        reportInfo->appendRow( new QStandardItem( "Alert: " % ConversionUtils::domElementList(element.elementsByTagName("alert") ).at(0).text() ) );
        reportInfo->appendRow( new QStandardItem( "Plugin Id: " % ConversionUtils::domElementList(element.elementsByTagName("pluginid") ).at(0).text() ) );
        reportInfo->appendRow( new QStandardItem( "Alert Reference: " % ConversionUtils::domElementList(element.elementsByTagName("alertRef") ).at(0).text() ) );
        reportInfo->appendRow( new QStandardItem( "Risk Description: " % ConversionUtils::domElementList(element.elementsByTagName("riskdesc") ).at(0).text() ) );
        QStandardItem *description = new QStandardItem( "Description: " % ConversionUtils::domElementList(element.elementsByTagName("desc") ).at(0).text() );
        reportInfo->appendRow(description);
        scanInfo->appendRow(reportInfo);

        reportInfo->appendRow( new QStandardItem( "Count: " % ConversionUtils::domElementList(element.elementsByTagName("count") ).at(0).text() ) );
        reportInfo->appendRow( new QStandardItem( "Solution: " % ConversionUtils::domElementList(element.elementsByTagName("solution") ).at(0).text() ) );
        reportInfo->appendRow( new QStandardItem( "Other info: " % ConversionUtils::domElementList(element.elementsByTagName("otherinfo") ).at(0).text() ) );
        reportInfo->appendRow( new QStandardItem( "Reference: " % ConversionUtils::domElementList(element.elementsByTagName("reference") ).at(0).text() ) );
        reportInfo->appendRow( new QStandardItem( "CWE Id: " % ConversionUtils::domElementList(element.elementsByTagName("cweid") ).at(0).text() ) );
        reportInfo->appendRow( new QStandardItem( "WA SC Id: " % ConversionUtils::domElementList(element.elementsByTagName("wascid") ).at(0).text() ) );
        reportInfo->appendRow( new QStandardItem( "Source Id: " % ConversionUtils::domElementList(element.elementsByTagName("sourceid") ).at(0).text() ) );

        // Instances
        QStandardItem *observations = new QStandardItem("Observations");
        tempElemList = ConversionUtils::domElementList(element.elementsByTagName("instance") );
        for( auto observation : tempElemList ){
            QStandardItem *observed= new QStandardItem(ConversionUtils::domElementList(observation.elementsByTagName("uri") ).at(0).text() );
            // observations->appendRow( new QStandardItem( "URI: " % ConversionUtils::domElementList(element.elementsByTagName("uri") ).at(0).text()  )  );
            observed->appendRow( new QStandardItem( "Method: " % ConversionUtils::domElementList(observation.elementsByTagName("method") ).at(0).text()  )  );
            observed->appendRow( new QStandardItem( "Param: " % ConversionUtils::domElementList(observation.elementsByTagName("param") ).at(0).text()  )  );
            observed->appendRow( new QStandardItem( "Attack: " % ConversionUtils::domElementList(observation.elementsByTagName("attack") ).at(0).text()  )  );
            observed->appendRow( new QStandardItem( "Evidence: " % ConversionUtils::domElementList(observation.elementsByTagName("evidence") ).at(0).text()  )  );
            observed->appendRow( new QStandardItem( "Other Info: " % ConversionUtils::domElementList(observation.elementsByTagName("otherinfo") ).at(0).text()  )  );
            observations->appendRow(observed);
        }

        reportInfo->appendRow(observations);
    }
    root->appendRow(scanInfo);
}

// TODO - finish implemention with a full MSF output XML, currently only a few entries
// TODO - needs error handling for nodes
void PtngXmlWidget::displayMetasploit(QDomDocument *doc, QStandardItemModel *model)
{
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Host" } );
    QList<QDomElement> elements = ConversionUtils::domElementList( doc->elementsByTagName("host") );
    for( auto element : elements ){
        QStandardItem *host = new QStandardItem( element.firstChildElement("address").text() );
        host->appendRow( new QStandardItem( "OS Name: " % element.firstChildElement("os-name").text() ) );
        host->appendRow( new QStandardItem( "MAC Address: " % element.firstChildElement("mac").text() ) );
        host->appendRow( new QStandardItem( "Name: " % element.firstChildElement("name").text() ) );
        host->appendRow( new QStandardItem( "State: " % element.firstChildElement("state").text() ) );
        host->appendRow( new QStandardItem( "Purpose: " % element.firstChildElement("purpose").text() ) );
        host->appendRow( new QStandardItem( "Vulnerability Count: " % element.firstChildElement("vuln-count").text() ) );
        host->appendRow( new QStandardItem( "Service Count: " % element.firstChildElement("service-count").text() ) );
        host->appendRow( new QStandardItem( "Exploit Attempt Count: " % element.firstChildElement("exploit-attempt-count").text() ) );
        host->appendRow( new QStandardItem( "Credential(s) Count: " % element.firstChildElement("cred-count").text() ) );
        host->appendRow( new QStandardItem( "Created: " % element.firstChildElement("created-at").text() ) );
        host->appendRow( new QStandardItem( "Updated: " % element.firstChildElement("updated-at").text() ) );

        // Services
        QStandardItem *servicesItem = new QStandardItem("Services");
        QList<QDomElement> services  = ConversionUtils::domElementList( element.elementsByTagName("service") );
        for( auto service : services ){
            QString svcName = service.firstChildElement("name").text();
            if( svcName.isEmpty() ){
                svcName = "Unknown";
            }
            QStandardItem *serviceItem = new QStandardItem( svcName );
            serviceItem->appendRow( new QStandardItem( "Protocol: " % service.firstChildElement("proto").text() ) );
            serviceItem->appendRow( new QStandardItem( "Port: " % service.firstChildElement("port").text() ) );
            serviceItem->appendRow( new QStandardItem( "State: " % service.firstChildElement("state").text() ) );
            servicesItem->appendRow(serviceItem);
        }

        // Vulnerabilities
        QStandardItem *vulnerabilitiesItem = new QStandardItem("Vulnerabilities");
        QList<QDomElement> vulnerabilities  = ConversionUtils::domElementList( element.elementsByTagName("vuln") );

        for( auto vulnerability : vulnerabilities ){
            QStandardItem *vulnerabilityItem = new QStandardItem( vulnerability.firstChildElement("name").text() );
            QStandardItem *infoItem = new QStandardItem("Description:" );
            infoItem->appendRow( new QStandardItem( vulnerability.firstChildElement("info").text() ) );
            vulnerabilityItem->appendRow(infoItem);
            vulnerabilityItem->appendRow( new QStandardItem( "Detail Count: " % vulnerability.firstChildElement("vuln-detail-count").text() ) );
            vulnerabilityItem->appendRow( new QStandardItem( "Attempt Count: " % vulnerability.firstChildElement("vuln-attempt-count").text() ) );

            QStandardItem *refItem = new QStandardItem("References:" );
            QList<QDomElement> references = ConversionUtils::domElementList( vulnerability.elementsByTagName("ref") );
            for( auto reference : references ){
                refItem->appendRow( new QStandardItem( reference.text() ) );
            }
            vulnerabilityItem->appendRow(refItem);
            vulnerabilitiesItem->appendRow(vulnerabilityItem);
        }

        // TODO - web_sites

        // TODO - web_pages

        // TODO - web_forms

        // TODO - web_vulns

        // TODO - module_details

        host->appendRow(servicesItem);
        host->appendRow(vulnerabilitiesItem);
        root->appendRow(host);
    }
}

// TODO - needs error handling for nodes
void PtngXmlWidget::displayDgml(QDomDocument *doc, QStandardItemModel *model)
{
    QStandardItem *root = model->invisibleRootItem();
    model->setHorizontalHeaderLabels( { "Element" } );

    // Nodes
    QList<QDomElement> elements = ConversionUtils::domElementList( doc->elementsByTagName("Node") );
    QStandardItem *nodes = new QStandardItem("Nodes");
    for( auto element : elements ){
        QStandardItem *node = new QStandardItem("Node");
        QDomNamedNodeMap attributes = element.attributes();
        for( int i = 0; i<attributes.count(); ++i){
            QDomAttr attribute = attributes.item(i).toAttr();
            QString entry = QString("%1=%2").arg( attribute.name() ).arg( attribute.value() );
            node->appendRow( new QStandardItem( entry ) );
        }
        nodes->appendRow(node);
    }

    // Links
    elements = ConversionUtils::domElementList( doc->elementsByTagName("Link") );
    QStandardItem *links = new QStandardItem("Links");
    QString linkSource;
    QString linkTarget;
    QStringList linkList;
    for( auto element : elements ){
        QStandardItem *link = new QStandardItem("Link");
        QDomNamedNodeMap attributes = element.attributes();
        for( int i = 0; i<attributes.count(); ++i){
            QDomAttr attribute = attributes.item(i).toAttr();
            QString linkLabel = attribute.value();
            if( linkLabel.isEmpty() ){ // The case where no labels has been specfiied in the creation of the link element of the DGML
                continue;
            }
            if( attribute.name() == "Source"  ){
                linkSource = attribute.value();
            }
            else if( attribute.name() == "Target" ){
                linkTarget = attribute.value();
            }
            QString title;
            if( !linkSource.isEmpty() && !linkTarget.isEmpty()  ){
                title = QString( "Link (%1->%2)" ).arg( linkSource ).arg( linkTarget );
                // De-dupe - not sure why the DGML contains duplicates but it looks shoddy
                if( linkList.contains(title)  ){
                    continue;
                }
                linkList << title;
                link->setText( title );
            }
            QString entry = QString("%1=%2").arg( attribute.name() ).arg( linkLabel );
            link->appendRow( new QStandardItem( entry ) );
        }
        if( link->hasChildren() ){
            links->appendRow(link);
        }
    }

    // Categories
    elements = ConversionUtils::domElementList( doc->elementsByTagName("Category") );
    QStandardItem *categories = new QStandardItem("Categories");
    for( auto element : elements ){
        QStandardItem *category = new QStandardItem("Category");
        QDomNamedNodeMap attributes = element.attributes();
        for( int i = 0; i<attributes.count(); ++i){
            QDomAttr attribute = attributes.item(i).toAttr();
            if( attribute.name() == "Label" ){
                category->setText( QString( "Category - %1").arg( attribute.value() ) );
            }
            QString entry = QString("%1=%2").arg( attribute.name() ).arg( attribute.value() );
            category->appendRow( new QStandardItem( entry ) );
        }
        categories->appendRow(category);
    }

    // Properties
    elements = ConversionUtils::domElementList( doc->elementsByTagName("Property") );
    QStandardItem *properties = new QStandardItem("Properties");
    for( auto element : elements ){
        QStandardItem *property = new QStandardItem("Property");
        QDomNamedNodeMap attributes = element.attributes();
        for( int i = 0; i<attributes.count(); ++i){
            QDomAttr attribute = attributes.item(i).toAttr();
            QString entry = QString("%1=%2").arg( attribute.name() ).arg( attribute.value() );
            property->appendRow( new QStandardItem( entry ) );
        }
        properties->appendRow(property);
    }

    // Paths
    elements = ConversionUtils::domElementList( doc->elementsByTagName("Path") );
    QStandardItem *paths = new QStandardItem("Paths");
    for( auto element : elements ){
        QStandardItem *path = new QStandardItem("Path");
        QDomNamedNodeMap attributes = element.attributes();
        for( int i = 0; i<attributes.count(); ++i){
            QDomAttr attribute = attributes.item(i).toAttr();
            QString entry = QString("%1=%2").arg( attribute.name() ).arg( attribute.value() );
            path->appendRow( new QStandardItem( entry ) );
        }
        paths->appendRow(path);
    }

    root->appendRow(nodes);
    root->appendRow(links);
    root->appendRow(categories);
    root->appendRow(properties);
    root->appendRow(paths);
}

/*
 * Internal management
 */

void PtngXmlWidget::showCCMMenu(const QPoint &point)
{
    if( !hasFile ){
        return;
    }
    QMenu *ccMenu = new QMenu();
    QAction *copy = new QAction();
    copy->setText("Copy selected");
    connect( copy,
             SIGNAL( triggered(bool)),
             this,
             SLOT( copy(bool) ),
             Qt::UniqueConnection
             );
    ccMenu->addAction(copy);
    ccMenu->exec(QCursor::pos());
}

void PtngXmlWidget::copy(bool checked)
{
    QModelIndexList selections = ui->treeViewXml->selectionModel()->selectedIndexes();
    QStringList stringList;
    for( auto selection : selections ){
        stringList << selection.data().toString();
    }
    QString copyText = stringList.join("\n");
    QClipboard *clipBoard = QGuiApplication::clipboard();
    clipBoard->setText(copyText);
}

QString PtngXmlWidget::getBanner()
{
    return banner;
}

void PtngXmlWidget::setBanner(const QString &newBanner)
{
    if (banner == newBanner)
        return;
    banner = newBanner;
    ui->labelBanner->setText(banner);
    emit bannerChanged();
}

