const int MAX_LEN = 31;

struct elem {
    char nome[MAX_LEN];
    int pettorale;
    elem* pun;
};

void init(elem*& l);
void visualizza(elem*& l);
void aggiungi(elem*& l, char* nome, int pettorale);
bool cerca(elem*& l, char* nome);
bool elimina(elem*& l, char* nome);