#include "piece.h"

class Rook : public Piece
{
private:
    string _type;
public:
    Rook();
    ~Rook();

    bool isMoveValid(const short src, const short dest) const override;
    vector <short> getPath(const short src, const short dest) const override;
};


