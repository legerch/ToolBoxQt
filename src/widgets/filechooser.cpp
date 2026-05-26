#include "toolboxqt/widgets/filechooser.h"

#include "toolboxqt/core/settingsini.h"

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
QString FileChooser::fromUserSpaceFile(QWidget *parent, Type idType, QStandardPaths::StandardLocation stdLocation, const QString &filter, SettingsIni *settings, const QString &keyLatest)
{
    return fromUserSpaceFile(parent, idType, QStandardPaths::writableLocation(stdLocation), filter, settings, keyLatest);
}

/*!
 * \brief Choose a file from user-space
 * \details
 * Allow to choose file from user-space and allow to easily
 * remember latest used directory.
 *
 * \param[in, out] parent
 * Parent widget.
 * \param[in] idType
 * Type of file to choose. \n
 * If unknown, nothing will be performed.
 * \param[in] dirLocation
 * Default directory to used when opening file dialog
 * window
 * \param[in] filter
 * Filter to use. Can be set using:
 * \code{.cpp}
 * tr("Images (*.png *.xpm *.jpg)" // Only display images files
 * tr("Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)" // Allow multiple filters (separated with ";;")
 * \endcode
 * \param[in,out] settings
 * Settings entity to use store if using \c keyLatest argument. \n
 * Nothing performed if \c nullptr.
 * \param[in] keyLatest
 * If not empty, provided key will be read from \c setting argument
 * and use the registered directory in it (and save it when file dialog
 * window is closed). \n
 * This is useful to directly open file dialog window to the latest use
 * directory for this specific ressource
 *
 * \return
 * Returns absolute path of the selected file. \n
 * This value will be empty if no file has been selected.
 *
 * \sa fromUserSpaceFile()
 * \sa fromUserSpaceDir()
 */
QString FileChooser::fromUserSpaceFile(QWidget *parent, Type idType, const QString &dirLocation, const QString &filter, SettingsIni *settings, const QString &keyLatest)
{
    const bool doSettings = settingsAreValid(settings, keyLatest);
    QString dir = dirLocation;

    /* Retrieve latest dir location */
    const QString cfgKeyDir = getKeyFmt(keyLatest);
    if(doSettings){
        const QString dirLatest = settings->getValue(cfgKeyDir).toString();
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
        return QString();
    }
    const QFileInfo file(filename);

    /* Save latest used directory */
    if(doSettings){
        settings->setValue(cfgKeyDir, file.absoluteDir().absolutePath());
    }

    return file.absoluteFilePath();
}

/*!
 * \overload
 * \brief Choose multiple files from user-space with standard location
 */
QStringList FileChooser::fromUserSpaceFiles(QWidget *parent, QStandardPaths::StandardLocation stdLocation, const QString &filter, SettingsIni *settings, const QString &keyLatest)
{
    return fromUserSpaceFiles(parent, QStandardPaths::writableLocation(stdLocation), filter, settings, keyLatest);
}

/*!
 * \brief Choose multiple files from user-space
 * \details
 * Allow to choose list of files from user-space and allow to easily
 * remember latest used directory.
 *
 * \param[in, out] parent
 * Parent widget.
 * \param[in] dirLocation
 * Default directory to used when opening file dialog
 * window
 * \param[in] filter
 * Filter to use. Can be set using:
 * \code{.cpp}
 * tr("Images (*.png *.xpm *.jpg)" // Only display images files
 * tr("Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)" // Allow multiple filters (separated with ";;")
 * \endcode
 * \param[in,out] settings
 * Settings entity to use store if using \c keyLatest argument. \n
 * Nothing performed if \c nullptr.
 * \param[in] keyLatest
 * If not empty, provided key will be read from \c setting argument
 * and use the registered directory in it (and save it when file dialog
 * window is closed). \n
 * This is useful to directly open file dialog window to the latest use
 * directory for this specific ressource
 *
 * \return
 * Returns absolute path of selected files. \n
 * This value will be empty if no file has been selected.
 *
 * \sa fromUserSpaceFile()
 * \sa fromUserSpaceDir()
 */
