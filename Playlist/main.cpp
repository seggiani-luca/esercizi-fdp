#include <iostream>
using namespace std;

#include "liste.h"
#include "id3.h"

void stampa_lista(lista<int> l) {
    cout << l.lunghezza() << endl;
    for(int i = 0; i < l.lunghezza(); i++) {
        int dest;
        l.leggi_indice(dest, i);
        cout << dest << " ";
    }
    cout << endl;
}

int main() {
    lista<int> l;
    cout << "Inserisci 6 interi:" << endl;
    for(int i = 0; i < 6; i++) {
        int a;
        cin >> a;
        l.inserisci_ordinato(a);
    }
    cout << "La lista memorizzata e'" << endl;
    stampa_lista(l);

    return 0;
}