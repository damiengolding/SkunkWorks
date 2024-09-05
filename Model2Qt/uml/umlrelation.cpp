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
#include "umlrelation.hpp"

UmlRelation::UmlRelation(const QString &uid, const QString &fromUid, const QString &toUid, const QString &name)
{
    m_uid = uid;
    m_fromUid = fromUid;
    m_toUid = toUid;
    m_name = name;
}

bool UmlRelation::fromElement(const QDomElement &elem)
{
    bool ret = true;

    /*
        --- UID ---
    */
    QDomElement uidElem = elem.firstChildElement("handle").firstChildElement("uid");
    if( !uidElem.isNull() ){
        m_uid = uidElem.text();
        // qInfo() << "Relation UID:" << m_uid;
    }

    /*
        --- Relation type ---
    */
    QDomElement typeElem = elem.firstChildElement("handle").firstChildElement("target").firstChildElement("instance");
    if( !typeElem.isNull() ){
        QString type = typeElem.attribute("type").toLower();
        // qInfo() << "Relation type:" << type;
        if( type == "minheritance" ){
            m_relationType = Realization;
        }
        else if( type == "mdependency" ){
            m_relationType = Dependency;
        }
        else if( type == "massociation" ){
            QDomElement kindElem = typeElem.firstChildElement("MAssociation")
                    .firstChildElement("a")
                    .firstChildElement("MAssociationEnd")
                    .firstChildElement("kind");
            if( kindElem.isNull() ){
                m_relationType = Association;
            }
            else{
                QString kindString = kindElem.text();
                int kindNum = kindString.toInt();
                switch( kindNum ){
                case 1:{
                    m_relationType = Aggregation;
                    break;
                }
                case 2:{
                    m_relationType = Composition;
                    break;
                }
                default:{
                    m_relationType = Association;
                }
                }
            }
        }
        else{
            m_relationType = Undefined;
        }
    }

    /*
        --- From and to UIDs ---
    */
    if( m_relationType == Association || m_relationType == Aggregation || m_relationType == Composition ){
        QDomElement fromElem = elem.firstChildElement("handle")
                .firstChildElement("target")
                .firstChildElement("instance")
                .firstChildElement("MAssociation")
                .firstChildElement("base-MRelation")
                .firstChildElement("MRelation")
                .firstChildElement("a");
        if( !fromElem.isNull() ){
            m_fromUid = fromElem.text();
        }

        QDomElement toElem = elem.firstChildElement("handle")
                .firstChildElement("target")
                .firstChildElement("instance")
                .firstChildElement("MAssociation")
                .firstChildElement("base-MRelation")
                .firstChildElement("MRelation")
                .firstChildElement("b");
        if( !toElem.isNull() ){
            m_toUid = toElem.text();
        }
    }
    else if( m_relationType == Realization ){
        QDomElement fromElem = elem.firstChildElement("handle")
                .firstChildElement("target")
                .firstChildElement("instance")
                .firstChildElement("MInheritance")
                .firstChildElement("base-MRelation")
                .firstChildElement("MRelation")
                .firstChildElement("a");
        if( !fromElem.isNull() ){
            m_fromUid = fromElem.text();
        }

        QDomElement toElem = elem.firstChildElement("handle")
                .firstChildElement("target")
                .firstChildElement("instance")
                .firstChildElement("MInheritance")
                .firstChildElement("base-MRelation")
                .firstChildElement("MRelation")
                .firstChildElement("b");
        if( !toElem.isNull() ){
            m_toUid = toElem.text();
        }
    }
    else if( m_relationType == Dependency ){
        QDomElement fromElem = elem.firstChildElement("handle")
                .firstChildElement("target")
                .firstChildElement("instance")
                .firstChildElement("MDependency")
                .firstChildElement("base-MRelation")
                .firstChildElement("MRelation")
                .firstChildElement("a");
        if( !fromElem.isNull() ){
            m_fromUid = fromElem.text();
        }

        QDomElement toElem = elem.firstChildElement("handle")
                .firstChildElement("target")
                .firstChildElement("instance")
                .firstChildElement("MDependency")
                .firstChildElement("base-MRelation")
                .firstChildElement("MRelation")
                .firstChildElement("b");
        if( !toElem.isNull() ){
            m_toUid = toElem.text();
        }
    }

    /*
        --- Relation name ---
    */
    if( m_relationType == Association || m_relationType == Aggregation || m_relationType == Composition ){
        QDomElement nameElem = elem.firstChildElement("handle")
                .firstChildElement("target")
                .firstChildElement("instance")
                .firstChildElement("MAssociation")
                .firstChildElement("base-MRelation")
                .firstChildElement("MRelation")
                .firstChildElement("name");
        if( !nameElem.isNull() ){
            m_name = nameElem.text();
        }
    }
    else if( m_relationType == Realization ){
        QDomElement nameElem = elem.firstChildElement("handle")
                .firstChildElement("target")
                .firstChildElement("instance")
                .firstChildElement("MInheritance")
                .firstChildElement("base-MRelation")
                .firstChildElement("MRelation")
                .firstChildElement("name");
        if( !nameElem.isNull() ){
            m_name = nameElem.text();
        }
    }
    else if( m_relationType == Dependency ){
        QDomElement nameElem = elem.firstChildElement("handle")
                .firstChildElement("target")
                .firstChildElement("instance")
                .firstChildElement("MDependency")
                .firstChildElement("base-MRelation")
                .firstChildElement("MRelation")
                .firstChildElement("name");
        if( !nameElem.isNull() ){
            m_name = nameElem.text();
        }
    }
    else{
        m_name = "Anonymous";
    }
    return( ret );
}

UmlRelation::RelationType UmlRelation::relationType() const
{
    return m_relationType;
}

QString UmlRelation::uid() const
{
    return m_uid;
}

QString UmlRelation::fromUid() const
{
    return m_fromUid;
}

QString UmlRelation::toUid() const
{
    return m_toUid;
}

QString UmlRelation::name() const
{
    return m_name;
}

