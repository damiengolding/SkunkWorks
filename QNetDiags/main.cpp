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
#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QList>

#include "QNetDiagsLogger.hpp"
#include "QNetDiagsConfig.hpp"

void initArgumentParser(QCoreApplication &app, QCommandLineParser &parser);
void initArgumentOptions(QCoreApplication &app, QCommandLineParser &parser);
void processArgumentOptions(QCoreApplication &app, QCommandLineParser &parser);

QList<QCommandLineOption> commandLineOptions;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QNetDiagsLogger::fileName = "qnetdiags_log.txt";
    QNetDiagsLogger::install();

    QCommandLineParser p;
    initArgumentParser(a,p);

    // CODECOMP Add logic after arguments are parsed

    // return(0);
    return(a.exec());
}

void initArgumentParser(QCoreApplication &app, QCommandLineParser &parser){
    app.setApplicationName("qnetdiags");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Golding's Gym");
    app.setOrganizationDomain("https://github.com/damiengolding");

    // Convenience options
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription("qnetdiags Provides diagnostics for TCP, SSL and HTTP client/server");

    initArgumentOptions(app,parser);
    parser.process(app);
    processArgumentOptions(app, parser);
}

void initArgumentOptions(QCoreApplication &app, QCommandLineParser &parser){
    /*
        Various ways to create options:
            Simplest:
                parser.addOption({{"o","output"},"Write to file","file"});
            Create a list:
                QList<QCommandLineOption> commandLineOptions;
                QCommandLineOption op1("short name","description","long name");
                parser.addOption(op1);
                commandLineOptions.append(op1);
        Positional arguments
            parser.addPositionalArgument("list-types", "List supported types");
    */

    // Positional arguments
    parser.addPositionalArgument("client", "Client connection diagnostics.");
    parser.addPositionalArgument("server", "Server listen diagnostic.s");
    parser.addPositionalArgument("tcp", "Plain TCP.");
    parser.addPositionalArgument("http", "Plain HTTP.");
    parser.addPositionalArgument("ssl", "Use SSL.");

    // Options
    parser.addOption({{"t","target"},"Target IP address. Required for client connections.","IP address"});
    parser.addOption({{"p","port"},"Port number. Required for both client connections and server listen.","int"});
    parser.addOption({{"c","cert"},"Certificate file. Required for SS (TCP and HTTP), both client and server.","file"});
    parser.addOption({{"k","key"},"Private key file. Required for SSL (TCP and HTTP) server.","file"});

}

void processArgumentOptions(QCoreApplication &app, QCommandLineParser &parser){
    // CODECOMP Process supplied options
    /*
       Individually:
        if(parser.isSet(<QString name|QCommandLineOption>)){
            Either get the value of an option:
                QString s = parser.value(<QString name|QCommandLineOption>);
            Or operate on a switch, e.g. parser.isSet("verbose"):
        }
       Grouped as QString names:
            for(QString n : parser.optionNames()){
                As above, but no isSet(...) test need
            }
       Grouped as QCommandLineOptions:
            for(QCommandLineOption clo : commandLineOptions ){
                As above
            }
       Manage incorrect/unrecognised/missing options:
            for( QString opt : parser.unknownOptionNames() ){
                qWarning() << ""; // recoverable error
                qCritical() << ""; // non-recoverable error, usually a system error such as read/write/execute privileges
                qFatal(""); // non-recoverable error, will exit and dump core
            }
        Poistional arguments:
            for(QString pos : parser.positionalArguments()){
                qDebug() << "[debug] Positional argument: " << pos;
            }
    */

}

