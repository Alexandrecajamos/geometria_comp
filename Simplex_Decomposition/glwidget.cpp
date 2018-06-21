#include "glwidget.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <time.h>
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
    glVertex3f(Pol->points.at(iA-1)->x,Pol->points.at(iA-1)->y,Pol->points.at(iA-1)->z);
    glVertex3f(Pol->points.at(iB-1)->x,Pol->points.at(iB-1)->y,Pol->points.at(iB-1)->z);
    glVertex3f(Pol->points.at(iC-1)->x,Pol->points.at(iC-1)->y,Pol->points.at(iC-1)->z);
    glEnd();

}
void GLWidget::PintaSimplex(int iA, int iB, int iC, int iD, Objeto *Pol){

    PintaFace(iA,iC,iB, Pol);
    PintaFace(iA,iB,iD, Pol);
    PintaFace(iB,iC,iD, Pol);
    PintaFace(iC,iA,iD, Pol);

}

void GLWidget::PintaFaces(Objeto* Pol){
    for(std::vector<Face*>::iterator i = Pol->faces.begin(); i!= Pol->faces.end(); i++){
        PintaFace((*i)->P1,(*i)->P2,(*i)->P3,Pol);

    }
}
void GLWidget::PAllSimplex(Objeto *Pol){

    glLoadIdentity();
    gluLookAt(Ex,Ey,Ez,Lox,Loy,Loz,Avx,Avy,Avz);

    int nS = Current_Simplex;
    for(int i=0; i<nS;i++){
        Simplex *sT = Pol->simplex.at(i);
        Objeto *T = new Objeto();
        T->addPoint(Pol->points.at(sT->A)->x,Pol->points.at(sT->A)->y, Pol->points.at(sT->A)->z);
        T->addPoint(Pol->points.at(sT->B)->x,Pol->points.at(sT->B)->y, Pol->points.at(sT->B)->z);
        T->addPoint(Pol->points.at(sT->C)->x,Pol->points.at(sT->C)->y, Pol->points.at(sT->C)->z);
        T->addPoint(Pol->points.at(sT->D)->x,Pol->points.at(sT->D)->y, Pol->points.at(sT->D)->z);

        T->addFace(0,1,3);
        T->addFace(1,2,3);
        T->addFace(2,0,3);
        T->addFace(0,2,1);

        PintaFaces(T);

//        T->addPoint();

//        PintaSimplex(Pol->simplex.at(i)->A,Pol->simplex.at(i)->B,Pol->simplex.at(i)->C,Pol->simplex.at(i)->D,Pol);
    }
}

void GLWidget::Expandir_Simplex(Objeto *Pol, float Fator, int Eixo){

    int nS = Current_Simplex;
    glLoadIdentity();
    for(int i=0; i<nS;i++){
        glLoadIdentity();

        gluLookAt(Ex,Ey,Ez,Lox,Loy,Loz,Avx,Avy,Avz);


        Simplex *sT = Pol->simplex.at(i);
        Objeto *T = new Objeto();

        T->addPoint(Pol->points.at(sT->A)->x,Pol->points.at(sT->A)->y, Pol->points.at(sT->A)->z);
        T->addPoint(Pol->points.at(sT->B)->x,Pol->points.at(sT->B)->y, Pol->points.at(sT->B)->z);
        T->addPoint(Pol->points.at(sT->C)->x,Pol->points.at(sT->C)->y, Pol->points.at(sT->C)->z);
        T->addPoint(Pol->points.at(sT->D)->x,Pol->points.at(sT->D)->y, Pol->points.at(sT->D)->z);

        T->addFace(0,1,3);
        T->addFace(1,2,3);
        T->addFace(2,0,3);
        T->addFace(0,2,1);

        Coord_3D cT = T->Centro();
//        cT.operator -=(&c);

        if(Eixo == 0)
            glTranslated((cT.x-Lox) * Fator, 1, 1);
        if(Eixo == 1)
            glTranslated(1, (cT.y-Loy) * Fator, 1);
        if(Eixo == 2)
            glTranslated(1, 1, (cT.z-Loz) * Fator);
        if(Eixo == 3)
            glTranslated((cT.x-Lox) * Fator, (cT.y-Loy)*Fator, (cT.z-Loz) * Fator);


        PintaFaces(T);

//        T->addPoint();

//        PintaSimplex(Pol->simplex.at(i)->A,Pol->simplex.at(i)->B,Pol->simplex.at(i)->C,Pol->simplex.at(i)->D,Pol);
    }

}

//void GLWidget::PAllSimplex(Objeto *Pol){
//    int nS = Current_Simplex;
//    for(int i=0; i<nS;i++){

//        PintaSimplex(Pol->simplex.at(i)->A,Pol->simplex.at(i)->B,Pol->simplex.at(i)->C,Pol->simplex.at(i)->D,Pol);
//    }
//}
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

