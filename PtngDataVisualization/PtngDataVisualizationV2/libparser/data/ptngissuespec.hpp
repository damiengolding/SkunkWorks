#pragma once
#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <QStandardItem>
#include "abstractitemspec.hpp"
namespace GoldingsGym::Ptng {
class PtngIssueSpec : public QObject, public AbstractItemSpec
{
    Q_OBJECT
public:
    explicit PtngIssueSpec(QObject* parent = nullptr);
    virtual ~PtngIssueSpec();

    friend QDebug operator<<(QDebug debug, const PtngIssueSpec &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
