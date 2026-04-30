#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Piece
{
private:

public:
    Piece();
    virtual ~Piece();

    virtual bool isMoveValid(const short src, const short dest) const = 0;
    virtual vector <short> getPath(const short src, const short dest) const = 0;

};
