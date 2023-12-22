#include <iostream>
#include <limits>
#include <fstream>
#include <cstring>
using namespace std;

#include "liste.h"

struct canzone {
    char* titolo;
    char* artista;
    canzone() {
        titolo = nullptr;
        artista = nullptr;
    }
    ~canzone() {
        delete[] titolo;
        delete[] artista;
    }
};
struct playlist {
    char* nome;
    lista<canzone*> l;
    playlist() {
        nome = nullptr;
    }
    ~playlist() {
        delete nome;
    }
};

struct eleMenu {
    char* nome;
    void (*funzione)();
};

class menu {
    public:
        int l;
        bool root = false;
        eleMenu* elementi;
    ~menu() {
        delete[] elementi;
    }
};

const int ELEM_GLOBALI = 5;
static menu menu_globale;
const int ELEM_PLAYLIST = 4;
static menu menu_playlist;

lista<playlist*> liste;
playlist* current = nullptr;

const int MAX_LEN = 30;

const char* path = "playlist";

void mostra_menu(const menu& m);

//lettura dati
char* leggi_tag(char*& line, bool& end) {
    int c = 0;
    char* nome = new char[MAX_LEN + 1];
    while(*line != 124 && c < MAX_LEN) {
        nome[c] = *line;
        line++;
        c++;
    }
    nome[c] = '\0';
    end = (*(line+1) == NULL);
    if(!end)
        *line++;
    return nome;
}
void leggi_dati() {
    ifstream data;
    data.open(path, ios::in);
    if(!data.is_open()) {
        cout << "Errore di lettura del file " << path << "." << endl;
        return;
    }
    char* line = new char[256];
    while(data.getline(line, 256)) {
        bool end;
        char* linep = line;
        char* nome = leggi_tag(linep, end);
        auto *lista = new playlist;
        lista->nome = nome;
        liste.inserisci_coda(lista);
        current = lista;

        if(end)
            continue;

        //canzone
        while(!end) {
            char* titolo = leggi_tag(linep, end);
            char* artista = leggi_tag(linep, end);
            canzone* c = new canzone;
            c->titolo = titolo;
            c->artista = artista;
            current->l.inserisci_coda(c);
        }

    }
    delete[] line;
    current = nullptr;
    cout << "Lette playlist da " << path << endl;
}

//salvataggio dati
void salva_dati() {

    ofstream data;
    data.open(path, ios::out);

    //

    for(int i = 0; i < liste.lunghezza(); i++) {
        playlist* dest;
        liste.leggi_indice(dest, i);
        data << dest->nome;
        if(dest->l.lunghezza() == 0) {
            data << "|" << endl;
            continue;
        }
        for(int j = 0; j < dest->l.lunghezza(); j++) {
            canzone* canzone;
            dest->l.leggi_indice(canzone, j);
            data << "|" << canzone->titolo << "|" << canzone->artista;
        }
        data << endl;
    }

    //

    data.close();
    cout << "Salvate playlist in " << path << endl;
}

