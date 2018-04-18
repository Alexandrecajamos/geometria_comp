#include "glwidget.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <time.h>
#include "quickhull3d.h"




void delay(int milliseconds)
{
    long pause;
    clock_t now,then;
    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}



GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{

//    timer = new QTimer();
//    connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
//    timer->start(0);
}


void GLWidget::PintaPontos(Objeto *P){
    glBegin(GL_POINTS);
    for(std::vector<Coord_3D*>::iterator i = P->points.begin(); i!= P->points.end(); i++){
        glVertex3f((*i)->x,(*i)->y,(*i)->z);
    }
    glEnd();
}
void GLWidget::PintaFace(int iA, int iB,int iC, Objeto* Pol){

    glBegin(GL_TRIANGLES);
    glVertex3f(Pol->points.at(iA)->x,Pol->points.at(iA)->y,Pol->points.at(iA)->z);
    glVertex3f(Pol->points.at(iB)->x,Pol->points.at(iB)->y,Pol->points.at(iB)->z);
    glVertex3f(Pol->points.at(iC)->x,Pol->points.at(iC)->y,Pol->points.at(iC)->z);
    glEnd();
    //delay(100);

}

void GLWidget::QuickHull_Recursivo_Animado(Objeto *Pol, int iA, int iB, int iC, bool *validos, bool *Fecho, int velocidade){

    int N = Pol->points.size();
    int Pontos_Validos = ContaValidos(validos,N);

    if(Pontos_Validos == 0){
        if(Pol->Pertence(iA,iB,iC)){
            return;
        }
        int max = Pmax(Pol,iA,iB,iC,validos,Fecho);
        if(max != -1){
            return;
        }
        Pol->addFace(iA, iB,iC);

        delay(velocidade);updateGL();

        Fecho[iA] = true; Fecho[iB] = true; Fecho[iC] = true;
        return;
    }
    int max;

    if(Pontos_Validos == 1){
        int iP;
        for(int i=0;i<N;i++)
            if(validos[i])
                iP = i;

        max = Pmax(Pol,iA,iB,iC,validos,Fecho);
        if(max != -1 && max != iP){
            //cout << endl<< iA << iB <<iC << iP;
            validos[iP] = false;
            return;
        }
        Coord_3D nF = Normal(Pol->points.at(iA), Pol->points.at(iB), Pol->points.at(iC));
        if(Coplanares(nF,iA,iP,Pol)){
            if(Fecho[iP]){
                if(!(Pol->Pertence(iA,iB,iC))){

                    Pol->addFace(iA,iB,iC);
                     delay(velocidade);updateGL();
                    }// || Pol->Pertence(iA,iB,iP)))

                validos[iP]=false;
                return;
            }



                Pol->addFace(iA, iB,iC);
                delay(velocidade);updateGL();
                Coord_3D nF2 = Normal(Pol->points.at(iA), Pol->points.at(iP), Pol->points.at(iB));

                if(((nF.z > 0 && nF2.z >0) || (nF.z < 0 && nF2.z < 0))&& !Pol->Pertence(iA,iP,iB)){
                    Pol->addFace(iA, iP,iB);
                   delay(velocidade); updateGL();
                }else
                    if(!Pol->Pertence(iB,iP,iC)){
                        Pol->addFace(iB, iP,iC);
                        delay(velocidade);updateGL();
                    }

            Fecho[iA] = true; Fecho[iB] = true; Fecho[iC] = true; Fecho[iP] = true;
            return;

        }else
            max = iP;

    }else
        max = Pmax(Pol, iA,iB,iC, validos, Fecho);

    if(max == -1){
        int iP;
        for(int i=0;i<N;i++)
            if(validos[i])
                iP = i;
        max = iP;
        validos[iP]= false;
        validos[iP+1]= false;
        //return;  // Todos são co-planares
    }

    bool* valC1 = CopiaValidos(validos,N);
    bool* valC2 = CopiaValidos(validos,N);
    bool* valC3 = CopiaValidos(validos,N);


    Particiona(Pol, iA,iB,max, valC1);
    Particiona(Pol, iB,iC,max, valC2);
    Particiona(Pol, iC,iA,max, valC3);



    QuickHull_Recursivo_Animado(Pol, iA,iB,max, valC1, Fecho, velocidade);
    QuickHull_Recursivo_Animado(Pol, iB,iC,max, valC2, Fecho, velocidade);
    QuickHull_Recursivo_Animado(Pol, iC,iA,max, valC3, Fecho, velocidade);


    for(int i=0;i<N;i++)
        if(!valC1[i] && !valC2[i] && !valC3[i])
            validos[i] = false;


}
void GLWidget::QuickHull_Animado(Objeto* Pol, int velocidade){


    int N = Pol->points.size();
    bool *Validos = (bool*)malloc(sizeof(bool)*N);
    bool *Fecho = (bool*)malloc(sizeof(bool)*N);

    for(int i=0;i<N;i++){
        Validos[i] = 1;
        Fecho[i]=0;
    }

    Face Ext = Extremos(Pol);

    int a = Ext.P1;
    int b = Ext.P2;
    int c = Ext.P3;

    cout << endl << "Extremos: " << a << b << c << endl;

    bool* valC1 = CopiaValidos(Validos,N);
    bool* valC2 = CopiaValidos(Validos,N);

    //cout << endl;
    Particiona(Pol, a,b,c, valC1);
    Particiona(Pol, a,c,b, valC2);


    cout << "C1";
    for(int i=0; i<N;i++){
        if(valC1[i])
        cout << " " << i;
    }
    cout << endl;
    cout << "C2";
    for(int i=0; i<N;i++){
        if(valC2[i])
        cout << " " << i;
    }
    cout << endl;


    QuickHull_Recursivo_Animado(Pol, a,b,c, valC1, Fecho, velocidade);
    QuickHull_Recursivo_Animado(Pol,a,c,b, valC2, Fecho,  velocidade);



    cout <<endl;cout <<endl;
    cout << "Indices de Pontos do Fecho: " << endl;
    for(int i=0;i<N;i++)
        cout << Fecho[i];
    cout << endl;

    cout << "Número de Faces: " << Pol->faces.size()<<endl;

}
void GLWidget::PintaFaces(Objeto* Pol){
    for(std::vector<Face*>::iterator i = Pol->faces.begin(); i!= Pol->faces.end(); i++){
        PintaFace((*i)->P1,(*i)->P2,(*i)->P3,Pol);

    }
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
       //glEnable(GL_DEPTH_TEST);

    Obj = new Objeto();

    Obj->addPoint(0,0,0);
    Obj->addPoint(10,0,0);
    Obj->addPoint(10,0,-10);
    Obj->addPoint(0,0,-10);
    Obj->addPoint(0,10,0);
    //Obj->addPoint(5,5,-5);
    Obj->addPoint(10,10,0);
    Obj->addPoint(10,10,-10);
    Obj->addPoint(0,10,-10);
    Obj->addPoint(15,0,0);
//    Face F = Extremos(Obj);
//    cout << F.P1 << F.P2 << F.P3 << endl;

}
void GLWidget::paintGL()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    float Material[4]={0.745098039, 0.745098039, 0.745098039, 1.0};

    glMatrixMode(GL_MODELVIEW);

    glMaterialfv(GL_FRONT, GL_AMBIENT, Material);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Material);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Material);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    glLoadIdentity();
    gluLookAt(Ex,Ey,Ez,Lox,Loy,Loz,Avx,Avy,Avz);
    PintaPontos(Obj);
    PintaFaces(Obj);


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
     Obj->faces.clear();
     Obj = QuickHull(Obj);
     updateGL();
}

void GLWidget::FechoAnimado(){
    Obj->faces.clear();
    QuickHull_Animado(Obj,velocidade);
    Obj->ImpFaces();
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
void GLWidget::attVelocidade(int x){
    this->velocidade = x;
}
