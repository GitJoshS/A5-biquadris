/* 
Filename: tBlock-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the implementation for the TBlock class, which represents the "T" shaped block in the Biquadris game.
*/
module TBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

TBlock::TBlock(int level) : Block{'T', level, 4, {{0,2}, {1,2}, {1,3}, {2,2}}}{}
