/* 
Filename: commandCenter.cc 
Author: Josh Stein
Date: 2024-06-15
Last Edited: 2024-06-15

Description:
This file contains the implementation of the Game class, which manages the overall game state,
*/

export module CommandCenter;    

import <string>;

using namespace std;

export class CommandCenter {
    vector<Command *> commands;

    public:
        Command processCmd(string);
        void executeCmd(Command*);
}
