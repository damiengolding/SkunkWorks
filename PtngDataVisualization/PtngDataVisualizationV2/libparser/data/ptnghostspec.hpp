#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractitemspec.hpp"

namespace GoldingsGym::Ptng {

/*!
 * \brief The PtngHostSpec class
 *
 * Holds details for a single host or network (CIDR) in a report.
 *
 * \sa PtngHostBuilder
 * \sa AbstractReportSpec
 */
class PtngHostSpec : public QObject, public AbstractItemSpec
{
    Q_OBJECT
public:
    explicit PtngHostSpec(QObject* parent = nullptr);
    virtual ~PtngHostSpec();

    friend QDebug operator<<(QDebug debug, const PtngHostSpec &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
