#ifndef VETOR_H
#define VETOR_H

#include "coord_2d.h"
#include "coord_3d.h"

#define PI 3.14159265


float NormaVetor2D(Coord_2D V);
float ProdutoEscalar2D(Coord_2D V1, Coord_2D V2);
float Distancia2D(Coord_2D V1, Coord_2D V2);
float Angulo2D(Coord_2D V1, Coord_2D V2);
float AnguloOrientado2D(Coord_2D V);
float PseudoAngulo_Quad2D(Coord_2D V);

//3D:

float NormaVetor3D(Coord_3D V);
float ProdutoEscalar3D(Coord_3D V1, Coord_3D V2);
float Distancia3D(Coord_3D V1, Coord_3D V2);
Coord_3D ProdutoVetorial3D(Coord_3D V1, Coord_3D V2);
float Angulo3D(Coord_3D V1, Coord_3D V2);
float ProdutoVetorial2D(Coord_3D V1, Coord_3D V2);
bool CCW3D(Coord_3D V1, Coord_3D V2);
void NormalizaVetor3D(Coord_3D *V);

#endif // VETOR_H
