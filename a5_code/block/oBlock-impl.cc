module OBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

OBlock::OBlock(int level) : Block{'O', level, 4, {{0,2}, {0,3}, {1,2}, {1,3}}} {}
