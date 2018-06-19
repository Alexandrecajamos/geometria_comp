#include "triangulacao.h"
#include "intersecet3d.h"

Coord_3D P_Otimo(Coord_3D *A, Coord_3D *B, Coord_3D *C){
    Coord_3D nF = Normal(A,B,C);
    float aF = NormaVetor3D(nF);

    NormalizaVetor3D(&nF);
    nF.operator *=(sqrt(aF));

    float sX, sY, sZ;

    sX = (A->x + B->x + C->x)/3;
    sY = (A->y + B->y + C->y)/3;
    sZ = (A->z + B->z + C->z)/3;

    Coord_3D c(sX, sY, sZ);
    c.operator +=(&nF);

    return c;
}

float** RankDistPontos(Face F, std::vector<Coord_3D*> *Pontos, bool Ord, int &nV){

    int nP = Pontos->size();
    int iA = F.P1, iB=F.P2, iC=F.P3;

    Coord_3D* a = Pontos->at(iA);
    Coord_3D* b = Pontos->at(iB);
    Coord_3D* c = Pontos->at(iC);

    Coord_3D nF = Normal(a,b,c);
    NormalizaVetor3D(&nF);
    Coord_3D Otm = P_Otimo(a,b,c);

    Coord_3D T = Otm;
    T.operator -=(a);
    float Tol = ProdutoEscalar3D(T,nF);
//    Tol = 5;
//    cout << "Tol " << Tol << endl;

    float ** Rank = (float**)malloc(sizeof(float*)*nP);

    for(int i=0;i<nP;i++){
        if(i!=iA && i!=iB && i != iC){

            Coord_3D temp = *Pontos->at(i);
            temp.operator -=(a);
            float pE = ProdutoEscalar3D(temp, nF);

            if(pE > 0){
                float d = Distancia3D(Otm, *Pontos->at(i));

                if(d<Tol){

                    Rank[nV]=(float*)malloc(sizeof(float)*2);
                    Rank[nV][0] = ANGSolido(a,b,c, Pontos->at(i));
                    Rank[nV][1]=i;
                    nV++;
                }
            }
        }
    }
    if(Ord)
        QuickSortM(Rank,0, nV-1,0,2);
    return Rank;
}