//        GetSimplex();
//        C_Obj = Objs.at(0)->Centro();

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
//        if((*i)->simplex.size() == 0)
//        PintaFaces((*i));

        if(expandir)
            Expandir_Simplex((*i), Fator_Exp, Eixo);
        else{
            PAllSimplex((*i));
            PintaPontos((*i));
        }
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
    string identifier, x, y, z,alfa, line;

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
//        int nFaces = Otemp->faces.size();
        int nSimplex = Otemp->simplex.size();
        output << "o P" << i+1 << "\n";

        for (int j = 0; j<nPontos; j++){
            Coord_3D *T = Otemp->points.at(j);
            output << "v " << T->x << " " << T->y << " " << T->z << "\n";
        }
        for(int j=0; j< nSimplex; j++){
            Simplex *S = Otemp->simplex.at(j);
            output << "f " << S->A+1 << " " << S->B+1 << " " << S->D+1 << "\n";
            output << "f " << S->B+1 << " " << S->C+1 << " " << S->D+1 << "\n";
            output << "f " << S->C+1 << " " << S->A+1 << " " << S->D+1 << "\n";
            output << "f " << S->A+1 << " " << S->C+1 << " " << S->B+1 << "\n";
        }


//        for (int j = 0; j < nFaces; j++){
//            Face *F = Otemp->faces.at(j);
//            output << "f " << F->P1 << " " << F->P2 << " " << F->P3 << "\n";
//        }

    }
}

//Slots para funções da interface:
void GLWidget::GetSimplex(){
    Objs.at(0)->simplex.clear();
    Triangulacao(Objs.at(0),Ebusca, addPonto, Limite);
    Current_Simplex = Objs.at(0)->simplex.size();
    attInfo();
    updateGL();
    cout << "FIm T" << endl;
}
void GLWidget::ASimplex(){
    int L = Objs.at(0)->simplex.size();
    Current_Simplex--;
    if(Current_Simplex < 0)
        Current_Simplex = L;
    updateGL();
}
void GLWidget::PSimplex(){
    int L = Objs.at(0)->simplex.size();
    Current_Simplex++;
    if(Current_Simplex > L)
        Current_Simplex = 0;
    updateGL();
}


void GLWidget::Importar(){
    Objs.clear();

    Objs = ReadObjs(path+"/"+File+".obj");
    Points = true;
    attInfo();
    if(Objs.size()>0){
        Coord_3D c = Objs.at(0)->Centro();
        Lox = c.x, Loy = c.y, Loz = c.z;
        Current_Simplex=0;
    }

    updateGL();
}
void GLWidget::Exportar(){
    WriteObjs(Objs);}
void GLWidget::Video(){
    float x = 2*PI;

    Coord_3D PO(Ex,Ey,Ez);
    Coord_3D LA(Lox, Loy, Loz);
    float R = Distancia3D(PO,LA);

    float a1 = Ex, a2 = Ez;

    for(float i=100; i>=1; i--){
        float y = (i/100);
        delay(velocidade/5);
        Ex=cos(x*y)*R + Lox;
        Ez=-sin(x*y)*R + Loz;
        updateGL();
    }
    Ex = a1;
    Ez = a2;
    updateGL();
}

void GLWidget::F(){
    float x = 2*PI;
    float a1 = Ex, a2 = Ez;
    Coord_3D PO(Ex,Ey,Ez);
    Coord_3D LA(Lox, Loy, Loz);
    float R = Distancia3D(PO,LA);

    RY--;

    if(RY<0) RY=20;

    float y = RY/20;
    Ex= (cos(x*y)*R)+Lox;
    Ez= (-sin(x*y)*R)+Loz;

    updateGL();
    Ex=a1;
    Ez=a2;

}
void GLWidget::T(){
    float x = 2*PI;
    float a1 = Ex, a2 = Ez;
    Coord_3D PO(Ex,Ey,Ez);
    Coord_3D LA(Lox, Loy, Loz);
    float R = Distancia3D(PO,LA);

    RY++;
    if(RY >= 20) RY=0;

    float y = RY/20;
    Ex= (cos(x*y)*R)+Lox;
    Ez= (-sin(x*y)*R)+Loz;

    updateGL();
    Ex=a1;
    Ez=a2;
}


void GLWidget::attArestas(bool b){
    Arestas = b;
    updateGL();
}
void GLWidget::ADDPonto(bool b){
    addPonto = b;
}

void GLWidget::attLim(int i){
    Limite = i;
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

        S+= ("Informações Gerais P ("+to_string(i)+"): \nNº Pontos: " +to_string(Objs.at(i)->points.size()) + ", Nº Simplex: " + to_string(Objs.at(i)->simplex.size()) + "\n");
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
//        int NP = Objs.at(i)->points.size();
//        int *pFecho = (int*)malloc(sizeof(int)*NP);
//        int nPF = Pontos_Fecho(Objs.at(i),pFecho);

//        if(nPF > 0){
//            S+= ("\nÁrea externa = " + to_string(Objs.at(i)->Area_Externa()));
//            S+= ("\nVolume = " + to_string(Objs.at(i)->Volume()));
//            S+= ("\nPontos pertencentes ao Fecho ("+ to_string(nPF) +") = \n");
//            for(int i =0; i<nPF;i++)
//                S+= (to_string(pFecho[i])+" ");
//            S+= ("\n");




//        }
        Info+=S;
    }

    QString T = QString::fromStdString(Info);
    I->setText(T);
}
void GLWidget::EBusca(bool b){
    Ebusca=b;
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
//        if(Objs.at(nP)->faces.size()>0)
//            Fecho();
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

void GLWidget::attEixo(int e){
    Eixo = e;
}
void GLWidget::attFator(double f){
    Fator_Exp = f;
}
void GLWidget::Expandir(){
    if(expandir)
        expandir = false;
    else
        expandir = true;
    updateGL();
}

