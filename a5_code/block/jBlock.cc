/* 
Filename: jBlock.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the interface for the JBlock class, which represents the "J" shaped block in the Biquadris game.
*/

export module JBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

export class JBlock : public Block{  
    public:
        /*
        Purpose: constructor for JBlock class.
        @param: level - level at which the block was generated
        returns: JBlock object
        */
        JBlock(int level);
};
