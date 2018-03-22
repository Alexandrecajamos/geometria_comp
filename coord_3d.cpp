#include "coord_3d.h"

Coord_3D::Coord_3D()
{

}
Coord_3D::Coord_3D(float _x, float _y, float _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

float Coord_3D::Produto_Escalar_Vetor(Coord_3D *C){
    float x= (this->x*C->x)+(this->y*C->y)+(this->z*C->z);
    return x;
}
void Coord_3D::ImpCoord_3D(){
    std::cout << "\nCoor.: " << this->x <<", "<< this->y<<", "<< this->z <<"; "<< endl;
}

float Coord_3D::Distancia_Vetor(Coord_3D *B){
    Coord_3D C(this->x,this->y,this->z);
    C.operator -=(B);
    float Dis = C.norma_Vetor();;
    return Dis;
}

float Coord_3D::Angulo_Vetor(Coord_3D *C2){
    float PE = this->Produto_Escalar_Vetor(C2);
    float n1 = this->norma_Vetor();
    float n2 = C2->norma_Vetor();
    return acos(PE/(n1*n2))* 180.0 / PI;
}

Coord_3D* Coord_3D::Produto_Vetorial(Coord_3D *B){

    float x,y,z;
    x = (this->y*B->z)-(this->z*B->y);
    y = (this->z*B->x)-(this->x*B->z);
    z = (this->x*B->y)-(this->y*B->x);
    Coord_3D *PV = new Coord_3D(x,y,z);
    return PV;
}

float Coord_3D::Produto_Vetorial2D(Coord_3D *B){
    return (this->x*B->y)-(this->y*B->x);
}

bool Coord_3D::ccw(Coord_3D *B){
    float k = this->Produto_Vetorial2D(B);
    if(k>0)
        return true;
    else
        return false;

}
