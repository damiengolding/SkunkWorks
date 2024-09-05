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
#include "umlclass.hpp"

UmlClass::UmlClass()
{

}

UmlClass::~UmlClass()
{

}

/*
    --- String expansions ---
    All:
        %{START_NAMESPACE}
        %{END_NAMESPACE}
    Header:
        %{ADDITIONAL_INCLUDES}
        %{BASE_CLASS}
        %{CLASS_NAME}
        %{MEMBERS}
    Impl:
        %{CLASS_HDR}
        %{CLASS_NAME}
    Interface:
        %{CLASS_NAME}
        %{MEMBERS}
*/

QString UmlClass::toDeclaration(bool useNamespaces)
{
    QString ret;
    if( m_isInterface ){
        QFile file( ":/templates/class/interface_hdr.txt" );
        file.open(QIODevice::ReadOnly);
        ret = file.readAll();
        file.close();

        // All the obvious stuff
        ret.replace("%{CLASS_NAME}", m_class_name);

        // Additional includes
        QString includes;
        if( !m_additional_includes.empty() ){
            includes = m_additional_includes.join("\n");
        }
        ret.replace("%{ADDITIONAL_INCLUDES}", includes);

        // Namespace
        if( useNamespaces ){
            if( !m_namespace.isEmpty() ){
                QString startNamespace = QString( "namespace %1 {" ).arg(m_namespace);
                QString endNamespace = QString( "} // End of namespace %1" ).arg(m_namespace);
                ret.replace("%{START_NAMESPACE}", startNamespace);
                ret.replace("%{END_NAMESPACE}",endNamespace);
            }
            else{
                ret.replace("%{START_NAMESPACE}", "");
                ret.replace("%{END_NAMESPACE}","");
            }
        }
        else{
            ret.replace("%{START_NAMESPACE}", "");
            ret.replace("%{END_NAMESPACE}","");
        }

        // Members - all are public and all are pure virtual
        QStringList members;
        for( auto member: m_public_functions ){
            QString newMember = member;
            QString simplifiedMember = member.remove(" ");
            if( !member.startsWith("virtual") ){
                newMember = newMember.prepend("virtual ");
            }
            if( !simplifiedMember.endsWith("=0;") ){
                newMember = newMember.removeLast();
                newMember = newMember.append(" = 0;");
            }
            members << newMember;
        }
        for( auto member: m_private_functions ){
            QString newMember = member;
            QString simplifiedMember = member.remove(" ");
            if( !member.startsWith("virtual") ){
                newMember = newMember.prepend("virtual ");
            }
            if( !simplifiedMember.endsWith("=0;") ){
                newMember = newMember.removeLast();
                newMember = newMember.append(" = 0;");
            }
            members << newMember;
        }
        for( auto member: m_protected_functions ){
            QString newMember = member;
            QString simplifiedMember = member.remove(" ");
            if( !member.startsWith("virtual") ){
                newMember = newMember.prepend("virtual ");
            }
            if( !simplifiedMember.endsWith("=0;") ){
                newMember = newMember.removeLast();
                newMember = newMember.append(" = 0;");
            }
            members << newMember;
        }

        QString allMembers = members.join("\n\t");
        ret.replace("%{MEMBERS}", allMembers);

    }
    else{
        QFile file( ":/templates/class/class_hdr.txt" );
        file.open(QIODevice::ReadOnly);
        ret = file.readAll();
        file.close();

        // All the obvious stuff
        ret.replace("%{CLASS_NAME}", m_class_name);
        if( m_base_class.isEmpty() ){
            ret.remove("%{BASE_CLASS}");
        }
        else{
            QString baseClass = QString( ", public %1" ).arg( m_base_class );
            ret.replace("%{BASE_CLASS}", baseClass);
        }

        // Additional includes
        QString includes;
        if( !m_additional_includes.empty() ){
            includes = m_additional_includes.join("\n");
        }
        ret.replace("%{ADDITIONAL_INCLUDES}", includes);

        // Namespace
        if( useNamespaces ){
            if( !m_namespace.isEmpty() ){
                QString startNamespace = QString( "namespace %1 {" ).arg(m_namespace);
                QString endNamespace = QString( "} // End of namespace %1" ).arg(m_namespace);
                ret.replace("%{START_NAMESPACE}", startNamespace);
                ret.replace("%{END_NAMESPACE}",endNamespace);
            }
            else{
                ret.replace("%{START_NAMESPACE}", "");
                ret.replace("%{END_NAMESPACE}","");
            }
        }
        else{
            ret.replace("%{START_NAMESPACE}", "");
            ret.replace("%{END_NAMESPACE}","");
        }

        // Members
        QString allPublic= "\npublic:";
        QString allPrivate= "\nprivate:";
        QString allProtected= "\nprotected:";

        if( !m_public_members.empty() ){
            allPublic += "\n\t";
            allPublic += m_public_members.join("\n\t");
        }
        if( !m_public_functions.empty() ){
            allPublic += "\n\t";
            allPublic += m_public_functions.join("\n\t");
        }

        if( !m_private_members.empty() ){
            allPrivate += "\n\t";
            allPrivate += m_private_members.join("\n\t");
        }
        if( !m_private_functions.empty() ){
            allPrivate += "\n\t";
            allPrivate += m_private_functions.join("\n\t");
        }

        if( !m_protected_members.empty() ){
            allProtected += "\n\t";
            allProtected += m_protected_members.join("\n\t");
        }
        if( !m_protected_functions.empty() ){
            allProtected += "\n\t";
            allProtected += m_protected_functions.join("\n\t");
        }

        QString members;
        if( allPublic != "\npublic:" ){
            members += allPublic;
        }
        if( allPrivate != "\nprivate:" ){
            members += allPrivate;
        }
        if( allProtected != "\nprotected:" ){
            members += allProtected;
        }

        ret.replace("%{MEMBERS}", members);
    }

    return(ret);
}

