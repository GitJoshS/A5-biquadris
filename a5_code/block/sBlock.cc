export module SBlock;

import string;
import utility;
import vector;
import Block;

export class SBlock : public Block{
    int tilesLeft;
    
    public:
    SBlock(int level);
    char getShape();
}