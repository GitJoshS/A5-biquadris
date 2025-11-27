module Board;

using namespace std;

Board::Board(int width, int height) : width{width}, height{height} {
    // fill grid with nullptr
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            grid[col][row] = nullptr;
        }
    }
}

int Board::getWidth() {
    return width;
}

int Board::getHeight() {
    return height;
}

Block* Board::getNextBlock() const {
    return nextBlock;
}

Block* Board::getActiveBlock() const {
    return activeBlock;
}

Level* Board::getLevel() const {
    return Level;
}

vector<vector<Block*>>& Board::getGrid() const {
    return grid;
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
void Board::placeBlock(Block* block) {
    /*IMPLEMENT THIS*/
     for (const std::pair<int, int>>& coord : block->getPosition()) {
        int col = coord.first;
        int row = coord.second;
        grid[col][row] = block;
     }
}


void Board::drop() { //Added by Linh
    while (true) {
        vector<pair<int, int>> tempPos = activeBlock->getPosition();
        for (auto& coord : tempPos) {
            coord.second += 1; 
        } 
        if (isValidMove(tempPos)) {
            activeBlock->setPosition(tempPos);
        }
        else {
            placeBlock(activeBlock);
            break;
        }
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


void Board::clearRow(int row) {
    // for each row from "row" to 0
    for (; row >= 0; --row) {
        // each column in the row
        for (int col = 0; col < width; ++col) {
            // edge case at top row
            if (row >= 1) {
                grid[col][row] = grid[col][row-1];
            } else {
                //Linh added: minus cellsLeft from Block and check if cells are all cleared
                if (grid[col][row]->decreaseCells()) {
                    //score += grid[col][row]->getLevelGenerated() + 1
                }
                grid[col][row] = nullptr;
            }
        }
    }
}


Board::~Board() {/*Does block own any ptrs? -Linh: idk but we dont hv to do memory management*/};

