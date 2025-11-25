export module LBlock;

import string;
import utility;
import vector;
import Block;

export class LBlock : public Block{
    int tilesLeft;
    
    public:
    LBlock(int level);
    char getShape();
}
