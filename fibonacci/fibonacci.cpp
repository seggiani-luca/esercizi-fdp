#include <iostream>
using namespace std;

int fib(int i) { //uso una funzione ricorsiva
	if(i==0) return 0;
	if(i==1) return 1;
	return (fib(i-2)+fib(i-1));
}

int main() {
		
	int n;
	cout << "Quanti numeri di fibonacci vuoi stampare?" << endl;
	cin >> n;
	
	for(int i = 0; i < n; i++) {
		if(i == n-1) {
			cout << fib(i) << endl;
			continue;
		}
		cout << fib(i) << ", ";
	}
	
	return 0;
}
