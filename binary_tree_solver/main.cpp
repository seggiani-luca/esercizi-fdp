#include <iostream>
#include "expr.h"
using namespace std;

const int MAX_LEN = 30;

char* ottieniStringa() {
  char* str = new char[MAX_LEN + 1];
  char c;
  int i = 0;
  cin >> c;
  while(c != '\n') {
    str[i] = c;
    c = cin.get();
    i++;
  }
  str[i] = '\0';
  return str;
}

int main() {
  cout << "Inserisci una stringa postfissa:" << endl;
  char* str = ottieniStringa();
  Btree* tree = new Btree(str);
  cout << "La stringa inserita e': " << str << endl;
  delete[] str;

  cout << "Visita in ordine anticipato:" << endl;
  tree->voa();
  cout << "Visita in ordine simmetrico:" << endl;
  tree->vos();
  cout << "Visita in ordine differito:" << endl;
  tree->vod();
  tree->stampa_espressione();
  
  delete tree;
  return 0;
}
