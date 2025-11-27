module starBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

starBlock::starBlock() : Block{}, cellsLeft{1}, blockType{'*'}, levelGenerated{4},
                            cells{{0,5}}{}
