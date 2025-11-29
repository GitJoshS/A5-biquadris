/* 
Filename: level2-impl.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file contains the implementation of the Level2 class for the Biquadris game.
*/

module Level2;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;

using namespace std;

/*
Constructor for Level2 class.
*/
Level2::Level2() : Level(2), currentIndex{0}, useSequence{false} {
    level = 2;
    howHeavy = 0;
}

/*
Constructor for Level2 class that takes in a file stream. File stream contains the sequence
*/
Level2::Level2(ifstream& f) : Level(2), currentIndex{0}, useSequence{true} {
    level = 2;
    howHeavy = 0;
    char c;
    while (f >> c) {
        sequence.push_back(c);
    }
    if (sequence.empty()) {
        useSequence = false;
    }
}

/*
getNextBlockType works by first checking if a sequence is being used. If so, it returns the next block type
in the sequence, cycling through it as needed. If no sequence is used, it generates a random number
and maps it to a block type according to Level 2 rules for probabilities.
*/
char Level2::getNextBlockType(){
    // If file sequence is being used, read from sequence
    if (useSequence && !sequence.empty()) {
        char result = sequence[currentIndex];
        currentIndex = (currentIndex + 1) % sequence.size();
        return result;
    }

    // No file was given - Level 2: Equal probability for all blocks
    const vector<char> blocks = {'I', 'J', 'L', 'S', 'Z', 'O', 'T'};
    int randomNum = rand() % 7;
    return blocks[randomNum];
}
