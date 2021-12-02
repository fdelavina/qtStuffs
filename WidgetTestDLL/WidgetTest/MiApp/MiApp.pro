QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../Lib1
DEPENDPATH  += $$PWD/../Lib1


LIBS += -L$$OUT_PWD/../MyProject/debug -lWidgetDLL
SOURCES += \
    main.cpp 
TARGET = MiAplicacion

