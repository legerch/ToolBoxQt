#include "labelanim.h"

#include <QMovie>

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

LabelAnim::LabelAnim(QWidget *parent)
    : QLabel(parent)
{
    /* Set members */
    m_anim = new QMovie(this);

    /* Set label attributes */
    setMovie(m_anim);

    setScaledContents(false);
    setAlignment(Qt::AlignCenter);
    setAttribute(Qt::WA_TranslucentBackground, true);

    connect(m_anim, &QMovie::frameChanged, this, &LabelAnim::updateMovieFrame);
}

void LabelAnim::setAnimation(const QString &animation)
{
    m_anim->setFileName(animation);
}

void LabelAnim::play()
{
    m_anim->start();
}

void LabelAnim::stop()
{
    m_anim->stop();
}

int LabelAnim::heightForWidth(int width) const
{
    const QPixmap pixmap = m_anim->currentPixmap();
    if(pixmap.isNull()) {
        return height();
    }

    return (pixmap.height() * width) / pixmap.width();
}

QSize LabelAnim::sizeHint() const
{
    const int sizeW = width();
    return QSize(sizeW, heightForWidth(sizeW));
}

void LabelAnim::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    updateMovieFrame();
}

void LabelAnim::updateMovieFrame()
{
    const QPixmap pixmap = m_anim->currentPixmap();
    if(pixmap.isNull()) {
        return;
    }

    QPixmap scaledPixmap = pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel::setPixmap(scaledPixmap);
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
