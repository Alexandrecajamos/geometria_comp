#include "ordmatriz.h"

void trocarM(float* x, float* y, int N) {
    float* z = (float*)malloc(sizeof(float)*N);
    for(int i = 0; i<N;i++){
        z[i] = x[i];
        x[i] = y[i];
        y[i] = z[i];
    }
    free(z);
}
int Particione_originalM(float** vetor, int p, int r, int ind, int N_Colluns) {
    int i=p-1;
    for (int j=p; j<r; j++) {
        if (vetor[j][ind] <= vetor[r][ind]) {
            i++;
            trocarM(vetor[i], vetor[j],N_Colluns);
        }
    }
    trocarM(vetor[i+1], vetor[r], N_Colluns);
    return i+1;
}
int Particione_aleatM(float** vetor, int p, int r, int ind, int N_Colluns) {
    srand (time(NULL));
    int pos_pivo = p + rand()%(r-p+1);
    trocarM(vetor[pos_pivo], vetor[r],N_Colluns);
    return Particione_originalM(vetor,p,r,ind, N_Colluns);
}
void QuickSortM(float** vetor, int p, int r, int ind, int N_Colluns) {
    if (p>=r) return;
    int q = Particione_aleatM(vetor,p,r, ind, N_Colluns);
    QuickSortM(vetor,p,q-1, ind, N_Colluns);
    QuickSortM(vetor,q+1,r, ind, N_Colluns);
}
