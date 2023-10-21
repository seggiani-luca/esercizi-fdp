//
// scrivere un programma che stampi una tavola pitagorica
//
#include <iostream>
using namespace std;

void stampa_riga(int r, int d) {
    for(int i = 0; i < d; i++) {
        int n = (i+1) * (r+1);
        cout << n;
        int lunghezza = 0;
        while(n > 0) {
            n /= 10;
            lunghezza++;
        }
        for(int j = 0; j < 4-lunghezza; j++) {
            cout << " ";
        }
    }
}

int main() {
    int o;
    cout << "Ordine? " << endl;
    cin >> o;

    for(int i = 0; i < o; i++) {
        stampa_riga(i, o);
        cout << endl;
    }
    return 0;
}