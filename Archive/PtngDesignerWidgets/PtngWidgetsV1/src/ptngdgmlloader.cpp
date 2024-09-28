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
#include "../inc/ptngdgmlloader.hpp"
#include "../inc/conversionutils.hpp"

PtngDgmlLoader::PtngDgmlLoader(const QString &dgmlFile, QObject *parent)
    : QObject{parent}
{
    inputFile = dgmlFile;
}

void PtngDgmlLoader::load()
{
    qInfo() << "Loading DGML file:"<<inputFile;
    QScopedPointer<QDomDocument> doc( new QDomDocument("dgml") );
    QScopedPointer<QFile> file( new QFile( inputFile ) );
    if( !file->open(QIODevice::ReadOnly) ){
        qWarning() << "Could not open"<< inputFile<<"for reading";
        emit loadCompleted( false );
        return;
    }
    if( !doc->setContent( file->readAll() ) ){
        qWarning() << "Could not parse DGML from:"<<inputFile;
        emit loadCompleted( false );
    }
    qInfo() << "DGML file"<<inputFile<<"Parsed";
    QList<QDomElement> dgmlNodes = ConversionUtils::DomElementList( doc->elementsByTagName("Node") );
    qInfo() << "DGML Nodes:"<<dgmlNodes.count();

    QList<QDomElement> dgmlLinks = ConversionUtils::DomElementList( doc->elementsByTagName("Link") );
    qInfo() << "DGML Links:"<<dgmlLinks.count();

    emit loadCompleted( true );
}
