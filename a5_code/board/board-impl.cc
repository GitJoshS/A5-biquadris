/* 
Filename: board-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file contains the implementation of the Board class, which manages the game board state,
including block placement, movement, level management, and game over conditions. 
*/

module Board;

import <utility>;
import <vector>;
import <memory>;
import <fstream>;
import <iostream>;
import Block;
import IBlock;  
import JBlock;
import LBlock;
import OBlock;
import SBlock;
import TBlock;
import ZBlock;
import starBlock;
import Level;
import LevelFactory;

using namespace std;

/*
For Board, we use grid.resize so when calling a Game Instance, we automatically have a grid of width x height
We also need to check startLevel and sequenceFile to initialize the Level pointer correctly as 
if startLevel is 0 and sequenceFile is not empty, we need to create a Level0 with the file but if 
startLevel is not 0, we create a random level without the file.
*/
Board::Board(int width, int height, int startLevel, string sequenceFile) 
    : width{width}, height{height}, gameOver{false}, sequenceFile{sequenceFile} {
    // resize grid
    grid.resize(width, vector<shared_ptr<Block>>(height, nullptr));

    // initialize level
    if (startLevel == 0 && !sequenceFile.empty()) {
        ifstream file(sequenceFile);
        level = levelFactory.create(startLevel, file);
    } else {
        level = levelFactory.create(startLevel);
    }
    // int curLevel = level->getLevel();
    char blockType = level->getNextBlockType();
    activeBlock = generateBlock(blockType);
    placeBlock(activeBlock);
    blockType = level->getNextBlockType();
    nextBlock = generateBlock(blockType);
}

// Gets board Width
int Board::getWidth() {
    return width;
}

// Gets board Height
int Board::getHeight() {
    return height;
}

// Gets next block
shared_ptr<Block> Board::getNextBlock() const {
    return nextBlock;
}

// Gets active block
shared_ptr<Block> Board::getActiveBlock() const {
    return activeBlock;
}

/*
Gets current level, note that we return a raw pointer since Board does not own Level
*/
Level* Board::getLevel() const {
    return level.get();
}

// Gets grid
const vector<vector<shared_ptr<Block>>>& Board::getGrid() const {
    return grid;
}

/*
Checks if game is over, returns bool indicating status. Used by Game class
to check if current player has lost.
*/
bool Board::isGameOver() const {
    return gameOver;
}

/*
noRandomLevel sets the board to use a non-random level based on the provided file.
Replaces the current level with another level pointer that generate blocks in a non-random order.
*/
void Board::noRandomLevel(ifstream& file) {
    int curLevel = level->getLevel();
    level = levelFactory.create(curLevel, file);
}

/*
restoreRandomLevel restores the board to use a random level, replacing the current level
with another level pointer that generates blocks randomly.
*/
void Board::restoreRandomLevel() {
    int curLevel = level->getLevel();
    level = levelFactory.create(curLevel);
}

/*
Checks if the proposed new positions for a block are valid (within bounds and unoccupied).
*/
bool Board::isValidMove(vector<pair<int, int>> newPosn) const { 
    // check each new coordinate of the block
    for (const pair<int, int>& coord : newPosn) {
        int col = coord.first;
        int row = coord.second;
        // if block exists there or out of bounds, not valid
        if ((col >= width || col < 0) || (row >= height || row < 0) || grid[col][row]) {
            return false;
        }
    }
    return true;
}

/*
placeBlock places the given block on the board grid at its current position.
This allows us to visually represent the block on the board. 
*/
void Board::placeBlock(shared_ptr<Block> block) {
     for (const std::pair<int, int>& coord : block->getPosition()) {
        int col = coord.first;
        int row = coord.second;
        grid[col][row] = block;
     }
}

