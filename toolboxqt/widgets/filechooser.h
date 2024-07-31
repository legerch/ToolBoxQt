#ifndef TBQ_WIDGETS_FILECHOOSER_H
#define TBQ_WIDGETS_FILECHOOSER_H

#include <QFileInfo>
#include <QStandardPaths>

#include "toolboxqt/toolboxqt_global.h"

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
    static QFileInfo fromUserSpace(Type idType, QStandardPaths::StandardLocation stdLocation, const QString &keyLatest = QString(), const QString &filter = QString(), QWidget *parent = nullptr);
    static QFileInfo fromUserSpace(Type idType, const QString &dirLocation, const QString &keyLatest = QString(), const QString &filter = QString(), QWidget *parent = nullptr);
};

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/

#endif // TBQ_WIDGETS_FILECHOOSER_H
