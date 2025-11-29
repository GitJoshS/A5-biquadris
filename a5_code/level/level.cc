/* 
Filename: level.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This is the interface for the Level class, which serves as a base class for different
levels in the Biquadris game.
*/

export module Level;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

export class Level {
    protected:
        int level;
        ifstream file;
        int howHeavy;

    public:
        /*
        Purpose: constructor for Level class.
        @param: level - the level number
        returns: Level object
        */
        Level(int level);

        /*
        Purpose: constructor for Level class that takes in a file stream. File stream contains the sequence
            for the blocks to be generated.
        @param: level - the level number
                file - input file stream containing the sequence for the blocks to be generated
        returns: Level object
        */
        Level(int level, ifstream& file);

        /*
        Purpose: pure virtual function to get the next block type. the block type that should 
                appears next ('I', 'J', 'L', 'O', 'S', 'Z', 'T')
        @param: None
        returns: character representing the next block type
        */
        virtual char getNextBlockType() = 0;  

        /*
        Purpose: getter for howHeavy attribute.
        @param: None
        returns: howHeavy value
        */
        virtual int getHowHeavy();

        /*
        Purpose: gets the level number
        @param: None
        returns: level number
        */
        int getLevel();

        /*
        Purpose: destructor for Level class.
        @param: None
        returns: None
        */
        virtual ~Level();
};
