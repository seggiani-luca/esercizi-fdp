//
// scrivi un programma che legga dieci numeri interi e ne stampi la somma
//
#include <iostream>
using namespace std;

int main() {

    int a = 0;
    int i = 0;

    while(i < 10) {

        i++;

        int b;
        cout << "Inserisci intero no. " << i << endl;
        cin >> b;
        a +=b;
    }

    cout << "La somma e' " << a;

}