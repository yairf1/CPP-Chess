#pragma once

#include "game_management/board.h"

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(){
    Board board;

    string boardString = board.getBoardString();
    short player = board.getCurrentTurn();
    string move;


    while (true)
    {
        try
        {
            boardString = board.getBoardString();
            player = board.getCurrentTurn();
            
            for (int i = 0; i < 64; i += 8)
            {
                cout << boardString.substr(i, 8) << endl;
            }
            
            cout << "turn of " << (player == 0 ? "white" : "black") << endl;
            
            cin >> move;
            cout << "move is: " << move << endl;
            
            cout << board.move(move) << endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            system("PAUSE");
        }
        
        
    }
    

    return 0;
}

