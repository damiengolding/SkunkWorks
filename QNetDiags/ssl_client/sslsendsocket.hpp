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
#include <QFile>
#include <QMetaEnum>
#include <QRunnable>
#include <QThread>
#include <QSslConfiguration>

#include "sslclientsignalhandler.hpp"

class SslSendSocket : public QObject, public QRunnable
{
    Q_OBJECT
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged FINAL)
    Q_PROPERTY(qint64 port READ port WRITE setPort NOTIFY portChanged FINAL)
    Q_PROPERTY(QSslSocket *socket READ socket WRITE setSocket NOTIFY socketChanged FINAL)
    Q_PROPERTY(SslClientSignalHandler *handler READ handler WRITE setHandler NOTIFY handlerChanged FINAL)
    Q_PROPERTY(QString caCertFile READ caCertFile WRITE setCaCertFile NOTIFY caCertFileChanged FINAL)
    Q_PROPERTY(QString clientCertFile READ clientCertFile WRITE setClientCertFile NOTIFY clientCertFileChanged FINAL)
    Q_PROPERTY(QString clientKeyFile READ clientKeyFile WRITE setClientKeyFile NOTIFY clientKeyFileChanged FINAL)
    Q_PROPERTY(QSslConfiguration sslconf READ sslconf WRITE setSslconf NOTIFY sslconfChanged FINAL)

public:
    explicit SslSendSocket(const QString& host, qint64 port, QObject *parent = nullptr);
    ~SslSendSocket();

public:
    void run() override;

    QString host() const;
    void setHost(const QString &newHost);
    qint64 port() const;
    void setPort(qint64 newPort);
    QSslSocket *socket() const;
    void setSocket(QSslSocket *newSocket);
    SslClientSignalHandler *handler() const;
    void setHandler(SslClientSignalHandler *newHandler);
    QString caCertFile() const;
    void setCaCertFile(const QString &newCaCertFile);
    QString clientCertFile() const;
    void setClientCertFile(const QString &newClientCertFile);
    QString clientKeyFile() const;
    void setClientKeyFile(const QString &newClientKeyFile);
    QSslConfiguration sslconf() const;
    void setSslconf(const QSslConfiguration &newSslconf);

signals:
    void hostChanged();
    void portChanged();
    void socketChanged();
    void handlerChanged();
    void caCertFileChanged();
    void clientCertFileChanged();
    void clientKeyFileChanged();
    void sslconfChanged();

private:
    void init();
    void setClientCert();
    QString m_host = {};
    qint64 m_port;
    QSslSocket* m_socket = nullptr;
    SslClientSignalHandler* m_handler = nullptr;
    QString m_caCertFile = {};
    QString m_clientCertFile = {};
    QString m_clientKeyFile = {};
    QSslConfiguration m_sslconf;
};

