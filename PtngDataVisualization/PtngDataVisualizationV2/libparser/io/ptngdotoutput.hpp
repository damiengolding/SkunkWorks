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

/*!
 * \brief The PtngDotOutput class
 *
 * Generates a Graphviz .dot runcontrol file from network-based report specs.
 *
 * \sa AbstractReportSpec
 * \sa AbstractItemSpec
 */
class PtngDotOutput : public QObject, public AbstractPtngOutput
{
    Q_OBJECT
public:
    explicit PtngDotOutput(QObject* parent = nullptr);
    virtual ~PtngDotOutput();

    friend QDebug operator<<(QDebug debug, const PtngDotOutput &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
