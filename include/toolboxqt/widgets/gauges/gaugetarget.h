#ifndef TBQ_WIDGETS_GAUGETARGET_H
#define TBQ_WIDGETS_GAUGETARGET_H

#include "toolboxqt/toolboxqt_global.h"

#include <QWidget>

namespace tbq
{

class TOOLBOXQT_EXPORT GaugeTargetStyle
{
    Q_GADGET

public:
    enum GaugeElement
    {
        GAUGE_ZONE_BAR = 0,
        GAUGE_ZONE_TOLERANCE,
        GAUGE_MARK_TARGET_CURSOR,
        GAUGE_MARK_TARGET_TEXT,
        GAUGE_MARK_VALUE_CURSOR_OK,
        GAUGE_MARK_VALUE_CURSOR_KO,
        GAUGE_MARK_VALUE_TEXT_OK,
        GAUGE_MARK_VALUE_TEXT_KO,

        GAUGE_NB_ELEMENTS
    };
    Q_ENUM(GaugeElement)

public:
    GaugeTargetStyle();

public:
    QColor getColor(GaugeElement idElement) const;

public:
    void reset();

    void setColor(GaugeElement idElement, const QColor &color);

private:
    QHash<GaugeElement, QColor> m_mapColors;
};

class TOOLBOXQT_EXPORT GaugeTarget : public QWidget
{
    Q_OBJECT

public:
    explicit GaugeTarget(QWidget *parent = nullptr);

public:
    bool isInTolerance() const;
    GaugeTargetStyle getStyle() const;

public:
    void setValue(int value);

    void setRange(int min, int max);
    void setTarget(int target, int tolerance);
    void setTarget(int target, int tolerance, int range);

    void setStyle(const GaugeTargetStyle &style);

public:
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void updateProperties();
    int findPixelFromValue(const QRect &zoneDraw, int value) const;

    QRect calcZoneMarkText(const QFontMetrics &ftInfos, const QRect &zoneDraw, const QLine &mark, const QString &txt, bool atTop);

private:
    int m_value = 0;

    int m_min = 0;
    int m_max = 0;
    int m_tolLow = 0;
    int m_tolHigh = 0;
    int m_target = 0;

    GaugeTargetStyle m_style;
};

} // namespace tbq

#endif // TBQ_WIDGETS_GAUGETARGET_H
