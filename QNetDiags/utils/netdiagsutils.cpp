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
    if( cert.isNull() ){
        qInfo() << "The client has not presented a certificate";
        return;
    }
    QList<QSslCertificate> chain = socket->peerCertificateChain();
    qInfo() << "";
    qInfo() << "#################### Certificate analysis  ####################";
    qInfo() << "Certificate chain length:" << chain.count();
    qInfo() << "Self-signed:" << cert.isSelfSigned();
    qInfo() << "Valid from:" << cert.effectiveDate().toString();
    qInfo() << "Valid until:" << cert.expiryDate().toString();
    qInfo() << "Serial number:" << cert.serialNumber();
    qInfo() << "Version:" << cert.version();
    qInfo() << "SHA256 digest:" << cert.digest(QCryptographicHash::Sha256);
    qInfo() << "";
    qInfo() << "Issuer information:";
    qInfo() << "\tIssuer display name:" << cert.issuerDisplayName();
    qInfo() << "\tIssuer Organization (O):" << cert.issuerInfo( QSslCertificate::Organization ).join(" ");
    qInfo() << "\tIssuer Common Name (CN) :" << cert.issuerInfo( QSslCertificate::CommonName ).join(" ");
    qInfo() << "\tIssuer Locality (L) :" << cert.issuerInfo( QSslCertificate::LocalityName ).join(" ");
    qInfo() << "\tIssuer Organizational Unit (OU):" << cert.issuerInfo( QSslCertificate::OrganizationalUnitName ).join(" ");
    qInfo() << "\tIssuer Country Name (C):" << cert.issuerInfo( QSslCertificate::CountryName ).join(" ");
    qInfo() << "\tIssuer State/province (ST):" << cert.issuerInfo( QSslCertificate::StateOrProvinceName ).join(" ");
    qInfo() << "\tIssuer Distinguished Name Qualifier:" << cert.issuerInfo( QSslCertificate::DistinguishedNameQualifier ).join(" ");
    qInfo() << "\tIssuer Serial Number:" << cert.issuerInfo( QSslCertificate::SerialNumber ).join(" ");
    qInfo() << "\tIssuer E-Mail Address:" << cert.issuerInfo( QSslCertificate::EmailAddress ).join(" ");
    qInfo() << "";
    qInfo() << "Subject information:";
    qInfo() << "\tSubject display name:" << cert.subjectDisplayName();
    qInfo() << "\tSubject Organization (O):" << cert.subjectInfo( QSslCertificate::Organization ).join(" ");
    qInfo() << "\tSubject Common Name (CN) :" << cert.subjectInfo( QSslCertificate::CommonName ).join(" ");
    qInfo() << "\tSubject Locality (L) :" << cert.subjectInfo( QSslCertificate::LocalityName ).join(" ");
    qInfo() << "\tSubject Organizational Unit (OU):" << cert.subjectInfo( QSslCertificate::OrganizationalUnitName ).join(" ");
    qInfo() << "\tSubject Country Name (C):" << cert.subjectInfo( QSslCertificate::CountryName ).join(" ");
    qInfo() << "\tSubject State/province (ST):" << cert.subjectInfo( QSslCertificate::StateOrProvinceName ).join(" ");
    qInfo() << "\tSubject Distinguished Name Qualifier:" << cert.subjectInfo( QSslCertificate::DistinguishedNameQualifier ).join(" ");
    qInfo() << "\tSubject Serial Number:" << cert.subjectInfo( QSslCertificate::SerialNumber ).join(" ");
    qInfo() << "\tSubject E-Mail Address:" << cert.subjectInfo( QSslCertificate::EmailAddress ).join(" ");
    qInfo() << "";
    qInfo() << "Server public key:";
    qInfo() << "";
    qInfo().noquote() << cert.publicKey().toPem();

    if( cert.extensions().count() > 0 ){
        qInfo() << "Certificate extensions:";
        for( auto extension : cert.extensions() ){
            qInfo() << "\tExtension name:" << extension.name();
            qInfo() << "\t\tCritical:" << extension.isCritical();
            qInfo() << "\t\tSupported:" << extension.isSupported();
            qInfo() << "\t\tOID:" << extension.oid();

            QString variantType = extension.value().typeName();
            variantType = variantType.toLower();
            // qInfo() << "Variant type:"<<variantType;
            if( variantType == "qbytearray" ){
                qInfo() << "\t\tValue:" << extension.value().toByteArray();
            }
            else if( variantType == "qstring" ){
                qInfo() << "\t\tValue:" << extension.value().toString();
            }
            else if( variantType == "bool" ){
                qInfo() << "\t\tValue:" << extension.value().toBool();
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
                qInfo() << "\t\tValue:" << extension.value();
            }
        }
    }

    if( chain.count() > 0 ){
        qInfo() << "";
        qInfo() << "Certificate chain:";
        for( auto cert : chain ){
            qInfo() << "Certificate name:" << cert.subjectDisplayName();
            qInfo() << "Public key:";
            qInfo() << "";
            qInfo().noquote() << cert.publicKey().toPem();
        }
    }
    qInfo() << "#################### End of certificate analysis  ####################";
    qInfo() << "";
}

NetDiagsUtils::~NetDiagsUtils(){}

