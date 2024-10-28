#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractbuilder.hpp"

namespace GoldingsGym::Ptng {

/*!
 * \brief The PtngIssueBuilder class
 *
 * Base class for building issue items.
 *
 * \sa AbstractItemSpec
 * \sa PtngIssueSpec
 */
class PtngIssueBuilder : public QObject, public AbstractBuilder
{
    Q_OBJECT
public:
    explicit PtngIssueBuilder(QObject* parent = nullptr);
    virtual ~PtngIssueBuilder();

    friend QDebug operator<<(QDebug debug, const PtngIssueBuilder &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
