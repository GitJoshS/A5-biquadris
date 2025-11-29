/* 
Filename: starBlock-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the implementation for the starBlock class, which represents the "*" shaped block in the Biquadris game.
*/

module starBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

starBlock::starBlock() : Block{'*', 4, 1, {{5,0}}}{}
