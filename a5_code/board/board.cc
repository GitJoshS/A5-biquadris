export module Board;

import <utility>;
import <vector>;
import <memory>;
import Block;
import Level;

using namespace std;

export class Board {
    int width;
    int height;
    shared_ptr<Block> nextBlock;
    shared_ptr<Block> activeBlock;
    unique_ptr<Level> level;
    vector<vector<shared_ptr<Block>>> grid; // grid[col][row]
    bool gameOver;
    string sequenceFile;

    shared_ptr<Block> generateNext(char type);

    public:
        Board(int width = 11, int height = 18, int startLevel = 0, string sequenceFile = "");

        int getWidth();
        int getHeight();
        shared_ptr<Block> getNextBlock() const;
        shared_ptr<Block> getActiveBlock() const;
        Level* getLevel() const;
        vector<vector<shared_ptr<Block>>>& getGrid() const;
        bool isGameOver() const;

        // Replace the current level with another level pointer that generate blocks in a non-random order
        void noRandomLevel(ifstream& file);
        // Restore randomness
        void restoreRandomLevel();

        bool isValidMove(vector<std::pair<int, int>> newPosn) const;
        bool drop(shared_ptr<Block> block = activeBlock); //Linh added this
        // Check whether the move is valid, if it is then move, if not do nothing
        bool move(int x, int y); //Linh added this
        // Generate new nextBlock and make the old nextBlock the activeBlock after a block is dropped
        void nextTurn(); //Linh added this
        void levelUp();
        void levelDown();
        void setLevel(unique_ptr<Level> newLevel);
        void rotate(bool clockwise);
        void placeBlock(shared_ptr<Block> block);
        bool checkGameOver();
        vector<int> checkCompletedRows();
        void clearRow(int row);

        ~Board();
};

//Linh's note: After a block is considered "drop", what class call the next behaviours (replace activeBlock with nextBlock, generate nextBlock)