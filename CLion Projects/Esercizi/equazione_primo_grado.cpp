/*
 * scrivere un programma che risolva un'equazione di tipo ax + b = 0.
*/
#include <iostream>
using namespace std;

int main() {

    double a=0;
    double b=0;

    while(a==0) {
        cout<<"Inserisci il valore di a (deve essere diverso da 0)"<<endl;
        cin>>a;
    }
    while(b==0) {
        cout<<"Inserisci il valore di b (deve essere diverso da 0)"<<endl;
        cin>>b;
    }

    double x = -b/a;

    cout<<"La soluzione dell'equazione e': "<<x;

    return 0;
}
