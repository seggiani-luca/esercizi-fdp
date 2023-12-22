//si definisce la classe SonicLevel, contenente:
//un enum stato di gioco
//un array 8x32 di caselle (tipo enum? struct?)
//il numero di anelli raccolti
//la posizione di sonic

//funzioni membro;

//s.blocchi i j nr nc
//i j limite inferiore - sinistro, nr nc dimensione righe e col
//attenzione! non fare niente se non entra nella schermata
//concatenabile
//solo a gioco fermo

//s.anello i j
//idem

//s.avvia i j
//avvia il gioco e colloca sonic in i j

//operator += n
//sonic cammina verso destra
//solo a gioco avviato
//n deve essere positivo
#include <ostream>

#define NUM_RIGHE 8
#define NUM_COLONNE 32

#ifndef SONIC_COMPITO_H
#define SONIC_COMPITO_H

struct vector {
    int x;
    int y;
    vector(const int x = 0, const int y = 0) {
        this->x = x;
        this->y = y;
    }
    bool operator==(const vector& b) {
        return (this->x == b.x) && (this->y == b.y);
    }
};

class SonicLevel {
private:
    enum { giocoAvviato, giocoFermo } _statoGioco;
    char _livello[NUM_RIGHE][NUM_COLONNE];
    unsigned _anelli;
    vector _posizioneSonic = vector(); //vettore nullo

    bool provaPasso(bool corsa, bool& invulnerabile);
    void cadi(bool& invulnerabile);
    void controllaVittoria();

    inline void raccogli();
    bool sali();
    void scendi();

    //mascheramento inutilizzati
    SonicLevel(SonicLevel& level);
    SonicLevel& operator=(SonicLevel& level);
public:
    SonicLevel();
    SonicLevel& blocchi(int i, int j, int nr, int nc);
    SonicLevel& anello(int i, int j);
    void avvia(int i, int j);
    SonicLevel& operator+=(int n);
    friend std::ostream& operator<<(std::ostream& stream, const SonicLevel& level);

    //parte 2
    SonicLevel& spuntone(int i, int j);
    SonicLevel& operator*=(int n);
};


#endif //SONIC_COMPITO_H
