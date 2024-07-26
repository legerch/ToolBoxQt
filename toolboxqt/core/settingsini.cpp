#include "settingsini.h"

#include <QFile>

/*****************************/
/* Class documentations      */
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
    std::make_unique<QSettings>(fileInfo.absoluteFilePath(), QSettings::IniFormat);

    /* Perform post operations */
    return postLoadSettings(fileInfo);
}

void SettingsIni::groupBegin(QAnyStringView keyGroup)
{
    m_settings->beginGroup(keyGroup);
}

void SettingsIni::groupEnd()
{
    m_settings->endGroup();
}

void SettingsIni::setValue(QAnyStringView key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

QVariant SettingsIni::getValue(QAnyStringView key, const QVariant &defaultValue) const
{
    return m_settings->value(key, defaultValue);
}

/*!
 * \brief Perform action before loading settings
 * \details
 * Virtual method allowing to perform oepration
 * before actually loading settings file.
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
 * \c true is pre-load succeed.
 */
bool SettingsIni::preLoadSettings(const QFileInfo &fileInfo)
{
    return true;
}

/*!
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
 */
bool SettingsIni::postLoadSettings(const QFileInfo &fileInfo)
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
