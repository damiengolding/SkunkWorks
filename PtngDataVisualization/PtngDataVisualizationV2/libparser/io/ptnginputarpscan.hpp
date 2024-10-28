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

/*!
 * \brief The PtngInputArpScan class
 *
 * ArpScan report parser.
 */
class PtngInputArpScan : public QObject, public AbstractPtngInput
{
    Q_OBJECT
public:
    explicit PtngInputArpScan(QObject* parent = nullptr);
    virtual ~PtngInputArpScan();

    friend QDebug operator<<(QDebug debug, const PtngInputArpScan &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
