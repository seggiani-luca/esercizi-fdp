//
// scrivere un programma che trova la posizione dell'elemento minimo di un vettore
//
#include <iostream>
using namespace std;

typedef double T;

int posMin(T* vett, int n) {
    T min = *vett;
    int pos = 0;
    for(int i = 1; i < n; i++) {
        if(*(vett+i) < min) {
            min = *(vett+i);
            pos = i;
        }
    }
    return pos;
}

int main() {
    int n;
    cout << "Inserire la dimensione del vettore" << endl;
    cin >> n;

    T vett[n];
    cout << "Inserire gli elementi del vettore" << endl;
    for(int i = 0; i < n; i++) {
        cin >> *(vett + i);
    }

    cout << "La posizione dell'elemento minimo del vettore e' " << posMin(vett,n);
    return 0;
}
