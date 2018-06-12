#-------------------------------------------------
#
# Project created by QtCreator 2018-06-12T10:12:46
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simplex_Decomposition
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    coord_3d.cpp \
    coord_2d.cpp \
    esfera.cpp \
    objeto.cpp \
    vetor.cpp \
    ordmatriz.cpp \
    face.cpp \
    triangulacao.cpp \
    simplex.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    coord_3d.h \
    coord_2d.h \
    esfera.h \
    objeto.h \
    vetor.h \
    ordmatriz.h \
    face.h \
    triangulacao.h \
    simplex.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU

RESOURCES += \
    crab.qrc
