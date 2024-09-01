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
#include "httpclient.hpp"

HttpClient::HttpClient(QObject *parent)
    : QObject{parent}
{

}

HttpClient::~HttpClient()
{
    m_manager->deleteLater();
}

void HttpClient::start()
{
    qInfo() << "Running SslSendSocket in thread" << QThread::currentThread();
    init();
    // qInfo() << "Local cert:" << m_sslconfig.localCertificate().toPem();
    // qInfo() << "Private key:" << m_sslconfig.privateKey().toPem();

    if( m_ssl ){
        qInfo() << "Connecting with SSL";
        m_manager->connectToHostEncrypted( m_url, m_portNumber, m_sslconfig );
    }
    else{
        qInfo() << "Connecting in plain text";
        m_manager->connectToHost( m_url, m_portNumber );
    }

    if( m_httpMethod.toLower() == "get" ){
        qInfo() << "Using GET";
        this->getMethod();
    }
    else if( m_httpMethod.toLower() == "put" ){
        qInfo() << "Using PUT";
        this->putMethod();
    }
    else if( m_httpMethod.toLower() == "post" ){
        qInfo() << "Using POST";
        this->postMethod();
    }
    else if( m_httpMethod.toLower() == "delete" ){
        qInfo() << "DELETE";
        this->deleteMethod();
    }
    else{
        qInfo() << "HTTP method" << m_httpMethod <<"not recognised";
    }
    // QCoreApplication::exit(0);
}

void HttpClient::init(){
    m_manager = new QNetworkAccessManager();
    /*
        --- QNetworkAccessManager connections ---
    */
    connect(m_manager, &QNetworkAccessManager::authenticationRequired, this, &HttpClient::authenticationRequired);
    connect(m_manager, &QNetworkAccessManager::encrypted ,this, &HttpClient::encrypted);
    connect(m_manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &HttpClient::preSharedKeyAuthenticationRequired);
    connect(m_manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &HttpClient::proxyAuthenticationRequired);
    connect(m_manager, &QNetworkAccessManager::sslErrors, this, &HttpClient::sslErrors);
    connect(m_manager, &QNetworkAccessManager::finished, this, &HttpClient::finished);

    /*
        --- SSL Configuration ---
    */
    // setClientCert();
    QByteArray caCertBytes;

    if( m_caCertFile.isEmpty() ){
        qInfo() << "No CA certificate file specified. HTTP plain text only";
        m_ssl = false;
        return;
    }
    else{
        m_ssl = true;
        QFile certFile(m_caCertFile);
        if(certFile.open(QIODevice::ReadOnly)){
            caCertBytes = certFile.readAll();
            certFile.close();
        }
        else{
            qDebug() << certFile.errorString();
        }
        QSslCertificate caSslCert(caCertBytes);

        QList<QSslCertificate> certificateList;
        certificateList.append(caSslCert);
        m_sslconfig.setCaCertificates(certificateList);
        setClientCert();
    }
}

void HttpClient::setClientCert()
{
    qInfo() << "Setting client certificate";
    if( m_clientCertFile.isEmpty() || m_clientKeyFile.isEmpty() ){
        qInfo() << "Either the client certificate file or the client private key file has not been set.";
        return;
    }

    QByteArray certBytes;
    QByteArray keyBytes;

    QFile certFile(m_clientCertFile);
    if(certFile.open(QIODevice::ReadOnly)){
        qInfo() << "Certificate file is open";
        certBytes = certFile.readAll();
        certFile.close();
    }
    else{
        qDebug() << "Error with client certificate file:"  << m_clientCertFile << certFile.errorString();
        return;
    }

    QFile keyFile(m_clientKeyFile);
    if(keyFile.open(QIODevice::ReadOnly)){
        qInfo() << "Key file is open";
        keyBytes = keyFile.readAll();
        keyFile.close();
    }
    else{
        qDebug() << "Error with client private key file:"  << m_clientKeyFile << keyFile.errorString();
        return;
    }

    QSslCertificate sslCert(certBytes);
    QSslKey sslKey( keyBytes, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey );

    m_sslconfig.setLocalCertificate( sslCert );
    m_sslconfig.setPrivateKey( sslKey );
    m_sslconfig.setProtocol( QSsl::SecureProtocols );
}

