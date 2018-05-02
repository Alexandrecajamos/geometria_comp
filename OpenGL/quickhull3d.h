#ifndef QUICKHULL3D_H
#define QUICKHULL3D_H

#include "vetor.h"
#include "objeto.h"

Objeto* QuickHull(Objeto* Pol);

void QuickHull_Recursivo(Objeto* Pol, int a, int b, int c, bool *validos);
void Particiona(Objeto* Pol, int a, int b, int c, bool *validos);
int Pmax(Objeto* Pol, int a, int b, int c, bool *validos);
int ContaValidos(bool* validos, int N);
bool* CopiaValidos(bool* validos, int N);
bool Coplanares(Coord_3D nFace,int P1, int P, Objeto* Pol);
Coord_3D Normal(Coord_3D* P1, Coord_3D*P2, Coord_3D*P3);
Face Extremos(Objeto* Pol);



Objeto* QuickHull2(Objeto* Obj);
void QuickHull_Recursivo2(Objeto* Obj, int* Parte, int nP, int a, int b, int c);
int Particiona2(Objeto* Obj,int* Validos,int nV, int* Parte, int iA, int iB, int iC);
int Pmax2(Objeto* Obj,int* Parte, int nP, Coord_3D* a, Coord_3D* b, Coord_3D* c);

#endif // QUICKHULL3D_H
