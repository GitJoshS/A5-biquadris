/* 
Filename: commandCenter.cc 
Author: Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the implementation of the Game class, which manages the overall game state,
*/

export module CommandCenter;    

// import Display;
// import Board;

import Command;

import <string>;

using namespace std;

export class CommandCenter {
    vector<string> commandList; 
    // will probably change to:
    // vector<sting> commandList;

    vector<string> loadCommandsFromFile();
    string findUniqueCommand(const string &input);
    
    public:
        CommandCenter() {
            commandList = loadCommandsFromFile();
        }

        Command processCmd(string);
        void executeCmd(Command*);
};
