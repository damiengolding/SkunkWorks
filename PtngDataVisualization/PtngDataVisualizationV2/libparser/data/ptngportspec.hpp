#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractitemspec.hpp"
namespace GoldingsGym::Ptng {
class PtngPortSpec : public QObject, public AbstractItemSpec
{
    Q_OBJECT
public:
    explicit PtngPortSpec(QObject* parent = nullptr);
    virtual ~PtngPortSpec();

    friend QDebug operator<<(QDebug debug, const PtngPortSpec &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
