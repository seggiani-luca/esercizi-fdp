/*
 * scrivere un programma che legga un numero da tastiera e mostri a video il suo triplo.
*/
#include <iostream>
using namespace std;

int main() {
    unsigned int numero;
    cout<<"Inserisci un numero:"<<endl; //chiede all'utente un numero
    cin>>numero;

    numero *= 3;

    cout<< "Il triplo del valore inserito e': " + to_string(numero);
    return 0;
}
