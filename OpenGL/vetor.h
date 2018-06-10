#ifndef VETOR_H
#define VETOR_H

#include "coord_3d.h"

#define PI 3.14159265

//3D:

float NormaVetor3D(Coord_3D V);
float ProdutoEscalar3D(Coord_3D V1, Coord_3D V2);
float Distancia3D(Coord_3D V1, Coord_3D V2);
Coord_3D ProdutoVetorial3D(Coord_3D V1, Coord_3D V2);
float Angulo3D(Coord_3D V1, Coord_3D V2);
void NormalizaVetor3D(Coord_3D *V);
bool CCW3D(Coord_3D V1, Coord_3D V2);
//

Coord_3D Normal(Coord_3D* P1, Coord_3D*P2, Coord_3D*P3);
#endif // VETOR_H
