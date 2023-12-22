#include <iostream>
#include <cmath>
using namespace std;

int main() {

    start:

    int N;  //numero N
    cout << "Inserisci il numero" << endl;
    cin >> N;

    int b;  //base
    cout <<"Inserisci la base" << endl;
    cin >> b;

    if(b < 2) { // failsafe base
        cout << "La base deve essere maggiore o uguale a 2" << endl;
        goto start;
    }

    cout << "Il numero " + to_string(N) + " (base " + to_string(b) + ") e' ";

    int number = 0;
    string Nstring = to_string(N);

    for(int i = Nstring.length()-1; i >= 0; i--) {
        number += (Nstring[i] - '0')*pow(b,Nstring.length()-1-i);
    }

    cout << to_string(number) + " in base dieci";

    return 0;
}