void HttpClient::getMethod()
{
    qInfo() << "Testing get verb";
    // QString getUrl = "https://127.0.0.1/upload?file=handbook.pdf";
    // QString getUrl = "https://127.0.0.1/upload?file=notes.txt";
    // QString getUrl = "https://127.0.0.1/upload?file=style_guide_color.docx";
    // QString getUrl = "https://127.0.0.1/upload?file=unzip.exe";
    // QString getUrl = "https://127.0.0.1/upload?file=source.zip";
    QString getUrl = m_url % "/" % "upload?file=" % m_httpFile;
    QNetworkRequest request;
    request.setUrl( QUrl( getUrl ) );
    request.setSslConfiguration( m_sslconfig );
    QNetworkReply* reply = m_manager->get( request );
    qInfo() << "Sent GET request to"<<getUrl;
    connect( reply, &QNetworkReply::errorOccurred, this, &HttpClient::errorOccurred );
    // connect( reply, &QNetworkReply::readyRead, this, &HttpClient::readyRead );
}

void HttpClient::postMethod()
{
    qInfo() << "Testing post verb";
    QString url = "https://127.0.0.1/download";
    QFileInfo fileInfo( "./Source/source.zip" );
    if( !fileInfo.exists() ){
        qInfo() << "File"<< fileInfo.absoluteFilePath()<<"doesn't exist";
        return;
    }
    QFile postFile( fileInfo.absoluteFilePath() );
    if( !postFile.open( QIODevice::ReadOnly )  ){
        qInfo() << "Couldn't open POST file for reading";
        return;
    }
    QByteArray data = postFile.readAll();
    postFile.close();

    // QNetworkReply* reply = m_manager->post( QNetworkRequest( QUrl( url ) ), data );

    QNetworkRequest request;
    request.setUrl( QUrl( url ) );
    request.setSslConfiguration( m_sslconfig );
    request.setHeader( QNetworkRequest::ContentTypeHeader, "multipart/x-zip" );
    request.setRawHeader("File-Name", "source.zip");
    QNetworkReply* reply = m_manager->post( request, data );

    connect( reply, &QNetworkReply::readyRead, this, &HttpClient::readyRead );
    connect( reply, &QNetworkReply::errorOccurred, this, &HttpClient::errorOccurred );
    connect( reply, &QNetworkReply::finished, this, &HttpClient::replyFinished );
}

void HttpClient::deleteMethod()
{
    qInfo() << "Delete method not implemented";
}

void HttpClient::postResponse(QNetworkReply *reply)
{
    qInfo() << "POST response";
    qInfo() << "Reply payload:" << reply->readAll();
}

void HttpClient::deleteResponse(QNetworkReply *reply)
{
    qInfo() << "Delete method not implemented";
}

void HttpClient::putMethod()
{
    qInfo() << "Testing put verb";
    QString url = "https://127.0.0.1/download";
    QFileInfo fileInfo( "./Source/source.zip" );
    if( !fileInfo.exists() ){
        qInfo() << "File"<< fileInfo.absoluteFilePath()<<"doesn't exist";
        return;
    }
    // qInfo() << "PUT file"<<fileInfo.absoluteFilePath();
    QFile putFile( fileInfo.absoluteFilePath() );
    if( !putFile.open( QIODevice::ReadOnly )  ){
        qInfo() << "Couldn't open PUT file for reading";
        return;
    }

    QByteArray data = putFile.readAll();
    putFile.close();

    // QNetworkReply* reply = m_manager->put( QNetworkRequest( QUrl( url ) ), data );

    QNetworkRequest request;
    request.setUrl( QUrl( url ) );
    request.setSslConfiguration( m_sslconfig );
    request.setHeader( QNetworkRequest::ContentTypeHeader, "application/zip" );
    request.setRawHeader("File-Name", "source.zip");
    QNetworkReply* reply = m_manager->put( request, data );

    connect( reply, &QNetworkReply::readyRead, this, &HttpClient::readyRead );
    connect( reply, &QNetworkReply::errorOccurred, this, &HttpClient::errorOccurred );
}

void HttpClient::putResponse(QNetworkReply *reply)
{
    qInfo() << "PUT response";
    qInfo() << "Reply payload:" << reply->readAll();
}

