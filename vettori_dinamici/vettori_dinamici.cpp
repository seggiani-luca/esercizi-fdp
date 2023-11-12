#include <iostream>
using namespace std;

typedef int T;

//Il passaggio del pointer vett avviene per riferimento, in caso contrario assegnerei la memoria
//sull'heap ad un pointer che e' solo argomento formale.
void allocaVettoreDinamico(T*& vett, int l) {
  vett = new T [l];
}

void deallocaVettoreDinamico(T* vett) {
  delete[] vett;
}

void leggiDaTastiera(T* vett, int l) {
  for(int i = 0; i < l; i++) {
    cin >> *(vett + i);
  }
}

void stampaVettoreDinamico(T* vett, int l) {
  for(int i = 0; i < l; i++) {
    cout << *(vett + i);
  }
  cout << endl;
}

void ridimensionaVettoreDinamico(T*& vett, int oldL, int newL) {
  T* tempVett = new T [newL];
  //clona
  for(int i = 0; i < oldL & i < newL; i++) {
    *(tempVett + i) = *(vett + i);
  }
  delete [] vett;
  vett = tempVett;
}

int main() {

  int l;
  cout << "Inserisci la dimensione del vettore: " << endl;
  cin >> l;
  if(l < 1)
    l = 1;

  T* vett;
  allocaVettoreDinamico(vett, l);

  cout << "Inserisci gli elementi del vettore" << endl;
  leggiDaTastiera(vett, l);
  
  stampaVettoreDinamico(vett, l);

  int newL;
  cout << "Seleziona la nuova dimensione del vettore" << endl;
  cin >> newL;
  if(newL < 1)
    newL = 1;
  
  ridimensionaVettoreDinamico(vett, l, newL);
  
  stampaVettoreDinamico(vett, newL);

  deallocaVettoreDinamico(vett);
  return 0;
}
