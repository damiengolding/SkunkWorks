#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractitemspec.hpp"
namespace GoldingsGym::ptng {
class PtngIpV4AddressSpec : public QObject, public AbstractItemSpec
{
    Q_OBJECT
public:
    explicit PtngIpV4AddressSpec(QObject* parent = nullptr);
    virtual ~PtngIpV4AddressSpec();

    friend QDebug operator<<(QDebug debug, const PtngIpV4AddressSpec &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::ptng
