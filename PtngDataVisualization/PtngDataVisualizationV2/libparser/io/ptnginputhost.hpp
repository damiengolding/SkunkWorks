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
class PtngInputHost : public QObject, public AbstractPtngInput
{
    Q_OBJECT
public:
    explicit PtngInputHost(QObject* parent = nullptr);
    virtual ~PtngInputHost();

    friend QDebug operator<<(QDebug debug, const PtngInputHost &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
