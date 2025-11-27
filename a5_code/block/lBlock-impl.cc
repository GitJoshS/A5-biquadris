module LBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

LBlock::LBlock(int level) : Block{}, cellsLeft{4}, blockType{'L'}, levelGenerated{level},
                            cells{{0,3}, {1,3}, {2,2}, {2,3}}{}
