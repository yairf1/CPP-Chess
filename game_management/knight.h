#include "piece.h"
#include <vector>
#include <cmath>

class Knight : public Piece
{
private:

public:
    Knight();
    ~Knight();

    bool isMoveValid(const short src, const short dest) const override;
    vector <short> getPath(const short src, const short dest) const override;
};


