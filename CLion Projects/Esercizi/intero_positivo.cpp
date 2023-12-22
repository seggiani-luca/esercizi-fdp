//
// scrivere un programma che accetta solo un intero positivo
//
#include <iostream>
using namespace std;

int main() {

    int a;
    cout << "Inserisci un'intero positivo" << endl;
    cin >> a;
    while(a < 0) {
        cout << "L'intero deve essere positivo!" << endl;
        cin >> a;
    }

    cout << 2 << endl;
    return 0;

}