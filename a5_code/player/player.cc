/* 
Filename: player.cc
Author: Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the player class definition that manages player state
*/

export module Player

import Board;
import <string>;

using namespace std;

export class Player {
    Board* board;
    string name;
    int curScore;
    int playerId;

    public: 
        // need a ctor, move ctor, copy ctor, copy asop, move asop and destructor later
        Player();
        Player(Board* b, int curScore, int playerId, string name);
        
        string getName() const;
        int getCurScore() const;
        int getPlayerId() const;

        void applySpecialAction(); // will add parameters later
        int calculateLineScore(int linesCleared);
        int calculateBlockScore(Block *b);
};
