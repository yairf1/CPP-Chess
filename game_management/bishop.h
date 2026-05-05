#include "piece.h"

class Bishop : public Piece
{
private:

public:
    Bishop();
    ~Bishop();

    bool isMoveValid(const short src, const short dest) const override;
    vector <short> getPath(const short src, const short dest) const override;
};


