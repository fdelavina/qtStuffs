
CONFIG += c++11 console
QT -= gui
CONFIG -= app_bundle
include (../Common/common.pri)
include (../Configs/app/appconfig.pri)
QT += core

LIBS+= -lFransiLog\
       -lFransiComm

SOURCES += main.cpp

TARGET = MiApp

