TARGET = SVCMNumPad

# Include translations
TRANSLATIONS = es.ts

QT = core gui widgets qml quick quickwidgets

# Relative path to root project directory
ROOTDIR = $$PWD/../../../../../../

# Include common build variables
include ($$ROOTDIR/build/common.pri)

# Include specific build type variables
include ($$ROOTDIR/build/lib.pri)

# Internal dependencies
LIBS += \
    $$WIDGETS_LIBS \
    -lDataManagerDB \
    -lDataManagerFavDB\
    -lDataManager \
    -lSVCMSCPMDB\
    -lSVCMHmiFavDB\
    -lSVCMPlanificadorFavDB\
    -lCMSStyle \
    -lLog \
    -lSignalHandler \
    -lPubSubComm -lNeommMessage -lCMSMessages \
    -lUSSBase \
    -lSVCMCommsAPI \
    -lTutorial \
    -lSVCMHmiFavConnector \
    -lSVCMScpmFavConnector \
    -lConfirmDialog

# External dependencies
LIBS += -lncqmlsymbols

SOURCES += \
    SVCMNumPadMain.cpp \
    SVCMNumPadControlWindow.cpp \
    SVCMNumPad.cpp \
    QLineEditNumPad.cpp \
    svcmnumpaddelegate.cpp
    QLineEditNumPad.cpp

HEADERS += \
    SVCMNumPad.h \
    SVCMNumPadControlWindow.h \
    QLineEditNumPad.h \
    svcmnumpaddelegate.h
    QLineEditNumPad.h

FORMS += \  
    SVCMNumPadControlWindow.ui

RESOURCES += resources.qrc
