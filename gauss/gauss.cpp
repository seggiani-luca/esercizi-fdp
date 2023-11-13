#include <iostream>
using namespace std;

void copiaArray(double* ar1, double* ar2, int s) {
    for(int i = 0; i < s; i++) {
        ar2[i] = ar1[i];
    }
}

class matrice {
    private:
        void parentesiAperte(int c, int r) {
            if((righe == 1)&(c == 0)) {
                cout << "( ";
                return;
            }
            if(c == 0) {
                        if(r == 0) {
                            cout << "/ ";
                        } else {
                            if(r == righe - 1) {
                                cout << "\\ ";
                            } else {
                                cout << "| ";
                            }
                        }
                        cout << "\t";
                    }
        };
        void parentesiChiuse(int c, int r) {
            if((righe == 1)&(c == colonne - 1)) {
                cout << ") ";
                return;
            }
            if(c == colonne - 1) {
                        if(r == 0) {
                            cout << "\\ ";
                        } else {
                            if(r == righe - 1) {
                                cout << "/ ";
                            } else {
                                cout << "| ";
                            }
                        }
                    }
        };

        int pivot(int r, int c) {
            for(int i = 0; (i + r) < righe; i++) {
                //cout << i << " " << c << endl;
                //cout << mat[i][c] << endl;
                if(mat[i+r][c] != 0) {
                    return i+r;
                }
            }
            return -1;
        }
        void scambiaRighe(int r1, int r2) {
            //cout << "Inizio scambio righe..." << endl;
            double* temp = new double[colonne];
            copiaArray(mat[r2], temp, colonne);
            copiaArray(mat[r1], mat[r2], colonne);
            copiaArray(temp, mat[r1], colonne);
            //cout << "Ho finito di scambiare le righe." << endl;
        }

        void elimina(int r, int c) {
            for(int i = 1; (i + r) < righe; i++) {
                double rap = mat[r + i][c] / mat[r][c];
                matrice multi = matrice(1, colonne);
                copiaArray(mat[r], multi.mat[0], colonne);
                //cout << "Matrice temporanea creata" << endl;
                for(int j = 0; j < colonne; j++) {
                    multi.mat[0][j] *= rap;
                    mat[r+i][j] -= multi.mat[0][j];
                }
                cout << "Sottraggo il vettore:" << endl;
                multi.stampa();
                cout << "Alla riga " << r + i << " della matrice." << endl << endl;
                multi.dealloca();
            }
        }

    public:
        char* tag;
        double** mat;
        int righe;
        int colonne;

        matrice(int r, int c, char* t = "") {
            mat = new double*[r];
            for(int i = 0; i < r; i++) {
                mat[i] = new double[c];
            }
            righe = r;
            colonne = c;
            tag = t;
        };

        void leggi() {
            if(tag != "") {
                cout << "Inserisci gli elementi della matrice " << tag << ":" << endl;
            } else {
                cout << "Inserisci gli elementi della matrice:" << endl;
            }
            for(int r = 0; r < righe; r++) {
                for(int c = 0; c < colonne; c++) {
                    cin >> mat[r][c];
                }
            }
        };

        void stampa() {
            for(int r = 0; r < righe; r++) {
                for(int c = 0; c < colonne; c++) {
                    parentesiAperte(c, r);
                    cout << mat[r][c] << "\t";
                    parentesiChiuse(c, r);
                }
                cout << endl;
            }  
        };

        void riduci() {
            int passo = 1;
            int r,c;
            r = c = 0;
            while((r <= righe - 2) && (c <= colonne - 1)) {
                cout << "\033[36;1mPasso " << passo << ":\033[0m" << endl;
                int t = pivot(r, c);
                if(t == -1) {
                    c++;
                    cout << "Colonna nulla, proseguo." << endl << endl;
                } else {
                    if(t != r) {
                        scambiaRighe(t, r);
                        cout << "Scambio le righe " << t << " e " << r << "." << endl << endl;
                    } 
                    elimina(r, c);
                    r++;
                    c++;
                }
                cout << "Dopo il passo " << passo << " la matrice ha l'aspetto:" << endl;
                stampa();
                cout << endl;
                passo++;
            }
        }

        void dealloca() {
            for(int i = 0; i < righe; i++) {
                delete[] mat[i];
            }
            delete[] mat;
        }
};

void inputDimensioni(int& var, char* nome) {
    cout << "Inserisci il numero di " << nome << ":" << endl;
    cin >> var;
    while(var < 1) {
        cout << "Inserisci un numero maggiore di 0." << endl;
        cin >> var;
    }
}

int main() {
    int R;
    int C;
    inputDimensioni(R, "righe");
    inputDimensioni(C, "colonne");

    matrice mat = matrice(R, C, "A");
    mat.leggi();
    cout << "La matrice A e':" << endl;
    mat.stampa();
    cout << endl;

    cout << "Applico il metodo di riduzione gaussiana." << endl;
    mat.riduci();

    cout << "La matrice A ridotta e':" << endl;
    mat.stampa();
    mat.dealloca();
    return 0;
}
