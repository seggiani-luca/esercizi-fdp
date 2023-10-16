#include <iostream>
using namespace std;

void scambia(int aa[5], int bb[5]) {
	for(int i = 0; i < 5; i++) {
		int t = *(aa+i);
		*(aa + i) = *(bb + i);
		*(bb + i) = t;
	}
}

int main() {
	
	int a[5];
	int b[5];
	
	cout << "Inserisci elementi di a: " << endl;
	for(int i = 0; i < 5; i++) {
		cin >> a[i];
	}
	cout << "Inserisci elementi di b: " << endl;
	for(int i = 0; i < 5; i++) {
		cin >> b[i];
	}
	
	scambia(a,b);
	
	cout << "Array a: " << endl;
	for(int i = 0; i < 5; i++) {
		cout << a[i] << endl;
	}
	cout << "Array b: " << endl;
	for(int i = 0; i < 5; i++) {
		cout << b[i] << endl;
	}
	
}