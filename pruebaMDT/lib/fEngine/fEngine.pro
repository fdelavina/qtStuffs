DEFINES += _FENGINE
QT+=core
QT+=widgets
CONFIG += c++11

TARGET = Fengine

include(../../common/common.pri)
include(../../globalLib/Global/globalLib.pri)
include(../../Configs/Lib/libconfig.pri)
include(src/src.pri)

LIBS += -lopengl32 \
        -lDynamicSologic

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

