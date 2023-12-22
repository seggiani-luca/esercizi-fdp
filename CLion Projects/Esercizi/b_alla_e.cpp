//
// scrivi un programma che chieda gli interi b ed e e stampi b alla e
//
#include <iostream>
using namespace std;

int main() {

    int b;
    int origB; //immagazzino la base in quanto lavorero' direttamente sulla variabile b
    int e;
    cout << "Inserisci la base b:" << endl;
    cin >> b;
    origB = b;
    cout << "Inserisci l'esponente e: " << endl;
    cin >> e;

    if(b==0 & e==0) {
        cout << "La potenza non e' definita" << endl;
        return 0;
    }

    if(e<=0) {
        cout << "La potenza e' 1" << endl;
        return 0;
    }

    if(b==0) {
        cout << "La potenza e' 0" << endl;
        return 0;
    }

    int i = 1;
    while(i < e) {
        b *= origB;
        i++;
    }

    cout << "La potenza e' " << b << endl;
}