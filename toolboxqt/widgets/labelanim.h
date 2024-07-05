#ifndef TBQ_WIDGETS_LABELANIM_H
#define TBQ_WIDGETS_LABELANIM_H

#include "toolboxqt/toolboxqt_global.h"

#include <QLabel>

namespace tbq
{

class TOOLBOXQT_EXPORT LabelAnim : public QLabel
{
    Q_OBJECT

public:
    explicit LabelAnim(QWidget *parent = nullptr);

public:
    void setAnimation(const QString &animation);

public slots:
    void play();
    void stop();

protected:
    virtual int heightForWidth(int width) const override;
    virtual QSize sizeHint() const override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    void updateMovieFrame();

private:
    QMovie *m_anim;
};

} // namespace tbq

#endif // TBQ_WIDGETS_LABELANIM_H
