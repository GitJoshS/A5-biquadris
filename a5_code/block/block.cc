/* 
Filename: block.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file is the interface for the Block class, which represents individual blocks and is a 
super class for all specific block types in the Biquadris game.
*/

export module Block;

import <string>;
import <utility>;
import <vector>;

using namespace std; 

export class Block {
    // protected member variables (protected so derived classes can access them)
    protected:
        char blockType;
        int levelGenerated;
        int cellsLeft;
        vector<pair<int,int>> cells; //Position of the cells in the block on a board

    public:
        /*
        Purpose: constructor for Block class.
        @param: blockType - character representing the block type (I, J, L, O, S, T, Z)
                levelGenerated - level at which the block was generated
                cellsLeft - number of cells left in the block
                cells - vector of pairs representing the coordinates of the block's cells
        returns: Block object
        */
        Block(char blockType, int levelGenerated, int cellsLeft, vector<pair<int,int>> cells);
        
        /*
        Purpose: Calculate the new positions of the block's cells after rotation.
                Returns the coordinate of the new position if the block to be rotated
        @param: clockwise - true for clockwise rotation, false for counterclockwise
        returns: vector of pairs representing the new coordinates after rotation
        */
        vector<pair<int,int>> rotatePosition(bool clockwise);

        /*
        Purpose: Set the position of the block to a new position. 
        @param: newPos - vector of pairs representing the new coordinates for the block's cells
        returns: None
        */
        void setPosition(vector<pair<int,int>>& newPos);

        /*
        Purpose: Decrease the number of cells left in the block by 1. Note, When a cell in a block 
        is destroyed, decrease the amount of cell that block has by 1. If it reaches 0, return true. Otherwise, return false
        @param: None
        returns: true if cellsLeft reaches 0, false otherwise
        */
        bool decreaseCells();

        /*
        Purpose: Get the level at which the block was generated.
        @param: None
        returns: integer representing the level generated
        */
        int getLevelGenerated();

        /*
        Purpose: Get the type of the block.
        @param: None
        returns: character representing the block type
        */
        virtual char getType();

        /*
        Purpose: Get the current position of the block's cells. 
        @param: None
        returns: vector of pairs representing the coordinates of the block's cells
        */
        virtual vector<pair<int,int>> getPosition();

        /*
        Purpose: Virtual destructor for Block class to ensure proper cleanup of derived classes.
        @param: None
        returns: None
        */
        virtual ~Block() = default;
};
