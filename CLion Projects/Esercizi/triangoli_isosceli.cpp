//
// Scrivere un programma che stampi triangoli isosceli di lato n a video
//
#include <iostream>
using namespace std;

int main() {
    int n;
    do {
        cout << "Lato? " << endl;
        cin >> n;
    } while (n<=0);
    int h = n/2 + 1;
    cout << "Triangolo isoscele rovesciato" << endl;
    for(int j = 0; j < h; j++) {
        for(int k= 0; k < j; k++) {
            cout << "   ";
        }
        for(int k = 0; k < n - j*2; k++) {
            cout << "*  ";
        }
        cout << endl;
    }
    cout << endl << "Triangolo isoscele ruotato" << endl;
    for(int j = 0; j < n; j++) {
        if(j < n / 2) {
            for(int k = 0; k < j+1; k++) {
                cout << "*   ";
            }
        } else {
            for(int k = 0; k < n/2+h-j; k++) {
                cout << "*   ";
            }
        }
        cout << endl;
    }
    return 0;
}
