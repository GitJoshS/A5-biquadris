export module IBlock;

import string;
import utility;
import vector;
import Block;

using namespace std;

export class IBlock : public Block{
    int tilesLeft;

    public:
    IBlock(int level);
}