void HttpClient::getResponse(QNetworkReply *reply)
{
    qInfo() << "GET response";
    qInfo() << "Header list:";
    for( auto header : reply->rawHeaderList() ){
        qInfo() << "Header name:"<<header;
    }
    qInfo() << "Headers:";
    for( auto pair : reply->rawHeaderPairs() ){
        qInfo() << "Header:" << pair.first << "Value:" << pair.second;
    }
    QByteArray fileContents = reply->readAll();
    QString fileLocation = "./Upload" % QDir::separator() % m_httpFile;
    QFileInfo fileInfo( fileLocation );
    QFile downloadFile( fileInfo.absoluteFilePath() );
    if( !downloadFile.open( QIODevice::WriteOnly  )  ){
        qInfo() << "Couldn't open"<< fileInfo.absoluteFilePath() << "for writing";
        return;
    }
    QDataStream outputStream(&downloadFile);
    outputStream << fileContents;
    downloadFile.flush();
    downloadFile.close();
}

#pragma QNetworkReply slots {

void HttpClient::errorOccurred(QNetworkReply::NetworkError code){
    qInfo() << "QNetworkReply error:" << code;
}

void HttpClient::replyFinished(){
    qInfo() << "QNetworkReply finished";
}

#pragma QNetworkReply slots }

#pragma QNetworkAccessManager slots {

void HttpClient::readyRead()
{
    qInfo() << "readyRead";
}

void HttpClient::finished(QNetworkReply *reply)
{
    qInfo() << "finished";
    qInfo() << "Response status code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QNetworkAccessManager::Operation operation = reply->operation();

    switch( operation ){
    case 2:{
        qInfo() << "GET response";
        getResponse(reply);
        break;
    }
    case 3:{
        qInfo() << "PUT response";
        putResponse(reply);
        break;
    }
    case 4:{
        qInfo() << "POST response";
        postResponse(reply);
        break;
    }
    case 5:{
        qInfo() << "DELETE response";
        deleteResponse(reply);
        break;
    }

    }

    reply->deleteLater();
    // QCoreApplication::exit(0);
}

void HttpClient::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    qInfo() << "authenticationRequired";
}

void HttpClient::encrypted(QNetworkReply *reply)
{
    qInfo() << "encrypted";
    NetDiagsUtils::certificateAnalysis( reply->sslConfiguration().peerCertificate(), reply->sslConfiguration().peerCertificateChain() );
}

void HttpClient::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    qInfo() << "preSharedKeyAuthenticationRequired";
}

void HttpClient::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qInfo() << "proxyAuthenticationRequired";
}

void HttpClient::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qInfo() << "sslErrors" << errors;
    reply->ignoreSslErrors();
}

#pragma QNetworkAccessManager slots }

#pragma Accessors and mutators {

QNetworkAccessManager *HttpClient::manager() const
{
    return m_manager;
}

QString HttpClient::url() const
{
    return m_url;
}

void HttpClient::setUrl(const QString &newUrl)
{
    if (m_url == newUrl)
        return;
    m_url = newUrl;
    emit urlChanged();
}

qint64 HttpClient::portNumber() const
{
    return m_portNumber;
}

void HttpClient::setPortNumber(qint64 newPortNumber)
{
    if (m_portNumber == newPortNumber)
        return;
    m_portNumber = newPortNumber;
    emit portNumberChanged();
}

QString HttpClient::caCertFile() const
{
    return m_caCertFile;
}

void HttpClient::setCaCertFile(const QString &newCaCertFile)
{
    if (m_caCertFile == newCaCertFile)
        return;
    m_caCertFile = newCaCertFile;
    emit caCertFileChanged();
}

QString HttpClient::clientCertFile() const
{
    return m_clientCertFile;
}

void HttpClient::setClientCertFile(const QString &newClientCertFile)
{
    if (m_clientCertFile == newClientCertFile)
        return;
    m_clientCertFile = newClientCertFile;
    emit clientCertFileChanged();
}

QString HttpClient::clientKeyFile() const
{
    return m_clientKeyFile;
}

void HttpClient::setClientKeyFile(const QString &newClientKeyFile)
{
    if (m_clientKeyFile == newClientKeyFile)
        return;
    m_clientKeyFile = newClientKeyFile;
    emit clientKeyFileChanged();
}

QString HttpClient::httpMethod() const
{
    return m_httpMethod;
}

void HttpClient::setHttpMethod(const QString &newHttpMethod)
{
    if (m_httpMethod == newHttpMethod)
        return;
    m_httpMethod = newHttpMethod;
    emit httpMethodChanged();
}

QString HttpClient::httpFile() const
{
    return m_httpFile;
}

void HttpClient::setHttpFile(const QString &newHttpFile)
{
    if (m_httpFile == newHttpFile)
        return;
    m_httpFile = newHttpFile;
    emit httpFileChanged();
}

#pragma Accessors and mutators }