QStringList FileChooser::fromUserSpaceFiles(QWidget *parent, const QString &dirLocation, const QString &filter, SettingsIni *settings, const QString &keyLatest)
{
    const bool doSettings = settingsAreValid(settings, keyLatest);
    QString dir = dirLocation;

    /* Retrieve latest dir location */
    const QString cfgKeyDir = getKeyFmt(keyLatest);
    if(doSettings){
        const QString dirLatest = settings->getValue(cfgKeyDir).toString();
        if(!dirLatest.isEmpty()){
            dir = dirLatest;
        }
    }

    /* Choose list of files */
    const QStringList listFiles = QFileDialog::getOpenFileNames(parent, "Open files", dir, filter);
    if(listFiles.isEmpty()){
        return listFiles;
    }
    const QFileInfo file(listFiles.first());

    /* Save latest used directory */
    if(doSettings){
        settings->setValue(cfgKeyDir, file.absoluteDir().absolutePath());
    }

    return listFiles;
}

/*!
 * \overload
 * \brief Choose a directory from user-space with standard location
 */
QString FileChooser::fromUserSpaceDir(QWidget *parent, QStandardPaths::StandardLocation stdLocation, SettingsIni *settings, const QString &keyLatest)
{
    return fromUserSpaceDir(parent, QStandardPaths::writableLocation(stdLocation), settings, keyLatest);
}

/*!
 * \brief Choose a directory from user-space
 * \details
 * Allow to choose directory from user-space and allowing to easily
 * remember latest.
 *
 * \param[in, out] parent
 * Parent widget.
 * \param[in] dirLocation
 * Default directory to used when opening
 * directory dialog window
 * \param[in,out] settings
 * Settings entity to use store if using \c keyLatest argument. \n
 * Nothing performed if \c nullptr.
 * \param[in] keyLatest
 * If not empty, provided key will be read from \c setting argument
 * and use the registered directory in it (and save it when directory dialog
 * window is closed). \n
 * This is useful to directly open directory dialog window to the latest used.
 *
 * \return
 * Returns selected directory path. \n
 * This value will be empty if no file has been selected.
 *
 * \sa fromUserSpaceFile(), fromUserSpaceFiles()
 */
QString FileChooser::fromUserSpaceDir(QWidget *parent, const QString &dirLocation, SettingsIni *settings, const QString &keyLatest)
{
    const bool doSettings = settingsAreValid(settings, keyLatest);
    QString dir = dirLocation;

    /* Retrieve latest dir location */
    const QString cfgKeyDir = getKeyFmt(keyLatest);
    if(doSettings){
        const QString dirLatest = settings->getValue(cfgKeyDir).toString();
        if(!dirLatest.isEmpty()){
            dir = dirLatest;
        }
    }

    /* Choose directory */
    const QString selectedDir = QFileDialog::getExistingDirectory(parent, tr("Open directory"), dir);
    if(selectedDir.isEmpty()){
        return selectedDir;
    }

    /* Save latest used directory */
    if(doSettings){
        settings->setValue(cfgKeyDir, selectedDir);
    }

    return selectedDir;
}

/*!
 * \brief Allow to retrieve a FileChooser path
 * from key.
 *
 * \param[in] setting
 * Setting instance to use. \n
 * Must be <b>not NULL</b>.
 * \param[in] key
 * Key used to perform registration
 * \param[in] defaultValue
 * Default value to use if key doesn't exist or if value is
 * empty.
 *
 * \return
 * Returns string path associated to \c key
 */
QString FileChooser::getPathFromKey(const SettingsIni *settings, const QString &key, const QString &defaultValue)
{
    const QString path = settings->getValue(getKeyFmt(key), defaultValue).toString();
    if(path.isEmpty()){
        return defaultValue;
    }

    return path;
}

bool FileChooser::settingsAreValid(const SettingsIni *settings, const QString &keyLatest)
{
    return settings != nullptr && !keyLatest.isEmpty();
}

/*!
 * \brief Format key to proper identifier
 *
 * \param[in] key
 * Key to use. \n
 * Must \b not be empty.
 *
 * \return
 * Return key formatted to <em>key path</em> format.
 */
QString FileChooser::getKeyFmt(const QString &key)
{
    static const QString MODEL_KEY_FILEPATH = "filepath/dir_%1";
    return MODEL_KEY_FILEPATH.arg(key);
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
