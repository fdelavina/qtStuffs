TEMPLATE = app
TARGET = ejecutable

SOURCES+=main.cpp
LIBS+= -L$$OUT_PWD//../Lib1/Release -lLib1Shared


INCLUDEPATH += $$PWD/../Lib1
DEPENDPATH  += $$PWD/../Lib1

