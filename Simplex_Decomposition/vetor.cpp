#include "vetor.h"
//2D:


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

    Coord_2D ab = B;
    Coord_2D ac = C;
    Coord_2D ad = D;

    Coord_2D cd = D;
    Coord_2D ca = A;
    Coord_2D cb = B;

    ab.operator -=(&A);
    ac.operator -=(&A);
    ad.operator -=(&A);

    cd.operator -=(&C);
    ca.operator -=(&C);
    cb.operator -=(&C);

    float a = ProdutoVetorial2D(ab, ac);
    float b = ProdutoVetorial2D(ab, ad);
    float c = ProdutoVetorial2D(cd, ca);
    float d = ProdutoVetorial2D(cd, cb);

    if((a*b)<0 && (c*d)<0)
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


bool Aux_Itt(Coord_2D *A,Coord_2D *B,Coord_2D *D,Coord_2D *E,Coord_2D *F){
    return( intersept(*A,*B,*D,*E) ||intersept(*A,*B, *E, *F)|| intersept(*A,*B, *F, *D));
}

void Barycentric2D(Coord_2D *p, Coord_2D *a, Coord_2D *b, Coord_2D *c, float &u, float &v, float &w)
{
    Coord_2D v0 = *b; Coord_2D v1 = *c; Coord_2D v2 = *p;
    v0.operator -=(a); v1.operator -=(a); v2.operator -=(a);

    float d00 = ProdutoEscalar2D(v0,v0); //v0v0
    float d01 = ProdutoEscalar2D(v0,v1); //v0v1
    float d11 = ProdutoEscalar2D(v1,v1);
    float d20 = ProdutoEscalar2D(v2,v0);
    float d21 = ProdutoEscalar2D(v2,v1);

    float denom = (d00 * d11) - (d01 * d01);

    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1-v-w;
}


