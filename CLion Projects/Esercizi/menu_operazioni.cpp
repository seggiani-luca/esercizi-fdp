//
// scrivere un programma che implementi un menu via switch
//
#include <iostream>
using namespace std;

struct Numeri { int a, b, c; };

Numeri chiedi_numeri() {
    Numeri numeri;
    cout << "Inserisci tre numeri" << endl;
    cin >> numeri.a;
    cin >> numeri.b;
    cin >> numeri.c;
    return numeri;
}

void minimo() {
    Numeri numeri = chiedi_numeri();
    int t = numeri.a;
    if(numeri.b < t)
        t = numeri.b;
    if(numeri.c < t)
        t = numeri.c;
    cout << "Stampo il minimo: " << t << endl;
}

void massimo() {
    Numeri numeri = chiedi_numeri();
    int t = numeri.a;
    if(numeri.b > t)
        t = numeri.b;
    if(numeri.c > t)
        t = numeri.c;
    cout << "Stampo il massimo: " << t << endl;
}

void media() {
    Numeri numeri = chiedi_numeri();
    double media = (numeri.a + numeri.b + numeri.c) / 3;
    cout << "Stampo la media: " << media << endl;
}

int main() {

    while(true) {
        cout << "Menu operazioni" << endl;
        cout << "1: minimo di tre interi" << endl;
        cout << "2: massimo di tre interi" << endl;
        cout << "3: media di tre interi" << endl;
        cout << "0: esci" << endl;

        int scelta;
        cout << endl << "Scelta? " << endl;
        cin >> scelta;

        if((scelta < 0)|(scelta > 3)) {
            scelta = 0;
        }

        switch(scelta) {
            case 0:
                exit(0);
                break;
            case 1:
                minimo();
                break;
            case 2:
                massimo();
                break;
            case 3:
                media();
                break;
        }
    }

    return 0;
}