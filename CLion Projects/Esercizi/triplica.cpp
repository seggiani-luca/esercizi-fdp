//
// scrivere un programma che triplica un numero
//
#include <iostream>
using namespace std;

void triplica(double *p) {
    (*p) *= 3;
}

int main() {
    double a;
    cout << "Numero? " << endl;
    cin >> a;

    triplica(&a);
    cout << "Il valore triplicato e' " << a;
}