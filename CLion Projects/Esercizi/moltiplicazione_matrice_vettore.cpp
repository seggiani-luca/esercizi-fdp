//
// scrivere un programma che implementa la moltiplicazione fra matrice e vettore
//
#include <iostream>
using namespace std;

const int dimY = 3;
const int dimX = 3;

void leggiMatrice(double** matr) {
    for(int y = 0; y < dimY; y++) {
        for(int x = 0; x < dimX; x++) {
            cin >> matr[y][x];
        }
    }
}

void stampaMatrice(double** const matr) {
    for(int y = 0; y < dimY; y++) {
        for(int x = 0; x < dimX; x++) {
            cout << matr[y][x] << " ";
        }
        cout << endl;
    }
}

void leggiVettore(double* const vett) {
    for(int i = 0; i < dimX; i++) {
        cin >> vett[i];
    }
}

void stampaVettore(double* const vett, int dim) {
    for(int i = 0; i < dim; i++) {
        cout << vett[i] << " ";
    }
    cout << endl;
}

double* mulMatVect(double** const matr, const double* vett) {
    double* prod = new double [dimY];
    for(int i = 0; i < dimY; i++) {
        double conto = 0;
        const double* riga = *(matr + i);
        for(int j = 0; j < dimX; j++) {
            conto += *(riga + j) * *(vett + j);
        }
        *(prod + i) = conto;
    }
    return prod;
}

int main() {

    double** matr = new double* [dimY];
    for(int i = 0; i < dimY; i++) {
        *(matr+i) = new double [dimX];
    }
    double vett[dimX];

    cout << "Inserisci i " << dimX * dimY << " elementi della matrice: " << endl;
    leggiMatrice(matr);
    stampaMatrice(matr);

    cout << "Inserisci i " << dimX << " elementi del vettore: " << endl;
    leggiVettore(vett);
    stampaVettore(vett, dimX);

    double* prod = mulMatVect(matr, vett);
    cout << "Il prodotto fra matrice e vettore e': ";
    stampaVettore(prod, dimY);
    cout << endl;

    for(int i = 0; i < dimY; i++) {
        delete[] *(matr+i);
    }
    delete[] matr;
    delete[] prod;
    return 0;
}
