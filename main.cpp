#include "vetor.h"
#include "poligono.h"
#include "objeto.h"



int main()
{

    Objeto *P1 = new Objeto();

    P1->addPoint(3,2,2);
    P1->addPoint(3,0,5);
    P1->addPoint(2,1,8);
    P1->addPoint(0,1,1);

    P1->ImpPoints();
    cout << endl;


    P1->Ordena(2);


    P1->ImpPoints();
    cout << endl;


    return 0;
}


