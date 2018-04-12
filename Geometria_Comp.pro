TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    coord_3d.cpp \
    coord_2d.cpp \
    triangulo.cpp \
    esfera.cpp \
    objeto.cpp \
    transformacoes.cpp \
    vetor.cpp \
    poligono.cpp \
    fecho2d.cpp \
    quickhull3d.cpp

HEADERS += \
    coord_3d.h \
    coord_2d.h \
    ordenacao.h \
    triangulo.h \
    transformacoes.h \
    esfera.h \
    objeto.h \
    vetor.h \
    poligono.h \
    fecho2d.h \
    quickhull3d.h
