DEFINES += _WINDOW
QT       += core gui

CONFIG += c++11

TARGET = Window

include(../../common/common.pri)
include(../../globalLib/Global/globalLib.pri)
include(../../Configs/Lib/libconfig.pri)
include(src/src.pri)

LIBS+= -lFengine
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

