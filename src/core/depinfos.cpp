#include "toolboxqt/core/depinfos.h"

/*****************************/
/* Class documentations      */
/*****************************/

/*****************************/
/* Macro definitions         */
/*****************************/

/*****************************/
/* Start namespace           */
/*****************************/

namespace tbq
{

/*****************************/
/* Constants defintitions    */
/*****************************/

/*****************************/
/* Functions implementation  */
/*         Class             */
/*****************************/

DepInfos::DepInfos(const RichLink &richLink, const QVersionNumber &version)
{
    setLink(richLink);
    setVersion(version);
}

void DepInfos::setLink(const RichLink &richLink)
{
    m_link = richLink;
}

void DepInfos::setVersion(const QVersionNumber &version)
{
    m_version = version;
}

const RichLink &DepInfos::getRichLink() const
{
    return m_link;
}

const QVersionNumber &DepInfos::getVersion() const
{
    return m_version;
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
