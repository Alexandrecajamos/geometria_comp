#ifndef ORDMATRIZ_H
#define ORDMATRIZ_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include <ctime>

//QuickSort para ordenar matriz considerando o valor de 1 coluna. Sendo ind o índice da coluna a partir da qual se dá a ordenação e N_Colluns o número de colunas da matriz

void trocarM(float* x, float* y, int N);
int Particione_originalM(float** vetor, int p, int r, int ind, int N_Colluns);
int Particione_aleatM(float** vetor, int p, int r, int ind, int N_Colluns);
void QuickSortM(float** vetor, int p, int r, int ind, int N_Colluns);


#endif // ORDMATRIZ_H
