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

#include "commands.hpp"
#include "uml/umlclass.hpp"
#include "uml/umlrelation.hpp"

UmlClass* getClassByUid( QList<UmlClass*> list, const QString& uid );

void processQtClass(const QString& inputFile, bool preserveCase, bool clobberExisting , bool useNamespaces){
    qInfo() << "Processing class diagram" << QDir::toNativeSeparators( inputFile ) << "into Qt QObjects";
    QDomDocument* doc = ModelUtils::VerifiedDomDocument(inputFile);
    Q_ASSERT( doc );

    if( doc->documentElement().tagName() != "qmt" ){
        qInfo() << "The supplied file is not a Qt Creator model document";
        return;
    }

    /*
        --- Package/Namespace names ---
    */
    QStringList namespaceNames;
    QList<QDomElement> mPackages = ModelUtils::DomElementList( doc->elementsByTagName( "MPackage" ));
    for( auto mPackage : mPackages ){
        QDomElement tempElement = mPackage.firstChildElement("base-MObject").firstChildElement("MObject").firstChildElement("name").toElement();
        QString packageName = tempElement.text();
        namespaceNames << packageName;
    }

    /*
        --- Containers ---
    */
    QList<UmlClass*> umlClasses;
    QList<UmlRelation*> umlRelations;
    QStringList additionalIncludes;
    /*
        --- Annotations ---
    */
    QList<QDomElement> mAnnotations = ModelUtils::DomElementList( doc->elementsByTagName("DAnnotation") );
    for( auto mAnnotation : mAnnotations ){
        QDomElement noteElem = mAnnotation.firstChildElement("text");
        if( !noteElem.isNull() ){
            QString annotationText = noteElem.text();
            QStringList incList = annotationText.split("\n");
            for( auto inc : incList ){
                if( inc.startsWith("#include") ){
                    additionalIncludes << inc;
                }
            }
        }
    }

    /*
        --- Classes and interfaces ---
    */
    QList<QDomElement> mClasses = ModelUtils::DomElementList( doc->elementsByTagName( "MClass" ));
    for( auto mClass : mClasses ){
        QDomElement nameElement = mClass.firstChildElement("base-MObject").firstChildElement("MObject").firstChildElement("name").toElement();
        if( !nameElement.isNull() ){
            umlClasses << UmlClassFactory::createClass( mClass, namespaceNames, additionalIncludes );
        }
    }

    /*
        --- Relationships ---
    */
    for( auto mClass : mClasses ){
        QDomElement relationElement = mClass.firstChildElement("base-MObject").firstChildElement("MObject").firstChildElement("relations").toElement();
        if( !relationElement.isNull() ){
            QDomElement relations = relationElement.firstChildElement("handles").firstChildElement("handles").firstChildElement("qlist").toElement();
            QList<QDomElement> items = ModelUtils::DomElementList( relationElement.elementsByTagName("item") );
            for( auto item : items ){
                UmlRelation* umlRelation = new UmlRelation();
                if( umlRelation->fromElement( item ) ){
                    umlRelations << umlRelation;
                }
            }
        }
    }

    for(  auto umlRelation : umlRelations ){
        QString fromUid = umlRelation->fromUid();
        QString toUid = umlRelation->toUid();
        UmlClass* fromClass = getClassByUid( umlClasses, fromUid );
        UmlClass* toClass = getClassByUid( umlClasses, toUid );

        if( fromClass == nullptr || toClass == nullptr ){
            continue;
        }

        QString newInclude;
        QString newBaseClass;
        QString newMember;
        switch( umlRelation->relationType() ){
        case UmlRelation::Dependency:{
            newInclude = QString("#include \"%1.hpp\"").arg( fromClass->className().toLower() );
            toClass->addInclude(newInclude);
            break;
        }
        case UmlRelation::Realization:{
            newInclude = QString("#include \"%1.hpp\"").arg( toClass->className().toLower() );
            fromClass->addInclude(newInclude);
            fromClass->addBaseClass( toClass->className() );
            break;
        }
        case UmlRelation::Composition:{
            newInclude = QString("#include \"%1.hpp\"").arg( toClass->className().toLower() );
            fromClass->addInclude(newInclude);
            newMember = QString("QList<%1*> m_%2;").arg(toClass->className()).arg( umlRelation->name().toLower() );
            fromClass->addMemberDeclaration(newMember);
            break;
        }
        case UmlRelation::Aggregation:{
            newInclude = QString("#include \"%1.hpp\"").arg( toClass->className().toLower() );
            fromClass->addInclude(newInclude);
            newMember = QString("QList<%1*>* m_%2;").arg(toClass->className()).arg( umlRelation->name().toLower() );
            fromClass->addMemberDeclaration(newMember);
            break;
        }
        case UmlRelation::Association:{
            newInclude = QString("#include \"%1.hpp\"").arg( toClass->className().toLower() );
            fromClass->addInclude(newInclude);
            break;
        }
        default:{
            break;
        }
        }

    }

    /*
        --- Some stats ---
    */
    int classCount = 0;
    int interfaceCount = 0;

    for( auto umlClass : umlClasses ){
        if( umlClass->isInterface() ){
            interfaceCount++;
        }
        else{
            classCount++;
        }
    }
    qInfo() << "Namespace:" << namespaceNames.first();
    qInfo() << "Packages:" << namespaceNames.count();
    for( auto package : namespaceNames ){
        qInfo() << "\tPackage:"<< package;
    }
    qInfo() << "Classes:"<<classCount;
    qInfo() << "Interfaces:"<<interfaceCount;
    qInfo() << "Annotations:" << mAnnotations.count();

    /*
        --- The story so far . . . ---
    */
    // Headerfiles
    for( auto mClass : umlClasses ){
        if( mClass->isClass() || mClass->isInterface() ){
            QString headerFileName = mClass->className().toLower() + ".hpp";
            QFileInfo headerFileInfo(headerFileName);
            if( headerFileInfo.exists() && clobberExisting == false ){
                qInfo() << "File exists (" << headerFileName << ") with no clobber set. Use the \"clobber\" positional argument to overwrite existing files";
                continue;
            }
            QFile headerFile(headerFileInfo.absoluteFilePath());
            if( !headerFile.open(QIODevice::WriteOnly) ){
                qInfo() << "Could not open file" << headerFileInfo.absoluteFilePath() << "for writing";
                return;
            }
            headerFile.write(  mClass->toDeclaration( useNamespaces ).toLatin1() );
            headerFile.close();
        }
    }

    // Implementation files
    for( auto mClass : umlClasses ){
        if( mClass->isClass() ){
            QString sourceFileName = mClass->className().toLower() + ".cpp";
            QFileInfo sourceFileInfo(sourceFileName);
            if( sourceFileInfo.exists() && clobberExisting == false ){
                qInfo() << "File exists (" << sourceFileName << ") with no clobber set. Use the \"clobber\" positional argument to overwrite existing files";
                continue;
            }
            QFile sourceFile(sourceFileInfo.absoluteFilePath());
            if( !sourceFile.open(QIODevice::WriteOnly) ){
                qInfo() << "Could not open file" << sourceFileInfo.absoluteFilePath() << "for writing";
                return;
            }
            sourceFile.write(  mClass->toDefinition( useNamespaces ).toLatin1() );
            sourceFile.close();
        }
    }
}

UmlClass* getClassByUid( QList<UmlClass*> list, const QString& uid ){
    for( auto umlClass : list ){
        if( umlClass->classUid() == uid ){
            return( umlClass );
        }
    }
    return( nullptr );
}

