#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractbuilder.hpp"

namespace GoldingsGym::Ptng {

/*!
 * \brief The PtngIPV4AddressBuilder class
 *
 * Base class for building IP V4 address items.
 *
 * \sa AbstractItemSpec
 * \sa PtngIPV4AddressSpec
 */
class PtngIPV4AddressBuilder : public QObject, public AbstractBuilder
{
    Q_OBJECT
public:
    explicit PtngIPV4AddressBuilder(QObject* parent = nullptr);
    virtual ~PtngIPV4AddressBuilder();

    friend QDebug operator<<(QDebug debug, const PtngIPV4AddressBuilder &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
