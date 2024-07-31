#include "filechooser.h"

#include "core/settingsini.h"

#include <QFileDialog>

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::FileChooser
 * \brief Used to choose a file from user-space
 * \details
 * This class provide methods making easier to choose a file
 * from user-space.
 */
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

/*!
 * \overload
 * \brief Choose a file from user-space with standard location
 */
QFileInfo FileChooser::fromUserSpace(Type idType, QStandardPaths::StandardLocation stdLocation, const QString &keyLatest, const QString &filter, QWidget *parent)
{
    return fromUserSpace(idType, QStandardPaths::writableLocation(stdLocation), keyLatest, filter, parent);
}

/*!
 * \brief Choose a file from user-space
 * \details
 * Allow to choose file from user-space and allowing to easily
 * remember latest used directory.
 *
 * \param[in] idType
 * Type of file to choose. \n
 * If unknown, nothing will be performed.
 * \param[in] dirLocation
 * Default directory to used when open file dialog
 * window
 * \param[in] keyLatest
 * If not empty, provided key will be read from \c tbq::SettingsIni
 * and use the registered directory in it (and save it when file dialog
 * window is closed). \n
 * This is useful to directly open file dialog window to the latest use
 * directory for this specific ressource
 * \param[in] filter
 * Filter to use. Can be set using:
 * \code{.cpp}
 * tr("Images (*.png *.xpm *.jpg)" // Only display images files
 * tr("Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)" // Allow multiple filters (separated with ";;")
 * \endcode
 * \param[in, out] parent
 * Parent widget.
 *
 * \return
 * Returns file information of the selected file. \n
 * This value will be empty if no file has been selected.
 */
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
