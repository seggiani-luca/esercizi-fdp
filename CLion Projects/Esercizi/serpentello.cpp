//
// coffee break: scrivere un programma che stampa un "serpente" di numeri
//
#include <iostream>
using namespace std;

inline int index(int x, int y, int dim) {
    return x + y * dim;
}

int* creaSerpente(int dimX, int dimY) {
    int* serpente = new int [dimX*dimY];
    for(int y = 0; y < dimY; y++) {
        bool pari;
        pari = (y%2==0) ? true : false;
        if(pari) {
            for(int i = 0; i < dimX; i++) {
                serpente[index(i,y, dimX)] = i + dimX * y + 1;
            }
        } else {
            for(int i = 0; i < dimX; i++) {
                serpente[index(dimX - 1 - i,y, dimX)] = i + dimX * y + 1;
            }
        }
    }
    return serpente;
}

int main() {
    int dimX;
    cout << "Inserisci la dimensione x" << endl;
    cin >> dimX;
    int dimY;
    cout << "Inserisci la dimensione y" << endl;
    cin >> dimY;

    int* serpente = creaSerpente(dimX, dimY);

    //stampo qui, perlopiù per pigrizia...
    for(int y = 0; y < dimY; y++) {
        for(int x = 0; x < dimX; x++) {
            cout << serpente[index(x,y,dimX)] << "\t";
        }
        cout << endl;
    }
    delete[] serpente;
    serpente = nullptr;
    return 0;
}
