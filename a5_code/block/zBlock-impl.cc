/* 
Filename: zBlock-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the implementation for the ZBlock class, which represents the "Z" shaped block in the Biquadris game.
*/

module ZBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

ZBlock::ZBlock(int level) : Block{'Z', level, 4, {{0,2}, {1,2}, {1,3}, {2,3}}} {}
