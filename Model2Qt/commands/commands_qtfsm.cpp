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

#include <QDomDocument>
#include "commands.hpp"
// #include "../utils/modelutils.hpp"

void processQtFsm(const QString& inputFile, bool preserveCase, bool clobberExisting, bool useNamespaces){
    qInfo() << "Processing scxml" << QDir::toNativeSeparators( inputFile ) << "into Qt QObjects";
    QDomDocument* doc = ModelUtils::VerifiedDomDocument(inputFile);
    Q_ASSERT( doc != nullptr );
    qInfo() << "Scxml doc is OK";
    QString nameTemp = doc->documentElement().toElement().attribute("name");
    QString fsmName;
    QString fsmNamespace;
    QStringList nameSplit = nameTemp.split("-");
    if( nameSplit.count() == 2 ){
        fsmName = nameSplit.at(0);
        fsmNamespace = nameSplit.at(1);
    }
    else if( nameSplit.count() == 1 ){
        fsmName = nameTemp;
    }
    else{
       fsmName = "anonymous";
    }
    qInfo() << "State machine name is:"<<fsmName;
    qInfo() << "State machine namespace is:"<<fsmNamespace;

    QList<QDomElement> states = ModelUtils::DomElementList(doc->elementsByTagName("state"));
    QList<QDomElement> parallels = ModelUtils::DomElementList(doc->elementsByTagName("parallel"));
    QList<QDomElement> allItems = states;
    allItems.append(parallels);

    qInfo() << "States:"<<states.count();
    qInfo() << "Parallels:"<<parallels.count();
    qInfo() << "All state objects:"<<allItems.count();

    // Interface file
    QFile fi(":/templates/qtfsm/fsm_interface.txt");
    if( !fi.open(QIODevice::ReadOnly) ){
        qFatal() << "Unable to open resource file :/templates/qtfsm/fsm_interface.txt for reading.";
    }
    QString fsmTemplate = fi.readAll();
    fi.close();

    // Namespace
    if( useNamespaces ){
        if( !fsmNamespace.isEmpty() ){
            QString startNamespace = QString( "namespace %1 {" ).arg(fsmNamespace);
            QString endNamespace = QString( "} // End of namespace %1" ).arg(fsmNamespace);
            fsmTemplate.replace("%{START_NAMESPACE}", startNamespace);
            fsmTemplate.replace("%{END_NAMESPACE}",endNamespace);
        }
        else{
            fsmTemplate.replace("%{START_NAMESPACE}", "");
            fsmTemplate.replace("%{END_NAMESPACE}","");
        }
    }
    else{
        fsmTemplate.replace("%{START_NAMESPACE}", "");
        fsmTemplate.replace("%{END_NAMESPACE}","");
    }

    QFile fo;
    QTextStream ts;
    // Write file out
    if( QFileInfo::exists("ifinitestatemachine.hpp") && !clobberExisting ){
        qInfo() << "Refusing to overwrite an existing file.";
    }
    else{
        QString interfaceFileName = "ifinitestatemachine.hpp";
        fo.setFileName(interfaceFileName);
        if( !fo.open(QIODevice::WriteOnly) ){
            qFatal() << "Unable to open header file" << interfaceFileName <<  "for writing.";
        }
        QTextStream ts( &fo );
        ts << fsmTemplate;
        ts.flush();
        fo.close();
    }

    // State machine proper
    QDomElement fsmState = allItems.first();
    QString headerFile;
    QString implFile;
    QString itemName;

#pragma Top level FSM {

    // Top level FSM
    preserveCase ? headerFile = fsmName % ".hpp" : headerFile = fsmName.toLower() % ".hpp";
    preserveCase ? implFile = fsmName % ".cpp" : implFile = fsmName.toLower() % ".cpp";

    // Header
    fi.setFileName(":/templates/qtfsm/fsm_hdr.txt");
    if( !fi.open(QIODevice::ReadOnly) ){
        qFatal() << "Unable to open State Machine template file for reading";
    }
    QString templateText = fi.readAll();
    fi.close();

    QString outputText = templateText.replace("%{FSM_CLASS}", fsmName);

    // Namespace
    if( useNamespaces ){
        if( !fsmNamespace.isEmpty() ){
            QString startNamespace = QString( "namespace %1 {" ).arg(fsmNamespace);
            QString endNamespace = QString( "} // End of namespace %1" ).arg(fsmNamespace);
            outputText.replace("%{START_NAMESPACE}", startNamespace);
            outputText.replace("%{END_NAMESPACE}",endNamespace);
        }
        else{
            outputText.replace("%{START_NAMESPACE}", "");
            outputText.replace("%{END_NAMESPACE}","");
        }
    }
    else{
        outputText.replace("%{START_NAMESPACE}", "");
        outputText.replace("%{END_NAMESPACE}","");
    }

    // Write file out
    if( QFileInfo::exists(headerFile) && !clobberExisting ){
        qInfo() << "Refusing to overwrite an existing file.";
    }
    else{
        fo.setFileName(headerFile);
        if( !fo.open(QIODevice::WriteOnly) ){
            qFatal() << "Unable to open State Machine template file for writing";
        }
        ts.setDevice(&fo);
        ts << outputText;
        ts.flush();
        fo.close();
    }

    // Implementation
    fi.setFileName(":/templates/qtfsm/fsm_impl.txt");
    if( !fi.open(QIODevice::ReadOnly) ){
        qFatal() << "Unable to open State Machine template file for reading";
    }
    templateText = fi.readAll();
    fi.close();

    outputText = templateText.replace("%{FSM_CLASS}", fsmName);
    outputText = outputText.replace("%{FSM_HDR}",headerFile);

    // Namespace
    if( useNamespaces ){
        if( !fsmNamespace.isEmpty() ){
            QString startNamespace = QString( "namespace %1 {" ).arg(fsmNamespace);
            QString endNamespace = QString( "} // End of namespace %1" ).arg(fsmNamespace);
            outputText.replace("%{START_NAMESPACE}", startNamespace);
            outputText.replace("%{END_NAMESPACE}",endNamespace);
        }
        else{
            outputText.replace("%{START_NAMESPACE}", "");
            outputText.replace("%{END_NAMESPACE}","");
        }
    }
    else{
        outputText.replace("%{START_NAMESPACE}", "");
        outputText.replace("%{END_NAMESPACE}","");
    }

    // Write file out
    if( QFileInfo::exists(implFile) && !clobberExisting ) {
        qInfo() << "Refusing to overwrite an existing file.";
    }
    else{
        fo.setFileName(implFile);
        if( !fo.open(QIODevice::WriteOnly) ){
            qFatal() << "Unable to open State Machine template file for writing";
        }
        ts.setDevice(&fo);
        ts << outputText;
        ts.flush();
        fo.close();
    }

#pragma Top level FSM }

#pragma Remaining states {
    allItems.removeFirst();

    QStringList allHeaders;
    QString stateHeader;
    QString stateImpl;
    QString hdrTemplate;
    QString implTemplate;

    // Read in template text
    fi.setFileName(":/templates/qtfsm/state_hdr.txt");
    if( !fi.open(QIODevice::ReadOnly) ){
        qFatal() << "Unable to open State Machine template file for reading";
    }
    hdrTemplate = fi.readAll();
    fi.close();

    fi.setFileName(":/templates/qtfsm/state_impl.txt");
    if( !fi.open(QIODevice::ReadOnly) ){
        qFatal() << "Unable to open State Machine template file for reading";
    }
    implTemplate = fi.readAll();
    fi.close();

    for( auto item : allItems ){
        QString stateName = item.attribute("id");

        preserveCase ? stateHeader = stateName % ".hpp" : stateHeader = stateName.toLower() % ".hpp";
        preserveCase ? stateImpl = stateName % ".cpp" : stateImpl = stateName.toLower() % ".cpp";
        allHeaders.append(stateHeader);

        // Header file
        QString outputText = hdrTemplate;
        outputText.replace("%{STATE_CLASS}", stateName);

        // Namespace
        if( useNamespaces ){
            if( !fsmNamespace.isEmpty() ){
                QString startNamespace = QString( "namespace %1 {" ).arg(fsmNamespace);
                QString endNamespace = QString( "} // End of namespace %1" ).arg(fsmNamespace);
                outputText.replace("%{START_NAMESPACE}", startNamespace);
                outputText.replace("%{END_NAMESPACE}",endNamespace);
            }
            else{
                outputText.replace("%{START_NAMESPACE}", "");
                outputText.replace("%{END_NAMESPACE}","");
            }
        }
        else{
            outputText.replace("%{START_NAMESPACE}", "");
            outputText.replace("%{END_NAMESPACE}","");
        }

        // Write file out
        if( QFileInfo::exists(stateHeader) && !clobberExisting ) {
            qInfo() << "Refusing to overwrite an existing file.";
        }
        else{
            fo.setFileName(stateHeader);
            if( !fo.open(QIODevice::WriteOnly) ){
                qFatal() << "Unable to open State Machine template file for writing";
            }
            ts.setDevice(&fo);
            ts << outputText;
            ts.flush();
            fo.close();
        }

        // Impl file
        outputText = implTemplate;
        outputText.replace("%{STATE_CLASS}", stateName);
        outputText = outputText.replace("%{STATE_HDR}", stateHeader);

        // Namespace
        if( useNamespaces ){
            if( !fsmNamespace.isEmpty() ){
                QString startNamespace = QString( "namespace %1 {" ).arg(fsmNamespace);
                QString endNamespace = QString( "} // End of namespace %1" ).arg(fsmNamespace);
                outputText.replace("%{START_NAMESPACE}", startNamespace);
                outputText.replace("%{END_NAMESPACE}",endNamespace);
            }
            else{
                outputText.replace("%{START_NAMESPACE}", "");
                outputText.replace("%{END_NAMESPACE}","");
            }
        }
        else{
            outputText.replace("%{START_NAMESPACE}", "");
            outputText.replace("%{END_NAMESPACE}","");
        }

        // Write file out
        if( QFileInfo::exists(stateImpl) && !clobberExisting ) {
            qInfo() << "Refusing to overwrite an existing file.";
        }
        else{
            fo.setFileName(stateImpl);
            if( !fo.open(QIODevice::WriteOnly) ){
                qFatal() << "Unable to open State Machine template file for writing";
            }
            ts.setDevice(&fo);
            ts << outputText;
            ts.flush();
            fo.close();
        }

    }
#pragma Remaining states }

#pragma fsm_includes {
    // Write file out
    if( QFileInfo::exists("fsm_includes.hpp") && !clobberExisting ) {
        qInfo() << "Refusing to overwrite an existing file.";
    }
    else{
        fo.setFileName("fsm_includes.hpp");
        if( !fo.open(QIODevice::WriteOnly) ){
            qFatal() << "Unable to open State Machine template file for writing";
        }
        ts.setDevice(&fo);
        ts << "#pragma once\r\n";
        for( auto header : allHeaders ){
            ts << "#include \"" << header <<"\"\r\n";
        }
        ts << "\r";
        ts.flush();
    }
    fo.close();

#pragma fsm_includes }

}

