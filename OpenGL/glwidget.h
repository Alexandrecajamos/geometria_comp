#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include "objeto.h"
#include "quickhull3d.h"

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
    void QuickHull_Recursivo_Animado(Objeto *Pol, int iA, int iB, int iC, bool *validos, bool *Fecho, int velocidade);
    void QuickHull_Animado(Objeto* Pol, int velocidade);
    void PintaFaces(Objeto* Pol);
    int velocidade = 50;
    float Ex=50, Ey=50, Ez=50;
    float Lox=0, Loy=0, Loz=0;
    float Avx=0, Avy=10, Avz=0;
    Objeto* Obj = new Objeto();
    bool RendFecho = false;

signals:

public slots:
    void attVelocidade(int);
    void Fecho();
    void FechoAnimado();
    //void ImpPontos();
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
