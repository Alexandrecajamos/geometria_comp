#include "glwidget.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer->start(0);
}



void GLWidget::initializeGL()
{
       GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
       GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};
       GLfloat luzEspecular[4]={0.7, 0.7, 0.7, 1.0};
       GLfloat posicaoLuz[4]={20.0, 30.0, 0.0, 1.0};

       GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
       GLint especMaterial = 60;

       glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

       // Habilita o modelo de colorização de Gouraud
       glShadeModel(GL_SMOOTH);

       // Define a refletância do material
       glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
       // Define a concentração do brilho
       glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

       // Ativa o uso da luz ambiente
       glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

       // Define os parâmetros da luz de número 0
       glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
       glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
       glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
       glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

       // Habilita a definição da cor do material a partir da cor corrente
      // glEnable(GL_COLOR_MATERIAL);
       //Habilita o uso de iluminação
       glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

       // Habilita o depth-buffering  Opacidade dos objetos
       glEnable(GL_DEPTH_TEST);




}

void GLWidget::paintGL()
{


    float grama[4]={0.4196, 0.5568, 0.1372, 1.0};

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // gluLookAt(Ex,Ey,Ez,Lox,Loy,Loz,Avx,Avy,Avz);

    glMatrixMode(GL_MODELVIEW);


    glMaterialfv(GL_FRONT, GL_AMBIENT, grama);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, grama);
    glMaterialfv(GL_FRONT, GL_SPECULAR, grama);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    glLoadIdentity();
    gluLookAt(Ex,Ey,Ez,Lox,Loy,Loz,Avx,Avy,Avz);







}



void GLWidget::resizeGL(int w, int h)
{

    glViewport(0,0, w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/h, 1, 1000.0);
    //glFrustum(-100,-100,w,h,3,3000);
    //gluLookAt(Ex,Ey,Ez,Lox,Loy,Loz,Avx,Avy,Avz);

    updateGL();
}

void GLWidget::Fecho(){
    Obj->addPoint(0,0,0);
    Obj->addPoint(2,0,0);
    Obj->addPoint(2,0,-2);
    Obj->addPoint(0,0,-2);
    Obj->addPoint(0,2,0);
    Obj->addPoint(2,2,0);
    Obj->addPoint(2,2,-2);
    Obj->addPoint(0,2,-2);
    Obj->addPoint(0.9,0.8,-1);

    Obj->addPoint(3,1,-1);

    Obj->ImpPoints();

    QuickHull(Obj);
    updateGL();
}


void GLWidget::Eye_X(double x){
    Ex=(float)x;
    updateGL();
}
void GLWidget::Eye_Y(double x){
    Ey=(float)x;
    updateGL();
}
void GLWidget::Eye_Z(double x){
    Ez=(float)x;
    updateGL();
}

void GLWidget::Lo_X(double x){
    Lox=(float)x;
    updateGL();
}
void GLWidget::Lo_Y(double x){
    Loy=(float)x;
    updateGL();
}
void GLWidget::Lo_Z(double x){
    Loz=(float)x;
    updateGL();
}

void GLWidget::Av_X(double x){
    Avx=(float)x;
    updateGL();
}
void GLWidget::Av_Y(double x){
    Avy=(float)x;
    updateGL();
}
void GLWidget::Av_Z(double x){
    Avz=(float)x;
    updateGL();
}

