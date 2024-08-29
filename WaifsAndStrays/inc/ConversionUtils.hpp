/*
   Copyright (C) Damien Golding

   This is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this software; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA

  Don't use it to find and eat babies ... unless you're really REALLY hungry ;-)

*/

#ifndef CONVERSIONUTILS_H
#define CONVERSIONUTILS_H

#include <QObject>
#include <QMetaEnum>
#include <QString>
#include <QDomNode>
#include <QDomElement>

namespace GoldingsGym{
/*!
   \brief The EnumStringConverter class

   This class uses the Q_PROPERTY system, specifically Q_ENUM and QMetaEnum
   to provide a property-base string/enum and enum/string conversion.
 */
class ConversionUtils : public QObject{
    Q_OBJECT
public:
    ConversionUtils(QObject *parent = nullptr) : QObject(parent){}
    ~ConversionUtils(){}

    /*!
     * \brief EnumFromString
     * \param textValue
     * \return
     */
    template <typename E>
    static E EnumFromString(const QString &textValue);

    /*!
     * \brief StringFromEnum
     * \param value
     * \return
     */
    template <typename E>
    static QString StringFromEnum(E value);

    /*!
       \brief domElementList
       \param list
       \return QList<QDomElement>

       Converts a QDomNodeList into a QList<QDomElement> because the inability to use for( auto node : QDomNodeList) is one of the most annoying things about Qt.
     */
    static QList<QDomElement> domElementList(const QDomNodeList &list);
};

}

#endif // CONVERSIONUTILS_H
