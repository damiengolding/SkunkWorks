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
#include "sslclientsignalhandler.hpp"

SslClientSignalHandler::SslClientSignalHandler(QObject *parent)
    : QObject{parent}
{

}

SslClientSignalHandler::~SslClientSignalHandler()
{

}

#pragma Slots {

void SslClientSignalHandler::on_socket_readyRead(){
    qInfo() << "Socket readyRead";
    QSslSocket* socket = qobject_cast<QSslSocket*>( sender() );
    qInfo() << "Connection from address:" << socket->peerAddress().toString();
    qInfo() << "Connection from port:" << socket->peerPort();
    qInfo() << "Connection type:" << socket->socketType();
    qInfo() << "Connection error:" << socket->error();
    qInfo() << "Bytes available to read:" << socket->bytesAvailable();
    qInfo() << "Read from server:" << socket->readAll();
    socket->close();
    socket->deleteLater();
    QCoreApplication::exit(0);
}

void SslClientSignalHandler::on_socket_encryptedBytesWritten(qint64 written)
{
    qInfo() << "Socket encryptedBytesWrite:" << written;
}

void SslClientSignalHandler::on_socket_connected()
{
    qInfo() << "Socket connected";
    QSslSocket* socket = qobject_cast<QSslSocket*>( sender() );
    qInfo() << "Connection from:" << socket->peerName();
    qInfo() << "Connection from address:" << socket->peerAddress();
    qInfo() << "Connection from port:" << socket->peerPort();
    qInfo() << "Connection type:" << socket->socketType();
    qInfo() << "Connection error:" << socket->error();
    qInfo() << "Connection error string:" << socket->errorString();
}

void SslClientSignalHandler::on_socket_modeChanged(QSslSocket::SslMode mode)
{
    qInfo() << "Socket modeChanged:" << mode;
}

void SslClientSignalHandler::on_socket_peerVerifyError(const QSslError &error)
{
    qInfo() << "Socket peerVerifyError:" << error;
}

void SslClientSignalHandler::on_socket_encrypted()
{
    qInfo() << "Socket encrypted";
    QSslSocket* socket = qobject_cast<QSslSocket*>( sender() );
    NetDiagsUtils::certificateAnalysis(socket);
}

void SslClientSignalHandler::on_socket_disconnected()
{
    qInfo() << "Socket disconnected";
}

void SslClientSignalHandler::on_socket_errorOccurred(QAbstractSocket::SocketError socketError)
{
    qInfo() << "Socket errorOccurred:" << socketError;
}

void SslClientSignalHandler::on_socket_hostFound()
{
    qInfo() << "Socket hostFound";
}

void SslClientSignalHandler::on_socket_proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qInfo() << "Socket proxyAuthenticationRequired";
}

void SslClientSignalHandler::on_socket_stateChanged(QAbstractSocket::SocketState socketState)
{
    qInfo() << "Socket state changed:" << socketState;
}

void SslClientSignalHandler::sslErrors(const QList<QSslError> &errors)
{
    QSslSocket* socket = qobject_cast<QSslSocket*>(sender());
    qInfo() << "SslErrors:";
    for( auto error : errors ){
        qInfo() << "\tError:" << error;
    }
    socket->ignoreSslErrors( errors );
}

#pragma Slots }

