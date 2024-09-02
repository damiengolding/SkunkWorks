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

#include "commands.hpp"

QList<QCommandLineOption> commandLineOptions;
QString inputFile = {};
bool preserveCaseFileNames = false;
bool qtFsm = false;
bool qtSmf = false;
bool qtClass = false;
bool clobberExisting = false;
bool useNamespaces = false;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCommandLineParser p;
    initArgumentParser(a,p);
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

    parser.setApplicationDescription("scxml2code Converts an scxml or class diagram UML file created with Qt Creator into classes, with pre-defined interfaces");
    initArgumentOptions(app,parser);
    parser.process(app);
    processArgumentOptions(app, parser);
}

void initArgumentOptions(QCoreApplication &app, QCommandLineParser &parser){
    parser.addOption({{"i","input"},"Input file","file"});
    // parser.addPositionalArgument("preserve-case", "Preserve case for file names");
    parser.addPositionalArgument("clobber", "Overwrite existing files");
    parser.addPositionalArgument("namespaces", "Use package and component names (if available) as namespaces");
    parser.addPositionalArgument("qtfsm", "Finite State Machine with QObjects");
    parser.addPositionalArgument("qtsmf", "Finite State Machine with QStates");
    parser.addPositionalArgument("qtclass", "Qt Creator class model diagram to QObjects");
}

void processArgumentOptions(QCoreApplication &app, QCommandLineParser &parser){
    if( !parser.isSet("input") ){
        parser.showHelp(1);
    }
    inputFile = parser.value("input");

    QStringList arguments = parser.positionalArguments();

    if( arguments.contains("clobber") ) clobberExisting = true;
    if( arguments.contains("namespaces") ) useNamespaces = true;
    // if( arguments.contains("preserve-case") ) preserveCaseFileNames = true;

    if( arguments.contains("qtfsm") ){
        qtFsm = true;
        processQtFsm( inputFile, preserveCaseFileNames, clobberExisting, useNamespaces );
    }
    else if( arguments.contains("qtsmf") ){
        qtSmf = true;
        processQtSmf( inputFile, preserveCaseFileNames, clobberExisting, useNamespaces );
    }
    else if( arguments.contains("qtclass") ){
        qtClass = true;
        processQtClass( inputFile, preserveCaseFileNames, clobberExisting, useNamespaces );
    }
    else{
        qCritical() << "No positional argument is set for input type (qtfsm|qtsmf|qtclass)";
        parser.showHelp(2);
    }


}


