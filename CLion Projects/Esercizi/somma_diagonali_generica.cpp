//
// riscrivere somma_diagonali in modo che accetti qualsiasi matrice
//
#include <iostream>
using namespace std;

inline int index(int x, int y, int dim) {
    return x + y * dim;
}

void leggiMatrice(int dim, int* matr) {
    for(int x = 0; x < dim; x++) {
        for(int y = 0; y < dim; y++) {
            cin >> *(matr+index(x,y,dim));
        }
    }
}

void stampaMatrice(int dim, int* matr) {
    for(int x = 0; x < dim; x++) {
        for(int y = 0; y < dim; y++) {
            cout << *(matr+index(x,y,dim)) << " ";
        }
        cout << endl;
    }
}

int sommaDiag(int dim, int* matr) {
    int conto = 0;
    for(int x = 0; x < dim; x++) {
        for(int y = 0; y < dim; y++) {
            if(x==y) { //diagonale 1
                conto += *(matr+index(x,y,dim));
            }
            if((x + y == dim-1) & (x != y)) { //diagonale 2
                conto += *(matr+index(x,y,dim));
            }
        }
    }
    return conto;
}

int main() {
    int dim;
    cout << "Inserisci la dimensione della matrice" << endl;
    cin >> dim;
    int matr[dim*dim];
    cout << "Inserisci i " << dim*dim << " elementi della matrice:" << endl;
    leggiMatrice(dim, matr);
    stampaMatrice(dim, matr);
    cout << "La somma delle diagonali e': ";
    cout << sommaDiag(dim, matr);
    return 0;
}