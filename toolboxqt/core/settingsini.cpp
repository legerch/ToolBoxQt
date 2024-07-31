#include "settingsini.h"

#include <QFile>

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::SettingsIni
 * \brief Class used to manage INI configuration file
 * \details
 * This class allow to easily manage settings depending on
 * a \c .ini file. \n
 * It will allow for example to not have to remember path of configuration file
 * each time we need it ! \n
 * This class used the <em>singleton pattern</em>, to use it, we can use:
 * - Method \c tbq::Settings::instance()
 * - Macro \c mSettings
 *
 * \note
 * Don't use this class if INI format is not mandatory, \c QSettings already provide
 * a way to manage other format without settings parameters each time at:
 * https://doc.qt.io/qt-6/qsettings.html#basic-usage
 *
 * To use this class in a project, we only have to initialize it in \c main
 * method:
 * \include{lineno} settings/maindefault.cpp
 *
 * Then we can use it anywhere with:
 * \code{.cpp}
 * mSettings.getValue("mySection/myKey");
 * \endcode
 *
 * This class also allow to have a custom behaviour for \b pre and \b post
 * load operations of the configuration file via setHooksPreLoadSettings()
 * and setHooksPostLoadSettings(). \n
 * We can defines custom ones like this:
 * - <em>Header file :</em>
 * \include{lineno} appsettings.h
 *
 * - <em>Source file :</em>
 * \include{lineno} appsettings.cpp
 *
 * - <em>Main file :</em>
 * \include{lineno} maincustom.cpp
 */

/*****************************/
/*      Custom types
 *     documentations        */
/*****************************/

/*!
 * \typedef SettingsIni::CbHook
 * \brief Custom callback hook use to implement custom behaviour
 *
 * \param[in] fileInfo
 * Path to configuration file used with \c loadSettings()
 *
 * \note
 * Defining custom hook is not mandatory, default
 * are provided (they do nothing excepting returning <tt>true</tt>).
 *
 * \return
 * Must return \c true if succeed.
 *
 * \sa setHooksPreLoadSettings(), setHooksPostLoadSettings()
 */

/*!
 * \def mSettings
 * \details
 * Custom macro simplying usage of tbq::SettingsIni::instance()
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
/* Constants definitions     */
/*****************************/

/*****************************/
/* Functions implementation  */
/*         Class             */
/*****************************/

SettingsIni &SettingsIni::instance()
{
    static SettingsIni instance;
    return instance;
}

SettingsIni::SettingsIni()
    : m_settings(nullptr), m_hookPreload(defaultHook), m_hookPostLoad(defaultHook)
{
    /* Nothing to do */
}

/*!
 * \brief Load settings from INI configuration file

 * \param fileInfo
 * INI configuration file to use
 *
 * \return
 * Return \c true if loading succeed.
 *
 * \sa setHooksPreLoadSettings(), setHooksPostLoadSettings()
 */
bool SettingsIni::loadSettings(const QFileInfo &fileInfo)
{
    /* Perform pre-operations */
    bool succeed = m_hookPreload(fileInfo);
    if(!succeed){
        return false;
    }

    /* Instantiate settings */
    m_settings = std::make_unique<QSettings>(fileInfo.absoluteFilePath(), QSettings::IniFormat);

    /* Perform post operations */
    return m_hookPostLoad(fileInfo);
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

/*!
 * \brief Use to set custom behaviour before loading settings
 * \param hookPreload
 * Custom callback to use
 *
 * \sa setHooksPostLoadSettings()
 */
void SettingsIni::setHooksPreLoadSettings(CbHook hookPreload)
{
    m_hookPreload = hookPreload;
}

/*!
 * \brief Use to set custom behaviour after loading settings
 * \param hookPostload
 * Custom callback to use
 *
 * \sa setHooksPreLoadSettings()
 */
void SettingsIni::setHooksPostLoadSettings(CbHook hookPostload)
{
    m_hookPostLoad = hookPostload;
}

bool SettingsIni::defaultHook(const QFileInfo &fileInfo)
{
    return true;
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
