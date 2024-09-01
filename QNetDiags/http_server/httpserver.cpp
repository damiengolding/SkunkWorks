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
#include "httpserver.hpp"

HttpServer::HttpServer(QObject *parent)
    : QObject{parent}
{

}

HttpServer::~HttpServer()
{

}

void HttpServer::start()
{
    /*
        --- Basic setup ---
    */
    m_server = new QHttpServer();
    m_server->setObjectName("server");

    /*
        --- Certificate and private key ---
    */
    if( !m_certFile.isEmpty() && !m_keyFile.isEmpty() ){
        qInfo() << "Setting up SSL";
        m_ssl = true;
        QList<QSslCertificate> certificateChain = QSslCertificate::fromPath(m_certFile);
        if( certificateChain.empty() ){
            qCritical() << "No certificates found";
            return;
        }

        QFile keyFile( m_keyFile );
        if( !keyFile.open(QIODevice::ReadOnly) ){
            qCritical() << "Unable to open private key file";
            return;
        }

        QSslConfiguration config;
        config.setLocalCertificate(certificateChain.at(0));
        config.setPrivateKey( QSslKey( &keyFile, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey ) );
        config.setProtocol( QSsl::SecureProtocols );
        config.setPeerVerifyMode( QSslSocket::AutoVerifyPeer );
        m_server->sslSetup(config);
        qInfo() << "QHttpServer: SSL setup complete";
        keyFile.close();
    }

    // After request
    m_server->afterRequest([] (QHttpServerResponse &&resp, const QHttpServerRequest &request) {
        qInfo() << "After request";
        NetDiagsUtils::certificateAnalysis(request.sslConfiguration().peerCertificate(), request.sslConfiguration().peerCertificateChain());
        return std::move(resp);
    });

    /*
        --- Routes ---
    */
    m_server->route("/", [&]() {
        qInfo() << "Incoming connection to root route";
        if( m_ssl ){
            return "For a moment, nothing happened. Then, after a second or so, nothing continued to happen.";
        }
        else{
            return "So long, and thanks for all the fish.";
        }
    });

    m_server->route("/qotd", []() {
        qInfo() << "Incoming connection to qotd route";
        return "We demand rigidly defined areas of doubt and uncertainty!";
    });

    m_server->route("/upload", QHttpServerRequest::Method::Get, [](const QHttpServerRequest &request) {
        qInfo() << "Incoming connection to upload route";
        NetDiagsUtils::certificateAnalysis(request.sslConfiguration().peerCertificate(), request.sslConfiguration().peerCertificateChain());
        QString requestedFile;
        QList< std::pair<QString, QString> > items = request.query().queryItems();
        for( auto item :  items ){
            if( item.first.toLower() == "file"  ){
                requestedFile = item.second;
            }
        }

        if( requestedFile.isEmpty() ){
            qInfo() << "Bad request";
            return( QHttpServerResponse( QHttpServerResponder::StatusCode::BadRequest ) );
        }
        else{
            QString fileLocation = "./Source" % QDir::separator() % requestedFile;
            QFileInfo fileInfo( fileLocation );
            qInfo() << "File absolute path:" << fileInfo.absoluteFilePath();

            if( !QFileInfo::exists( fileLocation ) ){
                qInfo() << "Not found";
                return( QHttpServerResponse( QHttpServerResponder::StatusCode::NotFound ) );
            }
            else{
                qInfo() << "OK";
                QHttpServerResponse response = QHttpServerResponse::fromFile( fileLocation );
                response.addHeader(  QString( "File-Name" ).toLatin1(), requestedFile.toLatin1()) ;
                return( response );
                // return( QHttpServerResponse::fromFile( fileLocation ) );
            }
        }
    });

    m_server->route("/download", QHttpServerRequest::Method::Get, [](const QHttpServerRequest &request) {
        qInfo() << "Download for method:" << request.method();
        return("GET method is not supported on this route");
    });

    m_server->route("/download", QHttpServerRequest::Method::Post, []( const QHttpServerRequest &request) {
        qInfo() << "Download for method:" << request.method();
        QString fileName;

        for( auto header : request.headers() ){
            qInfo() << "Header name:" << header.first << "value:" << header.second;
            if( header.first == "File-Name" ){
                fileName = header.second;
            }
        }

        qInfo() << "File name:"<<fileName;
        QString saveFileName = "./Download" % QDir::separator() % fileName;
        QFileInfo fileInfo(saveFileName);
        QFile outputFile( fileInfo.absoluteFilePath() );
        if( !outputFile.open( QIODevice::WriteOnly ) ){
            QString errorMessage = "Couldn't open " % fileInfo.absoluteFilePath() % "for writing";
            qInfo() <<  errorMessage;
            return(errorMessage);
        }
        QDataStream stream( &outputFile );
        QByteArray data = request.body();
        stream << data;
        outputFile.flush();
        outputFile.close();

        QString message = "Called download for POST: file saved locally to: " % fileInfo.absoluteFilePath();
        return( message );
    });

    m_server->route("/download", QHttpServerRequest::Method::Put, []( const QHttpServerRequest &request) {
        qInfo() << "Download for method:" << request.method();
        QString fileName;

        for( auto header : request.headers() ){
            qInfo() << "Header name:" << header.first << "value:" << header.second;
            if( header.first == "File-Name" ){
                fileName = header.second;
            }
        }

        qInfo() << "File name:"<<fileName;
        QString saveFileName = "./Download" % QDir::separator() % fileName;
        QFileInfo fileInfo(saveFileName);
        QFile outputFile( fileInfo.absoluteFilePath() );
        if( !outputFile.open( QIODevice::WriteOnly ) ){
            QString errorMessage = "Couldn't open " % fileInfo.absoluteFilePath() % "for writing";
            qInfo() <<  errorMessage;
            return(errorMessage);
        }
        QDataStream stream( &outputFile );
        QByteArray data = request.body();
        stream << data;
        outputFile.flush();
        outputFile.close();

        QString message = "Called download for PUT: file saved locally to: " % fileInfo.absoluteFilePath();
        return( message );
    });

    m_server->listen(QHostAddress::Any, m_port);
    qInfo() << "Listening on QHostAddress::Any port" << m_port << "SSL:" << m_ssl;
}

#pragma Properties {

qint64 HttpServer::port() const
{
    return m_port;
}

void HttpServer::setPort(qint64 newPort)
{
    if (m_port == newPort)
        return;
    m_port = newPort;
    emit portChanged();
}

QString HttpServer::certFile() const
{
    return m_certFile;
}

void HttpServer::setCertFile(const QString &newCertFile)
{
    if (m_certFile == newCertFile)
        return;
    m_certFile = newCertFile;
    emit certFileChanged();
}

QString HttpServer::keyFile() const
{
    return m_keyFile;
}

void HttpServer::setKeyFile(const QString &newKeyFile)
{
    if (m_keyFile == newKeyFile)
        return;
    m_keyFile = newKeyFile;
    emit keyFileChanged();
}

bool HttpServer::ssl() const
{
    return m_ssl;
}

void HttpServer::setSsl(bool newSsl)
{
    if (m_ssl == newSsl)
        return;
    m_ssl = newSsl;
    emit sslChanged();
}

#pragma Properties }
