#include "appsettings.h"

#include "toolboxqt/core/corehelper.h"
#include "toolboxqt/core/settingsini.h"

#include <QVersionNumber>

void AppSettings::setup(const QFileInfo &fileInfo)
{
    mSettings.setHooksPreLoadSettings(preLoadSettings);
    mSettings.setHooksPostLoadSettings(postLoadSettings);

    mSettings.loadSettings(fileInfo);
}

bool AppSettings::preLoadSettings(const QFileInfo &fileInfo)
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

bool AppSettings::postLoadSettings(const QFileInfo &fileInfo)
{
    /* Verify configuration version compatibility */
    const QString semverStr = mSettings.getValue("informations/version_cfg_file").toString();
    const QVersionNumber semver = QVersionNumber::fromString(semverStr);

    if(semver.majorVersion() > SUPPORT_VERSION_MAJOR){
        QString err = QString("Unable to load configuration file of application, version is unsupported [read: %1, major-supported: %2]")
                          .arg(semver.toString()).arg(SUPPORT_VERSION_MAJOR);
        tbq::CoreHelper::quitApplication(err);
        return false;
    }

    return false;
}
