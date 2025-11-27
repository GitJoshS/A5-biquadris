module JBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

JBlock::JBlock(int level) : Block{'J', level, 4, {{0,2}, {0,3}, {1,3}, {2,3}}} {}
