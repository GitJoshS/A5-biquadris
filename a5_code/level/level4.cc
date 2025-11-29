/* 
Filename: level4.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file contains the implementation of the Level4 class for the Biquadris game.
*/

export module Level4;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;
import Level;

using namespace std;

export class Level4 : public Level {
    vector<char> sequence;
    int currentIndex;
    bool useSequence;
    int count;
    
    public: 
        /*
        Purpose: constructor for Level4 class.
        @params: None
        returns: Level4 object
        */
        Level4();

        /*
        Purpose: constructor for Level4 class that takes in a file stream. File stream contains the sequence.
        @param: f - input file stream containing the sequence for the blocks to be generated
        returns: Level4 object
        */
        Level4(ifstream& f);

        /*
        Purpose: getNextBlockType works by first checking if a sequence is being used. If so, it returns the next block type
            in the sequence, cycling through it as needed. If no sequence is used, it generates a random number
            and maps it to a block type according to Level 4 rules for probabilities. Additionally, every 5th block returned is a '*' block.
            Also it sets howHeavy to 1.
        @param: None
        returns: character representing the next block type
        */
        char getNextBlockType() override;
};
