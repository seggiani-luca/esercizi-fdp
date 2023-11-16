#include <iostream>
using namespace std;
int f(int a)
{
    a *= 2;
    return a;
}
int main()
{
    int n;
    n=2;
    int*p;
    p = &n;
    *p = 5;
    int& r=n;
    r = 9;
    int m = f(n);
    cout << n << " " << m << endl;
    return 0;
}