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

#include "../inc/hostreconutils.hpp"

HostReconUtils::HostReconUtils( QObject* parent) : QObject{parent}{}


template<typename E>
E HostReconUtils::EnumFromString(const QString &textValue)
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
QString HostReconUtils::StringFromEnum(E value)
{
    const int intRepresentation = static_cast<int>(value);
    return( QString::fromUtf8(QMetaEnum::fromType<E>().valueToKey(intRepresentation)) );
}

QList<QDomElement> HostReconUtils::DomElementList(const QDomNodeList &list){
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

QDomDocument* HostReconUtils::VerifiedDomDocument(const QString &fileName)
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

QString HostReconUtils::IpAddressToNicName( const QString& host ){
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for( auto address : addresses ){
        QString ipAddress = address.toString();
        if( ipAddress != host ) continue;
        QString nicName;
        QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
        for( auto interface : interfaces ){
            QList<QNetworkAddressEntry> networkEntries = interface.addressEntries();
            for( auto networkEntry : networkEntries ){
                QString addr = networkEntry.ip().toString();
                if( addr == ipAddress ){
                    return( interface.name() );
                }
            }
        }
    }
    return( QString() );
}

HostReconUtils::~HostReconUtils(){}
