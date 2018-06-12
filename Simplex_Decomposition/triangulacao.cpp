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
int Valido(Face F, vector<Face> Faces,Objeto *Obj, bool &intersept){

    int nF = Faces.size();
    int Ext = -1;
    int i=0;
    bool p1=0,p2=0,p3=0;

    while(i<nF && Ext == -1 && !intersept){
        p1=0;p2=0;p3=0;

        if(F.P1 == Faces.at(i).P1 || F.P1 == Faces.at(i).P2 || F.P1 == Faces.at(i).P3)
            p1 = 1;
        if(F.P2 == Faces.at(i).P1 || F.P2 == Faces.at(i).P2 || F.P2 == Faces.at(i).P3)
            p2 = 1;
        if(F.P3 == Faces.at(i).P1 || F.P3 == Faces.at(i).P2 || F.P3 == Faces.at(i).P3)
            p3 = 1;

        if(p1 && p2 && p3){
//            cout << "Face Existente F(" << F.P1 << ", " << F.P2 << ", " << F.P3 << ")"  << endl;
            Ext=i;
        }else{
            cout << "Nao existe! F(" << F.P1 << ", " << F.P2 << ", " << F.P3 << ") X ("<< Faces.at(i).P1 << ", " << Faces.at(i).P2 << ", " << Faces.at(i).P3 << ");" << endl;
            if(IntersecaoTriangulos(Obj->points.at(F.P1),Obj->points.at(F.P2),Obj->points.at(F.P3), Obj->points. at(Faces.at(i).P1), Obj->points.at(Faces.at(i).P2), Obj->points.at(Faces.at(i).P3)))
                intersept = true;
            cout << intersept << endl;
        }
        i++;
    }

    return Ext;
}
int p_OtimoValido(Face F, vector<Face> *Faces, Objeto* Obj){

    int NP = Obj->points.size();
    int *validos = new int[NP];
    int nC = PValidos(F,Obj,validos);

    float **R_Ang = RankAngSol(Obj->points.at(F.P1),Obj->points.at(F.P2),Obj->points.at(F.P3), Obj->points,validos, nC, true);

    int Otm = -1;
    int Ind = nC-1;

    while(Otm == -1 && Ind >= 0){

        int Temp = R_Ang[Ind][1];

        bool i1=0, i2=0, i3=0;
        Face T1(F.P1, F.P2, Temp), T2(F.P2, F.P3, Temp), T3(F.P3, F.P1, Temp);

        int t1 = Valido(T1, *Faces, Obj, i1);
        int t2 = Valido(T2, *Faces, Obj, i2);
        int t3 = Valido(T3, *Faces, Obj, i3);

        if(!i1 && !i2 && !i3){
            Otm = Temp;

            if(t1 != -1)
                Faces->at(t1).Val = false;
            else
                Faces->push_back(T1);
            if(t2 != -1)
                Faces->at(t2).Val = false;
            else
                Faces->push_back(T2);
            if(t3 != -1)
                Faces->at(t3).Val = false;
            else
                Faces->push_back(T3);
        }else{
            Ind--;
        }

    }
    return Otm;

}


void ImpFaces(vector<Face> Faces){
    int nF = Faces.size();
    for(int i=0; i<nF;i++){
        cout << "Face F"<< i << "(" << Faces.at(i).P1 << ", " << Faces.at(i).P2 << ", " << Faces.at(i).P3 <<") V -> " << Faces.at(i).Val << endl;
    }

}


void Triangulacao(Objeto *Conv_Obj){
    vector <Face> Faces;
    int NF = Conv_Obj->faces.size();

    int *Livres = new int[NF];

    for(int i=0;i<NF;i++){
        Face T(Conv_Obj->faces.at(i)->P2,Conv_Obj->faces.at(i)->P1,Conv_Obj->faces.at(i)->P3);
        Faces.push_back(T);
    }
    for(int i=0; i<NF;i++){
//        cout << "F" << i << " -> " << Faces.at(i).P1 << Faces.at(i).P2 << Faces.at(i).P3 <<";"<< endl;
        Livres[i] = i;
//        cout << Livres[i] << endl;
    }


   int nL = NF;
   int controle = 0;
//   cout << nL << endl;

    while(nL>0 && controle < 25){


        Face F = Faces.at(Livres[0]);

        Faces.at(Livres[0]).Val = false;
        cout << "F -> " << F.P1 << F.P2 << F.P3 <<";"<< endl;


        int Otm = p_OtimoValido(F,&Faces, Conv_Obj);
        cout << Otm << endl;
        if(Otm != -1)
            Conv_Obj->addSimplex(F.P1, F.P2, F.P3, Otm);
        ImpFaces(Faces);

       free(Livres);
       nL = Faces.size();
//       cout << nL << endl;
       Livres = new int[nL];
       nL = attLivres(Faces, Livres);
////       cout << "Livres :" << nL << endl;
       controle++;

    }

//   int NT = Faces.size();
//   cout << NT << endl;
//   for(int i=NF; i<NT;i++){
//        Face T = Faces.at(i);
//        Conv_Obj->addFace(T.P1, T.P2, T.P3);
////        cout << "F -> " << T.P1 << T.P2 << T.P3 <<";"<< endl;
//    }
//    cout << Existe(X, Faces);
}
