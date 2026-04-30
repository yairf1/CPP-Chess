#pragma once

#include <cctype>

#include "board.h"
#include "piece.h"
#include "rook.h"
#include "king.h"

Board::Board(){
    this->currentTurn = m_player::white;
    // debuging string
    this->m_boardString = "R##K###R################################################r###k##r0 ";
    // this->m_boardString = "RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr0 ";
}

Board::~Board(){}

// helper method - turning string to index
int toIndex(const string& pos) {
    int col = pos[0] - 'a';
    int row = '8' - pos[1];
    return row * 8 + col;
}

// helper method - create new piece pointer with the string value
Piece* createPiece(char& c) {
    switch (c) {
        case 'r': case 'R': return new Rook();
        case 'k': case 'K': return new King();
        // case 'b': case 'B': return new Bishop();
        // case 'q': case 'Q': return new Queen();
        // case 'n': case 'N': return new Knight();
        // case 'p': case 'P': return new Pawn();
        
    }
    return nullptr;
}

// helper method - get King position by color, return index of king
short Board::getKingPos(m_player color) const{
    if (color == m_player::white) {  
        return m_boardString.find('K'); 
    }else {
        return m_boardString.find('k');
    }
}

// passing the turn to the other player
void Board::passTurn() {
    currentTurn == m_player::white ? currentTurn = m_player::black : currentTurn = m_player::white;
    
}

void Board::movePiece(const short& src, const short& dest){
    // move piece to src then clear src
    this->m_boardString[dest] = this->m_boardString[src];
    this->m_boardString[src] = '#';
}

// validate the move, if valid passing the turn to the other player
short Board::move(string command){
    string srcString = command.substr(0, 2);
    string destString = command.substr(2, 2);
    short src = toIndex(srcString);
    short dest = toIndex(destString);
    Piece* piece = nullptr;

    // board tiles validations
    if (!this->isInTheBoard(src, dest)){ return m_codes::invalid_index; }
    if (this->isDestSelfOccupied(dest)){ return m_codes::dest_occupied; }
    if (this->isSrcSelfFree(src)){ return m_codes::src_free; }
    if (this->isDestSameAsSrc(src, dest)){ return m_codes::src_equals_dest; }

    // piece movment validations
    piece = createPiece(m_boardString[src]);
    if (!piece)
    {
        throw std::runtime_error("unknown piece type");
    }
    
    auto path = piece->getPath(src, dest);

    if ( this->isMoveBlocked(path, dest) || !piece->isMoveValid(src, dest)){ 
        delete piece;
        piece = nullptr;
        return m_codes::invalid_move;
    }

    // validations of check and checkmate
    if (this->isSelfCheck(src, dest)){ 
        delete piece;
        piece = nullptr;
        return m_codes::self_check; 
    }

    if (this->isCheckmate(path, dest, piece)){
        movePiece(src, dest);
        passTurn();
        delete piece;
        piece = nullptr;
        return m_codes::valid_checkmate;
    }

    if (this->isKingInCheck(dest, piece)){
        movePiece(src, dest);
        passTurn();
        delete piece;
        piece = nullptr;
        return m_codes::valid_and_checked; 
    }
    
    // if neither of the special codes, return valid_move and pass turn
    movePiece(src, dest);
    passTurn();
    delete piece;
    piece = nullptr;
    return m_codes::valid_move;
    
}

