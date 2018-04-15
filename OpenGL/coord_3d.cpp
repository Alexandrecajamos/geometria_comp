#include "coord_3d.h"

Coord_3D::Coord_3D()
{

}
Coord_3D::Coord_3D(float _x, float _y, float _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}
void Coord_3D::ImpCoord_3D(){
    std::cout << "\nCoor.: " << this->x <<", "<< this->y<<", "<< this->z <<"; "<< endl;
}
