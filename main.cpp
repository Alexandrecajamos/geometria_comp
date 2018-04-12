#include "vetor.h"
#include "poligono.h"
#include "objeto.h"
#include "fecho2d.h"
//#include "quickhull3d.h"




int main()
{

//    Objeto *P1 = new Objeto();

//    P1->addPoint(0,0,5);
//    P1->addPoint(5,0,0);
//    P1->addPoint(0,0,-5);
//    P1->addPoint(0,5,0);

//    P1->addPoint(5,5,5);

//    P1->ImpPoints();


//    P1 = QuickHull(P1);
//    cout << "teste" << endl;
//    P1->ImpPoints();


    //P1 = Particiona(P1,a,b,c);

    //P1->ImpPoints();



    Poligono *P1 = new Poligono();

    P1->addPoint(1,1);
    P1->addPoint(2,1);
    P1->addPoint(3,1);
    P1->addPoint(4,1);
    P1->addPoint(2,2);
    P1->addPoint(3,2);
    P1->addPoint(2,3);
    P1->addPoint(3,3);
    P1->addPoint(4,3);
    P1->addPoint(3,4);
    P1->addPoint(2,4);
    P1->addPoint(4,4);

    P1->Imp();

    cout << "Fecho" << endl;
    P1 = QuickHull(P1);
    P1->Imp();


    return 0;
}


