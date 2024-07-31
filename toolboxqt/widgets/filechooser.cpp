#include "filechooser.h"

#include "core/settingsini.h"

#include <QFileDialog>

/*****************************/
/* Class documentations      */
/*****************************/

/*****************************/
/*      Custom types
 *     documentations        */
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
/* Constants definitions     */
/*****************************/

/*****************************/
/* Functions implementation  */
/*         Class             */
/*****************************/

QFileInfo FileChooser::fromUserSpace(Type idType, QStandardPaths::StandardLocation stdLocation, const QString &keyLatest, const QString &filter, QWidget *parent)
{
    return fromUserSpace(idType, QStandardPaths::writableLocation(stdLocation), keyLatest, filter, parent);
}

QFileInfo FileChooser::fromUserSpace(Type idType, const QString &dirLocation, const QString &keyLatest, const QString &filter, QWidget *parent)
{
    QString dir = dirLocation;

    /* Retrieve latest dir location */
    const QString cfgKeyDir = QString("filepath/dir_%1").arg(keyLatest);
    if(!keyLatest.isNull()){
        const QString dirLatest = mSettings.getValue(cfgKeyDir).toString();
        if(!dirLatest.isEmpty()){
            dir = dirLatest;
        }
    }

    /* Choose file according to selected type */
    QString filename;
    switch(idType)
    {
        case CHOOSE_FILE_EXIST:   filename = QFileDialog::getOpenFileName(parent, "Open file", dir, filter); break;
        case CHOOSE_FILE_CREATE:  filename = QFileDialog::getSaveFileName(parent, "File to save", dir, filter); break;
        default: break;
    }

    /* Do filename is valid ? */
    if(filename.isEmpty()){
        return QFileInfo();
    }
    const QFileInfo file(filename);

    /* Save latest used directory */
    if(!keyLatest.isNull()){
        mSettings.setValue(cfgKeyDir, file.absoluteDir().absolutePath());
    }

    return file;
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
