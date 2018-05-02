#include "quickhull3d.h"



int ContaValidos(bool* validos, int N){
    int Val=0;
    for(int i=0;i<N;i++){
        if(validos[i])
            Val++;
    }
    return Val;
}
bool* CopiaValidos(bool* validos, int N){

    bool *Ret = (bool*)malloc(sizeof(bool)*N);
    for(int i=0;i<N;i++)
        Ret[i] = validos[i];
    return Ret;
}
bool Coplanares(Coord_3D nFace, int P1, int P, Objeto* Pol){

    Coord_3D AP = *(Pol->points.at(P));

    AP.operator -=(Pol->points.at(P1));

    NormalizaVetor3D(&AP);

    int PE = ProdutoEscalar3D(nFace,AP);
    //cout << endl << A << B << P << PE;

    if(PE == 0)
        return true;
    return false;
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



Objeto* QuickHull(Objeto* Entrada){

    Objeto* Pol = new Objeto();

    Pol->CopiaPontos(Entrada);


    int N = Pol->points.size();
    bool *Validos = (bool*)malloc(sizeof(bool)*N);

    for(int i=0;i<N;i++){
        Validos[i] = 1;
    }

    Face Ext = Extremos(Pol);

    int a = Ext.P1;
    int b = Ext.P2;
    int c = Ext.P3;

    bool* valC1 = CopiaValidos(Validos,N);
    bool* valC2 = CopiaValidos(Validos,N);


    Particiona(Pol, a,b,c, valC1);
    Particiona(Pol, a,c,b, valC2);


    QuickHull_Recursivo(Pol, a,b,c, valC1);
    QuickHull_Recursivo(Pol,a,c,b, valC2);
    cout << Pol->faces.size();
    //Pol->ImpFaces();
    return Pol;

}

void QuickHull_Recursivo(Objeto *Pol, int iA, int iB, int iC, bool *validos){

    int N = Pol->points.size();
    int max = Pmax(Pol,iA,iB,iC,validos);

    if(max == -1){
//        if(Pol->Pertence(iA,iB,iC))
//            return;
        Pol->addFace(iA, iB,iC);
        return;
    }
    if(validos[max] != 1)
        return;

    bool* valC1 = CopiaValidos(validos,N);
    bool* valC2 = CopiaValidos(validos,N);
    bool* valC3 = CopiaValidos(validos,N);


    Particiona(Pol, iA,iB,max, valC1);
    Particiona(Pol, iB,iC,max, valC2);
    Particiona(Pol, iC,iA,max, valC3);

    QuickHull_Recursivo(Pol, iA,iB,max, valC1);
    QuickHull_Recursivo(Pol, iB,iC,max, valC2);
    QuickHull_Recursivo(Pol, iC,iA,max, valC3);


}

int Pmax(Objeto* Pol, int iA, int iB, int iC, bool *validos){

    Coord_3D* a = Pol->points.at(iA);
    Coord_3D* b = Pol->points.at(iB);
    Coord_3D* c = Pol->points.at(iC);

    float MairVolume = 0;

    Coord_3D nF = Normal(a,b,c);


    int Ind = -1;
    int N = Pol->points.size();

    for(int i=0; i < N;i++){

        if(validos[i]){
            Coord_3D temp = *(Pol->points.at(i));
            temp.operator -=(a);
            float pE = ProdutoEscalar3D(temp, nF);

            if(pE>MairVolume){
                MairVolume = pE;
                Ind = i;
            }
        }


    }
    return Ind;

}
void Particiona(Objeto* Pol, int iA, int iB, int iC, bool *validos){
    Coord_3D* a = Pol->points.at(iA);
    Coord_3D* b = Pol->points.at(iB);
    Coord_3D* c = Pol->points.at(iC);

    Coord_3D nF = Normal(a,b,c);
   // nF.ImpCoord_3D();
    int N = Pol->points.size();


    for(int i=0; i < N;i++){
        if(validos[i] && i != iA && i!= iB && i!= iC){
            Coord_3D temp = *(Pol->points.at(i));
            temp.operator -=(a);
            float pE = ProdutoEscalar3D(temp, nF);
            if(pE<0)
                validos[i] = false;
        }
    }
}




Objeto* QuickHull2(Objeto* Obj){

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


    int N1 = Particiona2(Obj,Validos, N, p1, a,b,c);
    int N2 = Particiona2(Obj,Validos, N, p2, a,c,b);

//    for(int i=0; i<N1; i++)
//        cout << p1[i] << endl;
//    cout << "t" << endl;

//    for(int i=0; i<N2; i++)
//        cout << p2[i] << endl;

//    int max = Pmax2(Obj, p2, N2, Obj->points.at(a),Obj->points.at(c),Obj->points.at(b));
//    cout << max << endl;


    QuickHull_Recursivo2(Obj,p1, N1, a,b,c);
    QuickHull_Recursivo2(Obj,p2, N2, a,c,b);

//    cout << Obj->faces.size() << endl;
//    Obj->ImpFaces();
    return Obj;


}

void QuickHull_Recursivo2(Objeto *Obj, int *Parte, int nP, int a, int b, int c){

    int max = Pmax2(Obj,Parte, nP, Obj->points.at(a),Obj->points.at(b),Obj->points.at(c));

    if(max == -1){
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
    int N1 = Particiona2(Obj,Parte, nP,p1, a,b,max);
    int N2 = Particiona2(Obj,Parte, nP,p2, b,c,max);
    int N3 = Particiona2(Obj,Parte, nP,p3, c,a,max);

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


//    cout << N1 << N2<< N3 << endl;

    QuickHull_Recursivo2(Obj, p1, N1, a,b,max);
    QuickHull_Recursivo2(Obj, p2, N2, b,c,max);
    QuickHull_Recursivo2(Obj, p3, N3, c,a,max);


}

int Particiona2(Objeto* Obj,int* Validos,int nV, int* Parte, int iA, int iB, int iC){

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

int Pmax2(Objeto *Obj, int *Parte, int nP, Coord_3D *a, Coord_3D *b, Coord_3D *c){

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
