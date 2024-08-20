#ifndef TOOLBOXQT_GLOBAL_H
#define TOOLBOXQT_GLOBAL_H

#include "config.h"
#include <QtGlobal>

/**********************************
 * Library management
 *********************************/
#if defined(TOOLBOXQT_LIBRARY_BUILD)
#   define TOOLBOXQT_EXPORT Q_DECL_EXPORT
#else
#   define TOOLBOXQT_EXPORT Q_DECL_IMPORT
#endif

/**********************************
 * Deprecations warnings
 *********************************/
#define TOOLBOXQT_DEPREC              [[deprecated]]            /**< Use to mark a method as deprecated. \n\code{.cpp}TOOLBOXQT_DEPREC void myOldFct(); \endcode */
#define TOOLBOXQT_DEPREC_X(reason)    [[deprecated(reason)]] 	/**< Use to mark a method as deprecated and specify a reason. \n\code{.cpp}TOOLBOXQT_DEPREC_X("Use myNewFct() instead") void myOldFunc(); \endcode */

/**********************************
 * Custom macros used to detect custom
 * built-in functions
 * Sources:
 * - MSVC: No equivalent
 * - GCC: https://gcc.gnu.org/onlinedocs/gcc-13.2.0/cpp/_005f_005fhas_005fbuiltin.html
 * - Clang: https://clang.llvm.org/docs/LanguageExtensions.html#has-builtin
 *********************************/
#if defined(__GNUC__) || defined(__clang__)
#   define TOOLBOXQT_BUILTIN(x)  __has_builtin(x)
#else
#   define TOOLBOXQT_BUILTIN(x)  0
#endif

/**********************************
 * Custom macros in order to
 * not trigger warning on expected
 * behaviour
 *********************************/
#define TOOLBOXQT_FALLTHROUGH  [[fallthrough]]    /**< Indicates that the fall through from the previous case label is intentional and should not be diagnosed by a compiler that warns on fallthrough */

/**********************************
 * Context informations
 *********************************/
#define TOOLBOXQT_FILE            __FILE__
#define TOOLBOXQT_LINE            __LINE__
#define TOOLBOXQT_FCTNAME         __func__

#define TOOLBOXQT_FCTSIG          Q_FUNC_INFO

/**********************************
 * Classes behaviours
 *********************************/
#define TOOLBOXQT_DISABLE_COPY(Class) \
    Q_DISABLE_COPY(Class)

#define TOOLBOXQT_DISABLE_MOVE(Class) \
    Q_DISABLE_MOVE(Class)

#define TOOLBOXQT_DISABLE_COPY_MOVE(Class) \
    Q_DISABLE_COPY_MOVE(Class)

/**********************************
 * Compatibility workaround
 *********************************/
#if QT_VERSION < QT_VERSION_CHECK(6, 4, 0)
#   define TB_QTCOMPAT_STR_VIEW const QString&
#else
#   define TB_QTCOMPAT_STR_VIEW QAnyStringView
#endif

#endif // TOOLBOXQT_GLOBAL_H
