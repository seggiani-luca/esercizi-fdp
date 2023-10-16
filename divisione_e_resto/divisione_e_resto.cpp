/*
 * scrivere un programma che divida due numeri e mostri resto e quoziente a video
*/
#include <iostream>
using namespace std;

int main() {
    start:
    unsigned int a;
    unsigned int b;

    cout << "Inserisci il dividendo" << endl;
    cin >> a;

    cout << "Inserisci il divisore (deve essere diverso da 0)" << endl;
    cin >> b;

    if(b==0) {
        cout << "Il divisore deve essere diverso da zero" << endl;
        goto start;
    }

    unsigned int q = a/b;
    unsigned int r = a%b;

    cout << "La parte intera del quoziente e': " + to_string(q) << endl
    << "Il resto della divisione intera e': " + to_string(r);

    return 0;
}