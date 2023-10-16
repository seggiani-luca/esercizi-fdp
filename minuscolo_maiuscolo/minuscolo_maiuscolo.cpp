//
// scrivere un programma che determina se un carattere è maisucolo o minuscolo
//
#include <iostream>
using namespace std;

int main() {

    char a;
    cout << "Inserisci un carattere: " << endl;
    cin >> a;

    if(a>=65&a<=90) {
        cout << "M";
        return 0;
    }

    if(a>=97&a<=122) {
        cout << "m";
        return 0;
    }

    return 0;

}