//funzioni di utilità
inline void flush() { //ripulisci lo stream di ingresso in caso di errori
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool leggiStringa(char*& t) {
    char c;
    int count = 0;
    cin >> c;
    while(c != '\n' & count < MAX_LEN) {
        t[count] = c;
        cin.get(c);
        count++;
    }
    t[count] = '\0';
    if(count == MAX_LEN) {
        flush();
        return false;
    } else {
        return true;
    }
}

//funzioni playlist

void stampa_playlist(lista<playlist*>& lista, int i) {
    playlist* dest;
    if(!lista.leggi_indice(dest, i) || i < -1) {
        cout << "\t\tPlaylist inesistente!" << endl;
        return;
    }
    cout << "\t\t" << dest->nome << ":" << endl;
    if(dest->l.lunghezza() == 0) {
        cout << "\t\t\tPlaylist vuota!" << endl;
        return;
    }
    for(int j = 0; j < dest->l.lunghezza(); j++) {
        canzone* canzone;
        dest->l.leggi_indice(canzone, j);
        cout << "\t\t\t" << canzone->titolo << " - " << canzone->artista << endl;
    }
    cout << endl;
}

void stampa_lista_playlist(lista<playlist*>& lista) {
    for(int i = 0; i < lista.lunghezza(); i++) {
        playlist* dest;
        lista.leggi_indice(dest, i);
        if(dest->nome == nullptr) //cout si offende se gli fornisco un nullptr
            return;
        cout << "\t\t" << i << ": " << dest->nome << endl;
    }
}

void visualizza_playlist() {
    if(liste.lunghezza() == 0) {
        cout << "\tNon hai ancora creato nessuna playlist!" << endl;
        return;
    }
    cout << "\tQuale playlist vuoi visualizzare? (digita -1 per visualizzarle tutte)" << endl;
    stampa_lista_playlist(liste);
    int scelta;
    cout << "\t\t\t";
    cin >> scelta;
    if(scelta == -1) {
        for(int i = 0; i < liste.lunghezza(); i++) {
            stampa_playlist(liste, i);
        }
        return;
    }
    stampa_playlist(liste, scelta);
}

void visualizza_playlist_corrente() {
    cout << "\t" << current->nome << ":" << endl;
    if(current->l.lunghezza() == 0) {
        cout << "\t\tPlaylist vuota!" << endl;
        return;
    }
    for(int j = 0; j < current->l.lunghezza(); j++) {
        canzone* canzone;
        current->l.leggi_indice(canzone, j);
        cout << "\t\t" << canzone->titolo << " - " << canzone->artista << endl;
    }
    cout << endl;
}

void crea_playlist() {
    auto *lista = new playlist;
    char* nome = new char[MAX_LEN+1];
    cout << "\t> Inserisci il titolo della playlist:" << endl;
    cout << "\t\t";
    if(!leggiStringa(nome))
        cout << "\t\tNome troppo lungo, tronco i primi 30 caratteri." << endl;
    lista->nome = nome;
    liste.inserisci_coda(lista);
    cout << "\t\tPlaylist creata!" << endl;
}

void modifica_playlist() {
    if(liste.lunghezza() == 0) {
        cout << "\tNon hai ancora creato nessuna playlist!" << endl;
        return;
    }
    cout << "\tQuale playlist vuoi modificare?" << endl;
    stampa_lista_playlist(liste);
    int scelta;
    cout << "\t\t\t";
    cin >> scelta;

    playlist* dest;
    if(!liste.leggi_indice(dest, scelta) || scelta < -1) {
        cout << "\t\tPlaylist inesistente!" << endl;
        return;
    }
    current = dest;
    mostra_menu(menu_playlist);
}

void elimina_singola_playlist(int scelta) {
    playlist* dest;
    if(!liste.leggi_indice(dest, scelta) || scelta < -1) {
        cout << "\t\tPlaylist inesistente!" << endl;
        return;
    }
    liste.estrai_indice(dest, scelta);
    cout << "\t\tElimino la playlist " << dest->nome << "." << endl;
    delete dest;
}

void elimina_playlist() {
    if(liste.lunghezza() == 0) {
        cout << "\tNon hai ancora creato nessuna playlist!" << endl;
        return;
    }
    cout << "\tQuale playlist vuoi eliminare? (digita -2 per annullare l'operazione e -1 per eliminarle tutte)" << endl;
    stampa_lista_playlist(liste);
    int scelta;
    cout << "\t\t\t";
    cin >> scelta;
    if(scelta == -2) {
        return;
    }
    if(scelta == -1) {
        cout << "\t\tStai per eliminare tutte le playlist. Sei sicuro? (Y\\n)" << endl;
        char c;
        cout << "\t\t\t";
        cin >> c;
        if(c != 'Y' && c != 'y')
            return;
        int lung = liste.lunghezza();
        for(int i = 0; i < lung; i++) {
            elimina_singola_playlist(0);
        }
        return;
    }
    elimina_singola_playlist(scelta);
}

void aggiungi_canzone() {
    char* titolo = new char[MAX_LEN + 1];
    cout << "\tInserisci il titolo della canzone" << endl;
    cout << "\t\t";
    if(!leggiStringa(titolo))
        cout << "\t\tTitolo troppo lungo, tronco i primi 30 caratteri." << endl;
    char* artista = new char[MAX_LEN];
    cout << "\tInserisci l'artista della canzone" << endl;
    cout << "\t\t";
    if(!leggiStringa(artista))
        cout << "\t\tIl nome dell'artista e' troppo lungo, tronco i primi 30 caratteri." << endl;

    canzone* c = new canzone;
    c->titolo = titolo;
    c->artista = artista;
    current->l.inserisci_coda(c);
    cout << "La canzone " << titolo << " di " << artista << " e' stata aggiunta alla playlist!" << endl;
}

void rimuovi_canzone() {
    if(current->l.lunghezza() == 0) {
        cout << "\tLa playlist e' vuota!" << endl;
        return;
    }
    cout << "\tQuale canzone vuoi eliminare? (digita -2 per annullare l'operazione e -1 per eliminarle tutte)" << endl;
    for(int i = 0; i < current->l.lunghezza(); i++) {
        canzone* canzone;
        current->l.leggi_indice(canzone, i);
        cout << "\t\t\t" << i << ": " << canzone->titolo << " - " << canzone->artista << endl;
    }
    int scelta;
    cout << "\t\t\t";
    cin >> scelta;
    if(scelta == -2) {
        return;
    }
    canzone* dest;
    if(scelta == -1) {
        cout << "\t\tStai per eliminare tutte le canzoni della playlist. Sei sicuro? (Y\\n)" << endl;
        char c;
        cout << "\t\t\t";
        cin >> c;
        if(c != 'Y' && c != 'y')
            return;
        int lung = current->l.lunghezza();
        for(int i = 0; i < lung; i++) {
            current->l.estrai_oggetto(0);
            cout << "Rimuovo la canzone " << dest->titolo << " di " << dest->artista;
            delete dest;
        }
        return;
    }
    current->l.estrai_indice(dest, scelta);
    cout << "Rimuovo la canzone " << dest->titolo << " di " << dest->artista;
    delete dest;
    return;
}

//funzioni menu

void mostra_menu(const menu& m) {
    while(true) {
        if(!m.root && current != nullptr && current->nome != nullptr)
            cout << "Playlist corrente: " << current->nome << endl;
        cout << "Quale azione vuoi eseguire?" << endl;

        //
        for(int i = 0; i < m.l; i++) {
            cout << "\t" << i << ": " << m.elementi[i].nome << endl;
        }
        //

        char scelta;
        cout << "\t\t";
        cin >> scelta;
        scelta -= '0';
        while(scelta < 0 | scelta >= m.l) {
            cout << "\tScelta non valida, riprova" << endl;
            flush();
            cout << "\t\t";
            cin >> scelta;
            scelta -= '0';
        }
        if(scelta == m.l - 1) {
            if(m.root) {
                salva_dati();
                exit(0);
            } else {
                cout << "\tEsco dal menu." << endl;
                return;
            }
        }
        (*m.elementi[scelta].funzione)();

        cout << endl;
    }
}

void inizializza_menu() {
    menu_globale.elementi = new eleMenu[ELEM_GLOBALI];
    menu_globale.l = ELEM_GLOBALI;
    menu_globale.root = true;

    menu_playlist.elementi = new eleMenu[ELEM_PLAYLIST];
    menu_playlist.l = ELEM_PLAYLIST;

    //

    menu_globale.elementi[0].nome = "Visualizza le playlist create";
    menu_globale.elementi[0].funzione = visualizza_playlist;
    menu_globale.elementi[1].nome = "Crea una nuova playlist";
    menu_globale.elementi[1].funzione = crea_playlist;
    menu_globale.elementi[2].nome = "Modifica una playlist esistente";
    menu_globale.elementi[2].funzione = modifica_playlist;
    menu_globale.elementi[3].nome = "Elimina una playlist esistente";
    menu_globale.elementi[3].funzione = elimina_playlist;
    menu_globale.elementi[4].nome = "Termina l'esecuzione del programma";
    menu_globale.elementi[4].funzione = nullptr;

    //

    menu_playlist.elementi[0].nome = "Visualizza la playlist";
    menu_playlist.elementi[0].funzione = visualizza_playlist_corrente;
    menu_playlist.elementi[1].nome = "Aggiungi una canzone";
    menu_playlist.elementi[1].funzione = aggiungi_canzone;
    menu_playlist.elementi[2].nome = "Rimuovi una canzone";
    menu_playlist.elementi[2].funzione = rimuovi_canzone;
    menu_playlist.elementi[3].nome = "Concludi l'operazione";
    menu_playlist.elementi[3].funzione = nullptr;
}

int main() {
    leggi_dati();

    //

    inizializza_menu();
    mostra_menu(menu_globale);
    return 0;
}