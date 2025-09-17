#include "toolboxqt/qml/qmlhelper.h"

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::QmlHelper
 * \brief Class containing multiple helpful methods that
 * can be used in QML
 * \details
 * This class group multiple methods that we can use
 * inside QML files. \n
 * In order to use it, this class must be exposed to QML
 * context property:
 * \include{lineno} qml/qmlexpose.cpp
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

QmlHelper::QmlHelper(QObject *parent)
    : QObject{parent}
{}

/*!
 * \brief Use to verify Qt version
 * \details
 * Can be used to dynamically manage function compatibilities:
 * \code{.qml}
Window{
    width: 1000
    height: 800
    visible: true
    title: qsTr("Hello world window title")

    Component.onCompleted:{
        if(qmlHelper.qtVersionCheck(6, 0, 0)){
            console.info("Qt6 (or superior) version detected")
        }else{
            console.info("Qt5 (or inferior) version detected")
        }
    }
}
 * \endcode
 *
 * \param[in] major
 * Major version to check
 * \param[in] minor
 * Minor version to check
 * \param[in] patch
 * Patch version to check
 *
 * \return
 * Returns \c true if Qt version is superior
 * or equal to argument version
 */
bool QmlHelper::qtVersionCheck(int major, int minor, int patch) const
{
    return QT_VERSION >= QT_VERSION_CHECK(major, minor, patch);
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
