//
// scrivere un programma che ricava la trasposta di una matrice
//
#include <iostream>
using namespace std;

const int DIM = 3;

inline int index(int x, int y, int dim) {
    return x + y * dim;
}

void leggiMatrice(const int dim, int* matr) {
    for(int x = 0; x < dim; x++) {
        for(int y = 0; y < dim; y++) {
            cin >> *(matr+index(x,y,dim));
        }
    }
}

void stampaMatrice(const int dim, const int* matr) {
    for(int x = 0; x < dim; x++) {
        for(int y = 0; y < dim; y++) {
            cout << *(matr+index(x,y,dim)) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int* trasposta(const int dim, const int* matr) {
    int* trasp = new int[dim*dim];
    for(int y = 0; y < dim; y++) {
        for(int x = 0; x < dim; x++) {
            trasp[index(x,y,dim)] = matr[index(y,x,dim)];
        }
    }
    return trasp;
}

int main() {
    int matr[DIM*DIM];
    cout << "Inserisci i 9 elementi della matrice: " << endl;
    leggiMatrice(DIM, matr);
    stampaMatrice(DIM, matr);

    int* trasp = trasposta(DIM, matr);
    cout << "La trasposta e'" << endl;
    stampaMatrice(DIM, trasp);
    return 0;
}
