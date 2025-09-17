#ifndef TBQ_WIDGETS_TABLE_TABLEWIDGETITEMLINK_H
#define TBQ_WIDGETS_TABLE_TABLEWIDGETITEMLINK_H

#include "toolboxqt/toolboxqt_global.h"
#include "toolboxqt/core/richlink.h"

#include <QTableWidgetItem>

namespace tbq
{

/*****************************/
/*     Class definitions     */
/*    TableWidgetItemLink    */
/*****************************/

class TOOLBOXQT_EXPORT TableWidgetItemLink : public QTableWidgetItem
{

public:
    static constexpr int TypeId = QTableWidgetItem::UserType + 1;

public:
    TableWidgetItemLink();
    TableWidgetItemLink(const RichLink &link);
    TableWidgetItemLink(const QIcon &icon, const RichLink &link);

public:
    bool openLink() const;
    void setLink(const RichLink &link);

private:
    using QTableWidgetItem::setText;

public:
    static bool isTypeId(const QTableWidgetItem *item);
};

/*****************************/
/*     Class definitions     */
/*    TableWidgetLinkHelper  */
/*****************************/

class TOOLBOXQT_EXPORT TableWidgetLinkHelper
{
public:
    static void manageEvents(QTableWidget *table);

public:
    static void handleOpening(QTableWidget *table, int row, int column);
    static void handleHovering(QTableWidget *table, QTableWidgetItem *item);
};

} // namespace tbq

#endif // TBQ_WIDGETS_TABLE_TABLEWIDGETITEMLINK_H
