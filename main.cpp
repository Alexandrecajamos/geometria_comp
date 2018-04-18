#include "vetor.h"
#include "poligono.h"
#include "objeto.h"
#include "fecho2d.h"
#include "quickhull3d.h"


int main()
{

    Poligono* Pol = new Poligono();

//    cout << Pertence(*(C2->points.at(3)),*(C1->points.at(1)),*(C1->points.at(2)))<< endl;

    Pol->addPoint(1,2);
    Pol->addPoint(1.5,3.5);
    Pol->addPoint(2,1);
    Pol->addPoint(3,3);
    Pol->addPoint(1,5);
    Pol->addPoint(2.5,6);
    Pol->addPoint(3.5,5);
    Pol->addPoint(5,5);

//    Pol = QuickHull(Pol);
//    Pol = Jarvis(Pol);
//    Pol = Estrelado(Pol);
//     Pol->Imp();


  // Pol = Graham(Pol);
    Pol = MergeHull(Pol);
    Pol->Imp();

    //cout << endl << " Pertence "<< Pertence(*(Pol->points.at(0)),*(Pol->points.at(1)),*(Pol->points.at(2))) << endl;
    return 0;
}


