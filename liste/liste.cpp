#include <iostream>
using namespace std;

typedef int T;

struct elem {
    T inf;
    elem* pun;
};
typedef elem* lista;

//funzioni di lista
void instesta(lista& p0, T a) {
    lista p = new elem;
    p->inf = a;
    p->pun = p0;
    p0 = p;
}

bool esttesta(lista& p0, int& a) {
    lista p = p0;
    if(p0 == nullptr) return false;
    a = p0->inf;
    p0 = p0->pun;
    delete p;
    return true;    
}

void insfondo(lista& p0, T a) {
    lista p, q;
    for(q = p0; q != nullptr; q = q->pun)
        p = q;
    q = new elem;
    q->inf = a;
    q->pun = nullptr;
    if(p0 == nullptr) {
        p0 = q;
    } else {
        p->pun = q;
    }
}

bool estfondo(lista& p0, T& a) {
    if(p0 == nullptr) return false;
    lista p = nullptr;
    lista q;
    for(q = p0; q->pun != nullptr; q = q->pun)
        p = q;
    a = q->inf;
    if(q == p0) {
        p0 = nullptr;
    } else {
        p->pun = nullptr;
    }
    delete q;
    return true;
}

bool est(lista& p0, T a) {
    lista p = nullptr;
    lista q;
    for(q = p0; q->pun != nullptr && q->inf != a; q = q->pun)
        p = q;
    if(q == 0)
        return false;
    if(q == p0) {
        p0 = q->pun;
    } else {
        p->pun = q->pun;
    }
    delete q;
    return true;
}

bool estord(lista& p0, T a) {
    lista p = nullptr;
    lista q;
    for(q = p0; q->pun != nullptr && q->inf < a; q = q->pun)
        p = q;
    if(q == 0)
        return false;
    if(q == p0 || q->inf > a) {
        p0 = q->pun;
    } else {
        p->pun = q->pun;
    }
    delete q;
    return true;
}

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

void stampaLista(lista& p) {
    while(p != nullptr) {
        int a;
        if(esttesta(p, a)) 
            cout << a << " ";
    }
    cout << endl;
}

void deallocaLista(lista& p0) {
    lista p = p0;
    lista q;
    while(p != nullptr) {
        q = p->pun;
        delete p;
        p = q;
    }
    p0 = nullptr;
    cout << "Dealloco e tolgo il disturbo" << endl;
}

int main() {
    lista l = nullptr;
    cout << "Inserisci 10 interi." << endl;
    for(int i = 0; i < 10; i++) {
        int a;
        cin >> a;
        insfondo(l, a);
    }

    cout << "Inserisco un elemento 8 mantenendo l'ordine di lista..." << endl;
    insord(l, 8);

    cout << "Rimuovo un presunto elemento = 5..." << endl;
    est(l, 5);

    cout << "La lista memorizzata e':" << endl;
    stampaLista(l);
    cout << "La lista adesso e':" << endl;
    stampaLista(l);
    deallocaLista(l);
    return 0;
}       