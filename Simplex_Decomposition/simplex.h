#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "coord_3d.h"
#include "vetor.h"

class Simplex
{
public:
    Simplex();
    Simplex(int A, int B, int C, int D);
    int A, B, C, D;
    void Geometria(vector<Coord_3D*> Pontos);
    Coord_3D Centro;
    float AreaExt;
    float Volume;




};

#endif // SIMPLEX_H
