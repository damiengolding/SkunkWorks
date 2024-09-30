#pragma once
#include <QObject>
#include <QDebug>
#include <QColor>
#include <QFont>
#include <QFile>
#include <QFileInfo>

#include "../inc/libparser_global.hpp"

namespace GoldingsGym::Ptng {

/*!
 * \brief The PtngStyleSheet class
 *
 * The StyleSheet class is used to provide a common source of configuration for colors, fonts etc.
 *
 * It is intended for use with classes that produce visual output, such as Graphviz dot runcontrol files.
 */
class LIBPARSER_EXPORT PtngStyleSheet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor criticalColor READ criticalColor WRITE setCriticalColor NOTIFY criticalColorChanged FINAL)
    Q_PROPERTY(QColor highColor READ highColor WRITE setHighColor NOTIFY highColorChanged FINAL)
    Q_PROPERTY(QColor mediumColor READ mediumColor WRITE setMediumColor NOTIFY mediumColorChanged FINAL)
    Q_PROPERTY(QColor lowColor READ lowColor WRITE setLowColor NOTIFY lowColorChanged FINAL)
    Q_PROPERTY(QColor infoColor READ infoColor WRITE setInfoColor NOTIFY infoColorChanged FINAL)
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged FINAL)
    Q_PROPERTY(QFont headingFont READ headingFont WRITE setHeadingFont NOTIFY headingFontChanged FINAL)
    Q_PROPERTY(QFont bodyFont READ bodyFont WRITE setBodyFont NOTIFY bodyFontChanged FINAL)
    Q_PROPERTY(QFont codeFont READ codeFont WRITE setCodeFont NOTIFY codeFontChanged FINAL)

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
    /*!
     * \brief LoadFromFile
     * \param file
     *
     * Load fonts and colors from a text file with name = value pairs. Default contents are as follows:
     *
     *      CriticalColor = #bc4543
     *      HighColor = #d66a23
     *      MediumColor = #afe196
     *      LowColor = #f1e897
     *      InfoColor = #75a0c6
     *      FillColor = #b3c4af
     *      HeadingFont = "Open Sans",22
     *      BodyFont = "Source Sans Pro",12
     *      CodeFont = "JetBrains Mono",12
     */
    void LoadFromFile( const QString& file );
    QColor criticalColor() const;
    void setCriticalColor(const QColor &newCriticalColor);
    QColor highColor() const;
    void setHighColor(const QColor &newHighColor);
    QColor mediumColor() const;
    void setMediumColor(const QColor &newMediumColor);
    QColor lowColor() const;
    void setLowColor(const QColor &newLowColor);
    QColor infoColor() const;
    void setInfoColor(const QColor &newInfoColor);
    QColor fillColor() const;
    void setFillColor(const QColor &newFillColor);
    QFont headingFont() const;
    void setHeadingFont(const QFont &newHeadingFont);
    QFont bodyFont() const;
    void setBodyFont(const QFont &newBodyFont);
    QFont codeFont() const;
    void setCodeFont(const QFont &newCodeFont);

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

    void criticalColorChanged();
    void highColorChanged();
    void mediumColorChanged();
    void lowColorChanged();
    void infoColorChanged();
    void fillColorChanged();
    void headingFontChanged();
    void bodyFontChanged();
    void codeFontChanged();
};
} // End of namespace GoldingsGym::Ptng
