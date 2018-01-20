#isEmpty(TEMPLATE):TEMPLATE=app
TARGET       = tst_worldfilewriter
CONFIG      += testcase
QT           = core testlib
SOURCES     += tst_worldfilewriter.cpp

# QT       += widgets xml

# Include:
INCLUDEPATH += $$PWD/../../../include


#-------------------------------------------------
# Definitions
#-------------------------------------------------
DEFINES += LIBAGE_LIBRARY

#-------------------------------------------------
# LINKING TO OSG
#-------------------------------------------------
include( $$PWD/../../../3rd/3rd.pri )

HEADERS += $$PWD/../../../src/io/worldfilewriter.h
SOURCES += $$PWD/../../../src/io/worldfilewriter.cpp

#-------------------------------------------------
# LINKING TO LIBAGE
#-------------------------------------------------
LIBS += -lAGE
LIBS += -L$${OUT_PWD}/../../../../libAGE

#-------------------------------------------------
# OUTPUT
#-------------------------------------------------
DESTDIR = $${OUT_PWD}/../../../../libAGE

