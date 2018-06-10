#ifndef FECHO2D_H
#define FECHO2D_H
#include "vetor.h"
#include "poligono.h"
#include "ordmatriz.h"
bool Pertence(Coord_2D C1, Coord_2D C2, Coord_2D C3);


Poligono* QHRec(Poligono* Pol, Coord_2D* a, Coord_2D*b);
Poligono* QuickHull(Poligono* Pol);
Poligono* Particiona(Poligono* Pol, Coord_2D* a, Coord_2D*b);
int Pmax(Poligono* Pol, Coord_2D* a, Coord_2D*b);

Poligono* Jarvis(Poligono* Pol);

Poligono* Estrelado(Poligono* Pol);
Poligono* Graham(Poligono*Pol);

Poligono* MergeHull(Poligono *Pol);
Poligono* MergeHull_Rec(Poligono *Pol);
Poligono* Merge(Poligono *P1, Poligono *P2);


#endif // FECHO2D_H
