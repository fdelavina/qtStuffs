QT       += core gui
TARGET = WidgetDLL
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TEMPLATE = lib

DEFINES = TEST

HEADERS+=$$PWD/test.h
SOURCES+=$$PWD/test.cpp



# Default rules for deployment.
DESTDIR    += $$OUT_PWD/../MyProject/debug
target.path = $$OUT_PWD/../MyProject/debug
INSTALLS += target



