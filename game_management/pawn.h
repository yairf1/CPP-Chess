#include "piece.h"

class Pawn : public Piece
{
private:

public:
    // move types
    enum class PawnMoveType {normal, capture, first, error};
    
    Pawn();
    ~Pawn();

    bool isMoveValid(const short src, const short dest) const override;
    vector <short> getPath(const short src, const short dest) const override;

    // return the move type for validations on the board
    PawnMoveType getMoveType(const short src, const short dest) const;

};


