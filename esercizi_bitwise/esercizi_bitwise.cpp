#include <iostream>
using namespace std;

unsigned short mask = 0x8000; //chiedo il bit all'utente
const unsigned short bitMask = 0x8000; // 1000 0000 0000 0000 

int main() {
	
	unsigned short a;
	cout << "Digita una sequenza di 16 bit: " << endl;
	for(int i = 0; i < 16; i++) { //traduci buffer sequenza in unsigned
		a += ((cin.get() - '0') << 15 >> i); //evil hack
	}
	
	unsigned short index;
	cout << "Scegli quale bit selezionare (contando da sinistra)" << endl;
	cin >> index;
	
	mask >>= (index-1);
	
	unsigned short b = a&~mask; //rimuovo
	unsigned short c = a&mask; //isolo
	
	cout << "Sequenza digitata:" << endl; //stampa le sequenze modificate piu' l'originale
	
	for(int i = 0; i < 16; i++) {
		
		cout << ((a & bitMask) ? 1 : 0);
		a = a << 1;
		
	}
	
	cout << endl << "Sequenza con i-esimo bit rimosso:" << endl;
	
	for(int i = 0; i < 16; i++) {
		
		cout << ((b & bitMask) ? 1 : 0);
		b = b << 1;
		
	}
	
	cout << endl << "Sequenza con i-esimo bit isolato:" << endl;
	
	for(int i = 0; i < 16; i++) {
		
		cout << ((c & bitMask) ? 1 : 0);
		c = c << 1;
		
	}
	
}