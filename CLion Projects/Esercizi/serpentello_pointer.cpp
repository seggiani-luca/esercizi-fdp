//
// riscrivere serpentello utilizzando un pointer a pointer
//
#include <iostream>
using namespace std;

int** creaSerpente(int dimX, int dimY) {
    int** serpente = new int* [dimY];
    for(int i = 0; i < dimY; i++) {
        *(serpente + i) = new int [dimX];
    }
    for(int y = 0; y < dimY; y++) {
        bool pari;
        pari = (y%2==0) ? true : false;
        if(pari) {
            for(int i = 0; i < dimX; i++) {
                serpente[y][i] = i + dimX * y + 1;
            }
        } else {
            for(int i = 0; i < dimX; i++) {
                serpente[y][dimX-1-i] = i + dimX * y + 1;
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

    int** serpente = creaSerpente(dimX, dimY);

    //stampo qui, perlopiù per pigrizia...
    for(int y = 0; y < dimY; y++) {
        for(int x = 0; x < dimX; x++) {
            cout << serpente[y][x] << "\t";
        }
        cout << endl;
    }
    for(int i = 0; i < dimY; i++)
        delete[] *(serpente + i);
    delete[] serpente;
    serpente = nullptr;
    return 0;
}