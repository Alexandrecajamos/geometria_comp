#include "mainwindow.h"
#include <QApplication>
#include <GL/glut.h>
#include "coord_3d.h"
#include "intersect.h"
#include <iostream>

#include "objeto.h"
#include "vetor.h"




int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
