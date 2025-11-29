/* 
Filename: level-impl.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This files contains the implementation for the Level class, which serves as a base class for different 
levels in the Biquadris game.
*/

module Level;

import <vector>;

using namespace std;

/*
Regular constructor for Level class. Note, howHeavy is initialized to 0 so blocks don't
go down when move commands are used 
*/
Level::Level(int level) : level{level}, howHeavy{0} {}

/*
consturctor for Level class that takes in a file stream. File stream contains the sequence
for the blocks to be generated.
*/
Level::Level(int level, ifstream& file) :  level{level}, file{std::move(file)}, howHeavy{0} { }

/*
Purpose: getter for howHeavy attribute.
*/
int Level::getHowHeavy() {
    return howHeavy;
}

/*
gets the level number
*/
int Level::getLevel() {
    return level;
}

/*
Destructor for Level class.
*/
Level::~Level() {
    if (file.is_open()) file.close();
}
    