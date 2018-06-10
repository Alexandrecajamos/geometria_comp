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
bool intersept(Coord_2D A, Coord_2D B, Coord_2D C, Coord_2D D){
    Coord_2D V1 = B;
    Coord_2D V2 = C;
    Coord_2D V3 = D;
    V1.operator -=(&A);
    V2.operator -=(&A);
    V3.operator -=(&A);

    float x= ProdutoVetorial2D(V1, V2);
    float y= ProdutoVetorial2D(V1, V3);

    if((x*y)<0)
        return true;
    return false;
}
float Area(Coord_2D *a, Coord_2D *b, Coord_2D *c){

    Coord_2D A1(b->x,b->y);
    Coord_2D A2(c->x,c->y);
    A1.operator -=(a);
    A2.operator -=(a);
    return ProdutoVetorial2D(A1,A2)/2;

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


Coord_3D Normal(Coord_3D* P1, Coord_3D*P2, Coord_3D*P3){

    Coord_3D p1=*(P1);
    Coord_3D a=*(P2);
    Coord_3D b=*(P3);

    a.operator -=(&p1);
    b.operator -=(&p1);
//    a.ImpCoord_3D();
//    b.ImpCoord_3D();

    p1.x=(a.y*b.z)-(a.z*b.y);
    p1.y=(a.z*b.x)-(a.x*b.z);
    p1.z=(a.x*b.y)-(a.y*b.x);

    return p1;

}











float ANGSolido(Coord_3D *A,Coord_3D *B, Coord_3D *C, Coord_3D *O){

    Coord_3D oa = *O, ob = *O, oc = *O;
    oa.operator -=(A);
    ob.operator -=(B);
    oc.operator -=(C);

    Coord_3D na_n(0,0,0),nb_n(0,0,0),nc_n(0,0,0);

    Coord_3D na = ProdutoVetorial3D(ob,oc);
    Coord_3D nb = ProdutoVetorial3D(oc,oa);
    Coord_3D nc = ProdutoVetorial3D(oa,ob);

    NormalizaVetor3D(&na);
    NormalizaVetor3D(&nb);
    NormalizaVetor3D(&nc);

    na_n.operator -=(&na);
    nb_n.operator -=(&nb);
    nc_n.operator -=(&nc);

    float P1 = ProdutoEscalar3D(na,nb_n), P2 = ProdutoEscalar3D(nb,nc_n), P3 = ProdutoEscalar3D(nc,na_n);

    return acos(P1)+acos(P2)+acos(P3)-PI;

}
float** RankAngSol(Coord_3D *A,Coord_3D *B, Coord_3D *C, std::vector<Coord_3D*> Pontos, int* Candidatos, int nC, bool Ord){

    float ** Rank = (float**)malloc(sizeof(float*)*nC);
    for(int i=0;i<nC;i++){
        Rank[i]=(float*)malloc(sizeof(float)*2);
        Rank[i][0]=ANGSolido(A,B,C,Pontos[Candidatos[i]]);
        Rank[i][1]=Candidatos[i];
    }

    if(Ord)
        QuickSortM(Rank,0, nC-1,0,2);
    return Rank;
}
float** RankDist(Coord_3D Otm, std::vector<Coord_3D*> Pontos, int* Candidatos, int nC, bool Ord){
    float ** Rank = (float**)malloc(sizeof(float*)*nC);
    for(int i=0;i<nC;i++){
        Rank[i]=(float*)malloc(sizeof(float)*2);
        Rank[i][0]=Distancia3D(Otm, *Pontos[Candidatos[i]]);
        Rank[i][1]=Candidatos[i];
    }

    if(Ord)
        QuickSortM(Rank,0, nC-1,0,2);
    return Rank;
}



float** RankDistFace(Coord_3D *A, Coord_3D *B, Coord_3D *C, std::vector<Coord_3D *> Pontos, int *Candidatos, int nC, bool Ord){
    float ** Rank = (float**)malloc(sizeof(float*)*nC);
    Coord_3D nF = Normal(A,B,C);
    NormalizaVetor3D(&nF);
    for(int i=0;i<nC;i++){
        Rank[i]=(float*)malloc(sizeof(float)*2);
        Coord_3D Temp = *Pontos[Candidatos[i]];
        Temp.operator -=(A);
//        NormalizaVetor3D(&Temp);
        Rank[i][0]=ProdutoEscalar3D(nF,Temp);
        Rank[i][1]=Candidatos[i];
    }

    if(Ord)
        QuickSortM(Rank,0, nC-1,0,2);
    return Rank;
}








