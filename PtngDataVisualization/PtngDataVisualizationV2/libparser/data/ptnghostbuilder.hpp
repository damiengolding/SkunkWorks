#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractbuilder.hpp"

namespace GoldingsGym::Ptng {

/*!
 * \brief The PtngHostBuilder class
 *
 * Base class for building host items.
 *
 * \sa AbstractItemSpec
 * \sa PtngHostSpec
 */
class PtngHostBuilder : public QObject, public AbstractBuilder
{
    Q_OBJECT
public:
    explicit PtngHostBuilder(QObject* parent = nullptr);
    virtual ~PtngHostBuilder();

    friend QDebug operator<<(QDebug debug, const PtngHostBuilder &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
