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
    bool shouldTriggerSpecialEffects;
    string renderEffect; 

    public: 
        /*
        Purpose: constructor for Player class.
        @params: curScore - current score of the player
                playerId - unique identifier for the player
                name - name of the player
                sequenceFile - file containing the block sequence for the player
        returns: Player object
        */
        Player(int curScore, int playerId, string name, string sequenceFile);

        /*
        Purpose: constructor for Player class with starting level.
        @params: curScore - current score of the player
                playerId - unique identifier for the player
                name - name of the player
                sequenceFile - file containing the block sequence for the player
                startLevel - level at which the player starts
        returns: Player object
        */
        Player(int curScore, int playerId, string name, string sequenceFile, int startLevel);
        
        /*
        Purpose: getter for the player's board.
        @params: None
        returns: pointer to the player's Board object
        */
        Board* getBoard() const;

        /*
        Purpose: getter for the player's name.
        @params: None
        returns: string representing the player's name
        */
        string getName() const;

        /*
        Purpose: getter for the player's current score.
        @params: None
        returns: integer representing the player's current score
        */
        int getCurScore() const;

        /*
        Purpose: getter for the player's unique identifier.
        @params: None
        returns: integer representing the player's ID
        */
        int getPlayerId() const;
        
        /*
        Purpose: applySpecialAction works by applying a special action for the player.
        @params: None
        returns: None
        */
        void applySpecialAction();

        /*
        Purpose: reset the player's state, including the board and score.
        @params: None
        returns: None
        */
        void reset();

        /*
        Purpose: addScore adds the specified score to the player's current score.
        @params: score - integer score to be added
        returns: None
        */
        void addScore(int score);

        /*
        Purpose: dropBlock works by dropping the active block on the player's board.
        @params: None
        returns: true if the turn has ended, false otherwise
        */
        bool dropBlock();

        /*
        Purpose: moveBlock works by moving the active block on the player's board by the specified x and y offsets.
        @params: x - integer offset in the x direction
                y - integer offset in the y direction
        returns: true if the move was successful, false otherwise
        */
        bool moveBlock(int x, int y);

        /*
        Purpose: moveBlockTo works by moving the active block to the specified absolute 
                coordinates on the player's board.
        @params: x - integer x coordinate
                y - integer y coordinate
        returns: true if the move was successful, false otherwise
        */
        void rotate(bool clockwise);

        /*
        Purpose: levelUp increases the player's board level by 1.
        @params: None
        returns: None
        */
        void levelUp();

        /*
        Purpose: levelDown decreases the player's board level by 1.
        @params: None
        returns: None
        */
        void levelDown();
        
        /*
        Purpose: addHeaviness increases the heaviness of the player's blocks by the specified amount.
        @params: amount - integer amount to increase heaviness
        returns: None
        */
        void addHeaviness(int amount);

        /*
        Purpose: resetHeaviness resets the additional heaviness of the player's blocks to zero.
        @params: None
        returns: None
        */
        void resetHeaviness();

        /*
        Purpose: getAdditionalHeaviness returns the additional heaviness of the player's blocks.
        @params: None
        returns: integer representing the additional heaviness
        */
        int getAdditionalHeaviness() const;
        
        /*
        Purpose: applyEffects works by applying any special effects to the player's board after each command.
        @params: None
        returns: true if the turn has ended, false otherwise
        */
        bool applyEffects();

        /*
        Purpose: hasSpecialEffects checks if the player has any special effects active.
        @params: None
        returns: true if special effects are active, false otherwise
        */
        bool hasSpecialEffects() const;

        /*
        Purpose: resetSpecialEffects resets the special effects for the player.
        @params: None
        returns: None
        */
        void resetSpecialEffects();
        
        /*
        Purpose: setRenderEffect sets a render effect for the player.
        @params: effect - string representing the render effect to be set
        returns: None
        */
        void setRenderEffect(const string& effect);

        /*
        Purpose: getRenderEffect returns the current render effect for the player.
        @params: None
        returns: string representing the current render effect
        */
        string getRenderEffect() const;

        /*
        Purpose: resetRenderEffect resets the render effect for the player.
        @params: None
        returns: None
        */
        void resetRenderEffect();
};
