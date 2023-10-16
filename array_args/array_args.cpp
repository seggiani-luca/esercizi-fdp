#include <iostream>
using namespace std;

int multiply(int arg[]) {
	
	for(int i = 0; i < 5; i++) {
		arg[i] *= 2;		
	}
	
}

int main() {
	
	int ar[5];
	
	for(int i = 0; i < 5; i++) {	
		cin >> ar[i];	
	}
	
	multiply(ar);
	
	for(int i = 0; i < 5; i++) {
		cout << ar[i];
	}
	
	return 0;
	
}