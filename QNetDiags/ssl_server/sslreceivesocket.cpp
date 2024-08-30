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
#include "sslreceivesocket.hpp"

SslReceiveSocket::SslReceiveSocket(qintptr handle, QObject *parent)
    : QObject{parent}
{
    m_handle = handle;
}

SslReceiveSocket::~SslReceiveSocket()
{

}

void SslReceiveSocket::certificateAnalysis(QSslSocket *socket)
{
    QSslCertificate cert = socket->peerCertificate();
    QList<QSslCertificate> chain = socket->peerCertificateChain();
    qInfo() << "";
    qInfo() << "#################### Certificate analysis  ####################";
    qInfo() << "Certificate chain length:" << chain.count();
    qInfo() << "Self-signed:" << cert.isSelfSigned();
    qInfo() << "Valid from:" << cert.effectiveDate().toString();
    qInfo() << "Valid until:" << cert.expiryDate().toString();

    qInfo() << "Issuer information:";
    qInfo() << "\tIssuer display name:" << cert.issuerDisplayName();
    qInfo() << "\tIssuer Organization (O):" << cert.issuerInfo( QSslCertificate::Organization );
    qInfo() << "\tIssuer Common Name (CN) :" << cert.issuerInfo( QSslCertificate::CommonName );
    qInfo() << "\tIssuer Locality (L) :" << cert.issuerInfo( QSslCertificate::LocalityName );
    qInfo() << "\tIssuer Organizational Unit (OU):" << cert.issuerInfo( QSslCertificate::OrganizationalUnitName );
    qInfo() << "\tIssuer Country Name (C):" << cert.issuerInfo( QSslCertificate::CountryName );
    qInfo() << "\tIssuer State/province (ST):" << cert.issuerInfo( QSslCertificate::StateOrProvinceName );
    qInfo() << "\tIssuer Distinguished Name Qualifier:" << cert.issuerInfo( QSslCertificate::DistinguishedNameQualifier );
    qInfo() << "\tIssuer Serial Number:" << cert.issuerInfo( QSslCertificate::SerialNumber );
    qInfo() << "\tIssuer E-Mail Address:" << cert.issuerInfo( QSslCertificate::EmailAddress );

    qInfo() << "Subject information:";
    qInfo() << "\tSubject display name:" << cert.subjectDisplayName();
    qInfo() << "\tSubject Organization (O):" << cert.subjectInfo( QSslCertificate::Organization );
    qInfo() << "\tSubject Common Name (CN) :" << cert.subjectInfo( QSslCertificate::CommonName );
    qInfo() << "\tSubject Locality (L) :" << cert.subjectInfo( QSslCertificate::LocalityName );
    qInfo() << "\tSubject Organizational Unit (OU):" << cert.subjectInfo( QSslCertificate::OrganizationalUnitName );
    qInfo() << "\tSubject Country Name (C):" << cert.subjectInfo( QSslCertificate::CountryName );
    qInfo() << "\tSubject State/province (ST):" << cert.subjectInfo( QSslCertificate::StateOrProvinceName );
    qInfo() << "\tSubject Distinguished Name Qualifier:" << cert.subjectInfo( QSslCertificate::DistinguishedNameQualifier );
    qInfo() << "\tSubject Serial Number:" << cert.subjectInfo( QSslCertificate::SerialNumber );
    qInfo() << "\tSubject E-Mail Address:" << cert.subjectInfo( QSslCertificate::EmailAddress );

    qInfo() << "Server public key:";
    qInfo().noquote() << cert.publicKey().toPem();

    if( cert.extensions().count() > 0 ){
        qInfo() << "Certificate extensions:";
        for( auto extension : cert.extensions() ){
            qInfo() << "\tExtension name:";
            qInfo() << "\t\tCritical:" << extension.isCritical();
            qInfo() << "\t\tSupported:" << extension.isSupported();
            qInfo() << "\t\tOID:" << extension.oid();
            qInfo() << "\t\tValue:" << extension.value();
        }
    }

    if( chain.count() > 0 ){
        qInfo() << "Certificate chain:";
        for( auto cert : chain ){
            qInfo() << "Certificate name:" << cert.subjectDisplayName();
            qInfo() << "Public key:";
            qInfo().noquote() << cert.publicKey().toPem();
        }
        qInfo() << "";
    }
    qInfo() << "#################### End of certificate analysis  ####################";
    qInfo() << "";
}

void SslReceiveSocket::run()
{
    qInfo() << "Running SslReceiveSocket in thread" << QThread::currentThread();
    m_handler = new SslServerSignalHandler();
    m_socket = new QSslSocket(m_handler);
    m_socket->setSocketOption( QAbstractSocket::KeepAliveOption, true );
    m_socket->setObjectName("socket");
    if( !m_socket->setSocketDescriptor( m_handle ) ){
        qCritical() << "m_socket/m_handle is invalid";
        return;
    }
    init();
    m_socket->startServerEncryption();
    m_socket->waitForReadyRead();
}

void SslReceiveSocket::init(){
    /*
        --- Certificate and key ---
    */
    QByteArray keyBytes;
    QByteArray certBytes;

    QFile keyFile(m_keyFile);
    if(keyFile.open(QIODevice::ReadOnly)) {
        keyBytes = keyFile.readAll();
        keyFile.close();
    }
    else{
        qDebug() << "Error with key file:"  << m_keyFile << keyFile.errorString();
    }

    QFile certFile(m_certFile);
    if(certFile.open(QIODevice::ReadOnly)){
        certBytes = certFile.readAll();
        certFile.close();
    }
    else{
        qDebug() << "Error with certificate file:"  << m_certFile << certFile.errorString();
    }

    QSslKey sslKey(keyBytes, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey);
    QSslCertificate sslCert(certBytes);

    m_socket->setPrivateKey( sslKey );
    m_socket->setLocalCertificate( sslCert );
    // m_socket->setPeerVerifyMode(QSslSocket::VerifyPeer );

    // TODO - is this necessary/useful?
    m_socket->setSocketOption( QAbstractSocket::KeepAliveOption, true );

    /*
        --- Connections ---
    */
    QMetaObject::connectSlotsByName(m_handler);
    // The one that dares to be different
    connect(m_socket, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors), m_handler, &SslServerSignalHandler::sslErrors);
}

QSslSocket *SslReceiveSocket::socket() const
{
    return m_socket;
}

#pragma  {

QString SslReceiveSocket::keyFile() const
{
    return m_keyFile;
}

void SslReceiveSocket::setKeyFile(const QString &newKeyFile)
{
    if (m_keyFile == newKeyFile)
        return;
    m_keyFile = newKeyFile;
    emit keyFileChanged();
}

QString SslReceiveSocket::certFile() const
{
    return m_certFile;
}

void SslReceiveSocket::setCertFile(const QString &newCertFile)
{
    if (m_certFile == newCertFile)
        return;
    m_certFile = newCertFile;
    emit certFileChanged();
}
#pragma Internal slots }
