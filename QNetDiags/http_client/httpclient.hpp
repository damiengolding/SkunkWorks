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
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkCookie>
#include <QSslConfiguration>
#include <QSslKey>
#include <QFile>
#include <QDir>
#include <QDataStream>
#include <QHttpMultiPart>
#include <QMetaEnum>

#include <QRunnable>
#include <QThread>

#include "utils/netdiagsutils.hpp"

class HttpClient : public QObject //, public QRunnable
{
    Q_OBJECT
    Q_PROPERTY(QNetworkAccessManager *manager READ manager MEMBER m_manager NOTIFY managerChanged FINAL)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged FINAL)
    Q_PROPERTY(qint64 portNumber READ portNumber WRITE setPortNumber NOTIFY portNumberChanged FINAL)
    Q_PROPERTY(QString caCertFile READ caCertFile WRITE setCaCertFile NOTIFY caCertFileChanged FINAL)
    Q_PROPERTY(QString clientCertFile READ clientCertFile WRITE setClientCertFile NOTIFY clientCertFileChanged FINAL)
    Q_PROPERTY(QString clientKeyFile READ clientKeyFile WRITE setClientKeyFile NOTIFY clientKeyFileChanged FINAL)
    Q_PROPERTY(QString httpMethod READ httpMethod WRITE setHttpMethod NOTIFY httpMethodChanged FINAL)
    Q_PROPERTY(QString httpFile READ httpFile WRITE setHttpFile NOTIFY httpFileChanged FINAL)

public:
    explicit HttpClient(QObject *parent = nullptr);
    ~HttpClient();

public slots:
    void getMethod();
    void putMethod();
    void postMethod();
    void deleteMethod();

    void getResponse(QNetworkReply *reply);
    void putResponse(QNetworkReply *reply);
    void postResponse(QNetworkReply *reply);
    void deleteResponse(QNetworkReply *reply);

    // QNetworkReply connections
    void errorOccurred(QNetworkReply::NetworkError code);
    void replyFinished();

    // QNetworkAccessManager connections
    void readyRead();
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);
    void finished(QNetworkReply *reply);
    void preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private: // Members
    QNetworkAccessManager* m_manager = nullptr;
    QString m_url = QString{};
    qint64 m_portNumber = -1;

    QString m_caCertFile = {};
    QString m_clientCertFile = {};
    QString m_clientKeyFile = {};
    QString m_httpMethod = {};
    QString m_httpFile = {};
    QSslConfiguration m_sslconfig;

    bool m_ssl = false;

private: // Functions
    void init();
    void setClientCert();

public:
    void start();
    QNetworkAccessManager *manager() const;
    QString url() const;
    void setUrl(const QString &newUrl);
    qint64 portNumber() const;
    void setPortNumber(qint64 newPortNumber);
    QString caCertFile() const;
    void setCaCertFile(const QString &newCaCertFile);
    QString clientCertFile() const;
    void setClientCertFile(const QString &newClientCertFile);
    QString clientKeyFile() const;
    void setClientKeyFile(const QString &newClientKeyFile);
    QString httpMethod() const;
    void setHttpMethod(const QString &newHttpMethod);
    QString httpFile() const;
    void setHttpFile(const QString &newHttpFile);

signals:
    void managerChanged();
    void urlChanged();
    void portNumberChanged();
    void caCertFileChanged();
    void clientCertFileChanged();
    void clientKeyFileChanged();
    void httpMethodChanged();
    void httpFileChanged();
};

