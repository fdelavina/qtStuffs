# Output directory configuration. 

CONFIG(debug,debug|release){
    CONFIG_DIR = Debugito
}
else{
    CONFIG_DIR = Releaseito
}



MAIN_DEST_DIR = $$clean_path($$PWD/../../output/$${CONFIG_DIR})


LIB_DEST_DIR = $$MAIN_DEST_DIR/lib
BIN_DEST_DIR = $$MAIN_DEST_DIR/bin

# Compilation temporaries destination
TMPDIR      = $$MAIN_DEST_DIR/tmp
OBJECTS_DIR = $$TMPDIR/obj/$$TARGET
MOC_DIR     = $$TMPDIR/moc/$$TARGET
UI_DIR      = $$TMPDIR/ui/$$TARGET
RCC_DIR     = $$TMPDIR/rcc/$$TARGET

INCLUDEPATH += $$PWD/../
DEPENDPATH  += $$PWD/../


LIBS += -L$$LIB_DEST_DIR






