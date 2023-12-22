#include <iostream>

#ifndef BUBBLE_BOBBLE_COMPITO_H
#define BUBBLE_BOBBLE_COMPITO_H

static const int NUM_ROW = 10;
static const int NUM_COL = 6;

class PuzzleBobble {
private:
    char _schema[NUM_ROW][NUM_COL];
public:
    PuzzleBobble();
    PuzzleBobble& fire(int i, char color);
    PuzzleBobble& scroll();
    PuzzleBobble& compact();
    operator int() const;
    friend std::ostream& operator<<(std::ostream& st, PuzzleBobble& pb);
};


#endif //BUBBLE_BOBBLE_COMPITO_H
