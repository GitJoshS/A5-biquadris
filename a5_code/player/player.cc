/* 
Filename: player.cc
Author: Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the player class definition that manages player state
*/

export module Player;

import Board;
import <string>;
import <memory>;
import LevelFactory;

using namespace std;

export class Player {
    unique_ptr<Board> board; 
    int curScore;    
    int playerId;         
    string name;                  
    string sequenceFile;
    LevelFactory levelFactory;
    int additionalHeaviness; 

    public: 
        // need a ctor, move ctor, copy ctor, copy asop, move asop and destructor later
        Player();
        Player(int curScore, int playerId, string name, string sequenceFile);
        
        Board* getBoard() const;
        string getName() const;
        int getCurScore() const;
        int getPlayerId() const;
        
        void applySpecialAction(); // will add parameters later
        void reset();
        void addScore(int score);
        bool dropBlock();
        bool moveBlock(int x, int y);
        void rotate(bool clockwise);
        void levelUp();
        void levelDown();
        
        void addHeaviness(int amount);
        void resetHeaviness();
        int getAdditionalHeaviness() const;
        
        bool applyEffects();
        bool hasSpecialEffects() const;
};
