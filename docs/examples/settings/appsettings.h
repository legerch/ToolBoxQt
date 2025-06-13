#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QFileInfo>

class AppSettings
{

public:
    static void setup(const QFileInfo &fileInfo);

private:
    static bool preLoadSettings(const QFileInfo &fileInfo);
    static bool postLoadSettings(const QFileInfo &fileInfo);

private:
    static constexpr int SUPPORT_VERSION_MAJOR = 1;
};

#endif // APPSETTINGS_H