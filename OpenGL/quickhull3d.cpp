#include "quickhull3d.h"

void Barycentric(Coord_3D p, Coord_3D a, Coord_3D b, Coord_3D c, float &u, float &v, float &w)
{
    Coord_3D v0 = b; Coord_3D v1 = c; Coord_3D v2 = p;
    v0.operator -=(&a); v1.operator -=(&a); v2.operator -=(&a);

    float d00 = ProdutoEscalar3D(v0,v0);
    float d01 = ProdutoEscalar3D(v0,v1);
    float d11 = ProdutoEscalar3D(v1,v1);
    float d20 = ProdutoEscalar3D(v2,v0);
    float d21 = ProdutoEscalar3D(v2,v1);

    float denom = (d00 * d11) - (d01 * d01);

    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1-v-w;

}
int MaiorY(int MX, Objeto* O){
    float MY = O->points.at(0)->y;
    int ind = 0;
    int N = O->points.size();
    for(int i=1; i < N;i++){
        float y = O->points.at(i)->y;
        if(y>MY && i != MX){
            MY = y;
            ind=i;
        }
    }
    return ind;
}

Objeto* QuickHull(Objeto* Obj){

    int a = Obj->MenorX();
    int b = Obj->MaiorX();
    int c = MaiorY(a,Obj);

    int N = Obj->points.size();
    int *Validos = (int*)malloc(sizeof(int)*N);
    int *p1 = (int*)malloc(sizeof(int)*N);
    int *p2 = (int*)malloc(sizeof(int)*N);

     for(int i=0;i<N;i++)
            Validos[i] = i;
    //Na primeira etapa, todos os pontos são "Validos"
    int N1 = Particiona(Obj,Validos, N, p1, a,b,c);
    int N2 = Particiona(Obj,Validos, N, p2, a,c,b);

    QuickHull_Recursivo(Obj,p1, N1, a,b,c);
    QuickHull_Recursivo(Obj,p2, N2, a,c,b);
//    Exclui_Internas(Obj);
    return Obj;

}
void QuickHull_Recursivo(Objeto *Obj, int *Validos, int nP, int a, int b, int c){

    int max = Pmax(Obj,Validos, nP, Obj->points.at(a),Obj->points.at(b),Obj->points.at(c));
    if(max == -1){
            Obj->addFace(a,b,c);
        return;
    }

    int *p1 = (int*)malloc(sizeof(int)*nP);
    int *p2 = (int*)malloc(sizeof(int)*nP);
    int *p3 = (int*)malloc(sizeof(int)*nP);

    int N1 = Particiona(Obj,Validos, nP,p1, a,b,max);
    int N2 = Particiona(Obj,Validos, nP,p2, b,c,max);
    int N3 = Particiona(Obj,Validos, nP,p3, c,a,max);

    QuickHull_Recursivo(Obj, p1, N1, a,b,max);
    QuickHull_Recursivo(Obj, p2, N2, b,c,max);
    QuickHull_Recursivo(Obj, p3, N3, c,a,max);

}
int Particiona(Objeto* Obj,int* Validos,int nV, int* Parte, int iA, int iB, int iC){

    int nP = 0;
    Coord_3D* a = Obj->points.at(iA);
    Coord_3D* b = Obj->points.at(iB);
    Coord_3D* c = Obj->points.at(iC);

    Coord_3D nF = Normal(a,b,c);

    for(int i=0; i < nV;i++){
        if(Validos[i]!= iA && Validos[i] != iB && Validos[i] != iC){
            Coord_3D temp = *(Obj->points.at(Validos[i]));
            temp.operator -=(a);

            float pE = ProdutoEscalar3D(temp, nF);
            if(pE>0){
                Parte[nP] = Validos[i];
                nP++;
            }
            if(pE == 0){
               float u=0, v=0, w=0;
               Barycentric(*(Obj->points.at(Validos[i])), *a,*b,*c, u, v, w);
               if(u<0 || u>1 || v<0 || v>1 || w<0 || w>1){
                   Parte[nP] = Validos[i];
                   nP++;
               }
           }
        }
     }

    return nP;
}
int Pmax(Objeto *Obj, int *Parte, int nP, Coord_3D *a, Coord_3D *b, Coord_3D *c){

    float MairVolume = 0;
    Coord_3D nF = Normal(a,b,c);

    int Ind = -1;

    for(int i=0; i < nP;i++){
        Coord_3D temp = *(Obj->points.at(Parte[i]));
        temp.operator -=(a);
        float pE = ProdutoEscalar3D(temp, nF);
        if(pE>MairVolume){
            MairVolume = pE;
            Ind = Parte[i];
        }
    }
    return Ind;
}

