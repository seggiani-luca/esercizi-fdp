#include <iostream>
using namespace std;

int fatt(int arg);

int main() {
	
	int n;
	cout << "Inserisci un n di cui calcolare il fattoriale: " << endl;
	cin >> n;

	cout << "Il fattoriale di " << n << " e': " << fatt(n) << endl;
	
	return 0;
}

int fatt(int arg) {
	
	if(arg==0) return 1;
	return arg * fatt(arg-1);
}