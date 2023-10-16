#include <iostream> //input/output
#include <cstdlib> //numeri casuali
#include <ctime>
using namespace std;

//tipi fondamentali
struct vettore2d { int x; int y; };

//elementi livello
enum TipoCasella { muro, casellaVuota };
enum Entita { giocatore, entitaVuota };
struct Casella { TipoCasella tipoCasella; Entita entita; };
vettore2d boundLivelloMinimi = {5,5};
vettore2d boundLivelloMassimi = {55, 15};

//elementi menu
struct elementoMenu { char ident; char* tag; void *funzione(void); };
const int elementiMenuMappa = 4; //fornisco una lunghezza fissa per il compilatore

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
			//assegna enumeratore
			if(muroSinistro|muroDestro|muroSuperiore|muroInferiore) {
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
	casellaGiocatore -> entita = giocatore;
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

int disegna_menu(elementoMenu menu[]) {
	
}

//logica di gioco
void spostaGiocatore() {
	
}

void disegna_stanza(Casella stanza[], int& dimX, int& dimY) {
	for(int y = 0; y < dimY; y++) {
		for(int x = 0; x < dimX; x++) {
			int indice = vettore2d_indice(x ,y, dimX);
			disegna_casella(stanza[indice]);
		}
		cout << endl;
	}
}

int main() {
	srand(time(0)); //inizializza seed casuale con time
	//inizializzazione livello
	int dimX = dado(boundLivelloMinimi.x, boundLivelloMassimi.x);
	int dimY = dado(boundLivelloMinimi.y, boundLivelloMassimi.y);
	Casella stanza[dimX * dimY];
	inizializza_stanza(stanza, dimX, dimY);
	
	//inizializzazione entita'
	inizializza_giocatore(stanza, dimX, dimY);
	
	//inizializzazione menu
	elementoMenu menuMappa[elementiMenuMappa] = //ridefinisci singolarmente o comunque sistema
	{
		'w', "Vai su", spostaGiocatore,
		'a', "Vai a sinistra", spostaGiocatore,
		's', "Vai giu", spostaGiocatore,
		'd', "Vai a destra", spostaGiocatore	
	};
	
	//game loop
	disegna_stanza(stanza, dimX, dimY);
	int scelta = disegna_menu(menuMappa);
	return 0;
}