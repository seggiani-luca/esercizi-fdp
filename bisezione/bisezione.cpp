//questo programma trova radici di polinomi attraverso il metodo di bisezione
#include <iostream>
#include <chrono> //usato per restiture il tempo d'esecuzione

using namespace std;

double evalua(double val, double *coefficienti, int grado);
double pow(double val, int exp);

int main() {

    int grado;
    cout << "Inserisci il grado del polinomio: " << endl;
    cin >> grado;
    grado += 1;
    double* coef;
    coef = new double[grado];

    cout << "Inserisci i coefficienti del polinomio dal grado maggiore al termine noto" << endl;

    char lettera = 'a';
    double *p = coef;
    for(int i = 0; i < grado; i++) {
        cout << (char)(lettera + i) << ": ";
        cin >> *(coef + i);
    }

    cout << "Inserisci il limite inferiore (a) ed il limite superiore (b) dell'intervallo [a, b]" << endl;
    double inf, sup;
    cout << "Limite inferiore (a): ";
    cin >> inf;
    cout << "Limite superiore (b): ";
    cin >> sup;

    int pass;
    do {
        cout << "Inserisci il numero di passaggi di approssimazione da eseguire (devono essere maggiori di 1)" << endl;
        cin >> pass;
    } while(pass < 1);

    auto start = chrono::steady_clock::now(); //tempo d'inizio

    //controlla prima a e b
    double valInf = evalua(inf, coef, grado);
    double valSup = evalua(sup, coef, grado);
    if(valSup < valInf) {
        double t = sup;
        sup = inf;
        inf = t;
    }

    double media;
    double val;
    for(int i = 0; i < pass; i++) {
        media = (inf + sup) / 2;
        val = evalua(media, coef, grado);
        cout << i << ": Media: " << media << " Valore: " << val << endl;
        if(val == 0)
            break;
        if(val < 0) {
            inf = media;
        } else { // val > 0
            sup = media;
        }
    }

    auto end = chrono::steady_clock::now(); // tempo di fine
    auto diff = end - start;

    cout << "Il valore approssimato e': " << media << ", la cui f vale: " << val << endl;
    cout << "La risposta e' stata calcolata in " << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    return 0;
}

double evalua(double val, double *coefficienti, int grado) {
    double f = 0;
    for(int i = 0; i < grado; i++) {
        f += *(coefficienti + i) * pow(val, grado-1-i);
    }
    return f;
}

double pow(double val, int exp) {
    double valOrig = val;
    if(exp == 0)
        return 1;
    for(int i = 1; i < exp; i++) {
        val *= valOrig;
    }
    return val;
}
