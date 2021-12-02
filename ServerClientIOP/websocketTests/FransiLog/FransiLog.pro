QT       -= gui
DEFINES += _FRANSILOG
TARGET = FransiLog

include (../Common/common.pri)
include(../globalLib/Global/globalLib.pri)
include (../Configs/lib/libconfig.pri)

INCLUDEPATH += $$PWD

SOURCES += $$PWD/QLogger.cpp \
    $$PWD/QLoggerWriter.cpp

HEADERS += $$PWD/QLogger.h \
    $$PWD/QLoggerLevel.h \
    $$PWD/QLoggerWriter.h


QMAKE_CXXFLAGS += -std=c++14
