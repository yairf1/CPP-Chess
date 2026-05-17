#include "stdafx.h"
#include "knight.h"

Knight::Knight(){}
Knight::~Knight(){}

bool Knight::isMoveValid(const short src, const short dest) const {
    int srcRow = src / 8;
    int srcCol = src % 8;

    int destRow = dest / 8;
    int destCol = dest % 8;

    return (abs(destRow - srcRow) == 1 && abs(destCol - srcCol) == 2) || (abs(destRow - srcRow) == 2 && abs(destCol - srcCol) == 1);
}

vector <short> Knight::getPath(const short src, const short dest) const {
    vector <short> result;
    return result;
}