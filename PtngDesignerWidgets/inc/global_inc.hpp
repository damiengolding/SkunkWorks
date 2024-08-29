/*
MIT License

Copyright (c) %date% %author%

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
#ifndef GLOBAL_INC_HPP
#define GLOBAL_INC_HPP

#include <QtCore/qglobal.h>
#include <QDomDocument>
#include <QDomNode>
#include <QDomNodeList>
#include <QDomElement>
#include <QDomText>
#include <QDomAttr>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QMap>
#include <QList>
#include <QDebug>
#include <QScopedPointer>
#include <QStringBuilder>
#include <QColor>
#include <QMessageBox>
#include <QFont>
#include <QFontInfo>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QUndoCommand>
#include <QUndoGroup>
#include <QUndoStack>
#include <QUndoView>

#include "PtngDGMLBuilder.hpp"
#include "PtngDGMLConv.hpp"
#include "PtngHostBuilder.hpp"
#include "PtngEnums.hpp"
#include "PtngIP4Address.hpp"
#include "PtngIdent.hpp"
#include "PtngSpecifications.hpp"
#include "PtngDGMLBuilder.hpp"
#include "PtngDGMLConv.hpp"
#include "PtngInputParser.hpp"
#include "PtngConfig.hpp"
using namespace ptng;

#include "ConversionUtils.hpp"
using namespace GoldingsGym;

#endif // GLOBAL_INC_HPP
