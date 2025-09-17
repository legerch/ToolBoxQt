#include "toolboxqt/toolboxtypes.h"

/*****************************/
/* Namespace documentations  */
/*****************************/

/*!
 * \namespace tbq
 * \brief Namespace used for \b ToolBoxQt library
 *
 * \sa getLibraryVersion()
 */

/*****************************/
/* Signals documentations    */
/*****************************/

/*****************************/
/* Start namespace           */
/*****************************/

namespace tbq
{

/*****************************/
/* Functions implementation  */
/*****************************/

/*!
 * \brief Used to retrieve \b ToolBoxQt library
 * version.
 *
 * \return
 * Returns semantic version of the library.
 */
QVersionNumber getLibraryVersion()
{
    return QVersionNumber(TOOLBOXQT_VERSION_MAJOR, TOOLBOXQT_VERSION_MINOR, TOOLBOXQT_VERSION_PATCH);
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
