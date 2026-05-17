#include "pawn.h"

Pawn::Pawn(){}
Pawn::~Pawn(){}

bool Pawn::isMoveValid(const short src, const short dest) const {
    int srcRow = src / 8;
    int srcCol = src % 8;

    int destRow = dest / 8;
    int destCol = dest % 8;

    // return true for every valid normal/first/capture move
    if ((srcCol == destCol && (abs(srcRow - destRow) == 2 || abs(srcRow - destRow) == 1)) || (abs(srcCol - destCol) == 1 && abs(srcRow - destRow) == 1)){
        return true;
    }

    return false;
}

vector <short> Pawn::getPath(const short src, const short dest) const {
    vector <short> result;
    int srcRow = src / 8;
    int srcCol = src % 8;

    int destRow = dest / 8;
    int destCol = dest % 8;

    int step = destRow > srcRow ? 1 : -1;

    // for first move return the path, for elimination and normal move there is no path
    if (srcCol == destCol && abs(srcRow - destRow) == 2)
    {
        for (short i = srcRow + step; i != destRow; i += step)
        {
            result.push_back(i * 8 + srcCol);
        }
    }
    
    return result;
}

Pawn::PawnMoveType Pawn::getMoveType(const short src, const short dest) const{
    int srcRow = src / 8;
    int srcCol = src % 8;

    int destRow = dest / 8;
    int destCol = dest % 8;

    if (srcCol == destCol && abs(srcRow - destRow) == 2){
        return PawnMoveType::first; 
    }

    if (srcCol == destCol && abs(srcRow - destRow) == 1){
        return PawnMoveType::normal; 
    }

    if (abs(srcCol - destCol) == 1 && abs(srcRow - destRow) == 1){
        return PawnMoveType::capture; 
    }

    return PawnMoveType::error;
}