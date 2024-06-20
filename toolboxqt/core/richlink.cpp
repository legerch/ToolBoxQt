#include "richlink.h"

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

RichLink::RichLink(const QUrl &link, const QString &display)
    : m_link(link), m_display(display)
{
    /* Nothing to do */
}

const QUrl& RichLink::getUrl() const
{
    return m_link;
}

const QString& RichLink::getTextDisplayed() const
{
    return m_display;
}

QString RichLink::toHtml() const
{
    /* Define HTML model once for all */
    static const QString STR_HTML_MODEL = QString("<a href=\"%1\">%2</a>");

    /* Construct HTML balise */
    const QString strLink = m_link.toString();
    return STR_HTML_MODEL.arg(
        strLink,
        m_display.isEmpty() ? strLink : m_display
    );
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
