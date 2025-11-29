/* 
Filename: oBlock.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the interface for the OBlock class, which represents the "O" shaped block in the Biquadris game.
*/

export module OBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

export class OBlock : public Block{  
    public:
        /*
        Purpose: constructor for OBlock class.
        @param: level - level at which the block was generated
        returns: OBlock object
        */
        OBlock(int level);
};
