#ifndef TBQ_CORE_DEPINFOS_H
#define TBQ_CORE_DEPINFOS_H

#include "toolboxqt/toolboxqt_global.h"
#include "toolboxqt/core/richlink.h"

#include <QVersionNumber>

namespace tbq
{

class TOOLBOXQT_EXPORT DepInfos
{
public:
    DepInfos(const RichLink &richLink, const QVersionNumber &version);

public:
    void setLink(const RichLink &richLink);
    void setVersion(const QVersionNumber &version);

public:
    const RichLink& getRichLink() const;
    const QVersionNumber& getVersion() const;

private:
    RichLink m_link;
    QVersionNumber m_version;
};

} // namespace tbq

#endif // TBQ_CORE_DEPINFOS_H
