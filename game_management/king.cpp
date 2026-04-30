#include "king.h"

#include <math.h>

King::King(){}

King::~King(){}

bool King::isMoveValid(const short src, const short dest) const{
    short srcRow = src / 8;
    short srcCol = src % 8;
    short destRow = dest / 8;
    short destCol = dest % 8;

    if ((abs(srcCol - destCol) <= 1 && abs(srcRow - destRow) <= 1) && src != dest){
        return true;
    }

    return false;
}
vector <short> King::getPath(const short src, const short dest) const{
    vector <short> result;
    return result;
}