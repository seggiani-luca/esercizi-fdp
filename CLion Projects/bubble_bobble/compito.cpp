#include "compito.h"
using namespace std;

PuzzleBobble::PuzzleBobble() {
    for(int r = 0; r < NUM_ROW; r++) {
        for(int c = 0; c < NUM_COL; c++) {
            _schema[r][c] = ' ';
        }
    }
}

PuzzleBobble& PuzzleBobble::fire(int i, char color) {
    int riga = 0;
    for(int r = NUM_ROW - 1; r >= 0; r--) {
        if(r == 0) { //fine schema
            _schema[r][i] = color;
            riga = r;
            //qui il break sarebbe ridondante
        } else {
            if(_schema[r - 1][i] != ' ') { //bolla adiacente
                _schema[r][i] = color;
                riga = r;
                break;
            }
        }
    }
    //inizia controlli di adiacenza per scoppio bolle

    //verticale
    int delta = 0;
    bool scoppiata = false;
    while(riga - delta >= 0) {
        delta++;
        if(_schema[riga - delta][i] != color) {
            break;
        }
    }
    if(delta >= 3) {
        scoppiata = true;
        delta = 1;
        while(riga - delta >= 0) {
            if(_schema[riga - delta][i] == color) {
                _schema[riga - delta][i] = ' ';
            } else {
                break;
            }
            delta++;
        }
    }

    //sinistra
    delta = 0;
    while(i - delta >= 0) {
        delta++;
        if(_schema[riga][i - delta] != color) {
            break;
        }
    }
    if(delta >= 3) {
        scoppiata = true;
        delta = 1;
        while(i - delta >= 0) {
            if(_schema[riga][i - delta] == color) {
                _schema[riga][i - delta] = ' ';
            } else {
                break;
            }
            delta++;
        }
    }

    //destra
    int prevDelta = delta - 1; //ricorda il delta precedente in quanto agisco sulla stessa riga...
    delta = 0;
    while(i + delta < NUM_COL) {
        delta++;
        if(_schema[riga][i + delta] != color) {
            break;
        }
    }
    if(delta + prevDelta >= 3) {
        scoppiata = true;
        delta = 1;
        while(i + delta < NUM_COL) {
            if(_schema[riga][i + delta] == color) {
                _schema[riga][i + delta] = ' ';
            } else {
                break;
            }
            delta++;
        }
    }

    if(scoppiata) {
        //solo adesso scoppia la bolla lanciata (se necessario)
        _schema[riga][i] = ' ';
    }

    //cout << *this;
    return *this;
}

PuzzleBobble::operator int() const {
    int count = 0;
    for(int r = 0; r < NUM_ROW; r++) {
        bool bolla = false;
        for(int c = 0; c < NUM_COL; c++) {
            if(_schema[r][c] != ' ') {
                bolla = true;
                break;
            }
        }
        if(bolla == false) {
            return count;
        }
        count++;
    }
    return NUM_ROW;
}

PuzzleBobble& PuzzleBobble::scroll() {
    if((int)*this >= 10) { //taglierei fuori almeno una bolla
        return *this;
    }
    for(int r = NUM_ROW - 1; r >= 0; r--) {
        for(int c = 0; c < NUM_COL; c++) {
            if(r == 0) {
                _schema[r][c] = '=';
            } else {
                _schema[r][c] = _schema[r - 1][c];
            }
        }
    }
    return *this;
}

PuzzleBobble& PuzzleBobble::compact() {
    for(int c = 0; c < NUM_COL; c++) {
        bool trovata_bolla = false;
        int count = 0;
        for(int r = NUM_ROW - 1; r >= 0; r--) {
            if(_schema[r][c] != ' ') {
                trovata_bolla = true;
            } else {
                if(trovata_bolla == true && _schema[r][c] == ' ') {
                    count++;
                }
            }
        }
        if(count == 0) {
            continue; //shortcut
        }
        for(int r = 0; r < NUM_ROW - 1; r++) {
            if(_schema[r][c] != '=') {
                _schema[r][c] = _schema[r + count][c];
            }
            //cout << *this;
        }
    }
    return *this;
}

ostream& operator<<(ostream& st, PuzzleBobble& pb) {
    for(int r = 0; r < NUM_ROW + 2; r++) {
        for(int c = 0; c < NUM_COL + 2; c++) {
            //bordi
            if(r == 0 || r == NUM_ROW + 1) {
                cout << "=";
                continue;
            }
            if(c == 0 || c == NUM_COL + 1) {
                cout << "|";
                continue;
            }
            //schema
            cout << pb._schema[r - 1][c - 1];
        }
        cout << '\n';
    }
    return st;
}
