#include "compito.h"
using namespace std;

VettoreSparso::VettoreSparso(int dimensione) {
    _dimensioneVettore = dimensione;
    _radice = nullptr;
}

VettoreSparso::~VettoreSparso() {
    entrata* q;
    entrata* p = _radice;
    while(p != nullptr) {
        q = p;
        p = p->pun;
        delete q;
    }
}

void VettoreSparso::set(int v, int i) { //l'inserimento viene eseguito in modo da mantenere la lista ordinata
    if(i >= _dimensioneVettore || i < 0) { //fuori range
        return;
    }
    if(v == 0) { //entrata inutile
        return;
    }
    if(_radice == nullptr) { //lista vuota
        entrata* entr = new entrata;
        entr->indice = i;
        entr->valore = v;
        entr->pun = nullptr;

        _radice = entr;
        return;
    }
    entrata* p;
    entrata* q = nullptr;
    for(p = _radice; p != nullptr && p->indice < i; p = p->pun) {
        q = p;
    }
    if(p->indice == i) { //coppia già esistente
        p->valore = v;
        return;
    }
    entrata* entr = new entrata;
    entr->indice = i;
    entr->valore = v;
    entr->pun = p;
    if(q == nullptr) { //primo elemento da sostituire
        _radice = entr;
    } else { //elemento interno da sostituire
        q->pun = entr;
    }
}

void VettoreSparso::visualizzaComeDenso() {
    cout << "< ";
    entrata* p = _radice;
    for(int i = 0; i < _dimensioneVettore; i++) {
        while(p != nullptr && p->indice < i) {
            p = p->pun;
        }
        if(p != nullptr && p->indice == i) {
            cout << p->valore << " ";
        } else {
            cout << "0 ";
        }
    }
    cout << ">" << endl;
}

void VettoreSparso::reset(int i) {
    entrata* q = nullptr;
    for(entrata* p = _radice; p != nullptr; p = p->pun) {
        if(p->indice == i) {
            if(q == nullptr) {
                _radice = p->pun;
            } else {
                q->pun = p->pun;
            }
            delete p;
            return;
        }
        q = p;
    }
    _radice = nullptr;
}


VettoreSparso& VettoreSparso::operator*=(int k) {
    if(k==0) {
        entrata* q;
        entrata* p = _radice;
        while(p != nullptr) {
            q = p;
            p = p->pun;
            delete q;
        }
        _radice = nullptr;
    } else {
        for(entrata* p = _radice; p != nullptr; p = p->pun) {
            p->valore *= k;
        }
    }
    return *this;
}

ostream& operator<<(ostream& stream, VettoreSparso& vett) {
    cout << "[" << vett._dimensioneVettore << "]";
    cout << "{";
    for(entrata* q = vett._radice; q != nullptr; q = q->pun) {
        cout << "(" << q->valore << "," << q->indice << ")";
    }
    cout << "}";
    return stream;
}
