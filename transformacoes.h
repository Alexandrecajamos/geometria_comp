#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H
#define TAM 4
#include "coord_3d.h"
class transformacoes
{
public:
    transformacoes();
    void Identidade(float I[TAM][TAM]);
    void Escala(float E[TAM][TAM], float e[TAM-1]);
    void Translacao(float T[TAM][TAM], float t[TAM-1]);


    void MxM(float A[TAM][TAM],float B[TAM][TAM],float C[TAM][TAM]);
    void MxV(float M[TAM][TAM], Coord_3D *P);
    void Imp(float M[TAM][TAM]);
    float Det3x3(float M[TAM-1][TAM-1]);
    void Inv3x3(float M[TAM-1][TAM-1], float det);
    Coord_3D mxv(float M[TAM-1][TAM-1], Coord_3D *P);

};

#endif // TRANSFORMACOES_H
