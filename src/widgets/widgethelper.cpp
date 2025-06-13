#include "toolboxqt/widgets/widgethelper.h"

/*****************************/
/* Class documentations      */
/*****************************/

/*!
 * \class tbq::WidgetHelper
 * \brief Class containing multiple helpful methods
 * related to widgets
 * \details
 * This class group multiple methods that are simple enough
 * to not have to create an inherited object.
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
 * \brief Use to display a directory path inside a label
 * \details
 * Latest directory path part will be displayed, the rest of it will
 * be displayed as a tooltip.
 *
 * \param[out] label
 * Label to use. \n
 * Must be <b>not NULL</b>.
 * \param[in] dir
 * Directory to display. \n
 * If directory is current working directory ("."),
 * directory will be considered as not selected.
 * \param[in] verifyExist
 * If \c true, method will verify that directory exist : if
 * not, we will consider that that directory has not been selected.
 *
 * \sa labelSetPathFile()
 */
void WidgetHelper::labelSetPathDir(QLabel *label, const QDir &dir, bool verifyExist)
{
    /* Verify that directory exists */
    if(verifyExist && !dir.exists()){
        label->setText(QLabel::tr("No directory selected"));
        return;
    }

    /* Verify that directory is valid */
    if(dir.dirName() == "."){
        label->setText(QLabel::tr("No directory selected"));
        return;
    }

    /* Set file informations */
    label->setText(dir.dirName());
    label->setToolTip(dir.absolutePath());
}

/*!
 * \brief Use to display a file info path inside a label
 * \details
 * Filaname will be displayed, the path will
 * be displayed as a tooltip.
 *
 * \param[out] label
 * Label to use. \n
 * Must be <b>not NULL</b>.
 * \param[in] fileInfo
 * File informations to use. \n
 * If empty, file will be considered as not selected.
 * \param[in] verifyExist
 * If \c true, method will verify that file exist : if
 * not, we will consider that file has not been selected.
 *
 * \sa labelSetPathDir()
 */
void WidgetHelper::labelSetPathFile(QLabel *label, const QFileInfo &fileInfo, bool verifyExist)
{
    /* Do file infos are valid ? */
    if(fileInfo.baseName().isEmpty()){
        label->setText(QLabel::tr("No file selected"));
        return;
    }

    if(verifyExist && !fileInfo.exists()){
        label->setText(QLabel::tr("No file selected"));
        return;
    }

    /* Set file informations */
    label->setText(fileInfo.fileName());
    label->setToolTip(fileInfo.absoluteFilePath());
}

/*****************************/
/* End namespace             */
/*****************************/

} // namespace tbq

/*****************************/
/* End file                  */
/*****************************/
