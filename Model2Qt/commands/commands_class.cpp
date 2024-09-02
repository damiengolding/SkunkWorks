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
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include "uml/umlclass.hpp"

void processDomDocument(const QString& inputFile, bool preserveCase, bool clobberExisting , bool useNamespaces);
void processXmlStreamReader(const QString& inputFile, bool preserveCase, bool clobberExisting , bool useNamespaces);

void processQtClass(const QString& inputFile, bool preserveCase, bool clobberExisting , bool useNamespaces){
    qInfo() << "Processing class diagram" << QDir::toNativeSeparators( inputFile ) << "into Qt QObjects";
    // processXmlStreamReader(inputFile, preserveCase, clobberExisting, useNamespaces);
    processDomDocument(inputFile, preserveCase, clobberExisting, useNamespaces);
}

void processDomDocument(const QString& inputFile, bool preserveCase, bool clobberExisting , bool useNamespaces){
    qInfo() << "Procesing with QDomDocument";
    QDomDocument* doc = FsmUtils::VerifiedDomDocument(inputFile);
    Q_ASSERT( doc );

    if( doc->documentElement().tagName() != "qmt" ){
        qInfo() << "The supplied file is not a Qt Creator model document";
        return;
    }

    /*
        --- Package/Namespace names ---
    */
    QStringList namespaceNames;
    QList<QDomElement> mPackages = FsmUtils::DomElementList( doc->elementsByTagName( "MPackage" ));
    for( auto mPackage : mPackages ){
        QDomElement tempElement = mPackage.firstChildElement("base-MObject").firstChildElement("MObject").firstChildElement("name").toElement();
        if( tempElement.isNull() ){
            qInfo() << "Packages: tempElement isNull";
        }
        QString packageName = tempElement.text();
        namespaceNames << packageName;
    }

    /*
        --- Containers ---
    */

    QList<UmlClass*> umlClasses;
    QStringList additionalIncludes;
    /*
        --- Annotations ---
    */
    QList<QDomElement> mAnnotations = FsmUtils::DomElementList( doc->elementsByTagName("DAnnotation") );
    for( auto mAnnotation : mAnnotations ){
        QDomElement noteElem = mAnnotation.firstChildElement("text");
        if( noteElem.isNull() ){
            qInfo() << "Annotation: text element isNull";
        }
        else{
            QString annotationText = noteElem.text();
            // qInfo() << "Annotation text" << annotationText;
            QStringList incList = annotationText.split("\n");
            // qInfo() << "incList count:" << incList.count();
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
    QList<QDomElement> mClasses = FsmUtils::DomElementList( doc->elementsByTagName( "MClass" ));
    for( auto mClass : mClasses ){
        QDomElement nameElement = mClass.firstChildElement("base-MObject").firstChildElement("MObject").firstChildElement("name").toElement();
        if( nameElement.isNull() ){
            // qInfo() << "Classes: name element isNull";
        }
        else{
            // qInfo() << "Name:" << nameElement.text();
            umlClasses << UmlClassFactory::createClass( mClass, namespaceNames, additionalIncludes );
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
    qInfo() << "Packages (inc. the file package):" << namespaceNames.count();
    for( auto package : namespaceNames ){
        qInfo() << "\tPackage:"<< package;
    }
    qInfo() << "Classes:"<<classCount;
    qInfo() << "Interfaces:"<<interfaceCount;
    qInfo() << "Annotations:" << mAnnotations.count();

    /*
        --- The story so far . .  . ---
    */

    // Headerfiles
    for( auto mClass : umlClasses ){
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

    // Implentation files
    for( auto mClass : umlClasses ){
        if( mClass->isInterface() ){
            continue;
        }
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

void processXmlStreamReader(const QString& inputFile, bool preserveCase, bool clobberExisting , bool useNamespaces){
    qInfo() << "Procesing with QXmlStreamReader (no, really)";
    QFile file(inputFile);
    if( !file.open(QIODevice::ReadOnly) ){
        qInfo() << "Couldn't open" << inputFile << "for reading";
        return;
    }

    QXmlStreamReader reader(&file);

    while(!reader.atEnd())
    {
        QXmlStreamReader::TokenType tokenType = reader.readNext();
        switch (tokenType) {
        case QXmlStreamReader::StartDocument:
            // Logical start of document
            break;
        case QXmlStreamReader::EndDocument:
            // Logical end of document
            break;
        case QXmlStreamReader::StartElement:{
            QString elementName = reader.name().toString();
            if( elementName.toLower() == "instance" ){
                QXmlStreamAttributes attrs = reader.attributes();
                if( attrs.hasAttribute("type") ){
                    QString instanceType = attrs.value("type").toString().toLower();
                    // qInfo() << "Instance type:" << instanceType ;
                    if( instanceType == "mclass" ){
                        while( reader.readNextStartElement() ){
                            QString readerName = reader.name().toString().toLower();
                            if( readerName == "mobject" ){
                                while( reader.readNextStartElement() ){
                                    readerName= reader.name().toString().toLower();
                                    if( readerName == "name" ){
                                        qInfo() << "Name:" << reader.text();
                                        break;
                                    }
                                }
                            }
                            // qInfo() << "\tNext token:" << reader.name() ;
                        }
                    }
                }
            }
            break;
        }
        case QXmlStreamReader::EndElement:
            // For completeness - don't really care about this
            break;
        }
    }
    if( file.isOpen()){
        file.close();
    }
}


