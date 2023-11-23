//
// scrivere un programma che implementi una lista ordinata
//
#include <iostream>
using namespace std;

struct elem {
    int inf;
    elem* pun;
}; typedef elem* lista;

//funzioni di lista
void insord(lista& p0, T a) {
    lista n = new elem;
    n->inf = a;
    n->pun = nullptr;
    if(p0 == nullptr) {
        p0 = n;
        return;
    }
    if(p0->inf >= a) {
        n->pun = p0;
        p0 = n;
        return;
    }
    lista p, q;
    for(q = p0; q != nullptr && q->inf <= a; q = q->pun)
        p = q;
    if(q == nullptr) {
        p->pun = q;
    }
    n->pun = q;
    p->pun = n;
}

void dealloca(lista p0) {
    lista p;
    while(p0 != nullptr) {
        lista p = p0;
        p0 = p0->pun;
        delete p;
    }
}

void stampa(lista p0) {
    while(p0 != nullptr) {
        cout << p0->inf << " " << endl;
        p0 = p0->pun;
    }
    cout << endl;
}

int main() {
    lista l = nullptr;
    cout << "Inserisci 6 numeri" << endl;
    for(int i = 0; i < 6; i++) {
        int a;
        cin >> a;
        insord(l, a);
    }

    stampa(l);

    dealloca(l);
    return 0;
}