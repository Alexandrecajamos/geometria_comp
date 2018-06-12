#include "esfera.h"

Esfera::Esfera()
{
}
Esfera::Esfera(Coord_3D c, float r){
    this->centro=c;
    this->raio=r;

}
bool Esfera::Interseccao(Coord_3D r){
    float a = ProdutoEscalar3D(r,r);
    float b = ProdutoEscalar3D(r,this->centro);
    float c = ProdutoEscalar3D(this->centro,this->centro);
    c -=(this->raio*this->raio);
    float Delta = ((b*b)-4*a*c);
    bool ret=false;
    if(Delta>=0)
        ret = true;
    return ret;
}
