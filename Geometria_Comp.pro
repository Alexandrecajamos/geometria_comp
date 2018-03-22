TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    coord_3d.cpp \
    coord_2d.cpp \
    triangulo.cpp \
    transformacoes.cpp

HEADERS += \
    coord_3d.h \
    coord_2d.h \
    ordenacao.h \
    triangulo.h \
    transformacoes.h
