#ifndef TBQ_CORE_COREHELPER_H
#define TBQ_CORE_COREHELPER_H

#include "toolboxqt/toolboxqt_global.h"

#include <QWidget>

namespace tbq
{

class TOOLBOXQT_EXPORT CoreHelper
{

public:
    static void quitApplication(const QString &reason = QString(), QWidget *parent = nullptr);
};

} // namespace tbq

#endif // TBQ_CORE_COREHELPER_H
