/* 
Filename: level1-impl.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file contains the implementation of the Level1 class for the Biquadris game.
*/

module Level1;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;

using namespace std;

/*
Constructor for Level1 class.
*/
Level1::Level1() : Level(1), currentIndex{0}, useSequence{false} {
    level = 1;
    howHeavy = 0;
}

/*
Constructor for Level1 class that takes in a file stream. File stream contains the sequence
*/
Level1::Level1(ifstream& f) : Level(1), currentIndex{0}, useSequence{true} {
    level = 1;
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
and maps it to a block type according to Level 1 rules for probabilities.
*/
char Level1::getNextBlockType(){
    if (useSequence && !sequence.empty()) {
        char result = sequence[currentIndex];
        currentIndex = (currentIndex + 1) % sequence.size();
        return result;
    }
    
    int randomNum = rand() % 12;
    if (randomNum == 1) return 'S';
    else if (randomNum == 2) return 'Z';
    else if (randomNum <= 4) return 'I';
    else if (randomNum <= 6) return 'J';
    else if (randomNum <= 8) return 'L';
    else if (randomNum <= 10) return 'O';
    else return 'T';
}
