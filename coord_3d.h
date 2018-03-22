#ifndef COORD_3D_H
#define COORD_3D_H
#include "cmath"
#include <iostream>
#include <math.h>
#define PI 3.14159265
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

        float norma_Vetor(){
            float len = sqrt(x*x + y*y + z*z );
            return len;
        }

        void normalize_Vetor(){
            float len = this->norma_Vetor();
            x/=len; y /= len; z /= len;
        }

        float Produto_Escalar_Vetor(Coord_3D *C2);
        float Distancia_Vetor(Coord_3D *C2);
        float Angulo_Vetor(Coord_3D *C2);
        Coord_3D* Produto_Vetorial(Coord_3D *B);
        float Produto_Vetorial2D(Coord_3D *B);
        bool ccw(Coord_3D *B);//counter Primitiva: counter-clockwise clockwise

        void ImpCoord_3D();

      float x,y,z;
};

#endif // COORD_3D_H
