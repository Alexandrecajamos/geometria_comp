#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include "objeto.h"
#include "quickhull3d.h"
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
    void PintaPontos(Objeto* Pol);

    void QuickHull_Recursivo_Animado(Objeto* Obj, int* Parte, int nP, int a, int b, int c, int velocidade);
    void QuickHull_Animado(Objeto* Pol, int velocidade);

    void PintaFaces(Objeto* Pol);

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

    bool RendFecho = false;

    QTextBrowser *I;
    string File = "cubo";
    string Info = "";


signals:

public slots:
    void attInfo();
    void attVelocidade(int);
    void attFile(QString);
    void Fecho();
    void FechoAnimado();
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
