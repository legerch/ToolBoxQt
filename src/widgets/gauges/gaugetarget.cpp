#include "toolboxqt/widgets/gauges/gaugetarget.h"

#include <QPainter>

/*****************************/
/* Class documentations      */
/*****************************/

/*****************************/
/* Signals documentations    */
/*****************************/

/*****************************/
/* Macro definitions         */
/*****************************/

#define DEBUG_DRAW_ZONE 0

/*****************************/
/* Start namespace           */
/*****************************/

namespace tbq
{

/*****************************/
/* Constants defintitions    */
/*****************************/

/*****************************/
/* Functions implementation  */
/*  Class GaugeTargetStyle   */
/*****************************/

GaugeTargetStyle::GaugeTargetStyle()
{
    reset();
}

QColor GaugeTargetStyle::getColor(GaugeElement idElement) const
{
    return m_mapColors.value(idElement, Qt::gray);
}

void GaugeTargetStyle::reset()
{
    m_mapColors.insert(GAUGE_ZONE_BAR, QColor(80, 80, 80));
    m_mapColors.insert(GAUGE_ZONE_TOLERANCE, QColor(190, 190, 190));
    m_mapColors.insert(GAUGE_MARK_TARGET_CURSOR, QColor(56, 164, 255));
    m_mapColors.insert(GAUGE_MARK_TARGET_TEXT, Qt::gray);
    m_mapColors.insert(GAUGE_MARK_VALUE_CURSOR_OK, Qt::green);
    m_mapColors.insert(GAUGE_MARK_VALUE_CURSOR_KO, Qt::red);
    m_mapColors.insert(GAUGE_MARK_VALUE_TEXT_OK, QColor(34, 139, 34));
    m_mapColors.insert(GAUGE_MARK_VALUE_TEXT_KO, Qt::red);

    Q_ASSERT(GAUGE_NB_ELEMENTS == m_mapColors.size());
}

void GaugeTargetStyle::setColor(GaugeElement idElement, const QColor &color)
{
    m_mapColors.insert(idElement, color);
}

/*****************************/
/* Functions implementation  */
/*    Class GaugeTarget      */
/*****************************/

GaugeTarget::GaugeTarget(QWidget *parent)
    : QWidget{parent}
{}

bool GaugeTarget::isInTolerance() const
{
    return (m_value >= m_tolLow && m_value <= m_tolHigh);
}

GaugeTargetStyle GaugeTarget::getStyle() const
{
    return m_style;
}

void GaugeTarget::setValue(int value)
{
    m_value = value;
    update();
}

void GaugeTarget::setRange(int min, int max)
{
    m_min = min;
    m_max = max;

    update();
}

void GaugeTarget::setTarget(int target, int tolerance)
{
    m_target = std::clamp(target, m_min, m_max);

    m_tolHigh = std::min(target + tolerance, m_max);
    m_tolLow = std::max(target - tolerance, m_min);

    update();
}

void GaugeTarget::setTarget(int target, int tolerance, int range)
{
    setRange(target - range, target + range);
    setTarget(target, tolerance);
}

void GaugeTarget::setStyle(const GaugeTargetStyle &style)
{
    m_style = style;
}

QSize GaugeTarget::sizeHint() const
{
    return QSize(180, 60);
}

void GaugeTarget::paintEvent(TOOLBOXQT_VAR_UNUSED QPaintEvent *event)
{
    const bool isValid = isInTolerance();

    /* Set painter properties */
    QPainter painter(this);
    painter.setFont(font());
    painter.setRenderHint(QPainter::Antialiasing);

    const QFontMetrics fontInfos(painter.font());
    const QRect zoneDraw(0, 0, width(), height());

    constexpr int margin = 4;

    /* Define bar zone */
    const int barHeight = zoneDraw.height() * 0.20;
    const int topLeft = height() * 0.5 - barHeight * 0.5;

    const QRect zoneBar(margin, topLeft, zoneDraw.width() - margin * 2, barHeight);
    const int cursorFactor = zoneBar.height() * 0.375;

    /* Define tolerance zone */
    const int pixTolLow = findPixelFromValue(zoneBar, m_tolLow);
    const int pixTolHigh = findPixelFromValue(zoneBar, m_tolHigh);
    const QRect zoneTol(pixTolLow, zoneBar.top(), pixTolHigh - pixTolLow, zoneBar.height());

    /* Draw background */
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_style.getColor(GaugeTargetStyle::GAUGE_ZONE_BAR));
    painter.drawRoundedRect(zoneBar, 4, 4);

