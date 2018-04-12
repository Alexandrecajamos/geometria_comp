#include "vetor.h"
#include "poligono.h"
#include "objeto.h"
#include "quickhull3d.h"




int main()
{

    Objeto *P1 = new Objeto();

    P1->addPoint(0,0,5);
    P1->addPoint(5,0,0);
    P1->addPoint(0,0,-5);
    P1->addPoint(0,5,0);

    P1->addPoint(5,5,5);

    P1->ImpPoints();

    Coord_3D* a  = new Coord_3D(0,0,0);
    Coord_3D* b = new Coord_3D(0,0,0);
    Coord_3D* c  = new Coord_3D(0,0,0);


    P1 = QuickHull(P1);
    cout << "teste" << endl;
    P1->ImpPoints();


    //P1 = Particiona(P1,a,b,c);

    //P1->ImpPoints();


    /*
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
*/


    return 0;
}


