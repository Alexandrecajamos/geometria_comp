#ifndef QUICKHULL3D_H
#define QUICKHULL3D_H

#include "vetor.h"
#include "objeto.h"


Coord_3D Normal(Coord_3D* P1, Coord_3D*P2, Coord_3D*P3);
Face Extremos(Objeto* Pol);


Objeto* QuickHull(Objeto* Obj);
void QuickHull_Recursivo(Objeto* Obj, int* Parte, int nP, int a, int b, int c);
int Particiona(Objeto* Obj,int* Validos,int nV, int* Parte, int iA, int iB, int iC);
int Pmax(Objeto* Obj,int* Parte, int nP, Coord_3D* a, Coord_3D* b, Coord_3D* c);
int Pontos_Fecho(Objeto* Fecho, int* Pontos);



#endif // QUICKHULL3D_H
