#include "vetor.h"
#include "poligono.h"
#include "objeto.h"
#include "fecho2d.h"
#include "quickhull3d.h"




int main()
{

    Objeto *P1 = new Objeto();


    P1->addPoint(0,0,0);
    P1->addPoint(2,0,0);
    P1->addPoint(2,0,-2);
    P1->addPoint(0,0,-2);
    P1->addPoint(0,2,0);
    P1->addPoint(2,2,0);
    P1->addPoint(2,2,-2);
    P1->addPoint(0,2,-2);


    P1->ImpPoints();

//    bool Validos[8] = {1,1,1,1,1,1,1,1};
//    bool* valC1 = CopiaValidos(Validos,8);

//    Particiona(P1, 1,0,4,valC1);

//    cout << endl;
//    for(int i = 0; i<8;i++)
//        cout << valC1[i];
//    int max = Pmax(P1, 1,2,4, valC1);

//    cout << "Max: " << max << endl;

    QuickHull(P1);
    P1->ImpFaces();
    //P1->faces.at(1)->Imp();



//    //int max = Pmax(P1, 0,3,2);
//    bool Validos[5] = {1,1,1,1,1};
//    Particiona(P1, 0,2,3,Validos);

//    int Max = Pmax(P1, 0,3,2,Validos);

//    cout << endl << Max << endl;

//    for(int i = 0; i<5;i++)
//        cout << Validos[i];

//    //P1 = QuickHull(P1);
//    //cout << endl << endl << "Fecho 3D: " << endl;
//    P1->ImpPoints();

//    cout << endl;


//    Poligono *P1 = new Poligono();

//    P1->addPoint(1,1);
//    P1->addPoint(2,1);
//    P1->addPoint(3,1);
//    P1->addPoint(4,1);
//    P1->addPoint(2,2);
//    P1->addPoint(3,2);
//    P1->addPoint(2,3);
//    P1->addPoint(3,3);
//    P1->addPoint(4,3);
//    P1->addPoint(3,4);
//    P1->addPoint(2,4);
//    P1->addPoint(4,4);

//    P1->Imp();

//    cout << "Fecho" << endl;
//    P1 = QuickHull(P1);
//    P1->Imp();


    return 0;
}


