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

#pragma once

#include <QString>
#include <QMetaEnum>
#include <QDomDocument>
#include <QDomNodeList>
#include <QDomElement>
#include <QList>
#include <QFile>

class FsmUtils : public QObject
{
    Q_OBJECT

public:
    explicit FsmUtils(QObject *parent = nullptr);
    ~FsmUtils();

    // QMetaEnum conversion to string
    template<typename E>
    static E EnumFromString(const QString &textValue);

    // QMetaEnum conversion from string
    template<typename E>
    static QString StringFromEnum(E value);

    // QList of verified QDomElements from QDomNodeList
    static QList<QDomElement> DomElementList(const QDomNodeList &list);

    // Verified populated QDomDocument* from a QString file name
    static QDomDocument* VerifiedDomDocument(const QString& fileName );

private:

signals:

};

