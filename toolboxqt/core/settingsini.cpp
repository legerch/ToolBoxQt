#include "settingsini.h"

#include <QFile>

/*****************************/
/* Class documentations      */
/*****************************/

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
