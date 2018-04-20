#include "vetor.h"



float NormaVetor2D(Coord_2D V){
    return sqrt(V.x*V.x + V.y*V.y);
}
void NormalizaVetor2D(Coord_2D *V){
    float len = NormaVetor2D((*V));
    V->x/=len; V->y /= len;
}

float ProdutoEscalar2D(Coord_2D V1, Coord_2D V2){
    return ((V1.x*V2.x)+(V1.y*V2.y));
}
float Distancia2D(Coord_2D V1, Coord_2D V2){
    Coord_2D Vet(V1.x-V2.x, V1.y-V2.y);
    return NormaVetor2D(Vet);
}
float Angulo2D(Coord_2D V1, Coord_2D V2){
    float PE = ProdutoEscalar2D(V1,V2);
    float n1 = NormaVetor2D(V1);
    float n2 = NormaVetor2D(V2);
    return acos(PE/(n1*n2))* 180.0 / PI;
}
float AnguloOrientado2D(Coord_2D V){
    Coord_2D U(1,0);
    float ang = Angulo2D(V,U);

    if(V.y>=0)
        return ang;
    else
        return (360-ang);
}


float PseudoAngulo_Quad2D(Coord_2D V){
    if(V.y >=0){
        if(V.x >=0){
            if(V.x>=V.y)
                return V.y/V.x;
            return (2 - (V.x/V.y));
        }
        if(-V.x <= V.y)
            return (2 + ((-V.x)/V.y));
        return (4-(V.y/(-V.x)));
    }
    if(V.x<=0){
        if(-V.x>=-V.y)
            return (4+ ((-V.y)/(-V.x)));
        return (6- ((-V.x)/(-V.y)));
    }
    if(V.x<=-V.y)
        return (6+ (V.x/(-V.y)));
    return (8 - ((-V.y)/V.x));

}
float PseudoAngulo(Coord_2D V1, Coord_2D V2){
    float aV1 = PseudoAngulo_Quad2D(V1);
    float aV2 = PseudoAngulo_Quad2D(V2);
    if(aV2>aV1)
        return aV2-aV1;
    return (8-(aV1-aV2));
}
float ProdutoVetorial2D(Coord_2D V1, Coord_2D V2){
    return (V1.x*V2.y)-(V1.y*V2.x);
}

bool CCW2D(Coord_2D V1, Coord_2D V2){
    float k = ProdutoVetorial2D(V1, V2);
    if(k>0)
        return true;
    else
        return false;
}

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
bool CCW3D(Coord_3D V1, Coord_3D V2){
    Coord_2D A(V1.x,V1.y);
    Coord_2D B(V2.x,V2.y);
    return CCW2D(A,B);
}
