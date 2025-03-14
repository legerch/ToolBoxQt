#include "dialogabout.h"

#include <QApplication>
#include <QGridLayout>

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

DialogAbout::DialogAbout(QWidget *parent)
    : QDialog{parent}
{
    /* Allocate members */
    m_labelIcon = new LabelScl(this);
    m_labelName = new QLabel(this);
    m_labelVersion = new QLabel(this);

    m_tabs = new QTabWidget(this);

    /* Initialize minimal UI */
    uiInitBase();
}

void DialogAbout::setAppInfos(const QString &name, const QVersionNumber &version)
{
    m_labelName->setText(name);
    m_labelVersion->setText(version.toString());
}

void DialogAbout::setLogo(const QPixmap &logo)
{
    m_labelIcon->setImg(logo);
}

void DialogAbout::uiInitBase()
{
    /* Set dialog layout */
    QGridLayout *titleLayout = new QGridLayout();
    titleLayout->addWidget(m_labelIcon, 0, 0, 2, 1, Qt::AlignCenter);
    titleLayout->addWidget(m_labelName, 0, 1);
    titleLayout->addWidget(m_labelVersion, 1, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(m_tabs);

    setLayout(mainLayout);

    /* Set font for labels */
    const QApplication *app = qApp;

    QFont font = qApp->font();
    font.setItalic(true);
    m_labelVersion->setFont(font);

    /* Set basic app informations */
    setAppInfos(app->applicationDisplayName(), QVersionNumber::fromString(app->applicationVersion()));
    setLogo(app->windowIcon().pixmap(QSize(48, 48)));
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
