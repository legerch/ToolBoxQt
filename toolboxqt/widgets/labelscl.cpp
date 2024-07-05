#include "labelscl.h"

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

LabelScl::LabelScl(QWidget *parent)
    : QLabel(parent)
{
    setScaledContents(false);
    setAlignment(Qt::AlignCenter);
    setAttribute(Qt::WA_TranslucentBackground, true);

    setTextAlt("No available image");
}

/*!
 * \brief Use to get original image
 *
 * \return
 * Return reference to original
 * image
 *
 * \sa getPixmapScaled()
 * \sa setImg()
 */
const QPixmap &LabelScl::getPixmap() const
{
    return m_pixmap;
}

/*!
 * \brief Use to get image scaled to fit
 * inside the label
 *
 * \return
 * Returns image scaled to fit inside the available
 * space of the label
 */
QPixmap LabelScl::getPixmapScaled() const
{
    return m_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void LabelScl::animPlay(bool start)
{
    start ? animStart() : animStop();
}

void LabelScl::animStart()
{
    m_anim->start();
}

void LabelScl::animStop()
{
    m_anim->stop();
}

/*!
 * \brief Set image to use via a \b QPixmap
 *
 * \param[in] pixmap
 * Pixmap image to use inside the label. Pixmap
 * image will be copied.
 */
void LabelScl::setImg(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    updatePixmap();
}

/*!
 * \brief Set image to use via a \b QImage
 *
 * \param[in] img
 * Image to use inside the label. This value
 * will be copied.
 */
void LabelScl::setImg(const QImage &img)
{
    setImg(QPixmap::fromImage(img));
}

/*!
 * \brief Set image via a pointer to \b QImage
 *
 * \param[in] img
 * Pointer to image to use. \n
 * If \c nullptr, nothing will be perform. \n
 * Caller don't need to keep a reference to the object,
 * value is copied.
 */
void LabelScl::setImg(const QImage *img)
{
    /* Verify pointer validity */
    if(!img){
        return;
    }

    /* Copy image */
    setImg(*img);
}

void LabelScl::setAnimation(const QString &animation)
{
    m_anim = std::make_unique<QMovie>(animation);
    connect(m_anim.get(), &QMovie::frameChanged, this, &LabelScl::updateMovieFrame);
}

/*!
 * \brief Set text to display when no image
 * has been set.
 *
 * \param[in] text
 * Text to display when no image has been set.
 */
void LabelScl::setTextAlt(const QString &text)
{
    m_text = text;
}

int LabelScl::heightForWidth(int width) const
{
    if(m_pixmap.isNull()){
        return height();
    }

    return (m_pixmap.height() * width) / ((double)width);
}

QSize LabelScl::sizeHint() const
{
    const int sizeW = width();
    return QSize(sizeW, heightForWidth(sizeW));
}

void LabelScl::resizeEvent(QResizeEvent *event)
{
    if(m_anim && m_anim->state() == QMovie::Running){
        updateMovieFrame();
    }else{
        updatePixmap();
    }
}

void LabelScl::updateMovieFrame()
{
    m_pixmap = m_anim->currentPixmap();
    updatePixmap();
}

void LabelScl::updatePixmap()
{
    /* Is image valid ? */
    if(m_pixmap.isNull()){
        QLabel::setText(m_text);
        return;
    }

    /* Draw pixmap */
    QLabel::setPixmap(getPixmapScaled());
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
