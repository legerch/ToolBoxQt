#ifndef TBQ_CORE_WIDGETHELPER_H
#define TBQ_CORE_WIDGETHELPER_H

#include <QDir>
#include <QLabel>

#include "toolboxqt/toolboxqt_global.h"

namespace tbq
{

class TOOLBOXQT_EXPORT WidgetHelper
{
public:
    static void labelSetPathDir(QLabel *label, const QDir &dir, bool verifyExist);
    static void labelSetPathFile(QLabel *label, const QFileInfo &fileInfo, bool verifyExist);
};

} // namespace tbq

#endif // TBQ_CORE_WIDGETHELPER_H
