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
#include <QSslSocket>
#include <QAbstractSocket>
#include <QCoreApplication>
#include <QSslCertificate>
#include <QSslKey>
#include <QSslCertificateExtension>

class SslServerSignalHandler : public QObject
{
    Q_OBJECT
public:
    explicit SslServerSignalHandler(QObject *parent = nullptr);
    ~SslServerSignalHandler();

public slots:
    void on_socket_connected();
    void on_socket_modeChanged(QSslSocket::SslMode mode);
    void on_socket_peerVerifyError(const QSslError &error);
    void on_socket_encrypted();
    void on_socket_readyRead();
    void on_socket_encryptedBytesWritten(qint64 written);
    void on_socket_disconnected();
    void on_socket_errorOccurred(QAbstractSocket::SocketError socketError);
    void on_socket_hostFound();
    void on_socket_proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void on_socket_stateChanged(QAbstractSocket::SocketState socketState);
    void sslErrors(const QList<QSslError> &errors);

private slots:
    void certificateAnalysis( QSslSocket* socket );
};

