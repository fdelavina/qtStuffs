TEMPLATE = subdirs

SUBDIRS = lib/dynamicSoologic
SUBDIRS+= lib/fEngine
SUBDIRS+= lib/window
# build must be last:
#CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
#CONFIG += TEST
# build must be last:
CONFIG += ordered
CONFIG += opencv_32_bit

TEST {
SUBDIRS += test
} else {
SUBDIRS += app
}

