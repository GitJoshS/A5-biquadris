/* 
Filename: level0-impl.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file contains the implementation of the Level0 class for the Biquadris game.
*/

module Level0;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;

using namespace std;

/*
Constructor for Level0 class.
*/
Level0::Level0() : Level(0), currentIndex{0} {
    level = 0;
    howHeavy = 0;
    sequence = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
}

/*
Constructor for Level0 class that takes in a file stream. File stream contains the sequence
*/
Level0::Level0(ifstream& f) : Level(0), currentIndex{0} {
    level = 0;
    howHeavy = 0;
    char c;
    while (f >> c) {
        sequence.push_back(c);
    }
    if (sequence.empty()) {
        sequence = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    }
}

/*
Gets the next block type in the sequence. Works by cycling through the sequence vector.
It then returns the character at the current index and increments the index, wrapping around
*/
char Level0::getNextBlockType(){
    if (sequence.empty()) return 'I';
    char result = sequence[currentIndex];
    currentIndex = (currentIndex + 1) % sequence.size();
    return result;
}
