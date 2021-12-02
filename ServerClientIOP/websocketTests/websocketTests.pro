TEMPLATE = subdirs

SUBDIRS = FransiComm \
          FransiLog \


# build must be last:
CONFIG += ordered

CONFIG += c++11 console
CONFIG -= app_bundle

# build must be last:
CONFIG += ordered
SUBDIRS += MiApp

