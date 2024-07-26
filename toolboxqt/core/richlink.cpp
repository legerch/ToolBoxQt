#include "richlink.h"

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::RichLink
 * \brief Display a link with a custom text
 * \details
 * Include with:
 * \code{.cpp}
 * #include "toolboxqt/core/richlink.h"
 * \endcode
 */

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

/*!
 * \brief Create a RichLink object
 *
 * \param[in] link
 * URL to used as a link
 * \param[in] display
 * Text to display
 *
 * \sa toHtml()
 */
RichLink::RichLink(const QUrl &link, const QString &display)
    : m_link(link), m_display(display)
{
    /* Nothing to do */
}

/*!
 * \brief Get URL used in the link
 *
 * \return
 * Returns reference to URL link
 */
const QUrl& RichLink::getUrl() const
{
    return m_link;
}

/*!
 * \brief Get displayed text of the link
 *
 * \return
 * Returns reference to displayed text.
 */
const QString& RichLink::getTextDisplayed() const
{
    return m_display;
}

/*!
 * \brief Convert rich link to html string
 * that can be used (like in \c QLabel for example)
 *
 * \return
 * Returns formatted HTML rich link. \n
 * If no display text has been set, the link will be
 * displayed "as is".
 */
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
