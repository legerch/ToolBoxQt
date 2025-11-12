#ifndef TBQ_CORE_WIDGETHELPER_H
#define TBQ_CORE_WIDGETHELPER_H

#include <QDir>
#include <QLabel>
#include <QLineEdit>

#include "toolboxqt/toolboxqt_global.h"

namespace tbq
{

class TOOLBOXQT_EXPORT WidgetHelper
{
public:
    static void labelSetPathDir(QLabel *label, const QDir &dir, bool verifyExist);
    static void labelSetPathFile(QLabel *label, const QFileInfo &fileInfo, bool verifyExist);

    static void lineEditSetAsInputPasswd(QLineEdit *lineEdit, const QIcon &iconShow, const QIcon &iconHide, const QString &txtShow = "Show password", const QString &txtHide = "Hide password");
};

} // namespace tbq

#endif // TBQ_CORE_WIDGETHELPER_H
