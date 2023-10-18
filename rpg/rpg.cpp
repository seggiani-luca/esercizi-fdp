#include <iostream> //input/output
#include <cstdlib> //numeri casuali
#include <string.h> //stringhe/testo
using namespace std;

//tipi fondamentali
struct vettore2d { int x; int y; };

//elementi livello
enum TipoCasella { muro, porta, casellaVuota };
enum Entita { giocatore, entitaVuota };
struct Casella { TipoCasella tipoCasella; Entita entita; };
vettore2d posizioneGiocatore; //la posizione del giocatore e' definita sia come entita che come coordinate per accesso rapido
vettore2d boundLivelloMinimi = {5,5};
vettore2d boundLivelloMassimi = {55, 15};

vettore2d posizioneGlobale; //rappresenta la base da cui viene calcolato il seed casuale
vettore2d dim; //dimensioni livello

int cantor(int a, int b) { //implementazione della funzione coppia di cantor
	return (0.5*(a+b)*(a+b+1)+b);
}

//elementi menu
int contatoreStringhe;
struct elementoMenu { char ident; string tag; int (*funzione)(int, Casella*); }; 	    //le funzioni accettano un indice i equivalente alla chiamata effettuata dal giocatore, questo
																						//è fatto per poter permettere comportamenti diversi alla solita funzione (e.g. spostaGiocatore)
																						//inoltre accettano un riferimento alla stanza attuale (per poterci lavorare)
const int elementiMenuMappa = 4; //fornisco una lunghezza fissa per il compilatore
const int scrollbackConsole = 16; //imposta uno scrollback di 16
string lineeConsole[scrollbackConsole];

//utility shell
void clear() {	//svuota lo schermo, multipiattaforma
	#ifdef __CYGWIN32__
		system("cls");
	#else
		system("clear");
	#endif
}
void separator(int dim) {
	for(int i = 0; i < dim * 2 + 48; i++) {
		cout << "-";
	}
	cout << endl;
}

//utility livello
int vettore2d_indice(vettore2d& vettore) { //converte un vettore bidimensionale in un indice array
	return vettore.x + vettore.y * dim.x;
}
int vettore2d_indice(int& x, int& y) { //overload per singole componenti
	return x + y * dim.x;
}
vettore2d indice_vettore2d(int& indice) { //converte un indice array in un vettore bidimensionale
	int x = indice % dim.x;
	int y = indice / dim.x;
	vettore2d ris = { x, y };
	return ris;
}

int dado(int min, int max) { //genera numeri casuali in un range min - max
	if(min > max) {
		cerr << "Errore nel lancio del dado: min non puo' essere maggiore di max." << endl;
		return 0;
	}
	int range = max - min;
	int dado = rand() % (range + 1) + min;
	return dado;
}

//generazione
void inizializza_stanza(Casella stanza[]) {
	for(int y = 0; y < dim.y; y++) {
		for(int x = 0; x < dim.x; x++) {
			Casella* casella = &stanza[vettore2d_indice(x, y)];
			//condizioni muro
			bool muroSinistro = (x == 0);
			bool muroDestro = (x == dim.x - 1);
			bool muroSuperiore = (y == 0);
			bool muroInferiore = (y == dim.y - 1);

			bool portaX = (x == dim.x/2);
			bool portaY = (y == dim.y/2);

			//assegna enumeratore
			if(muroSinistro|muroDestro|muroSuperiore|muroInferiore) {
				if(portaX|portaY) {
					casella -> tipoCasella = porta;
				} else {
					casella -> tipoCasella = muro;
				}
			} else {
				casella -> tipoCasella = casellaVuota;
			}
			
			casella -> entita = entitaVuota;
			
		}
	}
}

void inizializza_giocatore(Casella stanza[]) {
	if((posizioneGiocatore.x == 1)|(posizioneGiocatore.x == 999)) {
		posizioneGiocatore.y = dim.y / 2;
		if(posizioneGiocatore.x == 999) {
			posizioneGiocatore.x = dim.x - 2;
		}
	} else {
		if((posizioneGiocatore.y == 1)|(posizioneGiocatore.y == 999)) {
			posizioneGiocatore.x = dim.x / 2;
			if(posizioneGiocatore.y == 999) {
				posizioneGiocatore.y = dim.y - 2;
			}
		} else {
			posizioneGiocatore.x = dado(1, dim.x - 2);
			posizioneGiocatore.y = dado(1, dim.y - 2);
		}
	}
	Casella* casellaGiocatore = &stanza[vettore2d_indice(posizioneGiocatore)];
	casellaGiocatore -> entita = giocatore;
}

int spostaGiocatore(int i, Casella stanza[]); //inizializzo per la generazione successiva del menù

//generazione menu
void inizializza_menuMappa(elementoMenu menuMappa[elementiMenuMappa]) {
	menuMappa[0].ident = 'w';
	menuMappa[0].tag = "Vai su";
	menuMappa[0].funzione = spostaGiocatore;

	menuMappa[1].ident = 'a';
	menuMappa[1].tag = "Vai a sinistra";
	menuMappa[1].funzione = spostaGiocatore;

	menuMappa[2].ident = 's';
	menuMappa[2].tag = "Vai giu'";
	menuMappa[2].funzione = spostaGiocatore;

	menuMappa[3].ident = 'd';
	menuMappa[3].tag = "Vai a destra";
	menuMappa[3].funzione = spostaGiocatore;
}

void inizializza_console() {
	for(int i = 0; i < scrollbackConsole; i++) {
		lineeConsole[i].resize(64); //evita segfault per stringhe troppo grandi
	}
}

