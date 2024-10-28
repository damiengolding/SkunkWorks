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
 * \brief The PtngDgmlOutput class
 *
 * Generates a Directed GraphMarkup Language (DGML) file from network-based report specs.
 *
 * \sa AbstractReportSpec
 * \sa AbstractItemSpec
 */
class PtngDgmlOutput : public QObject, public AbstractPtngOutput
{
    Q_OBJECT
public:
    explicit PtngDgmlOutput(QObject* parent = nullptr);
    virtual ~PtngDgmlOutput();

    friend QDebug operator<<(QDebug debug, const PtngDgmlOutput &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
