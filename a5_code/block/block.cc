export module Block;

import string;
import utility;
import vector;

using namespace std; 

export class Block {
    protected:
    char blockType;
    int levelGenerated;
    int curRotation;
    vector<pair<int,int>> cells; //Position of the cells in the block on a board

    public:
    Block() {}
    //Returns the coordinate of the new position if the block to be rotated
    virtual vector<pair<int,int>> rotatePosition(bool clockwise);
    virtual vector<pair<int,int>> getPosition();
    //Set the position of the block to a new position
    virtual void setPosition(vector<pair<int,int>>& newPos);
    virtual ~Block() = default;
}
