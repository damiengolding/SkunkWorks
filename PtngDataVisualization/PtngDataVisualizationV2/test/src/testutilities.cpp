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

#include "../inc/testutilities.hpp"

TestUtilities::TestUtilities( QObject* parent) : QObject{parent}{}


template<typename E>
E TestUtilities::EnumFromString(const QString &textValue)
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
QString TestUtilities::StringFromEnum(E value)
{
    const int intRepresentation = static_cast<int>(value);
    return( QString::fromUtf8(QMetaEnum::fromType<E>().valueToKey(intRepresentation)) );
}

QList<QDomElement> TestUtilities::DomElementList(const QDomNodeList &list){
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

QDomDocument* TestUtilities::VerifiedDomDocument(const QString &fileName)
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

TestUtilities::~TestUtilities(){}
