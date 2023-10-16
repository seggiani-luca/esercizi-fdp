//
// scrivere un programma che determina se un carattere è maisucolo, minuscolo o cifra
//
#include <iostream>
using namespace std;

int main() {

    char a;
    cout << "Inserisci un carattere: " << endl;
    cin >> a;

    if(a>=65&a<=90) {
        cout << "lettera maiuscola";
        return 0;
    }

    if(a>=97&a<=122) {
        cout << "lettera minuscola";
        return 0;
    }

    if(a>=48&a<=57) {
        cout << "cifra decimale";
        return 0;
    }

    return 0;

}