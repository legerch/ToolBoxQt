#ifndef TOOLBOXQT_TOOLBOXTYPES_H
#define TOOLBOXQT_TOOLBOXTYPES_H

#include "toolboxqt_global.h"

#include <QObject>
#include <QVersionNumber>

/*****************************/
/* Namespace instructions    */
/*****************************/

namespace tbq
{
Q_NAMESPACE_EXPORT(TOOLBOXQT_EXPORT)

/*****************************/
/* Library types             */
/*****************************/

/*****************************/
/* Library methods           */
/*****************************/

TOOLBOXQT_EXPORT QVersionNumber getLibraryVersion();

/*****************************/
/* Qt related methods        */
/*****************************/

/*****************************/
/* End namespaces            */
/*****************************/

} // namespace tbq

/*****************************/
/* Qt specific meta-system   */
/*****************************/

#endif // TOOLBOXQT_TOOLBOXTYPES_H
