#include "rook.h"

Rook::Rook(){}

Rook::~Rook(){}

bool Rook::isMoveValid(const short src, const short dest) const {
    int srcRow = src / 8;
    int srcCol = src % 8;

    int destRow = dest / 8;
    int destCol = dest % 8;

    // if moving on the same row or colum, move is valid
    return (srcRow == destRow || srcCol == destCol) && src != dest;

    
}
vector <short> Rook::getPath(const short src, const short dest) const {
    vector <short> result;

    int srcRow = src / 8;
    int srcCol = src % 8;

    int destRow = dest / 8;
    int destCol = dest % 8;

    if (srcRow == destRow)
    {
        int step = destCol > srcCol ? 1 : -1;
        for (short i = srcCol + step; i != destCol; i += step)
        {
            result.push_back(i + srcRow * 8);
        }
        
    } else if (srcCol == destCol) {
        int step = destRow > srcRow ? 1 : -1;
        for (short i = srcRow + step; i != destRow; i += step)
        {
            result.push_back(i * 8 + srcCol);
        }
        
    }

    return result;
}