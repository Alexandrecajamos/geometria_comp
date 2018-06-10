#include "vetor.h"

//3D:

float NormaVetor3D(Coord_3D V){
    return sqrt(V.x*V.x + V.y*V.y + V.z*V.z );
}
float ProdutoEscalar3D(Coord_3D V1, Coord_3D V2){
    return ((V1.x*V2.x)+(V1.y*V2.y)+(V1.z*V2.z));
}
float Distancia3D(Coord_3D V1, Coord_3D V2){
    Coord_3D Vet(V1.x-V2.x, V1.y-V2.y, V1.z-V2.z);
    return NormaVetor3D(Vet);
}
Coord_3D ProdutoVetorial3D(Coord_3D V1, Coord_3D V2){
    float x,y,z;
    x = (V1.y*V2.z)-(V1.z*V2.y);
    y = (V1.z*V2.x)-(V1.x*V2.z);
    z = (V1.x*V2.y)-(V1.y*V2.x);
    Coord_3D PV(x,y,z);
    return PV;
}
float Angulo3D(Coord_3D V1, Coord_3D V2){
    float PE = ProdutoEscalar3D(V1, V2);
    float n1 = NormaVetor3D(V1);
    float n2 = NormaVetor3D(V2);
    return acos(PE/(n1*n2))* 180.0 / PI;
}
void NormalizaVetor3D(Coord_3D *V){
    float len = NormaVetor3D((*V));
    V->x/=len; V->y /= len; V->z /= len;
}
Coord_3D Normal(Coord_3D* P1, Coord_3D*P2, Coord_3D*P3){

    Coord_3D p1=*(P1);
    Coord_3D a=*(P2);
    Coord_3D b=*(P3);

    a.operator -=(&p1);
    b.operator -=(&p1);

    p1.x=(a.y*b.z)-(a.z*b.y);
    p1.y=(a.z*b.x)-(a.x*b.z);
    p1.z=(a.x*b.y)-(a.y*b.x);

    return p1;

}

