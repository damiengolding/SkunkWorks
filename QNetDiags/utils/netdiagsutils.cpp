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

#include "netdiagsutils.hpp"

NetDiagsUtils::NetDiagsUtils( QObject* parent) : QObject{parent}{}

template<typename E>
E NetDiagsUtils::EnumFromString(const QString &textValue)
{
    bool ok;
    auto enumResult = static_cast<E>(QMetaEnum::fromType<E>().keyToValue(textValue,&ok));
    if(!ok){
        qDebug()<<"Could not convert " << textValue << " to enum.";
        return{};
    }
    return(enumResult);
}

template<typename E>
QString NetDiagsUtils::StringFromEnum(E value)
{
    const int intRepresentation = static_cast<int>(value);
    return( QString::fromUtf8(QMetaEnum::fromType<E>().valueToKey(intRepresentation)) );
}

QList<QDomElement> NetDiagsUtils::DomElementList(const QDomNodeList &list){
    QList<QDomElement> ret;
    for( int i = 0; i<list.count();++i ){
        QDomNode node = list.at(i);
        QDomElement elem = node.toElement();
        if( elem.isNull() ){
            continue;
        }
        ret.append(elem);
    }
    return(ret);
}

QDomDocument* NetDiagsUtils::VerifiedDomDocument(const QString &fileName)
{
    QFile* file = new QFile(fileName);
    QDomDocument* doc = new QDomDocument("doc");

    if( !file->open(QIODevice::ReadOnly) ){
        qDebug() << "Unable to open"<<fileName<<"for reading";
        return(nullptr);
    }
    if( !doc->setContent(file->readAll())  ){
        qDebug() << "Unable to parse"<<fileName<<"into QDomDocument";
        return(nullptr);
    }
    return(doc);
}

void NetDiagsUtils::certificateAnalysis(QSslSocket *socket)
{
    QSslCertificate cert = socket->peerCertificate();
    QList<QSslCertificate> certChain = socket->peerCertificateChain();
    certificateAnalysis(cert, certChain);
}

