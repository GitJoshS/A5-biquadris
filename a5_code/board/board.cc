export module Board;

import <utility>;
import <vector>;
import Block;

export Board {
    // grid[row][column]
    vector<vector<Block*>> grid;
    Block* nextBlock;
    Block* activeBlock;
    Level* level;
    int height;
    int width;

    Board(int height, int width);

    bool isValidMove(Block*, vector<std::pair<int, int>> newPosn)
    void placeBlock(Block* block);
    void checkGameOver();
    void checkCompletedRows();
    void clearRow(int row);

    ~Board();
};



