module OBlock;

import string;
import utility;
import vector;
import Block;

OBlock::OBlock(int level) : cellsLeft{4}, blockType{'O'}, levelGenerated{level}, curRotation{0},
                            cells{{0,2}, {0,3}, {1,2}, {1,3}}{}
