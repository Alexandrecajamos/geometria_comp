#include "triangulo.h"

triangulo::triangulo()
{

}
triangulo::triangulo(Coord_3D _P1, Coord_3D _P2, Coord_3D _P3){
    this->P1=&_P1;
    this->P2=&_P2;
    this->P3=&_P3;
    this->attNormal();
}
triangulo::triangulo(Coord_3D *_P1, Coord_3D *_P2, Coord_3D *_P3)
{
    this->P1=_P1;
    this->P2=_P2;
    this->P3=_P3;
    this->attNormal();

}
Coord_3D triangulo::calcNormal(){

    Coord_3D p1=*(this->P1);
    Coord_3D a=*(this->P2);
    Coord_3D b=*(this->P3);
    a.operator -=(&p1);
    b.operator -=(&p1);

    p1.x=(a.y*b.z)-(a.z*b.y);
    p1.y=(a.z*b.x)-(a.x*b.z);
    p1.z=(a.x*b.y)-(a.y*b.x);

    return p1;

}
void triangulo::attNormal(){
    this->Normal= this->calcNormal();
}
void triangulo::Barycentric(Coord_3D p, Coord_3D a, Coord_3D b, Coord_3D c, float &u, float &v, float &w)
{
    Coord_3D v0 = b; Coord_3D v1 = c; Coord_3D v2 = p;
    v0.operator -=(&a); v1.operator -=(&a); v2.operator -=(&a);

    float d00 = ProdutoEscalar3D(v0,v0); //v0v0
    float d01 = ProdutoEscalar3D(v0,v1); //v0v1
    float d11 = ProdutoEscalar3D(v1,v1);
    float d20 = ProdutoEscalar3D(v2,v0);
    float d21 = ProdutoEscalar3D(v2,v1);

    float denom = (d00 * d11) - (d01 * d01);

    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1-v-w;

}

void triangulo::Imp(){
    cout<<endl<< "Face formada pelos pontos: " <<endl;
    this->P1->ImpCoord_3D();
    this->P2->ImpCoord_3D();
    this->P3->ImpCoord_3D();
    cout<<endl;

}
