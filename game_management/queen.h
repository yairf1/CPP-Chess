#include "piece.h"

class Queen : public Piece
{
private:

public:
    Queen();
    ~Queen();

    bool isMoveValid(const short src, const short dest) const override;
    vector <short> getPath(const short src, const short dest) const override;
};


