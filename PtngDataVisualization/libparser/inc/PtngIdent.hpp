/*
MIT License

Copyright (c) 2024 Damien Golding

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

Don't use it to find and eat babies ... unless you're really REALLY hungry ;-)
*/
#pragma once

#include "../inc/libparser_global.hpp"
#include "../inc/PtngEnums.hpp"

#include <QObject>

namespace ptng {

/*!
   \brief The PtngIdent class

   Provides input file identification
 */
class PtngIdent : public QObject
{
    Q_OBJECT
public:
    explicit PtngIdent(QObject *parent = nullptr);
    static PtngEnums::SupportedInputTypes checkFile(const QString &file);

private:
    static PtngEnums::SupportedInputTypes checkXmlFile(const QString &file);
    static PtngEnums::SupportedInputTypes checkTextFile(const QString &file);

signals:

private slots: // for QTest module
    void shouldRecogniseFile_data();
    void shouldRecogniseFile();

};
} // namespace ptng

