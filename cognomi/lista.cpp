#include <cstring>
#include "lista.h"
using namespace std;

//definizioni funzioni di lista
void inserisci(lista& p0, scheda* a) {
    lista n = new elem;
    n->inf = a;
    n->pun = nullptr;
    if(p0 == nullptr) {
        p0 = n;
        return;
    }
    if(strcmp(p0->inf->cognome, a->cognome) >= 0) {
        n->pun = p0;
        p0 = n;
        return;
    }
    lista p, q;
    for(q = p0; q != nullptr && strcmp(q->inf->cognome, a->cognome) < 0; q = q->pun)
        p = q;
    if(q == nullptr) {
        p->pun = q;
    }
    n->pun = q;
    p->pun = n;
}

void deallocaScheda(scheda* s);
int lunghezza(lista p);

bool estrai(lista& p0, int i) {
    if(p0 == nullptr || i > (lunghezza(p0) - 1))
        return false;
    if(i == 0) {
        lista p = p0;
        p0 = p0->pun;
        deallocaScheda(p->inf);
        delete p;
        return true;
    }
    int count = 0;
    lista p, q;
    for(q = p0; q != nullptr && count != i; q = q->pun) {
        p = q;
        count++;
    }
    if(q == nullptr) {
        deallocaScheda(q->inf);
        delete q;
        p->pun = nullptr;
    } else {
        p->pun = q->pun;
        deallocaScheda(q->inf);
        delete q;
    }
    return true;
}

void dealloca(lista& p0) {
    elem* p = p0;
    elem* q;
    while(p != nullptr) {
        q = p->pun;
        deallocaScheda(p->inf);
        delete p;
        p = q;
    }
    p0 = nullptr;
}

//funzioni di utilità
void deallocaScheda(scheda* s) {
    delete[] s->nome;
    delete[] s->cognome;
}

int lunghezza(lista p) {
    int i = 0;
    while(p != nullptr) {
        p = p->pun;
        i++;
    }
    return i;
}