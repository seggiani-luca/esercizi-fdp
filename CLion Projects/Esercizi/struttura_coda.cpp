//
// implementa una struttura di tipo coda
//
#include <iostream>
using namespace std;

const int SIZE = 10;

struct coda {
    int front;
    int back;
    int queue[SIZE];
};
//inizio funzioni coda
void init(coda& c) {
    c.front = 0;
    c.back = 0;
}

bool empty(coda& c) {
    return (c.front == c.back);
}

bool full(coda& c) {
    if(empty(c))
        return false;
    return ((c.front+1) % SIZE == c.back);
}

bool push(coda& c, int n) {
    if(full(c))
        return false;
    *(c.queue + c.front) = n;
    c.front = (c.front + 1) % SIZE;
    return true;
}

bool pop(coda &c, int& n) {
    n = *(c.queue + c.back);
    c.back = (c.back + 1) % SIZE;
    return true;
}
//fine funzioni coda

void leggiCoda(coda& c) {
    int n;
    while(pop(c, n)) {
        cout << n << " ";
    }
}

int main() {
    coda p;
    init(p);
    coda d;
    init(d);

    cout << "Inserisci " << SIZE << " interi." << endl;
    for(int i = 0; i < SIZE; i++) {
        int n;
        cin >> n;
        if(n%2==0) {
            push(p, n);
        } else {
            push(d, n);
        }
    }

    cout << endl << "Numeri pari: " << endl;
    leggiCoda(p);
    cout << endl << "Numeri dispari: " << endl;
    leggiCoda(d);
    return 0;
}

