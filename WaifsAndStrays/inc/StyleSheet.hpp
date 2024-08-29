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

#include <QObject>
#include <QColor>
#include <QFont>

namespace GoldingsGym {

/*!
   \brief The StyleSheet class

 */
class StyleSheet : public QObject
{
    Q_OBJECT

public:
    explicit StyleSheet(QObject *parent = nullptr);

public:
    // QColor colorCritical = QColor( 188,69,67 );
    static QColor colorCritical;
    static QColor colorHigh;
    static QColor colorMedium;
    static QColor colorLow;
    static QColor colorInfo;

    // Other colors
    static QColor fontColor;
    static QColor highlightColor;
    static QColor fillColor;
    static QColor borderColor;
    static QColor backgroundColor;

    // Fonts and text
    static QFont mainFont;
    static QFont headerFont;
    static QFont titleFont;

public:
    static bool loadStyleSheet(const QString &file);
    static bool saveStyleSheet(const QString &file);

signals:

};

} // namespace ptng

