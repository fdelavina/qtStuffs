MAIN_DEST_DIR = $$shadowed($$PWD/..)


LIB_DEST_DIR = $$MAIN_DEST_DIR/lib
BIN_DEST_DIR = $$MAIN_DEST_DIR/bin

# rpath-link (for linker only)
QMAKE_LFLAGS += -Wl,-rpath-link,$$LIB_DEST_DIR

# Directories to look for libraries at runtime
# It's set relative to executable path at runtime ($ORIGIN)
QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/../lib\''

# Compilation temporaries destination
TMPDIR      = $$MAIN_DEST_DIR/tmp
OBJECTS_DIR = $$TMPDIR/obj/$$TARGET
MOC_DIR     = $$TMPDIR/moc/$$TARGET
UI_DIR      = $$TMPDIR/ui/$$TARGET
RCC_DIR     = $$TMPDIR/rcc/$$TARGET

INCLUDEPATH += $$PWD/../
DEPENDPATH  += $$PWD/../


LIBS += -L$$LIB_DEST_DIR






