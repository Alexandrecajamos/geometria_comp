#include "fecho2d.h"

Poligono* QuickHull(Poligono *Pol, Coord_2D *a, Coord_2D *b){
    int N = Pol->points.size();

    if(N<=2){
        return Pol;
    }

    int pMin = Pol->MenorX();
    int pMax = Pol->MaiorX();

    a = Pol->points.at(pMin);
    b = Pol->points.at(pMax);

    Coord_2D* p1 = Pmax(Pol,a,b);
    Coord_2D* p2 = Pmax(Pol,b,a);

    Poligono* Q1 = QuickHull(Particiona(Pol,a,p1),a,p1);
    Poligono* Q2 = QuickHull(Particiona(Pol,p1,b),p1,b);

    Poligono* Q3 = QuickHull(Particiona(Pol,b,p2),b,p2);
    Poligono* Q4 = QuickHull(Particiona(Pol,p2,a),p2,a);


    Poligono* Hull = new Poligono();
    Hull->addPoint(a->x, a->y);
    Hull->addPoint(b->x, b->y);
    Hull->addPoint(p1->x, p1->y);
    Hull->addPoint(p2->x, p2->y);


    for(std::vector<Coord_2D*>::iterator i = Q1->points.begin(); i!= Q1->points.end(); i++)
        Hull->addPoint((*i)->x,(*i)->y);
    for(std::vector<Coord_2D*>::iterator i = Q2->points.begin(); i!= Q2->points.end(); i++)
        Hull->addPoint((*i)->x,(*i)->y);
    for(std::vector<Coord_2D*>::iterator i = Q3->points.begin(); i!= Q3->points.end(); i++)
        Hull->addPoint((*i)->x,(*i)->y);
    for(std::vector<Coord_2D*>::iterator i = Q4->points.begin(); i!= Q4->points.end(); i++)
        Hull->addPoint((*i)->x,(*i)->y);

    return Hull;
}



Poligono* QuickHull2(Poligono *Pol, Coord_2D *a, Coord_2D *b){
    int N = Pol->points.size();

    if(N<=2){
        Poligono* Novo = new Poligono();
        Novo->addPoint(a->x, a->y);
        Novo->addPoint(b->x, b->y);
        return Novo;
    }

    int pMin = Pol->MenorX();
    int pMax = Pol->MaiorX();

    a = Pol->points.at(pMin);
    b = Pol->points.at(pMax);

    cout<<"teste"<<endl;


    Coord_2D* p = Pmax(Pol,a,b);

    Poligono* C1 = Particiona(Pol,a,p);
    Poligono* C2 = Particiona(Pol,p,b);
    Poligono* C3 = Particiona(Pol,b,a);

    Poligono* Hull = new Poligono();


    //Hull->addPoint(p->x, p->y);

    Poligono* Q1 = QuickHull(C1,a,p);
    Poligono* Q2 = QuickHull(C2,p,b);
    Poligono* Q3 = QuickHull(C3,b,a);

    for(std::vector<Coord_2D*>::iterator i = Q1->points.begin(); i!= Q1->points.end(); i++)
        Hull->addPoint((*i)->x,(*i)->y);
    for(std::vector<Coord_2D*>::iterator i = Q2->points.begin(); i!= Q2->points.end(); i++)
        Hull->addPoint((*i)->x,(*i)->y);
    for(std::vector<Coord_2D*>::iterator i = Q3->points.begin(); i!= Q3->points.end(); i++)
        Hull->addPoint((*i)->x,(*i)->y);

    cout<<"FIM teste"<<endl;

    return Hull;
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

    for(int i=1; i < N;i++){
        float area = Area(a,b,Pol->points.at(i));
        if(area>AreaMax){
            AreaMax = area;
            Ind = i;
        }
    }
    Coord_2D* Max = new Coord_2D(Pol->points.at(Ind)->x,Pol->points.at(Ind)->y);
    return Max;
}
