export module OBlock;

import string;
import utility;
import vector;
import Block;

export class OBlock : public Block{
    int tilesLeft;
    
    public:
    OBlock(int level);
    char getShape();
}
