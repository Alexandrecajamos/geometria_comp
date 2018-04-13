#ifndef FECHO2D_H
#define FECHO2D_H
#include "vetor.h"
#include "poligono.h"

Poligono* QHRec(Poligono* Pol, Coord_2D* a, Coord_2D*b);
Poligono* QuickHull(Poligono* Pol);
Poligono* Particiona(Poligono* Pol, Coord_2D* a, Coord_2D*b);
Coord_2D* Pmax(Poligono* Pol, Coord_2D* a, Coord_2D*b);

#endif // FECHO2D_H