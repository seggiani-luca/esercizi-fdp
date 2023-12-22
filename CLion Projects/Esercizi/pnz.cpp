//
// scrivere un programma che richiede un numero e scriva p se positivo, n se negativo e z se nullo.
//
#include <iostream>
using namespace std;

int main() {

    int a;
    cout << "Inserisci un numero" << endl;
    cin >> a;

    if(a>0) {
        cout << "P";
    }

    if(a==0) {
        cout << "Z";
    }

    if(a<0) {
        cout << "N";
    }

    return 0;

}