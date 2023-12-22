//
// scrivere una funzione che restituisca il primo pari fra tre valori
//
#include <iostream>
using namespace std;

bool pari(int a, int b, int c, int& ritorno) {
    if(a%2 == 0) {
        ritorno = a;
        return true;
    }
    if(b%2 == 0) {
        ritorno = b;
        return true;
    }
    if(c%2 == 0) {
        ritorno = c;
        return true;
    }
    return false;
}

int main() {
    int a, b, c;
    cout << "Inserisci tre valori: " << endl;
    cin >> a >> b >> c;

    int ritorno;
    if(pari(a, b, c, ritorno)) {
        cout << "Il primo valore pari e' " << ritorno;
    } else {
        cout << "Non sono stati inseriti valori pari." << endl;
    }
    return 0;
}