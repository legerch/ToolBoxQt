#ifndef TBQ_CORE_RICHLINK_H
#define TBQ_CORE_RICHLINK_H

#include "toolboxqt/toolboxqt_global.h"

#include <QUrl>

namespace tbq
{

class TOOLBOXQT_EXPORT RichLink
{

public:
    explicit RichLink(const QUrl &link, const QString &display = QString());

public:
    const QUrl& getUrl() const;
    const QString& getTextDisplayed() const;

    QString toHtml() const;

private:
    QUrl m_link;
    QString m_display;
};

} // namespace tbq

#endif // TBQ_CORE_RICHLINK_H
