#include "fecho2d.h"


float Area(Coord_2D *a, Coord_2D *b, Coord_2D *c){

    Coord_2D A1(b->x,b->y);
    Coord_2D A2(c->x,c->y);
    A1.operator -=(a);
    A2.operator -=(a);
    return ProdutoVetorial2D(A1,A2)/2;

}
Poligono* Combina(Poligono*A, Poligono*B){

    Poligono* Comb = new Poligono();
    for(std::vector<Coord_2D*>::iterator i = A->points.begin(); i!= A->points.end(); i++){
        Comb->addPoint((*i)->x,(*i)->y);
    }
    for(std::vector<Coord_2D*>::iterator i = B->points.begin(); i!= B->points.end(); i++){
        Comb->addPoint((*i)->x,(*i)->y);
    }
    return Comb;
}

Poligono* QuickHull(Poligono *Pol){

    Coord_2D *a, *b;

    a = Pol->points.at(Pol->MenorX());
    b = Pol->points.at(Pol->MaiorX());

    Poligono* C1 = QHRec(Particiona(Pol, a,b), a,b);
    Poligono* C2 = QHRec(Particiona(Pol, b,a), b,a);

    Poligono* Fecho = new Poligono();

    Fecho->addPoint(a->x, a->y);
    Fecho = Combina(Fecho,C2);
    Fecho->addPoint(b->x,b->y);
    Fecho = Combina(Fecho, C1);

    return Fecho;

}
Poligono* QHRec(Poligono *Pol, Coord_2D *a, Coord_2D *b){
    int N = Pol->points.size();
    if(N == 0){
        return Pol;
    }
    int max;
    if(N == 1)
        max = 0;
    else
        max = Pmax(Pol, a,b);


    Coord_2D p(Pol->points.at(max)->x,Pol->points.at(max)->y);


    Poligono* C1 = QHRec(Particiona(Pol, a,&p), a,&p);
    Poligono* Result = QHRec(Particiona(Pol, &p,b),&p,b);

    Result->addPoint(p.x,p.y);
    Result = Combina(Result,C1);

    return Result;
}
Poligono* Particiona(Poligono *Pol, Coord_2D *a, Coord_2D *b){
    Poligono* Esq = new Poligono();
    Coord_2D* VetAb = new Coord_2D(b->x,b->y);
    VetAb->operator -=(a);
    int N = Pol->points.size();
    for(int i=0; i < N;i++){
        Coord_2D temp(Pol->points.at(i)->x,Pol->points.at(i)->y);
        temp.operator -=(a);
        if(CCW2D((*VetAb),temp))
            Esq->addPoint(Pol->points.at(i)->x,Pol->points.at(i)->y);
    }
    return Esq;

}
int Pmax(Poligono *Pol, Coord_2D *a, Coord_2D *b){

    float AreaMax = Area(a,b,Pol->points.at(0));
    int N = Pol->points.size();
    int Ind;
    for(int i=1; i < N;i++){
        float area = Area(a,b,Pol->points.at(i));
        if(area>AreaMax)
            Ind = i;
    }
    return Ind;
}



Poligono* Jarvis(Poligono *Pol){
    Poligono* Fecho = new Poligono();
    int mY = Pol->MenorY();
    Fecho->addPoint(Pol->points.at(mY)->x,Pol->points.at(mY)->y);
    //Fecho->points.at(0)->ImpCoord_2D();
    int ant, prox;
    ant=mY;

    Coord_2D AF(1,0);
    //AF.operator +=(Pol->points.at(ant));
    AF.operator -=(Pol->points.at(ant));
    //AF.ImpCoord_2D();


    int N = Pol->points.size();

    while(prox != mY){

        float mAng = 8;
        int ind_mAng;
        for(int i=0; i<N;i++){
            float ang=0;
            if(i!=ant){
                Coord_2D AT = *(Pol->points.at(i));
                AT.operator -=(Pol->points.at(ant));
                ang = PseudoAngulo(AF,AT);
                //cout<< ant <<" "<< i << ": " << mAng<<endl;
                if(ang <= mAng){
                    mAng=ang;
                    ind_mAng=i;

                }
            }
        }

        prox = ind_mAng;
        //cout<< ant <<" "<< prox << ": " << mAng<<endl;
        if(prox != mY){
            Fecho->addPoint(Pol->points.at(prox)->x,Pol->points.at(prox)->y);
            AF = *(Pol->points.at(prox));
            AF.operator -=(Pol->points.at(ant));
        }
        ant=prox;

    }


    return Fecho;

}


