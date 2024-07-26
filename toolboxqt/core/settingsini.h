#ifndef TBQ_CORE_SETTINGSINI_H
#define TBQ_CORE_SETTINGSINI_H

#include "toolboxqt/toolboxqt_global.h"

#include <QFileInfo>
#include <QSettings>

namespace tbq
{

class TOOLBOXQT_EXPORT SettingsIni
{
    TOOLBOXQT_DISABLE_COPY_MOVE(SettingsIni)

public:
    bool loadSettings(const QFileInfo &fileInfo);

    void groupBegin(QAnyStringView keyGroup);
    void groupEnd();

    void setValue(QAnyStringView key, const QVariant &value);
    QVariant getValue(QAnyStringView key, const QVariant &defaultValue = QVariant()) const;

protected:
    virtual bool preLoadSettings(const QFileInfo &fileInfo);
    virtual bool postLoadSettings(const QFileInfo &fileInfo);

private:
    explicit SettingsIni();

private:
    std::unique_ptr<QSettings> m_settings;
};

} // namespace tbq

#endif // TBQ_CORE_SETTINGSINI_H
