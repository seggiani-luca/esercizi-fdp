//
// scrivere un programma che legga dieci interi e stampi la media dei positivi
//

#include <iostream>
using namespace std;

int main() {

    int a = 0;
    int i = 0;
    int n = 0;

    while(i < 10) {
        i++;
        int b;
        cout << "Inserisci intero no. " << i << endl;
        cin >> b;
        if(b > 0) {
            a += b;
            n++;
        }
    }

    if(n == 0)
        n = 1;

    double media = (double) a / n;
    cout << "La media e' " << media;

}