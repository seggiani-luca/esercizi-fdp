//
// scrivere un programma che concatena vettori (si assume che il chiamante allochi le risorse necessarie)
//
#include <iostream>
using namespace std;

void concatena(const int* v1, const int* v2, int l1, int l2, int* v3) {
    for(int i = 0; i < l1; i++) {
        *(v3+i) = *(v1+i);
    }
    for(int i = 0; i< l2; i++) {
        *(v3+l1+i) = *(v2+i);
    }
}

void stampaVettore(int* vett, int l) {
    cout << "Vettore: ";
    for(int i = 0; i < l; i++) {
        cout << *(vett+i) << " ";
    }
    cout << endl;
}

int main() {
    //dichiarazione vettori
    int l1 = 5;
    int l2 = 3;
    int v1[l1] = {1, 2, 3, 6, 8};
    int v2[l2] = {2, 9, 4};
    int v3[l1+l2];
    //fine dichiarazione vettori
    concatena(v1, v2, l1, l2, v3);
    stampaVettore(v3, l1+l2);
    return 0;
}