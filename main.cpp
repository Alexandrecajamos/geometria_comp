#include "vetor.h"
#include "poligono.h"


int main()
{

    Poligono *P1 = new Poligono();

    P1->addPoint(3,2);
    P1->addPoint(3,0);
    P1->addPoint(2,1);
    P1->addPoint(0,1);

    int Maior = P1->MenorY();
    cout << Maior << endl;


    return 0;
}
