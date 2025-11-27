module Board;

import <utility>;
import <vector>;
import <memory>
import Block;
import Level;

using namespace std;

Board::Board(int width, int height) : width{width}, height{height} {
    // fill grid with nullptr
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            grid[col][row] = nullptr;
        }
    }
    // initialize level 0
    level = Level::create(0);
}

Board::Board(int width, int height, int lev) : width{width}, height{height} {
    // fill grid with nullptr
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            grid[col][row] = nullptr;
        }
    }
    // initialize level 
    level = Level::create(lev);
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
    return level;
}

vector<vector<shared_ptr<Block>>>& Board::getGrid() const {
    return grid;
}

void Board::noRandomLevel(ifstream& file) {
    int curLevel = level->getLevel();
    level = Level::create(curLevel, file);
}

void Board::restoreRandomLevel() {
    int curLevel = level->getLevel();
    level = Level::create(curLevel);
}

bool Board::isValidMove(vector<pair<int, int>> newPosn) const { //Linh: This might have a problem, it might collide with itself. For instance, if an L shape moves down, the tip of the L moving would coincide with its own block, and this function would return false
    // check each new coordinate of the block
    for (const std::pair<int, int>>& coord : newPosn) {
        int col = coord.first;
        int row = coord.second;
        // if block exists there or out of bounds, not valid
        if (grid[col][row] || (col > width || col < 0) || (row > height || row < 0)) {
            return false;
        }
    }
    return true;
}

//Linh: Is this assuming the position is valid and the block just have to "lock in place"?
void Board::placeBlock(shared_ptr<Block> block) {
    /*IMPLEMENT THIS*/
     for (const std::pair<int, int>>& coord : block->getPosition()) {
        int col = coord.first;
        int row = coord.second;
        grid[col][row] = block;
     }
}


void Board::drop(shared_ptr<Block> block) { //Added by Linh
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
    }
}

void Board::move(int x, int y) { 
    vector<pair<int, int>> tempPos = activeBlock->getPosition();
    for (auto& coord : tempPos) {
            coord.first += x;
            coord.second += y; 
        } 
    if (isValidMove(tempPos)) {
        activeBlock->setPosition(tempPos);
        placeBlock(activeBlock);
    }
}

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
    if (!checkGameOver()) {
        placeBlock(activeBlock);
    }
    else {
        //Condition if game is over? Maybe a bool field member?
        return;
    }
    char blockType = level->getNextBlockType();
    nextBlock = generateNext(blockType);
}

void Board::levelUp() {
    int curLevel = level->getLevel() + 1;
    level = Level::create(curLevel);  
}

void Board::levelDown() {
    int curLevel = level->getLevel() - 1;
    level = Level::create(curLevel);  
}

void Board::rotate(bool clockwise) {
    vector<pair<int,int>> tempPos = activeBlock->rotatePosition(clockwise);
    if (isValidMove(tempPos)) {
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
                    score += grid[col][row]->getLevelGenerated() + 1;
                }
                grid[col][row] = nullptr;
            }
        }
    }
    return score;
}


Board::~Board() {/*Does block own any ptrs? -Linh: idk but we dont hv to do memory management*/};

