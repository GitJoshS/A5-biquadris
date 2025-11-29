/* 
Filename: iBlock-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the implementation for the IBlock class, which represents the "I" shaped block in the Biquadris game.
*/

module IBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

IBlock::IBlock(int level) : Block{'I', level, 4, {{0,3}, {1,3}, {2,3}, {3,3}}} {}