//QuickSort para ordenar matriz considerando o valor de 1 coluna. Sendo ind o índice da coluna a partir da qual se dá a ordenação e N_Colluns o número de colunas da matriz

void trocar(float* x, float* y, int N) {
    float* z = (float*)malloc(sizeof(float)*N);
    for(int i = 0; i<N;i++){
        z[i] = x[i];
        x[i] = y[i];
        y[i] = z[i];
    }
    free(z);
}
int Particione_original(float** vetor, int p, int r, int ind, int N_Colluns) {
    int i=p-1;
    for (int j=p; j<r; j++) {
        if (vetor[j][ind] <= vetor[r][ind]) {
            i++;
            trocar(vetor[i], vetor[j],N_Colluns);
        }
    }
    trocar(vetor[i+1], vetor[r], N_Colluns);
    return i+1;
}
int Particione_aleat(float** vetor, int p, int r, int ind, int N_Colluns) {
    srand (time(NULL));
    int pos_pivo = p + rand()%(r-p+1);
    trocar(vetor[pos_pivo], vetor[r],N_Colluns);
    return Particione_original(vetor,p,r,ind, N_Colluns);
}
void QuickSort(float** vetor, int p, int r, int ind, int N_Colluns) {
    if (p>=r) return;
    int q = Particione_aleat(vetor,p,r, ind, N_Colluns);
    QuickSort(vetor,p,q-1, ind, N_Colluns);
    QuickSort(vetor,q+1,r, ind, N_Colluns);
}



Poligono* Estrelado(Poligono *Pol){
    Poligono* Est = new Poligono();


    float MX,mX,MY,mY;

    MX = Pol->points.at(Pol->MaiorX())->x;
    mX = Pol->points.at(Pol->MenorX())->x;
    MY = Pol->points.at(Pol->MaiorY())->y;
    mY = Pol->points.at(Pol->MenorY())->y;

    float dX = (abs(MX) + abs(mX))/2;
    float dY = (abs(MY) + abs(mY))/2;

    Coord_2D centro(dX, dY);
    Coord_2D U(1,0);
    U.operator +=(&centro);
    U.operator -=(&centro);


    int N = Pol->points.size();

    float **x = (float**)malloc(sizeof(float*)*N);
    for(int i =0; i<N;i++)
        x[i] = (float*)malloc(sizeof(float)*2);


    for(int i = 0; i<N; i++){
        Coord_2D Temp = *(Pol->points.at(i));
        Temp.operator -=(&centro);
        x[i][0]=i;
        x[i][1]=PseudoAngulo(U,Temp);
    }

    QuickSort(x,0,N-1,1,2); // Ordena matriz x, do índice 0 ao N-1, considerando a coluna 1, para uma matriz com 2 colunas;


    for(int i = 0; i<N; i++){
        Est->addPoint(Pol->points.at(x[i][0])->x,Pol->points.at(x[i][0])->y);
    }

    return Est;

}
bool Pertence(Coord_2D P1, Coord_2D P2, Coord_2D P3){
    Coord_2D A, B;
    A = P1;
    B = P3;
    A.operator -=(&P2);
    B.operator -=(&P2);
    float ang = PseudoAngulo(A,B);
    if(ang>=4)
        return true;
    return false;
}
Poligono* Graham(Poligono *Pol){

    Poligono* Fecho = new Poligono();
    Poligono* est = Estrelado(Pol);

    int N = est->points.size();
    Fecho->addPoint(est->points.at(0)->x,est->points.at(0)->y);

    int j = 1;

    for(int i = 1; i<(N-1);i++){
        //cout << j-1 << i << i+1 << Pertence(*(Fecho->points.at(j-1)),*(est->points.at(i)),*(est->points.at(i+1))) << endl;

        if(Pertence(*(Fecho->points.at(j-1)),*(est->points.at(i)),*(est->points.at(i+1)))){
            Fecho->addPoint(est->points.at(i)->x,est->points.at(i)->y);
            j++;
        }
    }
    if(Pertence(*(Fecho->points.at(j-1)),*(est->points.at(N-1)),*(est->points.at(0))))
        Fecho->addPoint(est->points.at(N-1)->x,est->points.at(N-1)->y);

    return Fecho;
}



