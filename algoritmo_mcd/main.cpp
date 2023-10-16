#include <iostream>
using namespace std;

int main() {
    int a;
    cout << "Inserisci a" << endl;
    cin >> a;
    if(a<0)
        a=0;

    int constA = a; //mantieni a in quando l'algoritmo ne cambia il valore

    int b;
    cout << "Inserisci b" << endl;
    cin >> b;
    if(b<0)
        b=0;

    int constB = b; //idem

    int r = a%b;
    int lastR = b;

    cout << "m = " << a << ", ";
    cout << "n = " << b << endl;

    while(r > 0) {

        a = b;
        b = r;
        lastR = r;
        r = a%b;

        cout << "m = " << a << ", ";
        cout << "n = " << b << endl;

    }

    cout << "Il M.C.D. fra " + to_string(constA) + " e " + to_string(constB) + " e' " + to_string(lastR);

    return 0;
}
