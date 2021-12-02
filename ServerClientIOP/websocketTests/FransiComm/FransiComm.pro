QT       -= gui
QT       += core websockets
DEFINES += _FRANSICOMM
TARGET = FransiComm

include (../Common/common.pri)
include(../globalLib/Global/globalLib.pri)
include (../Configs/lib/libconfig.pri)


INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += $$PWD/ClientWS.cpp \
           $$PWD/ServerWS.cpp

HEADERS += $$PWD/ClientWS.h \
           $$PWD/ServerWS.h


