#include "glwidget.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <time.h>
#include "quickhull3d.h"
#include <sstream>
#include "triangulacao.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{

}

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;
    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}


void GLWidget::PintaPontos(Objeto *P){
    glBegin(GL_POINTS);
    for(std::vector<Coord_3D*>::iterator i = P->points.begin(); i!= P->points.end(); i++){
        glVertex3f((*i)->x,(*i)->y,(*i)->z);
    }
    glEnd();
}
void GLWidget::PintaFace(int iA, int iB,int iC, Objeto* Pol){
    if(Arestas)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_TRIANGLES);
    glVertex3f(Pol->points.at(iA)->x,Pol->points.at(iA)->y,Pol->points.at(iA)->z);
    glVertex3f(Pol->points.at(iB)->x,Pol->points.at(iB)->y,Pol->points.at(iB)->z);
    glVertex3f(Pol->points.at(iC)->x,Pol->points.at(iC)->y,Pol->points.at(iC)->z);
    glEnd();

}

void GLWidget::QuickHull_Recursivo_Animado(Objeto *Obj, int *Parte, int nP, int a, int b, int c, int velocidade){
    int max = Pmax(Obj,Parte, nP,Obj->points.at(a),Obj->points.at(b),Obj->points.at(c));
    if(max == -1){
        Obj->addFace(a, b,c);
        delay(velocidade);updateGL();
        return;
    }
    int *p1 = (int*)malloc(sizeof(int)*nP);
    int *p2 = (int*)malloc(sizeof(int)*nP);
    int *p3 = (int*)malloc(sizeof(int)*nP);

    int N1 = Particiona(Obj,Parte, nP,p1, a,b,max);
    int N2 = Particiona(Obj,Parte, nP,p2, b,c,max);
    int N3 = Particiona(Obj,Parte, nP,p3, c,a,max);

    QuickHull_Recursivo_Animado(Obj, p1, N1, a,b,max, velocidade);
    QuickHull_Recursivo_Animado(Obj, p2, N2, b,c,max, velocidade);
    QuickHull_Recursivo_Animado(Obj, p3, N3, c,a,max, velocidade);

}
void GLWidget::QuickHull_Animado(Objeto* Obj, int velocidade){

    int a = Obj->MaiorX();
    int b = Obj->MenorX();
    int c = MaiorY(a,Obj);

    int N = Obj->points.size();
    int *Validos = (int*)malloc(sizeof(int)*N);
    int *p1 = (int*)malloc(sizeof(int)*N);
    int *p2 = (int*)malloc(sizeof(int)*N);

    for(int i=0;i<N;i++)
        Validos[i] = i;

    int N1 = Particiona(Obj,Validos, N, p1, a,b,c);
    int N2 = Particiona(Obj,Validos, N, p2, a,c,b);

    QuickHull_Recursivo_Animado(Obj,p1, N1, a,b,c, velocidade);
    QuickHull_Recursivo_Animado(Obj,p2, N2, a,c,b, velocidade);

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

        Importar();
//        Fecho();
//        Exclui_Internas(Objs.at(0));

        //        Objs.at(0)c->ImpFaces();
        Triangulacao(Objs.at(0));
        updateGL();

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
        if(Points)
            PintaPontos((*i));
        PintaFaces((*i));
    }
}
void GLWidget::resizeGL(int w, int h)
{

    glViewport(0,0, w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/h, 1, 1000.0);
    updateGL();
}


//Funções para leitura/Escrita
vector<Objeto*> GLWidget::ReadObjs (std::string filepath){

    ifstream readFile(filepath);
    string identifier, x, y, z, line;

    vector<Objeto*> Objetos;

    int sub_conj = -1;

    while(getline(readFile, line)){
        stringstream iss(line);
        getline(iss, identifier, ' ');

        if(identifier == "o"){
            Objeto* O = new Objeto();
            Objetos.push_back(O);
            sub_conj++;
        }

        if(identifier == "v"){
            getline(iss, x, ' ');
            getline(iss, y, ' ');
            getline(iss, z, ' ');
            Objetos.at(sub_conj)->addPoint(stof(x),stof(y),stof(z));

        }
        if(identifier == "f"){
            getline(iss, x, ' ');
            getline(iss, y, ' ');
            getline(iss, z, ' ');
            Objetos.at(sub_conj)->addFace(stof(x),stof(y),stof(z));

        }
    }

    return Objetos;
}
void GLWidget::WriteObjs(vector<Objeto*> Objs){

    int nPartes = Objs.size();

    std::ofstream output(path+"/output/output_"+File + ".obj");
    output << "#Alexandre Ramos - Output; Nº de Partes = " << nPartes << "\n";
    for (int i = 0; i<nPartes; i++){

        Objeto *Otemp = Objs.at(i);
        int nPontos = Otemp->points.size();
        int nFaces = Otemp->faces.size();

        output << "o P" << i+1 << "\n";

        for (int j = 0; j<nPontos; j++){
            Coord_3D *T = Otemp->points.at(j);
            output << "v " << T->x << " " << T->y << " " << T->z << "\n";
        }
        for (int j = 0; j < nFaces; j++){
            Face *F = Otemp->faces.at(j);
            output << "f " << F->P1+1 << " " << F->P2+1 << " " << F->P3+1 << "\n";
        }

    }
}

