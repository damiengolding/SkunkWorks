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

#include "../utils/modelutils.hpp"

class UmlClassFactory;

/*!
 * \brief The UmlState class
 */
class UmlState
{
public:
    UmlState();
    ~UmlState();
    friend class UmlStateFactory;

    inline bool hasChildren(){
        return( !m_children.empty() ? true : false );
    }

    inline QString getInclude(){
        QString ret = QString("#include \"%1.hpp\"").arg(m_name);
        return(ret);
    }

    QString name() const;
    QStringList transitions() const;
    QString parentState() const;
    QList<UmlState *> children() const;
    bool isParallel() const;
    bool isFinal() const;
    bool isState() const;
    bool useNamespace() const;
    bool isPushdown() const;
    QString stateNamespace() const;
    QString type() const;
    QString variableName() const;

protected:
    QString m_name = {};
    QString m_variableName = {};
    QString m_type = {};
    QStringList m_transitions = {};
    QString m_stateNamespace = {};
    QString m_parentState = {};
    QList<UmlState*> m_children = QList<UmlState*>();

    bool m_isParallel = false;
    bool m_isFinal = false;
    bool m_isState = false;
    bool m_useNamespace = false;
    bool m_isPushdown = false;
};

/*!
 * \brief The UmlStateFactory class
 */
class UmlStateFactory
{
public:
    UmlStateFactory();
    ~UmlStateFactory();
    static UmlState* createState( const QDomElement& fsmElem, const QString& fsmName, const QString& fsmNamespace = QString(), bool useNamespace = false );

};
