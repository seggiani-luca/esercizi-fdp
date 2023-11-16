//
// scrivere un programma che implementi una lista
//
#include <iostream>
using namespace std;

struct elem {
    int inf;
    elem* pun;
}; typedef elem* lista;

//funzioni di lista
void insfondo(lista& p0, int a) {
    if(p0 == nullptr) {
        p0 = new elem;
        p0->inf = a;
        p0->pun = nullptr;
        return;
    }
    lista p, q;
    for(q = p0; q != nullptr; q = q->pun)
        p = q;
    q = new elem;
    p->pun = q;
    q->inf = a;
    q->pun = nullptr;
}

void instesta(lista& p0, int a) {
    if(p0 == nullptr) {
        p0 = new elem;
        p0->inf = a;
        p0->pun = nullptr;
        return;
    }
    lista q = new elem;
    q->inf = a;
    q->pun = p0;
    p0 = q;
}

void stampa(lista p0) {
    while(p0 != nullptr) {
        cout << p0->inf << " " << endl;
        p0 = p0->pun;
    }
    cout << endl;
}

void dealloca(lista p0) {
    lista p = nullptr;
    while(p0 != nullptr) {
        lista p = p0;
        p0 = p0->pun;
        delete p;
    }
}

bool estrai(lista& p0, int a) {
    if(p0 == nullptr)
        return false;
    lista p, q;
    for(q = p0; q != nullptr & q->inf != a; q = q->pun)
        p = q;
    if(q == nullptr)
        return false;
    p->pun = q->pun;
    delete q;
    return true;
}

int main() {
    lista l;
    insfondo(l, 50);
    insfondo(l, 60);
    instesta(l, 70);

    stampa(l);

    estrai(l, 50);

    stampa(l);

    dealloca(l);
    return 0;
}