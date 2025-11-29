/* 
Filename: display-impl.cc 
Author: Josh, Taim and Linh
Date: 2024-11-25
Last Edited: 2024-06-28

Description:
This file contains the implementation of the Display class, which serves as a base class for different types of game displays.
*/


module Display;


import <vector>;
import Player;

using namespace std;

/*
General constructor that initializes the Display with a list of players.
*/
Display::Display(vector<Player*> players) : players{players} {}

