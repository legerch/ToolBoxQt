#ifndef TBQ_WIDGETS_COLORBUTTON_H
#define TBQ_WIDGETS_COLORBUTTON_H

#include "toolboxqt/toolboxqt_global.h"

#include <QPushButton>

namespace tbq
{

class TOOLBOXQT_EXPORT ColorButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ColorButton(QWidget *parent = nullptr);

public:
    const QColor& getColor() const;
    void setColor(const QColor &color);

signals:
    void colorChanged(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void chooseColor();

private:
    QColor m_color;
};

} // namespace tbq

#endif // TBQ_WIDGETS_COLORBUTTON_H
