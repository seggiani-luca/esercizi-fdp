//
// scrivere un programma che stampa il numero di parole in una stringa
//
#include <iostream>
using namespace std;

int contaParole(char* str) {
    int conto = 0;
    bool parola = false;
    while(*str != '\0') {
        if(*str != ' ' & !parola) {
            conto += 1;
            parola = true;
        }
        if(*str == ' ')
            parola = false;
        str++;
    }
    return conto;
}

int main() {
    char* stringa = "    Uno, nessuno, centomila      ";
    int parole = contaParole(stringa);
    cout << "La stringa ha " << parole << " parole" << endl;
    return 0;
}