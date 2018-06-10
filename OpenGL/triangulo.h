#ifndef TRIANGULO_H
#define TRIANGULO_H
#include "vetor.h"

class triangulo
{
public:
    Coord_3D *P1,*P2,*P3, Normal;
    triangulo();
    triangulo(Coord_3D P1, Coord_3D P2, Coord_3D P3);
    triangulo(Coord_3D *P1, Coord_3D *P2, Coord_3D *P3);
    Coord_3D calcNormal();
    void attNormal();
    float Inter(Coord_3D P);
    void Barycentric(Coord_3D p, Coord_3D a, Coord_3D b, Coord_3D c, float &u, float &v, float &w);
    float Ray_intersept(Coord_3D Po, Coord_3D D);
    void Imp();
};

#endif // TRIANGULO_H
