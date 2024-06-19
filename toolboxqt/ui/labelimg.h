#ifndef TBQ_UI_QLABELIMG_H
#define TBQ_UI_QLABELIMG_H

#include "toolboxqt_global.h"

#include <QLabel>

namespace tbq
{

class TOOLBOXQT_EXPORT LabelImg : public QLabel
{
    Q_OBJECT

public:
    explicit LabelImg(QWidget *parent = nullptr);

public:
    QPixmap getPixmapScaled() const;

public:
    void setImg(const QPixmap &pixmap);
    void setImg(const QImage &img);
    void setImg(const QImage *img);

    void setTextAlt(const QString &text);

public:
    virtual int heightForWidth(int width) const override;
    virtual QSize sizeHint() const override;

public slots:
    void resizeEvent(QResizeEvent *event) override;

private:
    void updatePixmap();

private:
    QPixmap m_pixmap;
    QString m_text;
};

} // namespace tbq

#endif // TBQ_UI_QLABELIMG_H
