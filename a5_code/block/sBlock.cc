/* 
Filename: sBlock.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the interface for the SBlock class, which represents the "S" shaped block in the Biquadris game.
*/

export module SBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

export class SBlock : public Block{   
    public:
        /*
        Purpose: constructor for SBlock class.
        @param: level - level at which the block was generated
        returns: SBlock object
        */
        SBlock(int level);
};
