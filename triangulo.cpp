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
float triangulo::Ray_intersept(Coord_3D Po, Coord_3D D){
    float t = -1;

    Coord_3D p1,p2,p3;
    p1= *(this->P1);
    p2= *(this->P2);
    p3= *(this->P3);

    Coord_3D nF = this->Normal;
    float PE = ProdutoEscalar3D(D,nF);
    if(PE<0){

        Coord_3D v1 = p2;
        Coord_3D v2 = p3;
        v1.operator -=(&p1);
        v2.operator -=(&p1);

        transformacoes tr;
        float M[3][3];
        M[0][0] = v1.x; M[1][0] = v1.y; M[2][0] = v1.z;
        M[0][1] = v2.x; M[1][1] = v2.y; M[2][1] = v2.z;
        M[0][2] = -D.x;  M[1][2] = -D.y;  M[2][2] = -D.z;
        float det = tr.Det3x3(M);
        tr.Inv3x3(M,det);
        Coord_3D b = Po;
        b.operator -=(&p1);
        Coord_3D lamb = tr.mxv(M,&b);

        float l3 = 1-(lamb.x+lamb.y);

        if(lamb.x>=0 && lamb.x<=1 && lamb.y>=0 && lamb.y<=1 && l3>=0 && l3<=1 && lamb.z>0){
            //std::cout << "\n" << lamb.x << ", " << lamb.y << ", " << lamb.z;
            t = lamb.z;

        }

    }
    return t;
}

