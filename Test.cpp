#pragma once

#include "game_management/board.h"

#include <iostream>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(){
    Board board;

    string boardString = board.getBoardString();
    short player = board.getCurrentTurn();

    cout << boardString.substr(0, 8) << endl;
    cout << boardString.substr(8, 8) << endl;
    cout << boardString.substr(16, 8) << endl;
    cout << boardString.substr(24, 8) << endl;
    cout << boardString.substr(32, 8) << endl;
    cout << boardString.substr(40, 8) << endl;
    cout << boardString.substr(48, 8) << endl;
    cout << boardString.substr(56, 8) << endl;
    cout << "turn of" << player << endl;
    
    cout << board.move("d8d7") << endl;
    
    boardString = board.getBoardString();
    cout << boardString.substr(0, 8) << endl;
    cout << boardString.substr(8, 8) << endl;
    cout << boardString.substr(16, 8) << endl;
    cout << boardString.substr(24, 8) << endl;
    cout << boardString.substr(32, 8) << endl;
    cout << boardString.substr(40, 8) << endl;
    cout << boardString.substr(48, 8) << endl;
    cout << boardString.substr(56, 8) << endl;


    return 0;
}

