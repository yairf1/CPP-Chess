#pragma once
#include <iostream>
#include <string>
#include <cctype>

#include "piece.h"
#include "king.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"

using std::cout;
using std::endl;
using std::string;

class Board
{
private:
    // saving the board state as string
    string m_boardString;
    // return codes
    enum m_codes {valid_move, valid_and_checked, src_free, dest_occupied, self_check, invalid_index, invalid_move, src_equals_dest, valid_checkmate};
    // saving the current player
    enum class m_player {white, black};
    m_player currentTurn;

    // ===== validations methods =====

    bool isInTheBoard(const short& src, const short& dest) const;
    bool isDestSelfOccupied(const short& dest) const;
    bool isSrcSelfFree(const short& src) const;
    bool isDestSameAsSrc(const short& src, const short& dest) const;
    
    bool isEnemyPiece(const short& dest) const;
    bool isKingInCheck(const short& dest, Piece* piece) const;
    bool isCheckmate(const vector <short>& path, const short& src, const short& dest, Piece* piece) const;
    bool isMoveBlocked(const vector <short>& path, const short& dest) const;
    bool isSelfCheck(const short& src = 0, const short& dest = 0) const;
    bool isPawnMoveValid(const short& src, const short& dest) const;
    short getKingPos(m_player color) const;

    // ===== validations methods =====

    // modifier for changing turns
    void passTurn();
    // modifier to move a piece in the _boardString
    void movePiece(const short& src, const short& dest);
    
public:
    Board(m_player currentTurn = m_player::white, string boardString = "RNBKQBNRPPPPPPPP################################pppppppprnbqkbnr0 " );
    ~Board();
    
    // move the piece after validations and return the code or dont move and return err code
    short move(string command);
    
    // simple getters
    string getBoardString() const;
    short getCurrentTurn() const;
};



