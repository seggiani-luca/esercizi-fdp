#include <iostream>
#include "lista.h"
using namespace std;

const int MAX_LEN = 30;

//gestione dei menù
struct elementoMenu {
    const char* nome;
    void (*funzione)(lista&);
}; const int ELEMENTI_MENU = 4;

//funzioni necessarie per la definizione dei menu
void stampaLista(lista& p);
void ottieniElemento(lista& p);
void rimuoviElemento(lista& p);

void inizializzaMenu(elementoMenu* menu) {
    menu[0].nome = "Visualizza le schede immagazzinate in memoria";
    menu[0].funzione = stampaLista;
    menu[1].nome = "Aggiungi una nuova scheda";
    menu[1].funzione = ottieniElemento;
    menu[2].nome = "Elimina una scheda";
    menu[2].funzione = rimuoviElemento;
    menu[3].nome = "Termina l'esecuzione del programma";
}

int stampaMenu(elementoMenu* menu) {
    cout << "Scegli la prossima operazione:" << endl;
    for(int i = 0; i < ELEMENTI_MENU; i++) {
        cout << i << " - " << menu[i].nome << endl;
    }
    int s;
    cin >> s;
    while(s <
     0 | s > ELEMENTI_MENU - 1) {
        cout << "Scegli un'operazione valida" << endl;
        cin >> s;
    }
    cout << endl;
    return s;
}

void eseguiScelta(elementoMenu* menu, int scelta, lista& l) {
    if(scelta == 3) {
        cout << "Dealloco i dati in memoria..." << endl;
        dealloca(l);
        exit(0);
    }
    (*menu[scelta].funzione)(l);
}

//operazioni su liste
void formattaElemento(scheda* inf, int i);
void stampaLista(lista& p) {
    if(p == nullptr) {
        cout << "La lista e' vuota." << endl;
        return;
    }
    cout << "Stampo la lista:" << endl;
    lista p0 = p;
    int i = 0;
    while(p0 != nullptr) {
        formattaElemento(p0->inf, i);
        p0 = p0->pun;
        i++;
    }
    cout << endl;
}

void ottieniElemento(lista& p) {
    scheda* s = new scheda;
    char* nome = new char[MAX_LEN + 1];
    char* cognome = new char[MAX_LEN + 1];
    cout << "Inserisci il nome del candidato:" << endl;
    cin >> cognome;
    cout << "Inserisci il cognome del candidato:" << endl;
    cin >> nome;
    s->cognome = cognome;
    s->nome = nome;
    inserisci(p, s);
    cout << "La scheda e' stata aggiunta alla lista." << endl;
}

void rimuoviElemento(lista& p) {
    stampaLista(p);
    if(p == nullptr)
        return;
    int i;
    cout << "Scegli un'elemento da rimuovere." << endl;
    cin >> i;
    if(estrai(p, i)) {
        cout << "Elemento rimosso con successo." << endl;
        stampaLista(p);
    } else {
        cout << "L'operazione di rimozione e' fallita" << endl;
        cout << "(si e' sicuri che l'elemento esista veramente?)." << endl;
    }
}

//funzioni utilità
void formattaElemento(scheda* inf, int i) {
    cout << i << " " << inf->cognome << " " << inf->nome << endl; 
}

int main() {
    //crea la lista di schede
    lista n = nullptr;

    //inizializza menu
    elementoMenu menu[ELEMENTI_MENU];
    inizializzaMenu(menu);

    //loop
    while(true) {
        int scelta = stampaMenu(menu);
        eseguiScelta(menu, scelta, n);
        cout << endl;
    }

    return 0;
}