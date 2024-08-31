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
#include "sslsendsocket.hpp"

SslSendSocket::SslSendSocket(const QString &host, qint64 port, QObject *parent)
    : QObject{parent}
{
    m_host = host;
    m_port = port;
}

SslSendSocket::~SslSendSocket()
{

}

void SslSendSocket::run()
{
    qInfo() << "Running SslSendSocket in thread" << QThread::currentThread();
    m_handler = new SslClientSignalHandler();
    m_socket = new QSslSocket(m_handler);
    // m_socket->setSocketOption( QAbstractSocket::KeepAliveOption, true );
    m_socket->setObjectName("socket");
    init();
    m_socket->connectToHostEncrypted( m_host, m_port );
    m_socket->write("Hello SSL Server");
    m_socket->waitForReadyRead();
}

void SslSendSocket::init()
{
    /*
       --- Certificates ---
   */
    setClientCert();

    QByteArray certBytes;
    QFile certFile(m_caCertFile);
    if(certFile.open(QIODevice::ReadOnly)){
        certBytes = certFile.readAll();
        certFile.close();
    }
    else{
        qDebug() << "Error with certificate file:"  << m_caCertFile << certFile.errorString();
    }

    QSslCertificate sslCert(certBytes);
    QList<QSslCertificate> certificateList;
    certificateList.append(sslCert);
    // QSslConfiguration conf;
    // setClientCert();
    m_sslconf.setCaCertificates(certificateList);
    m_socket->setSslConfiguration(m_sslconf);
    m_socket->setProtocol(QSsl::SecureProtocols);

    // TODO - is this necessary/useful?
    m_socket->setSocketOption( QAbstractSocket::KeepAliveOption, true );

    /*
           --- Connections ---
       */
    QMetaObject::connectSlotsByName(m_handler);
    // The one that dares to be different
    connect(m_socket, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors), m_handler, &SslClientSignalHandler::sslErrors);
}

void SslSendSocket::setClientCert()
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

    m_sslconf.setLocalCertificate( sslCert );
    m_sslconf.setPrivateKey( sslKey );

}

#pragma Properties {

QSslConfiguration SslSendSocket::sslconf() const
{
    return m_sslconf;
}

void SslSendSocket::setSslconf(const QSslConfiguration &newSslconf)
{
    if (m_sslconf == newSslconf)
        return;
    m_sslconf = newSslconf;
    emit sslconfChanged();
}

QString SslSendSocket::host() const
{
    return m_host;
}

void SslSendSocket::setHost(const QString &newHost)
{
    if (m_host == newHost)
        return;
    m_host = newHost;
    emit hostChanged();
}

qint64 SslSendSocket::port() const
{
    return m_port;
}

void SslSendSocket::setPort(qint64 newPort)
{
    if (m_port == newPort)
        return;
    m_port = newPort;
    emit portChanged();
}

QSslSocket *SslSendSocket::socket() const
{
    return m_socket;
}

void SslSendSocket::setSocket(QSslSocket *newSocket)
{
    if (m_socket == newSocket)
        return;
    m_socket = newSocket;
    emit socketChanged();
}

SslClientSignalHandler *SslSendSocket::handler() const
{
    return m_handler;
}

void SslSendSocket::setHandler(SslClientSignalHandler *newHandler)
{
    if (m_handler == newHandler)
        return;
    m_handler = newHandler;
    emit handlerChanged();
}

QString SslSendSocket::caCertFile() const
{
    return m_caCertFile;
}

void SslSendSocket::setCaCertFile(const QString &newCaCertFile)
{
    if (m_caCertFile == newCaCertFile)
        return;
    m_caCertFile = newCaCertFile;
    emit caCertFileChanged();
}

QString SslSendSocket::clientCertFile() const
{
    return m_clientCertFile;
}

void SslSendSocket::setClientCertFile(const QString &newClientCertFile)
{
    if (m_clientCertFile == newClientCertFile)
        return;
    m_clientCertFile = newClientCertFile;
    emit clientCertFileChanged();
}

QString SslSendSocket::clientKeyFile() const
{
    return m_clientKeyFile;
}

void SslSendSocket::setClientKeyFile(const QString &newClientKeyFile)
{
    if (m_clientKeyFile == newClientKeyFile)
        return;
    m_clientKeyFile = newClientKeyFile;
    emit clientKeyFileChanged();
}

#pragma Properties }
