//
// scrivere un programma che individua le componenti negative di un vettore e le alloca sull'heap
//
#include <iostream>
using namespace std;

const int DIM = 6;

void stampa_vettore(const int* vett, const int l) {
    for(int i = 0; i < l; i++) {
        cout << *(vett + i) << " ";
    }
    cout << endl;
}

int* componenti_negative(int* vett, const int dim, int& newDim) {
    int conto = 0;
    for(int i = 0; i < dim; i++) {
        if(*(vett+i) < 0)
            conto++;
    }
    int* newVett = new int[conto];
    newDim = conto;
    conto = 0;
    for(int i = 0; i < dim; i++) {
        if(*(vett+i) < 0) {
            *(newVett + conto) = *(vett + i);
            conto++;
        }
    }
    return newVett;
}

int main() {
    int vett[] = {11, -22, 4, -3, 18, -1};
    cout << "Vettore di partenza (con componenti sia positive che negative):" << endl;
    stampa_vettore(vett, DIM);

    int newDim = 0;
    int* vettNeg = componenti_negative(vett, DIM, newDim);
    cout << "Ecco il nuovo vettore (solo componenti negative):" << endl;
    stampa_vettore(vettNeg, newDim);
    cout << "Dealloco il vettore sull'heap..." << endl;
    delete[] vettNeg;
    return 0;
}