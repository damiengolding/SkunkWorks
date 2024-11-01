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

#include "../../inc/utils/stnlogger.hpp"

QString StnLogger::fileName = QDir::currentPath() % QDir::separator() % "log.txt";
bool StnLogger::isLogging = false;
QFile StnLogger::outFile(StnLogger::fileName);
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);
StnLogger::StnLogger( QObject* parent) : QObject{parent}{}

void StnLogger::install()
{
    StnLogger::outFile.setFileName(StnLogger::fileName);
    if( !StnLogger::outFile.open(QIODevice::Append) ){
        qCritical() << "Unable to open log file:"<<StnLogger::fileName<<"for QIODevice::Append";
        return;
    }
    StnLogger::isLogging = true;
    qInstallMessageHandler(StnLogger::messageHandler);
}

void StnLogger::uninstall()
{
    if( StnLogger::outFile.isOpen() ){
        StnLogger::outFile.close();
    }
    qInstallMessageHandler(nullptr);
}

void StnLogger::messageHandler(QtMsgType type, const QMessageLogContext &ctxt, const QString &msg)
{
    if( StnLogger::isLogging ){
        QString txt;
        switch (type){
        case QtInfoMsg:{
            txt = QString("[INFO] %1").arg(msg);
            break;
        }
        case QtDebugMsg:{
            txt = QString("[DEBUG] %1").arg(msg);
            break;
        }
        case QtWarningMsg:{
            txt = QString("[WARNING] %1").arg(msg);
            break;
        }
        case QtCriticalMsg:{
            txt = QString("[CRITICAL] %1").arg(msg);
            break;
        }
        case QtFatalMsg:{
            txt = QString("[FATAL] %1").arg(msg);
            break;
        }
        }
        if( !txt.isEmpty()){
            if( !StnLogger::outFile.isOpen() ){
                StnLogger::outFile.setFileName(StnLogger::fileName);
                StnLogger::outFile.open(QIODevice::Append);
            }
            QTextStream ts(&StnLogger::outFile);
            ts << txt << " - "
               << QDateTime::currentDateTime().toString()
      #ifdef QT_DEBUG
               << " - "
               << " from file: " << ctxt.file
               << " in function: " << ctxt.function
               <<  " at line: " << ctxt.line
       #endif
                << "\r\n";
            ts.flush();
        }
        (*QT_DEFAULT_MESSAGE_HANDLER)(type,ctxt,txt);
    }
    else{
        (*QT_DEFAULT_MESSAGE_HANDLER)(type,ctxt,msg);
    }
}

StnLogger::~StnLogger(){}
