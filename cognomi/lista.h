struct scheda {
    char* nome;
    char* cognome;
};

struct elem {
    scheda* inf;
    elem* pun;
};
typedef elem* lista;

//dichiarazione funzioni di lista
void inserisci(lista& p0, scheda* a);
bool estrai(lista& p0, int i);
void dealloca(lista& p);