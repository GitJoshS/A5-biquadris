export module TBlock;

import string;
import utility;
import vector;
import Block;

export class TBlock : public Block{
    int tilesLeft;
    
    public:
    TBlock(int level);
    char getShape();
}
