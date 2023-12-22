#include <iostream> //per la definizione di cout <<

#ifndef PRATO_FIORITO_COMPITO_H
#define PRATO_FIORITO_COMPITO_H

struct cella {
    bool mina = false;
    bool scoperta = false;
    int mine_adiacenti = 0;
};

class CampoMinato {
private:
    enum { non_avviato, avviato, vinto, perso } stato_gioco;
    cella** campo; //array bidimensionale di celle
    int dim;
    int num_mine;

    bool controlla_vittoria();
public:
    CampoMinato(int n);
    ~CampoMinato();
    CampoMinato(CampoMinato& cp);
    bool aggiungi_mina(int r, int c);
    void scopri(int r, int c);
    CampoMinato operator+(CampoMinato& cp);
    friend std::ostream& operator<<(std::ostream& s, CampoMinato& cp);
};

std::ostream& operator<<(std::ostream& s, CampoMinato& cp);


#endif //PRATO_FIORITO_COMPITO_H
