#pragma once

#include <QStandardItemModel>
#include <QStandardItem>

namespace GoldingsGym::Ptng {

/*!
 * \brief The AbstractReportSpec class
 *
 * Abstract base class for imported reports from supported penetration test tools. Inherits QStandardItemModel.
 *
 * \sa AbsatractItemSpec
 */
// TODO inherit QStandardItemModel
class AbstractReportSpec {
public:
    virtual QObject* ParseReportn(const QString& file) = 0;

};
} // End of namespace GoldingsGym::Ptng