int PValidos(Face F, std::vector<Coord_3D*> *Pontos, int *Candidatos){

    int nC = 0;
    int iA = F.P1, iB=F.P2, iC=F.P3;
    Coord_3D* a = Pontos->at(iA);
    Coord_3D* b = Pontos->at(iB);
    Coord_3D* c = Pontos->at(iC);

    int nV = Pontos->size();

    Coord_3D nF = Normal(a,b,c);



    for(int i=0; i < nV;i++){
        if(i != iA && i != iB && i != iC){
            Coord_3D temp = *(Pontos->at(i));


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
int Valido(Face F, vector<Face> *Faces,std::vector<Coord_3D*> *Pontos, bool &intersept){

    int nF = Faces->size();
    int Ext = -1;
    int i=0;
    bool p1=0,p2=0,p3=0;

    while(i<nF && Ext == -1 && !intersept){
        p1=0;p2=0;p3=0;

        if(F.P1 == Faces->at(i).P1 || F.P1 == Faces->at(i).P2 || F.P1 == Faces->at(i).P3)
            p1 = 1;
        if(F.P2 == Faces->at(i).P1 || F.P2 == Faces->at(i).P2 || F.P2 == Faces->at(i).P3)
            p2 = 1;
        if(F.P3 == Faces->at(i).P1 || F.P3 == Faces->at(i).P2 || F.P3 == Faces->at(i).P3)
            p3 = 1;

        if(p1 && p2 && p3){
//            cout << "Face Existente F(" << F.P1 << ", " << F.P2 << ", " << F.P3 << ")"  << endl;
            Ext=i;
        }else{

            intersept = IntersecaoTriangulos(Pontos->at(F.P1),Pontos->at(F.P2),Pontos->at(F.P3), Pontos->at(Faces->at(i).P1), Pontos->at(Faces->at(i).P2), Pontos->at(Faces->at(i).P3));

        }
        i++;
    }

    return Ext;
}
int Valido2(Face F, vector<Face> *Faces, int *Livres, int nLivres, vector<int> Rejeitadas, vector<Coord_3D*> *Pontos, bool &intersept){

    int Ext = -1;
    int i=0;
    bool p1=0,p2=0,p3=0;

    while(i<nLivres && Ext == -1 && !intersept){
        p1=0;p2=0;p3=0;

        if(F.P1 == Faces->at(Livres[i]).P1 || F.P1 == Faces->at(Livres[i]).P2 || F.P1 == Faces->at(Livres[i]).P3)
            p1 = 1;
        if(F.P2 == Faces->at(Livres[i]).P1 || F.P2 == Faces->at(Livres[i]).P2 || F.P2 == Faces->at(Livres[i]).P3)
            p2 = 1;
        if(F.P3 == Faces->at(Livres[i]).P1 || F.P3 == Faces->at(Livres[i]).P2 || F.P3 == Faces->at(Livres[i]).P3)
            p3 = 1;

        if(p1 && p2 && p3){
            Ext=i;
        }else{

            intersept = IntersecaoTriangulos(Pontos->at(F.P1),Pontos->at(F.P2),Pontos->at(F.P3), Pontos->at(Faces->at(Livres[i]).P1), Pontos->at(Faces->at(Livres[i]).P2), Pontos->at(Faces->at(Livres[i]).P3));

        }
        i++;
    }


    int nR = Rejeitadas.size();
    i=0;
    while(i<nR && Ext == -1 && !intersept){

        p1=0;p2=0;p3=0;

        if(F.P1 == Faces->at(Rejeitadas.at(i)).P1 || F.P1 == Faces->at(Rejeitadas.at(i)).P2 || F.P1 == Faces->at(Rejeitadas.at(i)).P3)
            p1 = 1;
        if(F.P2 == Faces->at(Rejeitadas.at(i)).P1 || F.P2 == Faces->at(Rejeitadas.at(i)).P2 || F.P2 == Faces->at(Rejeitadas.at(i)).P3)
            p2 = 1;
        if(F.P3 == Faces->at(Rejeitadas.at(i)).P1 || F.P3 == Faces->at(Rejeitadas.at(i)).P2 || F.P3 == Faces->at(Rejeitadas.at(i)).P3)
            p3 = 1;

        if(p1 && p2 && p3){
            Ext=i;
        }else{
            intersept = IntersecaoTriangulos(Pontos->at(F.P1),Pontos->at(F.P2),Pontos->at(F.P3), Pontos->at(Faces->at(Rejeitadas.at(i)).P1), Pontos->at(Faces->at(Rejeitadas.at(i)).P2), Pontos->at(Faces->at(Rejeitadas.at(i)).P3));
        }
       i++;
    }

    return Ext;
}

int p_OtimoValido(Face F, vector<Face> *Faces, std::vector<Coord_3D*> *Pontos, int *Livres, int nLivres, vector<int> Rejeitadas){

    int NP = Pontos->size();
    int *validos = new int[NP];
    int nC = PValidos(F,Pontos,validos);
    float **R_Ang = RankAngSol(Pontos->at(F.P1),Pontos->at(F.P2),Pontos->at(F.P3), *Pontos,validos, nC, true);

    int Otm = -1;
    int Ind = nC-1;

    while(Otm == -1 && Ind >= 0){

        int Temp = R_Ang[Ind][1];

        bool i1=0, i2=0, i3=0;
        Face T1(F.P1, F.P2, Temp), T2(F.P2, F.P3, Temp), T3(F.P3, F.P1, Temp);

        int t1 = Valido2(T1, Faces,Livres, nLivres, Rejeitadas, Pontos, i1);
        int t2 = Valido2(T2, Faces,Livres, nLivres, Rejeitadas, Pontos, i2);
        int t3 = Valido2(T3, Faces,Livres, nLivres, Rejeitadas, Pontos, i3);

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
        }
        else{
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


void Triangulacao2(Objeto *Conv_Obj, bool EBusca){
    cout << EBusca << endl;
    vector <Face> Faces;
    int NF = Conv_Obj->faces.size();

    int *Livres = new int[NF];

    for(int i=0;i<NF;i++){
        Face T(Conv_Obj->faces.at(i)->P2-1,Conv_Obj->faces.at(i)->P1-1,Conv_Obj->faces.at(i)->P3-1);
        Faces.push_back(T);
    }

    for(int i=0; i<NF;i++){
        Livres[i] = i;
    }


   int nL = NF;
   int controle = 0;

//   P_Otimo(Conv_Obj->points.at(0),Conv_Obj->points.at(5),Conv_Obj->points.at(6));

    while(nL>0 && controle < 5000){


//        Face F = Faces.at(Livres[0]);

//        Faces.at(Livres[0]).Val = false;

//        cout << "F -> " << F.P1 << F.P2 << F.P3 <<";"<< endl;


//        int Otm = p_OtimoValido(F,&Faces, &Conv_Obj->points, Libres, nL, Rejeitadas);
//        cout << Otm << endl;
//        if(Otm != -1){
//            Conv_Obj->addSimplex(F.P1, F.P2, F.P3, Otm);
//        }
//        else{
//            cout << "Não encontrado";
//        }
//        ImpFaces(Faces);
//        cout << "Teste" << endl;


       free(Livres);
       nL = Faces.size();
//       cout << nL << endl;
       Livres = new int[nL];
       nL = attLivres(Faces, Livres);
//       cout << "Livres :" << nL << endl;
//       ImpFaces(Faces);
       controle++;

    }

//       int NT = Faces.size();
//       cout << NT << endl;
//       for(int i=NF; i<NT;i++){
//            Face T = Faces.at(i);
//            Conv_Obj->addFace(T.P1, T.P2, T.P3);
//    //        cout << "F -> " << T.P1 << T.P2 << T.P3 <<";"<< endl;
//        }

}


int Melhor_Ponto(Face F, vector<Face> *Faces, std::vector<Coord_3D*> *Pontos,  int *Livres, int nLivres, vector<int> Rejeitadas, bool EBusca){
    int Otm = -1;

    if(EBusca){

        int nV =0;
        float **Rank = RankDistPontos(F, Pontos, 1, nV); // Return nV;
        int Ind = nV-1;


        while(Otm == -1 && Ind >= 0){

            int Temp = Rank[Ind][1];

            bool i1=0, i2=0, i3=0;

            Face T1(F.P1, F.P2, Temp), T2(F.P2, F.P3, Temp), T3(F.P3, F.P1, Temp);

            int t1 = Valido2(T1, Faces,Livres, nLivres, Rejeitadas, Pontos, i1);
            int t2 = Valido2(T2, Faces,Livres, nLivres, Rejeitadas, Pontos, i2);
            int t3 = Valido2(T3, Faces,Livres, nLivres, Rejeitadas, Pontos, i3);

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
            }
            else{
                Ind--;
            }

        }


    }else{
        return p_OtimoValido(F,Faces, Pontos, Livres, nLivres, Rejeitadas);

    }

    //EBusca -> 0:

    return Otm;

}

void Triangulacao(Objeto *Conv_Obj, bool EBusca){

    vector <Face> Faces;
    int NF = Conv_Obj->faces.size();
    int *Livres = new int[NF];

    for(int i=0;i<NF;i++){
        Face T(Conv_Obj->faces.at(i)->P2-1,Conv_Obj->faces.at(i)->P1-1,Conv_Obj->faces.at(i)->P3-1);
        Faces.push_back(T);
        Livres[i] = i;
    }
    vector <int> Rejeitadas;

   int nL = NF;
   int controle = 0;

    while(nL>0 && controle < 100000){


        Face F = Faces.at(Livres[0]);

        Faces.at(Livres[0]).Val = false;

        cout << "F -> " << F.P1 << F.P2 << F.P3 <<";"<< endl;
        float Otimo = Melhor_Ponto(F, &Faces, &Conv_Obj->points, Livres, nL, Rejeitadas, EBusca);
        cout << Otimo << endl;
        if(Otimo != -1){
            Conv_Obj->addSimplex(F.P1, F.P2, F.P3, Otimo);
        }else{
            Rejeitadas.push_back(Livres[0]);
        }



       free(Livres);
       nL = Faces.size();
//       cout << nL << endl;
       Livres = new int[nL];
       nL = attLivres(Faces, Livres);
//       cout << "Livres :" << nL << endl;
//       ImpFaces(Faces);
       controle++;

    }
    cout << "COntrole "<< controle << endl;

}
