/* 
Filename: commandCenter.cc 
Author: Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the implementation of the Game class, which manages the overall game state,
*/

export module CommandCenter;    

// import Command;
import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import Board;
import Player;


using namespace std;

export class CommandCenter {
    vector<string> commandList; 

    vector<string> loadCommandsFromFile();
    string findUniqueCommand(const string &input);
    
    public:
        CommandCenter();

        string processCmd(string cmd, int* multiplier);
        
        bool executeCmd(string cmd, Player* currentPlayer, Player* otherPlayer, int mult);
        bool executeSpecialEffectsCmd(string cmd, Player* currentPlayer, Player* otherPlayer);
};
