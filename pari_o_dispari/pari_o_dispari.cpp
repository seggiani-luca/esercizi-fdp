//
// scrivere un programma che determina se un numero è pari o dispari
//
#include <iostream>
using namespace std;

int main() {

    int a;
    cout << "Inserisci un numero" << endl;
    cin >> a;

    if(a%2==0) { //controlla se pari
        cout << "P";
    } else {
        cout << "D";
    }

    return 0;

}