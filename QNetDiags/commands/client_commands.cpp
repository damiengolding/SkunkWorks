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

#include <QThreadPool>
#include <QThread>

#include "commands.hpp"
#include "../tcp_client/tcpsendsocket.hpp"
#include "../ssl_client/sslsendsocket.hpp"

void tcp_client( const QString& host, qint64 port, const QString& certFile ){
    if( certFile.isEmpty() ){ // Plain text client
        qInfo() << "TCP plain text client";
        TcpSendSocket* socket = new TcpSendSocket( host, port );
        QThreadPool* pool = QThreadPool::globalInstance();
        pool->start( socket );
        socket->setAutoDelete(true);
    }
    else{
        qInfo() << "TCP SSL client";
        SslSendSocket* socket = new SslSendSocket( host,  port, certFile );
        QThreadPool* pool = QThreadPool::globalInstance();
        pool->start( socket );
        socket->setAutoDelete(true);
    }
}

void http_client( const QString& host, qint64 port, const QString& certFile){
    if( certFile.isEmpty() ){ // Plain text client
        qInfo() << "HTTP plain text client";
    }
    else{
        qInfo() << "HTTP SSL client";
    }
}
