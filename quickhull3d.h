#ifndef QUICKHULL3D_H
#define QUICKHULL3D_H

#include "vetor.h"
#include "objeto.h"

Objeto* QuickHull(Objeto* Pol);

Objeto* QuickHull_Recursivo(Objeto* Pol, Coord_3D* a, Coord_3D*b, Coord_3D*c);
Objeto* Particiona(Objeto* Pol, Coord_3D* a, Coord_3D*b, Coord_3D*c);
Coord_3D* Pmax(Objeto* Pol, Coord_3D* a, Coord_3D*b, Coord_3D*c);



#endif // QUICKHULL3D_H
