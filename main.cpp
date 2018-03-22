#include <iostream>
#include "coord_3d.h"
#include "coord_2d.h"
#include "ordenacao.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    int N = 10000;
    double* vetor = new double [N];
    srand(time(NULL));

    for (int i = 0; i<N; i++){
        vetor[i] = rand() % 100000;
        //cout << "|" << vetor[i] << "|";
    }
    cout << endl <<endl<<endl<<endl;

    InsertionSort(vetor, 0, N - 1);


    for (int i = 0; i<N; i++){
        cout << "|" << vetor[i] << "|";
    }
    cout << endl;


    return 0;
}
