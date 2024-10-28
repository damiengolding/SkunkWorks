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
 * \brief The AbstractPtngInput class
 *
 * Abstract base class for input parsers.
 */
class AbstractPtngInput {
public:
    /*!
     * \brief ParseReport
     * \param file
     * \return AbstractReportSpec*
     *
     * Pure virtual function, must be implemented for all derived classes.
     */
    virtual AbstractReportSpec* ParseReport(const QString& file) = 0;

};
} // End of namespace GoldingsGym::Ptng
