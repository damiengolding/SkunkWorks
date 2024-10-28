#pragma once

#include <QObject>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>
#include "abstractitemspec.hpp"

namespace GoldingsGym::Ptng {

/*!
 * \brief The AbstractBuilder class
 *
 * Abstract base class for builder classes.
 *
 * \sa AbstractItemSpec
 */
class AbstractBuilder {
public:
    virtual AbstractBuilder& Add(const QDomElement& element) = 0;
    virtual AbstractBuilder& Add(const QString& entry) = 0;

};
} // End of namespace GoldingsGym::Ptng
