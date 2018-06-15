#ifndef INTERSECET3D_H
#define INTERSECET3D_H

#include "coord_3d.h"
#include "face.h"
#include "vector"
int intersect(Coord_3D *A1,Coord_3D *A2,Coord_3D *A3,Coord_3D *B1,Coord_3D *B2,Coord_3D *B3);

int intersectF(Face *F1, Face *F2, vector<Coord_3D*> *Pontos);


#endif // INTERSECET3D_H
