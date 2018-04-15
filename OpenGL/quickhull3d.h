#ifndef QUICKHULL3D_H
#define QUICKHULL3D_H

#include "vetor.h"
#include "objeto.h"

void QuickHull(Objeto* Pol);

void QuickHull_Recursivo(Objeto* Pol, int a, int b, int c, bool *validos, bool*Fecho);
void Particiona(Objeto* Pol, int a, int b, int c, bool *validos);
int Pmax(Objeto* Pol, int a, int b, int c, bool *validos, bool *Fecho);
bool* CopiaValidos(bool* validos, int N);
bool Coplanares(Coord_3D nFace,int P1, int P, Objeto* Pol);
Coord_3D Normal(Coord_3D* P1, Coord_3D*P2, Coord_3D*P3);

#endif // QUICKHULL3D_H
