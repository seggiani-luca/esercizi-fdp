const int MAX_LEN = 31;

struct elem {
    char nome[MAX_LEN];
    int pettorale;
    elem* pun;
};

class lista {
public:
    elem* l;
    void init();
    void visualizza();
    void aggiungi(char* nome, int pettorale);
    bool cerca(char* nome);
    bool elimina(char* nome);

};