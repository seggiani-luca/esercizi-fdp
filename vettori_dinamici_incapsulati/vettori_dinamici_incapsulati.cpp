#include <iostream>
using namespace std;

typedef int T;

struct vettore {
  T* vett; //pointer al primo elemento
  int l; //lunghezza vettore
  vettore(int lunghezza) {
    vett = new T [lunghezza];
    l = lunghezza;
  }
  void dealloca() {
    delete[] vett;
  }
  void estendi(int nuovaDimensione) {
    T* tempVett = new T [nuovaDimensione];
    //clona
    for(int i = 0; i < l & i < nuovaDimensione; i++) {
      *(tempVett + i) = *(vett + i);
    }
    delete [] vett;
    vett = tempVett;
    l = nuovaDimensione;
  }
};

void stampaVettoreDinamico(vettore* vett) {
  for(int i = 0; i < vett->l; i++) {
    cout << *(vett->vett + i) << " ";
  }
  cout << endl;
}

void leggiDaTastiera(vettore* vett) {
  for(int i = 0; i < vett->l; i++) {
    cin >> *(vett->vett + i);
  }
}

int main() {
  int l;
  cout << "Inserisci la dimensione del vettore: " << endl;
  cin >> l;
  if(l < 1)
    l = 1;

  vettore* vett = new vettore(l);

  cout << "Inserisci gli elementi del vettore" << endl;
  leggiDaTastiera(vett);
  
  stampaVettoreDinamico(vett);

  int newL;
  cout << "Seleziona la nuova dimensione del vettore" << endl;
  cin >> newL;
  if(newL < 1)
    newL = 1;
  
  vett->estendi(newL);
  
  stampaVettoreDinamico(vett);

  vett->dealloca();
  return 0;
}
