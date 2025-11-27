 module IBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

IBlock::IBlock(int level) : Block{'I', level, 4, {{0,3}, {1,3}, {2,3}, {3,3}}} {}
