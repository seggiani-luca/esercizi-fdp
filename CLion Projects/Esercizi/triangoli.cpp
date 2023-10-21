//
// Scrivere un programma che stampi triangoli di lato n a video
//
#include <iostream>
using namespace std;

int main() {
    int n;
    do {
        cout << "Lato? " << endl;
        cin >> n;
    } while (n<=0);
    cout << "Triangolo rettangolo" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i+1; j++) {
            cout << "*  ";
        }
        cout << endl;
    }
    cout << endl << "Triangolo rettangolo rovesciato" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            cout << "   ";
        }
        for(int j = 0; j < n-i; j++) {
            cout << "*  ";
        }
        cout << endl;
    }
    return 0;
}