//Slots para funções da interface:


void GLWidget::Fecho(){
    for(vector<Objeto*>::iterator i = Objs.begin(); i!= Objs.end(); i++)
            (*i)->faces.clear();
Points = false;
for(vector<Objeto*>::iterator i = Objs.begin(); i!= Objs.end(); i++){
        (*i) = QuickHull((*i));
        updateGL();
        delay(velocidade);
    }
    attInfo();

    updateGL();
}
void GLWidget::FechoAnimado(){

    for(vector<Objeto*>::iterator i = Objs.begin(); i!= Objs.end(); i++)
        (*i)->faces.clear();

    for(vector<Objeto*>::iterator i = Objs.begin(); i!= Objs.end(); i++){
        QuickHull_Animado((*i),velocidade);
        delay(velocidade);
    }

    attInfo();
    updateGL();
}

void GLWidget::prox(){
    N++;
    if(N==22)
        N=0;
    File = ("Node"+to_string(N));
    Importar();
}
void GLWidget::ant(){
    N--;
    if(N==-1)
        N=21;
    File = ("Node"+to_string(N));
    Importar();
}

void GLWidget::Importar(){
    Objs.clear();
    Objs = ReadObjs(path+"/"+File+".obj");
    //cout << Info;
    Points = true;
    attInfo();
    updateGL();
}
void GLWidget::Exportar(){
    WriteObjs(Objs);}
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
void GLWidget::attArestas(bool b){
    Arestas = b;
    updateGL();
}

void GLWidget::attInfo(){

    int N = Objs.size();
    Info = (File +" -> Nº de Partes: "+ to_string(N));

    for(int i=0; i<N;i++){

        string S =("\n\n");

        Coord_3D C = Objs.at(i)->Centro();
        Coord_3D *mX, *MX, *mY, *MY, *mZ, *MZ;
        mX = Objs.at(i)->points.at(Objs.at(i)->MenorX());
        MX = Objs.at(i)->points.at(Objs.at(i)->MaiorX());
        mY = Objs.at(i)->points.at(Objs.at(i)->MenorY());
        MY = Objs.at(i)->points.at(Objs.at(i)->MaiorY());
        mZ = Objs.at(i)->points.at(Objs.at(i)->MenorZ());
        MZ = Objs.at(i)->points.at(Objs.at(i)->MaiorZ());

        S+= ("Informações Gerais P ("+to_string(i)+"): \nNº Pontos: " +to_string(Objs.at(i)->points.size()) + ", Nº Faces: " + to_string(Objs.at(i)->faces.size()) + "\n");
        S+= ("Centro = " + to_string(C.x) + ", " + to_string(C.y) + ", " + to_string(C.z) + "\n");
        S+= ("Extremos: \n");
        S+= ("Menor X = " + to_string(mX->x));
        S+= (", Menor Y = " + to_string(mY->y));
        S+= (", Menor Z = "+ to_string(mZ->z)+"\n");

        S+= ("Maior X = " + to_string(MX->x));
        S+= (", Maior Y = " + to_string(MY->y));
        S+= (", Maior Z = "+ to_string(MZ->z)+"\n");

        Objs.at(i)->calc_Esfera();
        float Volume = 4*PI*(Objs.at(i)->Esf.raio);
        S+= ("Esfera em que o objeto esteja inscrito: Raio: " + to_string(Objs.at(i)->Esf.raio)+ ", Volume: " + to_string(Volume));
        int NP = Objs.at(i)->points.size();
        int *pFecho = (int*)malloc(sizeof(int)*NP);
        int nPF = Pontos_Fecho(Objs.at(i),pFecho);

        if(nPF > 0){
            S+= ("\nÁrea externa = " + to_string(Objs.at(i)->Area_Externa()));
            S+= ("\nVolume = " + to_string(Objs.at(i)->Volume()));
            S+= ("\nPontos pertencentes ao Fecho ("+ to_string(nPF) +") = \n");
            for(int i =0; i<nPF;i++)
                S+= (to_string(pFecho[i])+" ");
            S+= ("\n");




        }
        Info+=S;
    }

    QString T = QString::fromStdString(Info);
    I->setText(T);
}

void GLWidget::New_X(double n){
    this->nx = n;
}
void GLWidget::New_Y(double n){
    this->ny = n;
}
void GLWidget::New_Z(double n){
    this->nz = n;
}
void GLWidget::Part_Ref(int n){
    this->nP = n;
}

void GLWidget::Add(){
    int N = Objs.size();
    if(N > nP){
        Objs.at(nP)->addPoint(nx,ny,nz);
        if(Objs.at(nP)->faces.size()>0)
            Fecho();
        updateGL();
    }
}
void GLWidget::attVelocidade(int x){
    this->velocidade = x;
}
void GLWidget::attFile(QString s){
    this->File = s.toUtf8().constData();

}
void GLWidget::attPath(QString s){
    this->path = s.toUtf8().constData(); //s.toUtf8().constData();

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
