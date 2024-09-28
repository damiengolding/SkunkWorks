#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractscanspec.hpp"
namespace GoldingsGym::ptng {
class PtngNessusScan : public QObject, public AbstractScanSpec
{
    Q_OBJECT
public:
    explicit PtngNessusScan(QObject* parent = nullptr);
    virtual ~PtngNessusScan();

    friend QDebug operator<<(QDebug debug, const PtngNessusScan &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::ptng
