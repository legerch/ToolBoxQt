#include "tablewidgetitemlink.h"

#include <QApplication>
#include <QDesktopServices>

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
/*  TableWidgetItemLink    */
/*****************************/

TableWidgetItemLink::TableWidgetItemLink()
    : QTableWidgetItem(TypeId)
{
    /* Nothing to do */
}

TableWidgetItemLink::TableWidgetItemLink(const RichLink &link)
    : TableWidgetItemLink()
{
    setLink(link);
}

TableWidgetItemLink::TableWidgetItemLink(const QIcon &icon, const RichLink &link)
    : TableWidgetItemLink(link)
{
    setIcon(icon);
}

bool TableWidgetItemLink::openLink() const
{
    const QUrl url = data(Qt::UserRole).toUrl();
    bool succeed = QDesktopServices::openUrl(url);
    if(!succeed){
        qWarning("Failed to open URL in default browser [url: %s]", qUtf8Printable(url.toDisplayString()));
    }

    return succeed;
}

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

bool TableWidgetItemLink::isTypeId(QTableWidgetItem *item)
{
    return item && item->type() == TableWidgetItemLink::TypeId;
}

/*****************************/
/* Functions implementation  */
/*  TableWidgetLinkHelper    */
/*****************************/

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
