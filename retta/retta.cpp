/*
 * scrivere un programma che data ascissa e parametri, calcoli l'ordinata di una retta y = ax + b.
*/
#include <iostream>
using namespace std;

int main() {
    double a; //ordinata
    double b; //origine
    double x;

    cout<<"Inserisici il valore di a"<<endl;
    cin>>a;

    cout<<"Inserisici il valore di b"<<endl;
    cin>>b;

    cout<<"Inserisci il valore di x"<<endl;
    cin>>x;

    double y = a*x + b; //y=mx+q

    cout<<"Il valore dell'ordinata y e': " << y;
	
	//ciao alessio

    return 0;
}
