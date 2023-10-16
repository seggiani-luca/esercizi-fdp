#include <iostream>
using namespace std;

int main() {
	
	int array[10];
	
	cout << array[11] << endl; //ERRORE LOGICO: valore fuori dall'array, possibile segfault
	
	array[11] = 2;
	
	cout << array[11] << endl; //effettivamente viene scritto e letto un valore, ma non si sa dove
	
	return 0;
	
}