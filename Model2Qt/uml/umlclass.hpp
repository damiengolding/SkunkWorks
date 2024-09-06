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
#include <QString>
#include <QDebug>
#include <QMetaEnum>

#include <QDomDocument>
#include <QDomNodeList>
#include <QDomElement>
#include <QList>
#include <QDir>
#include <QFile>
#include <QFileInfo>

#include "modelutils.hpp"

class UmlClassFactory;

/*!
 * \brief The UmlClass class
 */
class UmlClass
{
public:
    UmlClass();
    ~UmlClass();
    friend class UmlClassFactory;
    QString toDeclaration( bool useNamespaces = false );
    QString toDefinition( bool useNamespaces = false );

    bool isNull() const;
    QString className() const;
    bool isInterface() const;

    bool isClass() const;
    bool isControl() const;
    bool isBoundary() const;
    bool isEntity() const;

    QString classUid() const;

    inline void addInclude( const QString& header ){
        m_additional_includes << header;
    }
    inline void addBaseClass( const QString& className ){
        m_base_class = className;
    }
    inline void addMemberDeclaration( const QString& memberDeclaration ){
        m_private_members << memberDeclaration;
    }

protected:
    QString m_namespace = {};
    QString m_class_name = {};
    QString m_class_uid = {};
    QString m_base_class = {};
    QStringList m_namespaces;
    QStringList m_additional_includes;
    QStringList m_public_functions;
    QStringList m_private_functions;
    QStringList m_protected_functions;
    QStringList m_public_members;
    QStringList m_private_members;
    QStringList m_protected_members;

    bool m_isNull = false;
    bool m_isClass = false;
    bool m_isInterface = false;
    bool m_isControl = false;
    bool m_isBoundary = false;
    bool m_isEntity = false;
};
/*!
 * \brief The UmlClassFactory class
 */
class UmlClassFactory
{
public:
    UmlClassFactory() {}
    static UmlClass* createClass( const QDomElement& elem, QStringList namespaces = QStringList(), QStringList includes = QStringList() );
};

