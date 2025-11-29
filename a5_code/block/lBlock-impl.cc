/* 
Filename: lBlock-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the implementation for the LBlock class, which represents the "L" shaped block in the Biquadris game.
*/
module LBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

LBlock::LBlock(int level) : Block{'L', level, 4, {{0,3}, {1,3}, {2,2}, {2,3}}} {}
