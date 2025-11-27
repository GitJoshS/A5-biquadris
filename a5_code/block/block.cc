export module Block;

import string;
import utility;
import vector;

using namespace std; 

export class Block {
    protected:
    char blockType;
    int levelGenerated;
    int cellsLeft;
    vector<pair<int,int>> cells; //Position of the cells in the block on a board

    public:
    Block() {}
    //Returns the coordinate of the new position if the block to be rotated
    vector<pair<int,int>> rotatePosition(bool clockwise);
    //Set the position of the block to a new position
    void setPosition(vector<pair<int,int>>& newPos);
    //When a cell in a block is destroy, decrease the amount of cell that block has by 1. 
    // If it reaches 0, return true. Otherwise, return false
    bool decreaseCells();
    virtual char getType();
    virtual vector<pair<int,int>> getPosition();
    virtual ~Block() = default;
}
