#include "mainwindow.h"

#include <QApplication>

#include "toolboxqt/core/settingsini.h"

/*****************************/
/* Macro definitions         */
/*****************************/
#define APP_CFG_FILE    "configurations/configuration.ini"

/*****************************/
/* Main method               */
/*****************************/
int main(int argc, char *argv[])
{
    /* Manage application properties */
    QApplication app(argc, argv);

    /* Set application configuration file */
    mSettings.loadSettings(QFileInfo(APP_CFG_FILE));

    /* Create main window */
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}