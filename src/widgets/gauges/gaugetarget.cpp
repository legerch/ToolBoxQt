#include "toolboxqt/widgets/gauges/gaugetarget.h"

#include <QPainter>

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::GaugeTargetStyle
 * \brief Allow to set style of a \c GaugeTarget widget.
 *
 * \sa GaugeTarget
 */

/*!
 * \class tbq::GaugeTarget
 * \brief A gauge used to determine how close we are from a target value.
 * \details
 * Allow to display a <em>tolerance zone</em>, where a valu is considered valid
 * while trying to be as close as possible of a target.
 *
 * \sa GaugeTargetStyle
 */

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

/*!
 * \brief Construct a gauge target style element
 * \details
 * Contains default style of a gauge target.
 *
 * \sa reset()
 */
GaugeTargetStyle::GaugeTargetStyle()
{
    reset();
}

/*!
 * \brief Retrieve color of a gauge element
 *
 * \param[in] idElement
 * Element ID to retrieve the color. \n
 * If unknown ID, color \c Qt::gray is returned.
 *
 * \return
 * Returns color associated to selected element.
 *
 * \sa setColor()
 * \sa getMargins(), getMarkFactor()
 */
QColor GaugeTargetStyle::getColor(GaugeElement idElement) const
{
    return m_mapColors.value(idElement, Qt::gray);
}

/*!
 * \brief Retrieve margins used by the gauge
 *
 * \return
 * Returns margins used by the gauge.
 *
 * \sa setMargins()
 * \sa getColor(), getMarkFactor()
 */
int GaugeTargetStyle::getMargins() const
{
    return m_margins;
}

/*!
 * \brief Retrieve factor used for cursors marks
 * \details
 * Mark correspond to cursors (current value, target, etc...). \n
 * The factor (coefficient) is used to determine the size used
 * by cursors
 *
 * \return
 * Returns factor used for marks elements.
 *
 * \sa setMarkFactor()
 * \sa getMargins(), getColor()
 */
double GaugeTargetStyle::getMarkFactor() const
{
    return m_markFactor;
}

/*!
 * \brief Reset style to default values
 */
void GaugeTargetStyle::reset()
{
    /* Set default color style */
    m_mapColors.insert(GAUGE_ZONE_BAR, QColor(80, 80, 80));
    m_mapColors.insert(GAUGE_ZONE_TOLERANCE, QColor(190, 190, 190));
    m_mapColors.insert(GAUGE_MARK_TARGET_CURSOR, QColor(56, 164, 255, 150));
    m_mapColors.insert(GAUGE_MARK_TARGET_TEXT, Qt::gray);
    m_mapColors.insert(GAUGE_MARK_VALUE_CURSOR_OK, Qt::green);
    m_mapColors.insert(GAUGE_MARK_VALUE_CURSOR_KO, Qt::red);
    m_mapColors.insert(GAUGE_MARK_VALUE_TEXT_OK, QColor(34, 139, 34));
    m_mapColors.insert(GAUGE_MARK_VALUE_TEXT_KO, Qt::red);
    Q_ASSERT(GAUGE_NB_ELEMENTS == m_mapColors.size());

    /* Set size properties */
    m_margins = 4;
    m_markFactor = 0.3;
}

/*!
 * \brief Use to set color of a gauge element.
 *
 * \param[in] idElement
 * Element ID for which to set the color
 * \param[in] color
 * Color to use.
 *
 * \sa getColor()
 * \sa setMargins(), setMarkFactor()
 */
void GaugeTargetStyle::setColor(GaugeElement idElement, const QColor &color)
{
    m_mapColors.insert(idElement, color);
}

/*!
 * \brief Use to set margins used by the gauge
 *
 * \param[in] margins
 * Margins to use in pixels. \n
 * If value is negative, margins will be set to \c 0.
 *
 * \sa getMargins()
 * \sa setColor(), setMarkFactor()
 */
void GaugeTargetStyle::setMargins(int margins)
{
    m_margins = std::max(0, margins);
}

/*!
 * \brief Retrieve factor used for cursors marks
 * \details
 * Mark correspond to cursors (current value, target, etc...). \n
 * The factor (coefficient) is used to determine the size used
 * by cursors
 *
 * \return
 * Returns factor used for marks elements.
 *
 * \sa setMarkFactor()
 * \sa getMargins(), getColor()
 */

