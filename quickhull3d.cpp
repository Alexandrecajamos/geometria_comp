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
bool Coplanares(int A, int B, int P, Objeto* Pol){

    Coord_3D AB = *(Pol->points.at(B));
    Coord_3D AP = *(Pol->points.at(P));
    AB.operator -=(Pol->points.at(A));
    AP.operator -=(Pol->points.at(A));
    NormalizaVetor3D(&AB);
    NormalizaVetor3D(&AP);
    int PE = ProdutoEscalar3D(AB,AP);
    //cout << endl << A << B << P << PE;

    if(PE == 1)
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



void QuickHull(Objeto* Pol){

    int N = Pol->points.size();
    bool *Validos = (bool*)malloc(sizeof(bool)*N);

    for(int i=0;i<N;i++){
        Validos[i] = 1;
    }

    Face Ext = Extremos(Pol);

    int a = Ext.P1;
    int b = Ext.P2;
    int c = Ext.P3;



    cout << "Extremos : " << a << b << c << endl;


    bool* valC1 = CopiaValidos(Validos,N);
    bool* valC2 = CopiaValidos(Validos,N);


    Particiona(Pol, a,b,c, valC1);

    cout << endl;
    Particiona(Pol, a,c,b, valC2);


    for(int i=0;i<N;i++)
        cout << valC1[i];

    cout << endl;
    for(int i=0;i<N;i++)
        cout << valC2[i];

    QuickHull_Recursivo(Pol, a,b,c, valC1);
    QuickHull_Recursivo(Pol,a,c,b, valC2);



    for(int i=0;i<N;i++)
        if(!valC1[i] && !valC2[i])
            Validos[i] = false;

    Validos[a]=1;
    Validos[b]=1;
    Validos[c]=1;


    cout <<endl;cout <<endl;
    cout << "Indices de Pontos do Fecho: " << endl;
    for(int i=0;i<N;i++)
        cout << Validos[i];
    cout << endl;

    cout << "Número de Faces: " << Pol->faces.size()<<endl;

}
void QuickHull_Recursivo(Objeto *Pol, int iA, int iB, int iC, bool *validos){

    int N = Pol->points.size();
    int Pontos_Validos = ContaValidos(validos,N);

    if(Pontos_Validos == 0){
        Coord_3D nF = Normal(Pol->points.at(iA), Pol->points.at(iB), Pol->points.at(iC));
        if(nF.z > 0)
            Pol->addFace(iA, iB,iC);
        else
            Pol->addFace(iA, iC,iB);
        return;
    }

    int max;

    if(Pontos_Validos == 1){

        int iP;
        for(int i=0;i<N;i++)
            if(validos[i])
                iP = i;
        max = iP;

    }else
        max = Pmax(Pol, iA,iB,iC, validos);
    cout<< endl << "Max : "<< max;

    bool* valC1 = CopiaValidos(validos,N);
    bool* valC2 = CopiaValidos(validos,N);
    bool* valC3 = CopiaValidos(validos,N);


    Particiona(Pol, iA,iB,max, valC1);
    Particiona(Pol, iB,iC,max, valC2);
    Particiona(Pol, iC,iA,max, valC3);

    cout <<endl;
    for(int i=0; i<N;i++)
        cout << " " << valC1[i];
    cout <<endl;
    cout <<endl;
    for(int i=0; i<N;i++)
        cout << " " << valC2[i];
    cout <<endl;
    cout <<endl;
    for(int i=0; i<N;i++)
        cout << " " << valC3[i];
    cout <<endl;

    QuickHull_Recursivo(Pol, iA,iB,max, valC1);
    QuickHull_Recursivo(Pol, iB,iC,max, valC2);
    QuickHull_Recursivo(Pol, iC,iA,max, valC3);


    for(int i=0;i<N;i++)
        if(!valC1[i] && !valC2[i] && !valC3[i])
            validos[i] = false;


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


    int N = Pol->points.size();


    for(int i=0; i < N;i++){
        if(validos[i] && i != iA && i!= iB && i!= iC){
            Coord_3D temp = *(Pol->points.at(i));
            temp.operator -=(a);

            float pE = ProdutoEscalar3D(temp, nF);
            if(pE<=0)
                validos[i] = false;
        }
    }


    validos[iA]=false;
    validos[iB]=false;
    validos[iC]=false;


}

