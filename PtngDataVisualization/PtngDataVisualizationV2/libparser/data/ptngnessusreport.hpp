#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractreportspec.hpp"
namespace GoldingsGym::Ptng {
class PtngNessusReport : public QObject, public AbstractReportSpec
{
    Q_OBJECT
public:
    explicit PtngNessusReport(QObject* parent = nullptr);
    virtual ~PtngNessusReport();

    friend QDebug operator<<(QDebug debug, const PtngNessusReport &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
