#include "ptngstylesheet.hpp"

namespace GoldingsGym::Ptng {

PtngStyleSheet::PtngStyleSheet(QObject *parent)
    : QObject{parent}
{

}

PtngStyleSheet::~PtngStyleSheet()
{

}

void PtngStyleSheet::LoadFromFile(const QString &file)
{

}

#pragma Accessors and mutators {

QColor PtngStyleSheet::criticalColor() const
{
    return m_criticalColor;
}

void PtngStyleSheet::setCriticalColor(const QColor &newCriticalColor)
{
    if (m_criticalColor == newCriticalColor)
        return;
    m_criticalColor = newCriticalColor;
    emit criticalColorChanged();
}

QColor PtngStyleSheet::highColor() const
{
    return m_highColor;
}

void PtngStyleSheet::setHighColor(const QColor &newHighColor)
{
    if (m_highColor == newHighColor)
        return;
    m_highColor = newHighColor;
    emit highColorChanged();
}

QColor PtngStyleSheet::mediumColor() const
{
    return m_mediumColor;
}

void PtngStyleSheet::setMediumColor(const QColor &newMediumColor)
{
    if (m_mediumColor == newMediumColor)
        return;
    m_mediumColor = newMediumColor;
    emit mediumColorChanged();
}

QColor PtngStyleSheet::lowColor() const
{
    return m_lowColor;
}

void PtngStyleSheet::setLowColor(const QColor &newLowColor)
{
    if (m_lowColor == newLowColor)
        return;
    m_lowColor = newLowColor;
    emit lowColorChanged();
}

QColor PtngStyleSheet::infoColor() const
{
    return m_infoColor;
}

void PtngStyleSheet::setInfoColor(const QColor &newInfoColor)
{
    if (m_infoColor == newInfoColor)
        return;
    m_infoColor = newInfoColor;
    emit infoColorChanged();
}

QColor PtngStyleSheet::fillColor() const
{
    return m_fillColor;
}

void PtngStyleSheet::setFillColor(const QColor &newFillColor)
{
    if (m_fillColor == newFillColor)
        return;
    m_fillColor = newFillColor;
    emit fillColorChanged();
}

QFont PtngStyleSheet::headingFont() const
{
    return m_headingFont;
}

void PtngStyleSheet::setHeadingFont(const QFont &newHeadingFont)
{
    if (m_headingFont == newHeadingFont)
        return;
    m_headingFont = newHeadingFont;
    emit headingFontChanged();
}

QFont PtngStyleSheet::bodyFont() const
{
    return m_bodyFont;
}

void PtngStyleSheet::setBodyFont(const QFont &newBodyFont)
{
    if (m_bodyFont == newBodyFont)
        return;
    m_bodyFont = newBodyFont;
    emit bodyFontChanged();
}

QFont PtngStyleSheet::codeFont() const
{
    return m_codeFont;
}

void PtngStyleSheet::setCodeFont(const QFont &newCodeFont)
{
    if (m_codeFont == newCodeFont)
        return;
    m_codeFont = newCodeFont;
    emit codeFontChanged();
}

#pragma Accessors and mutators }

} // End of namespace GoldingsGym::Ptng
