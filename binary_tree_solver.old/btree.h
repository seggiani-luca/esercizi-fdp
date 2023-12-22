#ifndef BTREE_H
#define BTREE_H

typedef char type;

class Btree {
public:
  struct elem {
    type inf;
    elem* l; elem* r;
  };
private:
  elem* root; 
  void deltree(elem* p);
  void vs(elem* e);
  void va(elem* e);
  void vd(elem* e);
public:
  Btree();
  ~Btree();
  void vos();
  void voa();
  void vod();
  elem* insert(type inf, elem* l, elem* r);
};

#endif
