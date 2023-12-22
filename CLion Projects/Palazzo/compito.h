/*
 * La classe "Palazzo" è una lista di struct "Piano".
 * "Palazzo" contiene un puntatore "terra" al primo piano, e ogni piano contiene un puntatore al successivo.
 * "Palazzo" contiene inoltre le funzioni di interfaccia per le operazioni sulla lista e un integer "max" che indica
 * il massimo numero di piani. La limitazione di piani è implementata con un controllo in fase di aggiunta piani.
 * "Piano" è uno struct che contiene un'array incapsulata (array e numero di elementi) di booleani rappresentanti
 * le finestre (true significa "aperto" e false significa "chiuso") e il riferimento al piano successivo.
*/

#ifndef PALAZZO_COMPITO_H
#define PALAZZO_COMPITO_H

struct Piano {
    bool* finestre;
    int len;
    Piano* pun;

    Piano(int n = 1);
    ~Piano();
    Piano(Piano& p);
    void cambia(int j);
    void scala(int n);
};

class Palazzo {
private:
    int max;
    Piano* terra;

    int piani();
    void aggiungi(Piano& t); //variante per la copia di piani
public:
    Palazzo(int n);
    ~Palazzo();
    Palazzo(Palazzo& p);
    void aggiungi();
    void stampa();
    void cambia(int i, int j);
    int operator!();
    void operator%=(Palazzo& p);
};


#endif //PALAZZO_COMPITO_H
