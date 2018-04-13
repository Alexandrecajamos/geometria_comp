#ifndef QUICKHULL3D_H
#define QUICKHULL3D_H

#include "vetor.h"
#include "objeto.h"

void QuickHull(Objeto* Pol);

void QuickHull_Recursivo(Objeto* Pol, int a, int b, int c, bool *validos, bool*Fecho);
void Particiona(Objeto* Pol, int a, int b, int c, bool *validos);
int Pmax(Objeto* Pol, int a, int b, int c, bool *validos, bool *Fecho);
bool* CopiaValidos(bool* validos, int N);
#endif // QUICKHULL3D_H
