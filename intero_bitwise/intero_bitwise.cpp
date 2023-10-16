#include <iostream>
using namespace std;

unsigned short mask = 0x8000; //1000 0000 0000 0000;

int main() {
	
	unsigned short n;
	cout << "Inserisci un numero naturale maggiore di uno" << endl;
	cin >> n;
		
	for(int i = 0; i < 16; i++) {
		
		cout << ((n & mask) ? 1 : 0);
		n = n << 1;
		
	}
	
}