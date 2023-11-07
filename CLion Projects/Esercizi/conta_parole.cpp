//
// scrivere un programma che stampa il numero di parole in una stringa
//
#include <iostream>
using namespace std;

/* annotazione: sebbene l'esercizio richieda di operare su stringhe, ho scelto di lavorare sullo stream di ingresso */
int contaParole() {
    int conto = 0;
    char c;
    cin.get(c);
    while(c != '\n') {
        if(c == ' ')
          conto++;
        cin.get(c);
    }
    return (conto == 0 ? 0 : conto+1);
}

int main() {
    cout << "Inserisci una stringa di massimo 40 caratteri" << endl;
    int parole = contaParole();
    cout << "La stringa ha " << parole << " parole" << endl;
    return 0;
}
