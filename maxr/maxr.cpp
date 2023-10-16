#include <iostream>
using namespace std;

int& maxr(int& ra, int& rb) {
	if(ra >= rb) return ra;
	return rb;
}

int main() {
	int x, y;
	cin >> x >> y;
	maxr(x,y) = 0; //<-- maxr restituisce un riferimento al valore maggiore tra x e y, che poi rendo uguale a 0
	cout << x << " " << y;
	return 0;
}