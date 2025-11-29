/* 
Filename: tBlock.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the interface for the TBlock class, which represents the "T" shaped block in the Biquadris game.
*/
export module TBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

export class TBlock : public Block{   
    public:
        /*
        Purpose: constructor for TBlock class.
        @param: level - level at which the block was generated
        returns: TBlock object
        */
        TBlock(int level);
};
