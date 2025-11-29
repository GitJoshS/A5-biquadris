/* 
Filename: level0.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This files contains the interface for the Level0 class, which is a derived class of Level 
representing level 0 in the Biquadris game.
*/

export module Level0;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;
import Level;

using namespace std;

/*
Level0 class representing level 0 in the Biquadris game.
*/
export class Level0 : public Level {
    vector<char> sequence;
    int currentIndex;
    
    public: 
        /*
        Purpose: constructor for Level0 class.
        @param: None
        returns: Level0 object
        */
        Level0();

        /*
        Purpose: constructor for Level0 class that takes in a file stream. File stream contains the sequence
        @param: f - input file stream containing the sequence for the blocks to be generated
        returns: Level0 object
        */
        Level0(ifstream& f);

        /*
        Purpose: gets the next block type in the sequence. Works by cycling through the sequence vector.
                It then returns the character at the current index and increments the index, wrapping around
        @param: None
        returns: character representing the next block type
        */
        char getNextBlockType() override;
};
