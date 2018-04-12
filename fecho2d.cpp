#include "fecho2d.h"

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


    Poligono* C1 = Particiona(Pol, a,b);
    Poligono* C2 = Particiona(Pol, b,a);

    C1 = QHRec(C1, a,b);
    C2 = QHRec(C2, b,a);

    Poligono* Ret = new Poligono();
    Ret->addPoint(a->x, a->x);
    Ret = Combina(Ret,C2);
    Ret->addPoint(b->x,b->y);
    Ret = Combina(Ret, C1);

    return Ret;

}

Poligono* QHRec(Poligono *Pol, Coord_2D *a, Coord_2D *b){
    int N = Pol->points.size();
    if(N < 2){
        return Pol;
    }

    Coord_2D* p = Pmax(Pol, a,b);
    // cout << "P max : ";
    //p->ImpCoord_2D();
    Poligono* C1 = QHRec(Particiona(Pol, a,p), a,p);
    Poligono* Result = QHRec(Particiona(Pol, p,b),p,b);
    Result->addPoint(p->x,p->y);
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

float Area(Coord_2D *a, Coord_2D *b, Coord_2D *c){

    Coord_2D A1(b->x,b->y);
    Coord_2D A2(c->x,c->y);
    A1.operator -=(a);
    A2.operator -=(a);
    return ProdutoVetorial2D(A1,A2)/2;

}

Coord_2D* Pmax(Poligono *Pol, Coord_2D *a, Coord_2D *b){

    float AreaMax = Area(a,b,Pol->points.at(0));

    int N = Pol->points.size();
    int Ind;
    Coord_2D* Atual = Pol->points.at(0);

    for(int i=1; i < N;i++){
        float area = Area(a,b,Pol->points.at(i));
        if(area>AreaMax){
            AreaMax = area;
            Ind = i;
            Atual = Pol->points.at(i);
        }
        if(area == AreaMax && Atual->x > Pol->points.at(i)->x){
            cout << "Hello";
            AreaMax = area;
            Ind = i;
            Atual = Pol->points.at(i);
        }
    }
    Coord_2D* Max = new Coord_2D(Pol->points.at(Ind)->x,Pol->points.at(Ind)->y);
    return Max;
}
