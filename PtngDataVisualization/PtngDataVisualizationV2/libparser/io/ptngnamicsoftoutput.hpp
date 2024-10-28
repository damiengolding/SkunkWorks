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
#include "abstractptngoutput.hpp"
namespace GoldingsGym::Ptng {
class PtngNamicsoftOutput : public QObject, public AbstractPtngOutput
{
    Q_OBJECT
public:
    explicit PtngNamicsoftOutput(QObject* parent = nullptr);
    virtual ~PtngNamicsoftOutput();

    friend QDebug operator<<(QDebug debug, const PtngNamicsoftOutput &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
