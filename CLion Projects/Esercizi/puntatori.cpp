//
// scrivere un programma che chieda un numero e lo: 1) quadri se e' multiplo di 2; 2) cubi se e' multiplo di 3; 3) restituisca se non soddisfa gli altri casi
//
#include <iostream>
using namespace std;

int pow(int base, int exp) {
    int orig = base;
    if(exp == 0)
        return 1;
    for(int i = 1; i < exp; i++) {
        base *= orig;
    }
    return base;
}

void f(int* p) {

    cout << "Puntatore in f: " << p << endl;

    if(*p == 69) {
        cout << "Marco e' frocio" << endl;
        exit(0);
    }
    if((*p % 2) == 0) {
        *p = pow(*p, 2);
        return;
    }
    if((*p % 3) == 0) {
        *p = pow(*p, 3);
        return;
    }
}

int main() {
    int valore;
    cout << "Numero? " << endl;
    cin >> valore;

    cout << "L'indirizzo in memoria e': " << &valore << endl;
    f(&valore);

    cout << "Il valore e' " << valore;
    return 0;
}