QString UmlClass::toDefinition(bool useNamespaces)
{
    QString ret;
    if( m_isInterface ){
        return(ret);
    }
    else{
        QFile file( ":/templates/class/class_impl.txt" );
        file.open(QIODevice::ReadOnly);
        ret = file.readAll();
        file.close();

        // All the obvious stuff
        ret.replace("%{CLASS_NAME}", m_class_name);
        QString header = m_class_name.toLower();
        ret.replace("%{CLASS_HDR}", m_class_name.toLower());

        // Namespace
        if( useNamespaces ){
            if( !m_namespace.isEmpty() ){
                QString startNamespace = QString( "using namespace %1 {" ).arg(m_namespace);
                QString endNamespace = QString( "} // End of namespace %1" ).arg(m_namespace);
                ret.replace("%{START_NAMESPACE}", startNamespace);
                ret.replace("%{END_NAMESPACE}",endNamespace);
            }
            else{
                ret.replace("%{START_NAMESPACE}", "");
                ret.replace("%{END_NAMESPACE}","");
            }
        }
        else{
            ret.replace("%{START_NAMESPACE}", "");
            ret.replace("%{END_NAMESPACE}","");
        }
    }

    return(ret);
}

#pragma Accessors and mutators {

bool UmlClass::isNull() const
{
    return m_isNull;
}

QString UmlClass::className() const
{
    return m_class_name;
}

bool UmlClass::isInterface() const
{
    return m_isInterface;
}

bool UmlClass::isClass() const
{
    return m_isClass;
}

bool UmlClass::isControl() const
{
    return m_isControl;
}

bool UmlClass::isBoundary() const
{
    return m_isBoundary;
}

bool UmlClass::isEntity() const
{
    return m_isEntity;
}

QString UmlClass::classUid() const
{
    return m_class_uid;
}
#pragma Accessors and mutators }

