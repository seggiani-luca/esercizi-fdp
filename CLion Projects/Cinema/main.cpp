#include <iostream>
//#include "compito.h"
using namespace std;

int main(){
// PRIMA PARTE
    Cinema c(3,7,"Moderno");
    c.prenota('A',4);
    c.prenota('C',1);
    c.prenota('C',2);
    c.prenota('C',3);
    c.prenota('C',4);
    c.prenota('C',5);
    c.prenota('C',6);
    c.prenota('C',7);
    c.prenota('B',4);
    c.stampa();
    c.cancella('B',4);
    c.stampa();
// SECONDA PARTE
    cout << "Il numero di posti liberi in c e': " << c.quantiLiberi() << endl;
    c.prenotaAdiacenti(4);
    c.stampa();
    return 0;
}