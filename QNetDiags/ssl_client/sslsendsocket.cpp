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

SslSendSocket::SslSendSocket(const QString &host, qint64 port, const QString &certFile, QObject *parent)
    : QObject{parent}
{
    m_host = host;
    m_port = port;
    m_certFile = certFile;
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
           --- Certificate ---
       */
       QByteArray certBytes;
       QFile certFile(m_certFile);
       if(certFile.open(QIODevice::ReadOnly)){
           certBytes = certFile.readAll();
           certFile.close();
       }
       else{
           qDebug() << "Error with certificate file:"  << m_certFile << certFile.errorString();
       }

       QSslCertificate sslCert(certBytes);
       QList<QSslCertificate> certificateList;
       certificateList.append(sslCert);
       QSslConfiguration conf;
       conf.setCaCertificates(certificateList);
       m_socket->setSslConfiguration(conf);
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