void NetDiagsUtils::certificateAnalysis(QSslCertificate certificate, QList<QSslCertificate> certificateChain){
    QSslCertificate cert = certificate;
    if( cert.isNull() ){
        qInfo().noquote() << "The client has not presented a certificate";
        return;
    }
    QList<QSslCertificate> chain = certificateChain;
    qInfo().noquote() << "";
    qInfo().noquote() << "#################### Certificate analysis  ####################";
    qInfo().noquote() << "Certificate chain length:" << chain.count();
    qInfo().noquote() << "Self-signed:" << cert.isSelfSigned();
    qInfo().noquote() << "Valid from:" << cert.effectiveDate().toString();
    qInfo().noquote() << "Valid until:" << cert.expiryDate().toString();
    qInfo().noquote() << "Serial number:" << cert.serialNumber();
    qInfo().noquote() << "Version:" << cert.version();
    qInfo() << "SHA256 digest:" << cert.digest(QCryptographicHash::Sha256);
    qInfo().noquote() << "";
    qInfo().noquote() << "Issuer information:";
    qInfo().noquote() << "\tIssuer display name:" << cert.issuerDisplayName();
    qInfo().noquote() << "\tIssuer Organization (O):" << cert.issuerInfo( QSslCertificate::Organization ).join(" ");
    qInfo().noquote() << "\tIssuer Common Name (CN) :" << cert.issuerInfo( QSslCertificate::CommonName ).join(" ");
    qInfo().noquote() << "\tIssuer Locality (L) :" << cert.issuerInfo( QSslCertificate::LocalityName ).join(" ");
    qInfo().noquote() << "\tIssuer Organizational Unit (OU):" << cert.issuerInfo( QSslCertificate::OrganizationalUnitName ).join(" ");
    qInfo().noquote() << "\tIssuer Country Name (C):" << cert.issuerInfo( QSslCertificate::CountryName ).join(" ");
    qInfo().noquote() << "\tIssuer State/province (ST):" << cert.issuerInfo( QSslCertificate::StateOrProvinceName ).join(" ");
    qInfo().noquote() << "\tIssuer Distinguished Name Qualifier:" << cert.issuerInfo( QSslCertificate::DistinguishedNameQualifier ).join(" ");
    qInfo().noquote() << "\tIssuer Serial Number:" << cert.issuerInfo( QSslCertificate::SerialNumber ).join(" ");
    qInfo().noquote() << "\tIssuer E-Mail Address:" << cert.issuerInfo( QSslCertificate::EmailAddress ).join(" ");
    qInfo().noquote() << "";
    qInfo().noquote() << "Subject information:";
    qInfo().noquote() << "\tSubject display name:" << cert.subjectDisplayName();
    qInfo().noquote() << "\tSubject Organization (O):" << cert.subjectInfo( QSslCertificate::Organization ).join(" ");
    qInfo().noquote() << "\tSubject Common Name (CN) :" << cert.subjectInfo( QSslCertificate::CommonName ).join(" ");
    qInfo().noquote() << "\tSubject Locality (L) :" << cert.subjectInfo( QSslCertificate::LocalityName ).join(" ");
    qInfo().noquote() << "\tSubject Organizational Unit (OU):" << cert.subjectInfo( QSslCertificate::OrganizationalUnitName ).join(" ");
    qInfo().noquote() << "\tSubject Country Name (C):" << cert.subjectInfo( QSslCertificate::CountryName ).join(" ");
    qInfo().noquote() << "\tSubject State/province (ST):" << cert.subjectInfo( QSslCertificate::StateOrProvinceName ).join(" ");
    qInfo().noquote() << "\tSubject Distinguished Name Qualifier:" << cert.subjectInfo( QSslCertificate::DistinguishedNameQualifier ).join(" ");
    qInfo().noquote() << "\tSubject Serial Number:" << cert.subjectInfo( QSslCertificate::SerialNumber ).join(" ");
    qInfo().noquote() << "\tSubject E-Mail Address:" << cert.subjectInfo( QSslCertificate::EmailAddress ).join(" ");
    qInfo().noquote() << "";
    qInfo().noquote() << "Server public key:";
    qInfo().noquote() << "";
    qInfo().noquote() << cert.publicKey().toPem();

    if( cert.extensions().count() > 0 ){
        qInfo().noquote() << "Certificate extensions:";
        for( auto extension : cert.extensions() ){
            qInfo().noquote() << "\tExtension name:" << extension.name();
            qInfo().noquote() << "\t\tCritical:" << extension.isCritical();
            qInfo().noquote() << "\t\tSupported:" << extension.isSupported();
            qInfo().noquote() << "\t\tOID:" << extension.oid();

            QString variantType = extension.value().typeName();
            variantType = variantType.toLower();
            if( variantType == "qbytearray" ){
                qInfo().noquote() << "\t\tValue:" << extension.value().toByteArray();
            }
            else if( variantType == "qstring" ){
                qInfo().noquote() << "\t\tValue:" << extension.value().toString();
            }
            else if( variantType == "bool" ){
                qInfo().noquote() << "\t\tValue:" << extension.value().toBool();
            }
            else if(  variantType == "qvariantmap" ){
                for( auto [name,value] : extension.value().toMap().asKeyValueRange() ){
                    QString nameValue;
                    QString map_name = name;
                    QVariant map_variant = value;
                    QString varType = map_variant.typeName();
                    varType = varType.toLower();
                    if( varType == "qbytearray" ){
                        nameValue += name % "=" % map_variant.toByteArray();
                    }
                    else if( varType == "bool" ){
                        nameValue += name % "=" % QVariant(map_variant.toBool()).toString();
                    }
                    else if( varType == "qstring" ){
                        nameValue += name % "=" % map_variant.toString();
                    }
                    else{
                        nameValue += name % "=" % map_variant.toString();
                    }
                    qInfo().noquote() << "\t\tValue:" << nameValue;
                }
            }
            else{
                qInfo().noquote() << "\t\tValue:" << extension.value();
            }
        }
    }

    if( chain.count() > 0 ){
        qInfo().noquote() << "";
        qInfo().noquote() << "Certificate chain:";
        for( auto cert : chain ){
            qInfo().noquote() << "Certificate name:" << cert.subjectDisplayName();
            qInfo().noquote() << "Public key:";
            qInfo().noquote() << "";
            qInfo().noquote() << cert.publicKey().toPem();
        }
    }
    qInfo().noquote() << "#################### End of certificate analysis  ####################";
    qInfo().noquote() << "";
}

NetDiagsUtils::~NetDiagsUtils(){}

