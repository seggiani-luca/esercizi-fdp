#include <iostream>
using namespace std;

int main() {
	int i,j;
	cin >> i >> j;
	//int& pi; ERRORE: il riferimento deve essere dichiarato ed inizializzato
	int* pi;
	
	if(i>=j) {
		pi = &i;
	} else {
		pi = &j;
	}
	
	(*pi)++;
	
	cout << "&pi: " << *pi << endl;
	
	cout << "i: " << i << endl;
	cout << "j: " << j << endl;
	
	return 0;
}
