#ifndef COORD_2D_H
#define COORD_2D_H
#include <iostream>
#include <math.h>
#define PI 3.14159265
using namespace std;

class Coord_2D
{
public:
    Coord_2D();
    Coord_2D(float _x, float _y);
    Coord_2D& operator+=(Coord_2D *C) {
            x += C->x; y += C->y;
            return *this;
        }
    Coord_2D& operator*=(float Esc) {
            x *= Esc; y *= Esc;
            return *this;
        }
    Coord_2D& operator-=(Coord_2D *V){
            x -= V->x; y -= V->y;
            return *this;
        }
    Coord_2D operator/(float div) const {
            return Coord_2D(x/div, y/div);
        }
    Coord_2D& operator/=(float div) {
            x /= div; y/= div;
            return *this;
        }
    void ImpCoord_2D();
    float x,y;
};


#endif // COORD_2D_H
