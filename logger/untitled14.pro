TEMPLATE = subdirs

SUBDIRS = FransiLog

# build must be last:

CONFIG += c++11
CONFIG -= app_bundle

# build must be last:
CONFIG += ordered
SUBDIRS += main
