#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Inserisci n:" << endl;
    cin >> n;
    if(n < 1) {
        cout << "Numero non valido" << endl;
        return 0;
    }
    int* v = new int[n];
    cout << "Inserisci " << n << " numeri:" << endl;
    for(int i = 0; i < n; i++)
        cin >> v[i];
    int max = v[0];
    for(int i = 1; i < n; i++)
        max = (v[i] > max)?v[i]:max;
    for(int i = 0; i < n; i++)
        v[i] += max;
    int mul = v[0];
    for(int i = 1; i < n; i++)
        mul *= v[i];
    cout << "Risultato del calcolo:" << endl;
    cout << mul;
    delete[] v;
    return 0;
}