/* 
Filename: sBlock-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the implementation for the SBlock class, which represents the "S" shaped block in the Biquadris game.
*/

module SBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

SBlock::SBlock(int level) : Block{'S', level, 4, {{0,3}, {1,2}, {1,3}, {2,2}}}{}
