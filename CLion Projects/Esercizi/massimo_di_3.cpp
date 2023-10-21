//
// scrivere un programma che richieda 3 numeri e mostri a video il massimo
//
#include <iostream>
using namespace std;

int main() {

    int a,b,c;
    cout << "Inserisci 3 interi: " << endl;
    cin >> a >> b >> c;

    int max = -2147483648; //inizzializzo la variabile in quanto desidero usarla subito. Il valore -2147483648
                           // serve ad assicurarsi che max sia sempre più piccolo di a,b,c.
    if(a>max) {
        max = a;
    }
    if(b>max) {
        max = b;
    }
    if(c>max) {
        max = c;
    }

    cout << "Il massimo dei tre e' " << max;
    return 0;

}
