//
// scrivere un programma che mostra a video l'assoluto di un numero
//
#include <iostream>
using namespace std;

int main() {

    int num;
    cout << "Inserisci un numero intero: " << endl;
    cin >> num;

    if(num < 0) {
        num = -num;
    }

    cout << "L'assoluto e': " << num;

    return 0;

}
