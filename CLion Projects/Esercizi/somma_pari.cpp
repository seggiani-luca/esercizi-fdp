//
// scrivere un programma che stampa pari quando la somma degli elementi di un vettore e' pari
//
#include <iostream>
using namespace std;

int MAX_NUM = 10;

bool pari(int* vett) {
    int val = 0;
    for(int i = 0; i < MAX_NUM; i++) {
        val += *(vett + i);
    }
    if(val%2 == 0)
        return true;
    return false;
}

int main() {
    int vett[MAX_NUM];
    cout << "Inserisci 10 interi" << endl;
    for(int i = 0; i < MAX_NUM; i++) {
        cin >> *(vett + i);
    }
    if(pari(vett))
        cout << "Pari!" << endl;
    return 0;
}
