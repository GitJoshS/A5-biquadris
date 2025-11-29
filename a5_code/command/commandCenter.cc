/* 
Filename: commandCenter.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file is the interface for the CommandCenter class, which serves as the 
central hub for command processing in the Biquadris game.
*/

export module CommandCenter;    

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
        /*
        Purpose: constructor for CommandCenter class.
        @param: None
        returns: CommandCenter object
        requires: None
        */ 
        CommandCenter();

        /*
        Purpose: Process command string to extract multiplier and command.
            For example "3left" becomes multiplier=3, cmd="left".
        @param: cmd - command string
                 multiplier - pointer to int to store extracted multiplier
        returns: processed command string
        requires: multiplier is a valid pointer
        */
        string processCmd(string cmd, int* multiplier);
        
        /*
        Purpose: Execute the given command for the current player. For example,
            left" moves the block left, "drop" drops the block, etc.
        @param: cmd - command string, currentPlayer - pointer to current Player,
                 otherPlayer - pointer to the other Player, mult - multiplier for command
        returns: true if the turn has ended, false otherwise
        requires: currentPlayer and otherPlayer are valid Player pointers
        */
        bool executeCmd(string cmd, Player* currentPlayer, Player* otherPlayer, int mult);

        /*
        Purpose: Execute special effects command after turn ends. For example,
            "blind" applies blind effect to other player, etc.
        @param: cmd - command string, currentPlayer - pointer to current Player,
                otherPlayer - pointer to the other Player
        returns: true if the turn has ended, false otherwise
        */
        bool executeSpecialEffectsCmd(string cmd, Player* currentPlayer, Player* otherPlayer);
};
