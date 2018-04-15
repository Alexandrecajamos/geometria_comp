#include "coord_2d.h"

Coord_2D::Coord_2D()
{

}
Coord_2D::Coord_2D(float _x, float _y) {
    this->x = _x;
    this->y = _y;
}

void Coord_2D::ImpCoord_2D(){
    std::cout << "\nCoor.: " << this->x <<", "<< this->y<<"; "<< endl;
}

