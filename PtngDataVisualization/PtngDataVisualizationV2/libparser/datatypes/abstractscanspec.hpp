#pragma once

#include <QStandardItemModel>
#include <QStandardItem>

namespace GoldingsGym::ptng {
class AbstractScanSpec {
public:
    virtual QObject* ParseScan(const QString& file) = 0;

};
} // End of namespace GoldingsGym::ptng
