#include "vetor.h"
#include "poligono.h"
#include "objeto.h"
#include "fecho2d.h"
#include "quickhull3d.h"
#include "triangulo.h"

int main()
{

//    Coord_2D V1(1,6);

//    Coord_2D V2(5,2);

//    float Vet = ProdutoVetorial2D(V1,V2);
//    cout << Vet << endl;
    //Vet.ImpCoord_2D();

    Coord_3D c0(0,0,0);

    Coord_3D c1(0,0,7.071);

    Coord_3D c2(7.071,0,0);

    Coord_3D c3(0,7.071,0);
    Coord_3D c4(0,0,10);
    Coord_3D c5(0,5,0);

    vector<Coord_3D*> v;
    v.push_back(&c0);
    v.push_back(&c1);
    v.push_back(&c2);
    v.push_back(&c3);
    v.push_back(&c4);
    v.push_back(&c5);

    int nC = 3;
    int cd[nC] = {3,4,5};

    float **R = RankDistFace(&c0, &c1, &c2, v, cd, nC, true);
    cout << endl;
//    float ** R = RankAngSol(&c0,&c1,&c2, v,cd, 3, true);
//    cout << endl;
    for(int i=0;i<3;i++)
        cout << R[i][0] << ", id(" << R[i][1] <<");" << endl;


    cout << ANGSolido(&c0,&c1,&c2,&c4) << endl;

//    triangulo T(c0, c1, c3);

//    float u,v,w;
//    T.Barycentric(c2, c0, c1,c3, u, v, w);
//    cout << "Teste" << u << ", " << v << ", " << w;

//    Poligono* Pol = new Poligono();


//    Pol->addPoint(3,1);
//    Pol->addPoint(5,1);
//    Pol->addPoint(7,1);
//    Pol->addPoint(8,2);
//    Pol->addPoint(6.5,3);
//    Pol->addPoint(5.5,3.5);
//    Pol->addPoint(6,5);
//    Pol->addPoint(3,5);
//    Pol->addPoint(3.5,3.5);
//    Pol->addPoint(1,2.5);

//    //Pol->Imp();

//    cout << "Estrelado" << endl;
//    Pol = Estrelado(Pol);
//    Pol->Imp();




    return 0;
}


