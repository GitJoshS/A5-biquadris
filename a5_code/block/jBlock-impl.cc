module JBlock;

import string;
import utility;
import vector;
import Block;

JBlock::JBlock(int level) : cellsLeft{4}, blockType{'J'}, levelGenerated{level}, curRotation{0},
                            cells{{0,2}, {0,3}, {1,3}, {2,3}}{}
