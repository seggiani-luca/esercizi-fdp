//
// scrivere un programma che calcoli massimo, minimo e media di tre numeri in una sola funzione
//
#include <iostream>
using namespace std;

void func(int a, int b, int c, int& max, int& min, double& med) {

    med = (a+b+c) / 3.0;
    min = a;
    max = a;
    if(b>max)
        max = b;
    if(c>max)
        max = c;
    if(b<min)
        min = b;
    if(c<min)
        min = c;
}

int main() {
    int a, b, c;
    cout << "Inserisci tre numeri: " << endl;
    cin >> a >> b >> c;

    int max;
    int min;
    double med;
    func(a, b, c, max, min, med);

    cout << "Il massimo e' " << max << ", il minimo e' " << min << " e la media e' " << med << "." << endl;

    return 0;
}