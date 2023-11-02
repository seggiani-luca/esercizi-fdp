//
// scrivere un programma che trova il massimo di un vettore
//
#include <iostream>
using namespace std;

typedef double T;

T max(T* vett, int n) {
    T max = *vett;
    for(int i = 1; i < n; i++) {
        if(*(vett+i) > max)
            max = *(vett+i);
    }
    return max;
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

    cout << "Il massimo del vettore e' " << max(vett,n);
    return 0;
}
