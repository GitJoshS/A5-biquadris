module TBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

TBlock::TBlock(int level) : Block{'T', level, 4, {{0,2}, {1,2}, {1,3}, {2,2}}}{}
