#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "toolboxqt/core/settingsini.h"

#include <QVersionNumber>

#define mPrefs  (Preferences::instance())

class Preferences final : public QObject
{
    Q_OBJECT
    APP_DISABLE_COPY_MOVE(Preferences)

public:
    static Preferences& instance();

public:
    void setup(const QFileInfo &fileInfo);

private:
    Preferences();

private:
    bool preLoadSettings(const QFileInfo &fileInfo);
    bool postLoadSettings(const QFileInfo &fileInfo);

private:
    tbq::SettingsIni m_settings;

private:
    static const QVersionNumber SUPPORT_VERSION;
};

#endif // PREFERENCES_H