//Para mapear pontos referenciados pelas faces resultantes do Fecho
int Pontos_Fecho(Objeto *Fecho, int *Pontos){


    int nF = Fecho->faces.size();
    int nP = Fecho->points.size();
    bool *pontos = (bool*)malloc(sizeof(bool)*nP);

    for(int i=0;i<nP;i++)
        pontos[i]=0;

    for(int i=0; i< nF; i++){
        Face *F = Fecho->faces.at(i);
        pontos[F->P1] = 1;
        pontos[F->P2] = 1;
        pontos[F->P3] = 1;

    }
    int nPontos=0;
    for(int i=0;i<nP;i++)
    {
        if(pontos[i]){
            Pontos[nPontos] = i;
            nPontos++;
        }
    }
    return nPontos;
}


bool Pertence(Objeto *Obj, int iA, int iB, int iC){
    int N = Obj->points.size();
    Coord_3D* a = Obj->points.at(iA);
    Coord_3D* b = Obj->points.at(iB);
    Coord_3D* c = Obj->points.at(iC);

    Coord_3D nF = Normal(a,b,c);

    bool Ret = true;
    for(int i=0; i < N; i++){
        if(i!=iA && i!=iB && i!=iC){
            Coord_3D temp = *(Obj->points.at(i));
            temp.operator -=(a);
            float pE = ProdutoEscalar3D(temp, nF);
            if(pE>0){
                Ret = false;
            }

        }
    }
    return Ret;
}



//Versão 2 :

void Exclui_Internas(Objeto *Obj){

    int nF= Obj->faces.size();
    vector<Face*> P;
    for(int i=0; i<nF; i++){
        int a = Obj->faces.at(i)->P1;
        int b = Obj->faces.at(i)->P2;
        int c = Obj->faces.at(i)->P3;
        if(Pertence(Obj,a,b,c))
            P.push_back(Obj->faces.at(i));
    }
    Obj->faces.clear();

    nF = P.size();
    for(int i=0; i<nF; i++)
        Obj->faces.push_back(P.at(i));


}
void QRec(Objeto *Obj, int *Validos, int nP, int a, int b, int c){

    int max = Pmax(Obj,Validos, nP, Obj->points.at(a),Obj->points.at(b),Obj->points.at(c));
    if(max == -1){
        if(Pertence(Obj,a,b,c))
            Obj->addFace(a,b,c);
        return;
    }

    int *p1 = (int*)malloc(sizeof(int)*nP);
    int *p2 = (int*)malloc(sizeof(int)*nP);
    int *p3 = (int*)malloc(sizeof(int)*nP);

    int N1 = Particiona(Obj,Validos, nP,p1, a,b,max);
    int N2 = Particiona(Obj,Validos, nP,p2, b,c,max);
    int N3 = Particiona(Obj,Validos, nP,p3, c,a,max);

    QRec(Obj, p1, N1, a,b,max);
    if(Obj->faces.size()==0)
        QRec(Obj, p2, N2, b,c,max);
    if(Obj->faces.size()==0)
        QRec(Obj, p3, N3, c,a,max);
}
Objeto* QuickHull2(Objeto* Obj){


    int a = Obj->MenorX();
    int b = Obj->MaiorX();
    int c = MaiorY(a,Obj);

    int N = Obj->points.size();
    int *Validos = (int*)malloc(sizeof(int)*N);
    for(int i=0;i<N;i++)
            Validos[i] = i;

    int *Parte = (int*)malloc(sizeof(int)*N);
    int nP = Particiona(Obj,Validos,N, Parte,a,b,c);

    QRec(Obj,Parte,nP,a,b,c);
    Face *F = Obj->faces.at(0);

    QuickHull_Recursivo(Obj,Validos, N, F->P1,F->P3,F->P2);

    return Obj;


}


