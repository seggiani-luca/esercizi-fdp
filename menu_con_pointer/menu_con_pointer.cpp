#include <iostream>
#include <cmath>
using namespace std;

struct item { char* operazione; double (*funzione)(double);};

const int nItem = 7; //numero item indicato con const per indicare al compilatore la grandezza dell'array menu[]

void define_items(item menu[]) { //definizione membro a membro di array già allocata
	
	menu[0].operazione = "esci";
	menu[0].funzione = 0;
	menu[1].operazione = "sin(x)";
	menu[1].funzione = sin;
	menu[2].operazione = "cos(x)";
	menu[2].funzione = cos;
	menu[3].operazione = "tan(x)";
	menu[3].funzione = tan;
	menu[4].operazione = "asin(x)";
	menu[4].funzione = asin;
	menu[5].operazione = "acos(x)";
	menu[5].funzione = acos;
	menu[6].operazione = "atan(x)";
	menu[6].funzione = atan;
	
}

int stampa_menu(item menu[]) {
	
	cout << "Scegli un'operazione da eseguire: " << endl;
	for(int i = 0; i < nItem; i++) {
		cout << i << ' ' << menu[i].operazione << endl; 
	}
	
	int input;
	cin >>  input;
	return input;
	
}

double esegui_scelta(int i, item menu[]) {
	
	if(menu[i].funzione == 0) {
		cout << "bye bye" << endl;
		exit(0); //arresta esecuzione se "esci" selezionato		
	}
	double n;
	cout << "Inserisci x: " << endl;
	cin >> n;
	double ris = (*menu[i].funzione) (n);
	return ris;
	
}

int main() {
	
	item menu[nItem];
	define_items(menu);
	
	int scelta;
	double ris;
	
	while(true) { //bruttissimo ma funziona
		
		scelta = stampa_menu(menu);
		ris = esegui_scelta(scelta, menu);
		cout << "Il risultato e' " << ris << endl;
		
	}
	
	return 0;
}