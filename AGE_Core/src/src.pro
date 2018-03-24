#-------------------------------------------------
# Project created by QtCreator
#-------------------------------------------------
TEMPLATE = lib
TARGET   = AGE
QT      += core gui
QT      += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += no_keyword

QMAKE_CXXFLAGS += -std=c++11

lessThan(QT_VERSION, 5.0) {
    warning("prefere to build it with Qt 5.0")
}

#-------------------------------------------------
# Definitions
#-------------------------------------------------
# IF(DYNAMIC_OPENSCENEGRAPH)
#     ADD_DEFINITIONS(-DOSG_LIBRARY)
# ELSE()
#     ADD_DEFINITIONS(-DOSG_LIBRARY_STATIC)
# ENDIF()
#
#if (DYNAMIC_LIBAGE) {
    DEFINES += LIBAGE_LIBRARY
#} else {
#    DEFINES += LIBAGE_LIBRARY_STATIC
#}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#-------------------------------------------------
# DEPENDANCIES
#-------------------------------------------------
include($$PWD/../AGE_Core_config.pri)
include($$PWD/../3rd/3rd.pri)

#-------------------------------------------------
# VERSION
#-------------------------------------------------
VERSION_FILENAME = $$PWD/../version

!exists( $${VERSION_FILENAME} ) {
    error( "Cannot find version file \"$${VERSION_FILENAME}\"" )
}

APP_VERSION = "$$cat($$VERSION_FILENAME)"
DEFINES += APP_VERSION=\\\"$$APP_VERSION\\\"


#-------------------------------------------------
# INCLUDE
#-------------------------------------------------
INCLUDEPATH += $$PWD/../include/

#-------------------------------------------------
# SOURCES
#-------------------------------------------------
include($$PWD/core/core.pri)
include($$PWD/database/database.pri)
include($$PWD/io/io.pri)
include($$PWD/math/math.pri)
include($$PWD/script/script.pri)

SOURCES += \
    $$PWD/generator.cpp \
    $$PWD/scene.cpp

HEADERS += \
    $$PWD/generator.h \
    $$PWD/scene.h \
    $$PWD/globals.h \
    $$PWD/namespaces.h \
    $$PWD/version.h


#-------------------------------------------------
# RESOURCES
#-------------------------------------------------
# RESOURCES = $$PWD/resources.qrc

#-------------------------------------------------
# BUILD OPTIONS
#-------------------------------------------------

# Rem: On Ubuntu, directories starting with '.' are hidden by default
win32{
    MOC_DIR =      ./.moc
    OBJECTS_DIR =  ./.obj
    UI_DIR =       ./.ui
}else{
    MOC_DIR =      ./_moc
    OBJECTS_DIR =  ./_obj
    UI_DIR =       ./_ui
}

#-------------------------------------------------
# OUTPUT
#-------------------------------------------------
DESTDIR = $${OUT_PWD}/../../libAGE


#-------------------------------------------------
# INSTALL
#-------------------------------------------------
# instructions for 'make install'
unix {
    target.path = /usr/lib
    INSTALLS += target
}
