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
#include <QSslKey>
#include <QMetaEnum>
#include <QRunnable>
#include <QThread>

#include "sslserversignalhandler.hpp"

class SslReceiveSocket : public QObject, public QRunnable
{
    Q_OBJECT
    Q_PROPERTY(QString keyFile READ keyFile WRITE setKeyFile NOTIFY keyFileChanged FINAL)
    Q_PROPERTY(QString certFile READ certFile WRITE setCertFile NOTIFY certFileChanged FINAL)

public:
    explicit SslReceiveSocket(qintptr handle, QObject *parent = nullptr);
    ~SslReceiveSocket();

public:
    void run() override;

    QString keyFile() const;
    void setKeyFile(const QString &newKeyFile);
    QString certFile() const;
    void setCertFile(const QString &newCertFile);

    QSslSocket *socket() const;

signals:
    void keyFileChanged();
    void certFileChanged();

private:
    void init();
    qintptr m_handle;
    QSslSocket* m_socket = nullptr;
    SslServerSignalHandler* m_handler = nullptr;

private:
    QString m_keyFile = {};
    QString m_certFile = {};

};

