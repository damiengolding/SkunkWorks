#pragma once

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include "../data/abstractreportspec.hpp"
#include "../data/abstractitemspec.hpp"
#include "../utils/ptngenums.hpp"

namespace GoldingsGym::Ptng {

/*!
 * \brief The AbstractPtngOutput class
 *
 * Abstract base class for output generators.
 */
class AbstractPtngOutput {
public:
    virtual qint64 Write( QStandardItemModel* model, const QString& file, bool& ok) = 0;

};
} // End of namespace GoldingsGym::Ptng
