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
        Board(int width = 11, int height = 18); //Linh changed height to 18`

        int getWidth();
        int getHeight();
        Block* getNextBlock() const;
        Block* getActiveBlock() const;
        Level* getLevel() const;
        vector<vector<Block*>>& getGrid() const;

        /*Need to call level to generate next block at some point*/

        bool isValidMove(vector<std::pair<int, int>> newPosn) const;
        void drop(); //Linh added this
        // Check whether the move is valid, if it is then move, if not do nothing
        void move(int x, int y); //Linh added this
        void placeBlock(Block* block);
        bool checkGameOver();
        vector<int> checkCompletedRows();
        void clearRow(int row);

        ~Board();
};

//Linh's note: After a block is considered "drop", what class call the next behaviours (replace activeBlock with nextBlock, generate nextBlock)