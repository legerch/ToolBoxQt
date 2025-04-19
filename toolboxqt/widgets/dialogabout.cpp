#include "dialogabout.h"

#include <QApplication>
#include <QGridLayout>
#include <QTextEdit>
#include <QDesktopServices>

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

void DialogAbout::addSectionAbout(const QString &aboutApp, const RichLink &linkHome, const RichLink &linkBug)
{
    QFont fontBold = qApp->font();
    fontBold.setBold(true);

    /* Prepare layout properties */
    QGridLayout *aboutLayout = new QGridLayout();
    int idxRowItem = 0;

    /* Set app description */
    QTextEdit *appInfo = new QTextEdit();
    appInfo->setReadOnly(true);
    appInfo->setAcceptRichText(true);
    appInfo->setText(aboutApp);

    aboutLayout->addWidget(appInfo, idxRowItem, 0, 3, 3);
    idxRowItem += 3;

    /* Set app home URL */
    if(linkHome.isValid()){
        QLabel *homeUrlTitle = new QLabel(tr("Home page: "));
        homeUrlTitle->setFont(fontBold);

        QLabel *homeUrlValue = new QLabel(linkHome.toHtml());
        labelSetInteractions(homeUrlValue);

        aboutLayout->addWidget(homeUrlTitle, idxRowItem, 0, 1, 1);
        aboutLayout->addWidget(homeUrlValue, idxRowItem, 1, 1, 2);
        ++idxRowItem;
    }

    /* Set app bug URL */
    if(linkBug.isValid()){
        QLabel *bugUrlTitle = new QLabel(tr("Bug tracker: "));
        bugUrlTitle->setFont(fontBold);

        QLabel *bugUrlValue = new QLabel(linkBug.toHtml());
        labelSetInteractions(bugUrlValue);

        aboutLayout->addWidget(bugUrlTitle, idxRowItem, 0, 1, 1);
        aboutLayout->addWidget(bugUrlValue, idxRowItem, 1, 1, 2);
        ++idxRowItem;
    }

    /* Add widget to tabs */
    QWidget *widget = new QWidget(m_tabs);
    widget->setLayout(aboutLayout);

    m_tabs->addTab(widget, tr("About"));
}

void DialogAbout::addSectionDeps(const ListDeps &listDeps)
{
    /* Prepare layout properties */
    const QString modelDeps = QString("%1 :");
    QGridLayout *depsLayout = new QGridLayout();

    /* Manage each dependency */
    int row = 0;
    for(row = 0; row < listDeps.size(); ++row){
        const DepInfos &depInfo = listDeps.at(row);
        const RichLink &link = depInfo.getRichLink();
        const QVersionNumber &version = depInfo.getVersion();

        // Create dep title
        QLabel *labelTitle = new QLabel(modelDeps.arg(link.toHtml()));
        labelTitle->setToolTip(link.getUrl().toDisplayString());
        labelSetInteractions(labelTitle);

        // Create dep version
        const QString strVersion = version.isNull() ? tr("Unknown version") : version.toString();
        QLabel *labelVersion = new QLabel(strVersion);

        // Add desp info to layout
        depsLayout->addWidget(labelTitle, row, 0);
        depsLayout->addWidget(labelVersion, row, 1);
    }

    depsLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 2);
    depsLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), row, 1);

    /* Add widget to tabs */
    QWidget *widget = new QWidget(m_tabs);
    widget->setLayout(depsLayout);

    m_tabs->addTab(widget, tr("Dependencies"));
}

void DialogAbout::addSectionChangelog(const QUrl &sourceUrl, QTextDocument::ResourceType type)
{
    addSectionFromDoc(tr("Changelog"), sourceUrl, type);
}

void DialogAbout::addSectionLicense(const QUrl &sourceUrl, QTextDocument::ResourceType type)
{
    addSectionFromDoc(tr("License"), sourceUrl, type);
}

void DialogAbout::addSectionFromDoc(const QString &name, const QUrl &sourceUrl, QTextDocument::ResourceType type)
{
    /* Create text area */
    QTextBrowser *textArea = new QTextBrowser();
    textArea->setSource(sourceUrl, type);

    /* Set links behaviour */
    textArea->setOpenLinks(false);
    textArea->setOpenExternalLinks(false);
    connect(textArea, &QTextBrowser::anchorClicked, this, [this, textArea](const QUrl &link){
        handleDocsLinks(textArea, link);
    });

    /* Add text area to tabs */
    m_tabs->addTab(textArea, name);
}

void DialogAbout::labelSetInteractions(QLabel *label)
{
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setOpenExternalLinks(true);
}

void DialogAbout::handleDocsLinks(QTextBrowser *textArea, const QUrl &link)
{
    /* Do URL refer to an internal doc anchor ? */
    if(link.isRelative() || link.hasFragment()){
        textArea->scrollToAnchor(link.fragment());
        return;
    }

    /* Open URL in default browser */
    bool succeed = QDesktopServices::openUrl(link);
    if(!succeed){
        qWarning("Failed to open URL in default browser [url: %s]", qUtf8Printable(link.toDisplayString()));
    }
}

void DialogAbout::uiInitBase()
{
    /* Set dialog layout */
    QGridLayout *titleLayout = new QGridLayout();
    titleLayout->addWidget(m_labelIcon, 0, 0, 2, 1, Qt::AlignCenter);
    titleLayout->addWidget(m_labelName, 0, 1, 1, 1);
    titleLayout->addWidget(m_labelVersion, 1, 1, 1, 1);
    titleLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 2);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(m_tabs);

    setLayout(mainLayout);

    /* Set font for labels */
    const QApplication *app = qApp;

    QFont fontItalic = qApp->font();
    fontItalic.setItalic(true);
    m_labelVersion->setFont(fontItalic);

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
