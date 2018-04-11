#ifndef POLIGONO_H
#define POLIGONO_H
#include "vector"
#include "vetor.h"


class Poligono
{
public:

    Poligono();
    std::vector<Coord_2D*> points;
    void addPoint(float x, float y);
    Coord_2D Centro();
    float Area();
    int MaiorX();//Retorna Indice
    int MenorX();//Retorna Indice
    int MaiorY();//Retorna Indice
    int MenorY();//Retorna Indice
    void Imp();
    void Ordena(bool controle);


};

#endif // POLIGONO_H
