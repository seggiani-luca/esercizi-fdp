#include <iostream>
#include <cstring>
using namespace std;
struct punto
{
    float x;
    float y;
};
int main ()
{
// definizione di due elementi di tipo "punto"
    punto p1;
    p1.x=3.3;
    p1.y=1.1;
    punto p2;
    p2=p1;
// definizione di un array di 3 interi
    int v[3];
    int i=0;
    while (i<3)
    {
        v[i] = i;
        i++;
    }
    v[4]=123;
// definizione di una stringa
    char w[14];
    strcpy(w, "si");
    strcpy(w, "informatica");
// stampa della stringa
    cout << w << endl;
    return 0;
}