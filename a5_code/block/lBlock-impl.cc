module LBlock;

import string;
import utility;
import vector;
import Block;

LBlock::LBlock(int level) : cellsLeft{4}, blockType{'L'}, levelGenerated{level}, curRotation{0},
                            cells{{0,3}, {1,3}, {2,2}, {2,3}}{}