bool IttTriangulos(Coord_2D *A,Coord_2D *B,Coord_2D *C,Coord_2D *D,Coord_2D *E,Coord_2D *F){

    bool ret = false;

    if(Aux_Itt(A,B,D,E,F) || Aux_Itt(B,C,D,E,F) || Aux_Itt(C,A,D,E,F))
        ret = true;


    if(!ret){
        float u,v,w;
        Barycentric2D(D, A,B,C,u,v,w);
        if(u>=0 && v >=0 && w>=0  && u<1 && v <1 && w<1)
            return true;

        Barycentric2D(E, A,B,C,u,v,w);
        if(u>=0 && v >=0 && w>=0  && u<1 && v <1 && w<1)
            return true;

        Barycentric2D(F, A,B,C,u,v,w);
        if(u>=0 && v >=0 && w>=0  && u<1 && v <1 && w<1)
            return true;


        Barycentric2D(A, D,E,F,u,v,w);
        if(u>=0 && v >=0 && w>=0  && u<1 && v <1 && w<1)
            return true;

        Barycentric2D(B, D,E,F,u,v,w);
        if(u>=0 && v >=0 && w>=0  && u<1 && v <1 && w<1)
            return true;

        Barycentric2D(C, D,E,F,u,v,w);
        if(u>=0 && v >=0 && w>=0  && u<1 && v <1 && w<1)
            return true;

    }

    return ret;
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

float Dst(Coord_3D P, Coord_3D N, float d){
    return (ProdutoEscalar3D(P,N)+d);
}

void Barycentric(Coord_3D p, Coord_3D a, Coord_3D b, Coord_3D c, float &u, float &v, float &w)
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

bool InttTriangulos2D(Coord_3D *A,Coord_3D *B,Coord_3D *C,Coord_3D *D,Coord_3D *E,Coord_3D *F){


    Coord_2D Axy(A->x,A->y),Bxy(B->x,B->y), Cxy(C->x,C->y);
    Coord_2D Ayz(A->y,A->z),Byz(B->y,B->z), Cyz(C->y,C->z);
    Coord_2D Axz(A->x,A->z),Bxz(B->x,B->z), Cxz(C->x,C->z);

    Coord_2D Dxy(D->x,D->y),Exy(E->x,E->y),Fxy(F->x,F->y);
    Coord_2D Dyz(D->y,D->z),Eyz(E->y,E->z),Fyz(F->y,F->z);
    Coord_2D Dxz(D->x,D->z),Exz(E->x,E->z),Fxz(F->x,F->z);

    float A1 = abs(Area(&Axy, &Bxy, &Cxy));
    float A2 = abs(Area(&Ayz, &Byz, &Cyz));
    float A3 = abs(Area(&Axz, &Bxz, &Cxz));


//    cout << "Teste Areas : " << A1 << ", " << A2 << ", " << A3 << endl;

    if(A1 > A2 && A1 > A3)
        return IttTriangulos(&Axy, &Bxy, &Cxy,&Dxy, &Exy, &Fxy);
    if(A2>A3)
        return IttTriangulos(&Ayz, &Byz, &Cyz,&Dyz, &Eyz, &Fyz);

    return IttTriangulos(&Axz, &Bxz, &Cyz,&Dxz, &Exz, &Fxz);
}


bool IntersecaoTriangulos(Coord_3D *A,Coord_3D *B,Coord_3D *C,Coord_3D *D,Coord_3D *E,Coord_3D *F){

//    cout << "Teste Int" << endl;
    float h1,h2,h3,h4,h5,h6;
    Coord_3D n1, n2;
    n1 = Normal(A,B,C);
    n2 = Normal(D,E,F);
    float d1, d2;
    Coord_3D O(0,0,0);

    O.operator -=(A);
    d1 = ProdutoEscalar3D(O,n1);
    O.x=0;O.y=0;O.z=0;
    O.operator -=(D);
    d2 = ProdutoEscalar3D(*D,n2);
//    cout << "D1 = " << d1 << ", D2 = " << d2 << endl;
    h1=Dst(*A,n2,d2);h2=Dst(*B,n2,d2);h3=Dst(*C,n2,d2);
    h4=Dst(*D,n1,d1);h5=Dst(*E,n1,d1);h6=Dst(*F,n1,d1);

//    cout << "h1(" << h1 << "), h2(" << h2 << "), h3(" << h3<< "), h4(" << h4<< "), h5(" << h5<< "), h6(" << h6 <<");" << endl;

    if((h1==0 && h2==0 && h3==0) || (h4==0 && h5==0 && h6==0) ){
//        cout << "Coplanares" << endl << endl;
        return InttTriangulos2D(A,B,C,D,E,F);
//        cout << itt << endl;


    }
//    if((h1>0 && h2>0 && h3>0) || (h1<0 && h2<0 && h3<0)){
////        cout << "Não há possibilidade" << endl;
//        return false;
//    }
//    Coord_3D L = ProdutoVetorial3D(n1, n2);
//    L.ImpCoord_3D();

    return false;
}


bool Complanares(Coord_3D *A,Coord_3D *B,Coord_3D *C,Coord_3D *D,Coord_3D *E,Coord_3D *F){

    float h1,h2,h3,h4,h5,h6;
    Coord_3D n1, n2;
    n1 = Normal(A,B,C);
    n2 = Normal(D,E,F);
    float d1, d2;
    Coord_3D O(0,0,0);

    O.operator -=(A);
    d1 = ProdutoEscalar3D(O,n1);
    O.x=0;O.y=0;O.z=0;
    O.operator -=(D);
    d2 = ProdutoEscalar3D(*D,n2);
    h1=Dst(*A,n2,d2);h2=Dst(*B,n2,d2);h3=Dst(*C,n2,d2);
    h4=Dst(*D,n1,d1);h5=Dst(*E,n1,d1);h6=Dst(*F,n1,d1);

    if((h1==0 && h2==0 && h3==0) || (h4==0 && h5==0 && h6==0) ){
        return true;
    }
    return false;
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








