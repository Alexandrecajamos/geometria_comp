#include "vetor.h"
#include "poligono.h"
#include "objeto.h"
#include "fecho2d.h"




int main()
{

    Poligono *P1 = new Poligono();

    P1->addPoint(0,0);
    P1->addPoint(1,0);
    P1->addPoint(0,1);
    P1->addPoint(1,1);
    P1->addPoint(0.5,2);

    P1->addPoint(-0.5,1);
    P1->addPoint(0.5,0.5);
    P1->addPoint(-0.5,0);
    P1->addPoint(2,0.5);

    P1->addPoint(2,0);

    P1->addPoint(0,-2);


    P1->Imp();
    cout << endl;

    Coord_2D* a  = new Coord_2D(0,0);
    Coord_2D* b = new Coord_2D(0,0);


    //cout<< CCW2D((*a),(*b)); // B está à esquerda de A?
    //cout << areaTriangulo(a,b,P1->points.at(1));
    //Coord_2D* max = Pmax(P1,a,b);
    //max->ImpCoord_2D();
    //P1 = Esquerda(P1, a,b );
    P1 = QuickHull(P1, a,b);


    P1->Imp();

    return 0;
}


