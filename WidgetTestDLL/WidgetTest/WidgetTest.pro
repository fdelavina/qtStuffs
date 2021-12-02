QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = subdirs
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG(debug, debug|release) {
    message("debug mode")
}else {
    message("release mode")
}



SUBDIRS+=Lib1\
         MiApp
