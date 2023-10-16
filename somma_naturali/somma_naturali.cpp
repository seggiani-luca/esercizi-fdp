#include <iostream>
using namespace std;

int trova_naturali(int a) {
	
	int i = 0;
	int j = 0;
	do {
		i += (i+1);
		j++;
	} while (i < a);
	
	return j;
}

int main() {
	
	int a;
	cout << "Inserisci un numero" << endl;
	cin >> a;
	
	cout << "Puoi sommare i primi " << trova_naturali(a)
	<< " naturali prima di superare " << a << endl;

	return 0;
}