/* 
Filename: jBlock-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the implementation for the JBlock class, which represents the "J" shaped block in the Biquadris game.
*/

module JBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

JBlock::JBlock(int level) : Block{'J', level, 4, {{0,2}, {0,3}, {1,3}, {2,3}}} {}
