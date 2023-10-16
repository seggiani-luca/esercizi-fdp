#include <iostream>
using namespace std;

int function1(int arg);
void function2(int& arg);

int main() {
	
	int a = 1;
	a = function1(a);

	cout << a << endl;
	
}

int function1(int arg) {
	
	int& rarg = arg;
	
	function2(rarg);
	
	return arg;
	
}

void function2(int& reference) {
	
	reference = 2;
	
}