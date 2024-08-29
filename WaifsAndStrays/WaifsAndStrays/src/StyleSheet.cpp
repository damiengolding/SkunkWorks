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
#include "../inc/StyleSheet.hpp"

namespace GoldingsGym {

QColor StyleSheet::colorCritical = QColor( 188,69,67 );
QColor StyleSheet::colorHigh = QColor( 214,106,35 );
QColor StyleSheet::colorMedium = QColor( 175,225,150 );
QColor StyleSheet::colorLow = QColor( 241,232,151 );
QColor StyleSheet::colorInfo = QColor( 117,160,198 );
QColor StyleSheet::fontColor = QColorConstants::Black;
QColor StyleSheet::highlightColor = QColor( 220,220,220 );
QColor StyleSheet::fillColor = QColor(179,196,175);
QColor StyleSheet::borderColor = QColorConstants::Black;
QColor StyleSheet::backgroundColor = QColorConstants::White;
QFont StyleSheet::mainFont = QFont("Open Sans",10);
QFont StyleSheet::headerFont = QFont("Open Sans",12);
QFont StyleSheet::titleFont = QFont("Open Sans",15);

StyleSheet::StyleSheet(QObject *parent)
    : QObject{parent}
{

}

// TODO Implement load/save
bool StyleSheet::loadStyleSheet(const QString &file)
{
    return{};
}

bool StyleSheet::saveStyleSheet(const QString &file)
{
    return{};
}

} // namespace GoldingsGym
