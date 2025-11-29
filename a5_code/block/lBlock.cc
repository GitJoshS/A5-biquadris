/* 
Filename: lBlock.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the interface for the LBlock class, which represents the "L" shaped block in the Biquadris game.
*/

export module LBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

export class LBlock : public Block{

    public:
        /*
        Purpose: constructor for LBlock class.
        @param: level - level at which the block was generated
        returns: LBlock object
        */
        LBlock(int level);
};
