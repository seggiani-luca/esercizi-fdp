#include <iostream>

#ifndef VETTORE_SPARSO_COMPITO_H
#define VETTORE_SPARSO_COMPITO_H

struct entrata {
    int valore;
    int indice;
    entrata* pun;
};

class VettoreSparso {
private:
    int _dimensioneVettore;
    entrata *_radice;

    //occulto la copia e l'assegnamento
    VettoreSparso(VettoreSparso& vett);
    VettoreSparso& operator=(VettoreSparso& vett);
public:
    VettoreSparso(int dimensione);
    ~VettoreSparso();

    void set(int v, int i);
    void visualizzaComeDenso();
    void reset(int i);

    VettoreSparso& operator*=(int k);
    friend std::ostream& operator<<(std::ostream& stream, VettoreSparso& vett);
};

std::ostream& operator<<(std::ostream& stream, VettoreSparso& vett);

#endif //VETTORE_SPARSO_COMPITO_H
