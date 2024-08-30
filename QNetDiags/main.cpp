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
#include <QFileInfo>

#include "commands/commands.hpp"

void initArgumentParser(QCoreApplication &app, QCommandLineParser &parser);
void initArgumentOptions(QCoreApplication &app, QCommandLineParser &parser);
void processArgumentOptions(QCoreApplication &app, QCommandLineParser &parser);

bool testCertAndKeyFiles();
bool testCertFile();

QList<QCommandLineOption> commandLineOptions;

QString targetHost = QString();
qint64 targetPort = -1;
bool useSsl = false;
QString certFile = QString();
QString keyFile = QString();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser p;
    initArgumentParser(a,p);

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
    parser.setApplicationDescription("qnetdiags Provides diagnostics for TCP, SSL and HTTP client/server.\r\n\r\nThe application of SSL is inferred by the presence of the key and cert options.");

    initArgumentOptions(app,parser);
    parser.process(app);
    processArgumentOptions(app, parser);
}

void initArgumentOptions(QCoreApplication &app, QCommandLineParser &parser){
    // Positional arguments
    parser.addPositionalArgument("client", "Client connection diagnostics.");
    parser.addPositionalArgument("server", "Server listen diagnostic.s");
    parser.addPositionalArgument("tcp", "TCP client or server.");
    parser.addPositionalArgument("http", "HTTP client or server.");
    parser.addPositionalArgument("ssl", "Use SSL if certificate and key files are valid.");

    // Options
    parser.addOption({{"t","target"},"Target IP address. Required for all client connections.","IP address"});
    parser.addOption({{"p","port"},"Port number. Required for both client connections and server listen.","int"});
    parser.addOption({{"c","cert"},"Certificate file. Required for SSL (TCP and HTTP), both client and server.","file"});
    parser.addOption({{"k","key"},"Private key file. Required for SSL (TCP and HTTP) server.","file"});
    parser.addOption({{"m","method"},"HTTP method. Required for HTTP(s) client.","get|put|post|delete"});
    parser.addOption({{"d","data"},"Data to append. Required for HTTP(s) client with either the put or post method.","get|put|post|delete"});

}

void processArgumentOptions(QCoreApplication &app, QCommandLineParser &parser){
    if( parser.isSet("port") ){
        targetPort = parser.value("port").toInt();
    }
    else{
        qCritical() << "No port  number is set. Everything needs a port number to call home.";
        parser.showHelp( 1 );
    }

    if( parser.isSet("target") ) targetHost = parser.value("target");
    if( parser.isSet("key") ) keyFile = parser.value("key");
    if( parser.isSet("cert") ) certFile = parser.value("cert");

    QStringList arguments = parser.positionalArguments();
    if( arguments.contains("client") ){
        if( targetHost.isEmpty() ){
            qCritical() << "Target host must be set.";
            parser.showHelp( 2 );
        }
        if( arguments.contains("tcp") ){
            if( arguments.contains("ssl") && testCertFile() )
                tcp_client( targetHost, targetPort, certFile);
            else
                tcp_client( targetHost, targetPort );
        }
        else if( arguments.contains("http") ){
                http_client(targetHost, targetPort);
        }
        else{
            qInfo() << "No switch is set for TCP or HTTP";
            parser.showHelp( 3 );
        }
    }
    else if( arguments.contains("server") ){
        QFileInfo certFileInfo( certFile );
        QFileInfo keyFileInfo( keyFile );
        QFile certInputFile( certFileInfo.absoluteFilePath() );
        QFile keyInputFile( keyFileInfo.absoluteFilePath() );

        if( arguments.contains("tcp") ){
            if( arguments.contains("ssl") && testCertAndKeyFiles() )
                tcp_server(targetPort, certFileInfo.absoluteFilePath(), keyFileInfo.absoluteFilePath());
            else
                tcp_server(targetPort);
        }
        else if( arguments.contains("http") ){
            if( arguments.contains("ssl") && testCertAndKeyFiles() )
                http_server(targetPort, certFileInfo.absoluteFilePath(), keyFileInfo.absoluteFilePath());
            else
                http_server(targetPort);
        }
        else{
            qInfo() << "No switch is set for TCP or HTTP";
            parser.showHelp( 3 );
        }
    }
    else{
        qCritical() << "No switch is set for client or server.";
        parser.showHelp( 3 );
    }
}

bool testCertAndKeyFiles(){
    if( certFile.isEmpty() || keyFile.isEmpty() ){
        qInfo() << "Certificate file or private key file not set. Running as plain text TCP server";
        return( false );
    }
    else{
        QFileInfo certFileInfo( certFile );
        QFileInfo keyFileInfo( keyFile );
        QFile certInputFile( certFileInfo.absoluteFilePath() );
        QFile keyInputFile( keyFileInfo.absoluteFilePath() );
        if( !certFileInfo.exists() || !keyFileInfo.exists() ){
            qCritical() << "Certificate or private key file doesn't exist.";
            return(false);
        }
        if( !certInputFile.open( QIODevice::ReadOnly) || !keyInputFile.open( QIODevice::ReadOnly) ){
            qCritical() << "Unable to open certificate or private key file..";
            return( false );
        }
        if( certInputFile.isOpen() ) certInputFile.close();
        if( keyInputFile.isOpen() ) keyInputFile.close();
    }
    return( true );
}

bool testCertFile(){
    if( certFile.isEmpty() ){
        qInfo() << "Certificate file not set for client.";
        return( false );
    }
    else{
        QFileInfo certFileInfo( certFile );
        QFile certInputFile( certFileInfo.absoluteFilePath() );
        if( !certFileInfo.exists() ){
            qCritical() << "Certificate file doesn't exist.";
            return(false);
        }
        if( certInputFile.isOpen() ) certInputFile.close();
    }
    return( true );
}
