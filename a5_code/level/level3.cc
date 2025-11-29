
/* 
Filename: level3.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file contains the implementation of the Level3 class for the Biquadris game.
*/

export module Level3;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;
import Level;

using namespace std;

export class Level3 : public Level {
    vector<char> sequence;
    int currentIndex;
    bool useSequence;
    
    public: 
        /*
        Purpose: constructor for Level3 class.
        @params: None
        returns: Level3 object
        */
        Level3();

        /*
        Purpose: constructor for Level3 class that takes in a file stream. File stream contains the sequence
        @param: f - input file stream containing the sequence for the blocks to be generated
        returns: Level3 object
        */
        Level3(ifstream& f);

        /*
        Purpose: getNextBlockType works by first checking if a sequence is being used. If so, it returns the next block type
            in the sequence, cycling through it as needed. If no sequence is used, it generates a random number
            and maps it to a block type according to Level 3 rules for probabilities.
        @param: None
        returns: character representing the next block type
        */
        char getNextBlockType() override;
};
