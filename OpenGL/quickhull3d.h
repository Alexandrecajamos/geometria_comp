#ifndef QUICKHULL3D_H
#define QUICKHULL3D_H

#include "vetor.h"
#include "objeto.h"


Objeto* QuickHull(Objeto* Obj);
void QuickHull_Recursivo(Objeto* Obj, int* Parte, int nP, int a, int b, int c);
int Particiona(Objeto* Obj,int* Validos,int nV, int* Parte, int iA, int iB, int iC);
int Pmax(Objeto* Obj,int* Validos, int nP, Coord_3D* a, Coord_3D* b, Coord_3D* c);
int Pontos_Fecho(Objeto* Fecho, int* Pontos);
int MaiorY(int MX, Objeto* O);

Objeto* QuickHull2(Objeto* Obj);
bool Pertence(Objeto *Obj, int iA, int iB, int iC);
void Exclui_Internas(Objeto *Obj);

#endif // QUICKHULL3D_H
