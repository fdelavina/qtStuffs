CONFIG += c++11 console
include (../common/common.pri)
include (../Configs/App/appconfig.pri)

LIBS+=-lDynamicSologic

SOURCES += \
    main.cpp

TARGET = test
