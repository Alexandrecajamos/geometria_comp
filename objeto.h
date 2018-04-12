#ifndef OBJETO_H
#define OBJETO_H

#include<vector>
#include "stdio.h"
#include "coord_3d.h"
#include "triangulo.h"
#include "esfera.h"
#include <fstream>
#include "transformacoes.h"


#define TAM 4

class Objeto
{
public:
    Objeto();

    void addPoint(float x, float y, float z);
    void addFace(int iP1, int iP2, int iP3);
    float Ray_intersept(Coord_3D Po, Coord_3D Dir, int *iFace);
    bool Tiro(Coord_3D Ponto);
    void calc_Esfera();
    void Transforoma(float A[TAM][TAM]);
    void ImpPoints();
    bool Obstaculo(Coord_3D Pint, Coord_3D l);
    void Libera();
    void Ordena(int eixo);

    int MaiorX();//Retorna Indice
    int MenorX();//Retorna Indice
    int MaiorY();//Retorna Indice
    int MenorY();//Retorna Indice
    int MaiorZ();//Retorna Indice
    int MenorZ();//Retorna Indice


    Esfera Esf;

    std::vector<Coord_3D*> points;
    std::vector<triangulo*> faces;

};

#endif // OBJETO_H
