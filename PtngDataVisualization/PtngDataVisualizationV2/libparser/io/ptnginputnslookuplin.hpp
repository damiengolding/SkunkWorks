#pragma once
#include <QObject>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include "../data/abstractreportspec.hpp"
#include "../data/abstractitemspec.hpp"
#include "../utils/ptngenums.hpp"
#include "abstractptnginput.hpp"
namespace GoldingsGym::Ptng {
class PtngInputNslookupLin : public QObject, public AbstractPtngInput
{
    Q_OBJECT
public:
    explicit PtngInputNslookupLin(QObject* parent = nullptr);
    virtual ~PtngInputNslookupLin();

    friend QDebug operator<<(QDebug debug, const PtngInputNslookupLin &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
