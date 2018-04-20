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

    void trocar(int i, int j);
    int Particione_X(int p, int r);
    int Particione_Y(int p, int r);
    int Particione_Z(int p, int r);
    int Particione_aleat(int p, int r, bool eixo);
    void QuickSort(int p, int r, bool eixo);
    bool IndRotacao(Coord_2D P);

};

#endif // POLIGONO_H
