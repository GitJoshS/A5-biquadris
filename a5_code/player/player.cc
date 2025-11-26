/* 
Filename: player.cc
Author: Josh Stein
Date: 2024-06-15
Last Edited: 2024-06-15

Description:
This file contains the player class definition that manages player state
*/

export module Player

import Board;
import <string>;

export class Player {
    Board* board;
    string name;
    int curScore;
    int playerId;

    // need a ctor, move ctor, copy ctor, copy asop, move asop and destructor later
    Player();
    Player(Board* b, string name, int curScore int playerId);

    public: 
        int getCurScore();
        int getPlayerId();

        void applySpecialAction(); // will add parameters later
        int calcualteLineScore(int linesCleared)
        int calculateBlockScore(Block *b);
};
