//
// scrivere un programma che determina se un numero è multiplo di 2 ma non di 4
//
#include <iostream>
using namespace std;

int main() {

    int foo;
    cout << "Inserisci un numero: " << endl;
    cin >> foo;

    bool m2 = foo % 2 == 0;
    bool m4 = foo % 4 == 0;

    if(m2&!m4) {
        cout << "Il numero e' multiplo di 2 ma non di 4";
    }

    return 0;

}
