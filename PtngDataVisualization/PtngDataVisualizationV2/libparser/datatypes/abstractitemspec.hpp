#pragma once

#include <QStandardItemModel>
#include <QStandardItem>

namespace GoldingsGym::ptng {
class AbstractItemSpec {
public:
    virtual int LoadFromScanEntry(const QString& entry) = 0;

};
} // End of namespace GoldingsGym::ptng
