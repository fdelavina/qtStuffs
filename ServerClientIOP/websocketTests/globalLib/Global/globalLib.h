#ifndef GLOBALLIB_H
#define GLOBALLIB_H

#include <QtCore/qglobal.h>

#if defined(_FRANSICOMM)
#define FRANSICOMM_EXPORT Q_DECL_EXPORT
#else
#define FRANSICOMM_EXPORT Q_DECL_IMPORT
#endif

#if defined(_FRANSILOG)
#define QLOGGER_EXPORT Q_DECL_EXPORT
#else
#define QLOGGER_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBALLIB_H
