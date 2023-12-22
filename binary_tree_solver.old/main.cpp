#include <iostream>
#include "btree.h"
#include "stack.h"
#include <cstring>
using namespace std;

void stampaVisite(Btree* tree) {
  cout << "Visita in ordine simmetrico: " << endl;
  tree->vos();
  cout << "Visita in ordine anticipato: " << endl;
  tree->voa();
  cout << "Visita in ordine differito: " << endl;
  tree->vod();

}

char* ottieniStringaInfissa() {
  char c;
  char* str = new char[30];

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

Btree* creaEspressione(char* str) {
  int i = 0;
  Stack* stack = new Stack(strlen(str));
  Btree* tree = new Btree();

  while(str[i] != '\0') {
    if(str[i] == '+' | str[i] == '-' | str[i] == '*' | str[i] == '/' ) {
      char l, r;
      stack->pop(r); stack->pop(l);
      Btree::elem* lElem = new Btree::elem();
      Btree::elem* rElem = new Btree::elem();
      lElem->inf = l;
      rElem->inf = r;
      tree->insert(str[i], lElem, rElem);
    } else {
      stack->push(str[i]);
    }
    i++;
  }
  return tree;
}

int main() {
  char* str = ottieniStringaInfissa();
  Btree* tree = creaEspressione(str);
  cout << "Espressione infissa: " << str << endl;

  delete[] str;
  stampaVisite(tree);
  return 0;
}
