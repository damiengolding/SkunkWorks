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

#include <QObject>

#include <QSslServer>
#include <QSslSocket>
#include <QSslKey>
#include <QSslCertificate>

#include <QTcpServer>
#include <QFile>
#include <QMetaEnum>

#include <QRunnable>
#include <QThread>
#include <QThreadPool>

#include "sslreceivesocket.hpp"

class SslServer : public QSslServer
{
    Q_OBJECT
public:
    explicit SslServer(const QString& certFile, const QString& keyFile, QObject *parent = nullptr);
    ~SslServer();

public slots:
    void start( qint64 port );
    void stop();

private slots:
    // QTcpServer
    void on_sslserver_acceptError(QAbstractSocket::SocketError socketError);
    void on_sslserver_newConnection();
    void on_sslserver_pendingConnectionAvailable();

    // QSslServer
    void on_sslserver_alertReceived(QSslSocket *socket, QSsl::AlertLevel level, QSsl::AlertType type, const QString &description);
    void on_sslserver_alertSent(QSslSocket *socket, QSsl::AlertLevel level, QSsl::AlertType type, const QString &description);
    void on_sslserver_errorOccurred(QSslSocket *socket, QAbstractSocket::SocketError socketError);
    void on_sslserver_handshakeInterruptedOnError(QSslSocket *socket, const QSslError &error);
    void on_sslserver_peerVerifyError(QSslSocket *socket, const QSslError &error);
    void on_sslserver_preSharedKeyAuthenticationRequired(QSslSocket *socket, QSslPreSharedKeyAuthenticator *authenticator);
    void on_sslserver_startedEncryptionHandshake(QSslSocket *socket);
    void on_sslserver_sslErrors(QSslSocket *socket, const QList<QSslError> &errors);

    // Internal
    void init();

private: // Members
    QSslConfiguration m_sslconfig;
    QString m_certFile = QString();
    QString m_keyFile = QString();

protected:
    void incomingConnection(qintptr handle) override;
};

