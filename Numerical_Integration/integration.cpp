#include <iostream>
#include <cmath>
using namespace std;

struct Function {
  double (*fun)(double);
  Function* pun;
};

double evaluate(const Function* function, const double arg) {
  return (*function->fun)(arg);
}

double integrate_midpoint(const double a, const double b, const int steps, const Function* function) {
  double integral = 0;
  for(int k = 0; k < steps - 1; k++) {
    double delta = (b - a) / steps;
    double integrationPoint = delta * k + a ;
    integral += evaluate(function, integrationPoint) * delta;
  }
  return integral;
}

int main() {
  //Compute the definite integral of the function sin(x) from bound a to bound b using a method of numerical integration
  cout << "Insert values for bound a and b:" << endl;
  double a, b;
  cin >> a;
  cin >> b;
  cout << "Insert the amount of integration steps:" << endl;
  int steps;
  cin >> steps;

  Function* function = new Function;
  function->fun = atan;
  
  cout << "The calculated integral is " << integrate_midpoint(a, b, steps, function) << endl;

  delete function;
  return 0;
}
