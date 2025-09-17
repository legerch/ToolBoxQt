#ifndef TBQ_WIDGETS_DIALOGABOUT_H
#define TBQ_WIDGETS_DIALOGABOUT_H

#include "toolboxqt/toolboxqt_global.h"
#include "toolboxqt/core/depinfos.h"
#include "toolboxqt/core/richlink.h"
#include "toolboxqt/widgets/labelscl.h"

#include <QDialog>
#include <QTabWidget>
#include <QTableWidget>
#include <QTextBrowser>
#include <QVersionNumber>

namespace tbq
{

class TOOLBOXQT_EXPORT DialogAbout : public QDialog
{
    Q_OBJECT

public:
    struct Ressource
    {
        RichLink source;
        QString author;
        QString license;
    };

    struct RessourceGroup
    {
        QString name;
        QVector<Ressource> listRes;
    };

public:
    using ListDeps = QVector<DepInfos>;
    using ListResGroups = QVector<RessourceGroup>;

public:
    explicit DialogAbout(QWidget *parent = nullptr);

public:
    void setAppInfos(const QString &name, const QVersionNumber &version);
    void setLogo(const QPixmap &logo);

    void addSectionAbout(const QString &aboutApp, const RichLink &linkHome = RichLink(), const RichLink &linkBug = RichLink());
    void addSectionDeps(const ListDeps &listDeps, const QString &invalidSemver = "/");
    void addSectionRessources(const ListResGroups &listGroups);
    void addSectionChangelog(const QUrl &sourceUrl, QTextDocument::ResourceType type = QTextDocument::MarkdownResource);
    void addSectionLicense(const QUrl &sourceUrl, QTextDocument::ResourceType type = QTextDocument::MarkdownResource);

    void addSectionFromDoc(const QString &name, const QUrl &sourceUrl, QTextDocument::ResourceType type);

private:
    QTableWidget* createRessourceGroup(const RessourceGroup &resGroup);

    void labelSetInteractions(QLabel *label);
    void handleDocsLinks(QTextBrowser *textArea, const QUrl &link);

private:
    void uiInitBase();

private:
    /* Basic properties */
    LabelScl *m_labelIcon = nullptr;
    QLabel *m_labelName = nullptr;
    QLabel *m_labelVersion = nullptr;

    /* Detailled properties */
    QTabWidget *m_tabs = nullptr;
};

} // namespace tbq

#endif // TBQ_WIDGETS_DIALOGABOUT_H
