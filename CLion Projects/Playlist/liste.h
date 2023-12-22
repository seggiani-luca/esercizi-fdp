//l'header liste.h contiene la definizione di lista e diverse funzioni di utilità

template<typename T>
class lista {
    struct elem {
        T inf;
        elem* pun;
    };
    elem* testa;
    
    public:
        lista() {
            testa = nullptr;
        }
        ~lista() {
            elem* p = testa;
            elem* q;
            while(p != nullptr) {
                q = p->pun;
                delete p;
                p = q;
            }
            testa = nullptr;
        }
        int lunghezza() {
            int i = 0;
            elem* p = testa;
            while(p != nullptr) {
                p = p->pun;
                i++;
            }
            return i;
        }
        bool estrai_oggetto(T inf) {
            elem* p = nullptr;
            elem* q;
            for(q = testa; q->pun != nullptr && q->inf != inf; q = q->pun)
                p = q;
            if(q == nullptr)
                return false;
            if(q == testa) {
                testa = q->pun;
            } else {
                p->pun = q->pun;
            }
            delete q;
            return true;
        }
        void inserisci_ordinato(T inf) {
            elem* n = new elem;
            n->inf = inf;
            n->pun = nullptr;
            if(testa == nullptr) {
                testa = n;
                return;
            }
            if(testa->inf >= inf) {
                n->pun = testa;
                testa = n;
                return;
            }
            elem* p;
            elem* q;
            for(q = testa; q != nullptr && q->inf <= inf; q = q->pun)
                p = q;
            if(q == nullptr) {
                p->pun = n;
            }
            n->pun = q;
            p->pun = n;
        }
        void inserisci_indice(T inf, int i) {
            elem* n = new elem;
            n->inf = inf;
            n->pun = nullptr;
            if(i <= -1 || i >= lunghezza() + 1)
                return;
            if(i == 0) {
                n->pun = testa;
                testa = n;
                return;
            }
            int count = 0;
            elem* p;
            elem* q;
            for(q = testa; q != nullptr && count != i; q = q->pun) {
                p = q;
                count++;
            }
            if(q == nullptr) {
                p->pun = n;
            } else {
                n->pun = q;
                p->pun = n; 
            }
        }
        void inserisci_testa(T inf) {
            inserisci_indice(inf, 0);
        }
        void inserisci_coda(T inf) {
            inserisci_indice(inf, lunghezza());
        }
        bool estrai_indice(T& dest, int i) {
            if(testa == nullptr || i > lunghezza())
                return false;
            if(i == 0) {
                elem* p = testa;
                dest = testa->inf;
                testa = testa->pun;
                delete p;
                return true;
            }
            int count = 0;
            elem* p;
            elem* q;
            for(q = testa; q != nullptr && count != i; q = q->pun) {
                p = q;
                count++;
            }
            if(q == nullptr) {
                dest = q->inf;
                delete q;
                p->pun = nullptr;
            } else {
                dest = q->inf;
                p-> pun = q->pun;
                delete q;
            }
            return true;
        }
        bool estrai_testa(T& dest) {
            return estrai_indice(dest, 0);
        }
        bool estrai_coda(T& dest) {
            return estrai_indice(dest, lunghezza() - 1);
        }
        bool leggi_indice(T& dest, int i) {
            if(testa == nullptr || i > lunghezza() - 1) 
                return false;
            int count = 0;
            elem* p = testa;
            while(p != nullptr & count < i) {
                p = p->pun;
                count++;
            }
            dest = p->inf;
            return true;
        }
        bool leggi_testa(T& dest) {
            return leggi_indice(dest, 0);
        }
        bool leggi_coda(T& dest) {
            return leggi_indice(dest, lunghezza() - 1);
        }
};