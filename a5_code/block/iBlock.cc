/* 
Filename: iBlock.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the interface for the IBlock class, which represents the "I" shaped block in the Biquadris game.
*/

export module IBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

export class IBlock : public Block{

    public:
        /*
        Purpose: constructor for IBlock class.
        @param: level - level at which the block was generated
        returns: IBlock object
        */
        IBlock(int level);
};
