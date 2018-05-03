#include "quickhull3d.h"



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
int MaiorZ(int MX, int MY, Objeto* O){
    float MZ = O->points.at(0)->z;
    int ind = 0;
    int N = O->points.size();
    for(int i=1; i < N;i++){
        float z = O->points.at(i)->z;
        if(z>MZ && i != MX && i != MY){
            MZ = z;
            ind=i;
        }
    }
    return ind;
}
Face Extremos(Objeto* Pol){

    int MX = Pol->MaiorX();
    int MY = MaiorY(MX, Pol);
    int MZ = MaiorZ(MX,MY,Pol);

    Face F(MX,MY,MZ);

    return F;

}



bool Pertence(Objeto *Obj, int iA, int iB, int iC){
    int N = Obj->points.size();
    Coord_3D* a = Obj->points.at(iA);
    Coord_3D* b = Obj->points.at(iB);
    Coord_3D* c = Obj->points.at(iC);

    Coord_3D nF = Normal(a,b,c);

    bool Ret = true;
    for(int i=0; i < N; i++){
        Coord_3D temp = *(Obj->points.at(i));
        temp.operator -=(a);
        float pE = ProdutoEscalar3D(temp, nF);
        if(pE>0)
            Ret = false;
//        cout << "T("<<i<<") = " << pE << endl;

    }

    return Ret;
}

Objeto* QuickHull(Objeto* Obj){

    Face Ext = Extremos(Obj);

    int a = Ext.P1;
    int b = Ext.P2;
    int c = Ext.P3;

    int N = Obj->points.size();
    int *Validos = (int*)malloc(sizeof(int)*N);
    int *p1 = (int*)malloc(sizeof(int)*N);
    int *p2 = (int*)malloc(sizeof(int)*N);

    //int nV = 0;

    for(int i=0;i<N;i++)
//        if(i!= a && i != b && i!= c){
            Validos[i] = i;
  //          nV++;
    //    }


    int N1 = Particiona(Obj,Validos, N, p1, a,b,c);
    int N2 = Particiona(Obj,Validos, N, p2, a,c,b);

//    for(int i=0; i<N1; i++)
//        cout << p1[i] << endl;

//    cout << "t" << endl;

//    for(int i=0; i<N2; i++)
//        cout << p2[i] << endl;

//    int max = Pmax(Obj, p2, N2, Obj->points.at(a),Obj->points.at(c),Obj->points.at(b));
//    cout << "Max" <<  max << endl;


    QuickHull_Recursivo(Obj,p1, N1, a,b,c);
    QuickHull_Recursivo(Obj,p2, N2, a,c,b);

//    cout << Obj->faces.size() << endl;
//    Obj->ImpFaces();
    return Obj;


}

void Teste(Objeto *Obj, int *Parte, int nP, int a, int b, int c){
    int max = Pmax(Obj,Parte, nP, Obj->points.at(a),Obj->points.at(b),Obj->points.at(c));

    int *p1 = (int*)malloc(sizeof(int)*nP);
    int *p2 = (int*)malloc(sizeof(int)*nP);
    int *p3 = (int*)malloc(sizeof(int)*nP);


    cout << endl << endl << "Teste: ("<<a<<b<<c<<") com nº de pontos = " << nP << endl;
    for(int i=0; i<nP; i++)
        cout << Parte[i];
    cout <<endl<< "Fim Validos "<< endl << "pMax = " << max << endl;

    int N1 = Particiona(Obj,Parte, nP,p1, a,b,max);
    int N2 = Particiona(Obj,Parte, nP,p2, b,c,max);
    int N3 = Particiona(Obj,Parte, nP,p3, c,a,max);

    int m1, m2, m3;
    m1 = Pmax(Obj,p1, N1, Obj->points.at(a),Obj->points.at(b),Obj->points.at(max));
    m2 = Pmax(Obj,p2, N2, Obj->points.at(b),Obj->points.at(c),Obj->points.at(max));
    m3 = Pmax(Obj,p3, N3, Obj->points.at(c),Obj->points.at(a),Obj->points.at(max));

    cout << "Teste Particiona (" << a << b << max << "): " << endl;

    for(int i=0; i<N1; i++)
        cout << p1[i] << endl;

    cout << "pMax = " << m1 << endl;

    cout << "Teste Particiona (" << b << c << max << "): " << endl;

    for(int i=0; i<N2; i++)
        cout << p2[i] << endl;

    cout << "pMax = " << m2 << endl;

    cout << "Teste Particiona (" << c << a << max << "): " << endl;

    for(int i=0; i<N3; i++)
        cout << p3[i] << endl;

    cout << "pMax = " << m3 << endl;

}

void QuickHull_Recursivo(Objeto *Obj, int *Parte, int nP, int a, int b, int c){

    int max = Pmax(Obj,Parte, nP, Obj->points.at(a),Obj->points.at(b),Obj->points.at(c));

    if(max == -1){
        //if(Pertence(Obj,a,b,c) || Pertence(Obj, a,c,b))
            Obj->addFace(a,b,c);
        return;
    }

//    cout << "COnjunto : "<< endl;
//    for(int i = 0; i<nP; i++)
//        cout << Parte[i] << endl;

    int *p1 = (int*)malloc(sizeof(int)*nP);
    int *p2 = (int*)malloc(sizeof(int)*nP);
    int *p3 = (int*)malloc(sizeof(int)*nP);


//    cout << endl << endl << "Teste: " << nP << endl;
    int N1 = Particiona(Obj,Parte, nP,p1, a,b,max);
    int N2 = Particiona(Obj,Parte, nP,p2, b,c,max);
    int N3 = Particiona(Obj,Parte, nP,p3, c,a,max);

//    int m1, m2, m3;
//    m1 = Pmax2(Obj,p1, N1, Obj->points.at(a),Obj->points.at(b),Obj->points.at(max));
//    m2 = Pmax2(Obj,p2, N2, Obj->points.at(b),Obj->points.at(c),Obj->points.at(max));
//    m3 = Pmax2(Obj,p3, N3, Obj->points.at(c),Obj->points.at(a),Obj->points.at(max));

//    cout << "Teste Particiona (" << a << b << max << "): " << endl;

//    for(int i=0; i<N1; i++)
//        cout << p1[i] << endl;

//    cout << "pMax = " << m1 << endl;

//    cout << "Teste Particiona (" << b << c << max << "): " << endl;

//    for(int i=0; i<N2; i++)
//        cout << p2[i] << endl;

//    cout << "pMax = " << m2 << endl;

//    cout << "Teste Particiona (" << c << a << max << "): " << endl;

//    for(int i=0; i<N3; i++)
//        cout << p3[i] << endl;

//    cout << "pMax = " << m3 << endl;


    //cout << N1 << N2<< N3 << endl;
    //      T(Obj, p2, N2, b,c,max);
    //      T(Obj, p3, N3, c,a,max);

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
//        cout << endl << "abc - " <<  iA << iB << iC << endl;
     for(int i=0; i < nV;i++){
         if(Validos[i]!= iA && Validos[i] != iB && Validos[i] != iC){
//            cout << Validos[i] << endl;
            Coord_3D temp = *(Obj->points.at(Validos[i]));
            temp.operator -=(a);
            float pE = ProdutoEscalar3D(temp, nF);
//            cout << Validos[i] << " = " << pE << endl;

            if(pE>=0){
                Parte[nP] = Validos[i];
                nP++;
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
