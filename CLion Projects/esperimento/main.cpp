#include <iostream>
using namespace std;

class stringa {
  char* str;
public:
  stringa(char* c) {
    str = c;
  }
  friend ostream& operator<<(ostream& stream, stringa& str);
};

ostream& operator<<(ostream& stream, stringa& str) {
  cout << str.str;
  return stream;
}

int main() {
  stringa str = "prova";
  stringa str2 = "provina";
  cout << "Stringa 1: " << str << endl;
  cout << "Stringa 2: " << str2 << endl;
  return 0;
}