// ===== validations methods =====
// for all methods if not valid return the required code, if valid return valid_move code

    bool Board::isInTheBoard(const short& src, const short& dest) const{
        if (src >= 0 && src < 64 && dest >= 0 && dest < 64)
        {
            return true;
        }
        return false;
    }

    bool Board::isDestSelfOccupied(const short& dest) const{
        // check if there is a piece with the same color
        char destPiece = m_boardString[dest];
        if (currentTurn == m_player::white && isupper(destPiece))
        {
            return true;
        } if (currentTurn == m_player::black && islower(destPiece)) {
            return true;
        }

        return false;
    }

    bool Board::isSrcSelfFree(const short& src) const{
        // check if there is a piece with the same color
        char destPiece = m_boardString[src];
        if (currentTurn == m_player::white && isupper(destPiece))
        {
            return false;
        } if (currentTurn == m_player::black && islower(destPiece)) {
            return false;
        }

        return true;
    }

    bool Board::isDestSameAsSrc(const short& src, const short& dest) const{
        return src == dest ? true : false;
    }

    bool Board::isEnemyPiece(const short& dest) const{
        char destPiece = m_boardString[dest];

        if (destPiece == '#'){
            return false;
        }

        if (currentTurn == m_player::black && std::isupper(destPiece)) {
            return true;
        }

        if (currentTurn == m_player::white && std::islower(destPiece)) {
            return true;
        }

        return false;
    }

    bool Board::isKingInCheck(const short& dest, Piece* piece) const{
        short kingPos = getKingPos(currentTurn == m_player::white ? m_player::black : m_player::white);

        if (piece->isMoveValid(dest, kingPos) && !this->isMoveBlocked(piece->getPath(dest, kingPos), dest)){
            return true;
        }

        return false;
    }

    bool Board::isCheckmate(const vector <short>& path, const short& dest, Piece* p) const{
        if (!this->isKingInCheck(dest, p)) return false;

        short kingPos = getKingPos(currentTurn == m_player::white ? m_player::black : m_player::white);
        // check if the king can escape
        short row = kingPos / 8;
        short col = kingPos % 8;

        // move values for row and colum
        short dRow[] = {1, 1, 1, 0, 0, -1, -1, -1};
        short dCol[] = {1, 0, -1, 1, -1, 0, 1, -1};
        
        for (short i = 0; i < 8; i++)
        {
            short newRow = row + dRow[i];
            short newCol = col + dCol[i];

            // if the move is in the board, check if the move is valid
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
            {
                short newIndex = newRow * 8 + newCol;

                if (!isDestSelfOccupied(newIndex) && !isSelfCheck(kingPos, newIndex) && newIndex >= 0 && newIndex < 64){
                    return false;
                }
            }
        }
        
        // check if there is an available piece to block the checkmate or eliminate the threatening piece
        Piece* piece = nullptr;
        for (int i = 0; i < 64; i++)
        {
            char destPiece = m_boardString[i];
            if (destPiece == '#') continue;
            piece = createPiece(destPiece);

            for (auto &&tile : path)
            {
                auto piecePath = piece->getPath(i, tile);

                if(currentTurn == m_player::white && std::isupper(destPiece)){
                    if (piece->isMoveValid(i, tile) && !this->isMoveBlocked(piecePath, dest) && !this->isSelfCheck(i, tile))
                    {
                        delete piece;
                        piece = nullptr;
                        return false;
                    }
                }

                if(currentTurn == m_player::black && std::islower(destPiece)){
                    if (piece->isMoveValid(i, tile) && !this->isMoveBlocked(piecePath, dest) && !this->isSelfCheck(i, tile))
                    {
                        delete piece;
                        piece = nullptr;
                        return false;
                    }
                        
                }
            }
        }

        delete piece;
        piece = nullptr;
        return true;
        
    }

    bool Board::isMoveBlocked(const vector<short>& path, const short& dest) const {

        for (int i = 0; i < path.size(); i++) {
            if (m_boardString[path[i]] != '#') {
                return true;
            }
        }

        char destPiece = m_boardString[dest];

        if (destPiece == '#') {
            return false;
        }

        if ( isEnemyPiece(dest)) {
            return false;
        }

        return true;
    }

    bool Board::isSelfCheck(const short& src, const short& dest) const{
        // making the temporary move to tmp string to validate self check
        string tmpBoard = m_boardString;
        short tmpSrc = tmpBoard[src];
        tmpBoard[src] = '#';
        tmpBoard[dest] = tmpSrc;

        int kingPos = getKingPos(currentTurn);
        Piece* piece = nullptr;

        for (int i = 0; i < 64; i ++)
        {
            if (tmpBoard[i] == '#') continue;
            piece = createPiece(tmpBoard[i]);
            auto piecePath = piece->getPath(i, kingPos);

            // for white player check black pieces by checking if lower case
            if (currentTurn == m_player::white && islower( tmpBoard[i])){
                if (piece->isMoveValid(i, kingPos) && !this->isMoveBlocked(piecePath, dest)){
                    delete piece;
                    piece = nullptr;
                    return true;
                }
            }

            // for black player check white pieces by checking if upper case
            if (currentTurn == m_player::black && isupper( tmpBoard[i])){
                if (piece->isMoveValid(i, kingPos) && !this->isMoveBlocked(piecePath, dest)){
                    delete piece;
                    piece = nullptr;
                    return true;
                }
            }

            delete piece;
            piece = nullptr;
        }
        
        piece = nullptr;
        return false;
    }

// ===== validations method =====

// simple getters
string Board::getBoardString() const{
    return m_boardString;
}

short Board::getCurrentTurn() const{
    return currentTurn == m_player::white ? 0 : 1;
}