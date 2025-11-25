/* 
Filename: player.cc
Author: Josh Stein
Date: 2024-06-15
Last Edited: 2024-06-15

Description:
This file contains the player class definition that manages player state
*/

export module Player

export class Player {
    Board* board;
    int curScore;
    int playerId;

    Player() = default;

    int getCurScore();
    int getPlayerId();

    ___ applySpecialAction(); // will add parameters later
    ___ calcualteLineScore(int linesCleared)
    ___ calculateBlockScore(Block *b);
};
