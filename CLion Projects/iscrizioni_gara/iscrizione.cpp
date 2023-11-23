#include <iostream>
#include "iscrizione.h"

using namespace std;

typedef elem* lista;

void init(elem*& l) {
    l = nullptr;
}

void visualizza(elem*& l) {
    lista p = l;
    cout << "Atleti iscritti: " << endl;
    while(p != nullptr) {
        cout << p->nome << ", " << p->pettorale << endl;
        p = p->pun;
    }
    cout << endl;
}

void copy(char* src, char* dest) {
    while(*src != '\0') {
        *dest = *src;
        src++;
        dest++;
    }
}

bool confronta(char* str1, char* str2) {
    while(*str1 != '\0' & *str2 != '\0') {
        if(*str1 != *str2)
            return false;
        str1++;
        str2++;
    }
    return true;
}

bool cerca(elem*& l, char* nome) {
    elem* q;
    for(q = l; q != nullptr; q = q->pun) {
        if(confronta(q->nome, nome))
            return true;
    }
    return false;
}

bool elimina(elem*& l, char* nome) {
    if(l == nullptr) {
        return false;
    }

    if(confronta(l->nome, nome)) {
        lista p = l;
        l = l->pun;
        delete p;
        return true;
    }

    lista q, p;
    for(q = l; q != nullptr | (confronta(q->nome, nome)); q = q->pun)
        p = q;
    p->pun = q->pun;
    delete q;

    return true;
}

void aggiungi(elem*& l, char* nome, int pettorale) {
    if(cerca(l, nome))
        return;

    elem* n = new elem;
    n->pun = nullptr;
    copy(nome, n->nome);
    n->pettorale = pettorale;

    if(l == nullptr) {
        l = n;
        return;
    }

    lista q, p;
    for(q = l; q != nullptr; q = q->pun)
        p = q;
    p->pun = n;
}