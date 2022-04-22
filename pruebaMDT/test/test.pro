QT       += core network
CONFIG += c++11 console
include (../common/common.pri)
include (../Configs/App/appconfig.pri)

LIBS+=-lDynamicSologic \
      -lDownloadSoologic

SOURCES += \
    main.cpp

TARGET = test
