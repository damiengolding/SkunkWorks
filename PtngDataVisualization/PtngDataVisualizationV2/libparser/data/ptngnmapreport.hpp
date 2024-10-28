#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractreportspec.hpp"
namespace GoldingsGym::Ptng {
class PtngNmapReport : public QObject, public AbstractReportSpec
{
    Q_OBJECT
public:
    explicit PtngNmapReport(QObject* parent = nullptr);
    virtual ~PtngNmapReport();

    friend QDebug operator<<(QDebug debug, const PtngNmapReport &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
