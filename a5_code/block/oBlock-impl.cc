module OBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

OBlock::OBlock(int level) : cellsLeft{4}, blockType{'O'}, levelGenerated{level},
                            cells{{0,2}, {0,3}, {1,2}, {1,3}}{}
