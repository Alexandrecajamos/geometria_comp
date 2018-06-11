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








