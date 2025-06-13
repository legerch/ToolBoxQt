#include "toolboxqt/widgets/dialogabout.h"

void MenuBar::showHelpAbout()
{
    /* Create dialog about */
    tbq::DialogAbout *dialogAbout = new tbq::DialogAbout(this);
    dialogAbout->setAttribute(Qt::WA_DeleteOnClose);

    /* Set informations */
    // Set app main informations
    dialogAbout->addSectionAbout(
            "My great application which do many things:\n"
            "- The first great things\n"
            "- The second great things\n",
        tbq::RichLink(QUrl("https://github.com/myuser/myproject")),
        tbq::RichLink(QUrl("https://github.com/myuser/myproject/issues"))
    );

    // Set dependency section
    const QString teaseVer = QString::fromStdString(tease::Semver::getLibraryVersion().toString('.', 1));
    const tbq::DialogAbout::ListDeps listDeps = {
        tbq::DepInfos(tbq::RichLink(QUrl("https://www.qt.io/"), "Qt Framework"), QVersionNumber::fromString(QT_VERSION_STR)),

        tbq::DepInfos(tbq::RichLink(QUrl("https://github.com/google/googletest"), "Google Tests"), QVersionNumber()),
        tbq::DepInfos(tbq::RichLink(QUrl("https://github.com/nlohmann/json"), "JSON for Modern C++"), QVersionNumber()),
        tbq::DepInfos(tbq::RichLink(QUrl("https://github.com/legerch/QLogger"), "QLogger"), QLogger::QLoggerFactory::getLibraryVersion()),
        tbq::DepInfos(tbq::RichLink(QUrl("https://github.com/legerch/qtavplayer"), "QtAvPlayer"), QVersionNumber::fromString(QTAVPLAYER_VERSION_STR)),
        tbq::DepInfos(tbq::RichLink(QUrl("https://github.com/stachenov/quazip"), "Quazip"), QVersionNumber()),
        tbq::DepInfos(tbq::RichLink(QUrl("https://github.com/legerch/ToolBoxQt"), "Toolbox Qt"), QVersionNumber::fromString(TOOLBOXQT_VERSION_STR)),
        tbq::DepInfos(tbq::RichLink(QUrl("https://github.com/legerch/TransferEase"), "TransferEase"), QVersionNumber::fromString(teaseVer)),
        tbq::DepInfos(tbq::RichLink(QUrl("https://zlib.net/"), "ZLib"), QVersionNumber()),
    };
    dialogAbout->addSectionDeps(listDeps);

    // Set credit section
    const tbq::DialogAbout::ListResGroups listRes = {
        {
            .name = "Icons",
            .listRes = {
                {.source = tbq::RichLink(QUrl("https://www.flaticon.com/free-icon/local-area_2082759?term=computer&related_id=2082759"), "Main logo"), .author = "Eucalyp", .license = "Flaticon License"},
                {.source = tbq::RichLink(QUrl("https://www.bankoficons/greaticon1"), "Action1 icon"), .author = "David Awesome", .license = "Creative Commons"},
                {.source = tbq::RichLink(QUrl("https://www.bankoficons/greaticon2"), "Sub menu icon"), .author = "Paul Allesome", .license = "Creative Commons"},
            }
        },
        {
            .name = "Fonts",
            .listRes = {
                {.source = tbq::RichLink(QUrl("https://www.bankoffonts/greatfont1"), "App font"), .author = "Dave Calligraph", .license = "Creative Commons"},
                {.source = tbq::RichLink(QUrl("https://www.bankoffonts/greatfont2"), "Emoji font"), .author = "Sascha Isaac", .license = "GPL"},
            }
        }
    };
    dialogAbout->addSectionRessources(listRes);

    // Add useful documents
    dialogAbout->addSectionChangelog(QUrl("qrc:/docs/changelog"));
    dialogAbout->addSectionLicense(QUrl("qrc:/docs/license"));

    /* Display dialog about */
    dialogAbout->show();
}