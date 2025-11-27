module SBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

SBlock::SBlock(int level) : Block{}, cellsLeft{4}, blockType{'S'}, levelGenerated{level}, curRotation{0},
                            cells{{0,3}, {1,2}, {1,3}, {2,2}}{}
