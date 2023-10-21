//
// unire i programmi "triangoli" e "triangoli_isosceli" in un unico programma dotato di menu
//
#include <iostream>
using namespace std;
struct elementoMenu { char* tag; void (*funzione)(void); };
const int numeroElementiMenu = 5;

int stampa_menu(elementoMenu menu[]) {
    cout << "Triangoli disponibili: " << endl;
    for(int i = 0; i < numeroElementiMenu; i++) {
        cout << i << " : " << menu[i].tag << endl;
    }
    int scelta;
    cout << "Quale triangolo vuoi disegnare? (premi 0 per uscire)" << endl;
    cin >> scelta;
    return scelta;
}

int chiedi_lato() {
    int n;
    do {
        cout << "Lato? " << endl;
        cin >> n;
    } while (n<=0);
    return n;
}

void triangoloRettangolo() {
    int n = chiedi_lato();
    cout << "Triangolo rettangolo" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i+1; j++) {
            cout << "*  ";
        }
        cout << endl;
    }
}
void triangoloRettangoloRov() {
    int n = chiedi_lato();
    cout << endl << "Triangolo rettangolo rovesciato" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            cout << "   ";
        }
        for(int j = 0; j < n-i; j++) {
            cout << "*  ";
        }
        cout << endl;
    }
}
void triangoloIsosceleRov() {
    int n = chiedi_lato();
    int h = n/2 + 1;
    cout << "Triangolo isoscele rovesciato" << endl;
    for(int j = 0; j < h; j++) {
        for(int k= 0; k < j; k++) {
            cout << "   ";
        }
        for(int k = 0; k < n - j*2; k++) {
            cout << "*  ";
        }
        cout << endl;
    }
}
void triangoloIsosceleRot() {
    int n = chiedi_lato();
    int h = n/2 + 1;
    cout << endl << "Triangolo isoscele ruotato" << endl;
    for(int j = 0; j < n; j++) {
        if(j < n / 2) {
            for(int k = 0; k < j+1; k++) {
                cout << "*   ";
            }
        } else {
            for(int k = 0; k < n/2+h-j; k++) {
                cout << "*   ";
            }
        }
        cout << endl;
    }
}

void esci() {
    exit(0);
}

int main() {
    elementoMenu menu[] = {
            "Esci", esci,
            "Triangolo rettangolo", triangoloRettangolo,
            "Triangolo rettangolo rovesciato", triangoloRettangoloRov,
            "Triangolo isoscele rovesciato", triangoloIsosceleRov,
            "Triangolo isoscele ruotato", triangoloIsosceleRot
    };

    while(true) {
        int scelta = stampa_menu(menu);
        (*menu[scelta].funzione)();
    }
    return 0;
}