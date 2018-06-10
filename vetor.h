#ifndef VETOR_H
#define VETOR_H

#include "coord_2d.h"
#include "coord_3d.h"

#include<vector>
#include "ordmatriz.h"

#define PI 3.14159265


float NormaVetor2D(Coord_2D V);
void NormalizaVetor2D(Coord_2D *V);
float ProdutoEscalar2D(Coord_2D V1, Coord_2D V2);
float ProdutoVetorial2D(Coord_2D V1, Coord_2D V2);
float Distancia2D(Coord_2D V1, Coord_2D V2);
float Angulo2D(Coord_2D V1, Coord_2D V2);
float AnguloOrientado2D(Coord_2D V);
float PseudoAng2D(Coord_2D V1, Coord_2D V2);
float PseudoAngulo_Quad2D(Coord_2D V);
float PseudoAngulo(Coord_2D V1, Coord_2D V2);
bool CCW2D(Coord_2D V1, Coord_2D V2);
bool intersept(Coord_2D A, Coord_2D B, Coord_2D C, Coord_2D D);
float Area(Coord_2D *a, Coord_2D *b, Coord_2D *c);
//3D

float NormaVetor3D(Coord_3D V);
float ProdutoEscalar3D(Coord_3D V1, Coord_3D V2);
float Distancia3D(Coord_3D V1, Coord_3D V2);
Coord_3D ProdutoVetorial3D(Coord_3D V1, Coord_3D V2);
float Angulo3D(Coord_3D V1, Coord_3D V2);
void NormalizaVetor3D(Coord_3D *V);
bool CCW3D(Coord_3D V1, Coord_3D V2);



Coord_3D Normal(Coord_3D* P1, Coord_3D*P2, Coord_3D*P3);


//Novo

float ANGSolido(Coord_3D *A,Coord_3D *B, Coord_3D *C, Coord_3D *O);
float** RankAngSol(Coord_3D *A,Coord_3D *B, Coord_3D *C, std::vector<Coord_3D*> Pontos, int* Candidatos, int nC, bool Ord);
float** RankDist(Coord_3D Otm, std::vector<Coord_3D*> Pontos, int* Candidatos, int nC, bool Ord);
float** RankDistFace(Coord_3D *A,Coord_3D *B, Coord_3D *C, std::vector<Coord_3D*> Pontos, int* Candidatos, int nC, bool Ord);
#endif // VETOR_H
