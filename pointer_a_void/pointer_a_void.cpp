#include <iostream>
using namespace std;

//void (*pointer)(void);
struct struttura { void (*pointer)(void); };	
void funzione() {
	cout << "Eccomi!" << endl;
}
	
int main() {
	struttura struttura1;
	struttura1.pointer = funzione;
	(*struttura1.pointer)();
	return 0;
}