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
#include "tcpsignalhandler.hpp"

TcpSignalHandler::TcpSignalHandler(QObject *parent)
    : QObject{parent}
{

}

TcpSignalHandler::~TcpSignalHandler()
{

}

#pragma Slots {

void TcpSignalHandler::on_socket_readyRead(){
    qInfo() << "Socket readyRead";
    QTcpSocket* socket = qobject_cast<QTcpSocket*>( sender() );
    qInfo() << "Connection from:" << socket->peerName();
    qInfo() << "Connection from address:" << socket->peerAddress();
    qInfo() << "Connection from port:" << socket->peerPort();
    qInfo() << "Connection type:" << socket->socketType();
    qInfo() << "Connection error:" << socket->error();
    qInfo() << "Connection error string:" << socket->errorString();
    qInfo() << "";
    qInfo() << "Read from client:\r\n\r\n" << socket->readAll();
    QByteArray response = "Hello client";
    socket->write(response);
    socket->waitForBytesWritten();
    socket->close();
    socket->deleteLater();
}

void TcpSignalHandler::on_socket_connected()
{
    qInfo() << "Socket connected";
    QTcpSocket* socket = qobject_cast<QTcpSocket*>( sender() );
    qInfo() << "Connection from:" << socket->peerName();
    qInfo() << "Connection from address:" << socket->peerAddress();
    qInfo() << "Connection from port:" << socket->peerPort();
    qInfo() << "Connection type:" << socket->socketType();
    qInfo() << "Connection error:" << socket->error();
    qInfo() << "Connection error string:" << socket->errorString();
}

void TcpSignalHandler::on_socket_disconnected()
{
    qInfo() << "Socket disconnected";
}

void TcpSignalHandler::on_socket_errorOccurred(QAbstractSocket::SocketError socketError)
{
    qInfo() << "Socket errorOccurred";
}

void TcpSignalHandler::on_socket_hostFound()
{
    qInfo() << "Socket hostFound";
}

void TcpSignalHandler::on_socket_proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qInfo() << "Socket proxyAuthenticationRequired";
}

void TcpSignalHandler::on_socket_stateChanged(QAbstractSocket::SocketState socketState)
{
    qInfo() << "Socket state changed:" << socketState;
}

#pragma Slots }
