#ifndef EXPR_H
#define EXPR_H

/*Il modulo expr.h definisce tutte le strutture necessarie alla gestione di alberi binari rappresentanti espressioni, ovvero:
  1) Lo struct node, che contiene un char rappresentante o una costante o un operatore
  2) La classe Btree, albero binario di node che rappresenta l'espressione
  3) La classe Stack, usata per la conversione da notazione postfissa ad albero binario.
*/

typedef char type;

namespace expr {

union term {
  double value;
  char symbol;
};

struct node {
  type inf;
  node* l, *r;
};

class Stack {
public:
  int size;
  bool push(node* inf);
  bool pop(node*& dest);
  Stack(int SIZE);
  ~Stack();
private:
  int p;
  node** array;
};

}

using namespace expr;

class Btree {
private:
  node* root; 
  void deltree(node* p);
  void vs(node* e);
  void va(node* e);
  void vd(node* e);
  int lunghezza_albero(node* e);
public:
  Btree();
  Btree(char* str); //Il costruttore da stringa converte una sringa postfissa nell'albero binario corrispondente
  ~Btree();
  void vos();
  void voa();
  void vod();
  void stampa_espressione();
  double evalua_espressione();
};

#endif