/*
Drop the active block to the lowest valid position on the board.
It does this by iteratively moving the block down until it can no longer move,
then placing it at the last valid position. After dropping, it advances to the next turn. 
*/
bool Board::drop() { 
    vector<pair<int,int>> tempPos;
    while (true) {
        tempPos = activeBlock->getPosition();
        clearBlock(activeBlock);
        for (auto& coord : tempPos) {
            coord.second += 1;  
        }
        if (isValidMove(tempPos)) {
            activeBlock->setPosition(tempPos);
            continue;
        }
        else {
            placeBlock(activeBlock);
            break;
        }
    }
    if (activeBlock->getType() != '*') {
        nextTurn();
        return true;
    }
    return false;
}

/*
dropBlock handles the special case where we need to drop the special (*) block for level 4
in the middle of the board, every 5 turns.
*/
bool Board::dropBlock(shared_ptr<Block> block) { 
    // Place block initially on the board
    cout << "Dropping block: " << block->getType() << endl;
     vector<pair<int,int>> tempPos;
    while (true) {
        tempPos = block->getPosition();
        clearBlock(block);
        for (auto& coord : tempPos) {
            coord.second += 1;  
        }
        if (isValidMove(tempPos)) {
            block->setPosition(tempPos);
            cout << "Block: " << block->getType() << "is at" << block->getPosition()[0].first << " and " << block->getPosition()[0].second << endl;
            placeBlock(block);
            continue;
        }
        else {
            placeBlock(block);
            cout << "Done dropping block: " << block->getType() << endl;
            break;
        }
    }
    if (block->getType() != '*') {
        nextTurn();
        return true;
    }
    return false;
}

/*
Clearboard clears the given block from the board grid at its current position. It does this
by setting the grid cells occupied by the block to nullptr.
*/
void Board::clearBlock(shared_ptr<Block> block) {
    if (!block) return;
    for (const auto& coord : block->getPosition()) {
        int col = coord.first;
        int row = coord.second;
        // Ensure coordinates are within bounds before accessing grid
        if (col >= 0 && col < width && row >= 0 && row < height) {
            grid[col][row] = nullptr; 
        }
    }
}

/*
Move works by first calculating the proposed new positions for the active block based on the given
x and y offsets. It then checks if these new positions are valid using isValidMove.
If the move is valid, it updates the block's position and places it on the board.
*/
bool Board::move(int x, int y) { 
    vector<pair<int, int>> tempPos = activeBlock->getPosition();
    for (auto& coord : tempPos) {
            coord.first += x;
            coord.second += y; 
        } 
    clearBlock(activeBlock);
    if (isValidMove(tempPos)) {
        activeBlock->setPosition(tempPos);
        placeBlock(activeBlock);
        return false;
    } else {
        // Move invalid, put block back at original position
        placeBlock(activeBlock);
        return false;
    }
}

/*
Generates blocks by checking the type character and creating the corresponding block object.
*/
shared_ptr<Block> Board::generateBlock(char type) {
    int lev = level->getLevel();
    switch(type) {
        case 'I': return make_shared<IBlock>(lev);
        case 'J': return make_shared<JBlock>(lev);
        case 'L': return make_shared<LBlock>(lev);
        case 'O': return make_shared<OBlock>(lev);
        case 'S': return make_shared<SBlock>(lev);
        case 'Z': return make_shared<ZBlock>(lev);
        case 'T': return make_shared<TBlock>(lev);
        case '*': return make_shared<starBlock>();
    }
    return nullptr;
}

/*
nextTurn works by setting the active block to the next block, checking for game over conditions,
and generating a new next block based on the current level. If a star block is generated, it is 
immediately dropped before generating the next block as per level 4 rules.
*/
void Board::nextTurn() {
    activeBlock = nextBlock;
    if (!checkGameOver()) {
        placeBlock(activeBlock);
    }
    else {
        gameOver = true;
        return;
    }
    
    // Check if we need to generate a star block
    char blockType = level->getNextBlockType();
    if (blockType == '*') {
        // Create and immediately drop the star block
        shared_ptr<Block> starBlock = generateBlock(blockType);
        dropBlock(starBlock);
        // Get the actual next block after star block
        blockType = level->getNextBlockType();
    }
    nextBlock = generateBlock(blockType);
}

