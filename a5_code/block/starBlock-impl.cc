module starBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

starBlock::starBlock() : cellsLeft{4}, blockType{'*'}, levelGenerated{4},
                            cells{{0,0}}{}
