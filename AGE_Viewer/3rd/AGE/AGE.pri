# AGE Core
INCLUDEPATH += $$PWD/../../../AGE_Core/include

LIBAGE_DESTDIR = $${OUT_PWD}/../../libAGE
LIBS += -L$${LIBAGE_DESTDIR}
LIBS += -lAGE
