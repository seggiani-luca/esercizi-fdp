#include "disco.h"

unsigned Disco::dischi_totali = 0;

Disco::Disco(unsigned num) {
    dischi_totali++;

    if(num <= 0)
        num = 8;

    nextIdentifier = 1;
    settori = new settore[num];
    this->num = num;
    for(int i = 0; i < num; i++) {
        (settori + num)->identifier = 0; //settore vuoto
    }
}

Disco::~Disco() {
    dischi_totali--;

    delete[] settori;
}

int Disco::riserva(unsigned dim) {
    unsigned required = 0;
    while(required < dim){
        required += DIM_SETTORE;
    }
    required /= DIM_SETTORE;
    int c = 0;
    for(int i = 0; i < num; i++) {
        if((settori + i)->identifier == 0) {
            c++;
        }
    }
    if(c >= required) {
        for(int i = 0; i < num && required > 0; i++) {
            if((settori + i)->identifier == 0) {
                (settori + i)->identifier = nextIdentifier;
                required--;
            }
        }
        nextIdentifier++;
        return nextIdentifier - 1;
    }
    return 0;
}

void Disco::cancella(unsigned id) {
    for(int i = 0; i < num; i++) {
        if((settori + i)->identifier == id) {
            (settori + i)->identifier = 0;
        }
    }
}

std::ostream& operator<<(std::ostream& stream, Disco& disco) {
    for(int i = 0; i < disco.num; i++) {
        std::cout << (disco.settori + i)->identifier;
    }
    std::cout << std::endl;
    return stream;
}

void Disco::operator!() {
    nextIdentifier = 1;
    for(int i = 0; i < num; i++) {
        (settori + i)->identifier = 0;
    }
}

void Disco::deframmenta() {
    //la deframmentazione del disco assume essenzialmente la forma di un algoritmo di ordinamento stabile
    for(int i = 0; i < num; i++) {
        unsigned max = 0;
        unsigned max_pos = i;
        for(int j = i; j < num; j++) {
            if((settori + j)->identifier >= max) {
                max = (settori + j)->identifier;
                max_pos = j;
            }
        }
        (settori + max_pos)->identifier = (settori + i)->identifier;
        (settori + i)->identifier = max;
    }
}

unsigned Disco::getQuantiDischi() {
    return dischi_totali;
}
