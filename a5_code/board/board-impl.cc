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
import Level;
import LevelFactory;

using namespace std;

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
    activeBlock = generateNext(blockType);
    placeBlock(activeBlock);
    blockType = level->getNextBlockType();
    nextBlock = generateNext(blockType);
}

int Board::getWidth() {
    return width;
}

int Board::getHeight() {
    return height;
}

shared_ptr<Block> Board::getNextBlock() const {
    return nextBlock;
}

shared_ptr<Block> Board::getActiveBlock() const {
    return activeBlock;
}

Level* Board::getLevel() const {
    return level.get();
}

const vector<vector<shared_ptr<Block>>>& Board::getGrid() const {
    return grid;
}

bool Board::isGameOver() const {
    return gameOver;
}

void Board::noRandomLevel(ifstream& file) {
    int curLevel = level->getLevel();
    level = levelFactory.create(curLevel, file);
}

void Board::restoreRandomLevel() {
    int curLevel = level->getLevel();
    level = levelFactory.create(curLevel);
}

bool Board::isValidMove(vector<pair<int, int>> newPosn) const { //Linh: This might have a problem, it might collide with itself. For instance, if an L shape moves down, the tip of the L moving would coincide with its own block, and this function would return false
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

//Linh: Is this assuming the position is valid and the block just have to "lock in place"?
void Board::placeBlock(shared_ptr<Block> block) {
    /*IMPLEMENT THIS*/
     for (const std::pair<int, int>& coord : block->getPosition()) {
        int col = coord.first;
        int row = coord.second;
        grid[col][row] = block;
     }
}

bool Board::drop() { //Added by Linh
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

bool Board::dropBlock(shared_ptr<Block> block) { //Added by Linh
    while (true) {
        vector<pair<int, int>> tempPos = block->getPosition();
        for (auto& coord : tempPos) {
            coord.second += 1; 
        } 
        if (isValidMove(tempPos)) {
            block->setPosition(tempPos);
        }
        else {
            placeBlock(block);
            break;
        }
    }
    if (block->getType() != '*') {
        nextTurn();
        return true;
    }
    return false;
}

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
    } 
    // else if (y > 0) {
    //     return drop();
    // }
    placeBlock(activeBlock);
    return false;
}

//! GET THIS SHIT OUTTA HERE
shared_ptr<Block> Board::generateNext(char type) {
    int lev = level->getLevel();
    switch(type) {
        case 'I': return make_shared<IBlock>(lev);
        case 'J': return make_shared<JBlock>(lev);
        case 'L': return make_shared<LBlock>(lev);
        case 'O': return make_shared<OBlock>(lev);
        case 'S': return make_shared<SBlock>(lev);
        case 'Z': return make_shared<ZBlock>(lev);
        case 'T': return make_shared<TBlock>(lev);
    }
    return nullptr;
}

void Board::nextTurn() {
    activeBlock = nextBlock;
    placeBlock(activeBlock);
    if (!checkGameOver()) {
        placeBlock(activeBlock);
    }
    else {
        gameOver = true;
        return;
    }
    char blockType = level->getNextBlockType();
    nextBlock = generateNext(blockType);
}

void Board::levelUp() {
    int curLevel = level->getLevel() + 1;
    level = levelFactory.create(curLevel);
}

void Board::levelDown() {
    int curLevel = level->getLevel() - 1;
    level = levelFactory.create(curLevel);
}

void Board::setLevel(unique_ptr<Level> newLevel) {
    level = std::move(newLevel);
}

void Board::rotate(bool clockwise) {
    vector<pair<int,int>> tempPos = activeBlock->rotatePosition(clockwise);
    if (isValidMove(tempPos)) {
        clearBlock(activeBlock);
        activeBlock->setPosition(tempPos);
        placeBlock(activeBlock);
    }
}
bool Board::checkGameOver() {
    vector<pair<int,int>> spawnPos = activeBlock->getPosition();
    return !isValidMove(spawnPos);
}


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


int Board::clearRow(int row) {
    // for each row from "row" to 0
    int score = 0;
    for (; row >= 0; --row) {
        // each column in the row
        for (int col = 0; col < width; ++col) {
            // edge case at top row
            if (row >= 1) {
                grid[col][row] = grid[col][row-1];
            } else {
                //Linh added: minus cellsLeft from Block and check if cells are all cleared
                if (grid[col][row]->decreaseCells()) {
                    score += (grid[col][row]->getLevelGenerated() + 1)*(grid[col][row]->getLevelGenerated() + 1);
                }
                grid[col][row] = nullptr;
            }
        }
    }
    return score;
}


Board::~Board() {/*Does block own any ptrs? -Linh: idk but we dont hv to do memory management*/};

