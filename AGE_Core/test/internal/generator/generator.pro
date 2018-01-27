#isEmpty(TEMPLATE):TEMPLATE=app
TARGET       = tst_generator
CONFIG      += testcase
QT           = core testlib
SOURCES     += tst_generator.cpp

# Include:
INCLUDEPATH += $$PWD/../../../include

#-------------------------------------------------
# Definitions
#-------------------------------------------------
DEFINES += LIBAGE_LIBRARY

#-------------------------------------------------
# LINKING TO OSG
#-------------------------------------------------
include( $$PWD/../../../AGE_Core_config.pri )
include( $$PWD/../../../3rd/3rd.pri )

#-------------------------------------------------
# LINKING TO LIBAGE
#-------------------------------------------------
LIBS += -lAGE
LIBS += -L$${OUT_PWD}/../../../../libAGE

#-------------------------------------------------
# SOURCES
#-------------------------------------------------
HEADERS += $$PWD/../../../src/generator.h
SOURCES += $$PWD/../../../src/generator.cpp

HEADERS += $$PWD/../../../src/math/voronoi.h
SOURCES += $$PWD/../../../src/math/voronoi.cpp

#-------------------------------------------------
# OUTPUT
#-------------------------------------------------
DESTDIR = $${OUT_PWD}/../../../../libAGE

