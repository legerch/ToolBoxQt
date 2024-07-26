#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include "toolboxqt/core/settingsini.h"

#define mAppCfg  AppSettings::instance()

class AppSettings : public tbq::SettingsIni
{
    TOOLBOXQT_DISABLE_COPY_MOVE(AppSettings)

public:
    static AppSettings& instance();

protected:
    virtual bool preLoadSettings(const QFileInfo &fileInfo) override;
    virtual bool postLoadSettings(const QFileInfo &fileInfo) override;

private:
    explicit AppSettings();

private:
    static constexpr int SUPPORT_VERSION_MAJOR = 1;
};

#endif // APPSETTINGS_H
