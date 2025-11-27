export module Board;

import <utility>;
import <vector>;
import Block;

export Board {
    // grid[column][row]
    vector<vector<Block*>> grid;
    Block* nextBlock;
    Block* activeBlock;
    Level* level;
    int height;
    int width;

    public:
        Board(int height, int width);

        vector<vector<Block*>>& getGrid() const;
        Block* getNextBlock() const;
        Block* getActiveBlock() const;
        Level* getLevel() const;
        int getWidth();
        int getHeight();

        bool isValidMove(Block*, vector<std::pair<int, int>> newPosn)
        void placeBlock(Block* block);
        void checkGameOver();
        void checkCompletedRows();
        void clearRow(int row);

        ~Board();
};
