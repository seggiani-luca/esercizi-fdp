#include "expr.h"
#include <iostream>
#include <cstring>

using namespace expr;

//Definizioni Stack
bool Stack::push(node* n) {
  if(p == size-1)
    return false;
  array[p] = n;
  p++;
  return true;
}

bool Stack::pop(node*& n) {
  if(p == 0)
    return false;
  n = array[--p];
  return true;
}

Stack::Stack(int SIZE) {
  size = SIZE;
  array = new node*[size];
  p = 0;
}

Stack::~Stack() {
  delete[] array;
}

//Definizioni BTree
void Btree::deltree(node* st) {
  if(st == nullptr)
    return;
  if(st->l != nullptr)
    deltree(st->l);
  if(st->r != nullptr)
    deltree(st->r);
  delete st;
}

void Btree::vs(node* e) {
  if(e != nullptr) {
    vs(e->l);
    std::cout << e->inf;
    vs(e->r);
  }
}
void Btree::va(node* e) {
  if(e != nullptr) {
    std::cout << e->inf;
    va(e->l);
    va(e->r);
  }
}
void Btree::vd(node* e) {
  if(e != nullptr) {
    vd(e->l);
    vd(e->r);
    std::cout << e->inf;
  }
}

//Funzioni di utilità per la conversione da stringa a Btree
bool isOperator(char c) {
  if(c == '+' | c == '-' | c == '*' | c == '/') {
    return true;
  }
  return false;
}
//

Btree::Btree(char* str) {
  Stack* stack = new Stack(strlen(str));
  int i = 0;
  while(str[i] != '\0') {
    if(isOperator(str[i])) {
      node* l, *r;
      stack->pop(r); //gli elementi vengono rimossi nell'ordine inverso a quello a cui sono stati inseriti
      stack->pop(l);
      node* n = new node;
      n->inf = str[i];
      n->l = l;
      n->r = r;
      stack->push(n);
    } else {
      node* n = new node;
      n->inf = str[i];
      stack->push(n);
    }
    i++;
  } 
  stack->pop(root);
}

Btree::Btree() {
  root = nullptr;
}
Btree::~Btree() {
  deltree(root);
  root = nullptr;
}

//wrapper per i membri privati di ricerca
void Btree::vos() {
  vs(root);
  std::cout << std::endl;
}
void Btree::voa() {
  va(root);
  std::cout << std::endl;
}
void Btree::vod() {
  vd(root);
  std::cout << std::endl;
}
//

int Btree::lunghezza_albero(node* e) {
  if(e == nullptr)
    return 0;
  int n = 0;
  n += 1;
  return n + lunghezza_albero(e->l) + lunghezza_albero(e->r);
}

void Btree::stampa_espressione() {
  int strlength = lunghezza_albero(root);
  char* str = new char[strlength];
  std::cout << "La lunghezza dell'albero e': " << strlength << endl;
}
