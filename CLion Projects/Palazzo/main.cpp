#include "compito.h"
#include <iostream>
using namespace std;
int main()
{
// PRIMA PARTE:
    cout << "Test del costruttore:" << endl;
    Palazzo p1(5);
    p1.stampa();
    cout << endl;
    cout << "Test del costruttore di copia:" << endl;
    Palazzo p2(p1);
    p2.stampa();
    cout << endl;
    cout << "Test della aggiungi:" << endl;
    p1.aggiungi();
    p1.aggiungi();
    p1.stampa();
    cout << endl;
// SECONDA PARTE:
    cout << "Test del distruttore:" << endl;
    {
    Palazzo p(20);
    }
    cout << "(p e' stato distrutto)" << endl;
    cout << endl << "Test della cambia:" << endl;
    p1.cambia(2, 1);
    p1.cambia(3, 3);
    p1.stampa();
    cout << endl;
    cout << "Test operator! :" << endl;
    cout << !p1 << endl;
    cout << endl << "Test operator%= :" << endl;
    Palazzo p3(5);
    p3.aggiungi();
    p3.aggiungi();
    p1 %= p3;
    p1.stampa();
    cout << endl;
    return 0;
}