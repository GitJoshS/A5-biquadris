/* 
Filename: oBlock-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the implementation for the OBlock class, which represents the "O" shaped block in the Biquadris game.
*/

module OBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

OBlock::OBlock(int level) : Block{'O', level, 4, {{0,2}, {0,3}, {1,2}, {1,3}}} {}
