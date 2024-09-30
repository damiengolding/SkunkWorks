#pragma once
#include <QObject>
#include <QDebug>
#include <QColor>
#include <QFont>
#include <QFile>
#include <QFileInfo>

namespace GoldingsGym::Ptng {

/*!
 * \brief The PtngStyleSheet class
 *
 * The StyleSheet class is used to provide a common source of configuration for colors, fonts etc.
 *
 * It is intended for use with classes that produce visual output, such as Graphviz dot runcontrol files.
 */
class PtngStyleSheet : public QObject
{
    Q_OBJECT
public:
    explicit PtngStyleSheet(QObject* parent = nullptr);
    virtual ~PtngStyleSheet();

    friend QDebug operator<<(QDebug debug, const PtngStyleSheet &c)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "";
        return debug;
    }

public:
    void LoadFromFile( const QString& file );
private:
    QColor m_criticalColor;
    QColor m_highColor;
    QColor m_mediumColor;
    QColor m_lowColor;
    QColor m_infoColor;
    QColor m_fillColor;
    QFont m_headingFont;
    QFont m_bodyFont;
    QFont m_codeFont;
public slots:

signals:

};
} // End of namespace GoldingsGym::Ptng