/*
levelUp increases the current level by 1 and updates the level pointer accordingly.
*/
void Board::levelUp() {
    int curLevel = level->getLevel() + 1;
    level = levelFactory.create(curLevel);
}

/*
levelDown decreases the current level by 1 and updates the level pointer accordingly.
*/
void Board::levelDown() {
    int curLevel = level->getLevel() - 1;
    level = levelFactory.create(curLevel);
}

/*
setLevel sets the current level to a new level provided as a unique pointer.
*/
void Board::setLevel(unique_ptr<Level> newLevel) {
    level = std::move(newLevel);
}

/*
rotate works by calculating the proposed new positions for the active block after rotation.
It then checks if these new positions are valid using isValidMove.
If the rotation is valid, it updates the block's position and places it on the board.
*/
void Board::rotate(bool clockwise) {
    vector<pair<int,int>> tempPos = activeBlock->rotatePosition(!clockwise);
    clearBlock(activeBlock);
    if (isValidMove(tempPos)) {
        activeBlock->setPosition(tempPos);
    }
    placeBlock(activeBlock);
}

/*
forceBlockType forces the next active block to be of the specified type. It is meant
for special affects and testing purposes. It generates a new block of the given type,
clears the current active block from the board, and places the new block as the active block.
*/
void Board::forceBlockType(char type) {
    shared_ptr<Block> force = generateBlock(type);
    clearBlock(activeBlock);
    activeBlock = force;
    placeBlock(activeBlock);
}

/*
applyHeavy applies heaviness to the active block by attempting to move it down additional rows
based on the level's heaviness factor plus any additional heaviness specified. 
If the block cannot move down due to being blocked, it is auto-dropped and the turn ends.
*/
bool Board::applyHeavy(int additionalHeavy) {
    int heaviness = additionalHeavy + level->getHowHeavy();
    if (heaviness == 0) return false;
    
    for (int i = 0; i < heaviness; i++) {
        vector<pair<int, int>> oldPos = activeBlock->getPosition();
        move(0, 1);
        vector<pair<int, int>> newPos = activeBlock->getPosition();
        
        // If block didn't move down, it's blocked
        if (oldPos == newPos) {
            // Block is blocked and has heaviness, so auto-drop
            drop();
            return true; // Turn ended due to auto-drop
        }
    }
    return false; // No auto-drop occurred
}

/*
checkGameOver checks if the game is over by verifying if the active block can be placed
and then returns true if the game is over, false otherwise.
*/
bool Board::checkGameOver() {
    vector<pair<int,int>> spawnPos = activeBlock->getPosition();
    return !isValidMove(spawnPos);
}

/*
checkCompletedRows checks each row of the board to see if it is completely filled with blocks.
If a row is complete, its index is added to the completedRows vector, which is returned at the end.
*/
vector<int> Board::checkCompletedRows() {
    vector<int> completedRows;
    for (int row = 0; row < height; ++row) {
        // assume row is complete
        bool complete = true;
        for (int col = 0; col < width; ++col) {
            if (!grid[col][row]) {
                complete = false;
                break;
            }
        }
        if (complete) completedRows.push_back(row);
    }
    return completedRows;
}

/*
clearRow works by first clearing the specified row from the board grid,
then shifting all rows above it down by one. It also calculates and returns the score
obtained from clearing the row based on the blocks and levels of the blocks involved.
*/
int Board::clearRow(int row) {
    int score = 0;
    
    // First, clear the completed row and calculate score
    for (int col = 0; col < width; ++col) {
        if (grid[col][row]) {
            if (grid[col][row]->decreaseCells()) {
                score += grid[col][row]->getLevelGenerated() + 1;
            }
            grid[col][row] = nullptr;
        }
    }
    
    // Then shift rows down
    for (; row > 0; --row) {
        for (int col = 0; col < width; ++col) {
            grid[col][row] = std::move(grid[col][row-1]);
        }
    }
    
    // Clear top row
    for (int col = 0; col < width; ++col) {
        grid[col][0] = nullptr;
    }
    
    return score;
}

// Destructor for Board class
Board::~Board() {};
