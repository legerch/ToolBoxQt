#include "button.h"

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
/*    BtnAbstractWordWrap    */
/*****************************/

BtnAbstractWordWrap::BtnAbstractWordWrap()
    : m_padding(0)
{
    /* Nothing to do */
}

void BtnAbstractWordWrap::setTextWordWrap(const QString &text)
{
    m_text = text;
    performRefresh();
}

void BtnAbstractWordWrap::setPadding(int padding)
{
    m_padding = padding;
    performRefresh();
}

const QString& BtnAbstractWordWrap::getText() const
{
    return m_text;
}

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

void BtnPush::setText(const QString &text)
{
    setTextWordWrap(text);
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

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
