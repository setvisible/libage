#isEmpty(TEMPLATE):TEMPLATE=app
TARGET       = tst_generator
CONFIG      += testcase
QT           = core testlib
SOURCES     += tst_generator.cpp

# QT       += widgets xml

# Include:
INCLUDEPATH += $$PWD/../../../include

#-------------------------------------------------
# LINKING TO OSG
#-------------------------------------------------
include( $$PWD/../../../3rd/3rd.pri )

#-------------------------------------------------
# LINKING TO LIBAGE
#-------------------------------------------------
LIBS += -lAGE
LIBS += -L$${OUT_PWD}/../../../../libAGE

#-------------------------------------------------
# OUTPUT
#-------------------------------------------------
DESTDIR = $${OUT_PWD}/../../../../libAGE

