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

*/

#include "PtngEnums.hpp"
#include "PtngIdent.hpp"
using namespace ptng;

#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

void initArgumentParser(QCoreApplication &app, QCommandLineParser &parser);
void initArgumentOptions(QCommandLineParser &parser);
void processArgumentOptions(QCommandLineParser &parser);
void processFile(const QString &file);

QList<QCommandLineOption> commandLineOptions;

void showTypes();

int main(int argc, char *argv[])
{
    #ifdef QT_DEBUG
        qDebug() << "Starting ifident";
    #endif
    QCoreApplication a(argc, argv);
    QCommandLineParser p;
    initArgumentParser(a,p);
    //    return(a.exec());
    return(0);
}

// TODO this needs updating
void showTypes(){
    qInfo() << "Supported file types:";
    qInfo() << "nmap - standard scan";
    qInfo() << "nmap - with the dns-zone-transfer.nse script";
    qInfo() << "dns recon - use \'dnsrecon -d <domain> -n <nameserver> -t axfr -x <outputfile>.xml\'";
    qInfo() << "nslookup (windows) - use \'ls -d discworld.io > nslookup_win_axfr.txt\'";
    qInfo() << "nslookup (linux)";
    qInfo() << "arp-scan - use\'arp-scan <address_range> > <outputfile>.txt\'";
    qInfo() << "nbtscan - use \'nbtscan -s : <address_range> <outputfile>.txt\' (the \'s : '\ is required as it is the separator used on each entry)";
    qInfo() << "host - use \'host -t axfr <domain> <nameserver> > host_axfr.txt\'";
}

void initArgumentParser(QCoreApplication &app, QCommandLineParser &parser){
    app.setApplicationName("ifident");
    app.setApplicationVersion("0.0.1");
    app.setOrganizationName("Golding's Gym");

    // Convenience options
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription("ifident takes output files and\nattempts to identify the source tool from a number of\ncommon pen testing tools such as nmap, dig etc ");
    // Init options from here, defined separately in initArgumentOptions
    initArgumentOptions(parser);
    // Process the supplied arguments into the parser
    parser.process(app);
    // Process the arguments supplied to the application so we can use them
    processArgumentOptions(parser);
}

void initArgumentOptions(QCommandLineParser &parser){
    parser.addPositionalArgument("show-types","Currently supported input file types");
    parser.addOption({{"f","file"},"File to identify <file>","file"});
}

void processArgumentOptions(QCommandLineParser &parser){
    // Positional arguments
    for(QString pos : parser.positionalArguments()){
        if( pos.toLower() == "show-types"){
            showTypes();
        }
    }
    // Don't handle poitional arguments and options together, one or the other
    if( parser.positionalArguments().count() > 0 ){
        return;
    }

    if(parser.isSet("file")){
        QString inputFile = parser.value("f");
        #ifdef QT_DEBUG
            qDebug() << ""<< "Input file:" << qPrintable(inputFile);
        #endif
        if( !QFile::exists(inputFile) ){
            qCritical() << "[warning]" << "File" << inputFile <<  "does not exist.";
            return;
        }
        else{
            qInfo() << "[info]"<< "Opening file" << qPrintable(inputFile) << "for processing.";
            processFile(inputFile);
        }
    }
    else{
        qCritical() << "No input file specified - use -h or --help for options";
        return;
    }
}

void processFile(const QString &file){
    PtngEnums::SupportedInputTypes ret = PtngIdent::checkFile(file);
    qInfo() << "[info]" << "File type guess:" << ret;
}


