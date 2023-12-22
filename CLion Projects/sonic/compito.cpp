#include "compito.h"
#include <iostream>

SonicLevel::SonicLevel() {
    for(int y = 0; y < NUM_RIGHE; y++) {
        for(int x = 0; x < NUM_COLONNE; x++) {
            if(y == 0) {
                _livello[y][x] = '=';
            } else {
                _livello[y][x] = ' ';
            }
        }
    }
    _statoGioco = giocoFermo;
    _anelli = 0; //posiziona sonic fuori dalla mappa
    return;
}

SonicLevel &SonicLevel::blocchi(const int i, const int j, const int nr, const int nc) {
    if(_statoGioco != giocoFermo) {
        return *this;
    }

    int extrSuperiore = i + nr;
    int extrDestro = j + nc;

    //controlla bound
    {
        if(i < 0 || i > NUM_RIGHE - 1) {
            return *this;
        }
        if(j < 0 || j > NUM_COLONNE - 1) {
            return *this;
        }
        if(nr < 0 || nr > NUM_RIGHE - 1) {
            return *this;
        }
        if(nc < 0 || nc > NUM_COLONNE - 1) {
            return *this;
        }
    }
    for(int r = i; r < extrSuperiore; r++) {
        for(int c = j; c < extrDestro; c++) {
            _livello[r][c] = '=';
        }
    }

    return *this;
}

SonicLevel &SonicLevel::anello(const int i, const int j) {
    if(_statoGioco != giocoFermo) {
        return *this;
    }

    if(i < 0 || i > NUM_RIGHE - 1) {
        return *this;
    }
    if(j < 0 || j > NUM_COLONNE - 1) {
        return *this;
    }

    if(_livello[i][j] != ' ') {
        return *this;
    }
    _livello[i][j] = 'o';
    return *this;
}

void SonicLevel::avvia(const int i, const int j) {
    //controlla input
    if(j < 1 || j > NUM_COLONNE - 1 || i < 0 || i > NUM_RIGHE - 1) {
        return;
    }
    if(_livello[i - 1][j] != '=') {
        return;
    }
    if(_livello[i][j] == '=') {
        return; //sonic muore soffocato
    }
    _posizioneSonic = vector(j, i);
    _statoGioco = giocoAvviato;
    _anelli = 0;
    return;
}

inline void SonicLevel::raccogli() {
    //raccogli oggetti
    if(_livello[_posizioneSonic.y][_posizioneSonic.x] == 'o') {
        _livello[_posizioneSonic.y][_posizioneSonic.x] = ' ';
        _anelli++;
    }
}

void SonicLevel::cadi(bool& invulnerabile) {
    while(_livello[_posizioneSonic.y - 1][_posizioneSonic.x] != '=' && _livello[_posizioneSonic.y - 1][_posizioneSonic.x] != '^') {
        _posizioneSonic.y--;
        raccogli();
    }
    if(_livello[_posizioneSonic.y - 1][_posizioneSonic.x] == '^' && !invulnerabile) {
        if(_anelli == 0) {
            //game over
            _statoGioco = giocoFermo;
        } else {
            _anelli = 0;
            invulnerabile = true;
        }
    }
}

bool SonicLevel::provaPasso(const bool corsa, bool& invulnerabile) {
    //prima controlla a destra, in basso e in basso a destra
    bool destraLibera = _livello[_posizioneSonic.y][_posizioneSonic.x + 1] != '=' && _livello[_posizioneSonic.y][_posizioneSonic.x + 1] != '^';
    if(destraLibera & _posizioneSonic.x < NUM_COLONNE - 1) {
        _posizioneSonic.x++;
    } else {
        return false;
    }
    raccogli();
    bool aTerra = _livello[_posizioneSonic.y - 1][_posizioneSonic.x] == '=' || _livello[_posizioneSonic.y - 1][_posizioneSonic.x] == '^';
    bool prossimoATerra = _livello[_posizioneSonic.y - 1][_posizioneSonic.x + 1] == '=';
    if(!aTerra) {
        if(!(corsa && prossimoATerra)) {
            cadi(invulnerabile);
        }
    }
    if(_livello[_posizioneSonic.y - 1][_posizioneSonic.x] == '^' && !invulnerabile) {
        if(_anelli == 0) {
            //game over
            _statoGioco = giocoFermo;
        } else {
            _anelli = 0;
            invulnerabile = true;
        }
    }
    return true;
}