    /* Draw tolerance */
    painter.setBrush(m_style.getColor(GaugeTargetStyle::GAUGE_ZONE_TOLERANCE));
    painter.drawRoundedRect(zoneTol, 4, 4);

    /* Draw center mark */
    // Mark
    const int pixTarget = findPixelFromValue(zoneBar, m_target);
    const QLine markTarget(pixTarget, zoneBar.top() - cursorFactor, pixTarget, zoneBar.bottom() + cursorFactor);

    painter.setPen(QPen(m_style.getColor(GaugeTargetStyle::GAUGE_MARK_TARGET_CURSOR), 2, Qt::DotLine));
    painter.drawLine(markTarget);

    // Text
    const QString txtTarget = QString::number(m_target);
    const QRect zoneTxtTarget = calcZoneMarkText(fontInfos, zoneDraw, markTarget, txtTarget, false);

    painter.setPen(m_style.getColor(GaugeTargetStyle::GAUGE_MARK_TARGET_TEXT));
    painter.drawText(zoneTxtTarget, Qt::AlignCenter, txtTarget);

    /* Draw cursor */
    // Mark
    const int pixValue = findPixelFromValue(zoneBar, std::clamp(m_value, m_min, m_max));
    const QLine markValue(pixValue, zoneBar.top() - cursorFactor, pixValue, zoneBar.bottom() + cursorFactor);

    painter.setPen(QPen(isValid ? m_style.getColor(GaugeTargetStyle::GAUGE_MARK_VALUE_CURSOR_OK) : m_style.getColor(GaugeTargetStyle::GAUGE_MARK_VALUE_CURSOR_KO), 2));
    painter.drawLine(markValue);

    // Text
    const QString txtValue = QString::number(m_value);
    const QRect zoneTxtValue = calcZoneMarkText(fontInfos, zoneDraw, markValue, txtValue, true);

    painter.setPen(QPen(isValid ? m_style.getColor(GaugeTargetStyle::GAUGE_MARK_VALUE_TEXT_OK) : m_style.getColor(GaugeTargetStyle::GAUGE_MARK_VALUE_TEXT_KO)));
    painter.drawText(zoneTxtValue, Qt::AlignCenter, txtValue);

    /* Debug zones to draw */
#if DEBUG_DRAW_ZONE
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::red));
    painter.drawRect(zoneDraw);

    painter.setPen(QPen(Qt::magenta));
    painter.drawRect(zoneTxtValue);
    painter.drawRect(zoneTxtTarget);

    qDebug() << "Gauge cursor zone: " << zoneDraw << "(zone-bar: " << zoneBar << ")";
#endif
}

int GaugeTarget::findPixelFromValue(const QRect &zoneDraw, int value) const
{
    const double range = m_max - m_min;
    const double pixel = zoneDraw.left() + (value - m_min) * zoneDraw.width() / range;

    return static_cast<int>(pixel);
}

QRect GaugeTarget::calcZoneMarkText(const QFontMetrics &ftInfos, const QRect &zoneDraw, const QLine &mark, const QString &txt, bool atTop)
{
    /* Define text properties */
    const QSize txtSize = ftInfos.size(Qt::TextSingleLine, txt);

    /* Determinate coordinates */
    // Horizontal
    int posX = mark.x1() - txtSize.width() * 0.5;
    posX = std::max(posX, zoneDraw.x());

    // Vertical
    int posY = 0;
    if(atTop){
        posY = zoneDraw.top();
    }else{
        posY = zoneDraw.bottom() - txtSize.height();
    }

    /* Create text zone */
    return QRect(posX, posY, txtSize.width(), txtSize.height());
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
