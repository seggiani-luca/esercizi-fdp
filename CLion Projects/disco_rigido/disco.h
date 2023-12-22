#include <iostream>

#ifndef DISCO_RIGIDO_DISCO_H
#define DISCO_RIGIDO_DISCO_H

#define DIM_SETTORE 1024;

struct settore {
    unsigned identifier;

};

class Disco {
private:
    static unsigned dischi_totali;
    unsigned nextIdentifier;

    settore* settori;
    unsigned num;
public:
    Disco(unsigned num);
    ~Disco();
    int riserva(unsigned dim);
    void cancella(unsigned id);
    void deframmenta();
    static unsigned getQuantiDischi();

    //operatori
    void operator!();
    friend std::ostream& operator<<(std::ostream& stream, Disco& disco);
};

//dichiarazioni funzioni globali
std::ostream& operator<<(std::ostream& stream, Disco& disco);



#endif //DISCO_RIGIDO_DISCO_H
