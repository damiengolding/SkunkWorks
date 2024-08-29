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

#include "inc/reconcommands.hpp"

void initArgumentParser(QCoreApplication &app, QCommandLineParser &parser);
void initArgumentOptions(QCoreApplication &app, QCommandLineParser &parser);
void processArgumentOptions(QCoreApplication &app, QCommandLineParser &parser);

void showExamples();

QList<QCommandLineOption> commandLineOptions;

QString targetIpAddresses = QString();
bool writeToXml = false;
QString outputFileName = "";
bool runSilent = false;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCommandLineParser p;
    initArgumentParser(a,p);

    // CODECOMP Add logic after arguments are parsed

    return(0);
    // return(a.exec());
}

void initArgumentParser(QCoreApplication &app, QCommandLineParser &parser){
    app.setApplicationName("qsslrecon");
    app.setApplicationVersion("0.0.1");
    app.setOrganizationName("Golding's Gym");
    app.setOrganizationDomain("https://github.com/damiengolding");

    // Convenience options
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription("qsslrecon Queries an SSL server and examines certificate details. Can also provide details of internal networking configuration.");

    initArgumentOptions(app,parser);
    parser.process(app);
    processArgumentOptions(app, parser);
}

void initArgumentOptions(QCoreApplication &app, QCommandLineParser &parser){

    // Postitional arguments
    parser.addPositionalArgument("local", "Local host checks");
    parser.addPositionalArgument("all-nics", "Local host check - show all NICs");
    parser.addPositionalArgument("all-nics-config", "Local host checks - show configuration for all NICs");
    parser.addPositionalArgument("all-ips", "Local host checks - show all IP addresses on the local host");
    parser.addPositionalArgument("nic-for-ip", "Local host checks - show NICs for all IP addresses on the local host");
    parser.addPositionalArgument("domain", "Local host checks - domain membership and hostname");

    parser.addPositionalArgument("remote", "Remote host checks");
    parser.addPositionalArgument("resolve", "Remote host checks - resolves each host in the target option");

    parser.addPositionalArgument("all", "All checks for the selected mode (local or remote)");
    parser.addPositionalArgument("silent", "Do not print to console (only makes sense if you have set the -x/--xml option)");

    // Options
    parser.addOption({{"t","target"},"Comma-delimited list of host(s) to query.","IP Address(es) or domain name(s)"});
    parser.addOption({{"x","xml"},"Write to XML file. This is ignored for some operations.","file"});
}

void processArgumentOptions(QCoreApplication &app, QCommandLineParser &parser){
    ReconCommands reconCommands;

    QStringList arguments = parser.positionalArguments();
    if( arguments.empty() ){
        qCritical() << "No mode or sub-commands set";
        parser.showHelp( 1 );
    }

    if( arguments.contains("silent") ){
        runSilent = false;
    }

    if( parser.isSet("target") ){
        targetIpAddresses = parser.value("target");
    }

    if( parser.isSet("xml") ){
        outputFileName = parser.value("xml");
        writeToXml = true;
        if( !outputFileName.endsWith(".xml") ){
            outputFileName += ".xml";
        }
    }

    if( arguments.contains("silent") ){
        runSilent = true;
    }

    reconCommands.setIpAddress(targetIpAddresses);
    // reconCommands.setPortNumber(targetPortNumber);
    reconCommands.setOutputFileName(outputFileName);
    reconCommands.setWriteToXml(writeToXml);
    reconCommands.setSilent(runSilent);

    /*
        --- Process positional arguments and options
    */

    if( arguments.contains("local") ){
        reconCommands.setReconType( ReconCommands::Local );
        for( auto arg : arguments ){
            if( arg == "all" ){
                reconCommands.showAllNics();
                reconCommands.showAllNicsConfig();
                reconCommands.showAllAddresses();
                reconCommands.showNicToIp();
                reconCommands.showDomainHostName();
                break;
            }
            else if( arg == "all-nics" ){
                reconCommands.showAllNics();
            }
            else if( arg == "all-nics-config" ) {
                reconCommands.showAllNicsConfig();
            }
            else if( arg == "all-ips" ) {
                reconCommands.showAllAddresses();
            }
            else if( arg == "nic-for-ip"  ){
                reconCommands.showNicToIp();
            }
            else if( arg == "domain" ) {
                reconCommands.showDomainHostName();
            }
        }
    }
    else if( arguments.contains( "remote" ) ){
        reconCommands.setReconType( ReconCommands::Remote );
        if( targetIpAddresses.isEmpty() ){
            qCritical() << "Target hosts must be set with -t or --target";
            app.exit( 3 );
        }
        for( auto arg : arguments ){
            if( arg == "all" ){
                reconCommands.showHostResolve(targetIpAddresses);
                break;
            }
            else if( arg == "resolve" ) {
                reconCommands.showHostResolve(targetIpAddresses);
            }
        }
    }

    /*
        --- Finishing touches ---
    */
    reconCommands.writeOutput();
}

void showExamples(){
    qInfo() << "########## QHostRecon.exe usage examples ##########";
    qInfo() << "\tqhostrecon.exe local_host -o list-nics";
    qInfo() << "\tqhostrecon.exe local_host -o list-nics-config";
    qInfo() << "\tqhostrecon.exe local_host -o list-ips";
    qInfo() << "\tqhostrecon.exe local_host -o nic-for-ip:192.168.4.100";

}

