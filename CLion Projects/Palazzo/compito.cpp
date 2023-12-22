#include "compito.h"
#include <iostream> //per la stampa

Palazzo::Palazzo(int n) {
    max = n;
    terra = nullptr;
    aggiungi();
}

Palazzo::~Palazzo() {
    Piano* q = terra;
    while(q != nullptr) {
        Piano* p = q;
        q = q->pun;
        delete p;
    }
}

Palazzo::Palazzo(Palazzo &p) {
    max = p.max;
    terra = nullptr;
    Piano* q = p.terra;
    while(q != nullptr) {
        aggiungi(*q);
        q = q->pun;
    }
}

void Palazzo::aggiungi(Piano& t) {
    Piano* n = new Piano(t);
    if(terra == nullptr) {
        terra = n;
        return;
    }
    Piano* q = terra;
    Piano* p;
    while(q != nullptr) {
        p = q;
        q = q->pun;
    }
    p->pun = n;
}

void Palazzo::aggiungi() {
    if(piani() > max)
        return;
    if(terra == nullptr) {
        Piano* n = new Piano();
        terra = n;
        return;
    }
    Piano* q = terra;
    Piano* p;
    int conto = 1;
    while(q != nullptr) {
        p = q;
        q = q->pun;
        conto++;
    }
    Piano* n = new Piano(conto);
    p->pun = n;
}

int Palazzo::piani() {
    int count = 0;
    Piano* q = terra;
    while(q != nullptr) {
        q = q->pun;
        count++;
    }
    return count;
}

using namespace std;
void Palazzo::stampa() {
    cout << "<" << piani() << ">" << endl;
    Piano* q = terra;
    int count = 0;
    while(q != nullptr) {
        cout << "Piano " << count + 1 << ": ";
        for(int i = 0; i < q->len; i++) {
            if(q->finestre[i]) {
                cout << "Aperta ";
            } else {
                cout << "Chiusa ";
            }
        }
        q = q->pun;
        count++;
        cout << endl;
    }
}

void Palazzo::cambia(int i, int j) {
    i--;
    j--;
    if(i < 0 || i > piani())
        return;
    if(j > i)
        return;
    int count = 0;
    Piano* q = terra;
    while(q != nullptr && count != i) {
        q = q->pun;
        count++;
    }
    q->cambia(j);
}

int Palazzo::operator!() {
    int conto = 0;
    Piano* q = terra;
    while(q != nullptr) {
        for(int i = 0; i < q->len; i++) {
            if(q->finestre[i]) {
                conto++;
            }
        }
        q = q->pun;
    }
    return conto;
}

void Palazzo::operator%=(Palazzo &p) {
    if(piani() != p.piani()) {
        return;
    }
    Piano* q = p.terra;
    Piano* t = terra;
    while(q != nullptr) {
        for(int i = 0; i < q->len; i++) {
            if(t->finestre[i] && !q->finestre[i]) {
                t->finestre[i] = false;
            }
        }
        q = q->pun;
        t = t->pun;
    }
}

//

Piano::Piano(int n) {
    //inizializza una finestra chiusa
    finestre = nullptr;
    scala(n);
    len = n;
    pun = nullptr;
}

Piano::~Piano() {
    delete[] finestre;
}

Piano::Piano(Piano &p) {
    len = p.len;
    finestre = new bool[len];
    for(int i = 0; i < p.len; i++) {
        finestre[i] = p.finestre[i];
    }
    pun = nullptr;
}

void azzera(bool* b, int n) {
    for(int i = 0; i < n; i++) {
        b[i] = false;
    }
}

void Piano::scala(int n) {
    if(finestre == nullptr) {
        finestre = new bool[n];
        azzera(finestre, n);
        return;
    }
    bool* nuova = new bool[n];
    azzera(nuova, n);
    for(int i = 0; i < len; i++) {
        nuova[i] = finestre[i];
    }
    len = n;
    delete finestre;
    finestre = nuova;
}

void Piano::cambia(int j) {
    if(j > len) {
        scala(j);
    }
    finestre[j] = !finestre[j];
}
