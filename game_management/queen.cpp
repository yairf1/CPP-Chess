#include "queen.h"
#include "rook.h"
#include "bishop.h"

Queen::Queen(){}
Queen::~Queen(){}

bool Queen::isMoveValid(const short src, const short dest) const {
    return Rook().isMoveValid(src, dest) || Bishop().isMoveValid(src, dest);
}
vector <short> Queen::getPath(const short src, const short dest) const {
    Rook r;
    Bishop b;

    if (r.isMoveValid(src, dest)) return r.getPath(src, dest);
    if (b.isMoveValid(src, dest)) return b.getPath(src, dest);

    return {};
}