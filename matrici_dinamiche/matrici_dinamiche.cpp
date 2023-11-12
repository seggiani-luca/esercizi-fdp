#include <iostream>
using namespace std;

typedef int T;

int main() {

  int colonne;
  int righe;
  cout << "Inserisci le colonne della matrice" << endl;
  cin >> colonne;
  cout << "Inserisci le righe della matrice" << endl;
  cin >> righe;

  //controlla dimensioni
  if(colonne < 1)
    colonne = 1;
  if(righe < 1)
    righe = 1;

  T** matr = new T* [righe];
  for(int r = 0; r < righe; r++) {
    *(matr + r) = new T [colonne];
  }

  for(int x = 0; x < righe; x++) {
    for(int y = 0; y < colonne; y++) {
      cout << matr[y][x] << " ";
    }
    cout << endl;
  }

  return 0;
}
