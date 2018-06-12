#ifndef COORD_3D_H
#define COORD_3D_H
#include "cmath"
#include <iostream>
#include <math.h>
using namespace std;

class Coord_3D
{
public:
    Coord_3D();
    Coord_3D(float _x, float _y, float _z);
    Coord_3D& operator+=(Coord_3D *C) {
            x += C->x; y += C->y; z += C->z;
            return *this;
        }
    Coord_3D& operator*=(float Esc) {
            x *= Esc; y *= Esc; z *= Esc;
            return *this;
        }
    Coord_3D& operator-=(Coord_3D *V){
            x -= V->x; y -= V->y; z -= V->z;
            return *this;
        }
    Coord_3D operator/(float div) const {
            return Coord_3D(x/div, y/div, z/div);
        }
    Coord_3D& operator/=(float div) {
            x /= div; y/= div; z /= div;
            return *this;
        }
    void ImpCoord_3D();
    float x,y,z;
};

#endif // COORD_3D_H
