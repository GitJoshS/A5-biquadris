export module ZBlock;

import string;
import utility;
import vector;
import Block;

export class IBlock : public Block{
    int tilesLeft;
    
    public:
    ZBlock(int level);
    char getShape();
}
