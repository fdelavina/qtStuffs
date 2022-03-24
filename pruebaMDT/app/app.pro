QT       += core widgets

CONFIG += c++11
include (../common/common.pri)
include (../Configs/App/appconfig.pri)

LIBS+= -lFengine \
       -lWindow \
       -lDynamicSologic

SOURCES += \
    main.cpp

TARGET = app
