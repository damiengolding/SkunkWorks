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
#include "tcpclientsignalhandler.hpp"

TcpClientSignalHandler::TcpClientSignalHandler(QObject *parent)
    : QObject{parent}
{

}

TcpClientSignalHandler::~TcpClientSignalHandler()
{

}

#pragma Slots {

void TcpClientSignalHandler::on_socket_connected()
{
    qInfo() << "Socket connected";
    QTcpSocket* socket = qobject_cast<QTcpSocket*>( sender() );
    qInfo() << "Connection to address:" << socket->peerAddress().toString();
    qInfo() << "Connection to port:" << socket->peerPort();
    qInfo() << "Connection type:" << socket->socketType();
    qInfo() << "Connection error:" << socket->error();
}

void TcpClientSignalHandler::on_socket_bytesWritten( qint64 bytes ){
    qInfo() << "Bytes written:" << bytes;
}

void TcpClientSignalHandler::on_socket_readyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>( sender() );
    qInfo() << "Read from server:";
    qInfo() << socket->readAll();
    socket->close();
    socket->deleteLater();
    QCoreApplication::exit(0);
}

void TcpClientSignalHandler::on_socket_disconnected()
{
    qInfo() << "Disconnected";
    QTcpSocket* socket = qobject_cast<QTcpSocket*>( sender() );
    socket->deleteLater();
}

void TcpClientSignalHandler::on_socket_errorOccurred(QAbstractSocket::SocketError socketError)
{
    // QTcpSocket* socket = qobject_cast<QTcpSocket*>( sender() );
    qInfo() << "Error occurred:" << socketError;
}

void TcpClientSignalHandler::on_socket_hostFound()
{
    qInfo() << "Host found";
}

void TcpClientSignalHandler::on_socket_proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qInfo() << "Proxy authentication required";
}

void TcpClientSignalHandler::on_socket_stateChanged(QAbstractSocket::SocketState socketState)
{
    qInfo() << "State changed:" << socketState;
}

#pragma Slots }
