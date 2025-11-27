module IBlock;

import string;
import utility;
import vector;
import Block;

using namespace std;

IBlock::IBlock(int level) : tilesLeft{4}, blockType{'I'}, levelGenerated{level},
                            cells{{0,3}, {1,3}, {2,3}, {3,3}}{}
