/* 
Filename: board.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file contains the interface of the Board class, which manages the game board state,
including block placement, movement, level management, and game over conditions.
*/


export module Board;

import <utility>;
import <vector>;
import <memory>;
import Block;
import IBlock; 
import JBlock;
import LBlock;
import OBlock;
import SBlock;
import TBlock;
import ZBlock;
import Level;
import LevelFactory;

using namespace std;

export class Board {
    // private memeber variables
    int width;
    int height;
    shared_ptr<Block> nextBlock;
    shared_ptr<Block> activeBlock;
    unique_ptr<Level> level;
    vector<vector<shared_ptr<Block>>> grid; // grid[col][row]
    bool gameOver;
    string sequenceFile;
    LevelFactory levelFactory;
    shared_ptr<Block> generateBlock(char type);
    
    // private methods
    bool isValidMove(vector<std::pair<int, int>> newPosn) const;
    void clearBlock(shared_ptr<Block> block);
    void placeBlock(shared_ptr<Block> block);
    bool checkGameOver();

    public:
        /*
        Purpose: constructor for Board class. 
        @param: width - width of the board (default 11)
                 height - height of the board (default 18)
                 startLevel - starting level of the game (default 0)
                 sequenceFile - file path for block sequence (default "")
        returns: Board object
        */
        Board(const int width = 11, const int height = 18, int startLevel = 0, string sequenceFile = "");

        /*
        Purpose: Get the width of the board.
        @param: None
        returns: width of the board
        */
        int getWidth();

        /*
        Purpose: Get the height of the board.
        @param: None
        returns: height of the board
        */
        int getHeight();

        /*
        Purpose: Get the next block to be played.
        @param: None
        returns: shared pointer to the next Block (so we don't have to manage memory ourselves)
        */
        shared_ptr<Block> getNextBlock() const;

        /*
        Purpose: Get the currently active block on the board.
        @param: None
        returns: shared pointer to the next Block (so we don't have to manage memory ourselves)
        */
        shared_ptr<Block> getActiveBlock() const;

        /*
        Purpose: Get the current level of the game.
        @param: None
        returns: pointer to the current Level
        */
        Level* getLevel() const;

        /*
        Purpose : Get the current grid of the board.
        @param: None
        returns: reference to the 2D vector grid of shared pointers to Blocks
        */
        const vector<vector<shared_ptr<Block>>>& getGrid() const;

        /*
        Purpose: Check if the game is over.
        @param: None
        returns: true if the game is over, false otherwise
        */
        bool isGameOver() const;


        /*
        Purpose: Set the board to use a non-random level based on the provided file. Replaces 
            the current level with another level pointer that generate blocks in a non-random order.
        @param: file - input file stream containing the block sequence
        returns: None
        requires: file is a valid ifstream object
        */
        void noRandomLevel(ifstream& file);

        // Restore randomness
        /*
        Purpose: Restore the board to use a random level, replacing the current level
            with another level pointer that generates blocks randomly.
        @param: None
        returns: None
        */
        void restoreRandomLevel();
       
        /*
        Purpose: Drop the active block to the lowest valid position on the board.
        @param: None
        returns: true if the block was successfully dropped, false otherwise
        */
        bool drop();

        /*
        Purpose: Drop the specified block from its initial position to the lowest valid position on the board.
        @param: block - shared pointer to the Block to be dropped
        returns: true if the block was successfully dropped, false otherwise
        */
        bool dropBlock(shared_ptr<Block> block); //Drops block from its own initial position

        /*
        Purpose: Move the active block by the specified x and y offsets. Check whether the move is valid, 
            first and if it is then move, if not do nothing
        @param: x - horizontal offset (positive for right, negative for left)
                 y - vertical offset (positive for down, negative for up)
        returns: true if the block was successfully moved, false otherwise
        // requires: activeBlock is a valid shared pointer to a Block
        */
        bool move(int x, int y); //Linh added this

        /*
        Purpose: Advance to the next turn by replacing the active block with the next block,
            generating a new next block, and checking for game over conditions. Also generates new 
            nextBlock and make the old nextBlock the activeBlock after a block is dropped.
        @param: None
        returns: None
        */
        void nextTurn(); //Linh added this

        /*
        Purpose: Increase the game level by 1.
        @param: None
        returns: None
        */
        void levelUp();

        /*
        Purpose: Decrease the game level by 1.
        @param: None
        returns: None
        */
        void levelDown();

        /*
        Purpose: Set the current level to a new level.
        @param: newLevel - unique pointer to the new Level
        returns: None
        */
        void setLevel(unique_ptr<Level> newLevel);

        /*
        Purpose: Rotate the active block clockwise or counterclockwise.
        @param: clockwise - true for clockwise rotation, false for counterclockwise
        returns: None
        */
        void rotate(bool clockwise);
        
        /*
        Purpose: Force the next block to be of the specified type.
        @param: type - character representing the block type (I, J, L, O, S, T, Z)
        returns: None
        */
        void forceBlockType(char type);

        /*
        Purpose: Apply heaviness to the active block, moving it down additional rows if possible.
            Note: logic is different depending on level's heaviness factor.
        @param: additionalHeavy - number of additional rows to move the block down
        returns: true if the block was auto-dropped due to heaviness, false otherwise
        */
        bool applyHeavy(int additionalHeavy);

        /*
        Purpose: Check for completed rows on the board.
        @param: None
        returns: vector of row indices that are completed
        */
        vector<int> checkCompletedRows();

        /*
        Purpose: Clear the specified row from the board, shifting all rows above it down.
        @param: row - index of the row to be cleared
        returns: score obtained from clearing the row
        */
        int clearRow(int row);

        /*
        Purpose: Destructor for Board class.
        @param: None
        returns: None
        */
        ~Board();
};

// Note: After a block is considered "drop", what class call the next behaviours (replace activeBlock with nextBlock, generate nextBlock)
