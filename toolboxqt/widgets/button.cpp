#include "button.h"

#include <QTimer>

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::BtnAbstractWordWrap
 * \brief Virtual class implementing wordwrap for buttons
 * \details
 * Include with:
 * \code{.cpp}
 * #include "toolboxqt/widgets/labelimg.h"
 * \endcode
 * Qt button classes doesn't allow to wordwrap text when button size is not enough
 * (even when layout space allow it!). This class will manage this issue and
 * properly use the available space.
 *
 * \sa tbq::BtnPush, tbq::BtnTool
 */

/*!
 * \class tbq::BtnTool
 * \brief Custom QToolButton implementing wordwrap
 * \details
 * Include with:
 * \code{.cpp}
 * #include "toolboxqt/widgets/button.h"
 * \endcode
 *
 * \sa tbq::BtnAbstractWordWrap
 * \sa tbq::BtnPush
 */

/*!
 * \class tbq::BtnPush
 * \brief Custom QPushButton implementing wordwrap
 * \details
 * Include with:
 * \code{.cpp}
 * #include "toolboxqt/widgets/button.h"
 * \endcode
 *
 * \sa tbq::BtnTool
 * \sa tbq::BtnAbstractWordWrap
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
/*    BtnAbstractWordWrap    */
/*****************************/

BtnAbstractWordWrap::BtnAbstractWordWrap()
    : m_padding(0)
{
    /* Nothing to do */
}

/*!
 * \brief Use to set button text
 *
 * \param[in] text
 * Text to display inside the button.
 */
void BtnAbstractWordWrap::setTextWordWrap(const QString &text)
{
    m_text = text;
    performRefresh();
}

/*!
 * \brief Set padding to use inside button
 *
 * \param[in] padding
 * Padding to use. \n
 * By default, padding is set to \c 0.
 *
 * \sa getPadding()
 */
void BtnAbstractWordWrap::setPadding(int padding)
{
    m_padding = padding;
    performRefresh();
}

/*!
 * \brief Get button text
 *
 * \return
 * Returns reference to button text.
 *
 * \sa setTextWordWrap()
 */
const QString& BtnAbstractWordWrap::getText() const
{
    return m_text;
}

/*!
 * \brief Get current padding to use
 * \return
 * Return current padding.
 *
 * \sa setPadding()
 */
int BtnAbstractWordWrap::getPadding() const
{
    return m_padding;
}

void BtnAbstractWordWrap::paintTextWordWrap(QPainter *painter, const QRect &rect)
{
    const QRect txtRect = rect.adjusted(m_padding, m_padding, -m_padding, -m_padding);
    painter->drawText(txtRect, Qt::TextWordWrap | Qt::AlignCenter, m_text);
}

QSize BtnAbstractWordWrap::calcSizeHintWordWrap(const QFontMetrics &fm, int width) const
{
    const QRect txtBoundRect = fm.boundingRect(QRect(0, 0, width - 2 * m_padding, 0), Qt::TextWordWrap, m_text);
    return QSize(txtBoundRect.width() + 2 * m_padding, txtBoundRect.height() + 2 * m_padding);
}

void BtnAbstractWordWrap::performRefresh()
{
    updateGeometryBtn();
    updateBtn();
}

/*****************************/
/* Functions implementation  */
/*         BtnTool           */
/*****************************/

BtnTool::BtnTool(QWidget *parent)
    : BtnTool(QString(), 0, parent)
{
    /* Nothing to do */
}

BtnTool::BtnTool(const QString &text, int padding, QWidget *parent)
    : QToolButton(parent)
{
    setText(text);
    setPadding(padding);
}

/*!
 * \overload
 * \brief Use to set text of button
 * \details
 * This method is an overload, which simply call
 * \c setTextWordWrap method.
 *
 * \param[in] text
 * Text to display inside the button.
 *
 * \sa getText()
 */
void BtnTool::setText(const QString &text)
{
    setTextWordWrap(text);
}

void BtnTool::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);
    QPainter painter(this);

    paintTextWordWrap(&painter, rect());
}

QSize BtnTool::sizeHint() const
{
    QFontMetrics fm = fontMetrics();
    return calcSizeHintWordWrap(fm, width());
}

QSize BtnTool::minimumSizeHint() const
{
    return sizeHint();
}

void BtnTool::updateGeometryBtn()
{
    QToolButton::updateGeometry();
}

void BtnTool::updateBtn()
{
    QToolButton::update();
}

/*****************************/
/* Functions implementation  */
/*         BtnPush           */
/*****************************/

BtnPush::BtnPush(QWidget *parent)
    : BtnPush(QString(), 0, parent)
{
    /* Nothing to do */
}

BtnPush::BtnPush(const QString &text, int padding, QWidget *parent)
    : QPushButton(parent)
{
    setText(text);
    setPadding(padding);
}

/*!
 * \overload
 * \brief Use to set text of button
 * \details
 * This method is an overload, which simply call
 * \c setTextWordWrap method.
 *
 * \param[in] text
 * Text to display inside the button.
 *
 * \sa getText()
 */
void BtnPush::setText(const QString &text)
{
    setTextWordWrap(text);
}

//TODO: doc (milliseconds)
//TODO: doc (tell about "clicked" signal still available or simple if we want to be sure)
void BtnPush::setTimeDoubleClick(int interval)
{
    /* Do double click timer is defined ? */
    if(!m_timerDblClk){
        m_timerDblClk = new QTimer(this); // Using "this" as parent, object will be automatically destroyed
        m_timerDblClk->setSingleShot(true);

        connect(this, &QPushButton::clicked, this, &BtnPush::eventIsClicked);
        connect(m_timerDblClk, &QTimer::timeout, this, &BtnPush::eventTimeoutDblClk);
    }

    /* Set double click timer interval */
    m_timerDblClk->setInterval(interval);
}

void BtnPush::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    QPainter painter(this);

    paintTextWordWrap(&painter, rect());
}

QSize BtnPush::sizeHint() const
{
    QFontMetrics fm = fontMetrics();
    return calcSizeHintWordWrap(fm, width());
}

QSize BtnPush::minimumSizeHint() const
{
    return sizeHint();
}

void BtnPush::updateGeometryBtn()
{
    QPushButton::updateGeometry();
}

void BtnPush::updateBtn()
{
    QPushButton::update();
}

void BtnPush::eventIsClicked()
{
    /* Did first click already been fired ? */
    if(m_timerDblClk->isActive()){
        m_timerDblClk->stop();
        emit sClickedDouble();

    }else{
        m_timerDblClk->start();
    }
}

void BtnPush::eventTimeoutDblClk()
{
    emit sClickedSimple();
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
