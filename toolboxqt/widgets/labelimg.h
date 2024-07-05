#ifndef TBQ_WIDGETS_QLABELIMG_H
#define TBQ_WIDGETS_QLABELIMG_H

#include "toolboxqt/toolboxqt_global.h"

#include <QLabel>
#include <QMovie>

namespace tbq
{

class TOOLBOXQT_EXPORT LabelImg : public QLabel
{
    Q_OBJECT

public:
    explicit LabelImg(QWidget *parent = nullptr);

public:
    const QPixmap& getPixmap() const;
    QPixmap getPixmapScaled() const;

    void animPlay(bool start);
    void animStart();
    void animStop();

public:
    void setImg(const QPixmap &pixmap);
    void setImg(const QImage &img);
    void setImg(const QImage *img);

    void setAnimation(const QString &animation);

    void setTextAlt(const QString &text);

public:
    virtual int heightForWidth(int width) const override;
    virtual QSize sizeHint() const override;

public slots:
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateMovieFrame();
    void updatePixmap();

private:
    QPixmap m_pixmap;

    QString m_text;
    std::unique_ptr<QMovie> m_anim;
};

} // namespace tbq

#endif // TBQ_WIDGETS_QLABELIMG_H
