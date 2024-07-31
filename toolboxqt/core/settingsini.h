#ifndef TBQ_CORE_SETTINGSINI_H
#define TBQ_CORE_SETTINGSINI_H

#include "toolboxqt/toolboxqt_global.h"

#include <QFileInfo>
#include <QSettings>

#define mSettings   tbq::SettingsIni::instance()

namespace tbq
{

class TOOLBOXQT_EXPORT SettingsIni final
{
    TOOLBOXQT_DISABLE_COPY_MOVE(SettingsIni)

public:
    using CbHook = std::function<bool(const QFileInfo &fileInfo)>;

public:
    static SettingsIni& instance();

private:
    explicit SettingsIni();

public:
    bool loadSettings(const QFileInfo &fileInfo);

    void groupBegin(QAnyStringView keyGroup);
    void groupEnd();

    void setValue(QAnyStringView key, const QVariant &value);
    QVariant getValue(QAnyStringView key, const QVariant &defaultValue = QVariant()) const;

public:
    void setHooksPreLoadSettings(CbHook hookPreload);
    void setHooksPostLoadSettings(CbHook hookPostload);

private:
    static bool defaultHook(const QFileInfo &fileInfo);

private:
    std::unique_ptr<QSettings> m_settings;

    CbHook m_hookPreload;
    CbHook m_hookPostLoad;
};

} // namespace tbq

#endif // TBQ_CORE_SETTINGSINI_H
