#-------------------------------------------------
#
# Project created by QtCreator 2015-11-13T13:00:43
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT_OpenGL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    coord_3d.cpp \
    coord_2d.cpp \
    esfera.cpp \
    objeto.cpp \
    vetor.cpp \
    quickhull3d.cpp \
    face.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    coord_3d.h \
    coord_2d.h \
    esfera.h \
    objeto.h \
    vetor.h \
    fecho2d.h \
    quickhull3d.h \
    face.h


FORMS    += mainwindow.ui

LIBS += -lglut -lGLU
