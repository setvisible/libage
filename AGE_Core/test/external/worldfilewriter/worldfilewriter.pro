#isEmpty(TEMPLATE):TEMPLATE=app
TARGET       = tst_worldfilewriter
CONFIG      += testcase
QT           = core testlib
SOURCES     += tst_worldfilewriter.cpp

# Include:
INCLUDEPATH += $$PWD/../../../include

#-------------------------------------------------
# Definitions
#-------------------------------------------------
DEFINES += LIBAGE_LIBRARY

#-------------------------------------------------
# LINKING TO OSG
#-------------------------------------------------

#-------------------------------------------------
# LINKING TO LIBAGE
#-------------------------------------------------
LIBS += -lAGE
LIBS += -L$${OUT_PWD}/../../../../libAGE

#-------------------------------------------------
# SOURCES
#-------------------------------------------------
HEADERS += $$PWD/../../../src/io/worldfilewriter.h
HEADERS += $$PWD/../../../src/io/worldfilewriter_p.h
SOURCES += $$PWD/../../../src/io/worldfilewriter.cpp

#-------------------------------------------------
# OUTPUT
#-------------------------------------------------
DESTDIR = $${OUT_PWD}/../../../../libAGE

