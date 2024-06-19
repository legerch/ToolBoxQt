#include "labelimg.h"

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

LabelImg::LabelImg(QWidget *parent)
{
    setScaledContents(false);
    setAlignment(Qt::AlignCenter);

    setTextAlt("No available image");
}

QPixmap LabelImg::getPixmapScaled() const
{
    return m_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void LabelImg::setImg(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    updatePixmap();
}

void LabelImg::setImg(const QImage &img)
{
    setImg(QPixmap::fromImage(img));
}

void LabelImg::setImg(const QImage *img)
{
    /* Verify pointer validity */
    if(!img){
        return;
    }

    /* Copy image */
    setImg(*img);
}

void LabelImg::setTextAlt(const QString &text)
{
    m_text = text;
}

int LabelImg::heightForWidth(int width) const
{
    if(m_pixmap.isNull()){
        return height();
    }

    return (m_pixmap.height() * width) / ((double)width);
}

QSize LabelImg::sizeHint() const
{
    const int sizeW = width();
    return QSize(sizeW, heightForWidth(sizeW));
}

void LabelImg::resizeEvent(QResizeEvent *event)
{
    /* Is image valid ? */
    if(m_pixmap.isNull()){
        QLabel::setText(m_text);
        return;
    }

    /* Draw pixmap */
    updatePixmap();
}

void LabelImg::updatePixmap()
{
    QLabel::setPixmap(getPixmapScaled());
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