/*
    --- UmlClassFactory ---
*/
UmlClass* UmlClassFactory::createClass(const QDomElement &elem, QStringList namespaces, QStringList includes)
{
    UmlClass* umlClass(new UmlClass());

    /*
        --- Do all the basic stuff . . . ---
    */
    umlClass->m_namespaces = namespaces;
    umlClass->m_additional_includes = includes;
    if( !namespaces.empty() ){
        umlClass->m_namespace = namespaces.first().replace("-", "::");
    }

    QDomElement nameElem = elem.firstChildElement("base-MObject")
            .firstChildElement("MObject")
            .firstChildElement("name").toElement();
    if( nameElem.isNull() ){
        qInfo() << "Name element is null";
        umlClass->m_isNull = true;
        return( umlClass);
    }
    umlClass->m_class_name = nameElem.text();

    QDomElement uidElem = elem.firstChildElement("base-MObject")
            .firstChildElement("MObject")
            .firstChildElement("base-MElement")
            .firstChildElement("MElement")
            .firstChildElement("uid");
    if( uidElem.isNull() ){
        qInfo() << "UID element is null";
        umlClass->m_isNull = true;
        return( umlClass);
    }
    // qInfo() << "Class UID:"<<uidElem.text();
    umlClass->m_class_uid = uidElem.text();

    /*
        --- What type is it ---
    */
    QDomElement stereotypeElem = elem.firstChildElement("base-MObject")
            .firstChildElement("MObject")
            .firstChildElement("base-MElement")
            .firstChildElement("MElement")
            .firstChildElement("stereotypes")
            .firstChildElement("qlist")
            .firstChildElement("item");
    if( stereotypeElem.isNull() ){ // It's a class
        umlClass->m_isClass = true;
        umlClass->m_isInterface = false;
        umlClass->m_isControl = false;
        umlClass->m_isBoundary = false;
        umlClass->m_isEntity = false;
    }
    else{
        if( stereotypeElem.text() == "interface" ){
            umlClass->m_isClass = false;
            umlClass->m_isInterface = true;
            umlClass->m_isControl = false;
            umlClass->m_isBoundary = false;
            umlClass->m_isEntity = false;
        }
        else if( stereotypeElem.text() == "control" ){
            umlClass->m_isClass = false;
            umlClass->m_isInterface = false;
            umlClass->m_isControl = true;
            umlClass->m_isBoundary = false;
            umlClass->m_isEntity = false;
        }
        else if( stereotypeElem.text() == "entity" ){
            umlClass->m_isClass = false;
            umlClass->m_isInterface = false;
            umlClass->m_isControl = false;
            umlClass->m_isBoundary = false;
            umlClass->m_isEntity = true;
        }
        else if( stereotypeElem.text() == "boundary" ){
            umlClass->m_isClass = false;
            umlClass->m_isInterface = false;
            umlClass->m_isControl = false;
            umlClass->m_isBoundary = true;
            umlClass->m_isEntity = false;
        }
    }

    /*
        --- Members ---
    */
    QDomElement membersElem = elem.firstChildElement("members").firstChildElement("qlist");
    if( !membersElem.isNull() ) {
        QList<QDomElement> members = ModelUtils::DomElementList( membersElem.elementsByTagName("item") );
        for( auto member : members ){
            QDomElement memberElem = member.firstChildElement("MClassMember").toElement();
            if( memberElem.isNull() ){
                continue;
            }
            int type = memberElem.firstChildElement("type").text().toInt();
            QString declaration = memberElem.firstChildElement("declaration").text();
            if( declaration.startsWith("+") ){ // Public
                declaration.removeAt(0);
                if( !declaration.endsWith(";") ){
                    declaration.append(";");
                }
                if( type == 1 ){ // Member
                    umlClass->m_public_members.append(declaration);
                }
                else if( type == 2 ){ // Function
                    umlClass->m_public_functions.append(declaration);
                }
                else{ // Ignore?
                    qInfo() << "\tUnclassified declaration:" << declaration << "is of unknown type:" << type;
                }
            }
            else if( declaration.startsWith("-") ){ // Private
                declaration.removeAt(0);
                if( !declaration.endsWith(";") ){
                    declaration.append(";");
                }
                if( type == 1 ){ // Member
                    umlClass->m_private_members.append(declaration);
                }
                else if( type == 2 ){ // Function
                    umlClass->m_private_functions.append(declaration);
                }
                else{ // Ignore?
                    qInfo() << "Unclassified declaration:" << declaration << "is of unknown type:" << type;
                }
            }
            else if( declaration.startsWith("#") ){ // Protected
                declaration.removeAt(0);
                if( !declaration.endsWith(";") ){
                    declaration.append(";");
                }
                if( type == 1 ){ // Member
                    umlClass->m_protected_members.append(declaration);
                }
                else if( type == 2 ){ // Function
                    umlClass->m_protected_functions.append(declaration);
                }
                else{ // Ignore?
                    qInfo() << "\tUnclassified declaration:" << declaration << "is of unknown type:" << type;
                }
            }
            else{ //  Gotta do something , C++ is private by default . . .
                declaration.removeAt(0);
                if( !declaration.endsWith(";") ){
                    declaration.append(";");
                }
                if( type == 1 ){ // Member
                    umlClass->m_private_members.append(declaration);
                }
                else if( type == 2 ){ // Function
                    umlClass->m_private_functions.append(declaration);
                }
                else{ // Ignore?
                    qInfo() << "\tUnclassified declaration:" << declaration << "is of unknown type:" << type;
                }
            }
        }
    }

    return(umlClass);
}
