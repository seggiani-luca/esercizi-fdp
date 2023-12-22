#include "stack.h"

bool Stack::push(char inf) {
  if(p == size-1)
    return false;
  array[p] = inf;
  p++;
  return true;
}

bool Stack::pop(char& dest) {
  if(p == 0)
    return false;
  dest = array[--p];
  return true;
}

Stack::Stack(int SIZE) {
  size = SIZE;
  array = new type[size];
  p = 0;
}

Stack::~Stack() {
  delete[] array;
}
