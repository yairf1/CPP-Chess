#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "piece.h"

using std::cerr;
using std::string;
using std::vector;

class King : public Piece
{
private:
    string _type;
public:
    King();
    ~King();

    bool isMoveValid(const short src, const short dest) const override;
    vector <short> getPath(const short src, const short dest) const override;

};