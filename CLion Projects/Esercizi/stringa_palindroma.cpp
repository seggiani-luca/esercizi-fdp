//
// scrivere un programma che rileva se una stringa e' palidroma
//
#include <iostream>
#include <cstring>
using namespace std;

bool palindroma(char* stringa, int n) {
    int len = strlen(stringa);
    int halfLen = len/2;
    for(int i = 0; i < halfLen; i++) {
        int j = len - i - 1;
        if(stringa[i] != stringa[j])
            return false;
    }
    return true;
}

int main() {
    int MAX_NUM = 40;
    char stringa[MAX_NUM + 1];
    cout << "Inserisci una parola: " << endl;
    cin >> stringa;

    if(palindroma(stringa, MAX_NUM)) {
        cout << "La stringa e' palindroma" << endl;
    } else {
        cout << "La stringa non e' palindroma, cribbio!" << endl;
    }

    return 0;
}