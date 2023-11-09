//
// scrivere un programma che calcola la somma delle diagonali di una matrice
//
#include <iostream>
using namespace std;

const int DIM = 3;

void leggiMatrice(int matr[][DIM]) {
    for(int x = 0; x < DIM; x++) {
        for(int y = 0; y < DIM; y++) {
            cin >> matr[x][y];
        }
    }
}

void stampaMatrice(const int matr[][DIM]) {
    for(int x = 0; x < DIM; x++) {
        for(int y = 0; y < DIM; y++) {
            cout << matr[x][y] << " ";
        }
        cout << endl;
    }
}

int sommaDiag(const int matr[][DIM]) {
    int conto = 0;
    for(int x = 0; x < DIM; x++) {
        for(int y = 0; y < DIM; y++) {
            if(x==y) { //diagonale 1
                conto += matr[x][y];
            }
            if((x + y == DIM-1) & (x != y)) { //diagonale 2
                conto += matr[x][y];
            }
        }
    }
    return conto;
}

int main() {
    int matr[DIM][DIM];
    cout << "Inserisci i 9 elementi della matrice:" << endl;
    leggiMatrice(matr);
    stampaMatrice(matr);
    cout << "La somma delle diagonali e': ";
    cout << sommaDiag(matr);
    return 0;
}