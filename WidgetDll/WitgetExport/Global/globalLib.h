#ifndef MYGLOBAL_H
#define MYGLOBAL_H

#include <QtGlobal>

#ifdef MY_LIB_STATICLIB
#  undef MY_LIB_SHAREDLIB
#  define MY_LIB_EXPORT
#else
#  ifdef MY_LIB_MAKEDLL
#   define MY_LIB_EXPORT Q_DECL_EXPORT
#  else
#   define MY_LIB_EXPORT Q_DECL_IMPORT
#  endif
#endif

#endif//MYGLOBAL_H
