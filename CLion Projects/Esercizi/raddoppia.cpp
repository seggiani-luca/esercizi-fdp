//
// scrivere un programma che raddoppia un'int attraverso i riferimenti
//
#include <iostream>
using namespace std;

void raddoppia(int& valore);

int main() {

    int valore;
    cout << "Numero?" << endl;
    cin >> valore;

    raddoppia(valore);

    cout << "Nuovo valore di n: " << valore;
    return 0;
}

void raddoppia(int& valore) {
    cout << "Dentro raddoppia(): Indirizzo di a: " << &valore << endl;
    cout << "Dentro raddoppia(): a: " << valore << endl;
    valore *= 2;
    cout << "Dentro raddoppia(): a: " << valore << endl;
}