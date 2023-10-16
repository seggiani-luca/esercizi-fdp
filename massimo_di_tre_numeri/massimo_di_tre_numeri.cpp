#include <iostream>
using namespace std;

int main() {
	
	int a,b,c;
	cout << "Inserisci tre numeri: " << endl;
	cin >> a >> b >> c;
	
	int max = a;
	if(b>max)
		max = b;
	if(c>max)
		max = c;
	
	cout << "Il massimo dei tre numeri e': " << max << endl;
	
	return 0;
	
}