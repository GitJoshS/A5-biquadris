/* 
Filename: levelFactory.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file contains the implementation of the LevelFactory class for the Biquadris game.
The level factory is responsible for creating instances of different Level classes based on the specified level number.
*/

export module LevelFactory;

import <fstream>;
import <memory>;
import Level;

using namespace std;

export class LevelFactory {
    public:
        /*
        Purpose: This function creates and returns a unique pointer to a Level object based on the provided level number.
        @params: levelNum - integer representing the level number
        returns: unique_ptr to Level object
        */
        unique_ptr<Level> create(int levelNum);

        /*
        Purpose: This function creates and returns a unique pointer to a Level object based on the provided level number and
        input file stream.
        @params: levelNum - integer representing the level number
                 f - input file stream
        returns: unique_ptr to Level object
        */
        unique_ptr<Level> create(int levelNum, ifstream& f);
};
