//
// scrivere un programma che risolve un'equazione di tipo ax^2 + bx + c = 0.
//
#include <iostream>
#include <cmath> //usato per la funzione sqrt()

using namespace std;

int main() {

    /*
     * per risolvere un equazione di secondo grado, richiedo all'utente i coefficienti a, b, c
     * e faccio le seguenti considerazioni:
     * se a = 0 e b = 0, equazione degenere;
     * se solo a = 0, equazione di primo grado (e risolvo)
     * a questo punto calcolo il determinante d:
     * se d < 0, soluzioni immaginarie;
     * se d = 0, x = -b/2a
     * se d > 0, x1 = (-b-sqrt(d))/2a e x2 = (-b+sqrt(d))/2a
     *
     * (per esercizio personale ho reso il programma in grado di trovare soluzioni immaginarie,
     * il codice in questione è commentato per assicurare l'esecuzione richiesta dall'esercizio).
     */

    double a,b,c; //utilizzo un double perchè rappresenterò valori reali

    cout << "Inserisci il coefficiente a: " << endl;
    cin >> a;
    cout << "Inserisci il coefficiente b: " << endl;
    cin >> b;
    cout << "Inserisci il coefficiente c: " << endl;
    cin >> c;

    if(a==0){ //prime considerazioni sui coefficienti
        if(b==0) {
            cout << "L'equazione e' degenere";
            return 0;
        } else {
            cout << "L'equazione e' di primo grado, la soluzione e' ";
            double ris = -c / b;
            cout << ris;
            return 0;
        }
    }

    int det = b*b - 4 * a * c; //b^2-4ac
    if(det < 0) {
        cout << "L'equazione ha soluzioni immaginarie"<<endl;

        /*
        double ris_a = -b / (2 * a);
        double ris_b = sqrt(-det) / (2 * a);

        cout << "Le soluzioni immaginarie dell'equazione sono: " //concateno la stringa qui
             << ris_a << " + i" << ris_b << " e "
             << ris_a << " - i" << ris_b;
        */

    }
    if(det == 0) {
        double ris = -b / (2 * a);
        cout << "La soluzione reale dell'equazione e' " << ris;
    }
    if(det > 0) {
        double ris1 = (-b - sqrt(det)) / (2*a);
        double ris2 = (-b + sqrt(det)) / (2*a);
        cout << "Le soluzioni reali dell'equazione sono " << ris1 << " e " << ris2;
    }

    return 0;

}