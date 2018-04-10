#ifndef ESFERA_H
#define ESFERA_H
#include "vetor.h"

class Esfera
{
public:
    Esfera();
    Esfera(Coord_3D c, float r);
    bool Interseccao(Coord_3D p);
    Coord_3D centro;
    float raio;
};

#endif // ESFERA_H
