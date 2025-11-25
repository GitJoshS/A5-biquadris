export module JBlock;

import string;
import utility;
import vector;
import Block;

export class JBlock : public Block{
    int tilesLeft;
    
    public:
    JBlock(int level);
    char getShape();
}
