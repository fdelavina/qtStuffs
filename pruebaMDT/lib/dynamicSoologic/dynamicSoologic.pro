DEFINES += _DYNAMICSOOLOGIC
QT       += core 

CONFIG += c++11

TARGET = DynamicSologic

include(../../common/common.pri)
include(../../globalLib/Global/globalLib.pri)
include(../../Configs/Lib/libconfig.pri)
include(src/src.pri)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

