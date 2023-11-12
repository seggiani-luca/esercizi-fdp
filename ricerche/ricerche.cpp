#include <iostream>
using namespace std;

typedef int T;

void scambia(T& elem1, T& elem2) {
    T aux = elem1;
    elem1 = elem2;
    elem2 = aux;
}

int riclin(T* array, T& k, int lung) {
    for(int i = 0; i < lung; i++) {
        if(*(array + i) == k)
            return i;
    }
    return 0;
    cerr << "Elemento non trovato!" << endl;
}

int ricbin(T* array, T& k, int infe, int supe) {
    if(supe < infe) {
        return 0;
        cerr << "Elemento non trovato!" << endl;
    }
    int med = (supe + infe) / 2;
    T eleMed = *(array + med);
    if(eleMed == k)
        return med;
    if(eleMed > k) {
        return ricbin(array, k, infe, med - 1);
    } else { //eleMed > k
        return ricbin(array, k, med + 1, supe);
    }
    return 0;
    cerr << "Elemento non trovato!" << endl;
}

void selectionSortIterativa(T* array, int lung) {
    for(int i = 0; i < lung; i++) {
        int min = *(array + i);
        int posMin = i;
        for(int j = i + 1; j < lung; j++ ) {
            if(*(array + j) < min) {
                min = *(array + j);
                posMin = j;
            }
        }
        scambia(*(array+i), *(array+posMin));
    }
}

void stampaArray(T* array, int lung) {
    for(int i = 0; i < lung; i++) {
        cout << *(array + i) << " ";
    }
    cout << endl;
}

int main() {

    unsigned lung;
    do {
        cout << "Quanti elementi? " << endl;
        cin >> lung;
    } while(lung < 1);

    T array[lung];

    cout << "Inserisci i " << lung << " elementi della lista" << endl;
    for(int i = 0; i < lung; i++) {
        cin >> *(array + i);
    }

    int k;
    cout << "Quale elemento stai cercando? " << endl;
    cin >> k;

    int tipo;
    cout << "Ricerca lineare (1) o binaria (0)?" << endl;
    cin >> tipo;

    int pos;
    if(tipo) {
        pos = riclin(array, k, lung);
    } else {
        selectionSortIterativa(array, lung);
        cout << "L'array ordinata e': ";
        stampaArray(array, lung);

        pos = ricbin(array, k, 0, lung);
    }

    //array ordinata
    cout << "L'elemento si trova in posizione " << pos << endl;

    return 0;
}
