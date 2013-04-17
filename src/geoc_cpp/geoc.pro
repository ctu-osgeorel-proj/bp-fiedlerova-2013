#-------------------------------------------------
#
# Project created by QtCreator 2013-02-03T09:54:46
#
#-------------------------------------------------

DEFINES += GEOCLIBRARY

TEMPLATE = lib

SOURCES += \
    vertexsnapper.cpp \
    matchinggeometry.cpp \
    affinetransformation.cpp \
    triangulation.cpp \
    vertexgeometryoperation.cpp \
    triangle.cpp \
    coveragealignment.cpp \
    aligngeometryeditoroperation.cpp \
    linematcher.cpp

HEADERS += geoc.h\
    vertexsnapper.h \
    matchinggeometry.h \
    affinetransformation.h \
    triangulation.h \
    vertexgeometryeditoroperation.h \
    triangle.h \
    coveragealignment.h \
    aligngeometryeditoroperation.h \
    sort.h \
    geocgeom.h \
    linematcher.h


unix:LIBS += -L/usr/local/lib \
        -lgeos \
	-lgeos_c
