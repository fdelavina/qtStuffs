#ifndef GLOBALLIB_H
#define GLOBALLIB_H

#include <QtCore/qglobal.h>

#if defined(_LIB1)
#   define LIB1SHARED_EXPORT Q_DECL_EXPORT
# else
#   define LIB1SHARED_EXPORT Q_DECL_IMPORT
# endif

#endif // GLOBALLIB_H