void SonicLevel::controllaVittoria() {
    if(_posizioneSonic.x == NUM_COLONNE - 1) {
        _statoGioco = giocoFermo;
    }
    return;
}

SonicLevel &SonicLevel::operator+=(const int n) {
    if(_statoGioco != giocoAvviato | n < 0) {
        return *this;
    }
    bool invulnerabile = false;
    for(int i = 0; i < n; i++) {
        //std::cout << *this << "\n" ;
        if(!provaPasso(i >= 10, invulnerabile))
            break;
    }
    controllaVittoria();
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const SonicLevel& level) {
    if(level._statoGioco == SonicLevel::giocoFermo) {
        stream << "(GIOCO FERMO)\n";
        return stream;
    }
    stream << "Anelli: " << level._anelli << "\n";
    for(int y = NUM_RIGHE - 1; y >= -1; y--) {
        for(int x = -1; x < NUM_COLONNE; x++) {
            if(y == -1) { //fila num inferiore
                if(x >= 0) {
                    stream << x % 10;
                } else {
                    stream << ' ';
                }
                continue;
            }
            if(x == -1) { //fila num laterale
                stream << y;
                continue;
            }

            if(vector(x, y) == level._posizioneSonic) {
                stream << 'S';
            } else {
                stream << level._livello[y][x];
            }
        }
        stream << '\n';
    }
    return stream;
}

//parte 2
SonicLevel &SonicLevel::spuntone(const int i, const int j) {
    if(_statoGioco != giocoFermo) {
        return *this;
    }

    if(i < 0 || i > NUM_RIGHE - 1) {
        return *this;
    }
    if(j < 0 || j > NUM_COLONNE - 1) {
        return *this;
    }
    if(_livello[i][j] != '=' && _livello[i][j] != ' ') {
        return *this;
    }
    _livello[i][j] = '^';
    return *this;
}

bool SonicLevel::sali() {
    bool testa = (_posizioneSonic.y >= NUM_RIGHE - 1) || _livello[_posizioneSonic.y + 1][_posizioneSonic.x] == '=' || _livello[_posizioneSonic.y + 1][_posizioneSonic.x] == '^';
    bool destraLibera = _livello[_posizioneSonic.y + 1][_posizioneSonic.x + 1] != '=' && _livello[_posizioneSonic.y + 1][_posizioneSonic.x + 1] != '^';
    if(!testa) {
        if(destraLibera) {
            _posizioneSonic.x++;
        }
        if(_posizioneSonic.y < NUM_RIGHE - 1) {
            _posizioneSonic.y++;
        }
        raccogli();
    } else {
        return false;
    }

    return true;
}

void SonicLevel::scendi() {
    while(_livello[_posizioneSonic.y - 1][_posizioneSonic.x] != '=' && _livello[_posizioneSonic.y - 1][_posizioneSonic.x] != '^') {
        bool destraLibera = _livello[_posizioneSonic.y - 1][_posizioneSonic.x + 1] != '=' && _livello[_posizioneSonic.y - 1][_posizioneSonic.x + 1] != '^';
        if(destraLibera) {
            _posizioneSonic.x++;
        }
        _posizioneSonic.y--;
        raccogli();
        //std::cout << *this;
    }
    if(_livello[_posizioneSonic.y - 1][_posizioneSonic.x] == '^') {
        if(_anelli == 0) {
            //game over
            _statoGioco = giocoFermo;
        } else {
            _anelli = 0;
        }
    }
}

SonicLevel &SonicLevel::operator*=(int n) {
    if(_statoGioco != giocoAvviato | n < 0) {
        return *this;
    }

    for(int i = 0; i < n; i++) {
        //std::cout << *this;
        if(!sali())
            break;
    }

    scendi();
    controllaVittoria();

    return *this;
}

