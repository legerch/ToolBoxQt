#include "toolboxqt/core/settingsini.h"

#include <QFile>

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::SettingsIni
 * \brief Class used to manage INI configuration file
 * \details
 * This class allow to easily manage settings depending on
 * a <tt>.ini</tt> file. \n
 * It will allow for example to not have to remember path of configuration file
 * each time we need it !
 *
 * \note
 * Don't use this class if INI format is not mandatory, \c QSettings already provide
 * a way to manage other format without settings parameters each time at:
 * https://doc.qt.io/qt-6/qsettings.html#basic-usage
 *
 * To use this class in a project, it will be easier to create a \em singleton from it
 * adpated to our specific configuration file. \n
 * This class also allow to have a custom behaviour for \b pre and \b post
 * load operations of the configuration file via setHooksPreLoadSettings()
 * and setHooksPostLoadSettings(). \n
 * We can defines custom ones like this:
 * - <em>Header file:</em>
 * \include{lineno} preferences.h
 *
 * - <em>Source file:</em>
 * \include{lineno} preferences.cpp
 * 
 * Then we only have to initialize it in our main:
 * \include{lineno} maincustom.cpp
 *
 * Then we can use it anywhere with:
 * \code{.cpp}
 * mPrefs.getValue("mySection/myKey");
 * \endcode
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

QFileInfo SettingsIni::getPath() const
{
    if(!m_settings){
        return QFileInfo();
    }

    return QFileInfo(m_settings->fileName());
}

void SettingsIni::groupBegin(TOOLBOXQT_QTCOMPAT_STR_VIEW keyGroup)
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

void SettingsIni::setValue(TOOLBOXQT_QTCOMPAT_STR_VIEW key, const QVariant &value)
{
    if(m_settings){
        m_settings->setValue(key, value);
    }
}

bool SettingsIni::contains(TOOLBOXQT_QTCOMPAT_STR_VIEW key) const
{
    if(m_settings){
        return m_settings->contains(key);
    }

    return false;
}

/*!
 * \brief Use to retrieve value from \c .ini file
 *
 * \param[in] key
 * Key of parameter to retrieve at format <tt>section/my_field</tt>.
 * \param[in] defaultValue
 * Value to use if the setting \c key doesn't exist
 *
 * \return
 * Returns value associated to \c key or \c defaultValue if field
 * doesn't exists.
 *
 * \sa getString()
 * \sa setValue()
 */
QVariant SettingsIni::getValue(TOOLBOXQT_QTCOMPAT_STR_VIEW key, const QVariant &defaultValue) const
{
    if(!m_settings){
        return QVariant();
    }

    return m_settings->value(key, defaultValue);
}

/*!
 * \brief Use to retrieve a string from \c .ini file
 * \details
 * This method differs from \c getValue() because here, default
 * value will also be returned if the field exist but the value is empty.
 *
 * \param[in] key
 * Key of parameter to retrieve at format <tt>section/my_field</tt>.
 * \param[in] defaultValue
 * Value to use if:
 * - The setting \c key doesn't exist
 * - Retrieved string value is empty
 *
 * \return
 * Returns value associated to \c key or \c defaultValue
 *
 * \sa getValue()
 * \sa setValue()
 */
QString SettingsIni::getString(TOOLBOXQT_QTCOMPAT_STR_VIEW key, const QString &defaultValue) const
{
    const QString value = getValue(key, defaultValue).toString();
    if(value.isEmpty()){
        return defaultValue;
    }

    return value;
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

bool SettingsIni::defaultHook(TOOLBOXQT_VAR_UNUSED const QFileInfo &fileInfo)
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
