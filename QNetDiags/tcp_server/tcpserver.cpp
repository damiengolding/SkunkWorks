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
#include "tcpserver.hpp"

TcpServer::TcpServer(QObject *parent)
    : QTcpServer{parent}
{
    connect(this, &QTcpServer::acceptError, this, &TcpServer::acceptError);
    connect(this, &QTcpServer::newConnection, this, &TcpServer::newConnection);
    connect(this, &QTcpServer::pendingConnectionAvailable, this, &TcpServer::pendingConnectionAvailable );
}

TcpServer::~TcpServer()
{

}

void TcpServer::start(qint64 port)
{
    if( this->listen(QHostAddress::Any, port) )
        qInfo() << "Starting server on port" << port << "in thread:" << QThread::currentThread();
    else
        qFatal() << "Unable to listen on port:" << port;
}

void TcpServer::stop()
{
    qInfo() << "Stopping server";
    this->close();
}

void TcpServer::acceptError(QAbstractSocket::SocketError socketError)
{
    qInfo() << "TcpServer::acceptError";
}

void TcpServer::newConnection()
{
    qInfo() << "New connection";
}

void TcpServer::pendingConnectionAvailable()
{
    qInfo() << "Pending connection available";
}

void TcpServer::incomingConnection(qintptr handle)
{
    qInfo() << "Incoming connection in thread:" << QThread::currentThread();
    TcpReceiveSocket* receiveSocket = new TcpReceiveSocket( handle );

    QThreadPool* pool = QThreadPool::globalInstance();
    pool->start(receiveSocket);
    receiveSocket->setAutoDelete(true);
    addPendingConnection( receiveSocket->socket() );
}
