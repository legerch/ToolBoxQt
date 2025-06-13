#include "tablewidgetitemlink.h"

#include <QApplication>
#include <QDesktopServices>

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::TableWidgetItemLink
 * \brief Qt widget item allowing to store link informations
 * \details
 * Note that this class inherit from \c QTableWidgetItem. \n
 * Events management required usage of \c TableWidgetLinkHelper
 *
 * \sa TableWidgetLinkHelper
 */

/*!
 * \class tbq::TableWidgetLinkHelper
 * \brief Allow to manage events between \c tbq::TableWidgetItemLink
 * and a \c QTableWidget
 * \details
 * When a \c QTableWidgetItem is used to store a link,
 * it cannot be clicked and being fully displayed. \n
 * This class aims to fix this issue by properly:
 * - Manage hover event over an link item
 * - Open the link if clicked
 *
 * Caller only have to use:
 * \code{.cpp}
 * QTableWidget *table = new QTableWidget(...);
 * tbq::TableWidgetLinkHelper::manageEvents(table);
 * \endcode
 *
 * \sa manageEvents()
 * \sa handleOpening(), handleHovering()
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
/*  TableWidgetItemLink    */
/*****************************/

/*!
 * \brief Construct a table item link
 *
 * \sa setLink()
 */
TableWidgetItemLink::TableWidgetItemLink()
    : QTableWidgetItem(TypeId)
{
    /* Nothing to do */
}

/*!
 * \brief Construct a table item link with the
 * given \c link
 *
 * \param[in] link
 * Rich link to use for the item.
 *
 * \sa setLink()
 */
TableWidgetItemLink::TableWidgetItemLink(const RichLink &link)
    : TableWidgetItemLink()
{
    setLink(link);
}

/*!
 * \brief Construct a table item link with the
 * given \c icon and \c link
 *
 * \param[in] icon
 * Icon to use for the item.
 * \param[in] link
 * Rich link to use for the item.
 *
 * \sa setLink()
 */
TableWidgetItemLink::TableWidgetItemLink(const QIcon &icon, const RichLink &link)
    : TableWidgetItemLink(link)
{
    setIcon(icon);
}

/*!
 * \brief Allow to open item link URL.
 *
 * \return
 * Returns \c true if opening the URL has been
 * accepted. This doesn't mean that the URL opening
 * succeed, only that the request is accepted.
 */
bool TableWidgetItemLink::openLink() const
{
    const QUrl url = data(Qt::UserRole).toUrl();
    bool succeed = QDesktopServices::openUrl(url);
    if(!succeed){
        qWarning("Failed to open URL in default browser [url: %s]", qUtf8Printable(url.toDisplayString()));
    }

    return succeed;
}

/*!
 * \brief Use to set link of the item
 *
 * \param[in] link
 * Rich link to use for the item.
 */
void TableWidgetItemLink::setLink(const RichLink &link)
{
    /* Retrieve link style */
    const QColor linkColor = qApp->palette().color(QPalette::Link);

    QFont linkFont = qApp->font();
    linkFont.setUnderline(true);

    /* Set link text */
    setText(link.getTextDisplayed());

    /* Set link style */
    setForeground(linkColor);
    setFont(linkFont);

    /* Set link informations */
    setToolTip(link.getUrl().toDisplayString());
    setData(Qt::UserRole, link.getUrl());
}

/*!
 * \brief Use to verify if a \c QTableWidgetItem
 * is a TableWidgetItemLink.
 * \details
 * Can be useful is the type must be cast:
 * \code{.cpp}
 * if(TableWidgetItemLink::isTypeId(item)){
 *     auto *linkItem = static_cast<TableWidgetItemLink *>(item);
 *     // Do something with it
 * }else{
 *     // Not a TableWidgetItemLink, do something else
 * }
 * \endcode
 *
 * \param[in] item
 * Table widget item to verify. \n
 * if \b NULL, \c false will be returned.
 *
 * \return
 * Returns \c true if item is a \c TableWidgetItemLink
 * object.
 */
bool TableWidgetItemLink::isTypeId(const QTableWidgetItem *item)
{
    return item && item->type() == TableWidgetItemLink::TypeId;
}

/*****************************/
/* Functions implementation  */
/*  TableWidgetLinkHelper    */
/*****************************/

/*!
 * \brief Use to set listeners for events related
 * to a \c TableWidgetItemLink.
 * \details
 * This method only set connect events to their
 * respective method. If caller need to to re-implement
 * connection event, methods \c handleOpening() and
 * \c handleHovering() can be called.
 *
 * \param[out] table
 * Table to use to manage events.
 *
 * \sa handleOpening(), handleHovering()
 */
void TableWidgetLinkHelper::manageEvents(QTableWidget *table)
{
    /* Manage link opening */
    QObject::connect(table, &QTableWidget::cellClicked, table, [=](int row, int column){
        handleOpening(table, row, column);
    });

    /* Manage link hovering */
    table->setMouseTracking(true);
    QObject::connect(table, &QTableWidget::itemEntered, table, [=](QTableWidgetItem *item) {
        handleHovering(table, item);
    });
}

/*!
 * \brief Allow to manage "open" event of a \c QTableWidget
 * \details
 * If item at cell \c (row, col) is not a \c TableWidgetItemLink,
 * nothing will be performed, otherwise link will be opened.
 *
 * \param[in, out] table
 * Table associated to the event
 * \param[in] row
 * Row of the related cell
 * \param[in] column
 * Colum of the related cell
 *
 * \sa handleHovering()
 * \sa manageEvents()
 */
void TableWidgetLinkHelper::handleOpening(QTableWidget *table, int row, int column)
{
    /* Is proper type ? */
    auto *item = table->item(row, column);
    if(!TableWidgetItemLink::isTypeId(item)){
        return;
    }

    auto *linkItem = static_cast<TableWidgetItemLink *>(item);
    linkItem->openLink();
}

/*!
 * \brief Allow to manage "hover" event of a \c QTableWidget
 * \details
 * If item is a \c TableWidgetItemLink, cursor will be set to
 * \c Qt::PointingHandCursor, otherwise it be reset to default.
 *
 * \param[in, out] table
 * Table associated to the event. \n
 * Must be <b>not NULL</b>.
 * \param[in] item
 * Item related to the event. \n
 * Can be \b NULL.
 *
 * \sa handleOpening()
 * \sa manageEvents()
 */
void TableWidgetLinkHelper::handleHovering(QTableWidget *table, QTableWidgetItem *item)
{
    if(TableWidgetItemLink::isTypeId(item)){
        table->viewport()->setCursor(Qt::PointingHandCursor);
    }else{
        table->viewport()->unsetCursor();
    }
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
