#include "corehelper.h"

#include <QCoreApplication>
#include <QMessageBox>
#include <QTimer>

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::CoreHelper
 * \brief Class containing multiple helpful methods
 * \details
 * This class group multiple methods that can't be associated
 * to specific core part, this is only utilities.
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
 * \brief Use to quit application
 * \details
 * To properly quit application, we have to queue "quit" event,
 * otherwise nothing will be performed (like when \c quit() is called
 * from a constructor for example). \n
 * This method was implemented to properly take care of those edge cases : so it can be called
 * anywhere, quit event will be made.
 *
 * \param[in] reason
 * Reason for the application to quit. \n
 * This will appear in a \c QMessageBox and be logged.
 * \param[in] parent
 * Parent widget. \n
 * This value can be \c nullptr.
 */
void CoreHelper::quitApplication(const QString &reason, QWidget *parent)
{
    const QString err = QString("%1.\nApplication exit !").arg(reason);

    QMessageBox::critical(parent, "Error", err);
    qCritical() << err;

    QTimer::singleShot(0, QCoreApplication::instance(), &QCoreApplication::quit);
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
