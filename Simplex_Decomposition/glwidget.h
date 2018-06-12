#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include "objeto.h"
#include "QTextBrowser"

class GLWidget : public QGLWidget
{
    Q_OBJECT
    QTimer* timer;
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void PintaFace(int iA, int iB,int iC, Objeto* Pol);
    void PintaSimplex(int a, int b, int c, int d, Objeto* Pol);
    void PintaPontos(Objeto* Pol);

    void PintaFaces(Objeto* Pol);
    void PAllSimplex(Objeto* Pol);
    int Current_Simplex = 0;


    vector<Objeto*> ReadObjs (std::string filepath);
    void WriteObjs(vector<Objeto*> Objs);

    int velocidade = 50;
    float Ex=50, Ey=50, Ez=50;
    float Lox=0, Loy=0, Loz=0;
    float Avx=0, Avy=10, Avz=0;

    float nx =0, ny=0, nz=0;
    int nP = 0;

    vector<Objeto*> Objs;

    Objeto* Obj = new Objeto();
    bool Arestas = false;
    bool RendFecho = false;
    bool Points = true;
    int N = 0;
    QTextBrowser *I;
    string Info = "";
    string path = "/home/alexandre/geometria_comp/Simplex_Decomposition/data";
    string File = "cubo";
    Coord_3D C_Obj;

signals:

public slots:

    void PSimplex();
    void ASimplex();

    void GetSimplex();
    void attArestas(bool);
    void attInfo();
    void attVelocidade(int);
    void attPath(QString);
    void attFile(QString);
    void Importar();
    void Exportar();
    void Video();

    //void ImpPontos();
    void New_X(double);
    void New_Y(double);
    void New_Z(double);
    void Part_Ref(int);
    void Add();

    void Eye_X(double);
    void Eye_Y(double);
    void Eye_Z(double);
    void Lo_X(double);
    void Lo_Y(double);
    void Lo_Z(double);
    void Av_X(double);
    void Av_Y(double);
    void Av_Z(double);

};

#endif // GLWIDGET_H
