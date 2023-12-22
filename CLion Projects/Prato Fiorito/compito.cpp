#include "compito.h"

//metodi pubblici

CampoMinato::CampoMinato(int n) {
    stato_gioco = non_avviato;

    campo = new cella*[n]; //direttorio righe
    for(int r = 0; r < n; r++) {
        *(campo + r) = new cella[n]; //righe
    }

    dim = n;
    num_mine = 0;
}

CampoMinato::~CampoMinato() {
    for(int r = 0; r < dim; r++) {
        delete[] *(campo + r);
    }
    delete[] campo;
}

CampoMinato::CampoMinato(CampoMinato &cp) {
    stato_gioco = non_avviato;
    campo = new cella*[cp.dim]; //direttorio righe
    for(int r = 0; r < cp.dim; r++) {
        *(campo + r) = new cella[cp.dim]; //righe
        for(int c = 0; c < cp.dim; c++) {
            campo[r][c] = cp.campo[r][c];
            campo[r][c].scoperta = false;
        }
    }
    dim = cp.dim;
    num_mine = cp.num_mine;
}

bool CampoMinato::aggiungi_mina(int r, int c) {
    //controlli
    if(stato_gioco != non_avviato) {
        return false;
    }
    if(r < 0 || r >=dim || c < 0 || c >= dim) { //controllo bound
        return false;
    }
    if(campo[r][c].mina) {
        return false;
    }
    //aggiunta
    campo[r][c].mina = true;
    num_mine++;

    //precalcolo il numero di mine adiacenti a ogni cella
    for(int y = -1; y < 2; y++) {
        for(int x = -1; x < 2; x++) {
            int ad_r = r + y;
            int ad_c = c + x;
            if(ad_r >= 0 && ad_r < dim && ad_c >= 0 && ad_c < dim) {
                campo[ad_r][ad_c].mine_adiacenti++;
            }
        }
    }
    return true;
}

void CampoMinato::scopri(int r, int c) {
    //controlli
    if(r < 0 || r >=dim || c < 0 || c >= dim) { //controllo bound
        return;
    }
    if(num_mine == 0) {
        return;
    }
    if(stato_gioco == vinto || stato_gioco == perso) {
        return;
    }
    //scopri
    stato_gioco = avviato;
    campo[r][c].scoperta = true;
    if(campo[r][c].mina) {
        //mina esplosa
        stato_gioco = perso;
        return;
    } else {
        //prosegui
        if(campo[r][c].mine_adiacenti == 0) {
            for(int y = -1; y < 2; y++) {
                for(int x = -1; x < 2; x++) {
                    int ad_r = r + y;
                    int ad_c = c + x;
                    if(ad_r >= 0 && ad_r < dim && ad_c >= 0 && ad_c < dim) {
                        campo[ad_r][ad_c].scoperta = true;
                    }
                }
            }
        }
        if(controlla_vittoria()) {
            stato_gioco = vinto;
            return;
        }
    }
}

CampoMinato CampoMinato::operator+(CampoMinato &cp) {
    CampoMinato nuovo(dim + cp.dim);
    nuovo.stato_gioco = non_avviato;

    for(int r = 0; r < dim; r++) { //c1
        for(int c = 0; c < dim; c++) {
            nuovo.campo[r][c] = campo[r][c];
            nuovo.campo[r][c].scoperta = false;
        }
    }
    for(int r = 0; r < cp.dim; r++) { //c1
        for(int c = 0; c < cp.dim; c++) {
            nuovo.campo[r+dim][c+dim] = cp.campo[r][c];
            nuovo.campo[r+dim][c+dim].scoperta = false;
        }
    }

    nuovo.num_mine = num_mine + cp.num_mine;

    return nuovo;
}

using namespace std;
ostream& operator<<(ostream& s, CampoMinato& cp) {
    switch(cp.stato_gioco) {
        case CampoMinato::non_avviato:
            if(cp.num_mine == 0) {
                cout << "Inserire una mina per avviare il gioco" << endl;
                return s;
            }
            break;
        case CampoMinato::vinto:
            cout << "Vittoria!" << endl;
            return s;
        case CampoMinato::perso:
            cout << "Game over" << endl;
            return s;
    }

    cout << "Campo Minato " << cp.dim << "x" << cp.dim << " - Mine da trovare: " << cp.num_mine << endl;

    for(int r = 0; r < cp.dim; r++) {
        for(int c = 0; c < cp.dim; c++) {
            cella& cell = cp.campo[r][c];
            if(cell.scoperta) {
                if(cell.mine_adiacenti == 0) {
                    cout << "  ";
                } else {
                    cout << cell.mine_adiacenti << " ";
                }
            } else {
                cout << "x ";
            }
        }
        cout << endl;
    }

    return s;
}

//metodi privati

bool CampoMinato::controlla_vittoria() {
    bool vinto = true;
    for(int r = 0; r < dim; r++) {
        for(int c = 0; c < dim; c++) {
            if(!campo[r][c].scoperta && !campo[r][c].mina) {
                vinto = false;
            }
        }
    }
    return vinto;
}

