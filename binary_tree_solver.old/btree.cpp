#include <iostream>
#include "btree.h"

void Btree::deltree(elem* st) {
  if(st == nullptr)
    return;
  if(st->l != nullptr)
    deltree(st->l);
  if(st->r != nullptr)
    deltree(st->r);
  delete st;
}

void Btree::vs(elem* e) {
  if(e != nullptr) {
    vs(e->l);
    std::cout << e->inf;
    vs(e->r);
  }
}
void Btree::va(elem* e) {
  if(e != nullptr) {
    std::cout << e->inf;
    vs(e->l);
    vs(e->r);
  }
}
void Btree::vd(elem* e) {
  if(e != nullptr) {
    vs(e->l);
    vs(e->r);
    std::cout << e->inf;
  }
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

Btree::elem* Btree::insert(type inf, elem* l, elem* r) {
  elem* p = new elem();
  p->inf = inf;
  p->l = l;
  p->r = r;
  if(root == nullptr)
    root = p;
  return p;
} 
