#include <iostream>
using namespace std;

int main() {
	
	int a;
	int* p; 
	p = &a; //puntatore ad a
	
	cin >> a;
	
	cout << "A vale: " << a << endl;
	cout << "P vale: " << p << endl;
	cout << "*P vale: " << *p << endl;
	
	int i;
	
	cin >> i;
	
	int* q = &i;
	
	p = q;
	
	cout << "I vale: " << i << endl;
	cout << "P vale: " << p << endl;
	cout << "*P vale: " << *p << endl;
	
}