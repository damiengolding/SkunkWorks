/*
MIT License

Copyright (c) 2024 Damien Golding

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

Don't use it to find and eat babies ... unless you're really REALLY hungry ;-)
*/

#include "../inc/ConversionUtils.hpp"
using namespace GoldingsGym;

template<typename E>
E ConversionUtils::ConversionUtils::EnumFromString(const QString &textValue)
{
    bool ok;
    auto enumResult = static_cast<E>(QMetaEnum::fromType<E>().keyToValue(textValue,&ok));
    if(!ok){
        qDebug()<<"Could not convert" << textValue << "to enum.";
        return{};
    }
    return(enumResult);
}

template<typename E>
QString ConversionUtils::StringFromEnum(E value)
{
    const int intRepresentation = static_cast<int>(value);
    return( QString::fromUtf8(QMetaEnum::fromType<E>().valueToKey(intRepresentation)) );
}

QList<QDomElement> ConversionUtils::domElementList(const QDomNodeList &list){
    QList<QDomElement> ret;
    for( int i = 0; i<list.count();++i ){
        QDomNode node = list.at(i);
        QDomElement elem = node.toElement();
        ret.append(elem);
    }
    return(ret);
}
