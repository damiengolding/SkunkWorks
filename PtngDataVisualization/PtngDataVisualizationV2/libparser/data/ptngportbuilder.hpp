#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractbuilder.hpp"

namespace GoldingsGym::Ptng {

/*!
 * \brief The PtngPortBuilder class
 *
 * Base class for building port items.
 *
 * \sa AbstractItemSpec
 * \sa PtngPortSpec
 */
class PtngPortBuilder : public QObject, public AbstractBuilder
{
    Q_OBJECT
public:
    explicit PtngPortBuilder(QObject* parent = nullptr);
    virtual ~PtngPortBuilder();

    friend QDebug operator<<(QDebug debug, const PtngPortBuilder &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
