#ifndef TBQ_WIDGETS_BUTTON_H
#define TBQ_WIDGETS_BUTTON_H

#include <QPainter>
#include <QPushButton>
#include <QToolButton>
#include <QWidget>

#include "toolboxqt/toolboxqt_global.h"

/*****************************/
/* Start namespace           */
/*****************************/

namespace tbq
{

/*****************************/
/*     Class definitions     */
/*    BtnAbstractWordWrap    */
/*****************************/

class TOOLBOXQT_EXPORT BtnAbstractWordWrap
{

public:
    explicit BtnAbstractWordWrap();

public:
    void setPadding(int padding);

public:
    const QString& getText() const;
    int getPadding() const;

protected:
    void setTextWordWrap(const QString &text);

    void paintTextWordWrap(QPainter *painter, const QRect &rect);
    QSize calcSizeHintWordWrap(const QFontMetrics &fm, int width) const;

protected:
    virtual void updateGeometryBtn() = 0;
    virtual void updateBtn() = 0;

private:
    void performRefresh();

private:
    QString m_text;
    int m_padding;
};

/*****************************/
/*     Class definitions     */
/*         BtnTool           */
/*****************************/

class TOOLBOXQT_EXPORT BtnTool : public QToolButton, public BtnAbstractWordWrap
{
    Q_OBJECT

public:
    explicit BtnTool(QWidget *parent = nullptr);
    explicit BtnTool(const QString &text, int padding = 5, QWidget *parent = nullptr);

public:
    void setText(const QString &text);

protected: // Virtual methods from QToolButton
    void paintEvent(QPaintEvent *event) override;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected: // Virtual methods from BtnAbstractWordWrap
    void updateGeometryBtn() override;
    void updateBtn() override;

private: // Disable inherited public methods that can confuse users
    using QToolButton::text;
};

/*****************************/
/*     Class definitions     */
/*         BtnPush           */
/*****************************/

class TOOLBOXQT_EXPORT BtnPush : public QPushButton, public BtnAbstractWordWrap
{
    Q_OBJECT

public:
    explicit BtnPush(QWidget *parent = nullptr);
    explicit BtnPush(const QString &text, int padding = 5, QWidget *parent = nullptr);

public:
    void setText(const QString &text);
    void setTimeDoubleClick(int interval = 250);

signals:
    void sClickedSimple();
    void sClickedDouble();

protected: // Virtual methods from QToolButton
    void paintEvent(QPaintEvent *event) override;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected: // Virtual methods from BtnAbstractWordWrap
    void updateGeometryBtn() override;
    void updateBtn() override;

private: // Disable inherited public methods that can confuse users
    using QPushButton::text;

private:
    void eventIsClicked();
    void eventTimeoutDblClk();

private:
    QTimer *m_timerDblClk = nullptr;
};

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/

#endif // TBQ_WIDGETS_BUTTON_H
