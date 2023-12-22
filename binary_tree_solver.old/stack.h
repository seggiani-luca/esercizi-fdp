#ifndef STACK_H
#define STACK_H

typedef char type;

class Stack {
public:
  int size;
  bool push(char inf);
  bool pop(char& dest);
  Stack(int SIZE);
  ~Stack();
private:
  int p;
  type* array;
};
#endif
