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
#include "sslserver.hpp"

SslServer::SslServer(const QString &certFile, const QString &keyFile, QObject *parent)
    : QSslServer{parent}
{
    m_certFile = certFile;
    m_keyFile = keyFile;
    init();
}

SslServer::~SslServer()
{

}

#pragma Internal {

void SslServer::init()
{
    setObjectName("sslserver");

    /*
        --- Certificate and key ---
    */
    QByteArray certBytes;
    QByteArray keyBytes;
    QFile certFile( m_certFile );
    QFile keyFile( m_keyFile);

    if( certFile.open(QIODevice::ReadOnly) ){
        certBytes = certFile.readAll();
        certFile.close();
    }
    else{
        qDebug() << "Unable to open certificate file:" << certFile.errorString();
        return;
    }

    if( keyFile.open(QIODevice::ReadOnly) ){
        keyBytes = keyFile.readAll();
        keyFile.close();
    }
    else{
        qDebug() << "Unable to open private key file:" << keyFile.errorString();
        return;
    }

    QSslKey key(keyBytes, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey);
    QSslCertificate cert(certBytes);
    QList<QSslCertificate> certificateList;
    certificateList << cert;
    m_sslconfig.setCaCertificates(certificateList);
    m_sslconfig.setLocalCertificate(cert);
    m_sslconfig.setPrivateKey(key);
    m_sslconfig.setProtocol(QSsl::SecureProtocols);
    m_sslconfig.setPeerVerifyMode( QSslSocket::VerifyPeer );
    this->setSslConfiguration(m_sslconfig);

    /*
        --- Connections ---
    */
    QMetaObject::connectSlotsByName(this);
}

void SslServer::incomingConnection(qintptr handle)
{
    SslReceiveSocket* receiveSocket = new SslReceiveSocket( handle );
    receiveSocket->setCertFile(m_certFile);
    receiveSocket->setKeyFile(m_keyFile);
    QThreadPool* pool = QThreadPool::globalInstance();
    qInfo() << "Starting SslReceiveSocket in thread:" << QThread::currentThread();
    pool->start( receiveSocket );
    receiveSocket->setAutoDelete(true);
    addPendingConnection( receiveSocket->socket() );
}

void SslServer::start(qint64 port)
{
    if( this->listen(QHostAddress::Any, port) )
           qInfo() << "Starting server on port" << port << "in thread:" << QThread::currentThread();
       else
           qFatal() << "Unable to listen on port:" << port;
}

void SslServer::stop()
{
    qInfo() << "Stopping server";
    this->close();
}

#pragma Internal }

#pragma Inherited QTcpServer slots {

void SslServer::on_sslserver_acceptError(QAbstractSocket::SocketError socketError)
{
    qInfo() << "SslServer acceptError";
}

void SslServer::on_sslserver_newConnection()
{
    qInfo() << "SslServer newConnection";
}

void SslServer::on_sslserver_pendingConnectionAvailable()
{
    qInfo() << "SslServe pendingConnectionAvailable";
}

#pragma Inherited QTcpServer slots }

#pragma Inherited QSslServer slots {

void SslServer::on_sslserver_alertReceived(QSslSocket *socket, QSsl::AlertLevel level, QSsl::AlertType type, const QString &description)
{
    qInfo() << "SslServe alertReceived";
}

void SslServer::on_sslserver_alertSent(QSslSocket *socket, QSsl::AlertLevel level, QSsl::AlertType type, const QString &description)
{
    qInfo() << "SslServer alertSent";
}

void SslServer::on_sslserver_errorOccurred(QSslSocket *socket, QAbstractSocket::SocketError socketError)
{
    qInfo() << "SslServer errorOccurred";
}

void SslServer::on_sslserver_handshakeInterruptedOnError(QSslSocket *socket, const QSslError &error)
{
    qInfo() << "SslServe handshakeInterruptedOnError";
}

void SslServer::on_sslserver_peerVerifyError(QSslSocket *socket, const QSslError &error)
{
    qInfo() << " SslServer peerVerifyError";
}

void SslServer::on_sslserver_preSharedKeyAuthenticationRequired(QSslSocket *socket, QSslPreSharedKeyAuthenticator *authenticator)
{
    qInfo() << "SslServer preSharedKeyAuthenticationRequired";
}

void SslServer::on_sslserver_startedEncryptionHandshake(QSslSocket *socket)
{
    qInfo() << "SslServer startedEncryptionHandshake";
}

void SslServer::on_sslserver_sslErrors(QSslSocket *socket, const QList<QSslError> &errors)
{
    qInfo() << "SslServer sslErrors";
    socket->ignoreSslErrors( errors );
}

#pragma Inherited QSslServer slots }
