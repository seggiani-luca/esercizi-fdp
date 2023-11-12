#include <iostream>
using namespace std;

typedef int T;

struct eleMenu { char* stringa; void (*funzione) (T*, int); };
const int numElementi = 4;

void scambia(T& elem1, T& elem2) {
    T aux = elem1;
    elem1 = elem2;
    elem2 = aux;
}

void selectionSortRicorsiva(T* array, int lung) {
    int min = *array;
    int posMin = 0;
    for(int i = 1; i < lung; i++) {
        if(*(array + i) < min) {
            min = *(array + i);
            posMin = i;
        }
    }
    scambia(*array, *(array + posMin));

    if(lung > 1) {
        selectionSortRicorsiva(array + 1, lung - 1);
    }
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

void bubbleSort(T* array, int lung) {
    for(int i = 0; i < lung; i++) {
        for(int j = lung - 1; j > i; j--) {
            if(*(array + j) < *(array + j - 1))
                scambia(*(array+j), *(array + j - 1));
        }
    }
}

void bubbleSortOttimizzato(T* array, int lung) {
    for(int i = 0; i < lung; i++) {
        bool salta = true;
        for(int j = lung - 1; j > i; j--) {
            if(*(array + j) < *(array + j - 1)) {
                scambia(*(array+j), *(array + j - 1));
                salta = false;
            }
        }
        if(salta)
            return;
    }
}

void stampaArray(T* array, int lung) {
    for(int i = 0; i < lung; i++) {
        cout << *(array + i) << " ";
    }
    cout << endl;
}

//helper menu
int stampaMenu(eleMenu menu[]) {
    for(int i = 0; i < numElementi; i++) {
        cout << i << " " << menu[i].stringa << endl;
    }
    int i;
    cout << "Fai la tua scelta." << endl;
    cin >> i;
    return i;
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

    eleMenu menu[numElementi];
    menu[0].stringa = "Selection sort ricorsiva";
    menu[0].funzione = selectionSortRicorsiva;
    menu[1].stringa = "Selection sort iterativa";
    menu[1].funzione = selectionSortIterativa;
    menu[2].stringa = "Bubble sort";
    menu[2].funzione = bubbleSort;
    menu[3].stringa = "Bubble sort ottimizzata";
    menu[3].funzione = bubbleSortOttimizzato;

    int i = stampaMenu(menu);
    (*menu[i].funzione)(array, lung);

    //array ordinata
    cout << "L'array ordinata e' ";
    stampaArray(array, lung);

    return 0;
}
