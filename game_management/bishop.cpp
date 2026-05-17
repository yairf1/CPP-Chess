

#include "bishop.h"

Bishop::Bishop(){}
Bishop::~Bishop(){}

bool Bishop::isMoveValid(const short src, const short dest) const {
    int srcRow = src / 8;
    int srcCol = src % 8;

    int destRow = dest / 8;
    int destCol = dest % 8;
    
    return abs(srcRow - destRow) == abs(srcCol - destCol) && src != dest;
    
}

vector <short> Bishop::getPath(const short src, const short dest) const {
    vector <short> result;
    
    int srcRow = src / 8;
    int srcCol = src % 8;
    
    int destRow = dest / 8;
    int destCol = dest % 8;

    int rowStep = srcRow < destRow ? 1 : -1;
    int colStep = srcCol < destCol ? 1 : -1;

    short rowMove = srcRow + rowStep;
    short colMove = srcCol + colStep;

    while (rowMove != destRow && colMove != destCol)
    {
        result.push_back(rowMove * 8 + colMove);

        rowMove += rowStep;
        colMove += colStep;
    }

    return result;
}