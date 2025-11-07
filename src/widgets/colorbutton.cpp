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
    m_color(Qt::white)
{
    connect(this, &QPushButton::clicked, this, &ColorButton::chooseColor);
}

const QColor &ColorButton::getColor() const
{
    return m_color;
}

void ColorButton::setColor(const QColor &color)
{
    /* Verify color validity */
    if(!color.isValid()){
        return;
    }

    /* Do color differs */
    if(color == color){
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

    /* Draw button */
    QStyleOptionButton option;
    initStyleOption(&option);

    style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);

    /* Set color "pastille" properties */
    // Size
    const int diameter = height() * 0.8;    // 80 % of the button height

    // Alignment
    int x = (width() - diameter) / 2;       // Center it horizontally
    int y = (height() - diameter) / 2;      // Center it vertically

    QRect rect(x, y, diameter, diameter);

    /* Draw the color */
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::gray);
    painter.setBrush(m_color);
    painter.drawEllipse(rect);
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
