//
// scrivere un programma che studia il comportamento di puntatori e null pointer
//
#include <iostream>
using namespace std;

void func(int*& p) { //uso un riferimento a puntatore
    p = 0;
}

int main() {
    int* p;
    cout << "Puntatore non inizializzato: " << p << endl;

    int a = 5;
    p = &a;
    cout << "Puntatore assegnato ad a: " << p << endl;
    cout << "Valore di a: " << a << endl;

    func(p);

    cout << "Puntatore assegnato a NULL: " << p;

    return 0;
}
