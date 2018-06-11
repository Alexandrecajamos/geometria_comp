#include "triangulacao.h"

int PValidos(Face F, Objeto *Obj, int *Candidatos){

    int nC = 0;
    int iA = F.P1, iB=F.P2, iC=F.P3;

    Coord_3D* a = Obj->points.at(iA);
    Coord_3D* b = Obj->points.at(iB);
    Coord_3D* c = Obj->points.at(iC);

    Coord_3D nF = Normal(a,b,c);

    int nV = Obj->points.size();

    for(int i=0; i < nV;i++){
        if(i != iA && i != iB && i != iC){
            Coord_3D temp = *(Obj->points.at(i));
            temp.operator -=(a);
            float pE = ProdutoEscalar3D(temp, nF);
            if(pE>0){
                Candidatos[nC] = i;
                nC++;
            }
        }
     }

    return nC;
}
int attLivres(vector<Face> Faces, int* Livres){
    int nL = 0;
    int nF = Faces.size();
    for(int i=0; i<nF;i++)
        if(Faces.at(i).Val){
            Livres[nL]=i;
            nL++;
        }
    return nL;
}
int Existe(Face F, vector<Face> Faces){

    int nF = Faces.size();
    int Ext = -1;
    int i=0;
    bool p1=0,p2=0,p3=0;

    while(i<nF && Ext == -1){
        p1=0;p2=0;p3=0;

        if(F.P1 == Faces.at(i).P1 || F.P1 == Faces.at(i).P2 || F.P1 == Faces.at(i).P3)
            p1 = 1;
        if(F.P2 == Faces.at(i).P1 || F.P2 == Faces.at(i).P2 || F.P2 == Faces.at(i).P3)
            p2 = 1;
        if(F.P3 == Faces.at(i).P1 || F.P3 == Faces.at(i).P2 || F.P3 == Faces.at(i).P3)
            p3 = 1;

        if(p1 && p2 && p3){
            Ext=i;
        }
        i++;
    }

    return Ext;
}

void Triangulacao(Objeto *Conv_Obj){
//    vector<Face *> Fecho, vector<Coord_3D *> Pontos;
    vector <Face> Faces;

    int NF = Conv_Obj->faces.size();
    int NP = Conv_Obj->points.size();

    int *Livres = new int[NF];
    int *validos = new int[NP];


    for(int i=0;i<NF;i++){
        Face T(Conv_Obj->faces.at(i)->P2,Conv_Obj->faces.at(i)->P1,Conv_Obj->faces.at(i)->P3);
        Faces.push_back(T);
    }

   for(int i=0; i<NF;i++){
//        cout << "F" << i << " -> " << Faces.at(i).P1 << Faces.at(i).P2 << Faces.at(i).P3 <<";"<< endl;
        Livres[i] = i;
//        cout << Livres[i] << endl;
    }

   int nC = 0;
   int nL = NF;
   int controle = 0;
   cout << nL << endl;

   while(nL>0 && controle < 1){
       Face F = Faces.at(Livres[0]);
//       cout << "F = " << Faces.at(Livres[0]).Val << endl;
       Faces.at(Livres[0]).Val = false;
       cout << "F -> " << F.P1 << F.P2 << F.P3 <<";"<< endl;
       nC = PValidos(F,Conv_Obj,validos);

//        cout << nC << ": "<< endl;
//        for(int i=0; i<nC;i++)
//            cout << validos[i] << endl;

       float **R_Ang = RankAngSol(Conv_Obj->points.at(F.P1),Conv_Obj->points.at(F.P2),Conv_Obj->points.at(F.P3), Conv_Obj->points,validos, nC, true);

       int Otm = R_Ang[nC-1][1];
       cout << "Ponto ótimo: " << Otm << endl;

       Face T1(F.P1, F.P2, Otm), T2(F.P2, F.P3, Otm), T3(F.P3, F.P1, Otm);
       int t1 = Existe(T1, Faces);
       int t2 = Existe(T2, Faces);
       int t3 = Existe(T3, Faces);
       cout << t1 << t2 << t3 << endl;

       if(t1 != -1)
           Faces.at(t1).Val = false;
       else
           Faces.push_back(T1);

       if(t2 != -1)
           Faces.at(t2).Val = false;
       else
           Faces.push_back(T2);
       if(t3 != -1)
           Faces.at(t3).Val = false;
       else
           Faces.push_back(T3);

        //        for(int i = 0;i<nC;i++){
//            cout << RAng[i][0] << ", " << RAng[i][1] << endl;
//        }

       free(Livres);
       nL = Faces.size();
//       cout << nL << endl;
       Livres = new int[nL];
       nL = attLivres(Faces, Livres);
//       cout << "Livres :" << nL << endl;
       controle++;

    }

   int NT = Faces.size();
   cout << NT << endl;
   for(int i=NF; i<NT;i++){
        Face T = Faces.at(i);
        Conv_Obj->addFace(T.P1, T.P2, T.P3);
//        cout << "F -> " << T.P1 << T.P2 << T.P3 <<";"<< endl;
    }
    cout << Existe(X, Faces);
}
