#include "labelimg.h"

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::LabelImg
 * \brief Label used to display an image
 * \details
 * Include with:
 * \code{.cpp}
 * #include "toolboxqt/widgets/labelimg.h"
 * \endcode
 *
 * QLabel doesn't behave properly when using it to display an image
 * that is loaded at runtime. Since size of image is not known
 * when layout is rendered, QLabel size will be wrong and will not be properly
 * updated when finally rendering an image (either too small, too big or not properly
 * scaled). This class will manage this issue.
 *
 * \note
 * Note that this class will be useful for QLabel containing image
 * which are loaded at runtime. The described issue do not happen when image
 * is available at compile-time.
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

LabelImg::LabelImg(QWidget *parent)
{
    setScaledContents(false);
    setAlignment(Qt::AlignCenter);

    setTextAlt("No available image");
}

const QPixmap &LabelImg::getPixmap() const
{
    return m_pixmap;
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
