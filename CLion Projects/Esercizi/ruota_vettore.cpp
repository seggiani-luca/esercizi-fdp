//
// scrivere un programma che ruota vettori
//
#include <iostream>
using namespace std;

int MAX_NUM = 6;

void scambia(int* a, int* b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void inverti(int* vett, int l = MAX_NUM) {
    for(int i = 0; i < l / 2; i++) {
        scambia(vett+i, vett + l - i - 1);
    }
}

void ruotaVettore(int* vett, int passi) {
    passi %= MAX_NUM;
    if(passi < 0)
        passi = MAX_NUM + passi;
    cout << passi << endl;
    inverti(vett);
    inverti(vett, passi);
    inverti(vett + passi, MAX_NUM - passi);
}

int main() {
    int vett[MAX_NUM];
    cout << "Inserisci gli elementi del vettore: " << endl;
    for(int i = 0; i < MAX_NUM; i++) {
        cin >> *(vett+i);
    }
    int passi;
    cout << "Inserisci il numero dei passi di rotazione: " << endl;
    cin >> passi;

    ruotaVettore(vett, passi);

    cout << "Vettore ruotato: ";
    for(int i = 0; i < MAX_NUM; i++) {
        cout << *(vett+i) << " ";
    }
    cout << endl;
    return 0;
}
