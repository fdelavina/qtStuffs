DEFINES += _FRANSILOG
QT       += core

CONFIG += c++11


include (../Common/common.pri)
include(../globalLib/Global/globalLib.pri)
include (../Configs/lib/libconfig.pri)

#include(FLog1/Flog1.pri)
include(FLog2/Flog2.pri)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TARGET = FransiLog
