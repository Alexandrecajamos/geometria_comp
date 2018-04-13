#ifndef QUICKHULL3D_H
#define QUICKHULL3D_H

#include "vetor.h"
#include "objeto.h"

void QuickHull(Objeto* Pol);

void QuickHull_Recursivo(Objeto* Pol, int a, int b, int c, bool *validos);
void Particiona(Objeto* Pol, int a, int b, int c, bool *validos);
int Pmax(Objeto* Pol, int a, int b, int c, bool *validos);

#endif // QUICKHULL3D_H
