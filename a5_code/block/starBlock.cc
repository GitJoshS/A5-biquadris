/* 
Filename: sBlock.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
Contains the interface for the starBlock class, which represents the "*" shaped block in the Biquadris game.
*/

export module starBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

export class starBlock : public Block{
    public:
        /*
        Purpose: constructor for starBlock class.
        @param: None
        returns: starBlock object
        */
        starBlock();
};
