#ifndef QMLHELPER_H
#define QMLHELPER_H

#include "toolboxqt/toolboxqt_global.h"

#include <QObject>

namespace tbq
{

class TOOLBOXQT_EXPORT QmlHelper : public QObject
{
    Q_OBJECT

public:
    explicit QmlHelper(QObject *parent = nullptr);

public:
    Q_INVOKABLE bool qtVersionCheck(int major, int minor, int patch) const;
};

} // namespace tbq

#endif // QMLHELPER_H
