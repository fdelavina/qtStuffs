#ifndef GLOBALLIB_H
#define GLOBALLIB_H

    #include <QtCore/qglobal.h>

    #if defined(_FRANSILOG)
    #define FRANSILOG_EXPORT Q_DECL_EXPORT
    #else
    #define FRANSILOG_EXPORT Q_DECL_IMPORT
    #endif

#endif // GLOBALLIB_H
