#ifndef TBQ_WIDGETS_FILECHOOSER_H
#define TBQ_WIDGETS_FILECHOOSER_H

#include "toolboxqt/toolboxqt_global.h"
#include "toolboxqt/core/settingsini.h"

#include <QFileInfo>
#include <QStandardPaths>

/*****************************/
/* Start namespace           */
/*****************************/

namespace tbq
{

/*****************************/
/*     Class definitions     */
/*         FileChooser       */
/*****************************/

class TOOLBOXQT_EXPORT FileChooser : public QObject
{
    Q_OBJECT

public:
    enum Type
    {
        CHOOSE_FILE_EXIST,
        CHOOSE_FILE_CREATE
    };
    Q_ENUM(Type)

public:
    static QString fromUserSpaceFile(QWidget *parent, Type idType, QStandardPaths::StandardLocation stdLocation, const QString &filter = QString(), SettingsIni *settings = nullptr, const QString &keyLatest = QString());
    static QString fromUserSpaceFile(QWidget *parent, Type idType, const QString &dirLocation, const QString &filter = QString(), SettingsIni *settings = nullptr, const QString &keyLatest = QString());

    static QString fromUserSpaceDir(QWidget *parent, QStandardPaths::StandardLocation stdLocation, SettingsIni *settings = nullptr, const QString &keyLatest = QString());
    static QString fromUserSpaceDir(QWidget *parent, const QString &dirLocation, SettingsIni *settings = nullptr, const QString &keyLatest = QString());

public:
    static QString getPathFromKey(const SettingsIni *settings, const QString &key, const QString &defaultValue = QString());

private:
    static bool settingsAreValid(const SettingsIni *settings, const QString &keyLatest);
    static QString getKeyFmt(const QString &key);
};

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/

#endif // TBQ_WIDGETS_FILECHOOSER_H
