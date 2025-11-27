export module Board;

import <utility>;
import <vector>;
import <memory>
import Block;
import Level;

using namespace std;

export class Board {
    int width;
    int height;
    shared_ptr<Block> nextBlock;
    shared_ptr<Block> activeBlock;
    Level* level;
    vector<vector<shared_ptr<Block>>> grid; // grid[col][row]

    shared_ptr<Block> generateNext(char type);

    public:
        Board(int width = 11, int height = 18); //Linh changed height to 18`
        Board(int width = 11, int height = 18, int lev); // In case user wants to provid initial level

        int getWidth();
        int getHeight();
        shared_ptr<Block> getNextBlock() const;
        shared_ptr<Block> getActiveBlock() const;
        Level* getLevel() const;
        vector<vector<shared_ptr<Block>>>& getGrid() const;

        /*Need to call level to generate next block at some point*/

        bool isValidMove(vector<std::pair<int, int>> newPosn) const;
        void drop(shared_ptr<Block> block = activeBlock); //Linh added this
        // Check whether the move is valid, if it is then move, if not do nothing
        void move(int x, int y); //Linh added this
        // Generate new nextBlock and make the old nextBlock the activeBlock after a block is dropped
        void nextTurn(); //Linh added this
        void levelUp();
        void levelDown();
        void rotate(bool clockwise);
        void placeBlock(shared_ptr<Block> block);
        bool checkGameOver();
        vector<int> checkCompletedRows();
        void clearRow(int row);

        ~Board();
};

//Linh's note: After a block is considered "drop", what class call the next behaviours (replace activeBlock with nextBlock, generate nextBlock)