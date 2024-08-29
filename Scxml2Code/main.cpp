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
#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QList>

#include "fsmutils.hpp"

void initArgumentParser(QCoreApplication &app, QCommandLineParser &parser);
void initArgumentOptions(QCoreApplication &app, QCommandLineParser &parser);
void processArgumentOptions(QCoreApplication &app, QCommandLineParser &parser);

void processScxml();

QList<QCommandLineOption> commandLineOptions;
QString inputFile;
bool preserveCaseFileNames = false;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCommandLineParser p;
    initArgumentParser(a,p);

    // CODECOMP Add logic after arguments are parsed
    processScxml();
    // return(a.exec());
    return(0);
}

void initArgumentParser(QCoreApplication &app, QCommandLineParser &parser){
    app.setApplicationName("scxml2code");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Golding's Gym");
    app.setOrganizationDomain("https://github.com/damiengolding");

    parser.addHelpOption();
    parser.addVersionOption();

    parser.setApplicationDescription("scxml2code Converts an scxml file created qith Qt Creator to classes, with pre-defined interfaces");
    initArgumentOptions(app,parser);
    parser.process(app);
    processArgumentOptions(app, parser);
}

void initArgumentOptions(QCoreApplication &app, QCommandLineParser &parser){
    parser.addOption({{"i","input"},"Input file","file"});
    parser.addPositionalArgument("preserve-case", "Preserve case for file names");
}

void processArgumentOptions(QCoreApplication &app, QCommandLineParser &parser){
    if( !parser.isSet("input") ){
        parser.showHelp(1);
    }

    inputFile = parser.value("input");

    for( auto pos : parser.positionalArguments() ){
        if( pos == "preserve-case" ){
            preserveCaseFileNames = true;
        }
    }
}

void processScxml(){
    qInfo() << "Processing scxml";
    QString fsmName;
    QDomDocument* doc = FsmUtils::VerifiedDomDocument(inputFile);
    Q_ASSERT( doc != nullptr );
    qInfo() << "Scxml doc is OK";
    QDomNodeList stateNodeList = doc->elementsByTagName("state");
    QDomNodeList parallelNodeList = doc->elementsByTagName("parallel");

    qInfo() << "States:"<<stateNodeList.count();
    qInfo() << "Parallels:"<<parallelNodeList.count();

    QList<QDomElement> states = FsmUtils::DomElementList(stateNodeList);
    QList<QDomElement> parallels = FsmUtils::DomElementList(parallelNodeList);

    QList<QDomElement> allItems = states;
    allItems.append(parallels);

    qInfo() << "All state objects:"<<allItems.count();

    // Interface file
    QFile fi(":/templates/fsm_interface.txt");
    if( !fi.open(QIODevice::ReadOnly) ){
        qFatal() << "Unable to open resource file qrc:/templates/fsm_interface.txt for reading.";
    }
    QString fsmTemplate = fi.readAll();
    fi.close();

    QString interfaceFileName = "IFiniteStateMachine.hpp";
    QFile fo(interfaceFileName);
    if( !fo.open(QIODevice::WriteOnly) ){
        qFatal() << "Unable to open header file" << interfaceFileName <<  "for writing.";
    }
    QTextStream ts( &fo );
    ts << fsmTemplate;
    ts.flush();
    fo.close();

    // State machine proper
    QDomElement fsmState = allItems.first();
    fsmName = fsmState.attribute("id");
    qInfo() << "FSM Name:"<<fsmState.attribute("id");
    QString headerFile;
    QString implFile;
    QString itemName;

#pragma Top level FSM {

    // Top level FSM
    preserveCaseFileNames ? headerFile = fsmName % ".hpp" : headerFile = fsmName.toLower() % ".hpp";
    preserveCaseFileNames ? implFile = fsmName % ".cpp" : implFile = fsmName.toLower() % ".cpp";

    // Header
    fi.setFileName(":/templates/fsm_hdr.txt");
    if( !fi.open(QIODevice::ReadOnly) ){
        qFatal() << "Unable to open State Machine template file for reading";
    }
    QString templateText = fi.readAll();
    fi.close();

    QString outputText = templateText.replace("%{FSM_CLASS}", fsmName);
    fo.setFileName(headerFile);
    if( !fo.open(QIODevice::WriteOnly) ){
        qFatal() << "Unable to open State Machine template file for writing";
    }
    ts.setDevice(&fo);
    ts << outputText;
    ts.flush();
    fo.close();

    // Implementation
    fi.setFileName(":/templates/fsm_impl.txt");
    if( !fi.open(QIODevice::ReadOnly) ){
        qFatal() << "Unable to open State Machine template file for reading";
    }
    templateText = fi.readAll();
    fi.close();

    outputText = templateText.replace("%{FSM_CLASS}", fsmName);
    outputText = outputText.replace("%{FSM_HDR}",headerFile);
    fo.setFileName(implFile);
    if( !fo.open(QIODevice::WriteOnly) ){
        qFatal() << "Unable to open State Machine template file for writing";
    }
    ts.setDevice(&fo);
    ts << outputText;
    ts.flush();
    fo.close();

#pragma Top level FSM }

#pragma Remaining states {
    allItems.removeFirst();

    QStringList allHeaders;
    QString stateHeader;
    QString stateImpl;
    QString hdrTemplate;
    QString implTemplate;

    // Read in template text
    fi.setFileName(":/templates/state_hdr.txt");
    if( !fi.open(QIODevice::ReadOnly) ){
        qFatal() << "Unable to open State Machine template file for reading";
    }
    hdrTemplate = fi.readAll();
    fi.close();

    fi.setFileName(":/templates/state_impl.txt");
    if( !fi.open(QIODevice::ReadOnly) ){
        qFatal() << "Unable to open State Machine template file for reading";
    }
    implTemplate = fi.readAll();
    fi.close();

    for( auto item : allItems ){
        QString stateName = item.attribute("id");

        preserveCaseFileNames ? stateHeader = stateName % ".hpp" : stateHeader = stateName.toLower() % ".hpp";
        preserveCaseFileNames ? stateImpl = stateName % ".cpp" : stateImpl = stateName.toLower() % ".cpp";
        allHeaders.append(stateHeader);

        // Header file
        QString outputText = hdrTemplate;
        outputText.replace("%{STATE_CLASS}", stateName);
        fo.setFileName(stateHeader);
        if( !fo.open(QIODevice::WriteOnly) ){
            qFatal() << "Unable to open State Machine template file for writing";
        }
        ts.setDevice(&fo);
        ts << outputText;
        ts.flush();
        fo.close();

        // Impl file
        outputText = implTemplate;
        outputText.replace("%{STATE_CLASS}", stateName);
        outputText = outputText.replace("%{STATE_HDR}", stateHeader);
        fo.setFileName(stateImpl);
        if( !fo.open(QIODevice::WriteOnly) ){
            qFatal() << "Unable to open State Machine template file for writing";
        }
        ts.setDevice(&fo);
        ts << outputText;
        ts.flush();
        fo.close();

    }
#pragma Remaining states }

#pragma fsm_includes {

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
    fo.close();

#pragma fsm_includes }

}
