#include "quickhull3d.h"

Objeto* Combina(Objeto *P1, Objeto *P2, Objeto *P3){
    Objeto *Res = new Objeto();

    for(std::vector<Coord_3D*>::iterator i = P1->points.begin(); i!= P1->points.end(); i++)
        Res->addPoint((*i)->x,(*i)->y, (*i)->z);
    for(std::vector<Coord_3D*>::iterator i = P2->points.begin(); i!= P2->points.end(); i++)
        Res->addPoint((*i)->x,(*i)->y, (*i)->z);
    for(std::vector<Coord_3D*>::iterator i = P3->points.begin(); i!= P3->points.end(); i++)
        Res->addPoint((*i)->x,(*i)->y, (*i)->z);
    return Res;
}
Objeto* Combina2(Objeto *P1, Objeto *P2){
    Objeto *Res = new Objeto();

    for(std::vector<Coord_3D*>::iterator i = P1->points.begin(); i!= P1->points.end(); i++)
        Res->addPoint((*i)->x,(*i)->y, (*i)->z);
    for(std::vector<Coord_3D*>::iterator i = P2->points.begin(); i!= P2->points.end(); i++)
        Res->addPoint((*i)->x,(*i)->y, (*i)->z);

    return Res;
}

Objeto* QuickHull(Objeto* Pol){

    Coord_3D *a, *b, *c;

    a = Pol->points.at(Pol->MaiorX());
    b = Pol->points.at(Pol->MaiorY());
    c = Pol->points.at(Pol->MaiorZ());

    Objeto* Cima = Particiona(Pol, a,b,c);
    Objeto* Baixo = Particiona(Pol, a,c,b);

    Cima = QuickHull_Recursivo(Cima, a,b,c);
    Baixo = QuickHull_Recursivo(Pol,a,c,b);

    Objeto* Hull = Combina2(Cima, Baixo);

    Hull->addPoint(a->x, a->y, a->z);
    Hull->addPoint(b->x, b->y, b->z);
    Hull->addPoint(c->x, c->y, c->z);

    return Hull;

}
Objeto* QuickHull_Recursivo(Objeto *Pol, Coord_3D *a, Coord_3D *b, Coord_3D *c){
    int N = Pol->points.size();
    if(N<2)
        return Pol;

    Coord_3D* max = Pmax(Pol, a,b,c);

    Objeto *C1, *C2, *C3;

    C1 = Particiona(Pol, a,b,max);
    C2 = Particiona(Pol, b,c,max);
    C3 = Particiona(Pol, c,a,max);

    C1 = QuickHull_Recursivo(C1, a,b,max);
    C2 = QuickHull_Recursivo(C1, b,c,max);
    C3 = QuickHull_Recursivo(C1, c,a,max);

    return Combina(C1,C2,C3);

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
Objeto* Particiona(Objeto* Pol, Coord_3D* a, Coord_3D*b, Coord_3D*c){
    Objeto* Res = new Objeto();
    Coord_3D nF = Normal(a,b,c);

    int N = Pol->points.size();
    for(int i=0; i < N;i++){
        Coord_3D temp = *(Pol->points.at(i));
        temp.operator -=(a);
        float pE = ProdutoEscalar3D(temp, nF);
        if(pE>0)
            Res->addPoint(Pol->points.at(i)->x, Pol->points.at(i)->y, Pol->points.at(i)->z);
    }

    return Res;

}
Coord_3D* Pmax(Objeto* Pol, Coord_3D* a, Coord_3D*b, Coord_3D*c){
    float MairVolume = 0;
    Coord_3D nF = Normal(a,b,c);

    Coord_3D* Ret;

    int N = Pol->points.size();
    if(N>=1)
        Ret = Pol->points.at(0);

    for(int i=1; i < N;i++){
        Coord_3D temp = *(Pol->points.at(i));
        temp.operator -=(a);
        float pE = ProdutoEscalar3D(temp, nF);
        if(pE>MairVolume){
            MairVolume = pE;
            Ret->x=Pol->points.at(i)->x;
            Ret->y=Pol->points.at(i)->y;
            Ret->z=Pol->points.at(i)->z;


        }
            //Res->addPoint(Pol->points.at(i)->x, Pol->points.at(i)->y, Pol->points.at(i)->z);
    }

    return Ret;

}
