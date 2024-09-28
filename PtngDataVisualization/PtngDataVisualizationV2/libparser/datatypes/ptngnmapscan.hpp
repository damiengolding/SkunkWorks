#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractscanspec.hpp"
namespace GoldingsGym::ptng {
class PtngNmapScan : public QObject, public AbstractScanSpec
{
    Q_OBJECT
public:
    explicit PtngNmapScan(QObject* parent = nullptr);
    virtual ~PtngNmapScan();

    friend QDebug operator<<(QDebug debug, const PtngNmapScan &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::ptng
