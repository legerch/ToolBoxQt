#include "settingsini.h"

#include <QFile>

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::SettingsIni
 * \brief Virtual class used to manage INI configuration file
 * \details
 * This class add necessary bases to easily manage settings depending on
 * a \c .ini file. \n
 * It will allow for example to not have to remember path of configuration file
 * each time we need it ! \n
 * This class was implemented with <em>singleton pattern</em> in mind but since we use
 * inheritance to manage \em pre/post operations, this pattern will have to be implemented
 * by child classes.
 *
 * \note
 * Don't use this class if INI format is not mandatory, \c QSettings already provide
 * a way to manage other format without settings parameters each time at:
 * https://doc.qt.io/qt-6/qsettings.html#basic-usage
 *
 * Below, an example of a child class. \n
 * <em>Header file :</em>
 * \include{lineno} appsettings.h
 *
 * <em>Source file :</em>
 * \include{lineno} appsettings.cpp
 *
 * Then to use it, we have to :
 * 1. Load configuration in main method:
 * \include{lineno} settings/main.cpp
 *
 * 2. Use it anywhere with:
 * \code{.cpp}
 * AppSettings::instance().getValue("mySection/myKey");
 * \endcode
 */

/*****************************/
/*     Virtual methods
 *     documentations        */
/*****************************/

/*!
 * \fn tbq::SettingsIni::preLoadSettings()
 * \brief Perform action before loading settings
 * \details
 * Virtual method allowing to perform oepration
 * before actually loading settings file.
 *
 * \param[in] fileInfo
 * File information used in \c loadSettings()
 *
 * \return
 * Child classes should return
 * \c true is pre-load succeed.
 *
 * \sa postLoadSettings()
 */

/*!
 * \fn tbq::SettingsIni::postLoadSettings()
 * \brief Perform action after loading settings
 * \details
 * Virtual method allowing to perform oepration
 * after loading settings file.
 *
 * \param[in] fileInfo
 * File information used in \c loadSettings()
 *
 * \note
 * Base implementation perform nothing, \c true will
 * always be returned.
 *
 * \return
 * Classes reimplementing this method should return
 * \c true is post-load succeed.
 *
 * \sa preLoadSettings()
 */

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

SettingsIni::SettingsIni()
    : m_settings(nullptr)
{
    /* Nothing to do */
}

bool SettingsIni::loadSettings(const QFileInfo &fileInfo)
{
    /* Perform pre-operations */
    bool succeed = preLoadSettings(fileInfo);
    if(!succeed){
        return false;
    }

    /* Instantiate settings */
    m_settings = std::make_unique<QSettings>(fileInfo.absoluteFilePath(), QSettings::IniFormat);

    /* Perform post operations */
    return postLoadSettings(fileInfo);
}

void SettingsIni::groupBegin(QAnyStringView keyGroup)
{
    if(m_settings){
        m_settings->beginGroup(keyGroup);
    }
}

void SettingsIni::groupEnd()
{
    if(m_settings){
        m_settings->endGroup();
    }
}

void SettingsIni::setValue(QAnyStringView key, const QVariant &value)
{
    if(m_settings){
        m_settings->setValue(key, value);
    }
}

QVariant SettingsIni::getValue(QAnyStringView key, const QVariant &defaultValue) const
{
    if(!m_settings){
        return QVariant();
    }

    return m_settings->value(key, defaultValue);
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
