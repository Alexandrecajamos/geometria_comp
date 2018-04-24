#include "glwidget.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <time.h>
#include "quickhull3d.h"
#include "fecho2d.h"
#include <sstream>


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


    int max;
    max = Pmax(Pol, iA,iB,iC, validos);


    if(max == -1){

        if(Pol->Pertence(iA,iB,iC)){
            return;
        }

        Pol->addFace(iA, iB,iC);

        delay(velocidade);updateGL();

        Fecho[iA] = true; Fecho[iB] = true; Fecho[iC] = true;
        return;
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


    bool* valC1 = CopiaValidos(Validos,N);
    bool* valC2 = CopiaValidos(Validos,N);


    Particiona(Pol, a,b,c, valC1);
    Particiona(Pol, a,c,b, valC2);

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
       GLfloat luzAmbiente[4]={1,1,1,1.0};

       GLfloat luzDifusa[4]={1.2,1.2,1.2,1.0};

       GLfloat luzEspecular[4]={1, 1, 1, 0.0};

       GLfloat posicaoLuz[4]={10.0, 10.0, 10.0, 0};

       GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
       GLint especMaterial = 100;

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
       //glEnable(GL_COLOR_MATERIAL);
       //Habilita o uso de iluminação
        glEnable(GL_LIGHTING);

        glEnable(GL_LIGHT0);

       // Habilita o depth-buffering  Opacidade dos objetos
        glEnable(GL_DEPTH_TEST);

        Obj = new Objeto();

        Obj->addPoint(0,10,0);
        Obj->addPoint(10,0,10);
        Obj->addPoint(-10,0,10);
        Obj->addPoint(-10,0,-10);
        Obj->addPoint(10,0,-10);

        Objs.push_back(Obj);


}
void GLWidget::paintGL()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    float Material[4]={0.145098039, 0.145098039, 0.145098039, 1.0};
    glMatrixMode(GL_MODELVIEW);

    glMaterialfv(GL_FRONT, GL_AMBIENT, Material);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Material);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Material);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    glLoadIdentity();
    gluLookAt(Ex,Ey,Ez,Lox,Loy,Loz,Avx,Avy,Avz);

    for(vector<Objeto*>::iterator i = Objs.begin(); i!= Objs.end(); i++){
        PintaPontos((*i));
        PintaFaces((*i));
    }

    cout << Objs.at(0)->faces.size() << endl;

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

vector<Objeto*> GLWidget::ReadObjs (std::string filepath){

    ifstream readFile(filepath);
    string identifier, x, y, z, line;

    vector<Objeto*> Objetos;

    int sub_conj = -1;

    while(getline(readFile, line)){
        stringstream iss(line);
        getline(iss, identifier, ' ');

        if(identifier == "O"){
            Objeto* O = new Objeto();
            Objetos.push_back(O);
            sub_conj++;
        }

        if(identifier == "V"){
            getline(iss, x, ' ');
            getline(iss, y, ' ');
            getline(iss, z, ' ');
            Objetos.at(sub_conj)->addPoint(stof(x),stof(y),stof(z));

        }
    }

    return Objetos;
}
void GLWidget::WriteObjs(vector<Objeto*> Objs){

    int nPartes = Objs.size();

    std::ofstream output("/home/alexandre/geometria_comp/OpenGL/data/output/output_ "+ File + ".obj");

    for (int i = 0; i<nPartes; i++){

        Objeto *Otemp = Objs.at(i);
        int nPontos = Otemp->points.size();
        int nFaces = Otemp->faces.size();

        output << "O P" << i+1 << "\n";

        for (int j = 0; j<nPontos; j++){
            Coord_3D *T = Otemp->points.at(j);
            output << "V " << T->x << " " << T->y << " " << T->z << "\n";
        }
        for (int j = 0; j < nFaces; j++){
            Face *F = Otemp->faces.at(j);
            output << "F " << F->P1 << " " << F->P2 << " " << F->P3 << "\n";
        }

    }
}


void GLWidget::Fecho(){

for(vector<Objeto*>::iterator i = Objs.begin(); i!= Objs.end(); i++){
        (*i)->faces.clear();
        (*i) = QuickHull((*i));
        updateGL();
    }}
void GLWidget::FechoAnimado(){

    for(vector<Objeto*>::iterator i = Objs.begin(); i!= Objs.end(); i++){
        (*i)->faces.clear();
        QuickHull_Animado((*i),velocidade);
    }
}

void GLWidget::Importar(){
    Objs.clear();
    cout << File << endl;
    Objs = ReadObjs("/home/alexandre/geometria_comp/OpenGL/data/input/"+File+".obj");
    updateGL();
}
void GLWidget::Exportar(){
    WriteObjs(Objs);
}
void GLWidget::Video(){
    float x = 2*PI;
    float R = Ex;
    float aux = Ez;
    for(float i=10; i>=1; i--){
        float y = (i/10);
        delay(velocidade);
        //cout << cos(x*y)*50 << ", " <<  sin(x*y)*50 << endl;
        Ex=cos(x*y)*R;
        Ez=-sin(x*y)*R;
        updateGL();
    }
    Ex = R;
    Ez = aux;
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
void GLWidget::attVelocidade(int x){
    this->velocidade = x;
}
void GLWidget::attFile(QString s){
    this->File = s.toUtf8().constData(); //s.toUtf8().constData();
}
