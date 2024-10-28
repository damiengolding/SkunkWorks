#pragma once

#include <QStandardItemModel>
#include <QStandardItem>

namespace GoldingsGym::Ptng {

/*!
 * \brief The AbstractItemSpec class
 *
 * Abstract base class for network items such as hosts, open ports, issues and IP addresses. Inherits QStandardItem
 *
 * \sa AbstractReportSpec
 */
// TODO inherit QStandardItem
class AbstractItemSpec {
public:
    virtual int LoadFromScanEntry(const QString& entry) = 0;

};
} // End of namespace GoldingsGym::Ptng
