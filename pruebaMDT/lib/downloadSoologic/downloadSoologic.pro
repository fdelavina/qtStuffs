DEFINES += _DOWNLOADSOOLOGIC
QT       += core network gui

CONFIG += c++11

TARGET = DownloadSoologic

include(../../common/common.pri)
include(../../globalLib/Global/globalLib.pri)
include(../../Configs/Lib/libconfig.pri)
include(src/src.pri)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

