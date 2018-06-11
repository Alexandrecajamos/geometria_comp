#ifndef ORDENACAO_H
#define ORDENACAO_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include <ctime>

using namespace std;


void trocar(double& x, double& y) {double z = x; x = y; y = z;}

int Particione_original(double* vetor, int p, int r) {
    double pivo = vetor[r];
    int i=p-1;
    for (int j=p; j<r; j++) {
        if (vetor[j] <= pivo) {
            i++;
            trocar(vetor[i], vetor[j]);
        }
    }
    trocar(vetor[i+1], vetor[r]);
    return i+1;
}
int Particione_aleat(double* vetor, int p, int r) {
    srand (time(NULL));
    int pos_pivo = p + rand()%(r-p+1);
    trocar(vetor[pos_pivo], vetor[r]);
    return Particione_original(vetor,p,r);
}
void QuickSort(double* vetor, int p, int r) {
    if (p>=r) return;
    int q = Particione_aleat(vetor,p,r);
    QuickSort(vetor,p,q-1);
    QuickSort(vetor,q+1,r);
}

void InsertionSort(double* vetor, int p, int r) {
    int i,j; double carta;
    for (j=p+1;j<=r;j++) {
        carta = vetor[j];
        i = j-1;
        while ((i>=p)&&(vetor[i]>carta)) {
            vetor[i+1] = vetor[i];
            i--;
        }
        vetor[i+1] = carta;
    }
}
void Merge(double* vetor, int p, int q, int r) {
    int infinito = INT_MAX;
    int N1 = q-p+1;
    int N2 = r-q;
    double* esq = new double[N1+1];
    double* dir = new double[N2+1];
    for (int i=0; i<N1; i++) esq[i]=vetor[p+i];
    for (int j=0; j<N2; j++) dir[j]=vetor[q+j+1];
    esq[N1] = infinito;
    dir[N2] = infinito;

    int i=0;
    int j=0;
    for (int k=p; k<=r; k++) {
        if (esq[i]<=dir[j])
             vetor[k] = esq[i++];
        else vetor[k] = dir[j++];
    }
    delete[] esq;
    delete[] dir;
}
void MergeSort(double* vetor, int p, int r) {
    if (p>=r) return;
    int q = (p+r)/2;
    MergeSort(vetor,p,q);
    MergeSort(vetor,q+1,r);
    Merge(vetor,p,q,r);
}

#endif // ORDENACAO_H
