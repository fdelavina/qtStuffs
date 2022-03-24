#ifndef GLOBALLIB_H
#define GLOBALLIB_H

    #include <QtCore/qglobal.h>

    #if defined(_DYNAMICSOOLOGIC)
    #define DYNAMICSOOLOGIC_EXPORT Q_DECL_EXPORT
    #else
    #define DYNAMICSOOLOGIC_EXPORT Q_DECL_IMPORT
    #endif

    #if defined(_FENGINE)
    #define FENGINE_EXPORT Q_DECL_EXPORT
    #else
    #define FENGINE_EXPORT Q_DECL_IMPORT
    #endif

    #if defined(_WINDOW)
    #define WINDOW_EXPORT Q_DECL_EXPORT
    #else
    #define WINDOW_EXPORT Q_DECL_IMPORT
    #endif


#endif // GLOBALLIB_H
