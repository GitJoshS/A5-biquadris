module ZBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

ZBlock::ZBlock(int level) : Block{'Z', level, 4, {{0,2}, {1,2}, {1,3}, {2,3}}} {}
