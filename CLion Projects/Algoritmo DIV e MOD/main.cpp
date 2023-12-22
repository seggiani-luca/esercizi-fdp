#include <iostream>
using namespace std;

int main() {

    start:

    int N;  //numero N
    cout << "Inserisci il numero (base dieci)" << endl;
    cin >> N;

    int b;  //base
    cout <<"Inserisci la base" << endl;
    cin >> b;

    if(b < 2) { // failsafe base
        cout << "La base deve essere maggiore o uguale a 2" << endl;
        goto start;
    }

    cout <<"Il numero " + to_string(N) + " in base " + to_string(b) + " e' "; //algoritmo div e mod
    if(N == 0) {
        cout << 0 << endl;
        return 0;
    }

    int q = N;
    string number;
    while(q > 0) {
        int a = q % b;
        number.append(to_string(a));
        q = q / b;
    }

    for(int i = number.length()-1; i >= 0; i--) { //stampa stringa al contrario
        cout<<number[i];
    }

    return 0;
}
