#include "toolboxqt/widgets/colorbutton.h"

#include <QColorDialog>
#include <QPainter>
#include <QStyleOptionButton>

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::ColorButton
 * \brief Button used to pick a color
 * \details
 * Include with:
 * \code{.cpp}
 * #include "toolboxqt/widgets/colorbutton.h"
 * \endcode
 *
 * Create a button that allow to pick a color when
 * clicking on it and display the selected color
 */

/*****************************/
/* Signals documentations    */
/*****************************/

/*!
 * \fn tbq::ColorButton::sColorChanged()
 * \brief Signal emitted when new color has been selected.
 *
 * \sa getColor(), setColor()
 */

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

/*!
 * \brief Create default color button
 * \details
 * By default, \em shape is set to \c ColorShape::COLOR_SHAPE_RECT
 * and \em color to \c Qt::white.
 *
 * \param[in, out] parent
 * Parent widget.
 */
ColorButton::ColorButton(QWidget *parent) :
    QPushButton(parent),
    m_shape(ColorShape::COLOR_SHAPE_RECT)
{
    setColor(Qt::white);
    connect(this, &QPushButton::clicked, this, &ColorButton::chooseColor);
}

/*!
 * \brief Use to get button current shape
 * \return
 * Returns shape of the button
 *
 * \sa setShape()
 */
ColorButton::ColorShape ColorButton::getShape() const
{
    return m_shape;
}

/*!
 * \brief Use to get selected color
 * \return
 * Returns currently selected color
 *
 * \sa setColor()
 */
const QColor &ColorButton::getColor() const
{
    return m_color;
}

/*!
 * \brief Use to set button shape
 *
 * \param[in] shape
 * Shape to use.
 *
 * \sa getShape()
 */
void ColorButton::setShape(ColorShape shape)
{
    m_shape = shape;
}

/*!
 * \brief Use to set selected color.
 * \details
 * Allow to manually set selected color
 * which will update displayed color
 * and related tooltip button.
 *
 * \param[in] color
 * Color to set. \n
 * If invalid or same as already selected,
 * nothing is performed.
 *
 * \sa getColor()
 * \sa colorChanged()
 */
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
    setToolTip(m_color.name().toUpper());

    emit sColorChanged(m_color);
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

/*!
 * \brief Use to pick a color
 * \details
 * Trigger color picker window.
 */
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
