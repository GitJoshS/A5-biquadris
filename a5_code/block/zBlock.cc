/* 
Filename: zBlock.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the interface for the ZBlock class, which represents the "Z" shaped block in the Biquadris game.
*/

export module ZBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

export class ZBlock : public Block{
    public:
        /*
        Purpose: constructor for ZBlock class.
        @param: level - level at which the block was generated
        returns: ZBlock object
        */
        ZBlock(int level);
};
