export module Board;

import <utility>;
import <vector>;
import Block;
import Level;

export class Board {
    int width;
    int height;
    Block* nextBlock;
    Block* activeBlock;
    Level* level;
    vector<vector<Block*>> grid; // grid[col][row]

    public:
        Board(int width = 11, int height = 15);

        int getWidth();
        int getHeight();
        Block* getNextBlock() const;
        Block* getActiveBlock() const;
        Level* getLevel() const;
        vector<vector<Block*>>& getGrid() const;

        /*Need to call level to generate next block at some point*/

        bool isValidMove(vector<std::pair<int, int>> newPosn) const;
        void placeBlock(Block* block);
        bool checkGameOver();
        vecotor<int> checkCompletedRows();
        void clearRow(int row);

        ~Board();
};
