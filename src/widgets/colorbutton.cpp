#include "toolboxqt/widgets/colorbutton.h"

#include <QColorDialog>
#include <QPainter>
#include <QStyleOptionButton>

/*****************************/
/* Class documentations      */
/*****************************/

/*****************************/
/* Macro definitions         */
/*****************************/

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
/*         Class             */
/*****************************/

ColorButton::ColorButton(QWidget *parent) :
    QPushButton(parent),
    m_shape(ColorShape::COLOR_SHAPE_RECT), m_color(Qt::white)
{
    connect(this, &QPushButton::clicked, this, &ColorButton::chooseColor);
}

ColorButton::ColorShape ColorButton::getShape() const
{
    return m_shape;
}

const QColor &ColorButton::getColor() const
{
    return m_color;
}

void ColorButton::setShape(ColorShape shape)
{
    m_shape = shape;
}

void ColorButton::setColor(const QColor &color)
{
    /* Verify color validity */
    if(!color.isValid()){
        return;
    }

    /* Do color differs */
    if(m_color == color){
        return;
    }

    /* Perform color change */
    m_color = color;
    update();

    emit colorChanged(m_color);
}

void ColorButton::paintEvent(TOOLBOXQT_VAR_UNUSED QPaintEvent *event)
{
    QPainter painter(this);

    /* Draw base button */
    QStyleOptionButton option;
    initStyleOption(&option);

    style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);

    /* Set painter properties */
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::gray);
    painter.setBrush(m_color);

    /* Draw the color */
    switch(m_shape)
    {
        case ColorShape::COLOR_SHAPE_CIRCLE:{
            const int diameter = height() * 0.8;        // 80 % of the button height

            const int x = (width() - diameter) / 2;     // Center it horizontally
            const int y = (height() - diameter) / 2;    // Center it vertically

            const QRect rect(x, y, diameter, diameter);
            painter.drawEllipse(rect);
        }break;

        case ColorShape::COLOR_SHAPE_RECT:{
            const QRect rect = this->rect().adjusted(2, 2, -2, -2); // Give small margins
            painter.drawRect(rect);
        }break;

        default: break;
    }
}

void ColorButton::chooseColor()
{
    const QColor newColor = QColorDialog::getColor(m_color, this, tr("Select color"));
    if(newColor.isValid()){
        setColor(newColor);
    }
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
