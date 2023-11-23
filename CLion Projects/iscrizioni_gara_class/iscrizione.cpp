#include <iostream>
#include "iscrizione.h"

using namespace std;

void lista::init() {
    l = nullptr;
}

void lista::visualizza() {
    elem* p = l;
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

bool lista::cerca(char* nome) {
    elem* q;
    for(q = l; q != nullptr; q = q->pun) {
        if(confronta(q->nome, nome))
            return true;
    }
    return false;
}

bool lista::elimina(char* nome) {
    if(l == nullptr) {
        return false;
    }

    if(confronta(l->nome, nome)) {
        elem* p = l;
        l = l->pun;
        delete p;
        return true;
    }

    elem* q, *p;
    for(q = l; q != nullptr | (confronta(q->nome, nome)); q = q->pun)
        p = q;
    p->pun = q->pun;
    delete q;

    return true;
}

void lista::aggiungi(char* nome, int pettorale) {
    if(cerca(nome))
        return;

    //cerco pettorale
    elem* q;
    for(q = l; q != nullptr; q = q->pun) {
        if(q->pettorale == pettorale)
            return;
    }

    elem* n = new elem;
    n->pun = nullptr;
    copy(nome, n->nome);
    n->pettorale = pettorale;

    if(l == nullptr) {
        l = n;
        return;
    }

    elem* p;
    for(q = l; q != nullptr; q = q->pun)
        p = q;
    p->pun = n;
}
