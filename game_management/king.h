#pragma once
#include "piece.h"

#include <vector>
#include <cmath>

using std::string;
using std::vector;

class King : public Piece
{
private:

public:
    King();
    ~King();

    bool isMoveValid(const short src, const short dest) const override;
    vector <short> getPath(const short src, const short dest) const override;

};