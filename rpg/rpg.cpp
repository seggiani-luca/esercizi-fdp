#include <iostream> //input/output
#include <cstdlib> //numeri casuali
#include <string.h> //stringhe/testo
using namespace std;

//tipi fondamentali
struct vettore2d { int x; int y; };

//elementi livello
enum TipoCasella { muro, casellaVuota };
enum Entita { giocatore, entitaVuota };
struct Casella { TipoCasella tipoCasella; Entita entita; };
vettore2d posizioneGiocatore; //la posizione del giocatore e' definita sia come entita che come coordinate... forse va cambiato
vettore2d boundLivelloMinimi = {5,5};
vettore2d boundLivelloMassimi = {55, 15};

//elementi menu
int contatoreStringhe;
struct elementoMenu { char ident; string tag; void (*funzione)(int, Casella*, int&); }; 	//le funzioni accettano un indice i equivalente alla chiamata effettuata dal giocatore, questo
																						//è fatto per poter permettere comportamenti diversi alla solita funzione (e.g. spostaGiocatore)
																						//inoltre accettano un riferimento alla stanza attuale e la dimensione orizzontale della suddetta
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
	for(int i = 0; i < dim * 2 + 32; i++) {
		cout << "-";
	}
	cout << endl;
}

//utility livello
int vettore2d_indice(vettore2d& vettore, int& dimX) { //converte un vettore bidimensionale in un indice array
	return vettore.x + vettore.y * dimX;
}
int vettore2d_indice(int& x, int& y, int& dimX) { //overload per singole componenti
	return x + y * dimX;
}
vettore2d indice_vettore2d(int& indice, int& dimX) { //converte un indice array in un vettore bidimensionale
	int x = indice % dimX;
	int y = indice / dimX;
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
void inizializza_stanza(Casella stanza[], int& dimX, int& dimY) {
	for(int y = 0; y < dimY; y++) {
		for(int x = 0; x < dimX; x++) {		
			Casella* casella = &stanza[vettore2d_indice(x, y, dimX)];
			//condizioni muro
			bool muroSinistro = (x == 0);
			bool muroDestro = (x == dimX - 1);
			bool muroSuperiore = (y == 0);
			bool muroInferiore = (y == dimY - 1);

			bool portaX = (x == dimX/2);
			bool portaY = (y == dimY/2);

			//assegna enumeratore
			if((muroSinistro|muroDestro|muroSuperiore|muroInferiore)&!(portaX|portaY)) {
				casella -> tipoCasella = muro;
			} else {
				casella -> tipoCasella = casellaVuota;
			}
			
			casella -> entita = entitaVuota;
			
		}
	}
}

void inizializza_giocatore(Casella stanza[], int dimX, int dimY) {
	int posizione_giocatoreX = dado(1, dimX - 2);
	int posizione_giocatoreY = dado(1, dimY - 2);
	Casella* casellaGiocatore = &stanza[vettore2d_indice(posizione_giocatoreX, posizione_giocatoreY, dimX)];
	posizioneGiocatore.x = posizione_giocatoreX;
	posizioneGiocatore.y = posizione_giocatoreY;
	casellaGiocatore -> entita = giocatore;
}

void spostaGiocatore(int i, Casella stanza[], int& dimX); //inizializzo per la generazione successiva del menù

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
void esegui_scelta(int i, elementoMenu menu[elementiMenuMappa], Casella stanza[], int& dimX) {
	(*menu[i].funzione) (i, stanza, dimX);
}

void spostaGiocatore(int i, Casella stanza[], int& dimX) { //0 = su; 1 = sinistra; 2 = giù; 3 = destra
	Casella* casellaGiocatore = &stanza[vettore2d_indice(posizioneGiocatore, dimX)];
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
	Casella* nuovaCasella = &stanza[vettore2d_indice(posizioneGiocatore, dimX)];
	if(nuovaCasella -> tipoCasella == casellaVuota) {
		nuovaCasella -> entita = giocatore;
		concatenaConsole("Ti sei spostato " + stringaDirezione);
	} else {
		casellaGiocatore -> entita = giocatore; //reimposta giocatore se ha colliso
		posizioneGiocatore = vecchiaPosizione;
		concatenaConsole("Hai incontrato un muro!");
	}
}

void disegna_stanza(Casella stanza[], int& dimX, int& dimY) { //oltre alla stanza, si concatena sul lato destro la console
	for(int y = 0; y < dimY; y++) {
		for(int x = 0; x < dimX; x++) {
			int indice = vettore2d_indice(x ,y, dimX);
			disegna_casella(stanza[indice]);
		}
		cout << "| ";
		stampa_linea_console(y);
		cout << endl;
	}
}

int main() {
	srand(25); //inizializza seed casuale con time
	//inizializzazione livello
	int dimX = dado(boundLivelloMinimi.x, boundLivelloMassimi.x);
	int dimY = dado(boundLivelloMinimi.y, boundLivelloMassimi.y);
	Casella stanza[dimX * dimY];
	inizializza_stanza(stanza, dimX, dimY);
	
	//inizializzazione entita'
	inizializza_giocatore(stanza, dimX, dimY);
	
	//inizializzazione menu
	elementoMenu menuMappa[elementiMenuMappa];
	inizializza_menuMappa(menuMappa);
	inizializza_console();

	int scelta;
	
	while(true) {
		clear();
		//game loop
		disegna_stanza(stanza, dimX, dimY);
		separator(dimX);
		int scelta = disegna_menu(menuMappa, scelta);
		esegui_scelta(scelta, menuMappa, stanza, dimX);
	}
	return 0;
}
