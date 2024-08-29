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

#include "commands.hpp"

#include <QFile>
#include "tcp_server/tcpserver.hpp"

void server( qint64 port, const QString& certFile, const QString& keyFile ){
    if( certFile.isEmpty() || keyFile.isEmpty() ){ // Plain text TCP server
        TcpServer* server = new TcpServer();
        server->start( port );
    }
    else{ // SSL server

    }
}

#pragma Sanity checks {

    /*
        --- Cert and key ---
    */
// qInfo() << "Certificate file:" << certFile;
// qInfo() << "Private key file:" << keyFile;
// qInfo() << "Testing whether the files were closed correctly";

// QFile cert( certFile );
// QFile key( keyFile );

// if( !cert.open(QIODevice::ReadOnly) ){
//     qInfo() << "Couldn't open the cert file";
// }
// else{
//     qInfo() << "Opened the cert file";
// }
// cert.close();

// if( !key.open(QIODevice::ReadOnly) ){
//     qInfo() << "Couldn't open the key file";
// }
// else{
//     qInfo() << "Opened the key file";
// }
// key.close();

#pragma Sanity checks }