//interazione console
void concatenaConsole(string nuovaStringa) {
	for(int i = scrollbackConsole - 1; i >= 0; i--) {
		lineeConsole [i + 1] = lineeConsole[i];
	}
	lineeConsole[0] = "("+to_string(contatoreStringhe)+") " + nuovaStringa;
	contatoreStringhe += 1;
}

//disegno
void disegna_entita(Entita& entita) {
	switch(entita) {
		case giocatore:
			cout << "a ";
	}
}

void disegna_casella(Casella& casella) {
	if(casella.entita != entitaVuota) {
		disegna_entita(casella.entita);
		return;
	}
	switch(casella.tipoCasella) {
		case muro:
			cout << "# ";
			break;
		case porta:
			cout << "A ";
			break;
		case casellaVuota:
			cout << "  ";
	}
}

void stampa_linea_console(int i) {
	if(i == 0)
		cout << "=> ";
	cout << lineeConsole[i];
}

int disegna_menu(elementoMenu menu[elementiMenuMappa], int& scelta) {
	cout << "Comandi disponibili: " << endl;
	for(int i = 0; i < elementiMenuMappa; i++) {
		elementoMenu* elemento = &menu[i];
		cout << "\t" << (elemento -> ident) << " : " << (elemento -> tag) << endl;
	}
	char sceltaChar;
	cout << "Digita un comando (o una sequenza di comandi): ";
	cin >> sceltaChar;

	for(int i = 0; i < elementiMenuMappa; i++) {
		if(sceltaChar == menu[i].ident)
			return i;
	}

	return 0;
}

//logica di gioco
int esegui_scelta(int i, elementoMenu menu[elementiMenuMappa], Casella stanza[]) {
	return (*menu[i].funzione) (i, stanza);
}

int spostaGiocatore(int i, Casella stanza[]) { //0 = su; 1 = sinistra; 2 = giù; 3 = destra
	Casella* casellaGiocatore = &stanza[vettore2d_indice(posizioneGiocatore)];
	casellaGiocatore -> entita = entitaVuota;
	vettore2d vecchiaPosizione = posizioneGiocatore;
	string stringaDirezione;
	switch(i) {
		case 0:
			posizioneGiocatore.y -= 1;
			stringaDirezione = "verso l'alto.";
			break;
		case 1:
			posizioneGiocatore.x -= 1;
			stringaDirezione = "verso sinistra.";
			break;
		case 2:
			posizioneGiocatore.y += 1;
			stringaDirezione = "verso il basso.";
			break;
		case 3:
			posizioneGiocatore.x += 1;
			stringaDirezione = "verso destra.";
			break;
	}
	Casella* nuovaCasella = &stanza[vettore2d_indice(posizioneGiocatore)];
	if(nuovaCasella -> tipoCasella == casellaVuota) {
		nuovaCasella -> entita = giocatore;
		concatenaConsole("Ti sei spostato " + stringaDirezione);
	} else {
		if(nuovaCasella -> tipoCasella == porta) {
			bool portaX = (posizioneGiocatore.x == dim.x/2);
			bool portaY = (posizioneGiocatore.y == dim.y/2);
			if(portaX & posizioneGiocatore.y == 0) {
				posizioneGlobale.y -= 1;
				posizioneGiocatore.y = 999;
			} else {
				if(portaX & posizioneGiocatore.y != 0) {
					posizioneGlobale.y += 1;
					posizioneGiocatore.y = 1;
				}
			}
			if(portaY & posizioneGiocatore.x == 0) {
				posizioneGlobale.x -= 1;
				posizioneGiocatore.x = 999;
			} else {
				if(portaY & posizioneGiocatore.x != 0) {
					posizioneGlobale.x += 1;
					posizioneGiocatore.x = 1;
			}
			}
			concatenaConsole("Ti sei spostato in una nuova stanza " + stringaDirezione);
			return 0;
		} else {
			casellaGiocatore -> entita = giocatore; //reimposta giocatore se ha colliso
			posizioneGiocatore = vecchiaPosizione;
			concatenaConsole("Hai incontrato un muro!");
		}
	}
	return 1;
}

void disegna_stanza(Casella stanza[]) { //oltre alla stanza, si concatena sul lato destro la console
	for(int y = 0; y < dim.y; y++) {
		for(int x = 0; x < dim.x; x++) {
			int indice = vettore2d_indice(x ,y);
			disegna_casella(stanza[indice]);
		}
		cout << "| ";
		stampa_linea_console(y);
		cout << endl;
	}
}

int main() {

	posizioneGlobale.x = 256; //inizializza in un luogo arbitrario
	posizioneGlobale.y = 256;
	
	//inizializzazione menu
	elementoMenu menuMappa[elementiMenuMappa];
	inizializza_menuMappa(menuMappa);
	inizializza_console();

	int scelta;

	start:
	srand(cantor(posizioneGlobale.x, posizioneGlobale.y)); //inizializza seed casuale con posizione globale//inizializzazione livello
	dim.x = dado(boundLivelloMinimi.x, boundLivelloMassimi.x);
	dim.y = dado(boundLivelloMinimi.y, boundLivelloMassimi.y);
	Casella stanza[dim.x * dim.y];
	inizializza_stanza(stanza);
	//inizializzazione entita'
	inizializza_giocatore(stanza);
	
	while(true) {
		clear();
		//game loop
		disegna_stanza(stanza);
		separator(dim.x);
		int scelta = disegna_menu(menuMappa, scelta);
		if(!esegui_scelta(scelta, menuMappa, stanza)) {
			goto start;
		}
	}
	return 0;
}
