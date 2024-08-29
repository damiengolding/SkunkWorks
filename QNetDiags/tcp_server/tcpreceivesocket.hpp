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
#include <QTcpSocket>
#include <QMetaEnum>
#include <QRunnable>
#include <QThread>

#include "tcpsignalhandler.hpp"

class TcpReceiveSocket : public QObject, public QRunnable
{
    Q_OBJECT
    Q_PROPERTY(qintptr handle READ handle MEMBER m_handle NOTIFY handleChanged FINAL)
    Q_PROPERTY(QTcpSocket *socket READ socket MEMBER m_socket NOTIFY socketChanged FINAL)
    Q_PROPERTY(TcpSignalHandler *handler READ handler MEMBER m_handler NOTIFY handlerChanged FINAL)

public:
    explicit TcpReceiveSocket(qintptr handle, QObject *parent = nullptr);
    ~TcpReceiveSocket();

public:
    void run() override;

    qintptr handle() const;
    QTcpSocket *socket() const;
    TcpSignalHandler *handler() const;

signals:
    void handleChanged();
    void socketChanged();
    void handlerChanged();

private:
    qintptr m_handle;
    QTcpSocket* m_socket = nullptr;
    TcpSignalHandler* m_handler = nullptr;

};

