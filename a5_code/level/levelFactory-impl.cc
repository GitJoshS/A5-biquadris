/* 
Filename: levelFactory-impl.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file contains the implementation of the LevelFactory class for the Biquadris game.
The level factory is responsible for creating instances of different Level classes based on the specified level number.
*/

module LevelFactory;

import Level0;
import Level1;
import Level2;
import Level3;
import Level4;

using namespace std;

/*
This function creates and returns a unique pointer to a Level object based on the provided level number.
*/
unique_ptr<Level> LevelFactory::create(int level) {
    switch(level) {
        case 0: return make_unique<Level0>();
        case 1: return make_unique<Level1>();
        case 2: return make_unique<Level2>();
        case 3: return make_unique<Level3>();
        case 4: return make_unique<Level4>();
        default: return make_unique<Level0>();
    }
}

/*
This function creates and returns a unique pointer to a Level object based on the provided level number and 
input file stream.
*/
unique_ptr<Level> LevelFactory::create(int level, ifstream& f) {
    switch(level) {
        case 0: return make_unique<Level0>(f);
        case 1: return make_unique<Level1>(f);
        case 2: return make_unique<Level2>(f);
        case 3: return make_unique<Level3>(f);
        case 4: return make_unique<Level4>(f);
        default: return make_unique<Level0>(f);
    }
}
