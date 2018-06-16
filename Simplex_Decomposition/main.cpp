#include "mainwindow.h"
#include <QApplication>
#include <GL/glut.h>
#include "coord_3d.h"
#include "intersecet3d.h"
#include "intersect.h"
#include <iostream>

#include "objeto.h"
#include "vetor.h"

bool adj(Face *F1, Face *F2, int &i, int &j){
    int f1[3],f2[3];
    f1[0]=F1->P1;f1[1]=F1->P2;f1[2]=F1->P3;
    f2[0]=F2->P1;f2[1]=F2->P2;f2[2]=F2->P3;
    i=0;

    bool c = false;

    while(i<3 && !c){
        j=0;
        while(j<3 && !c){
            if(f1[i] == f2[j])
                c = true;
            else
                j++;
        }
        if(!c)
            i++;
    }
    cout << i << j <<endl;

    if(i==3)
        return false;

    return true;
}



int main(int argc, char *argv[])
{

    Objeto *Obj = new Objeto();
    Obj->addPoint(0,0,0);
      Obj->addPoint(10,0,0);
      Obj->addPoint(10,0,-10);
      Obj->addPoint(0,0,-10);
      Obj->addPoint(0,10,0);
      Obj->addPoint(10,10,0);
      Obj->addPoint(10,10,-10);
      Obj->addPoint(0,10,-10);

//      Obj->addFace(0,1,4); //0
//      Obj->addFace(4,1,5);//1
//      Obj->addFace(1,2,5);//2
//      Obj->addFace(5,2,6);//3
//      Obj->addFace(2,3,6);//4
//      Obj->addFace(6,3,7);//5
//      Obj->addFace(3,0,7);//6
//      Obj->addFace(7,0,4);//7
//      Obj->addFace(4,5,7);//8
//      Obj->addFace(7,5,6);//9
//      Obj->addFace(1,0,2);//10
//      Obj->addFace(2,0,3);//11
//      Obj->addFace(1,0,4);



//      Coord_3D *A1 = Obj->points.at(2);
//      Coord_3D *A2 = Obj->points.at(1);
//      Coord_3D *A3 = Obj->points.at(0);

//      Coord_3D *B1 = Obj->points.at(0);
//      Coord_3D *B2 = Obj->points.at(1);
//      Coord_3D *B3 = Obj->points.at(3);

//      std::cout << IntersecaoTriangulos(A1, A2, A3, B1, B2, B3) << std::endl;

//    std::cout << intersectF(Obj->faces.at(12), Obj->faces.at(0), &Obj->points) << std::endl;
//    std::cout << intersect(A1,A2,A3,B1,B2,B3) << std::endl;

    glutInit(&argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
