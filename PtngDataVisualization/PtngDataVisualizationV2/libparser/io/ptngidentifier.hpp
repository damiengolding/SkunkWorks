#pragma once
#include <QObject>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>
#include "../data/abstractreportspec.hpp"
#include "../data/abstractitemspec.hpp"
#include "../utils/ptngenums.hpp"

namespace GoldingsGym::Ptng {

/*!
 * \brief The PtngIdentifier class
 *
 * Provides a static function which attempts to identify the source tool for a given input file.
 *
 * \sa PtngEnums
 */
class PtngIdentifier : public QObject
{
    Q_OBJECT
public:
    explicit PtngIdentifier(QObject* parent = nullptr);
    virtual ~PtngIdentifier();

    friend QDebug operator<<(QDebug debug, const PtngIdentifier &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public:
    /*!
     * \brief checkFile
     * \param file
     * \return
     */
    static PtngEnums::SupportedInputType checkFile(const QString &file);
private:
    static PtngEnums::SupportedInputType checkXmlFile(const QString &file);
    static PtngEnums::SupportedInputType checkTextFile(const QString &file);
public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
