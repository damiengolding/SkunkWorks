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
#include "tcpreceivesocket.hpp"

TcpReceiveSocket::TcpReceiveSocket(qintptr handle, QObject *parent)
    : QObject{parent}
{
    m_handle = handle;
}

TcpReceiveSocket::~TcpReceiveSocket()
{

}


void TcpReceiveSocket::run()
{
    qInfo() << "Running ReceiveSocket in thread" << QThread::currentThread();
    m_handler = new TcpSignalHandler();
    m_socket = new QTcpSocket(m_handler);
    m_socket->setSocketOption( QAbstractSocket::KeepAliveOption, true );
    m_socket->setObjectName("socket");
    QMetaObject::connectSlotsByName(m_handler);
    if( !m_socket->setSocketDescriptor( m_handle ) ){
        qCritical() << "m_socket/m_handle is invalid";
        return;
    }
    m_socket->waitForReadyRead();
}

qintptr TcpReceiveSocket::handle() const
{
    return m_handle;
}

QTcpSocket *TcpReceiveSocket::socket() const
{
    return m_socket;
}

TcpSignalHandler *TcpReceiveSocket::handler() const
{
    return m_handler;
}
