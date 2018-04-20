#include "vetor.h"
#include "poligono.h"
#include "objeto.h"
#include "fecho2d.h"
#include "quickhull3d.h"


int main()
{

//    Coord_2D V1(1,6);

//    Coord_2D V2(5,2);

//    float Vet = ProdutoVetorial2D(V1,V2);
//    cout << Vet << endl;
    //Vet.ImpCoord_2D();


    Poligono* Pol = new Poligono();


    Pol->addPoint(3,1);
    Pol->addPoint(5,1);
    Pol->addPoint(7,1);
    Pol->addPoint(8,2);
    Pol->addPoint(6.5,3);
    Pol->addPoint(5.5,3.5);
    Pol->addPoint(6,5);
    Pol->addPoint(3,5);
    Pol->addPoint(3.5,3.5);
    Pol->addPoint(1,2.5);

    //Pol->Imp();

    cout << "Estrelado" << endl;
    Pol = Estrelado(Pol);
    Pol->Imp();




    return 0;
}


