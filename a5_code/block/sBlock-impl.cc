module SBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

SBlock::SBlock(int level) : Block{'S', level, 4, {{0,3}, {1,2}, {1,3}, {2,2}}}{}
