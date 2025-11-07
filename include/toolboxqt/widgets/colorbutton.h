#ifndef TBQ_WIDGETS_COLORBUTTON_H
#define TBQ_WIDGETS_COLORBUTTON_H

#include "toolboxqt/toolboxqt_global.h"

#include <QPushButton>

namespace tbq
{

class TOOLBOXQT_EXPORT ColorButton : public QPushButton
{
    Q_OBJECT

public:
    enum class ColorShape
    {
        COLOR_SHAPE_CIRCLE = 0,
        COLOR_SHAPE_RECT
    };
    Q_ENUM(ColorShape);
public:
    explicit ColorButton(QWidget *parent = nullptr);

public:
    ColorShape getShape() const;
    const QColor& getColor() const;

public:
    void setShape(ColorShape shape);
    void setColor(const QColor &color);

signals:
    void colorChanged(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void chooseColor();

private:
    ColorShape m_shape;
    QColor m_color;
};

} // namespace tbq

#endif // TBQ_WIDGETS_COLORBUTTON_H
