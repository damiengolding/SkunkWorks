#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractitemspec.hpp"
namespace GoldingsGym::Ptng {
class PtngIPV4AddressSpec : public QObject, public AbstractItemSpec
{
    Q_OBJECT
public:
    explicit PtngIPV4AddressSpec(QObject* parent = nullptr);
    virtual ~PtngIPV4AddressSpec();

    friend QDebug operator<<(QDebug debug, const PtngIPV4AddressSpec &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