Poligono* MergeHull(Poligono *Pol){
    Poligono* P = new Poligono();
    int N = Pol->points.size();
    for(int i = 0; i<N;i++)
        P->addPoint(Pol->points.at(i)->x,Pol->points.at(i)->y);
    P->Ordena(0);

    Poligono* C1 = new Poligono();
    Poligono* C2 = new Poligono();

    for(int i=0; i<N;i++){
        if(i<(N/2))
            C1->addPoint(Pol->points.at(i)->x, Pol->points.at(i)->y);
        else
            C2->addPoint(Pol->points.at(i)->x, Pol->points.at(i)->y);
    }

    C1 = MergeHull_Rec(C1);
    C2 = MergeHull_Rec(C2);

    return Merge(C1, C2);
}

Poligono* MergeHull_Rec(Poligono *Pol){

    int N = Pol->points.size();


    if(N < 3){
        return Pol;
    }
    if(N == 3){
        Coord_2D AB = *(Pol->points.at(1));
        Coord_2D AC = *(Pol->points.at(2));

        AB.operator -=(Pol->points.at(0));
        AC.operator -=(Pol->points.at(0));

        if(!CCW2D(AB,AC)){
            Pol->trocar(1,2);
        }
        return Pol;
    }

    Poligono* C1 = new Poligono();
    Poligono* C2 = new Poligono();

    int cont = N/2;
    for(int i=0; i<N;i++){
        if(i<cont)
            C1->addPoint(Pol->points.at(i)->x, Pol->points.at(i)->y);
        else
            C2->addPoint(Pol->points.at(i)->x, Pol->points.at(i)->y);
    }


    C1 = MergeHull_Rec(C1);
    C2 = MergeHull_Rec(C2);

    return Merge(C1, C2);
}

Poligono* Merge(Poligono *P1, Poligono *P2){
    Poligono* Fecho = new Poligono();

    int i = P1->MaiorX();

    int j = P2->MenorX();
    int i2=i,j2=j;


    int N1 = P1->points.size();
    int N2 = P2->points.size();
    int ant;

    if(i>0)
        ant = i-1;
    else
        ant = N1-1;

    while(!Pertence(*(P1->points.at(ant)),*(P1->points.at(i)),*(P2->points.at(j)))){
        i--;
        ant = i-1;
        if(i == 0){
            ant = N1-1;
        }
        if(i < 0){
            i=N1-1;
            ant=N1-2;
        }
    }
    int prox;

    if(j==N2-1)
        prox=0;
    else
        prox=j+1;

    while(!(Pertence(*(P1->points.at(i)), *(P2->points.at(j)),*(P2->points.at(prox))))){

        j++;prox++;
        if(j == N2){
            j=0;
            prox=1;
        }
        if(prox == N2){
            prox = 0;
        }

    }

    if(i2 == N1-1)
        ant = 0;
    else
        ant = (i2+1);

   while(!Pertence(*(P2->points.at(j2)),*(P1->points.at(i2)),*(P2->points.at(ant)))){
        i2++;ant++;
        if(i2 == N1){
            i2=0;
            ant=1;
        }
        if(ant == N1){
            ant =0;
        }

    }

   if(j2>0)
       prox = j2-1;
   else
       prox = N2-1;

   while(!Pertence(*(P2->points.at(prox)),*(P2->points.at(j2)),*(P1->points.at(i2)))){
        j2--;
        prox = j2-1;

        if(j2 == 0){
            prox = N2-1;
        }
        if(j2 < 0){
            j2=N2-1;
            prox=N2-2;
        }

   }

    int k = i2;
    while(k!=i){
        Fecho->addPoint(P1->points.at(k)->x,P1->points.at(k)->y);
        k++;
        if(k == N1)
            k=0;
    }
    Fecho->addPoint(P1->points.at(i)->x,P1->points.at(i)->y);

    k = j;
       while(k!=j2){
        Fecho->addPoint(P2->points.at(k)->x,P2->points.at(k)->y);
        k++;
        if(k == N2)
            k=0;
    }
    Fecho->addPoint(P2->points.at(j)->x,P2->points.at(j)->y);
    return Fecho;

}
