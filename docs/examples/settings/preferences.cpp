#include "preferences.h"

#include "toolboxqt/core/corehelper.h"

const QVersionNumber Preferences::SUPPORT_VERSION = QVersionNumber(1, 0, 0);

Preferences& Preferences::instance()
{
    static Preferences instance;
    return instance;
}

Preferences::Preferences()
{
    /* Nothing to do */
}

void Preferences::setup(const QFileInfo &fileInfo)
{
    // Here we use "std::bind", but we could have also used a lambda function instead
    m_settings.setHooksPreLoadSettings(std::bind(&Preferences::preLoadSettings, this, std::placeholders::_1));
    m_settings.setHooksPostLoadSettings(std::bind(&Preferences::postLoadSettings, this, std::placeholders::_1));

    m_settings.loadSettings(fileInfo);
}

bool Preferences::preLoadSettings(const QFileInfo &fileInfo)
{
    /* Verify that configuration file exists */
    const QString filePath = fileInfo.absoluteFilePath();
    if(!QFile::exists(filePath)){
        const QString err = QString("Could not find configuration file: %1").arg(filePath);
        tbq::CoreHelper::quitApplication(err);
        return false;
    }

    return true;
}

bool Preferences::postLoadSettings(APP_VAR_UNUSED const QFileInfo &fileInfo)
{
    static const QString KEY_VERSION_FILE = "app/version_cfg_file";

    /* Verify configuration version compatibility */
    const QString semverStr = m_settings.getValue(KEY_VERSION_FILE).toString();
    const QVersionNumber semver = QVersionNumber::fromString(semverStr);

    if(semver.majorVersion() < SUPPORT_VERSION.majorVersion() || semver.majorVersion() > SUPPORT_VERSION.majorVersion()){
        QString err = QString("Unable to load configuration file of application, version is unsupported [read: %1, major-supported: %2]")
        .arg(semver.toString()).arg(SUPPORT_VERSION.majorVersion());

        tbq::CoreHelper::quitApplication(err);
        return false;
    }

    /* Update file settings properties */
    m_settings.setValue(KEY_VERSION_FILE, SUPPORT_VERSION.toString());

    return true;
}