/*!
 * \brief Set factor used for cursors marks.
 * \details
 * Mark correspond to cursors (current value, target, etc...). \n
 * The factor (coefficient) is used to determine the size used
 * by cursors.
 *
 * \param[in] factor
 * Factor coefficient to use for mark cursors. \n
 * Value will be clamped in range <b>[0.0 ; 10.0]</b>
 *
 * \sa getMarkFactor()
 * \sa setColor(), setMargins()
 */
void GaugeTargetStyle::setMarkFactor(double factor)
{
    m_markFactor = std::clamp(factor, 0.0, 10.0);
}

/*****************************/
/* Functions implementation  */
/*    Class GaugeTarget      */
/*****************************/

/*!
 * \brief Create a gauge target with their default values
 *
 * \param[in, out] parent
 * Parent widget.
 */
GaugeTarget::GaugeTarget(QWidget *parent)
    : QWidget{parent}
{}

/*!
 * \brief Use to know if current value is in tolerance
 * zone.
 *
 * \return
 * Returns \c true if current value is in tolerance zone.
 *
 * \sa setRange(), setTarget()
 * \sa setValue()
 */
bool GaugeTarget::isInTolerance() const
{
    return (m_value >= m_tolLow && m_value <= m_tolHigh);
}

/*!
 * \brief Retrieve gauge current style
 *
 * \return
 * Returns style associated to the gauge.
 *
 * \sa setStyle()
 */
GaugeTargetStyle GaugeTarget::getStyle() const
{
    return m_style;
}

/*!
 * \brief Use to set current value
 *
 * \param[in] value
 * Current value
 *
 * \sa setRange(), setTarget()
 */
void GaugeTarget::setValue(int value)
{
    m_value = value;
    updateProperties();
}

/*!
 * \brief Use to set range to display for the gauge
 * \details
 * The range corresponds to the all gauge.
 *
 * \param[in] min
 * Minimum range to use
 * \param[in] max
 * Maximum range to use
 *
 * \sa setTarget(), setValue()
 */
void GaugeTarget::setRange(int min, int max)
{
    m_min = min;
    m_max = max;

    updateProperties();
}

/*!
 * \brief Set the target value
 *
 * \param[in] target
 * Target value to use. \n
 * The goal is to be as close as possible
 * of this value
 * \param[in] tolerance
 * Tolerance value to use.
 *
 * \sa setRange(), setValue()
 */
void GaugeTarget::setTarget(int target, int tolerance)
{
    m_target = std::clamp(target, m_min, m_max);

    m_tolHigh = std::min(target + tolerance, m_max);
    m_tolLow = std::max(target - tolerance, m_min);

    updateProperties();
}

/*!
 * \overload
 *
 * \param[in] target
 * Target value to use. \n
 * The goal is to be as close as possible
 * of this value
 * \param[in] tolerance
 * Tolerance value to use.
 * \param[in] range
 * Range to use
 *
 * \sa setRange(), setValue()
 */
void GaugeTarget::setTarget(int target, int tolerance, int range)
{
    setRange(target - range, target + range);
    setTarget(target, tolerance);
}

/*!
 * \brief Set style of the gauge
 *
 * \param[in] style
 * Style to use on the gauge
 */
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
    const QRect zoneDraw = rect();

    const int margin = m_style.getMargins();

    /* Do the widget is enabled ? */
    if(!isEnabled()){
        painter.setOpacity(0.4);
    }

    /* Define bar zone */
    const int barHeight = zoneDraw.height() * 0.20;
    const int topLeft = height() * 0.5 - barHeight * 0.5;

    const QRect zoneBar(margin, topLeft, zoneDraw.width() - margin * 2, barHeight);
    const int cursorFactor = zoneBar.height() * m_style.getMarkFactor();

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

    painter.setPen(QPen(m_style.getColor(GaugeTargetStyle::GAUGE_MARK_TARGET_CURSOR), 2));
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

void GaugeTarget::updateProperties()
{
    /* Update tooltip informations */
    const QString tooltip = QString(tr("Current value: %1\nTarget: %2\nTolerance zone: [%3 ; %4]\nBar zone: [%5 ; %6]")).arg(
        QString::number(m_value), QString::number(m_target),
        QString::number(m_tolLow), QString::number(m_tolHigh),
        QString::number(m_min), QString::number(m_max)
    );
    setToolTip(tooltip);

    /* Call method used to refresh widget UI */
    update();
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
    posX = std::clamp(posX, zoneDraw.left(), zoneDraw.right() - txtSize.width());

    // Vertical
    int posY = 0;
    if(atTop){
        posY = mark.y1() - txtSize.height();
    }else{
        posY = mark.y2();
    }
    posY = std::clamp(posY, zoneDraw.top(), zoneDraw.bottom() - txtSize.height());

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
